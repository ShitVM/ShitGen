#include <sgn/Type.hpp>

namespace sgn {
	TypeData::TypeData(std::string name, std::uint64_t size) noexcept
		: m_Name(std::move(name)), m_Size(size) {}

	std::string_view TypeData::GetName() const noexcept {
		return m_Name;
	}
	std::uint64_t TypeData::GetSize() const noexcept {
		return m_Size;
	}
}

namespace sgn {
	Type::Type(std::nullptr_t) noexcept {}
	Type::Type(const TypeData* data) noexcept
		: m_Data(data) {}
	Type::Type(const Type& type) noexcept
		: m_Data(type.m_Data) {}

	Type& Type::operator=(std::nullptr_t) noexcept {
		m_Data = nullptr;
		return *this;
	}
	Type& Type::operator=(const TypeData* data) noexcept {
		m_Data = data;
		return *this;
	}
	Type& Type::operator=(const Type& type) noexcept {
		m_Data = type.m_Data;
		return *this;
	}
	bool Type::operator==(const Type& type) const noexcept {
		return m_Data == type.m_Data;
	}
	bool Type::operator!=(const Type& type) const noexcept {
		return m_Data != type.m_Data;
	}
	const TypeData& Type::operator*() const noexcept {
		return *m_Data;
	}
	const TypeData* Type::operator->() const noexcept {
		return m_Data;
	}

	namespace {
		static const TypeData s_IntType("int", 4);
		static const TypeData s_LongType("long", 8);
		static const TypeData s_DoubleType("double", 8);
	}

	const Type IntType = &s_IntType;
	const Type LongType = &s_LongType;
	const Type DoubleType = &s_DoubleType;
}