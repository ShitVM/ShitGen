#include <sgn/Type.hpp>

#include <utility>

namespace sgn {
	Type::Type(std::string name, std::uint32_t code) noexcept
		: Name(std::move(name)), Code(code) {}

	namespace {
		static const Type s_IntType("int", 3);
		static const Type s_LongType("long", 4);
		static const Type s_DoubleType("double", 6);
		static const Type s_PointerType("pointer", 7);
	}

	const Type* IntType = &s_IntType;
	const Type* LongType = &s_LongType;
	const Type* DoubleType = &s_DoubleType;
	const Type* PointerType = &s_PointerType;
}