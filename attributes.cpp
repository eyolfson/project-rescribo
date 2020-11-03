#include "attributes.hpp"

#include "buffer.hpp"

#include <cassert>

using namespace project_totus;

Attributes::Attributes(const uint8_t** buffer,
                       uint16_t count,
                       ClassFile* class_file) {
	for (uint64_t i = 0; i < count; ++i) {
		attributes.push_back(Attribute::make(buffer, class_file));
	}
}

Attributes::Attributes(const uint8_t** buffer,
                       uint16_t count,
                       Field* field) {
	for (uint64_t i = 0; i < count; ++i) {
		attributes.push_back(Attribute::make(buffer, field));
	}
}

Attributes::Attributes(const uint8_t** buffer,
                       uint16_t count,
                       Method* method) {
	for (uint64_t i = 0; i < count; ++i) {
		attributes.push_back(Attribute::make(buffer, method));
	}
}

Attributes::Attributes(const uint8_t** buffer,
                       uint16_t count,
                       Code* code) {
	for (uint64_t i = 0; i < count; ++i) {
		attributes.push_back(Attribute::make(buffer, code));
	}
}

Attributes::~Attributes() = default;

uint32_t Attributes::get_byte_size() const {
	uint32_t result = 0;
	for (const auto& a : attributes) {
		result += a->get_byte_size();
	}
	return result;
}

void Attributes::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, attributes.size());
	for (const auto& attribute : attributes) {
		attribute->write_buffer(buffer);
	}
}
