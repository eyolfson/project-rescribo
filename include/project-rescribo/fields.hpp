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

#ifndef PROJECT_RESCRIBO_FIELDS_HPP
#define PROJECT_RESCRIBO_FIELDS_HPP

#include <cstdint>
#include <memory>
#include <vector>

namespace project_rescribo {

class Field;
class ClassFile;

class Fields {
public:
	Fields(const uint8_t** buffer, uint16_t count, ClassFile* class_file);
	~Fields();

	void add(std::unique_ptr<Field> field) {
		fields.push_back(std::move(field));
	}

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

private:
	std::vector<std::unique_ptr<Field>> fields;
};

}

#endif
