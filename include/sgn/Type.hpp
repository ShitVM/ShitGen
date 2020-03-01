#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace sgn {
	class TypeData final {
	private:
		std::string m_Name;
		std::uint64_t m_Size = 0;

	public:
		TypeData(std::string name, std::uint64_t size) noexcept;
		TypeData(const TypeData&) = delete;
		virtual ~TypeData() = default;

	public:
		TypeData& operator=(const TypeData&) = delete;
		bool operator==(const TypeData&) = delete;
		bool operator!=(const TypeData&) = delete;

	public:
		std::string_view GetName() const noexcept;
		std::uint64_t GetSize() const noexcept;
	};
}

namespace sgn {
	class Type final {
	private:
		const TypeData* m_Data = nullptr;

	public:
		Type() noexcept = default;
		Type(std::nullptr_t) noexcept;
		Type(const TypeData* data) noexcept;
		Type(const Type& type) noexcept;
		~Type() = default;

	public:
		Type& operator=(std::nullptr_t) noexcept;
		Type& operator=(const TypeData* data) noexcept;
		Type& operator=(const Type& type) noexcept;
		bool operator==(const Type& type) const noexcept;
		bool operator!=(const Type& type) const noexcept;
		const TypeData& operator*() const noexcept;
		const TypeData* operator->() const noexcept;
	};

	extern const Type IntType;
	extern const Type LongType;
	extern const Type DoubleType;
}