#pragma once

#include <sgn/Type.hpp>

#include <cstdint>

namespace sgn {
	class Constant {
	private:
		Type m_Type;

	public:
		explicit Constant(Type type) noexcept;
		Constant(const Constant&) = delete;
		virtual ~Constant() = 0;

	public:
		Constant& operator=(const Constant&) = delete;
		bool operator==(const Constant&) = delete;
		bool operator!=(const Constant&) = delete;

	public:
		Type GetType() const noexcept;
	};

	class IntConstant final : public Constant {
	public:
		std::uint32_t Value = 0;

	public:
		IntConstant() noexcept;
		IntConstant(std::uint32_t value) noexcept;
		IntConstant(const IntConstant& constant) noexcept;
		virtual ~IntConstant() override = default;

	public:
		IntConstant& operator=(std::uint32_t value) noexcept;
		IntConstant& operator=(const IntConstant& constant) noexcept;
		bool operator==(const IntConstant& constant) const noexcept;
		bool operator!=(const IntConstant& constant) const noexcept;
	};

	class LongConstant final : public Constant {
	public:
		std::uint64_t Value = 0;

	public:
		LongConstant() noexcept;
		LongConstant(std::uint64_t value) noexcept;
		LongConstant(const LongConstant& constant) noexcept;
		virtual ~LongConstant() override = default;

	public:
		LongConstant& operator=(std::uint64_t value) noexcept;
		LongConstant& operator=(const LongConstant& constant) noexcept;
		bool operator==(const LongConstant& constant) const noexcept;
		bool operator!=(const LongConstant& constant) const noexcept;
	};

	class DoubleConstant final : public Constant {
	public:
		double Value = 0;

	public:
		DoubleConstant() noexcept;
		DoubleConstant(double value) noexcept;
		DoubleConstant(const DoubleConstant& constant) noexcept;
		virtual ~DoubleConstant() override = default;

	public:
		DoubleConstant& operator=(double value) noexcept;
		DoubleConstant& operator=(const DoubleConstant& constant) noexcept;
		bool operator==(const DoubleConstant& constant) const noexcept;
		bool operator!=(const DoubleConstant& constant) const noexcept;
	};
}