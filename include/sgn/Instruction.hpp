#pragma once

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
		"add", "sub", "mul", "imul", "div", "idiv", "mod", "imod", "neg",
		"and", "or", "xor", "not", "shl", "shr", "sal", "sar",
		"cmp", "icmp", "jmp", "je", "jne", "ja", "jae", "jb", "jbe", "call", "ret",
		"i2l", "i2d", "l2i", "l2d", "d2i", "d2l",
	};
}