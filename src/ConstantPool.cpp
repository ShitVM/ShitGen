#include <sgn/ConstantPool.hpp>

#include <algorithm>
#include <utility>

namespace sgn {
	ConstantPool::ConstantPool(ConstantPool&& pool) noexcept
		: m_IntPool(std::move(pool.m_IntPool)), m_LongPool(std::move(pool.m_LongPool)), m_DoublePool(std::move(pool.m_DoublePool)) {}

	ConstantPool& ConstantPool::operator=(ConstantPool&& pool) noexcept {
		m_IntPool = std::move(pool.m_IntPool);
		m_LongPool = std::move(pool.m_LongPool);
		m_DoublePool = std::move(pool.m_DoublePool);
		return *this;
	}

	void ConstantPool::Clear() noexcept {
		m_IntPool.clear();
		m_LongPool.clear();
		m_DoublePool.clear();
	}
	bool ConstantPool::IsEmpty() const noexcept {
		return m_IntPool.empty() && m_LongPool.empty() && m_DoublePool.empty();
	}

	void ConstantPool::AddIntConstant(const IntConstant& intConstant) {
		m_IntPool.push_back(intConstant);
	}
	void ConstantPool::AddLongConstant(const LongConstant& longConstant) {
		m_LongPool.push_back(longConstant);
	}
	void ConstantPool::AddDoubleConstant(const DoubleConstant& doubleConstant) {
		m_DoublePool.push_back(doubleConstant);
	}

	bool ConstantPool::Contains(const IntConstant& intConstant) const noexcept {
		return std::find(m_IntPool.begin(), m_IntPool.end(), intConstant) != m_IntPool.end();
	}
	bool ConstantPool::Contains(const LongConstant& longConstant) const noexcept {
		return std::find(m_LongPool.begin(), m_LongPool.end(), longConstant) != m_LongPool.end();
	}
	bool ConstantPool::Contains(const DoubleConstant& doubleConstant) const noexcept {
		return std::find(m_DoublePool.begin(), m_DoublePool.end(), doubleConstant) != m_DoublePool.end();
	}
}