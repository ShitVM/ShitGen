#pragma once

#include <cstdint>

namespace sgn {
	enum class ByteFileVersion : std::uint16_t {
		v0_1_0,
		v0_2_0,
		v0_3_0,
		v0_4_0,

		Least = v0_1_0,
		Latest = v0_4_0,
	};

	enum class ByteCodeVersion : std::uint16_t {
		v0_1_0,
		v0_2_0,
		v0_3_0,
		v0_4_0,

		Least = v0_1_0,
		Latest = v0_4_0,
	};
}