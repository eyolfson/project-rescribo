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

#include "methods.hpp"

#include "buffer.hpp"
#include "method.hpp"

#include <cassert>

using namespace project_rescribo;

Methods::Methods(const uint8_t** buffer,
                 uint16_t count,
                 ClassFile* class_file) {
	for (uint32_t i = 0; i < count; ++i) {
		methods.push_back(std::make_unique<Method>(buffer, class_file));
	}
}

Methods::~Methods() = default;

uint32_t Methods::get_byte_size() const {
	uint32_t result = 2;
	for (const auto& m : methods) {
		result += m->get_byte_size();
	}
	return result;
}

void Methods::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, methods.size());
	for (const auto& m : methods) {
		m->write_buffer(buffer);
	}
}
