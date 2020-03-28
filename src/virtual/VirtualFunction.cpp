#include <sgn/virtual/VirtualFunction.hpp>

#include <utility>

namespace sgn {
	VirtualFunctionInfo::VirtualFunctionInfo(std::uint16_t arity, bool hasResult) noexcept
		: svm::core::VirtualFunctionInfo(arity, hasResult) {}
	VirtualFunctionInfo::VirtualFunctionInfo(VirtualFunctionInfo&& functionInfo) noexcept
		: svm::core::VirtualFunctionInfo(std::move(functionInfo)) {}

	VirtualFunctionInfo& VirtualFunctionInfo::operator=(VirtualFunctionInfo&& functionInfo) noexcept {
		svm::core::VirtualFunctionInfo::operator=(std::move(functionInfo));
		return *this;
	}
}