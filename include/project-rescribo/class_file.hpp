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

#ifndef PROJECT_RESCRIBO_CLASS_FILE_HPP
#define PROJECT_RESCRIBO_CLASS_FILE_HPP

#include <cstdint>
#include <memory>

#include "access.hpp"

namespace project_rescribo {

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
