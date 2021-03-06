#include <sgn/Structure.hpp>

#include <utility>

namespace sgn {
	Field::Field(sgn::Type type) noexcept
		: Type(type) {}
	Field::Field(sgn::Type type, std::uint64_t count) noexcept
		: Type(type), Count(count) {}
}

namespace sgn {
	StructureInfo::StructureInfo(StructureInfo&& structureInfo) noexcept
		: svm::StructureInfo(std::move(structureInfo)) {}

	StructureInfo& StructureInfo::operator=(StructureInfo&& structureInfo) noexcept {
		svm::StructureInfo::operator=(std::move(structureInfo));
		return *this;
	}

	FieldIndex StructureInfo::AddField(const Field& field) {
		Fields.push_back(svm::Field{ 0, field.Type, field.Count });
		return static_cast<FieldIndex>(Fields.size() - 1);
	}
	FieldIndex StructureInfo::AddField(sgn::Type type) {
		Fields.push_back(svm::Field{ 0, type });
		return static_cast<FieldIndex>(Fields.size() - 1);
	}
	FieldIndex StructureInfo::AddField(sgn::Type type, std::uint64_t count) {
		Fields.push_back(svm::Field{ 0, type, count });
		return static_cast<FieldIndex>(Fields.size() - 1);
	}
	FieldIndex StructureInfo::GetField(std::uint32_t index) const noexcept {
		return static_cast<FieldIndex>(index);
	}
}