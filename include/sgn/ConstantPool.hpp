#pragma once

#include <sgn/Constant.hpp>

#include <vector>

namespace sgn {
	class ConstantPool final {
	private:
		std::vector<IntConstant> m_IntPool;
		std::vector<LongConstant> m_LongPool;
		std::vector<DoubleConstant> m_DoublePool;

	public:
		ConstantPool() noexcept = default;
		ConstantPool(ConstantPool&& pool) noexcept;
		~ConstantPool() = default;

	public:
		ConstantPool& operator=(ConstantPool&& pool) noexcept;
		bool operator==(const ConstantPool&) = delete;
		bool operator!=(const ConstantPool&) = delete;

	public:
		void Clear() noexcept;
		bool IsEmpty() const noexcept;

		void AddIntConstant(const IntConstant& intConstant);
		void AddLongConstant(const LongConstant& longConstant);
		void AddDoubleConstant(const DoubleConstant& doubleConstant);

		bool Contains(const IntConstant& intConstant) const noexcept;
		bool Contains(const LongConstant& longConstant) const noexcept;
		bool Contains(const DoubleConstant& doubleConstant) const noexcept;
	};
}