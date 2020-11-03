#include "constant_pool.hpp"

#include "buffer.hpp"
#include "casting.hpp"

#include <classfile_constants.h>

#include <cassert>
#include <cstring>

using namespace project_totus;

ConstantPool::ConstantPool(const uint8_t** buffer, uint16_t count) {
	for (uint32_t index = 1; index < count; ++index) {
		entries.push_back(ConstantPoolEntry::make(buffer));
		if (entries.back()->is_8_byte()) {
			entries.emplace_back();
			++index;
		}
	}
}

ConstantPool::~ConstantPool() = default;

ConstantPoolEntry* ConstantPool::get_entry(uint16_t index) const {
	assert(index > 0 && index <= entries.size());
	return entries[index - 1].get();
}

uint32_t ConstantPool::get_byte_size() const {
	uint32_t result = 0;
	for (const auto& entry : entries) {
		if (entry != nullptr)
			result += entry->get_byte_size();
	}
	return result;
}

void ConstantPool::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, entries.size() + 1); // CP starts at 1
	for (const auto& entry : entries) {
		if (!entry) {
			continue;
		}
		entry->write_buffer(buffer);
	}
}

uint16_t ConstantPool::get_or_create_utf8_index(const char* str) {
	for (uint16_t i = 1; i <= entries.size(); ++i) {
		auto entry = get_entry(i);
		if (!entry) {
			continue;
		}
		ConstantPoolUtf8* utf8_entry
			= dyn_cast<ConstantPoolUtf8>(entry);
		if (!utf8_entry) {
			continue;
		}
		if (utf8_entry->equals(str)) {
			return i;
		}
	}
	std::vector<uint8_t> bytes;
	size_t length = strlen(str);
	assert(length <= UINT16_MAX);
	for (size_t i = 0; i < length; ++i) {
		bytes.push_back(str[i]);
	}
	entries.push_back(
		std::make_unique<ConstantPoolUtf8>(std::move(bytes))
	);
	return entries.size();
}

uint16_t ConstantPool::get_or_create_name_and_type_index(uint16_t name_index,
	                                                 uint16_t type_index) {
	for (uint16_t i = 1; i <= entries.size(); ++i) {
		auto entry = get_entry(i);
		if (!entry) {
			continue;
		}
		ConstantPoolNameAndType* name_and_type_entry
			= dyn_cast<ConstantPoolNameAndType>(entry);
		if (!name_and_type_entry) {
			continue;
		}
		if (name_and_type_entry->get_name_index() == name_index
		    && name_and_type_entry->get_descriptor_index()
		       == type_index) {
			return i;
		}
	}
	entries.push_back(
		std::make_unique<ConstantPoolNameAndType>(name_index,
		                                          type_index)
	);
	return entries.size();
}

uint16_t ConstantPool::get_or_create_class_index(uint16_t name_index) {
	for (uint16_t i = 1; i <= entries.size(); ++i) {
		auto entry = get_entry(i);
		if (!entry) {
			continue;
		}
		ConstantPoolClass* class_entry
			= dyn_cast<ConstantPoolClass>(entry);
		if (!class_entry) {
			continue;
		}
		if (class_entry->get_name_index() == name_index) {
			return i;
		}
	}
	entries.push_back(
		std::make_unique<ConstantPoolClass>(name_index)
	);
	return entries.size();
}

uint16_t ConstantPool::get_or_create_string_index(uint16_t index) {
	for (uint16_t i = 1; i <= entries.size(); ++i) {
		auto entry = get_entry(i);
		if (!entry) {
			continue;
		}
		ConstantPoolString* string_entry
			= dyn_cast<ConstantPoolString>(entry);
		if (!string_entry) {
			continue;
		}
		if (string_entry->get_string_index() == index) {
			return i;
		}
	}
	entries.push_back(
		std::make_unique<ConstantPoolString>(index)
	);
	return entries.size();
}

uint16_t ConstantPool::get_or_create_fieldref_index(
	uint16_t class_index,
	uint16_t name_and_type_index) {
	for (uint16_t i = 1; i <= entries.size(); ++i) {
		auto entry = get_entry(i);
		if (!entry) {
			continue;
		}
		ConstantPoolFieldref* fieldref_entry
			= dyn_cast<ConstantPoolFieldref>(entry);
		if (!fieldref_entry) {
			continue;
		}
		if (fieldref_entry->get_class_index() == class_index
		    && fieldref_entry->get_name_and_type_index()
		       == name_and_type_index) {
			return i;
		}
	}
	entries.push_back(
		std::make_unique<ConstantPoolFieldref>(class_index,
		                                        name_and_type_index)
	);
	return entries.size();
}

uint16_t ConstantPool::get_or_create_fieldref_index(
	uint16_t class_index,
	const char* field_name,
	const char* field_descriptor) {
	uint16_t field_descriptor_index = get_or_create_utf8_index(
		field_descriptor
	);
	uint16_t field_name_index = get_or_create_utf8_index(field_name);
	uint16_t field_name_and_type_index = get_or_create_name_and_type_index(
		field_name_index, field_descriptor_index
	);
	uint16_t fieldref_index = get_or_create_fieldref_index(
		class_index, field_name_and_type_index
	);
	return fieldref_index;
}

uint16_t ConstantPool::get_or_create_methodref_index(
	uint16_t class_index,
	uint16_t name_and_type_index) {
	for (uint16_t i = 1; i <= entries.size(); ++i) {
		auto entry = get_entry(i);
		if (!entry) {
			continue;
		}
		ConstantPoolMethodref* methodref_entry
			= dyn_cast<ConstantPoolMethodref>(entry);
		if (!methodref_entry) {
			continue;
		}
		if (methodref_entry->get_class_index() == class_index
		    && methodref_entry->get_name_and_type_index()
		       == name_and_type_index) {
			return i;
		}
	}
	entries.push_back(
		std::make_unique<ConstantPoolMethodref>(class_index,
		                                        name_and_type_index)
	);
	return entries.size();
}

uint16_t ConstantPool::get_or_create_methodref_index(
	const char* class_name,
	const char* method_name,
	const char* method_descriptor) {
	uint16_t method_descriptor_index = get_or_create_utf8_index(
		method_descriptor
	);
	uint16_t method_name_index = get_or_create_utf8_index(method_name);
	uint16_t method_name_and_type_index = get_or_create_name_and_type_index(
		method_name_index, method_descriptor_index
	);
	uint16_t class_name_index = get_or_create_utf8_index(class_name);
	uint16_t class_index = get_or_create_class_index(class_name_index);
	uint16_t methodref_index = get_or_create_methodref_index(
		class_index, method_name_and_type_index
	);
	return methodref_index;
}
