#pragma once
#include <sgn/Operand.hpp>

namespace sgn {
	template<typename T>
	constexpr std::uint8_t GetOperandIndex() noexcept {
		return static_cast<std::uint8_t>(T::OperandIndex);
	}
}