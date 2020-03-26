#pragma once
#include <sgn/ByteFile.hpp>

#include <cassert>

namespace sgn {
	namespace detail {
		inline const Instructions* ByteFileAdapter::GetEntrypointInternal() const noexcept {
			return &GetEntrypoint();
		}
		inline Instructions* ByteFileAdapter::GetEntrypointInternal() noexcept {
			return &GetEntrypoint();
		}
	}

	inline ByteFile::ByteFile(ByteFile&& byteFile) noexcept
		: detail::ByteFileAdapter(std::move(byteFile)), m_ShitBFVersion(byteFile.m_ShitBFVersion), m_ShitBCVersion(byteFile.m_ShitBCVersion),
		m_HasBuilder(byteFile.m_HasBuilder) {}

	inline ByteFile& ByteFile::operator=(ByteFile&& byteFile) noexcept {
		detail::ByteFileAdapter::operator=(std::move(byteFile));

		m_ShitBFVersion = byteFile.m_ShitBFVersion;
		m_ShitBCVersion = byteFile.m_ShitBCVersion;
		m_HasBuilder = byteFile.m_HasBuilder;
		return *this;
	}

	inline ShitBFVersion ByteFile::GetShitBFVersion() const noexcept {
		return m_ShitBFVersion;
	}
	inline void ByteFile::SetShitBFVersion(ShitBFVersion version) noexcept {
		m_ShitBFVersion = version;
	}
	inline ShitBCVersion ByteFile::GetShitBCVersion() const noexcept {
		return m_ShitBCVersion;
	}
	inline void ByteFile::SetShitBCVersion(ShitBCVersion version) noexcept {
		m_ShitBCVersion = version;
	}

	inline void ByteFile::CreatedBuilder() noexcept {
		m_HasBuilder = true;
	}

	inline TypeIndex ByteFile::GetTypeIndex(Type type) const noexcept {
		return static_cast<TypeIndex>(type->Code);
	}
	inline TypeIndex ByteFile::GetTypeIndex(StructureIndex structure) const noexcept {
		return static_cast<TypeIndex>(static_cast<std::uint32_t>(structure) + static_cast<std::uint32_t>(TypeCode::Structure));
	}
	inline ArrayIndex ByteFile::MakeArray(Type type) const {
		return MakeArray(GetTypeIndex(type));
	}
	inline ArrayIndex ByteFile::MakeArray(StructureIndex structure) const {
		return MakeArray(GetTypeIndex(structure));
	}
	inline ArrayIndex ByteFile::MakeArray(TypeIndex type) const {
		return static_cast<ArrayIndex>(type);
	}

	inline std::uint32_t ByteFile::TransformConstantIndex(IntConstantIndex index) const noexcept {
		return static_cast<const ConstantPool&>(GetConstantPool()).TransformRealIndex(index);
	}
	inline std::uint32_t ByteFile::TransformConstantIndex(LongConstantIndex index) const noexcept {
		return static_cast<const ConstantPool&>(GetConstantPool()).TransformRealIndex(index);
	}
	inline std::uint32_t ByteFile::TransformConstantIndex(DoubleConstantIndex index) const noexcept {
		return static_cast<const ConstantPool&>(GetConstantPool()).TransformRealIndex(index);
	}
	inline std::uint32_t ByteFile::TransformConstantIndex(StructureIndex index) const noexcept {
		return GetConstantPool().GetAllCount() + static_cast<std::uint32_t>(index);
	}

