#include <sgn/Structure.hpp>

#include <sgn/Memory.hpp>

#include <cassert>
#include <utility>

namespace sgn {
	bool Field::IsArray() const noexcept {
		return Count >= 1;
	}
}

namespace sgn {
	Structure::Structure(std::vector<Field> fields) noexcept
		: m_Fields(std::move(fields)) {}
	Structure::Structure(Type&& type) noexcept
		: m_Type(std::move(type)) {}
	Structure::Structure(std::vector<Field> fields, Type&& type) noexcept
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
			if (m_Fields[i].IsArray()) {
				WriteConstant(stream, m_Fields[i].Type->Code | (1 << 31));
				WriteConstant(stream, m_Fields[i].Count);
			} else {
				WriteConstant(stream, m_Fields[i].Type->Code);
			}
		}
	}
	std::uint32_t Structure::GetFieldCount() const noexcept {
		return static_cast<std::uint32_t>(m_Fields.size());
	}

	FieldIndex Structure::AddField(const Type* type) {
		m_Fields.emplace_back().Type = type;
		return static_cast<FieldIndex>(m_Fields.size() - 1);
	}
	FieldIndex Structure::AddField(const Type* type, std::uint64_t count) {
		Field& field = m_Fields.emplace_back();
		field.Type = type;
		field.Count = count;
		return static_cast<FieldIndex>(m_Fields.size() - 1);
	}
	FieldIndex Structure::GetField(std::uint32_t index) const noexcept {
		assert(index < m_Fields.size());
		return static_cast<FieldIndex>(index);
	}

	const Type* Structure::GetType() const noexcept {
		return &m_Type;
	}
}