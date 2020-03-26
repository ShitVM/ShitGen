#pragma once

#include <cstdint>

namespace sgn {
	enum class TypeIndex : std::uint32_t {};
	enum class ArrayIndex : std::uint32_t {};
	enum class IntConstantIndex : std::uint32_t {};
	enum class LongConstantIndex : std::uint32_t {};
	enum class DoubleConstantIndex : std::uint32_t {};
	enum class StructureIndex : std::uint32_t {};
	enum class FieldIndex : std::uint32_t {};
	enum class FunctionIndex : std::uint32_t {};
	enum class LabelIndex : std::uint32_t {};
	enum class LocalVariableIndex : std::uint32_t {};
}