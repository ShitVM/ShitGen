#include <sgn/ByteFile.hpp>

#include <sgn/Memory.hpp>

#include <fstream>
#include <memory>
#include <stdexcept>
#include <utility>

namespace sgn {
	ByteFile::ByteFile(ByteFile&& file) noexcept
		: m_ConstantPool(std::move(file.m_ConstantPool)), m_Functions(std::move(file.m_Functions)), m_EntryPoint(std::move(file.m_EntryPoint)),
		m_ByteFileVersion(file.m_ByteFileVersion), m_ByteCodeVersion(file.m_ByteCodeVersion), m_HasBuilder(file.m_HasBuilder) {
		file.m_ByteFileVersion = ByteFileVersion::Latest;
		file.m_ByteCodeVersion = ByteCodeVersion::Latest;

		file.m_HasBuilder = false;
	}

	ByteFile& ByteFile::operator=(ByteFile&& file) noexcept {
		m_ConstantPool = std::move(file.m_ConstantPool);
		m_Structures = std::move(file.m_Structures);
		m_Functions = std::move(file.m_Functions);
		m_EntryPoint = std::move(file.m_EntryPoint);

		m_ByteFileVersion = file.m_ByteFileVersion;
		m_ByteCodeVersion = file.m_ByteCodeVersion;

		file.m_ByteFileVersion = ByteFileVersion::Latest;
		file.m_ByteCodeVersion = ByteCodeVersion::Latest;

		file.m_HasBuilder = false;
		return *this;
	}

	ByteFileVersion ByteFile::GetByteFileVersion() const noexcept {
		return m_ByteFileVersion;
	}
	void ByteFile::SetByteFileVersion(ByteFileVersion newVersion) noexcept {
		m_ByteFileVersion = newVersion;
	}
	ByteCodeVersion ByteFile::GetByteCodeVersion() const noexcept {
		return m_ByteCodeVersion;
	}
	bool ByteFile::SetByteCodeVersion(ByteCodeVersion newVersion) noexcept {
		if (m_HasBuilder) return false;

		m_ByteCodeVersion = newVersion;
		return true;
	}

	void ByteFile::CreatedBuilder() noexcept {
		m_HasBuilder = true;
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

	StructureIndex ByteFile::AddStructure() {
		const std::uint32_t number = static_cast<std::uint32_t>(m_Structures.size() + 1);
		const std::string name = "structure" + std::to_string(number);

		m_Structures.push_back(std::make_unique<Structure>(Type(name, number)));
		return static_cast<StructureIndex>(m_Structures.size() - 1);
	}
	const Structure* ByteFile::GetStructure(StructureIndex index) const noexcept {
		return m_Structures[static_cast<std::size_t>(index)].get();
	}
	Structure* ByteFile::GetStructure(StructureIndex index) noexcept {
		return m_Structures[static_cast<std::size_t>(index)].get();
	}

	FunctionIndex ByteFile::AddFunction() {
		m_Functions.push_back(std::make_unique<Function>());
		return static_cast<FunctionIndex>(m_Functions.size() - 1);
	}
	FunctionIndex ByteFile::AddFunction(std::uint16_t arity) {
		m_Functions.push_back(std::make_unique<Function>(arity));
		return static_cast<FunctionIndex>(m_Functions.size() - 1);
	}
	FunctionIndex ByteFile::AddFunction(bool hasResult) {
		m_Functions.push_back(std::make_unique<Function>(hasResult));
		return static_cast<FunctionIndex>(m_Functions.size() - 1);
	}
	FunctionIndex ByteFile::AddFunction(std::uint16_t arity, bool hasResult) {
		m_Functions.push_back(std::make_unique<Function>(arity, hasResult));
		return static_cast<FunctionIndex>(m_Functions.size() - 1);
	}
	const Function* ByteFile::GetFunction(FunctionIndex index) const noexcept {
		return m_Functions[static_cast<std::size_t>(index)].get();
	}
	Function* ByteFile::GetFunction(FunctionIndex index) noexcept {
		return m_Functions[static_cast<std::size_t>(index)].get();
	}

	const Instructions* ByteFile::GetEntryPoint() const noexcept {
		return &m_EntryPoint;
	}
	Instructions* ByteFile::GetEntryPoint() noexcept {
		return &m_EntryPoint;
	}

	void ByteFile::Save(const std::string& path) const {
		std::ofstream stream(path, std::ofstream::binary);
		if (!stream) throw std::runtime_error("Failed to open the file.");

		// Header
		static constexpr std::uint8_t magicNumber[] = { 0x74, 0x68, 0x74, 0x68 };

		stream.write(reinterpret_cast<const char*>(magicNumber), sizeof(magicNumber));
		WriteConstant(stream, m_ByteFileVersion);
		WriteConstant(stream, m_ByteCodeVersion);

		// Constant Pool
		m_ConstantPool.Save(stream, m_ByteFileVersion);

		// Structures
		if (m_ByteFileVersion >= ByteFileVersion::v0_2_0) {
			WriteConstant(stream, static_cast<std::uint32_t>(m_Structures.size()));
			for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(m_Structures.size()); ++i) {
				m_Structures[i]->Save(stream);
			}
		}

		// Functions
		WriteConstant(stream, static_cast<std::uint32_t>(m_Functions.size()));
		for (std::uint32_t i = 0; i < static_cast<std::uint32_t>(m_Functions.size()); ++i) {
			m_Functions[i]->Save(stream, m_ByteFileVersion, m_ByteCodeVersion, m_ConstantPool);
		}

		// Entry Point
		m_EntryPoint.Save(stream, m_ByteCodeVersion, m_ConstantPool);
	}
}