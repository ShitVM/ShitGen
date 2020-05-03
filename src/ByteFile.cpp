#include <sgn/ByteFile.hpp>

#include <sgn/ConstantPool.hpp>

#include <cassert>
#include <string>
#include <utility>

namespace sgn::detail {
	ByteFileAdapter::ByteFileAdapter(ByteFileAdapter&& byteFile) noexcept
		: svm::core::ByteFile(std::move(byteFile)) {}

	ByteFileAdapter& ByteFileAdapter::operator=(ByteFileAdapter&& byteFile) noexcept {
		svm::core::ByteFile::operator=(std::move(byteFile));
		return *this;
	}

	const Instructions* ByteFileAdapter::GetEntrypointInternal() const noexcept {
		return &svm::core::ByteFile::GetEntrypoint();
	}
	Instructions* ByteFileAdapter::GetEntrypointInternal() noexcept {
		return &svm::core::ByteFile::GetEntrypoint();
	}
}

namespace sgn {
	ByteFile::ByteFile(ByteFile&& byteFile) noexcept
		: detail::ByteFileAdapter(std::move(byteFile)), m_Dependencies(std::move(byteFile.m_Dependencies)),
		m_ShitBFVersion(byteFile.m_ShitBFVersion), m_ShitBCVersion(byteFile.m_ShitBCVersion), m_HasBuilder(byteFile.m_HasBuilder) {}

	ByteFile& ByteFile::operator=(ByteFile&& byteFile) noexcept {
		detail::ByteFileAdapter::operator=(std::move(byteFile));

		m_Dependencies = std::move(byteFile.m_Dependencies);

		m_ShitBFVersion = byteFile.m_ShitBFVersion;
		m_ShitBCVersion = byteFile.m_ShitBCVersion;
		m_HasBuilder = byteFile.m_HasBuilder;
		return *this;
	}

	ShitBFVersion ByteFile::GetShitBFVersion() const noexcept {
		return m_ShitBFVersion;
	}
	void ByteFile::SetShitBFVersion(ShitBFVersion version) noexcept {
		assert(version >= ShitBFVersion::Least);

		m_ShitBFVersion = version;
	}
	ShitBCVersion ByteFile::GetShitBCVersion() const noexcept {
		return m_ShitBCVersion;
	}
	void ByteFile::SetShitBCVersion(ShitBCVersion version) noexcept {
		assert(!m_HasBuilder);
		assert(version >= ShitBCVersion::Least);

		m_ShitBCVersion = version;
	}

	void ByteFile::CreatedBuilder() noexcept {
		m_HasBuilder = true;
	}

	TypeIndex ByteFile::GetTypeIndex(Type type) const noexcept {
		return static_cast<TypeIndex>(type->Code);
	}
	TypeIndex ByteFile::GetTypeIndex(StructureIndex structure) const noexcept {
		return static_cast<TypeIndex>(static_cast<std::uint32_t>(structure) + static_cast<std::uint32_t>(TypeCode::Structure));
	}
	MappedTypeIndex ByteFile::GetTypeIndex(MappedStructureIndex structure) const noexcept {
		return static_cast<MappedTypeIndex>(structure);
	}
	ArrayIndex ByteFile::MakeArray(Type type) const {
		return MakeArray(GetTypeIndex(type));
	}
	ArrayIndex ByteFile::MakeArray(StructureIndex structure) const {
		return MakeArray(GetTypeIndex(structure));
	}
	ArrayIndex ByteFile::MakeArray(TypeIndex type) const {
		return static_cast<ArrayIndex>(type);
	}
	MappedArrayIndex ByteFile::MakeArray(MappedStructureIndex structure) const {
		return MakeArray(GetTypeIndex(structure));
	}
	MappedArrayIndex ByteFile::MakeArray(MappedTypeIndex type) const {
		return static_cast<MappedArrayIndex>(type);
	}

