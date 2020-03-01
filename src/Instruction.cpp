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

	void Instructions::Save(std::ofstream& stream) const {
		WriteConstant(stream, static_cast<std::uint32_t>(m_Labels.size()));
		for (std::uint32_t i = 0; i < m_Labels.size(); ++i) {
			WriteConstant(stream, m_Labels[i]);
		}

		WriteConstant(stream, static_cast<std::uint64_t>(m_Instructions.size()));
		for (std::uint64_t i = 0; i < m_Instructions.size(); ++i) {
			const Instruction& inst = m_Instructions[static_cast<std::size_t>(i)];
			WriteConstant(stream, inst.OpCode);

			switch (inst.Operand.index()) {
			case 1: WriteConstant(stream, std::get<IntConstantIndex>(inst.Operand)); break;
			case 2: WriteConstant(stream, std::get<LongConstantIndex>(inst.Operand)); break;
			case 3: WriteConstant(stream, std::get<DoubleConstantIndex>(inst.Operand)); break;
			case 4: WriteConstant(stream, std::get<FunctionIndex>(inst.Operand)); break;
			case 5: WriteConstant(stream, std::get<LabelIndex>(inst.Operand)); break;
			case 6: WriteConstant(stream, std::get<LocalVariableIndex>(inst.Operand)); break;
			}
		}
	}

	void Instructions::AddLabel(std::uint64_t offset) {
		m_Labels.push_back(offset);
	}
	void Instructions::AddInstruction(const Instruction& instruction) {
		m_Instructions.push_back(instruction);
	}
}