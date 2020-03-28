#include <sgn/virtual/VirtualModule.hpp>

#include <utility>

namespace sgn {
	VirtualModule::VirtualModule(VirtualModule&& module) noexcept
		: svm::core::VirtualModule<VirtualFunctionInfo>(std::move(module)) {}

	VirtualModule& VirtualModule::operator=(VirtualModule&& module) noexcept {
		svm::core::VirtualModule<VirtualFunctionInfo>::operator=(std::move(module));
		return *this;
	}

	ExternFunctionIndex VirtualModule::AddFunction(std::uint16_t arity, bool hasResult) {
		auto& functions = GetFunctions();
		functions.emplace_back(arity, hasResult);
		return static_cast<ExternFunctionIndex>(functions.size() - 1);
	}
}