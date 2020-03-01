#pragma once

#include <sgn/Instruction.hpp>

#include <cstdint>
#include <fstream>
#include <vector>

namespace sgn {
	class Function final {
	public:
		std::uint16_t Arity = 0;
		bool HasResult = false;
		sgn::Instructions Instructions;

	public:
		Function() noexcept = default;
		Function(Function&& function) noexcept;
		~Function() = default;

	public:
		Function& operator=(Function&& function) noexcept;
		bool operator==(const Function&) = delete;
		bool operator!=(const Function&) = delete;

	public:
		void Save(std::ofstream& stream) const;
	};

	using Functions = std::vector<Function>;
}