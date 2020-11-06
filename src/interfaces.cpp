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

#include "interfaces.hpp"

#include "buffer.hpp"

using namespace project_rescribo;

Interfaces::Interfaces(const uint8_t** buffer,
		       ClassFile* class_file) {
	uint16_t interfaces_count = next_u16(buffer);
	for (uint32_t i = 0; i < interfaces_count; ++i) {
		interfaces.push_back(next_u16(buffer));
	}
}

Interfaces::~Interfaces() = default;

uint32_t Interfaces::get_byte_size() const {
	return 2 + 2 * interfaces.size();
}

void Interfaces::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, interfaces.size());
	for (uint16_t interface : interfaces) {
		next_u16(buffer, interface);
	}
}
