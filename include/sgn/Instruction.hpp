#pragma once

#include <sgn/ConstantPool.hpp>
#include <sgn/Operand.hpp>
#include <sgn/Version.hpp>

#include <cstdint>
#include <fstream>
#include <vector>

namespace sgn {
	enum class OpCode : std::uint8_t {
		Nop,

		Push,
		Pop,
		Load,
		Store,
		Lea,
		FLea,
		TLoad,
		TStore,
		Copy,
		Swap,

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

		ToB,
		ToS,
		ToI,
		ToL,
		ToF,
		ToD,
		ToP,

		Null,
		New,
		Delete,
	};
}

namespace sgn {
	class Instruction final {
	public:
		sgn::OpCode OpCode = sgn::OpCode::Nop;
		sgn::Operand Operand;

	public:
		Instruction() noexcept = default;
		Instruction(sgn::OpCode opCode) noexcept;
		Instruction(sgn::OpCode opCode, sgn::Operand operand) noexcept;
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
		void Save(std::ofstream& stream, ByteCodeVersion bcVersion, const ConstantPool& constantPool) const;

		std::uint32_t GetLabelCount() const noexcept;
		std::uint64_t GetInstructionCount() const noexcept;

		void AddLabel(std::uint64_t offset);
		void AddInstruction(const Instruction& instruction);
		void SetLabel(std::uint32_t index, std::uint64_t offset) noexcept;

	private:
		OpCode TransformOpCode(OpCode opCode, ByteCodeVersion bcVersion) const;
	};
}