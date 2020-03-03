#include <sgn/Function.hpp>

#include <sgn/Memory.hpp>

#include <utility>

namespace sgn {
	Function::Function(std::uint16_t arity) noexcept
		: Arity(arity) {}
	Function::Function(bool hasResult) noexcept
		: HasResult(hasResult) {}
	Function::Function(std::uint16_t arity, bool hasResult) noexcept
		: Arity(arity), HasResult(hasResult) {}
	Function::Function(Function&& function) noexcept
		: Arity(function.Arity), HasResult(function.HasResult), Instructions(std::move(function.Instructions)) {}

	Function& Function::operator=(Function&& function) noexcept {
		Arity = function.Arity;
		HasResult = function.HasResult;
		Instructions = std::move(function.Instructions);
		return *this;
	}

	void Function::Save(std::ofstream& stream, ByteFileVersion, ByteCodeVersion bcVersion) const {
		WriteConstant(stream, Arity);
		WriteConstant(stream, HasResult);
		Instructions.Save(stream, bcVersion);
	}
}