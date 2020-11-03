#ifndef PROJECT_TOTUS_INTERFACES_HPP
#define PROJECT_TOTUS_INTERFACES_HPP

#include <cstdint>
#include <memory>
#include <vector>

namespace project_totus {

class ClassFile;
class Interface;

class Interfaces {
public:
	Interfaces(const uint8_t** buffer,
		   ClassFile* class_file);
	~Interfaces();

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

	ClassFile* get_class_file() const {
		return class_file;
	}
private:
	ClassFile* class_file;
	std::vector<uint16_t> interfaces;
};

}

#endif
