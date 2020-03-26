#pragma once
#include <sgn/ConstantPool.hpp>

namespace sgn {
	inline ConstantPool::ConstantPool(ConstantPool&& constantPool) noexcept
		: svm::core::ConstantPool(std::move(constantPool)) {}

	inline ConstantPool& ConstantPool::operator=(ConstantPool&& constantPool) noexcept {
		svm::core::ConstantPool::operator=(std::move(constantPool));
		return *this;
	}

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