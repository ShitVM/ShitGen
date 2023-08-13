#pragma once

#include <sgn/ByteFile.hpp>
#include <sgn/ConstantPool.hpp>
#include <sgn/Function.hpp>
#include <sgn/Instruction.hpp>
#include <sgn/Structure.hpp>
#include <svm/core/ConstantPool.hpp>
#include <svm/core/Parser.hpp>

#include <cstdint>
#include <fstream>
#include <string>

namespace sgn {
	class Generator final {
	private:
		const ByteFile& m_ByteFile;
		std::ofstream m_Stream;

	public:
		Generator(const ByteFile& byteFile) noexcept;
		Generator(const Generator&) = delete;
		~Generator() = default;

	public:
		Generator& operator=(const Generator&) = delete;
		bool operator==(const Generator&) = delete;
		bool operator!=(const Generator&) = delete;

	public:
		void Generate(const std::string& path);

	private:
		template<typename T>
		void Write(T value);
		void Write(const std::string& value);

		void Generate(const svm::Mappings& mappings);
		void Generate(const svm::core::ConstantPool& constantPool);
		void Generate(const Structures& structures);
		void Generate(const Functions& functions);
		void Generate(const Instructions& instructions);

		std::uint32_t ConvertOperand(std::uint32_t operand, std::uint8_t operandIndex) noexcept;
	};
}

#include "detail/impl/Generator.hpp"