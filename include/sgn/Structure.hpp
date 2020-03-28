#pragma once

#include <sgn/Operand.hpp>
#include <sgn/Type.hpp>
#include <svm/Structure.hpp>

#include <cstdint>

namespace sgn {
	struct Field {
		sgn::Type Type;
		std::uint64_t Count = 0;

		Field(sgn::Type type) noexcept;
		Field(sgn::Type type, std::uint64_t count) noexcept;
	};
}

namespace sgn {
	using svm::Structure;
	using svm::Structures;

	class StructureInfo final : public svm::StructureInfo {
	public:
		using svm::StructureInfo::StructureInfo;
		StructureInfo(StructureInfo&& structureInfo) noexcept;

	public:
		StructureInfo& operator=(StructureInfo&& structureInfo) noexcept;

	public:
		FieldIndex AddField(const Field& field);
		FieldIndex AddField(sgn::Type type);
		FieldIndex AddField(sgn::Type type, std::uint64_t count);
		FieldIndex GetField(std::uint32_t index) const noexcept;
	};
}