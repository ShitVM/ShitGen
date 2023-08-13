#include <sgn/Builder.hpp>

#include <sgn/Version.hpp>

#include <cassert>
#include <stdexcept>
#include <utility>

namespace sgn {
	Builder::Builder(ByteFile& file, FunctionIndex index)
		: m_ByteFile(&file) {
		m_Function = *file.GetFunctionInfo(index);
		m_Instructions = &file.GetFunctionInfo(index)->Instructions;
		m_LocalVariableIndex = m_Function->Arity;

		file.CreatedBuilder();
	}
	Builder::Builder(ByteFile& file, Instructions* instructions)
		: m_ByteFile(&file), m_Instructions(instructions) {
		file.CreatedBuilder();
	}
	Builder::Builder(Builder&& builder) noexcept
		: m_ByteFile(builder.m_ByteFile), m_Function(builder.m_Function), m_Instructions(builder.m_Instructions), m_LocalVariableIndex(builder.m_LocalVariableIndex),
		m_ReservedLabels(std::move(builder.m_ReservedLabels)) {}

	Builder& Builder::operator=(Builder&& builder) noexcept {
		m_ByteFile = builder.m_ByteFile;
		m_Function = builder.m_Function;
		m_Instructions = builder.m_Instructions;
		m_LocalVariableIndex = builder.m_LocalVariableIndex;
		m_ReservedLabels = std::move(builder.m_ReservedLabels);
		return *this;
	}

	const ByteFile& Builder::GetByteFile() const noexcept {
		return *m_ByteFile;
	}
	ByteFile& Builder::GetByteFile() noexcept {
		return *m_ByteFile;
	}

	LocalVariableIndex Builder::GetArgument(std::uint32_t index) const noexcept {
		assert(m_Function != nullptr);
		assert(index < m_Function->Arity);
		return static_cast<LocalVariableIndex>(index);
	}
	LocalVariableIndex Builder::AddLocalVariable() {
		return static_cast<LocalVariableIndex>(m_LocalVariableIndex++);
	}
	LabelIndex Builder::AddLabel() {
		m_Instructions->AddLabel(m_Instructions->GetInstructionCount());
		return static_cast<LabelIndex>(m_Instructions->GetLabelCount() - 1);
	}
	LabelIndex Builder::AddLabel(const std::string& reserved) {
		const auto iter = m_ReservedLabels.find(reserved);
		const LabelIndex index = iter->second;

		m_Instructions->SetLabel(static_cast<std::uint32_t>(index), m_Instructions->GetInstructionCount());
		m_ReservedLabels.erase(iter);

		return index;
	}
	LabelIndex Builder::ReserveLabel(const std::string& reserve) {
		const LabelIndex index = AddLabel();
		m_ReservedLabels[reserve] = index;
		return index;
	}

#define InstructionImpl(opCode, version)							\
void Builder:: opCode() {											\
	if (m_ByteFile->GetShitBCVersion() < version) {					\
		throw std::runtime_error("Incompatible instruction");		\
	}																\
	m_Instructions->AddInstruction(Instruction(OpCode:: opCode));	\
}
#define InstructionWithOperandImpl(opCode, indexType, version)			\
void Builder:: opCode(indexType index) {								\
	if (m_ByteFile->GetShitBCVersion() < version) {						\
		throw std::runtime_error("Incompatible instruction");			\
	}																	\
	m_Instructions->AddInstruction(Instruction(OpCode:: opCode,			\
		static_cast<std::uint32_t>(index), OperandIndex<indexType>));	\
}
#define InstructionWithGeneralOperandImpl(opCode, generalIndexType, firstIndexType, secondIndexType)	\
void Builder:: opCode(generalIndexType index) {															\
	if (std::holds_alternative<firstIndexType>(index)) {												\
		opCode(std::get<firstIndexType>(index));														\
	} else if (std::holds_alternative<secondIndexType>(index)) {										\
		opCode(std::get<secondIndexType>(index));														\
	}																									\
}

	InstructionImpl(Nop, ShitBCVersion::v0_1_0);

	InstructionWithOperandImpl(Push, IntConstantIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Push, LongConstantIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Push, DoubleConstantIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Push, StructureIndex, ShitBCVersion::v0_2_0);
	InstructionWithOperandImpl(Push, MappedStructureIndex, ShitBCVersion::v0_4_0);
	InstructionImpl(Pop, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Load, LocalVariableIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Store, LocalVariableIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Lea, LocalVariableIndex, ShitBCVersion::v0_2_0);
	InstructionWithOperandImpl(FLea, FieldIndex, ShitBCVersion::v0_2_0);
	InstructionImpl(TLoad, ShitBCVersion::v0_2_0);
	InstructionImpl(TStore, ShitBCVersion::v0_2_0);
	InstructionImpl(Copy, ShitBCVersion::v0_2_0);
	InstructionImpl(Swap, ShitBCVersion::v0_2_0);

