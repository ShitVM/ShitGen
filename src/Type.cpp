#include <sgn/Type.hpp>

#include <utility>

namespace sgn {
	Type::Type(std::string name, std::uint32_t code) noexcept
		: Name(std::move(name)), Code(code) {}
	Type::Type(Type&& type) noexcept
		: Name(std::move(type.Name)), Code(type.Code) {}

	Type& Type::operator=(Type&& type) noexcept {
		Name = std::move(type.Name);
		Code = type.Code;
		return *this;
	}

	namespace {
		static const Type s_IntType("int", 3);
		static const Type s_LongType("long", 4);
		static const Type s_DoubleType("double", 6);
		static const Type s_PointerType("pointer", 7);
		static const Type s_GCPointerType("gcpointer", 8);
	}

	const Type* IntType = &s_IntType;
	const Type* LongType = &s_LongType;
	const Type* DoubleType = &s_DoubleType;
	const Type* PointerType = &s_PointerType;
	const Type* GCPointerType = &s_GCPointerType;
}