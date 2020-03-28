#pragma once

#include <sgn/Operand.hpp>
#include <sgn/Structure.hpp>
#include <sgn/virtual/VirtualFunction.hpp>
#include <svm/core/virtual/VirtualModule.hpp>

#include <cstdint>
#include <vector>

namespace sgn {
	class VirtualModule final : public svm::core::VirtualModule<VirtualFunctionInfo> {
	public:
		using svm::core::VirtualModule<VirtualFunctionInfo>::VirtualModule;
		VirtualModule(VirtualModule&& module) noexcept;

	public:
		VirtualModule& operator=(VirtualModule&& module) noexcept;

	public:
		ExternStructureIndex AddStructure(const std::vector<Field>& fields);
		ExternFunctionIndex AddFunction(std::uint16_t arity, bool hasResult);
	};
}