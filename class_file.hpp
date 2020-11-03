#ifndef PROJECT_TOTUS_CLASS_FILE_HPP
#define PROJECT_TOTUS_CLASS_FILE_HPP

#include <cstdint>
#include <memory>

#include "access.hpp"

namespace project_totus {

class Attributes;
class ConstantPool;
class Fields;
class Interfaces;
class Methods;

class ClassFile {
public:
	ClassFile(const uint8_t** buffer);
	~ClassFile();

	uint16_t get_this_class() const {
		return this_class;
	}
	uint16_t get_super_class() const {
		return super_class;
	}
	ConstantPool* get_constant_pool() {
		return constant_pool.get();
	}

	Methods* get_methods() {
		return methods.get();
	}

	uint32_t get_byte_size();
	void write_buffer(uint8_t** buffer);

private:
	uint16_t major_version;
	uint16_t minor_version;
	Access access;
	uint16_t this_class;
	uint16_t super_class;
	std::unique_ptr<ConstantPool> constant_pool;
	std::unique_ptr<Fields> fields;
	std::unique_ptr<Interfaces> interfaces;
	std::unique_ptr<Methods> methods;
	std::unique_ptr<Attributes> attributes;
};

}

#endif
