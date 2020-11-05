#ifndef PROJECT_RESCRIBO_METHOD_HPP
#define PROJECT_RESCRIBO_METHOD_HPP

#include <cstdint>
#include <memory>

#include "access.hpp"

namespace project_rescribo {

class Attributes;
class ClassFile;
class Code;
class ConstantPool;
class ConstantPoolUtf8;

class Method {
public:
	Method(const uint8_t** buffer, ClassFile* class_file);
	Method(ClassFile* class_file,
	       Access access,
	       const char *name,
	       const char* descriptor);
	~Method();
	ClassFile* get_class_file() const {
		return class_file;
	}
	ConstantPool* get_constant_pool() const;

	uint16_t get_name_index() const {
		return name_index;
	}
	ConstantPoolUtf8* get_name_utf8() const;
	uint16_t get_descriptor_index() const {
		return descriptor_index;
	}
	ConstantPoolUtf8* get_descriptor_utf8() const;
	bool is_static() const {
		return access.is_static();
	}

	uint32_t get_byte_size() const;

	Code* get_code() {
		return code;
	}

	void write_buffer(uint8_t** buffer) const;

	bool is_name(const char* str) const;

	void print() const;
private:
	ClassFile* class_file;
	Access access;
	uint16_t name_index;
	uint16_t descriptor_index;
	std::unique_ptr<Attributes> attributes;

	Code* code;
};

}

#endif
