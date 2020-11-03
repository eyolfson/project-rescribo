#include "annotation.hpp"

#include "buffer.hpp"
#include "code.hpp"
#include "field.hpp"
#include "method.hpp"

#include <cassert>

using namespace project_totus;

ElementValue::~ElementValue() {}

std::unique_ptr<ElementValue> ElementValue::make(const uint8_t** buffer,
	                                         ConstantPool* constant_pool) {
	uint8_t tag = next_u8(buffer);
	switch (tag) {
	case 'B':
	case 'C':
	case 'D':
	case 'F':
	case 'I':
	case 'J':
	case 'S':
	case 'Z':
	case 's': {
		uint16_t index = next_u16(buffer);
		return std::make_unique<ConstValueIndex>(
			tag, index, constant_pool
		);
	}
	case 'e': {
		uint16_t type_name_index = next_u16(buffer);
		uint16_t value_name_index = next_u16(buffer);
		return std::make_unique<EnumConstValue>(
			tag, type_name_index, value_name_index, constant_pool
		);
	}
	case 'c': {
		uint16_t index = next_u16(buffer);
		return std::make_unique<ClassInfoIndex>(
			tag, index, constant_pool
		);
	}
	case '@': {
		std::unique_ptr<Annotation> value
			= std::make_unique<Annotation>(
				buffer, constant_pool
			);
		return std::make_unique<AnnotationValue>(
			tag, std::move(value), constant_pool
		);
	}
	case '[': {
		std::vector<std::unique_ptr<ElementValue>> value;
		uint16_t num_values = next_u16(buffer);
		for (uint32_t i = 0; i < num_values; ++i) {
			value.push_back(
				ElementValue::make(buffer, constant_pool)
			);
		}
		return std::make_unique<ArrayValue>(
			tag, std::move(value), constant_pool
		);
	}
	default: {
		assert(false && "Unimplemented");
	}
	}
}

uint32_t AnnotationValue::get_byte_size() const {
	return 1 + value->get_byte_size();
}

void AnnotationValue::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_tag());
	value->write_buffer(buffer);
}

uint32_t ArrayValue::get_byte_size() const {
	uint32_t result = 3;
	for (const auto& v : value) {
		result += v->get_byte_size();
	}
	return result;
}

void ArrayValue::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_tag());
	next_u16(buffer, value.size());
	for (const auto& v : value) {
		v->write_buffer(buffer);
	}
}

void ConstValueIndex::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_tag());
	next_u16(buffer, index);
}

void ClassInfoIndex::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_tag());
	next_u16(buffer, index);
}

void EnumConstValue::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_tag());
	next_u16(buffer, type_name_index);
	next_u16(buffer, value_name_index);
}

ElementValuePair::ElementValuePair(const uint8_t** buffer,
                                   ConstantPool* constant_pool) {
	name_index = next_u16(buffer);
	value = ElementValue::make(buffer, constant_pool);
}

ElementValuePair::~ElementValuePair() {}

uint32_t ElementValuePair::get_byte_size() const {
	return 2 + value->get_byte_size();
}

void ElementValuePair::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, name_index);
	value->write_buffer(buffer);
}

ElementValuePairs::ElementValuePairs(const uint8_t** buffer,
                                     ConstantPool* constant_pool) {
	uint16_t num_element_value_pairs = next_u16(buffer);
	for (uint32_t i = 0; i < num_element_value_pairs; ++i) {
		element_value_pairs.push_back(
			std::make_unique<ElementValuePair>(
				buffer, constant_pool
			)
		);
	}
}

ElementValuePairs::~ElementValuePairs() {}

uint32_t ElementValuePairs::get_byte_size() const {
	uint32_t result = 2;
	for (const auto& p : element_value_pairs) {
		result += p->get_byte_size();
	}
	return result;
}

void ElementValuePairs::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, element_value_pairs.size());
	for (const auto& p : element_value_pairs) {
		p->write_buffer(buffer);
	}
}

Annotation::Annotation(const uint8_t** buffer, ConstantPool* constant_pool)
: constant_pool(constant_pool) {
	type_index = next_u16(buffer);
	element_value_pairs = std::make_unique<ElementValuePairs>(
		buffer, constant_pool
	);
}

Annotation::~Annotation() {}

uint32_t Annotation::get_byte_size() const {
	uint32_t result = 2;
	result += element_value_pairs->get_byte_size();
	return result;
}

void Annotation::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, type_index);
	element_value_pairs->write_buffer(buffer);
}

TypePath::TypePath(const uint8_t** buffer) {
	uint8_t path_length = next_u8(buffer);
	for (int i = 0; i < path_length; ++i) {
		uint8_t type_path_kind = next_u8(buffer);
		uint8_t type_argument_index = next_u8(buffer);
		entries.push_back({type_path_kind, type_argument_index});
	}
}

TypePath::~TypePath() {}

uint32_t TypePath::get_byte_size() const {
	return 1 + 2 * entries.size();
}

void TypePath::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, entries.size());
	for (const auto& e : entries) {
		next_u8(buffer, e.type_path_kind);
		next_u8(buffer, e.type_argument_index);
	}
}

TypeTarget::~TypeTarget() {}

