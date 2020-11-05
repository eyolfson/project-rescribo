#include "field.hpp"

#include "attributes.hpp"
#include "buffer.hpp"
#include "class_file.hpp"
#include "constant_pool.hpp"

using namespace project_rescribo;

Field::Field(const uint8_t** buffer, ClassFile* class_file)
: class_file(class_file) {
	access = Access(next_u16(buffer));
	name_index = next_u16(buffer);
	descriptor_index = next_u16(buffer);
	uint16_t attributes_count = next_u16(buffer);
	attributes = std::make_unique<Attributes>(buffer,
	                                          attributes_count,
	                                          this);
}

Field::Field(ClassFile* class_file,
             Access access,
             const char* name,
             const char* descriptor)
: class_file(class_file), access(access) {
	ConstantPool* constant_pool = class_file->get_constant_pool();
	name_index = constant_pool->get_or_create_utf8_index(name);
	descriptor_index = constant_pool->get_or_create_utf8_index(descriptor);
	attributes = std::make_unique<Attributes>();
}

Field::~Field() = default;

uint32_t Field::get_byte_size() const {
	uint32_t result = 0;
	result += 2; // access
	result += 2; // name_index
	result += 2; // descriptor_index
	result += 2; // attributes_count
	result += attributes->get_byte_size();
	return result;
}

void Field::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, access.get_flags());
	next_u16(buffer, name_index);
	next_u16(buffer, descriptor_index);
	attributes->write_buffer(buffer);
}

ConstantPool* Field::get_constant_pool() const {
	return class_file->get_constant_pool();
}
