#pragma once

#include <svm/core/virtual/VirtualFunction.hpp>

#include <cstdint>
#include <string>

namespace sgn {
	class VirtualFunctionInfo final : public svm::core::VirtualFunctionInfo {
	public:
		VirtualFunctionInfo(std::string name, std::uint16_t arity, bool hasResult) noexcept;
		VirtualFunctionInfo(VirtualFunctionInfo&& functionInfo) noexcept;
		~VirtualFunctionInfo() = default;

	public:
		VirtualFunctionInfo& operator=(VirtualFunctionInfo&& functionInfo) noexcept;
	};
}

namespace sgn {
	using VirtualFunction = svm::core::VirtualFunction<VirtualFunctionInfo>;
	using VirtualFunctions = svm::core::VirtualFunctions<VirtualFunctionInfo>;
}