#pragma once

#include <sgn/ConstantPool.hpp>
#include <sgn/Function.hpp>
#include <sgn/Instruction.hpp>
#include <sgn/Structure.hpp>
#include <sgn/Operand.hpp>
#include <sgn/Version.hpp>

#include <cstdint>
#include <string>

namespace sgn {
	class ByteFile final {
	private:
		ConstantPool m_ConstantPool;
		Structures m_Structures;
		Functions m_Functions;
		Instructions m_EntryPoint;

		ByteFileVersion m_ByteFileVersion = ByteFileVersion::Latest;
		ByteCodeVersion m_ByteCodeVersion = ByteCodeVersion::Latest;

		bool m_HasBuilder = false;

	public:
		ByteFile() noexcept = default;
		ByteFile(ByteFile&& file) noexcept;
		~ByteFile() = default;

	public:
		ByteFile& operator=(ByteFile&& file) noexcept;
		bool operator==(const ByteFile&) = delete;
		bool operator!=(const ByteFile&) = delete;

	public:
		ByteFileVersion GetByteFileVersion() const noexcept;
		void SetByteFileVersion(ByteFileVersion newVersion) noexcept;
		ByteCodeVersion GetByteCodeVersion() const noexcept;
		bool SetByteCodeVersion(ByteCodeVersion newVersion) noexcept;

		void CreatedBuilder() noexcept;

		TypeIndex GetTypeIndex(const Type* type) const noexcept;
		TypeIndex GetTypeIndex(StructureIndex structure) const noexcept;

		IntConstantIndex AddIntConstant(std::uint32_t value);
		LongConstantIndex AddLongConstant(std::uint64_t value);
		DoubleConstantIndex AddDoubleConstant(double value);
		IntConstantIndex AddIntConstantFast(std::uint32_t value);
		LongConstantIndex AddLongConstantFast(std::uint64_t value);
		DoubleConstantIndex AddDoubleConstantFast(double value);

		StructureIndex AddStructure();
		const Structure* GetStructure(TypeIndex index) const noexcept;
		Structure* GetStructure(TypeIndex index) noexcept;
		const Structure* GetStructure(StructureIndex index) const noexcept;
		Structure* GetStructure(StructureIndex index) noexcept;

		FunctionIndex AddFunction();
		FunctionIndex AddFunction(std::uint16_t arity);
		FunctionIndex AddFunction(bool hasResult);
		FunctionIndex AddFunction(std::uint16_t arity, bool hasResult);
		const Function* GetFunction(FunctionIndex index) const noexcept;
		Function* GetFunction(FunctionIndex index) noexcept;

		const Instructions* GetEntryPoint() const noexcept;
		Instructions* GetEntryPoint() noexcept;

		void Save(const std::string& path) const;
	};
}