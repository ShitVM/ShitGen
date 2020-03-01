#include <sgn/Function.hpp>

#include <sgn/Memory.hpp>

#include <utility>

namespace sgn {
	Function::Function(Function&& function) noexcept
		: Arity(function.Arity), HasResult(function.HasResult), Instructions(std::move(function.Instructions)) {}

	Function& Function::operator=(Function&& function) noexcept {
		Arity = function.Arity;
		HasResult = function.HasResult;
		Instructions = std::move(function.Instructions);
		return *this;
	}

	void Function::Save(std::ofstream& stream) const {
		WriteConstant(stream, Arity);
		WriteConstant(stream, HasResult);
		Instructions.Save(stream);
	}
}