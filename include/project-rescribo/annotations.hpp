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

#ifndef PROJECT_RESCRIBO_ANNOTATIONS_HPP
#define PROJECT_RESCRIBO_ANNOTATIONS_HPP

#include <cstdint>
#include <memory>
#include <vector>

namespace project_rescribo {

class Annotation;
class Code;
class ConstantPool;
class Field;
class TypeAnnotation;
class Method;

class Annotations {
public:
	Annotations(const uint8_t** buffer, ConstantPool* constant_pool);
	~Annotations();

	std::vector<std::unique_ptr<Annotation>>& get() {
		return annotations;
	}

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

private:
	std::vector<std::unique_ptr<Annotation>> annotations;
};

class TypeAnnotations {
public:
	TypeAnnotations(const uint8_t** buffer, ConstantPool* constant_pool);
	TypeAnnotations(const uint8_t** buffer, Field* field);
	TypeAnnotations(const uint8_t** buffer, Method* method);
	TypeAnnotations(const uint8_t** buffer, Code* code);
	~TypeAnnotations();

	std::vector<std::unique_ptr<TypeAnnotation>>& get() {
		return annotations;
	}

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

private:
	std::vector<std::unique_ptr<TypeAnnotation>> annotations;
};

}

#endif
