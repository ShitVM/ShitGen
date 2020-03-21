#pragma once

#include <sgn/Operand.hpp>
#include <sgn/Type.hpp>

#include <fstream>
#include <memory>
#include <vector>

namespace sgn {
	struct Field final {
		const sgn::Type* Type;
		std::uint64_t Count = 0;

		bool IsArray() const noexcept;
	};
}

namespace sgn {
	class Structure final {
	public:
		std::vector<Field> m_Fields;
		Type m_Type;

	public:
		Structure() noexcept = default;
		explicit Structure(std::vector<Field> fields) noexcept;
		explicit Structure(Type&& type) noexcept;
		Structure(std::vector<Field> fields, Type&& type) noexcept;
		Structure(Structure&& structures) noexcept;
		~Structure() = default;

	public:
		Structure& operator=(Structure&& structure) noexcept;
		bool operator==(const Structure&) = delete;
		bool operator!=(const Structure&) = delete;

	public:
		void Save(std::ofstream& stream) const;

		std::uint32_t GetFieldCount() const noexcept;

		FieldIndex AddField(const Type* type);
		FieldIndex AddField(const Type* type, std::uint64_t count);
		FieldIndex GetField(std::uint32_t index) const noexcept;

		const Type* GetType() const noexcept;
	};

	using StructurePtr = std::unique_ptr<Structure>;
	using Structures = std::vector<StructurePtr>;
}