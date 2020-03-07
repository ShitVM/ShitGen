#pragma once

#include <sgn/Operand.hpp>
#include <sgn/Version.hpp>

#include <cstdint>
#include <fstream>
#include <vector>

namespace sgn {
	class ConstantPool final {
	private:
		std::vector<std::uint32_t> m_IntPool;
		std::vector<std::uint64_t> m_LongPool;
		std::vector<double> m_DoublePool;

	public:
		ConstantPool() noexcept = default;
		ConstantPool(ConstantPool&& pool) noexcept;
		~ConstantPool() = default;

	public:
		ConstantPool& operator=(ConstantPool&& pool) noexcept;
		bool operator==(const ConstantPool&) = delete;
		bool operator!=(const ConstantPool&) = delete;

	public:
		void Clear() noexcept;
		bool IsEmpty() const noexcept;

		void Save(std::ofstream& stream, ByteFileVersion bfVersion) const;

		std::uint32_t AddIntConstant(std::uint32_t intConstant);
		std::uint32_t AddLongConstant(std::uint64_t longConstant);
		std::uint32_t AddDoubleConstant(double doubleConstant);

		std::uint32_t ContainsIntConstant(std::uint32_t intConstant) const noexcept;
		std::uint32_t ContainsLongConstant(std::uint64_t longConstant) const noexcept;
		std::uint32_t ContainsDoubleConstant(double doubleConstant) const noexcept;

		std::uint32_t TransformRealIndex(IntConstantIndex index) const noexcept;
		std::uint32_t TransformRealIndex(LongConstantIndex index) const noexcept;
		std::uint32_t TransformRealIndex(DoubleConstantIndex index) const noexcept;

	private:
		std::uint32_t GetIntConstantOffset() const noexcept;
		std::uint32_t GetLongConstantOffset() const noexcept;
		std::uint32_t GetDoubleConstantOffset() const noexcept;
		std::uint32_t GetIntConstantCount() const noexcept;
		std::uint32_t GetLongConstantCount() const noexcept;
		std::uint32_t GetDoubleConstantCount() const noexcept;
	};
}