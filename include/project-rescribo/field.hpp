#ifndef PROJECT_RESCRIBO_FIELD_HPP
#define PROJECT_RESCRIBO_FIELD_HPP

#include <cstdint>
#include <memory>

#include "access.hpp"

namespace project_rescribo {

class Attributes;
class ClassFile;
class ConstantPool;

class Field {
public:
	Field(const uint8_t** buffer, ClassFile* class_file);
	Field(ClassFile* class_file,
	      Access access,
	      const char* name,
	      const char* descriptor);
	~Field();

	ClassFile* get_class_file() const {
		return class_file;
	}
	ConstantPool* get_constant_pool() const;

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;
private:
	ClassFile* class_file;
	Access access;
	uint16_t name_index;
	uint16_t descriptor_index;
	std::unique_ptr<Attributes> attributes;
};

}

#endif
