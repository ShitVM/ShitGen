#include <sgn/Generator.hpp>

#include <stdexcept>

namespace sgn {
	Generator::Generator(const ByteFile& byteFile) noexcept
		: m_ByteFile(byteFile) {}

	void Generator::Generate(const std::string& path) {
		m_Stream.open(path, std::ofstream::binary);
		if (!m_Stream) throw std::runtime_error("Failed to open the file.");

		// Header
		static constexpr std::uint8_t magic[] = { 0x74, 0x68, 0x74, 0x68 };
		m_Stream.write(reinterpret_cast<const char*>(magic), sizeof(magic));
		Write(m_ByteFile.m_ShitBFVersion);
		Write(m_ByteFile.m_ShitBCVersion);

		// Dependencies
		const auto& dependencies = m_ByteFile.GetDependencies();
		Write(static_cast<std::uint32_t>(dependencies.size()));
		for (std::uint32_t i = 0; i < dependencies.size(); ++i) {
			const auto& depen = dependencies[i];
			Write(static_cast<std::uint32_t>(depen.size()));
			m_Stream.write(depen.c_str(), depen.size());
		}

		Generate(m_ByteFile.GetConstantPool());
		Generate(m_ByteFile.GetStructures());
		Generate(m_ByteFile.GetFunctions());
		Generate(m_ByteFile.GetMappings());
		Generate(*m_ByteFile.GetEntrypointInternal());
	}

	void Generator::Generate(const svm::core::ConstantPool& constantPool) {
		const auto& intPool = constantPool.GetIntPool();
		Write(static_cast<std::uint32_t>(intPool.size()));
		for (std::uint32_t i = 0; i < intPool.size(); ++i) {
			Write(intPool[i].Value);
		}

		const auto& longPool = constantPool.GetLongPool();
		Write(static_cast<std::uint32_t>(longPool.size()));
		for (std::uint32_t i = 0; i < longPool.size(); ++i) {
			Write(longPool[i].Value);
		}

		const auto& doublePool = constantPool.GetDoublePool();
		Write(static_cast<std::uint32_t>(doublePool.size()));
		for (std::uint32_t i = 0; i < doublePool.size(); ++i) {
			Write(doublePool[i].Value);
		}
	}
	void Generator::Generate(const Structures& structures) {
		Write(static_cast<std::uint32_t>(structures.size()));
		for (std::uint32_t i = 0; i < structures.size(); ++i) {
			const auto& fields = structures[i].Fields;

			Write(static_cast<std::uint32_t>(fields.size()));
			for (std::uint32_t j = 0; j < fields.size(); ++j) {
				if (fields[j].IsArray()) {
					Write(static_cast<std::uint32_t>(fields[j].Type->Code) | (1 << 31));
					Write(fields[j].Count);
				} else {
					Write(fields[j].Type->Code);
				}
			}
		}
	}
	void Generator::Generate(const Functions& functions) {
		Write(static_cast<std::uint32_t>(functions.size()));
		for (std::uint32_t i = 0; i < functions.size(); ++i) {
			const auto& func = functions[i];

			Write(func.Arity);
			Write(func.HasResult);
			Generate(func.Instructions);
		}
	}
	void Generator::Generate(const svm::Mappings& mappings) {
		const std::uint32_t structMappingCount = mappings.GetStructureMappingCount();
		Write(structMappingCount);
		for (std::uint32_t i = 0; i < structMappingCount; ++i) {
			const auto& mapping = mappings.GetStructureMapping(i);

			Write(mapping.Module);
			Write(mapping.Index);
		}

		const std::uint32_t funcMappingCount = mappings.GetFunctionMappingCount();
		Write(funcMappingCount);
		for (std::uint32_t i = 0; i < funcMappingCount; ++i) {
			const auto& mapping = mappings.GetFunctionMapping(i);

			Write(mapping.Module);
			Write(mapping.Index);
		}
	}
	void Generator::Generate(const Instructions& instructions) {
		Write(instructions.GetLabelCount());
		for (std::uint32_t i = 0; i < instructions.GetLabelCount(); ++i) {
			Write(instructions.GetLabel(i));
		}

		Write(instructions.GetInstructionCount());
		for (std::uint64_t i = 0; i < instructions.GetInstructionCount(); ++i) {
			const auto& inst = instructions.GetInstruction(i);

			Write(inst.OpCode);
			if (inst.HasOperand()) {
				Write(ConvertOperand(inst.Operand, inst.OperandIndex));
			}
		}
	}

	std::uint32_t Generator::ConvertOperand(std::uint32_t operand, std::uint8_t operandIndex) noexcept {
		switch (operandIndex) {
		case OperandIndex<MappedTypeIndex>: return m_ByteFile.TransformMappedIndex(static_cast<MappedTypeIndex>(operand));
		case OperandIndex<ArrayIndex>: return operand | (1 << 31);
		case OperandIndex<MappedArrayIndex>: return m_ByteFile.TransformMappedIndex(static_cast<MappedTypeIndex>(operand)) | (1 << 31);
		case OperandIndex<IntConstantIndex>: return m_ByteFile.TransformConstantIndex(static_cast<IntConstantIndex>(operand));
		case OperandIndex<LongConstantIndex>: return m_ByteFile.TransformConstantIndex(static_cast<LongConstantIndex>(operand));
		case OperandIndex<DoubleConstantIndex>: return m_ByteFile.TransformConstantIndex(static_cast<DoubleConstantIndex>(operand));
		case OperandIndex<StructureIndex>: return m_ByteFile.TransformConstantIndex(static_cast<StructureIndex>(operand));
		case OperandIndex<MappedStructureIndex>: return m_ByteFile.TransformMappedIndex(static_cast<MappedStructureIndex>(operand));
		case OperandIndex<MappedFunctionIndex>: return m_ByteFile.TransformMappedIndex(static_cast<MappedFunctionIndex>(operand));

		default: return operand;
		}
	}
}