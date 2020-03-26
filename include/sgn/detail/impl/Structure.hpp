#pragma once
#include <sgn/Structure.hpp>

namespace sgn {
	inline FieldIndex StructureInfo::AddField(sgn::Type type) {
		Fields.push_back(Field{ 0, type });
		return static_cast<FieldIndex>(Fields.size() - 1);
	}
	inline FieldIndex StructureInfo::AddField(sgn::Type type, std::uint64_t count) {
		Fields.push_back(Field{ 0, type, count });
		return static_cast<FieldIndex>(Fields.size() - 1);
	}
	inline FieldIndex StructureInfo::GetField(std::uint32_t index) const noexcept {
		return static_cast<FieldIndex>(index);
	}
}