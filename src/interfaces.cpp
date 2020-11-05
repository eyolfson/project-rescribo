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