	std::uint32_t ByteFile::TransformConstantIndex(IntConstantIndex index) const noexcept {
		return static_cast<const ConstantPool&>(GetConstantPool()).TransformRealIndex(index);
	}
	std::uint32_t ByteFile::TransformConstantIndex(LongConstantIndex index) const noexcept {
		return static_cast<const ConstantPool&>(GetConstantPool()).TransformRealIndex(index);
	}
	std::uint32_t ByteFile::TransformConstantIndex(DoubleConstantIndex index) const noexcept {
		return static_cast<const ConstantPool&>(GetConstantPool()).TransformRealIndex(index);
	}
	std::uint32_t ByteFile::TransformConstantIndex(StructureIndex index) const noexcept {
		return GetConstantPool().GetAllCount() + static_cast<std::uint32_t>(index);
	}
	std::uint32_t ByteFile::TransformMappedIndex(MappedTypeIndex index) const noexcept {
		return static_cast<std::uint32_t>(GetStructures().size() + static_cast<std::uint32_t>(index));
	}
	std::uint32_t ByteFile::TransformMappedIndex(MappedStructureIndex index) const noexcept {
		return GetConstantPool().GetAllCount() + TransformMappedIndex(static_cast<MappedTypeIndex>(index));
	}
	std::uint32_t ByteFile::TransformMappedIndex(MappedFunctionIndex index) const noexcept {
		return static_cast<std::uint32_t>(GetFunctions().size() + static_cast<std::uint32_t>(index));
	}

	ExternModuleIndex ByteFile::AddExternModule(const std::string& path) {
		GetDependencies().push_back(path);
		return m_Dependencies.CreateModule(path);
	}
	ExternModuleIndex ByteFile::GetExternModule(const std::string& path) const noexcept {
		return m_Dependencies.GetModule(path);
	}
	const VirtualModule* ByteFile::GetExternModuleInfo(ExternModuleIndex index) const noexcept {
		return m_Dependencies.GetModuleInfo(index);
	}
	VirtualModule* ByteFile::GetExternModuleInfo(ExternModuleIndex index) noexcept {
		return m_Dependencies.GetModuleInfo(index);
	}

	IntConstantIndex ByteFile::AddIntConstant(std::uint32_t value) {
		if (const auto index = GetConstantPool().FindIntConstant(value); index != ConstantPool::NPos) return static_cast<IntConstantIndex>(index);
		else return static_cast<IntConstantIndex>(GetConstantPool().AddIntConstant(value));
	}
	LongConstantIndex ByteFile::AddLongConstant(std::uint64_t value) {
		if (const auto index = GetConstantPool().FindLongConstant(value); index != ConstantPool::NPos) return static_cast<LongConstantIndex>(index);
		else return static_cast<LongConstantIndex>(GetConstantPool().AddLongConstant(value));
	}
	DoubleConstantIndex ByteFile::AddDoubleConstant(double value) {
		if (const auto index = GetConstantPool().FindDoubleConstant(value); index != ConstantPool::NPos) return static_cast<DoubleConstantIndex>(index);
		else return static_cast<DoubleConstantIndex>(GetConstantPool().AddDoubleConstant(value));
	}
	IntConstantIndex ByteFile::AddIntConstantFast(std::uint32_t value) {
		return static_cast<IntConstantIndex>(GetConstantPool().AddIntConstant(value));
	}
	LongConstantIndex ByteFile::AddLongConstantFast(std::uint64_t value) {
		return static_cast<LongConstantIndex>(GetConstantPool().AddLongConstant(value));
	}
	DoubleConstantIndex ByteFile::AddDoubleConstantFast(double value) {
		return static_cast<DoubleConstantIndex>(GetConstantPool().AddDoubleConstant(value));
	}

