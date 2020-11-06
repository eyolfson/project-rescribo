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

#include "annotations.hpp"

#include "annotation.hpp"
#include "buffer.hpp"

using namespace project_rescribo;

Annotations::Annotations(const uint8_t** buffer,
                         ConstantPool* constant_pool) {
	uint16_t num_annotations = next_u16(buffer);
	for (uint32_t i = 0; i < num_annotations; ++i) {
		annotations.push_back(std::make_unique<Annotation>(
			buffer, constant_pool
		));
	}
}

Annotations::~Annotations() {}

uint32_t Annotations::get_byte_size() const {
	uint32_t result = 2;
	for (const auto& a : annotations) {
		result += a->get_byte_size();
	}
	return result;
}

void Annotations::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, annotations.size());
	for (const auto& a : annotations) {
		a->write_buffer(buffer);
	}
}

TypeAnnotations::TypeAnnotations(const uint8_t** buffer,
                                 ConstantPool* constant_pool) {
	uint16_t num_annotations = next_u16(buffer);
	for (uint32_t i = 0; i < num_annotations; ++i) {
		annotations.push_back(std::make_unique<TypeAnnotation>(
			buffer, constant_pool
		));
	}
}

TypeAnnotations::TypeAnnotations(const uint8_t** buffer,
                                 Field* field) {
	uint16_t num_annotations = next_u16(buffer);
	for (uint32_t i = 0; i < num_annotations; ++i) {
		annotations.push_back(std::make_unique<TypeAnnotation>(
			buffer, field
		));
	}
}

TypeAnnotations::TypeAnnotations(const uint8_t** buffer,
                                 Method* method) {
	uint16_t num_annotations = next_u16(buffer);
	for (uint32_t i = 0; i < num_annotations; ++i) {
		annotations.push_back(std::make_unique<TypeAnnotation>(
			buffer, method
		));
	}
}

TypeAnnotations::TypeAnnotations(const uint8_t** buffer,
                                 Code* code) {
	uint16_t num_annotations = next_u16(buffer);
	for (uint32_t i = 0; i < num_annotations; ++i) {
		annotations.push_back(std::make_unique<TypeAnnotation>(
			buffer, code
		));
	}
}

TypeAnnotations::~TypeAnnotations() {}

uint32_t TypeAnnotations::get_byte_size() const {
	uint32_t result = 2;
	for (const auto& a : annotations) {
		result += a->get_byte_size();
	}
	return result;
}

void TypeAnnotations::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, annotations.size());
	for (const auto& a : annotations) {
		a->write_buffer(buffer);
	}
}
