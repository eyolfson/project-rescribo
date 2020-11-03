#ifndef PROJECT_TOTUS_ATTRIBUTES_HPP
#define PROJECT_TOTUS_ATTRIBUTES_HPP

#include <cstdint>
#include <memory>
#include <vector>

#include "attribute.hpp"

namespace project_totus {

class ClassFile;
class Code;
class Field;
class Method;

class Attributes {
public:
	Attributes(const uint8_t** buffer, uint16_t count, ClassFile* class_file);
	Attributes(const uint8_t** buffer, uint16_t count, Field* field);
	Attributes(const uint8_t** buffer, uint16_t count, Method* method);
	Attributes(const uint8_t** buffer, uint16_t count, Code* code);
	Attributes() {}
	~Attributes();

	std::vector<std::unique_ptr<Attribute>>& get() {
		return attributes;
	}
	void add(std::unique_ptr<Attribute> attribute) {
		attributes.push_back(std::move(attribute));
	}

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

private:
	std::vector<std::unique_ptr<Attribute>> attributes;
};

}

#endif