	StructureIndex ByteFile::AddStructure() {
		const std::uint32_t number = static_cast<std::uint32_t>(GetStructures().size() + static_cast<std::uint32_t>(TypeCode::Structure));
		std::string name = "structure" + std::to_string(number - static_cast<std::uint32_t>(TypeCode::Structure));

		GetStructures().emplace_back(std::vector<svm::Field>(), TypeInfo(std::move(name), static_cast<TypeCode>(number)));
		return static_cast<StructureIndex>(GetStructures().size() - 1);
	}
	const StructureInfo* ByteFile::GetStructureInfo(TypeIndex index) const noexcept {
		assert(static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(TypeCode::Structure));

		return static_cast<const StructureInfo*>(&GetStructures()[static_cast<std::uint32_t>(index) - static_cast<std::uint32_t>(TypeCode::Structure)]);
	}
	StructureInfo* ByteFile::GetStructureInfo(TypeIndex index) noexcept {
		assert(static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(TypeCode::Structure));

		return static_cast<StructureInfo*>(&GetStructures()[static_cast<std::uint32_t>(index) - static_cast<std::uint32_t>(TypeCode::Structure)]);
	}
	const StructureInfo* ByteFile::GetStructureInfo(StructureIndex index) const noexcept {
		return GetStructureInfo(GetTypeIndex(index));
	}
	StructureInfo* ByteFile::GetStructureInfo(StructureIndex index) noexcept {
		return GetStructureInfo(GetTypeIndex(index));
	}
	const StructureInfo* ByteFile::GetStructureInfo(MappedTypeIndex index) const noexcept {
		const auto& mapping = GetMappings().GetStructureMapping(static_cast<std::uint32_t>(index));
		const auto moduleInfo = m_Dependencies.GetModuleInfo(static_cast<ExternModuleIndex>(mapping.Module));
		return static_cast<const StructureInfo*>(&moduleInfo->GetStructures()[mapping.Index]);
	}
	StructureInfo* ByteFile::GetStructureInfo(MappedTypeIndex index) noexcept {
		const auto& mapping = GetMappings().GetStructureMapping(static_cast<std::uint32_t>(index));
		const auto moduleInfo = m_Dependencies.GetModuleInfo(static_cast<ExternModuleIndex>(mapping.Module));
		return static_cast<StructureInfo*>(&moduleInfo->GetStructures()[mapping.Index]);
	}
	const StructureInfo* ByteFile::GetStructureInfo(MappedStructureIndex index) const noexcept {
		return GetStructureInfo(GetTypeIndex(index));
	}
	StructureInfo* ByteFile::GetStructureInfo(MappedStructureIndex index) noexcept {
		return GetStructureInfo(GetTypeIndex(index));
	}

	FunctionIndex ByteFile::AddFunction() {
		GetFunctions().emplace_back();
		return static_cast<FunctionIndex>(GetFunctions().size() - 1);
	}
	FunctionIndex ByteFile::AddFunction(std::uint16_t arity) {
		GetFunctions().emplace_back(arity);
		return static_cast<FunctionIndex>(GetFunctions().size() - 1);
	}
	FunctionIndex ByteFile::AddFunction(bool hasResult) {
		GetFunctions().emplace_back(hasResult);
		return static_cast<FunctionIndex>(GetFunctions().size() - 1);
	}
	FunctionIndex ByteFile::AddFunction(std::uint16_t arity, bool hasResult) {
		GetFunctions().emplace_back(arity, hasResult);
		return static_cast<FunctionIndex>(GetFunctions().size() - 1);
	}
	const FunctionInfo* ByteFile::GetFunctionInfo(FunctionIndex index) const noexcept {
		return &GetFunctions()[static_cast<std::uint32_t>(index)];
	}
	FunctionInfo* ByteFile::GetFunctionInfo(FunctionIndex index) noexcept {
		return &GetFunctions()[static_cast<std::uint32_t>(index)];
	}

	MappedStructureIndex ByteFile::Map(ExternModuleIndex module, ExternStructureIndex structure) {
		GetMappings().AddStructureMapping(static_cast<std::uint32_t>(module), static_cast<std::uint32_t>(structure));
		return static_cast<MappedStructureIndex>(GetMappings().GetStructureMappingCount() - 1);
	}
	MappedFunctionIndex ByteFile::Map(ExternModuleIndex module, ExternFunctionIndex function) {
		GetMappings().AddFunctionMapping(static_cast<std::uint32_t>(module), static_cast<std::uint32_t>(function));
		return static_cast<MappedFunctionIndex>(GetMappings().GetFunctionMappingCount() - 1);
	}

	const Instructions* ByteFile::GetEntrypoint() const noexcept {
		return GetEntrypointInternal();
	}
	Instructions* ByteFile::GetEntrypoint() noexcept {
		return GetEntrypointInternal();
	}
}