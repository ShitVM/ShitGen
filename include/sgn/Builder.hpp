#pragma once

#include <sgn/ByteFile.hpp>
#include <sgn/Instruction.hpp>
#include <sgn/Operand.hpp>

#include <string>
#include <unordered_map>

namespace sgn {
	class Builder final {
	private:
		ByteFile* m_ByteFile = nullptr;
		Instructions* m_Instructions = nullptr;
		std::uint32_t m_LocalVariableIndex = 0;
		std::unordered_map<std::string, LabelIndex> m_ReservedLabels;

	public:
		Builder(ByteFile& file, FunctionIndex index);
		Builder(ByteFile& file, Instructions* instructions);
		Builder(Builder&& builder) noexcept;
		~Builder() = default;

	public:
		Builder& operator=(Builder&& builder) noexcept;
		bool operator==(const Builder&) = delete;
		bool operator!=(const Builder&) = delete;

	public:
		const ByteFile& GetByteFile() const noexcept;
		ByteFile& GetByteFile() noexcept;

		LocalVariableIndex GetArgument(std::uint32_t index);
		LocalVariableIndex AddLocalVariable();
		LabelIndex AddLabel();
		LabelIndex AddLabel(const std::string& reserved);
		LabelIndex ReserveLabel(const std::string& reserve);

		void Nop();

		void Push(IntConstantIndex index);
		void Push(LongConstantIndex index);
		void Push(DoubleConstantIndex index);
		void Pop();
		void Load(LocalVariableIndex index);
		void Store(LocalVariableIndex index);

		void Add();
		void Sub();
		void Mul();
		void IMul();
		void Div();
		void IDiv();
		void Mod();
		void IMod();
		void Neg();
		void Inc();
		void Dec();

		void And();
		void Or();
		void Xor();
		void Not();
		void Shl();
		void Sal();
		void Shr();
		void Sar();

		void Cmp();
		void ICmp();
		void Jmp(LabelIndex index);
		void Je(LabelIndex index);
		void Jne(LabelIndex index);
		void Ja(LabelIndex index);
		void Jae(LabelIndex index);
		void Jb(LabelIndex index);
		void Jbe(LabelIndex index);
		void Call(FunctionIndex index);
		void Ret();

		void ToI();
		void ToL();
		void ToD();
	};
}