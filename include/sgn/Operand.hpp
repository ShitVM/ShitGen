#pragma once

#include <cstdint>
#include <variant>

namespace sgn {
#define SGN_INDEX(name, index) enum class name : std::uint32_t { OperandIndex = index };

	SGN_INDEX(TypeIndex, 1);
	SGN_INDEX(MappedTypeIndex, 2);
	SGN_INDEX(ArrayIndex, 3);
	SGN_INDEX(MappedArrayIndex, 4);
	SGN_INDEX(IntConstantIndex, 5);
	SGN_INDEX(LongConstantIndex, 6);
	SGN_INDEX(SingleConstantIndex, 18);
	SGN_INDEX(DoubleConstantIndex, 7);
	SGN_INDEX(StructureIndex, 8);
	SGN_INDEX(MappedStructureIndex, 9);
	SGN_INDEX(FieldIndex, 10);
	SGN_INDEX(FunctionIndex, 11);
	SGN_INDEX(MappedFunctionIndex, 12);
	SGN_INDEX(LabelIndex, 13);
	SGN_INDEX(LocalVariableIndex, 14);

	SGN_INDEX(ExternModuleIndex, 15);
	SGN_INDEX(ExternStructureIndex, 16);
	SGN_INDEX(ExternFunctionIndex, 17);

	template<typename T>
	static constexpr std::uint8_t OperandIndex = static_cast<std::uint8_t>(T::OperandIndex);

	using GeneralTypeIndex = std::variant<TypeIndex, MappedTypeIndex>;
	using GeneralArrayIndex = std::variant<ArrayIndex, MappedArrayIndex>;
}