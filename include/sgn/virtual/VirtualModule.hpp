#pragma once

#include <sgn/Operand.hpp>
#include <sgn/virtual/VirtualFunction.hpp>
#include <svm/core/virtual/VirtualModule.hpp>

namespace sgn {
	class VirtualModule final : public svm::core::VirtualModule<VirtualFunctionInfo> {
	public:
		using svm::core::VirtualModule<VirtualFunctionInfo>::VirtualModule;
		inline VirtualModule(VirtualModule&& module) noexcept;

	public:
		inline VirtualModule& operator=(VirtualModule&& module) noexcept;

	public:
		inline ExternFunctionIndex AddFunction(std::uint16_t arity, bool hasResult);
	};
}

#include "detail/impl/VirtualModule.hpp"