#include <sgn/Constant.hpp>

namespace sgn {
	Constant::Constant(const Type* type) noexcept
		: m_Type(type) {}
	Constant::~Constant() {}

	const Type* Constant::GetType() const noexcept {
		return m_Type;
	}
}

namespace sgn {
	IntConstant::IntConstant() noexcept
		: Constant(IntType) {}
	IntConstant::IntConstant(std::uint32_t value) noexcept
		: Constant(IntType), Value(value) {}
	IntConstant::IntConstant(const IntConstant& constant) noexcept
		: Constant(IntType), Value(constant.Value) {}

	IntConstant& IntConstant::operator=(std::uint32_t value) noexcept {
		Value = value;
		return *this;
	}
	IntConstant& IntConstant::operator=(const IntConstant& constant) noexcept {
		Value = constant.Value;
		return *this;
	}
	bool IntConstant::operator==(const IntConstant& constant) const noexcept {
		return Value == constant.Value;
	}
	bool IntConstant::operator!=(const IntConstant& constant) const noexcept {
		return Value != constant.Value;
	}
}

namespace sgn {
	LongConstant::LongConstant() noexcept
		: Constant(LongType) {}
	LongConstant::LongConstant(std::uint64_t value) noexcept
		: Constant(LongType), Value(value) {}
	LongConstant::LongConstant(const LongConstant& constant) noexcept
		: Constant(LongType), Value(constant.Value) {}

	LongConstant& LongConstant::operator=(std::uint64_t value) noexcept {
		Value = value;
		return *this;
	}
	LongConstant& LongConstant::operator=(const LongConstant& constant) noexcept {
		Value = constant.Value;
		return *this;
	}
	bool LongConstant::operator==(const LongConstant& constant) const noexcept {
		return Value == constant.Value;
	}
	bool LongConstant::operator!=(const LongConstant& constant) const noexcept {
		return Value != constant.Value;
	}
}

namespace sgn {
	DoubleConstant::DoubleConstant() noexcept
		: Constant(DoubleType) {}
	DoubleConstant::DoubleConstant(double value) noexcept
		: Constant(DoubleType), Value(value) {}
	DoubleConstant::DoubleConstant(const DoubleConstant& constant) noexcept
		: Constant(DoubleType), Value(constant.Value) {}

	DoubleConstant& DoubleConstant::operator=(double value) noexcept {
		Value = value;
		return *this;
	}
	DoubleConstant& DoubleConstant::operator=(const DoubleConstant& constant) noexcept {
		Value = constant.Value;
		return *this;
	}
	bool DoubleConstant::operator==(const DoubleConstant& constant) const noexcept {
		return Value == constant.Value;
	}
	bool DoubleConstant::operator!=(const DoubleConstant& constant) const noexcept {
		return Value != constant.Value;
	}
}