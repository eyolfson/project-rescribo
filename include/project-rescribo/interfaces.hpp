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

#ifndef PROJECT_RESCRIBO_INTERFACES_HPP
#define PROJECT_RESCRIBO_INTERFACES_HPP

#include <cstdint>
#include <memory>
#include <vector>

namespace project_rescribo {

class ClassFile;
class Interface;

class Interfaces {
public:
	Interfaces(const uint8_t** buffer,
		   ClassFile* class_file);
	~Interfaces();

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

	ClassFile* get_class_file() const {
		return class_file;
	}
private:
	ClassFile* class_file;
	std::vector<uint16_t> interfaces;
};

}

#endif
