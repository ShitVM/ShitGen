#include <sgn/virtual/VirtualModule.hpp>

#include <utility>

namespace sgn {
	VirtualModule::VirtualModule(VirtualModule&& module) noexcept
		: svm::core::VirtualModule<VirtualFunctionInfo>(std::move(module)) {}

	VirtualModule& VirtualModule::operator=(VirtualModule&& module) noexcept {
		svm::core::VirtualModule<VirtualFunctionInfo>::operator=(std::move(module));
		return *this;
	}

	ExternStructureIndex VirtualModule::AddStructure(std::string name, const std::vector<Field>& fields) {
		auto& structures = GetStructures();
		StructureInfo& structure = static_cast<StructureInfo&>(structures.emplace_back());
		structure.Name = name;
		structure.Type.Name = std::move(name);

		for (const auto& field : fields) {
			structure.AddField(field);
		}

		return static_cast<ExternStructureIndex>(structures.size() - 1);
	}
	ExternFunctionIndex VirtualModule::AddFunction(std::string name, std::uint16_t arity, bool hasResult) {
		auto& functions = GetFunctions();
		functions.emplace_back(std::move(name), arity, hasResult);
		return static_cast<ExternFunctionIndex>(functions.size() - 1);
	}
}