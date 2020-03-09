#include <sgn/Structure.hpp>

#include <sgn/Memory.hpp>

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

	void Structure::Save(std::ofstream& stream) const {
		WriteConstant(stream, static_cast<std::uint32_t>(Fields.size()));
		for (std::uint32_t i = 0; i < Fields.size(); ++i) {
			WriteConstant(stream, Fields[i]->Code);
		}
	}
}