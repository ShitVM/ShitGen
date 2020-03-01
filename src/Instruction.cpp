#include <sgn/Instruction.hpp>

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

	void Instructions::AddLabel(std::uint64_t offset) {
		m_Labels.push_back(offset);
	}
	void Instructions::AddInstruction(const Instruction& instruction) {
		m_Instructions.push_back(instruction);
	}
}