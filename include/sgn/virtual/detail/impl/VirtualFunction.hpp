#pragma once
#include <sgn/virtual/VirtualFunction.hpp>

#include <utility>

namespace sgn {
	inline VirtualFunctionInfo::VirtualFunctionInfo(std::uint16_t arity, bool hasResult) noexcept
		: svm::core::VirtualFunctionInfo(arity, hasResult) {}
	inline VirtualFunctionInfo::VirtualFunctionInfo(VirtualFunctionInfo&& functionInfo) noexcept
		: svm::core::VirtualFunctionInfo(std::move(functionInfo)) {}

	inline VirtualFunctionInfo& VirtualFunctionInfo::operator=(VirtualFunctionInfo&& functionInfo) noexcept {
		svm::core::VirtualFunctionInfo::operator=(std::move(functionInfo));
		return *this;
	}
}