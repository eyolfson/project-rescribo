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

#ifndef PROJECT_RESCRIBO_CONSTANT_POOL_HPP
#define PROJECT_RESCRIBO_CONSTANT_POOL_HPP

#include "constant_pool_entry.hpp"

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

namespace project_rescribo {

class ConstantPoolEntry;

class ConstantPool {
public:
	ConstantPool(const uint8_t** buffer, uint16_t count);
	~ConstantPool();
	uint32_t get_byte_size() const;

	ConstantPoolEntry* get_entry(uint16_t index) const;
	uint32_t get_size() const {
		return entries.size();
	}

	uint16_t get_or_create_utf8_index(const char* str);
	uint16_t get_or_create_name_and_type_index(uint16_t name_index,
	                                           uint16_t type_index);
	uint16_t get_or_create_class_index(uint16_t name_index);
	uint16_t get_or_create_string_index(uint16_t index);
	uint16_t get_or_create_fieldref_index(uint16_t class_index,
	                                      uint16_t name_and_type_index);
	uint16_t get_or_create_fieldref_index(uint16_t class_index,
	                                      const char* field_name,
	                                      const char* field_descriptor);
	uint16_t get_or_create_methodref_index(uint16_t class_index,
	                                       uint16_t name_and_type_index);
	uint16_t get_or_create_methodref_index(const char* class_name,
	                                       const char* method_name,
	                                       const char* method_descriptor);

	void write_buffer(uint8_t** buffer) const;
private:
	std::vector<std::unique_ptr<ConstantPoolEntry>> entries;
};

}

#endif
