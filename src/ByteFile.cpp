#include <sgn/ByteFile.hpp>

namespace sgn {
	ByteFile::ByteFile(ByteFile&& file) noexcept
		: m_ConstantPool(std::move(file.m_ConstantPool)), m_Functions(std::move(file.m_Functions)), m_EntryPoint(std::move(file.m_EntryPoint)) {}

	ByteFile& ByteFile::operator=(ByteFile&& file) noexcept {
		m_ConstantPool = std::move(file.m_ConstantPool);
		m_Functions = std::move(file.m_Functions);
		m_EntryPoint = std::move(file.m_EntryPoint);
		return *this;
	}

	IntConstantIndex ByteFile::AddIntConstant(std::uint32_t value) {
		if (const auto dis = m_ConstantPool.ContainsIntConstant(value); dis) {
			return static_cast<IntConstantIndex>(dis - 1);
		} else return AddIntConstantFast(value);
	}
	LongConstantIndex ByteFile::AddLongConstant(std::uint64_t value) {
		if (const auto dis = m_ConstantPool.ContainsLongConstant(value); dis) {
			return static_cast<LongConstantIndex>(dis - 1);
		} else return AddLongConstantFast(value);
	}
	DoubleConstantIndex ByteFile::AddDoubleConstant(double value) {
		if (const auto dis = m_ConstantPool.ContainsDoubleConstant(value); dis) {
			return static_cast<DoubleConstantIndex>(dis - 1);
		} else return AddDoubleConstantFast(value);
	}
	IntConstantIndex ByteFile::AddIntConstantFast(std::uint32_t value) {
		return static_cast<IntConstantIndex>(m_ConstantPool.AddIntConstant(value));
	}
	LongConstantIndex ByteFile::AddLongConstantFast(std::uint64_t value) {
		return static_cast<LongConstantIndex>(m_ConstantPool.AddLongConstant(value));
	}
	DoubleConstantIndex ByteFile::AddDoubleConstantFast(double value) {
		return static_cast<DoubleConstantIndex>(m_ConstantPool.AddDoubleConstant(value));
	}

	FunctionIndex ByteFile::AddFunction() {
		m_Functions.emplace_back();
		return static_cast<FunctionIndex>(m_Functions.size() - 1);
	}
	FunctionIndex ByteFile::AddFunction(std::uint16_t arity) {
		m_Functions.emplace_back();
		m_Functions.back().Arity = arity;
		return static_cast<FunctionIndex>(m_Functions.size() - 1);
	}
	FunctionIndex ByteFile::AddFunction(bool hasResult) {
		m_Functions.emplace_back();
		m_Functions.back().HasResult = hasResult;
		return static_cast<FunctionIndex>(m_Functions.size() - 1);
	}
	FunctionIndex ByteFile::AddFunction(std::uint16_t arity, bool hasResult) {
		m_Functions.emplace_back();
		m_Functions.back().Arity = arity;
		m_Functions.back().HasResult = hasResult;
		return static_cast<FunctionIndex>(m_Functions.size() - 1);
	}

	const Instructions* ByteFile::GetEntryPoint() const noexcept {
		return &m_EntryPoint;
	}
	Instructions* ByteFile::GetEntryPoint() noexcept {
		return &m_EntryPoint;
	}
}