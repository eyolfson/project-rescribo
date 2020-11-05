#include "constant_pool_entry.hpp"

#include "buffer.hpp"

#include <cassert>
#include <cstring>

using namespace project_rescribo;

std::unique_ptr<ConstantPoolEntry>
ConstantPoolEntry::make(const uint8_t** buffer) {
	switch (Kind(next_u8(buffer))) {
	case Kind::Utf8: {
		uint16_t length = next_u16(buffer);
		std::vector<uint8_t> bytes;
		for (uint32_t i = 0; i < length; ++i) {
			bytes.push_back(next_u8(buffer));
		}
		return std::make_unique<ConstantPoolUtf8>(std::move(bytes));
	}
	case Kind::Integer: {
		uint32_t bytes = next_u32(buffer);
		return std::make_unique<ConstantPoolInteger>(bytes);
	}
	case Kind::Float: {
		uint32_t bytes = next_u32(buffer);
		return std::make_unique<ConstantPoolFloat>(bytes);
	}
	case Kind::Long: {
		uint64_t bytes = next_u64(buffer);
		return std::make_unique<ConstantPoolLong>(bytes);
	}
	case Kind::Double: {
		uint64_t bytes = next_u64(buffer);
		return std::make_unique<ConstantPoolDouble>(bytes);
	}
	case Kind::Class: {
		uint16_t name_index = next_u16(buffer);
		return std::make_unique<ConstantPoolClass>(name_index);
	}
	case Kind::String: {
		uint16_t string_index = next_u16(buffer);
		return std::make_unique<ConstantPoolString>(string_index);
	}
	case Kind::Fieldref: {
		uint16_t class_index = next_u16(buffer);
		uint16_t name_and_type_index = next_u16(buffer);
		return std::make_unique<ConstantPoolFieldref>(
			class_index, name_and_type_index);
	}
	case Kind::Methodref: {
		uint16_t class_index = next_u16(buffer);
		uint16_t name_and_type_index = next_u16(buffer);
		return std::make_unique<ConstantPoolMethodref>(
			class_index, name_and_type_index);
	}
	case Kind::InterfaceMethodref: {
		uint16_t class_index = next_u16(buffer);
		uint16_t name_and_type_index = next_u16(buffer);
		return std::make_unique<ConstantPoolInterfaceMethodref>(
			class_index, name_and_type_index);
	}
	case Kind::NameAndType: {
		uint16_t name_index = next_u16(buffer);
		uint16_t descriptor_index = next_u16(buffer);
		return std::make_unique<ConstantPoolNameAndType>(
			name_index, descriptor_index);
	}
	case Kind::MethodHandle: {
		uint8_t reference_kind = next_u8(buffer);
		uint16_t reference_index = next_u16(buffer);
		return std::make_unique<ConstantPoolMethodHandle>(
			reference_kind, reference_index);
	}
	case Kind::MethodType: {
		uint16_t descriptor_index = next_u16(buffer);
		return std::make_unique<ConstantPoolMethodType>(
			descriptor_index);
	}
	case Kind::Dynamic: {
		uint16_t bootstrap_method_attr_index = next_u16(buffer);
		uint16_t name_and_type_index = next_u16(buffer);
		return std::make_unique<ConstantPoolDynamic>(
			bootstrap_method_attr_index, name_and_type_index);
	}
	case Kind::InvokeDynamic: {
		uint16_t bootstrap_method_attr_index = next_u16(buffer);
		uint16_t name_and_type_index = next_u16(buffer);
		return std::make_unique<ConstantPoolInvokeDynamic>(
			bootstrap_method_attr_index, name_and_type_index);
	}
	default:
		assert(false && "Unknown constant pool tag");
	}
}

void ConstantPoolUtf8::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, bytes.size());
	for (const auto& b : bytes) {
		next_u8(buffer, b);
	}
}

void ConstantPoolInteger::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u32(buffer, bytes);
}

void ConstantPoolFloat::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u32(buffer, bytes);
}

void ConstantPoolLong::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u64(buffer, bytes);
}

void ConstantPoolDouble::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u64(buffer, bytes);
}

void ConstantPoolClass::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, name_index);
}

void ConstantPoolString::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, string_index);
}

void ConstantPoolRef::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, class_index);
	next_u16(buffer, name_and_type_index);
}

void ConstantPoolNameAndType::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, name_index);
	next_u16(buffer, descriptor_index);
}

void ConstantPoolMethodHandle::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, reference_kind);
	next_u16(buffer, reference_index);
}

void ConstantPoolMethodType::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, descriptor_index);
}

void ConstantPoolDynamic::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, bootstrap_method_attr_index);
	next_u16(buffer, name_and_type_index);
}

void ConstantPoolInvokeDynamic::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, bootstrap_method_attr_index);
	next_u16(buffer, name_and_type_index);
}

// https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.4
bool ConstantPoolUtf8::equals(const char *str) const {
	auto len = strlen(str);
	if (bytes.size() != len) {
		return false;
	}
	return strncmp(str,
	               reinterpret_cast<const char*>(bytes.data()),
	               bytes.size())
	       == 0;
}

void ConstantPoolUtf8::print() const {
	for (size_t i = 0; i < bytes.size(); ++i) {
		printf("%c", bytes.data()[i]);
	}
	printf("\n");
}