	InstructionImpl(Add, ShitBCVersion::v0_1_0);
	InstructionImpl(Sub, ShitBCVersion::v0_1_0);
	InstructionImpl(Mul, ShitBCVersion::v0_1_0);
	InstructionImpl(IMul, ShitBCVersion::v0_1_0);
	InstructionImpl(Div, ShitBCVersion::v0_1_0);
	InstructionImpl(IDiv, ShitBCVersion::v0_1_0);
	InstructionImpl(Mod, ShitBCVersion::v0_1_0);
	InstructionImpl(IMod, ShitBCVersion::v0_1_0);
	InstructionImpl(Neg, ShitBCVersion::v0_1_0);
	InstructionImpl(Inc, ShitBCVersion::v0_1_0);
	InstructionImpl(Dec, ShitBCVersion::v0_1_0);

	InstructionImpl(And, ShitBCVersion::v0_1_0);
	InstructionImpl(Or, ShitBCVersion::v0_1_0);
	InstructionImpl(Xor, ShitBCVersion::v0_1_0);
	InstructionImpl(Not, ShitBCVersion::v0_1_0);
	InstructionImpl(Shl, ShitBCVersion::v0_1_0);
	InstructionImpl(Sal, ShitBCVersion::v0_1_0);
	InstructionImpl(Shr, ShitBCVersion::v0_1_0);
	InstructionImpl(Sar, ShitBCVersion::v0_1_0);

	InstructionImpl(Cmp, ShitBCVersion::v0_1_0);
	InstructionImpl(ICmp, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Jmp, LabelIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Je, LabelIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Jne, LabelIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Ja, LabelIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Jae, LabelIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Jb, LabelIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Jbe, LabelIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Call, FunctionIndex, ShitBCVersion::v0_1_0);
	InstructionWithOperandImpl(Call, MappedFunctionIndex, ShitBCVersion::v0_4_0);
	InstructionImpl(Ret, ShitBCVersion::v0_1_0);

	InstructionImpl(ToI, ShitBCVersion::v0_1_0);
	InstructionImpl(ToL, ShitBCVersion::v0_1_0);
	InstructionImpl(ToD, ShitBCVersion::v0_1_0);
	InstructionImpl(ToP, ShitBCVersion::v0_2_0);

	InstructionImpl(Null, ShitBCVersion::v0_3_0);
	InstructionWithOperandImpl(New, TypeIndex, ShitBCVersion::v0_3_0);
	InstructionWithOperandImpl(New, MappedTypeIndex, ShitBCVersion::v0_4_0);
	InstructionWithGeneralOperandImpl(New, GeneralTypeIndex, TypeIndex, MappedTypeIndex);
	InstructionImpl(Delete, ShitBCVersion::v0_3_0);
	InstructionImpl(GCNull, ShitBCVersion::v0_3_0);
	InstructionWithOperandImpl(GCNew, TypeIndex, ShitBCVersion::v0_3_0);
	InstructionWithOperandImpl(GCNew, MappedTypeIndex, ShitBCVersion::v0_4_0);
	InstructionWithGeneralOperandImpl(GCNew, GeneralTypeIndex, TypeIndex, MappedTypeIndex);

	InstructionWithOperandImpl(APush, ArrayIndex, ShitBCVersion::v0_3_0);
	InstructionWithOperandImpl(APush, MappedArrayIndex, ShitBCVersion::v0_4_0);
	InstructionWithGeneralOperandImpl(APush, GeneralArrayIndex, ArrayIndex, MappedArrayIndex);
	InstructionWithOperandImpl(ANew, ArrayIndex, ShitBCVersion::v0_3_0);
	InstructionWithOperandImpl(ANew, MappedArrayIndex, ShitBCVersion::v0_4_0);
	InstructionWithGeneralOperandImpl(ANew, GeneralArrayIndex, ArrayIndex, MappedArrayIndex);
	InstructionWithOperandImpl(AGCNew, ArrayIndex, ShitBCVersion::v0_3_0);
	InstructionWithOperandImpl(AGCNew, MappedArrayIndex, ShitBCVersion::v0_4_0);
	InstructionWithGeneralOperandImpl(AGCNew, GeneralArrayIndex, ArrayIndex, MappedArrayIndex);
	InstructionImpl(ALea, ShitBCVersion::v0_3_0);
	InstructionImpl(Count, ShitBCVersion::v0_3_0);
}