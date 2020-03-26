#pragma once

#include <sgn/Operand.hpp>
#include <sgn/Type.hpp>
#include <svm/Structure.hpp>

#include <cstdint>

namespace sgn {
	using svm::Field;
	using svm::Structure;
	using svm::Structures;

	class StructureInfo final : public svm::StructureInfo {
	public:
		using svm::StructureInfo::StructureInfo;
		inline StructureInfo(StructureInfo&& structureInfo) noexcept;

	public:
		inline StructureInfo& operator=(StructureInfo&& structureInfo) noexcept;

	public:
		inline FieldIndex AddField(sgn::Type type);
		inline FieldIndex AddField(sgn::Type type, std::uint64_t count);
		inline FieldIndex GetField(std::uint32_t index) const noexcept;
	};
}

#include "detail/impl/Structure.hpp"