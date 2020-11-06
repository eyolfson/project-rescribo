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

#include "fields.hpp"

#include "buffer.hpp"
#include "field.hpp"

#include <cassert>

using namespace project_rescribo;

Fields::Fields(const uint8_t** buffer, uint16_t count, ClassFile* class_file) {
	for (uint32_t i = 0; i < count; ++i) {
		fields.push_back(std::make_unique<Field>(buffer, class_file));
	}
}

Fields::~Fields() = default;

uint32_t Fields::get_byte_size() const {
	uint32_t result = 2;
	for (const auto& f : fields) {
		result += f->get_byte_size();
	}
	return result;
}

void Fields::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, fields.size());
	for (const auto& f : fields) {
		f->write_buffer(buffer);
	}
}
