#pragma once

#include <cstdint>
#include <vector>

namespace sgn {
	enum class OpCode {
		Nop,

		Push,
		Pop,
		Load,
		Store,

		Add,
		Sub,
		Mul,
		IMul,
		Div,
		IDiv,
		Mod,
		IMod,
		Neg,
		Inc,
		Dec,

		And,
		Or,
		Xor,
		Not,
		Shl,
		Sal,
		Shr,
		Sar,

		Cmp,
		ICmp,
		Jmp,
		Je,
		Jne,
		Ja,
		Jae,
		Jb,
		Jbe,
		Call,
		Ret,

		I2L,
		I2D,
		L2I,
		L2D,
		D2I,
		D2L,
	};

	static constexpr const char* Mnemonics[] = {
		"nop",
		"push", "pop", "load", "store",
		"add", "sub", "mul", "imul", "div", "idiv", "mod", "imod", "neg", "inc", "dec",
		"and", "or", "xor", "not", "shl", "shr", "sal", "sar",
		"cmp", "icmp", "jmp", "je", "jne", "ja", "jae", "jb", "jbe", "call", "ret",
		"i2l", "i2d", "l2i", "l2d", "d2i", "d2l",
	};
}

namespace sgn {
	class Instruction final {
	public:
		sgn::OpCode OpCode = sgn::OpCode::Nop;
		std::uint32_t Operand = 0;

	public:
		Instruction() noexcept = default;
		Instruction(sgn::OpCode opCode) noexcept;
		Instruction(sgn::OpCode opCode, std::uint32_t operand) noexcept;
		Instruction(const Instruction& instruction) noexcept;
		~Instruction() = default;

	public:
		Instruction& operator=(const Instruction& instruction) noexcept;
		bool operator==(const Instruction& instruction) const noexcept;
		bool operator!=(const Instruction& instruction) const noexcept;
	};
}

namespace sgn {
	class Instructions final {
	private:
		std::vector<std::uint64_t> m_Labels;
		std::vector<Instruction> m_Instructions;

	public:
		Instructions() noexcept = default;
		Instructions(Instructions&& instructions) noexcept;
		~Instructions() = default;

	public:
		Instructions& operator=(Instructions&& instructions) noexcept;
		bool operator==(const Instructions&) = delete;
		bool operator!=(const Instructions&) = delete;

	public:
		void AddLabel(std::uint64_t offset);
		void AddInstruction(const Instruction& instruction);
	};
}