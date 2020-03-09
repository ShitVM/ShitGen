#pragma once

#include <sgn/Type.hpp>

#include <fstream>
#include <vector>

namespace sgn {
	class Structure final {
	public:
		std::vector<const Type*> m_Fields;
		Type m_Type;

	public:
		Structure() noexcept = default;
		explicit Structure(std::vector<const Type*> fields) noexcept;
		explicit Structure(Type&& type) noexcept;
		Structure(std::vector<const Type*> fields, Type&& type) noexcept;
		Structure(Structure&& structures) noexcept;
		~Structure() = default;

	public:
		Structure& operator=(Structure&& structure) noexcept;
		bool operator==(const Structure&) = delete;
		bool operator!=(const Structure&) = delete;

	public:
		void Save(std::ofstream& stream) const;

		std::uint32_t GetFieldCount() const noexcept;

		void AddField(const Type* type);

		const Type* GetType() const noexcept;
	};

	using StructurePtr = std::unique_ptr<Structure>;
	using Structures = std::vector<StructurePtr>;
}