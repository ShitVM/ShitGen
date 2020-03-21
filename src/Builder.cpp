#include <sgn/Builder.hpp>

#include <sgn/Version.hpp>

#include <cassert>
#include <stdexcept>
#include <utility>

namespace sgn {
	Builder::Builder(ByteFile& file, FunctionIndex index)
		: m_ByteFile(&file) {
		m_Instructions = &file.GetFunction(index)->Instructions();
		m_Function = file.GetFunction(index);
		m_LocalVariableIndex = m_Function->GetArity();

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
		assert(index < m_Function->GetArity());
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
	if (m_ByteFile->GetByteCodeVersion() < version) {				\
		throw std::runtime_error("Incompatible instruction");		\
	}																\
	m_Instructions->AddInstruction(Instruction(OpCode:: opCode));	\
}
#define InstructionWithOperandImpl(opCode, indexType, version)				\
void Builder:: opCode(indexType index) {									\
	if (m_ByteFile->GetByteCodeVersion() < version) {						\
		throw std::runtime_error("Incompatible instruction");				\
	}																		\
	m_Instructions->AddInstruction(Instruction(OpCode:: opCode, index));	\
}

	InstructionImpl(Nop, ByteCodeVersion::v0_1_0);

	InstructionWithOperandImpl(Push, IntConstantIndex, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Push, LongConstantIndex, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Push, DoubleConstantIndex, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Push, StructureIndex, ByteCodeVersion::v0_2_0);
	InstructionImpl(Pop, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Load, LocalVariableIndex, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Store, LocalVariableIndex, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Lea, LocalVariableIndex, ByteCodeVersion::v0_2_0);
	InstructionWithOperandImpl(FLea, FieldIndex, ByteCodeVersion::v0_2_0);
	InstructionImpl(TLoad, ByteCodeVersion::v0_2_0);
	InstructionImpl(TStore, ByteCodeVersion::v0_2_0);
	InstructionImpl(Copy, ByteCodeVersion::v0_2_0);
	InstructionImpl(Swap, ByteCodeVersion::v0_2_0);

	InstructionImpl(Add, ByteCodeVersion::v0_1_0);
	InstructionImpl(Sub, ByteCodeVersion::v0_1_0);
	InstructionImpl(Mul, ByteCodeVersion::v0_1_0);
	InstructionImpl(IMul, ByteCodeVersion::v0_1_0);
	InstructionImpl(Div, ByteCodeVersion::v0_1_0);
	InstructionImpl(IDiv, ByteCodeVersion::v0_1_0);
	InstructionImpl(Mod, ByteCodeVersion::v0_1_0);
	InstructionImpl(IMod, ByteCodeVersion::v0_1_0);
	InstructionImpl(Neg, ByteCodeVersion::v0_1_0);
	InstructionImpl(Inc, ByteCodeVersion::v0_1_0);
	InstructionImpl(Dec, ByteCodeVersion::v0_1_0);

	InstructionImpl(And, ByteCodeVersion::v0_1_0);
	InstructionImpl(Or, ByteCodeVersion::v0_1_0);
	InstructionImpl(Xor, ByteCodeVersion::v0_1_0);
	InstructionImpl(Not, ByteCodeVersion::v0_1_0);
	InstructionImpl(Shl, ByteCodeVersion::v0_1_0);
	InstructionImpl(Sal, ByteCodeVersion::v0_1_0);
	InstructionImpl(Shr, ByteCodeVersion::v0_1_0);
	InstructionImpl(Sar, ByteCodeVersion::v0_1_0);

	InstructionImpl(Cmp, ByteCodeVersion::v0_1_0);
	InstructionImpl(ICmp, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Jmp, LabelIndex, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Je, LabelIndex, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Jne, LabelIndex, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Ja, LabelIndex, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Jae, LabelIndex, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Jb, LabelIndex, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Jbe, LabelIndex, ByteCodeVersion::v0_1_0);
	InstructionWithOperandImpl(Call, FunctionIndex, ByteCodeVersion::v0_1_0);
	InstructionImpl(Ret, ByteCodeVersion::v0_1_0);

	InstructionImpl(ToI, ByteCodeVersion::v0_1_0);
	InstructionImpl(ToL, ByteCodeVersion::v0_1_0);
	InstructionImpl(ToD, ByteCodeVersion::v0_1_0);
	InstructionImpl(ToP, ByteCodeVersion::v0_2_0);

	InstructionImpl(Null, ByteCodeVersion::v0_3_0);
	InstructionWithOperandImpl(New, TypeIndex, ByteCodeVersion::v0_3_0);
	InstructionImpl(Delete, ByteCodeVersion::v0_3_0);
	InstructionImpl(GCNull, ByteCodeVersion::v0_3_0);
	InstructionWithOperandImpl(GCNew, TypeIndex, ByteCodeVersion::v0_3_0);

	InstructionWithOperandImpl(APush, ArrayIndex, ByteCodeVersion::v0_3_0);
	InstructionWithOperandImpl(ANew, ArrayIndex, ByteCodeVersion::v0_3_0);
	InstructionWithOperandImpl(AGCNew, ArrayIndex, ByteCodeVersion::v0_3_0);
	InstructionImpl(ALea, ByteCodeVersion::v0_3_0);
	InstructionImpl(Count, ByteCodeVersion::v0_3_0);
}