std::unique_ptr<TypeTarget> TypeTarget::make(const uint8_t** buffer,
	                                     ConstantPool* constant_pool) {
	uint8_t type = next_u8(buffer);
	switch (type) {
	default: {
		printf("Type target: 0x%x\n", type);
		assert(false && "Unimplemented class file type target");
	}
	}
}

std::unique_ptr<TypeTarget> TypeTarget::make(const uint8_t** buffer,
	                                     Field* field) {
	uint8_t type = next_u8(buffer);
	switch (type) {
	case 0x13: {
		auto path = std::make_unique<TypePath>(buffer);
		return std::make_unique<EmptyTarget>(
			type, std::move(path)
		);
	}
	default: {
		printf("Type target: 0x%x\n", type);
		assert(false && "Unimplemented field type target");
	}
	}
}

std::unique_ptr<TypeTarget> TypeTarget::make(const uint8_t** buffer,
	                                     Method* method) {
	uint8_t type = next_u8(buffer);
	switch (type) {
	case 0x14: {
		auto path = std::make_unique<TypePath>(buffer);
		return std::make_unique<EmptyTarget>(
			type, std::move(path)
		);
	}
	case 0x16: {
		uint8_t index = next_u8(buffer);
		auto path = std::make_unique<TypePath>(buffer);
		return std::make_unique<FormalParameterTarget>(
			type, index, std::move(path)
		);
	}
	default: {
		printf("Type target: 0x%x\n", type);
		assert(false && "Unimplemented method type target");
	}
	}
}

std::unique_ptr<TypeTarget> TypeTarget::make(const uint8_t** buffer,
	                                     Code* code) {
	uint8_t type = next_u8(buffer);
	switch (type) {
	case 0x40: {
		uint16_t table_length = next_u16(buffer);
		std::vector<LocalVarTarget::Entry> entries;
		for (int i = 0; i < table_length; ++i) {
			uint16_t start_pc = next_u16(buffer);
			Instruction* start = code->get_instruction(start_pc);
			uint16_t length = next_u16(buffer);
			Instruction* end = nullptr;
			if ((start_pc + length) != code->get_next_bci()) {
				end = code->get_instruction(start_pc + length);
			}
			uint16_t index = next_u16(buffer);
			entries.push_back({start, end, index});
		}
		auto path = std::make_unique<TypePath>(buffer);
		return std::make_unique<LocalVarTarget>(
			type, code, std::move(entries), std::move(path)
		);
	}
	default: {
		printf("Type target: 0x%x\n", type);
		assert(false && "Unimplemented code type target");
	}
	}
}

uint32_t EmptyTarget::get_byte_size() const {
	return 1 + get_path()->get_byte_size();
}

void EmptyTarget::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_type());
	get_path()->write_buffer(buffer);
}

uint32_t FormalParameterTarget::get_byte_size() const {
	return 1 + 1 + get_path()->get_byte_size();
}

uint32_t LocalVarTarget::get_byte_size() const {
	return 1 + 2 + (6 * entries.size())
	       + get_path()->get_byte_size();
}

void LocalVarTarget::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_type());
	next_u16(buffer, entries.size());
	for (const auto& entry : entries) {
		next_u16(buffer, entry.start->get_bci());
		uint16_t length;
		if (entry.end) {
			length = entry.end->get_bci() - entry.start->get_bci();
		}
		else {
			length = code->get_next_bci() - entry.start->get_bci();
		}
		next_u16(buffer, length);
		next_u16(buffer, entry.index);
	}
	get_path()->write_buffer(buffer);
}

void FormalParameterTarget::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_type());
	next_u8(buffer, get_index());
	get_path()->write_buffer(buffer);
}

TypeAnnotation::TypeAnnotation(const uint8_t** buffer,
                               ConstantPool* constant_pool) {
	target = TypeTarget::make(buffer, constant_pool);
	type_index = next_u16(buffer);
	element_value_pairs = std::make_unique<ElementValuePairs>(
		buffer, constant_pool
	);
}

TypeAnnotation::TypeAnnotation(const uint8_t** buffer,
                               Field* field) {
	target = TypeTarget::make(buffer, field);
	type_index = next_u16(buffer);
	element_value_pairs = std::make_unique<ElementValuePairs>(
		buffer, field->get_constant_pool()
	);
}

TypeAnnotation::TypeAnnotation(const uint8_t** buffer,
                               Method* method) {
	target = TypeTarget::make(buffer, method);
	type_index = next_u16(buffer);
	element_value_pairs = std::make_unique<ElementValuePairs>(
		buffer, method->get_constant_pool()
	);
}

TypeAnnotation::TypeAnnotation(const uint8_t** buffer,
                               Code* code) {
	target = TypeTarget::make(buffer, code);
	type_index = next_u16(buffer);
	element_value_pairs = std::make_unique<ElementValuePairs>(
		buffer, code->get_constant_pool()
	);
}

TypeAnnotation::~TypeAnnotation() {}

uint32_t TypeAnnotation::get_byte_size() const {
	return get_target()->get_byte_size()
	       + 2
	       + get_element_value_pairs()->get_byte_size();
}

void TypeAnnotation::write_buffer(uint8_t** buffer) const {
	get_target()->write_buffer(buffer);
	next_u16(buffer, get_type_index());
	get_element_value_pairs()->write_buffer(buffer);
}
