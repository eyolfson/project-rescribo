#ifndef PROJECT_TOTUS_FIELDS_HPP
#define PROJECT_TOTUS_FIELDS_HPP

#include <cstdint>
#include <memory>
#include <vector>

namespace project_totus {

class Field;
class ClassFile;

class Fields {
public:
	Fields(const uint8_t** buffer, uint16_t count, ClassFile* class_file);
	~Fields();

	void add(std::unique_ptr<Field> field) {
		fields.push_back(std::move(field));
	}

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

private:
	std::vector<std::unique_ptr<Field>> fields;
};

}

#endif
