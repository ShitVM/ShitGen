#pragma once

#include <sgn/ConstantPool.hpp>
#include <sgn/Function.hpp>
#include <sgn/Instruction.hpp>
#include <sgn/Operand.hpp>
#include <sgn/Specification.hpp>
#include <sgn/Structure.hpp>
#include <sgn/Type.hpp>
#include <svm/core/ByteFile.hpp>

#include <cstdint>

namespace sgn {
	namespace detail {
		class ByteFileAdapter : public svm::core::ByteFile {
		public:
			using svm::core::ByteFile::ByteFile;
			inline ByteFileAdapter(ByteFileAdapter&& byteFile) noexcept;

		public:
			inline ByteFileAdapter& operator=(ByteFileAdapter&& byteFile) noexcept;

		protected:
			inline const Instructions* GetEntrypointInternal() const noexcept;
			inline Instructions* GetEntrypointInternal() noexcept;

		private:
			using svm::core::ByteFile::GetEntrypoint;
			using svm::core::ByteFile::SetEntrypoint;
		};
	}

	class Generator;

	class ByteFile final : public detail::ByteFileAdapter {
		friend class Generator;

	private:
		ShitBFVersion m_ShitBFVersion = ShitBFVersion::Latest;
		ShitBCVersion m_ShitBCVersion = ShitBCVersion::Latest;
		bool m_HasBuilder = false;

	public:
		ByteFile() noexcept = default;
		inline ByteFile(ByteFile&& byteFile) noexcept;
		~ByteFile() = default;

	public:
		inline ByteFile& operator=(ByteFile&& byteFile) noexcept;
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
		inline ShitBFVersion GetShitBFVersion() const noexcept;
		inline void SetShitBFVersion(ShitBFVersion version) noexcept;
		inline ShitBCVersion GetShitBCVersion() const noexcept;
		inline void SetShitBCVersion(ShitBCVersion version) noexcept;
		inline void CreatedBuilder() noexcept;

		inline TypeIndex GetTypeIndex(Type type) const noexcept;
		inline TypeIndex GetTypeIndex(StructureIndex structure) const noexcept;
		inline ArrayIndex MakeArray(Type type) const;
		inline ArrayIndex MakeArray(StructureIndex structure) const;
		inline ArrayIndex MakeArray(TypeIndex type) const;

		inline std::uint32_t TransformConstantIndex(IntConstantIndex index) const noexcept;
		inline std::uint32_t TransformConstantIndex(LongConstantIndex index) const noexcept;
		inline std::uint32_t TransformConstantIndex(DoubleConstantIndex index) const noexcept;
		inline std::uint32_t TransformConstantIndex(StructureIndex index) const noexcept;

		inline IntConstantIndex AddIntConstant(std::uint32_t value);
		inline LongConstantIndex AddLongConstant(std::uint64_t value);
		inline DoubleConstantIndex AddDoubleConstant(double value);
		inline IntConstantIndex AddIntConstantFast(std::uint32_t value);
		inline LongConstantIndex AddLongConstantFast(std::uint64_t value);
		inline DoubleConstantIndex AddDoubleConstantFast(double value);

		inline StructureIndex AddStructure();
		inline const StructureInfo* GetStructureInfo(TypeIndex index) const noexcept;
		inline StructureInfo* GetStructureInfo(TypeIndex index) noexcept;
		inline const StructureInfo* GetStructureInfo(StructureIndex index) const noexcept;
		inline StructureInfo* GetStructureInfo(StructureIndex index) noexcept;

		inline FunctionIndex AddFunction();
		inline FunctionIndex AddFunction(std::uint16_t arity);
		inline FunctionIndex AddFunction(bool hasResult);
		inline FunctionIndex AddFunction(std::uint16_t arity, bool hasResult);
		inline const FunctionInfo* GetFunctionInfo(FunctionIndex index) const noexcept;
		inline FunctionInfo* GetFunctionInfo(FunctionIndex index) noexcept;

		inline const Instructions* GetEntrypoint() const noexcept;
		inline Instructions* GetEntrypoint() noexcept;
	};
}

#include "detail/impl/ByteFile.hpp"