#pragma once

#include <sgn/Function.hpp>
#include <sgn/Instruction.hpp>
#include <sgn/Operand.hpp>
#include <sgn/Specification.hpp>
#include <sgn/Structure.hpp>
#include <sgn/Type.hpp>
#include <svm/core/ByteFile.hpp>

#include <cstdint>

namespace sgn::detail {
	class ByteFileAdapter : public svm::core::ByteFile {
	public:
		using svm::core::ByteFile::ByteFile;
		ByteFileAdapter(ByteFileAdapter&& byteFile) noexcept;

	public:
		ByteFileAdapter& operator=(ByteFileAdapter&& byteFile) noexcept;

	protected:
		const Instructions* GetEntrypointInternal() const noexcept;
		Instructions* GetEntrypointInternal() noexcept;

	private:
		using svm::core::ByteFile::GetEntrypoint;
		using svm::core::ByteFile::SetEntrypoint;
	};
}

namespace sgn {
	class Generator;

	class ByteFile final : public detail::ByteFileAdapter {
		friend class Generator;

	private:
		ShitBFVersion m_ShitBFVersion = ShitBFVersion::Latest;
		ShitBCVersion m_ShitBCVersion = ShitBCVersion::Latest;
		bool m_HasBuilder = false;

	public:
		ByteFile() noexcept = default;
		ByteFile(ByteFile&& byteFile) noexcept;
		~ByteFile() = default;

	public:
		ByteFile& operator=(ByteFile&& byteFile) noexcept;
		bool operator==(const ByteFile&) = delete;
		bool operator!=(const ByteFile&) = delete;

	private:
		using svm::core::ByteFile::GetPath;
		using svm::core::ByteFile::SetPath;
		using svm::core::ByteFile::GetDependencies;
		using svm::core::ByteFile::SetDependencies;
		using svm::core::ByteFile::GetConstantPool;
		using svm::core::ByteFile::SetConstantPool;
		using svm::core::ByteFile::GetStructures;
		using svm::core::ByteFile::SetStructures;
		using svm::core::ByteFile::GetFunctions;
		using svm::core::ByteFile::SetFunctions;
		using svm::core::ByteFile::GetMappings;
		using svm::core::ByteFile::SetMappings;
		using svm::core::ByteFile::GetEntrypoint;
		using svm::core::ByteFile::SetEntrypoint;

		using svm::core::ByteFile::UpdateStructureCodes;

	public:
		ShitBFVersion GetShitBFVersion() const noexcept;
		void SetShitBFVersion(ShitBFVersion version) noexcept;
		ShitBCVersion GetShitBCVersion() const noexcept;
		void SetShitBCVersion(ShitBCVersion version) noexcept;
		void CreatedBuilder() noexcept;

		TypeIndex GetTypeIndex(Type type) const noexcept;
		TypeIndex GetTypeIndex(StructureIndex structure) const noexcept;
		ArrayIndex MakeArray(Type type) const;
		ArrayIndex MakeArray(StructureIndex structure) const;
		ArrayIndex MakeArray(TypeIndex type) const;

		std::uint32_t TransformConstantIndex(IntConstantIndex index) const noexcept;
		std::uint32_t TransformConstantIndex(LongConstantIndex index) const noexcept;
		std::uint32_t TransformConstantIndex(DoubleConstantIndex index) const noexcept;
		std::uint32_t TransformConstantIndex(StructureIndex index) const noexcept;

		IntConstantIndex AddIntConstant(std::uint32_t value);
		LongConstantIndex AddLongConstant(std::uint64_t value);
		DoubleConstantIndex AddDoubleConstant(double value);
		IntConstantIndex AddIntConstantFast(std::uint32_t value);
		LongConstantIndex AddLongConstantFast(std::uint64_t value);
		DoubleConstantIndex AddDoubleConstantFast(double value);

		StructureIndex AddStructure();
		const StructureInfo* GetStructureInfo(TypeIndex index) const noexcept;
		StructureInfo* GetStructureInfo(TypeIndex index) noexcept;
		const StructureInfo* GetStructureInfo(StructureIndex index) const noexcept;
		StructureInfo* GetStructureInfo(StructureIndex index) noexcept;

		FunctionIndex AddFunction();
		FunctionIndex AddFunction(std::uint16_t arity);
		FunctionIndex AddFunction(bool hasResult);
		FunctionIndex AddFunction(std::uint16_t arity, bool hasResult);
		const FunctionInfo* GetFunctionInfo(FunctionIndex index) const noexcept;
		FunctionInfo* GetFunctionInfo(FunctionIndex index) noexcept;

		const Instructions* GetEntrypoint() const noexcept;
		Instructions* GetEntrypoint() noexcept;
	};
}