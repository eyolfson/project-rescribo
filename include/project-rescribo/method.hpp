/*
 * Copyright 2019-2020 Jonathan Eyolfson
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 3 as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
