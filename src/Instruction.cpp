#include <sgn/Instruction.hpp>

#include <sgn/Memory.hpp>

#include <utility>

namespace sgn {
	Instruction::Instruction(sgn::OpCode opCode) noexcept
		: OpCode(opCode) {}
	Instruction::Instruction(sgn::OpCode opCode, sgn::Operand operand) noexcept
		: OpCode(opCode), Operand(operand) {}
	Instruction::Instruction(const Instruction& instruction) noexcept
		: OpCode(instruction.OpCode), Operand(instruction.Operand) {}

	Instruction& Instruction::operator=(const Instruction& instruction) noexcept {
		OpCode = instruction.OpCode;
		Operand = instruction.Operand;
		return *this;
	}
	bool Instruction::operator==(const Instruction& instruction) const noexcept {
		return OpCode == instruction.OpCode && Operand == instruction.Operand;
	}
	bool Instruction::operator!=(const Instruction& instruction) const noexcept {
		return OpCode != instruction.OpCode || Operand != instruction.Operand;
	}
}

namespace sgn {
	Instructions::Instructions(Instructions&& instructions) noexcept
		: m_Labels(std::move(instructions.m_Labels)), m_Instructions(std::move(instructions.m_Instructions)) {}

	Instructions& Instructions::operator=(Instructions&& instructions) noexcept {
		m_Labels = std::move(instructions.m_Labels);
		m_Instructions = std::move(instructions.m_Instructions);
		return *this;
	}

	void Instructions::Save(std::ofstream& stream, ByteCodeVersion bcVersion, const ConstantPool& constantPool) const {
		WriteConstant(stream, static_cast<std::uint32_t>(m_Labels.size()));
		for (std::uint32_t i = 0; i < m_Labels.size(); ++i) {
			WriteConstant(stream, m_Labels[i]);
		}

		WriteConstant(stream, static_cast<std::uint64_t>(m_Instructions.size()));
		for (std::uint64_t i = 0; i < m_Instructions.size(); ++i) {
			const Instruction& inst = m_Instructions[static_cast<std::size_t>(i)];
			WriteConstant(stream, TransformOpCode(inst.OpCode, bcVersion));

			switch (inst.Operand.index()) {
			case 1: WriteConstant(stream, std::get<TypeIndex>(inst.Operand)); break;
			case 2: WriteConstant(stream, constantPool.TransformRealIndex(std::get<IntConstantIndex>(inst.Operand))); break;
			case 3: WriteConstant(stream, constantPool.TransformRealIndex(std::get<LongConstantIndex>(inst.Operand))); break;
			case 4: WriteConstant(stream, constantPool.TransformRealIndex(std::get<DoubleConstantIndex>(inst.Operand))); break;
			case 5: WriteConstant(stream, static_cast<std::uint32_t>(std::get<StructureIndex>(inst.Operand)) + constantPool.GetAllCount()); break;
			case 6: WriteConstant(stream, std::get<FieldIndex>(inst.Operand)); break;
			case 7: WriteConstant(stream, std::get<FunctionIndex>(inst.Operand)); break;
			case 8: WriteConstant(stream, std::get<LabelIndex>(inst.Operand)); break;
			case 9: WriteConstant(stream, std::get<LocalVariableIndex>(inst.Operand)); break;
			}
		}
	}

	std::uint32_t Instructions::GetLabelCount() const noexcept {
		return static_cast<std::uint32_t>(m_Labels.size());
	}
	std::uint64_t Instructions::GetInstructionCount() const noexcept {
		return m_Instructions.size();
	}

	void Instructions::AddLabel(std::uint64_t offset) {
		m_Labels.push_back(offset);
	}
	void Instructions::AddInstruction(const Instruction& instruction) {
		m_Instructions.push_back(instruction);
	}
	void Instructions::SetLabel(std::uint32_t index, std::uint64_t offset) noexcept {
		m_Labels[index] = offset;
	}

	OpCode Instructions::TransformOpCode(OpCode opCode, ByteCodeVersion bcVersion) const {
		if (bcVersion >= ByteCodeVersion::Latest) {
			return opCode;
		}

		if (bcVersion <= ByteCodeVersion::v0_2_0) {
			if (OpCode::ToI <= opCode) {
				opCode = static_cast<OpCode>(static_cast<std::uint8_t>(opCode) - 2);
			}
			if (OpCode::ToD <= opCode) {
				opCode = static_cast<OpCode>(static_cast<std::uint8_t>(opCode) - 1);
			}
		}

		if (bcVersion <= ByteCodeVersion::v0_1_0) {
			if (opCode >= OpCode::Add) {
				opCode = static_cast<OpCode>(static_cast<std::uint8_t>(opCode) - 6);
			}
		}

		return opCode;
	}
}