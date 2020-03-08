#include <sgn/Structure.hpp>

#include <utility>

namespace sgn {
	Structure::Structure(std::vector<const Type*> fields) noexcept
		: Fields(std::move(fields)) {}
	Structure::Structure(Structure&& structure) noexcept
		: Fields(std::move(structure.Fields)) {}

	Structure& Structure::operator=(Structure&& structure) noexcept {
		Fields = std::move(structure.Fields);
		return *this;
	}
}