#include "class_file.hpp"

#include "attributes.hpp"
#include "buffer.hpp"
#include "code.hpp"
#include "constant_pool.hpp"
#include "field.hpp"
#include "fields.hpp"
#include "method.hpp"
#include "methods.hpp"
#include "interfaces.hpp"

#include <cassert>

using namespace project_rescribo;

// https://docs.oracle.com/javase/specs/jvms/se11/html/jvms-4.html
ClassFile::ClassFile(const uint8_t** buffer) {
	assert(next_u32(buffer) == 0xCAFEBABE); // magic
	minor_version = next_u16(buffer);
	major_version = next_u16(buffer);

	uint16_t constant_pool_count = next_u16(buffer);
	constant_pool = std::make_unique<ConstantPool>(buffer,
	                                               constant_pool_count);

	access = Access(next_u16(buffer));
	this_class = next_u16(buffer);
	super_class = next_u16(buffer);

	interfaces = std::make_unique<Interfaces>(buffer,
						  this);

	uint16_t fields_count = next_u16(buffer);
	fields = std::make_unique<Fields>(buffer, fields_count, this);

	uint16_t methods_count = next_u16(buffer);
	methods = std::make_unique<Methods>(buffer, methods_count, this);

	uint16_t attributes_count = next_u16(buffer);
	attributes = std::make_unique<Attributes>(buffer,
	                                          attributes_count,
	                                          this);
}

ClassFile::~ClassFile() = default;

uint32_t ClassFile::get_byte_size() {
	uint32_t result = 0;
	result += 4; // magic
	result += 2; // minor_version
	result += 2; // major_version

	result += 2; //constant_pool_count
	result += constant_pool->get_byte_size();
	result += 2; // access
	result += 2; // this_class
	result += 2; // super_class

	result += interfaces->get_byte_size();
	result += fields->get_byte_size();
	result += methods->get_byte_size();

	result += 2; // attributes_count
	result += attributes->get_byte_size();

	return result;
}

void ClassFile::write_buffer(uint8_t** buffer) {
	uint8_t* start = *buffer;

	uint32_t magic_number = 0xCAFEBABE;
	next_u32(buffer, magic_number);

	next_u16(buffer, minor_version);
	next_u16(buffer, major_version);

	constant_pool->write_buffer(buffer);

	next_u16(buffer, access.get_flags());
	next_u16(buffer, this_class);
	next_u16(buffer, super_class);

	interfaces->write_buffer(buffer);
	fields->write_buffer(buffer);
	methods->write_buffer(buffer);
	attributes->write_buffer(buffer);

	*buffer = start;
}
