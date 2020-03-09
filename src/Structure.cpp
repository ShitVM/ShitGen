#include <sgn/Structure.hpp>

#include <sgn/Memory.hpp>

#include <utility>

namespace sgn {
	Structure::Structure(std::vector<const sgn::Type*> fields) noexcept
		: Fields(std::move(fields)) {}
	Structure::Structure(sgn::Type&& type) noexcept
		: Type(std::move(type)) {}
	Structure::Structure(std::vector<const sgn::Type*> fields, sgn::Type&& type) noexcept
		: Fields(std::move(fields)), Type(std::move(type)) {}
	Structure::Structure(Structure&& structure) noexcept
		: Fields(std::move(structure.Fields)), Type(std::move(structure.Type)) {}

	Structure& Structure::operator=(Structure&& structure) noexcept {
		Fields = std::move(structure.Fields);
		return *this;
	}

	void Structure::Save(std::ofstream& stream) const {
		WriteConstant(stream, static_cast<std::uint32_t>(Fields.size()));
		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(Fields.size()); ++i) {
			WriteConstant(stream, Fields[i]->Code);
		}
	}
}