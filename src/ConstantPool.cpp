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

	std::uint32_t ConstantPool::AddIntConstant(const IntConstant& intConstant) {
		m_IntPool.push_back(intConstant);
		return static_cast<std::uint32_t>(m_IntPool.size() - 1);
	}
	std::uint32_t ConstantPool::AddLongConstant(const LongConstant& longConstant) {
		m_LongPool.push_back(longConstant);
		return static_cast<std::uint32_t>(m_LongPool.size() - 1);
	}
	std::uint32_t ConstantPool::AddDoubleConstant(const DoubleConstant& doubleConstant) {
		m_DoublePool.push_back(doubleConstant);
		return static_cast<std::uint32_t>(m_DoublePool.size() - 1);
	}

	std::uint32_t ConstantPool::ContainsIntConstant(const IntConstant& intConstant) const noexcept {
		const auto iter = std::find(m_IntPool.begin(), m_IntPool.end(), intConstant);
		if (iter == m_IntPool.end()) return 0;
		else return std::distance(m_IntPool.begin(), iter) + 1;
	}
	std::uint32_t ConstantPool::ContainsLongConstant(const LongConstant& longConstant) const noexcept {
		const auto iter = std::find(m_LongPool.begin(), m_LongPool.end(), longConstant);
		if (iter == m_LongPool.end()) return 0;
		else return std::distance(m_LongPool.begin(), iter) + 1;
	}
	std::uint32_t ConstantPool::ContainsDoubleConstant(const DoubleConstant& doubleConstant) const noexcept {
		const auto iter = std::find(m_DoublePool.begin(), m_DoublePool.end(), doubleConstant);
		if (iter == m_DoublePool.end()) return 0;
		else return std::distance(m_DoublePool.begin(), iter) + 1;
	}
}