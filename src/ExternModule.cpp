#include <sgn/ExternModule.hpp>

#include <sgn/virtual/VirtualModule.hpp>
#include <svm/core/virtual/VirtualModule.hpp>

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <iterator>
#include <utility>
#include <variant>

namespace sgn::detail {
	LoaderAdapter::LoaderAdapter(LoaderAdapter&& loader) noexcept
		: svm::core::Loader<VirtualFunctionInfo>(std::move(loader)) {}

	LoaderAdapter& LoaderAdapter::operator=(LoaderAdapter&& loader) noexcept {
		svm::core::Loader<VirtualFunctionInfo>::operator=(std::move(loader));
		return *this;
	}

	ExternModuleIndex LoaderAdapter::GetModuleInternal(const svm::core::ModulePath& path) const noexcept {
		const auto& modules = GetModules();
		const auto iter = std::find_if(modules.begin(), modules.end(), [path](const auto& module) {
			return module->GetPath() == path;
		});
		if (iter == modules.end()) {
			assert(false);
			return static_cast<ExternModuleIndex>(0);
		} else return static_cast<ExternModuleIndex>(std::distance(modules.begin(), iter));
	}
	const VirtualModule* LoaderAdapter::GetModuleInfoInternal(ExternModuleIndex index) const noexcept {
		return static_cast<const VirtualModule*>(&std::get<svm::core::VirtualModule<VirtualFunctionInfo>>(GetModules()[static_cast<std::uint32_t>(index)]->Module));
	}
	VirtualModule* LoaderAdapter::GetModuleInfoInternal(ExternModuleIndex index) noexcept {
		return static_cast<VirtualModule*>(&std::get<svm::core::VirtualModule<VirtualFunctionInfo>>(GetModules()[static_cast<std::uint32_t>(index)]->Module));
	}
}

namespace sgn {
	ExternModuleManager::ExternModuleManager(ExternModuleManager&& manager) noexcept
		: detail::LoaderAdapter(std::move(manager)) {}

	ExternModuleManager& ExternModuleManager::operator=(ExternModuleManager&& manager) noexcept {
		detail::LoaderAdapter(std::move(manager));
		return *this;
	}

	ExternModuleIndex ExternModuleManager::CreateModule(const std::string& path) {
		assert(!path.empty());

		auto modulePath = ResolveDependency(std::move(path));
		if (std::holds_alternative<std::filesystem::path>(modulePath)) {
			Create(std::move(std::get<std::filesystem::path>(modulePath)));
		} else if (std::holds_alternative<std::string>(modulePath)) {
			Create(std::move(std::get<std::string>(modulePath)));
		}
		return static_cast<ExternModuleIndex>(GetModuleCount() - 1);
	}
	ExternModuleIndex ExternModuleManager::GetModule(const std::string& path) const noexcept {
		return GetModuleInternal(ResolveDependency(path));
	}
	const VirtualModule* ExternModuleManager::GetModuleInfo(ExternModuleIndex index) const noexcept {
		return GetModuleInfoInternal(index);
	}
	VirtualModule* ExternModuleManager::GetModuleInfo(ExternModuleIndex index) noexcept {
		return GetModuleInfoInternal(index);
	}

	svm::core::ModulePath ExternModuleManager::ResolveDependency(const std::string& path) {
		const auto fsPath = std::filesystem::u8path(path);
		if (path[0] == '/') return std::filesystem::weakly_canonical(fsPath).generic_u8string();
		else return std::filesystem::weakly_canonical(fsPath);
	}
}