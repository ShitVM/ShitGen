#pragma once

#include <cstdint>
#include <string>

namespace sgn {
	class Type final {
	public:
		std::string Name;
		std::uint32_t Code = 0;

	public:
		Type(std::string name, std::uint32_t code) noexcept;
		Type(const Type&) = delete;
		virtual ~Type() = default;

	public:
		Type& operator=(const Type&) = delete;
		bool operator==(const Type&) = delete;
		bool operator!=(const Type&) = delete;
	};

	extern const Type* IntType;
	extern const Type* LongType;
	extern const Type* DoubleType;
	extern const Type* PointerType;
}