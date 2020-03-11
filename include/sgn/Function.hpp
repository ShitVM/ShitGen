#pragma once

#include <sgn/ConstantPool.hpp>
#include <sgn/Instruction.hpp>
#include <sgn/Version.hpp>

#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>

namespace sgn {
	class Function final {
	private:
		std::uint16_t m_Arity = 0;
		bool m_HasResult = false;
		sgn::Instructions m_Instructions;

	public:
		Function() noexcept = default;
		explicit Function(std::uint16_t arity) noexcept;
		explicit Function(bool hasResult) noexcept;
		Function(std::uint16_t arity, bool hasResult) noexcept;
		Function(Function&& function) noexcept;
		~Function() = default;

	public:
		Function& operator=(Function&& function) noexcept;
		bool operator==(const Function&) = delete;
		bool operator!=(const Function&) = delete;

	public:
		void Save(std::ofstream& stream, ByteFileVersion bfVersion, ByteCodeVersion bcVersion, const ConstantPool& constantPool) const;

		std::uint16_t GetArity() const noexcept;
		bool HasResult() const noexcept;
		const sgn::Instructions& GetInstructions() const noexcept;
		sgn::Instructions& Instructions() noexcept;
	};

	using FunctionPtr = std::unique_ptr<Function>;
	using Functions = std::vector<FunctionPtr>;
}