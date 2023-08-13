#pragma once

#include <sgn/ByteFile.hpp>
#include <sgn/Function.hpp>
#include <sgn/Instruction.hpp>
#include <sgn/Operand.hpp>

#include <cstdint>
#include <string>
#include <unordered_map>

namespace sgn {
	class Builder final {
	private:
		ByteFile* m_ByteFile = nullptr;
		Function m_Function = nullptr;
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

		LocalVariableIndex GetArgument(std::uint32_t index) const noexcept;
		LocalVariableIndex AddLocalVariable();
		LabelIndex AddLabel();
		LabelIndex AddLabel(const std::string& reserved);
		LabelIndex ReserveLabel(const std::string& reserve);

		void Nop();

		void Push(IntConstantIndex index);
		void Push(LongConstantIndex index);
		void Push(DoubleConstantIndex index);
		void Push(StructureIndex index);
		void Push(MappedStructureIndex index);
		void Pop();
		void Load(LocalVariableIndex index);
		void Store(LocalVariableIndex index);
		void Lea(LocalVariableIndex index);
		void FLea(FieldIndex index);
		void TLoad();
		void TStore();
		void Copy();
		void Swap();

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
		void Call(MappedFunctionIndex index);
		void Ret();

		void ToI();
		void ToL();
		void ToD();
		void ToP();

		void Null();
		void New(TypeIndex index);
		void New(MappedTypeIndex index);
		void New(GeneralTypeIndex index);
		void Delete();
		void GCNull();
		void GCNew(TypeIndex index);
		void GCNew(MappedTypeIndex index);
		void GCNew(GeneralTypeIndex index);

		void APush(ArrayIndex index);
		void APush(MappedArrayIndex index);
		void APush(GeneralArrayIndex index);
		void ANew(ArrayIndex index);
		void ANew(MappedArrayIndex index);
		void ANew(GeneralArrayIndex index);
		void AGCNew(ArrayIndex index);
		void AGCNew(MappedArrayIndex index);
		void AGCNew(GeneralArrayIndex index);
		void ALea();
		void Count();
	};
}