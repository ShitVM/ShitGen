#include <sgn/Function.hpp>

#include <sgn/Memory.hpp>

#include <utility>

namespace sgn {
	Function::Function(std::uint16_t arity) noexcept
		: m_Arity(arity) {}
	Function::Function(bool hasResult) noexcept
		: m_HasResult(hasResult) {}
	Function::Function(std::uint16_t arity, bool hasResult) noexcept
		: m_Arity(arity), m_HasResult(hasResult) {}
	Function::Function(Function&& function) noexcept
		: m_Arity(function.m_Arity), m_HasResult(function.m_HasResult), m_Instructions(std::move(function.m_Instructions)) {}

	Function& Function::operator=(Function&& function) noexcept {
		m_Arity = function.m_Arity;
		m_HasResult = function.m_HasResult;
		m_Instructions = std::move(function.m_Instructions);
		return *this;
	}

	void Function::Save(std::ofstream& stream, ByteFileVersion, ByteCodeVersion bcVersion) const {
		WriteConstant(stream, m_Arity);
		WriteConstant(stream, m_HasResult);
		m_Instructions.Save(stream, bcVersion);
	}

	std::uint16_t Function::GetArity() const noexcept {
		return m_Arity;
	}
	bool Function::HasResult() const noexcept {
		return m_HasResult;
	}
	const Instructions& Function::GetInstructions() const noexcept {
		return m_Instructions;
	}
	Instructions& Function::Instructions() noexcept {
		return m_Instructions;
	}
}