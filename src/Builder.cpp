#include <sgn/Builder.hpp>

#include <utility>

namespace sgn {
	Builder::Builder(ByteFile& file, FunctionIndex index)
		: m_ByteFile(&file) {
		m_Instructions = &file.GetFunction(index)->Instructions;
		m_LocalVariableIndex += file.GetFunction(index)->Arity;
	}
	Builder::Builder(ByteFile& file, Instructions* instructions)
		: m_ByteFile(&file), m_Instructions(instructions) {}
	Builder::Builder(Builder&& builder) noexcept
		: m_ByteFile(builder.m_ByteFile), m_Instructions(builder.m_Instructions), m_LocalVariableIndex(builder.m_LocalVariableIndex),
		m_ReservedLabels(std::move(builder.m_ReservedLabels)) {}

	Builder& Builder::operator=(Builder&& builder) noexcept {
		m_ByteFile = builder.m_ByteFile;
		m_Instructions = builder.m_Instructions;
		m_LocalVariableIndex = builder.m_LocalVariableIndex;
		return *this;
	}

	const ByteFile& Builder::GetByteFile() const noexcept {
		return *m_ByteFile;
	}
	ByteFile& Builder::GetByteFile() noexcept {
		return *m_ByteFile;
	}

	LocalVariableIndex Builder::GetArgument(std::uint32_t index) {
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

#define InstructionImpl(opCode)										\
void Builder:: opCode() {											\
	m_Instructions->AddInstruction(Instruction(OpCode:: opCode));	\
}
#define InstructionWithOperandImpl(opCode, indexType)						\
void Builder:: opCode(indexType index) {									\
	m_Instructions->AddInstruction(Instruction(OpCode:: opCode, index));	\
}

	InstructionImpl(Nop);

	InstructionWithOperandImpl(Push, IntConstantIndex);
	InstructionWithOperandImpl(Push, LongConstantIndex);
	InstructionWithOperandImpl(Push, DoubleConstantIndex);
	InstructionImpl(Pop);
	InstructionWithOperandImpl(Load, LocalVariableIndex);
	InstructionWithOperandImpl(Store, LocalVariableIndex);

	InstructionImpl(Add);
	InstructionImpl(Sub);
	InstructionImpl(Mul);
	InstructionImpl(IMul);
	InstructionImpl(Div);
	InstructionImpl(IDiv);
	InstructionImpl(Mod);
	InstructionImpl(IMod);
	InstructionImpl(Neg);
	InstructionImpl(Inc);
	InstructionImpl(Dec);

	InstructionImpl(And);
	InstructionImpl(Or);
	InstructionImpl(Xor);
	InstructionImpl(Not);
	InstructionImpl(Shl);
	InstructionImpl(Sal);
	InstructionImpl(Shr);
	InstructionImpl(Sar);

	InstructionImpl(Cmp);
	InstructionImpl(ICmp);
	InstructionWithOperandImpl(Jmp, LabelIndex);
	InstructionWithOperandImpl(Je, LabelIndex);
	InstructionWithOperandImpl(Jne, LabelIndex);
	InstructionWithOperandImpl(Ja, LabelIndex);
	InstructionWithOperandImpl(Jae, LabelIndex);
	InstructionWithOperandImpl(Jb, LabelIndex);
	InstructionWithOperandImpl(Jbe, LabelIndex);
	InstructionWithOperandImpl(Call, FunctionIndex);
	InstructionImpl(Ret);

	InstructionImpl(I2L);
	InstructionImpl(I2D);
	InstructionImpl(L2I);
	InstructionImpl(L2D);
	InstructionImpl(D2I);
	InstructionImpl(D2L);
}