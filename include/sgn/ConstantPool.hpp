#pragma once

#include <sgn/Operand.hpp>
#include <svm/core/ConstantPool.hpp>

#include <cstdint>

namespace sgn {
	class ConstantPool final : public svm::core::ConstantPool {
	public:
		using svm::core::ConstantPool::ConstantPool;
		ConstantPool(ConstantPool&& constantPool) noexcept;

	public:
		ConstantPool& operator=(ConstantPool&& constantPool) noexcept;

	private:
		using svm::core::ConstantPool::GetConstant;
		using svm::core::ConstantPool::GetConstantType;

	public:
		std::uint32_t TransformRealIndex(IntConstantIndex index) const noexcept;
		std::uint32_t TransformRealIndex(LongConstantIndex index) const noexcept;
		std::uint32_t TransformRealIndex(SingleConstantIndex index) const noexcept;
		std::uint32_t TransformRealIndex(DoubleConstantIndex index) const noexcept;
	};
}