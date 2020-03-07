#include <sgn/ConstantPool.hpp>

#include <sgn/Memory.hpp>

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

	void ConstantPool::Save(std::ofstream& stream, ByteFileVersion) const {
		WriteConstant(stream, static_cast<std::uint32_t>(m_IntPool.size()));
		for (std::uint32_t i = 0; i < m_IntPool.size(); ++i) {
			WriteConstant(stream, m_IntPool[i]);
		}

		WriteConstant(stream, static_cast<std::uint32_t>(m_LongPool.size()));
		for (std::uint32_t i = 0; i < m_LongPool.size(); ++i) {
			WriteConstant(stream, m_LongPool[i]);
		}

		WriteConstant(stream, static_cast<std::uint32_t>(m_DoublePool.size()));
		for (std::uint32_t i = 0; i < m_DoublePool.size(); ++i) {
			WriteConstant(stream, m_DoublePool[i]);
		}
	}

	std::uint32_t ConstantPool::AddIntConstant(std::uint32_t intConstant) {
		m_IntPool.push_back(intConstant);
		return static_cast<std::uint32_t>(m_IntPool.size() - 1);
	}
	std::uint32_t ConstantPool::AddLongConstant(std::uint64_t longConstant) {
		m_LongPool.push_back(longConstant);
		return static_cast<std::uint32_t>(m_LongPool.size() - 1);
	}
	std::uint32_t ConstantPool::AddDoubleConstant(double doubleConstant) {
		m_DoublePool.push_back(doubleConstant);
		return static_cast<std::uint32_t>(m_DoublePool.size() - 1);
	}

	std::uint32_t ConstantPool::ContainsIntConstant(std::uint32_t intConstant) const noexcept {
		const auto iter = std::find(m_IntPool.begin(), m_IntPool.end(), intConstant);
		if (iter == m_IntPool.end()) return 0;
		else return static_cast<std::uint32_t>(std::distance(m_IntPool.begin(), iter) + 1);
	}
	std::uint32_t ConstantPool::ContainsLongConstant(std::uint64_t longConstant) const noexcept {
		const auto iter = std::find(m_LongPool.begin(), m_LongPool.end(), longConstant);
		if (iter == m_LongPool.end()) return 0;
		else return static_cast<std::uint32_t>(std::distance(m_LongPool.begin(), iter) + 1);
	}
	std::uint32_t ConstantPool::ContainsDoubleConstant(double doubleConstant) const noexcept {
		const auto iter = std::find(m_DoublePool.begin(), m_DoublePool.end(), doubleConstant);
		if (iter == m_DoublePool.end()) return 0;
		else return static_cast<std::uint32_t>(std::distance(m_DoublePool.begin(), iter) + 1);
	}

	std::uint32_t ConstantPool::TransformRealIndex(IntConstantIndex index) const noexcept {
		return static_cast<std::uint32_t>(index) + GetIntConstantOffset();
	}
	std::uint32_t ConstantPool::TransformRealIndex(LongConstantIndex index) const noexcept {
		return static_cast<std::uint32_t>(index) + GetLongConstantOffset();
	}
	std::uint32_t ConstantPool::TransformRealIndex(DoubleConstantIndex index) const noexcept {
		return static_cast<std::uint32_t>(index) + GetDoubleConstantOffset();
	}

	std::uint32_t ConstantPool::GetIntConstantOffset() const noexcept {
		return 0;
	}
	std::uint32_t ConstantPool::GetLongConstantOffset() const noexcept {
		return GetIntConstantOffset() + GetIntConstantCount();
	}
	std::uint32_t ConstantPool::GetDoubleConstantOffset() const noexcept {
		return GetLongConstantOffset() + GetLongConstantCount();
	}
	std::uint32_t ConstantPool::GetIntConstantCount() const noexcept {
		return static_cast<std::uint32_t>(m_IntPool.size());
	}
	std::uint32_t ConstantPool::GetLongConstantCount() const noexcept {
		return static_cast<std::uint32_t>(m_LongPool.size());
	}
	std::uint32_t ConstantPool::GetDoubleConstantCount() const noexcept {
		return static_cast<std::uint32_t>(m_DoublePool.size());
	}
}