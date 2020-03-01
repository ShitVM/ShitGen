#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace sgn {
	class Type final {
	private:
		std::string m_Name;
		std::uint64_t m_Size = 0;

	public:
		Type(std::string name, std::uint64_t size) noexcept;
		Type(const Type&) = delete;
		virtual ~Type() = default;

	public:
		Type& operator=(const Type&) = delete;
		bool operator==(const Type&) = delete;
		bool operator!=(const Type&) = delete;

	public:
		std::string_view GetName() const noexcept;
		std::uint64_t GetSize() const noexcept;
	};

	extern const Type* IntType;
	extern const Type* LongType;
	extern const Type* DoubleType;
}