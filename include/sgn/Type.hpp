#pragma once

#include <cstdint>
#include <string>

namespace sgn {
	class Type final {
	public:
		std::string Name;
		std::uint32_t Code = 0;

	public:
		Type() noexcept = default;
		Type(std::string name, std::uint32_t code) noexcept;
		Type(Type&& type) noexcept;
		virtual ~Type() = default;

	public:
		Type& operator=(Type&& type) noexcept;
		bool operator==(const Type&) = delete;
		bool operator!=(const Type&) = delete;
	};

	extern const Type* IntType;
	extern const Type* LongType;
	extern const Type* DoubleType;
	extern const Type* PointerType;
	extern const Type* GCPointerType;
}