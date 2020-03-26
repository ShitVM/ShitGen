#pragma once

#include <sgn/Operand.hpp>
#include <svm/core/ConstantPool.hpp>

namespace sgn {
	class ConstantPool final : public svm::core::ConstantPool {
	public:
		using svm::core::ConstantPool::ConstantPool;
		inline ConstantPool(ConstantPool&& constantPool) noexcept;

	public:
		inline ConstantPool& operator=(ConstantPool&& constantPool) noexcept;

	private:
		using svm::core::ConstantPool::GetConstant;
		using svm::core::ConstantPool::GetConstantType;

	public:
		inline std::uint32_t TransformRealIndex(IntConstantIndex index) const noexcept;
		inline std::uint32_t TransformRealIndex(LongConstantIndex index) const noexcept;
		inline std::uint32_t TransformRealIndex(DoubleConstantIndex index) const noexcept;
	};
}

#include "detail/impl/ConstantPool.hpp"