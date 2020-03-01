#include <sgn/Function.hpp>

namespace sgn {
	Function::Function(Function&& function) noexcept
		: Arity(function.Arity), HasResult(function.HasResult), Instructions(std::move(function.Instructions)) {}

	Function& Function::operator=(Function&& function) noexcept {
		Arity = function.Arity;
		HasResult = function.HasResult;
		Instructions = std::move(function.Instructions);
		return *this;
	}
}