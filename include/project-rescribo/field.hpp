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
