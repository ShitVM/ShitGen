#pragma once

#include <cstdint>

namespace sgn {
#define SGN_INDEX(name, index) enum class name : std::uint32_t { OperandIndex = index };

	SGN_INDEX(TypeIndex, 1);
	SGN_INDEX(ArrayIndex, 2);
	SGN_INDEX(IntConstantIndex, 3);
	SGN_INDEX(LongConstantIndex, 4);
	SGN_INDEX(DoubleConstantIndex, 5);
	SGN_INDEX(StructureIndex, 6);
	SGN_INDEX(FieldIndex, 7);
	SGN_INDEX(FunctionIndex, 8);
	SGN_INDEX(LabelIndex, 9);
	SGN_INDEX(LocalVariableIndex, 10);

	SGN_INDEX(ExternModuleIndex, 11);
	SGN_INDEX(ExternStructureIndex, 12);
	SGN_INDEX(ExternFunctionIndex, 13);

	template<typename T>
	static constexpr std::uint8_t OperandIndex = static_cast<std::uint8_t>(T::OperandIndex);
}