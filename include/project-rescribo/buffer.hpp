#ifndef PROJECT_RESCRIBO_BUFFER_HPP
#define PROJECT_RESCRIBO_BUFFER_HPP

#include <cstdint>
#include <cstdio>

namespace project_rescribo {

inline uint16_t convert_big_endian_to_host_u16(const uint8_t* data) {
	return (static_cast<uint16_t>(data[1]) << 0)
	       | (static_cast<uint16_t>(data[0]) << 8);
}

inline uint32_t convert_big_endian_to_host_u32(const uint8_t* data) {
	return (static_cast<uint32_t>(data[3]) << 0)
	       | (static_cast<uint32_t>(data[2]) << 8)
	       | (static_cast<uint32_t>(data[1]) << 16)
	       | (static_cast<uint32_t>(data[0]) << 24);
}

inline uint64_t convert_big_endian_to_host_u64(const uint8_t* data) {
	return (static_cast<uint64_t>(data[7]) << 0)
	       | (static_cast<uint64_t>(data[6]) << 8)
	       | (static_cast<uint64_t>(data[5]) << 16)
	       | (static_cast<uint64_t>(data[4]) << 24)
	       | (static_cast<uint64_t>(data[3]) << 32)
	       | (static_cast<uint64_t>(data[2]) << 40)
	       | (static_cast<uint64_t>(data[1]) << 48)
	       | (static_cast<uint64_t>(data[0]) << 56);
}

inline uint16_t convert_host_to_big_endian_u16(uint16_t data) {
	return ((data >> 0) & 0xFF) << 8
	       | ((data >> 8) & 0xFF) << 0;
}

inline uint32_t convert_host_to_big_endian_u32(uint32_t data) {
	return ((data >> 0) & 0xFF) << 24
	       | ((data >> 8) & 0xFF) << 16
	       | ((data >> 16) & 0xFF) << 8
	       | ((data >> 24) & 0xFF) << 0;
}

inline uint64_t convert_host_to_big_endian_u64(uint64_t data) {
	return ((data >> 0) & 0xFF) << 56
	       | ((data >> 8) & 0xFF) << 48
	       | ((data >> 16) & 0xFF) << 40
	       | ((data >> 24) & 0xFF) << 32
	       | ((data >> 32) & 0xFF) << 24
	       | ((data >> 40) & 0xFF) << 16
	       | ((data >> 48) & 0xFF) << 8
	       | ((data >> 56) & 0xFF) << 0;
}

inline uint8_t next_u8(const uint8_t** buffer) {
	uint8_t value = **buffer;
	*buffer += 1;
	return value;
}

inline uint16_t next_u16(const uint8_t** buffer) {
	uint16_t value = convert_big_endian_to_host_u16(*buffer);
	*buffer += 2;
	return value;
}

inline uint32_t next_u32(const uint8_t** buffer) {
	uint32_t value = convert_big_endian_to_host_u32(*buffer);
	*buffer += 4;
	return value;
}

inline uint64_t next_u64(const uint8_t** buffer) {
	uint64_t value = convert_big_endian_to_host_u64(*buffer);
	*buffer += 8;
	return value;
}

inline void next_u8(uint8_t** buffer, uint8_t value) {
	**buffer = value;
	*buffer += 1;
}

inline void next_u16(uint8_t** buffer, uint16_t value) {
	value = convert_host_to_big_endian_u16(value);
	for (int i = 0; i < 2; ++i) {
		(*buffer)[i] = (value >> i*8) & 0xFF;
	}
	*buffer += 2;
}

inline void next_u32(uint8_t** buffer, uint32_t value) {
	value = convert_host_to_big_endian_u32(value);
	for (int i = 0; i < 4; ++i) {
		(*buffer)[i] = (value >> i*8) & 0xFF;
	}
	*buffer += 4;
}

inline void next_u64(uint8_t** buffer, uint64_t value) {
	value = convert_host_to_big_endian_u64(value);
	for (int i = 0; i < 8; ++i) {
		(*buffer)[i] = (value >> i*8) & 0xFF;
	}
	*buffer += 8;
}

}

#endif
