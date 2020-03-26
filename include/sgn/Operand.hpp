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

	template<typename T>
	constexpr std::uint8_t GetOperandIndex() noexcept;
}

#include "detail/impl/Operand.hpp"