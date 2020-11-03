#include "method.hpp"

#include "attributes.hpp"
#include "buffer.hpp"
#include "casting.hpp"
#include "class_file.hpp"
#include "code.hpp"
#include "constant_pool.hpp"

#include <cassert>

using namespace project_totus;

Method::Method(const uint8_t** buffer, ClassFile* class_file)
: class_file(class_file), code(nullptr) {
	access = Access(next_u16(buffer));
	name_index = next_u16(buffer);
	descriptor_index = next_u16(buffer);
	uint16_t attributes_count = next_u16(buffer);
	attributes = std::make_unique<Attributes>(buffer,
	                                          attributes_count,
	                                          this);

	for (auto&& attribute : attributes->get()) {
		if (Code* c = dyn_cast<Code>(attribute.get())) {
			assert(code == nullptr);
			code = c;
		}
	}
}

Method::Method(ClassFile* class_file,
               Access access,
               const char *name,
	       const char* descriptor)
: class_file(class_file), access(access), code(nullptr) {
	ConstantPool* constant_pool = class_file->get_constant_pool();
	name_index = constant_pool->get_or_create_utf8_index(name);
	descriptor_index = constant_pool->get_or_create_utf8_index(descriptor);
	attributes = std::make_unique<Attributes>();
	auto code_attribute = std::make_unique<Code>(this);
	code = code_attribute.get();
	attributes->add(std::move(code_attribute));
}

Method::~Method() = default;

ConstantPool* Method::get_constant_pool() const {
	return class_file->get_constant_pool();
}

uint32_t Method::get_byte_size() const {
	uint32_t result = 0;
	result += 2; // access
	result += 2; // name_index
	result += 2; // descriptor_index
	result += 2; // attributes_count
	result += attributes->get_byte_size();
	return result;
}

void Method::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, access.get_flags());
	next_u16(buffer, name_index);
	next_u16(buffer, descriptor_index);
	attributes->write_buffer(buffer);
}

ConstantPoolUtf8* Method::get_name_utf8() const {
	return cast<ConstantPoolUtf8>(
		get_constant_pool()->get_entry(name_index)
	);
}

ConstantPoolUtf8* Method::get_descriptor_utf8() const {
	return cast<ConstantPoolUtf8>(
		get_constant_pool()->get_entry(descriptor_index)
	);
}

bool Method::is_name(const char* str) const {
	return get_name_utf8()->equals(str);
}

void Method::print() const {
	get_name_utf8()->print();
}
