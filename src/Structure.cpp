#include <sgn/Structure.hpp>

#include <sgn/Memory.hpp>

#include <utility>

namespace sgn {
	Structure::Structure(std::vector<const Type*> fields) noexcept
		: m_Fields(std::move(fields)) {}
	Structure::Structure(Type&& type) noexcept
		: m_Type(std::move(type)) {}
	Structure::Structure(std::vector<const Type*> fields, Type&& type) noexcept
		: m_Fields(std::move(fields)), m_Type(std::move(type)) {}
	Structure::Structure(Structure&& structure) noexcept
		: m_Fields(std::move(structure.m_Fields)), m_Type(std::move(structure.m_Type)) {}

	Structure& Structure::operator=(Structure&& structure) noexcept {
		m_Fields = std::move(structure.m_Fields);
		m_Type = std::move(structure.m_Type);
		return *this;
	}

	void Structure::Save(std::ofstream& stream) const {
		WriteConstant(stream, static_cast<std::uint32_t>(m_Fields.size()));
		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(m_Fields.size()); ++i) {
			WriteConstant(stream, m_Fields[i]->Code);
		}
	}
	std::uint32_t Structure::GetFieldCount() const noexcept {
		return static_cast<std::uint32_t>(m_Fields.size());
	}

	void Structure::AddField(const Type* type) {
		m_Fields.push_back(type);
	}

	const Type* Structure::GetType() const noexcept {
		return &m_Type;
	}
}