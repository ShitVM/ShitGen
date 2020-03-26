#pragma once
#include <sgn/Generator.hpp>

#include <svm/Memory.hpp>

namespace sgn {
	template<typename T>
	void Generator::Write(T value) {
		if constexpr (sizeof(value) > 1) {
			if (svm::GetEndian() != svm::Endian::Little) {
				value = svm::ReverseEndian(value);
			}
		}
		m_Stream.write(reinterpret_cast<const char*>(&value), sizeof(value));
	}
}