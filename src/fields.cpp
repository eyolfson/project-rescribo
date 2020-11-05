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
