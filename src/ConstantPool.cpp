#include <sgn/ConstantPool.hpp>

namespace sgn {
	ConstantPool::ConstantPool(ConstantPool&& constantPool) noexcept
		: svm::core::ConstantPool(std::move(constantPool)) {}

	ConstantPool& ConstantPool::operator=(ConstantPool&& constantPool) noexcept {
		svm::core::ConstantPool::operator=(std::move(constantPool));
		return *this;
	}

	std::uint32_t ConstantPool::TransformRealIndex(IntConstantIndex index) const noexcept {
		return static_cast<std::uint32_t>(index) + GetIntOffset();
	}
	std::uint32_t ConstantPool::TransformRealIndex(LongConstantIndex index) const noexcept {
		return static_cast<std::uint32_t>(index) + GetLongOffset();
	}
	std::uint32_t ConstantPool::TransformRealIndex(DoubleConstantIndex index) const noexcept {
		return static_cast<std::uint32_t>(index) + GetDoubleOffset();
	}
}