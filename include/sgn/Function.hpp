#pragma once

#include <sgn/Instruction.hpp>
#include <sgn/Version.hpp>

#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>

namespace sgn {
	class Function final {
	public:
		std::uint16_t Arity = 0;
		bool HasResult = false;
		sgn::Instructions Instructions;

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
		void Save(std::ofstream& stream, ByteFileVersion bfVersion, ByteCodeVersion bcVersion) const;
	};

	using FunctionPtr = std::unique_ptr<Function>;
	using Functions = std::vector<FunctionPtr>;
}