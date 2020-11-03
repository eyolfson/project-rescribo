#include "methods.hpp"

#include "buffer.hpp"
#include "method.hpp"

#include <cassert>

using namespace project_totus;

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
