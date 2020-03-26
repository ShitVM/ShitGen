#pragma once
#include <sgn/ConstantPool.hpp>

namespace sgn {
	inline std::uint32_t ConstantPool::TransformRealIndex(IntConstantIndex index) const noexcept {
		return static_cast<std::uint32_t>(index) + GetIntOffset();
	}
	inline std::uint32_t ConstantPool::TransformRealIndex(LongConstantIndex index) const noexcept {
		return static_cast<std::uint32_t>(index) + GetLongOffset();
	}
	inline std::uint32_t ConstantPool::TransformRealIndex(DoubleConstantIndex index) const noexcept {
		return static_cast<std::uint32_t>(index) + GetDoubleOffset();
	}
}