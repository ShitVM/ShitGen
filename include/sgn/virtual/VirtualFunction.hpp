#pragma once

#include <svm/core/virtual/VirtualFunction.hpp>

#include <cstdint>

namespace sgn {
	class VirtualFunctionInfo final : public svm::core::VirtualFunctionInfo {
	public:
		inline VirtualFunctionInfo(std::uint16_t arity, bool hasResult) noexcept;
		inline VirtualFunctionInfo(VirtualFunctionInfo&& functionInfo) noexcept;
		~VirtualFunctionInfo() = default;

	public:
		inline VirtualFunctionInfo& operator=(VirtualFunctionInfo&& functionInfo) noexcept;
	};
}

namespace sgn {
	using VirtualFunction = svm::core::VirtualFunction<VirtualFunctionInfo>;
	using VirtualFunctions = svm::core::VirtualFunctions<VirtualFunctionInfo>;
}

#include "detail/impl/VirtualFunction.hpp"