	inline IntConstantIndex ByteFile::AddIntConstant(std::uint32_t value) {
		if (const auto index = GetConstantPool().FindIntConstant(value); index != ConstantPool::NPos) return static_cast<IntConstantIndex>(index);
		else return static_cast<IntConstantIndex>(GetConstantPool().AddIntConstant(value));
	}
	inline LongConstantIndex ByteFile::AddLongConstant(std::uint64_t value) {
		if (const auto index = GetConstantPool().FindLongConstant(value); index != ConstantPool::NPos) return static_cast<LongConstantIndex>(index);
		else return static_cast<LongConstantIndex>(GetConstantPool().AddLongConstant(value));
	}
	inline DoubleConstantIndex ByteFile::AddDoubleConstant(double value) {
		if (const auto index = GetConstantPool().FindDoubleConstant(value); index != ConstantPool::NPos) return static_cast<DoubleConstantIndex>(index);
		else return static_cast<DoubleConstantIndex>(GetConstantPool().AddDoubleConstant(value));
	}
	inline IntConstantIndex ByteFile::AddIntConstantFast(std::uint32_t value) {
		return static_cast<IntConstantIndex>(GetConstantPool().AddIntConstant(value));
	}
	inline LongConstantIndex ByteFile::AddLongConstantFast(std::uint64_t value) {
		return static_cast<LongConstantIndex>(GetConstantPool().AddLongConstant(value));
	}
	inline DoubleConstantIndex ByteFile::AddDoubleConstantFast(double value) {
		return static_cast<DoubleConstantIndex>(GetConstantPool().AddDoubleConstant(value));
	}

	inline StructureIndex ByteFile::AddStructure() {
		const std::uint32_t number = static_cast<std::uint32_t>(GetStructures().size() + static_cast<std::uint32_t>(TypeCode::Structure));
		std::string name = "structure" + std::to_string(number - static_cast<std::uint32_t>(TypeCode::Structure));

		GetStructures().emplace_back(std::vector<Field>(), TypeInfo(std::move(name), static_cast<TypeCode>(number)));
		return static_cast<StructureIndex>(GetStructures().size() - 1);
	}
	inline const StructureInfo* ByteFile::GetStructureInfo(TypeIndex index) const noexcept {
		assert(static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(TypeCode::Structure));

		return &GetStructures()[static_cast<std::uint32_t>(index) - static_cast<std::uint32_t>(TypeCode::Structure)];
	}
	inline const StructureInfo* ByteFile::GetStructureInfo(StructureIndex index) const noexcept {
		return &GetStructures()[static_cast<std::uint32_t>(index)];
	}
	inline StructureInfo* ByteFile::GetStructureInfo(TypeIndex index) noexcept {
		assert(static_cast<std::uint32_t>(index) >= static_cast<std::uint32_t>(TypeCode::Structure));

		return &GetStructures()[static_cast<std::uint32_t>(index) - static_cast<std::uint32_t>(TypeCode::Structure)];
	}
	inline StructureInfo* ByteFile::GetStructureInfo(StructureIndex index) noexcept {
		return &GetStructures()[static_cast<std::uint32_t>(index)];
	}

	inline FunctionIndex ByteFile::AddFunction() {
		GetFunctions().emplace_back();
		return static_cast<FunctionIndex>(GetFunctions().size() - 1);
	}
	inline FunctionIndex ByteFile::AddFunction(std::uint16_t arity) {
		GetFunctions().emplace_back(arity);
		return static_cast<FunctionIndex>(GetFunctions().size() - 1);
	}
	inline FunctionIndex ByteFile::AddFunction(bool hasResult) {
		GetFunctions().emplace_back(hasResult);
		return static_cast<FunctionIndex>(GetFunctions().size() - 1);
	}
	inline FunctionIndex ByteFile::AddFunction(std::uint16_t arity, bool hasResult) {
		GetFunctions().emplace_back(arity, hasResult);
		return static_cast<FunctionIndex>(GetFunctions().size() - 1);
	}
	inline const FunctionInfo* ByteFile::GetFunctionInfo(FunctionIndex index) const noexcept {
		return &GetFunctions()[static_cast<std::uint32_t>(index)];
	}
	inline FunctionInfo* ByteFile::GetFunctionInfo(FunctionIndex index) noexcept {
		return &GetFunctions()[static_cast<std::uint32_t>(index)];
	}

	inline const Instructions* ByteFile::GetEntrypoint() const noexcept {
		return GetEntrypointInternal();
	}
	inline Instructions* ByteFile::GetEntrypoint() noexcept {
		return GetEntrypointInternal();
	}
}