#pragma once

#include <sgn/Operand.hpp>
#include <sgn/virtual/VirtualFunction.hpp>
#include <sgn/virtual/VirtualModule.hpp>
#include <svm/core/Loader.hpp>
#include <svm/core/Module.hpp>

namespace sgn {
	using ExternModuleInfo = svm::core::ModuleInfo<VirtualFunctionInfo>;
	using ExternModule = svm::core::Module<VirtualFunctionInfo>;
	using ExternModules = svm::core::Modules<VirtualFunctionInfo>;
}

namespace sgn::detail {
	class LoaderAdapter : public svm::core::Loader<VirtualFunctionInfo> {
	public:
		using svm::core::Loader<VirtualFunctionInfo>::Loader;
		LoaderAdapter(LoaderAdapter&& loader) noexcept;

	public:
		LoaderAdapter& operator=(LoaderAdapter&& loader) noexcept;

	protected:
		ExternModuleIndex GetModuleInternal(const std::string& path) const noexcept;
		const VirtualModule* GetModuleInfoInternal(ExternModuleIndex index) const noexcept;
		VirtualModule* GetModuleInfoInternal(ExternModuleIndex index) noexcept;

	protected:
		using svm::core::Loader<VirtualFunctionInfo>::Create;

	private:
		using svm::core::Loader<VirtualFunctionInfo>::Load;
		using svm::core::Loader<VirtualFunctionInfo>::LoadDependencies;

		using svm::core::Loader<VirtualFunctionInfo>::GetModule;
		using svm::core::Loader<VirtualFunctionInfo>::GetModules;
		using svm::core::Loader<VirtualFunctionInfo>::SetModules;
	};
}

namespace sgn {
	class ExternModuleManager final : public detail::LoaderAdapter {
	public:
		using detail::LoaderAdapter::LoaderAdapter;
		ExternModuleManager(ExternModuleManager&& manager) noexcept;

	public:
		ExternModuleManager& operator=(ExternModuleManager&& manager) noexcept;

	public:
		ExternModuleIndex CreateModule(const std::string& path);
		ExternModuleIndex GetModule(const std::string& path) const noexcept;
		const VirtualModule* GetModuleInfo(ExternModuleIndex index) const noexcept;
		VirtualModule* GetModuleInfo(ExternModuleIndex index) noexcept;
	};
}