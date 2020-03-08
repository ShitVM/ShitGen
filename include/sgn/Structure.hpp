#pragma once

#include <sgn/Type.hpp>

#include <vector>

namespace sgn {
	class Structure final {
	public:
		std::vector<const Type*> Fields;

	public:
		Structure() noexcept = default;
		explicit Structure(std::vector<const Type*> fields) noexcept;
		Structure(Structure&& structures) noexcept;
		~Structure() = default;

	public:
		Structure& operator=(Structure&& structure) noexcept;
		bool operator==(const Structure&) = delete;
		bool operator!=(const Structure&) = delete;
	};

	using Structures = std::vector<Structure*>;
}