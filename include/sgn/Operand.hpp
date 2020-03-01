#pragma once

#include <cstdint>
#include <variant>

namespace sgn {
	enum class IntConstantIndex : std::uint32_t {};
	enum class LongConstantIndex : std::uint32_t {};
	enum class DoubleConstantIndex : std::uint32_t {};
	enum class FunctionIndex : std::uint32_t {};
	enum class LabelIndex : std::uint32_t {};
	enum class LocalVariableIndex : std::uint32_t {};

	using Operand = std::variant<std::monostate, IntConstantIndex, LongConstantIndex, DoubleConstantIndex, FunctionIndex, LabelIndex, LocalVariableIndex>;
}