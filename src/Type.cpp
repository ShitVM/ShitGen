#include <sgn/Type.hpp>

namespace sgn {
	Type::Type(std::string name, std::uint64_t size) noexcept
		: m_Name(std::move(name)), m_Size(size) {}

	std::string_view Type::GetName() const noexcept {
		return m_Name;
	}
	std::uint64_t Type::GetSize() const noexcept {
		return m_Size;
	}

	namespace {
		static const Type s_IntType("int", 4);
		static const Type s_LongType("long", 8);
		static const Type s_DoubleType("double", 8);
	}

	const Type* IntType = &s_IntType;
	const Type* LongType = &s_LongType;
	const Type* DoubleType = &s_DoubleType;
}