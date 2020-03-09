#pragma once

#include <sgn/Type.hpp>

#include <fstream>
#include <vector>

namespace sgn {
	class Structure final {
	public:
		std::vector<const sgn::Type*> Fields;
		sgn::Type Type;

	public:
		Structure() noexcept = default;
		explicit Structure(std::vector<const sgn::Type*> fields) noexcept;
		explicit Structure(sgn::Type&& type) noexcept;
		Structure(std::vector<const sgn::Type*> fields, sgn::Type&& type) noexcept;
		Structure(Structure&& structures) noexcept;
		~Structure() = default;

	public:
		Structure& operator=(Structure&& structure) noexcept;
		bool operator==(const Structure&) = delete;
		bool operator!=(const Structure&) = delete;

	public:
		void Save(std::ofstream& stream) const;
	};

	using StructurePtr = std::unique_ptr<Structure>;
	using Structures = std::vector<StructurePtr>;
}