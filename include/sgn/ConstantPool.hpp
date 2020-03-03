#pragma once

#include <sgn/Constant.hpp>
#include <sgn/Operand.hpp>
#include <sgn/Version.hpp>

#include <cstdint>
#include <fstream>
#include <vector>

namespace sgn {
	class ConstantPool final {
	private:
		std::vector<IntConstant> m_IntPool;
		std::vector<LongConstant> m_LongPool;
		std::vector<DoubleConstant> m_DoublePool;

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

		std::uint32_t AddIntConstant(const IntConstant& intConstant);
		std::uint32_t AddLongConstant(const LongConstant& longConstant);
		std::uint32_t AddDoubleConstant(const DoubleConstant& doubleConstant);

		std::uint32_t ContainsIntConstant(const IntConstant& intConstant) const noexcept;
		std::uint32_t ContainsLongConstant(const LongConstant& longConstant) const noexcept;
		std::uint32_t ContainsDoubleConstant(const DoubleConstant& doubleConstant) const noexcept;

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