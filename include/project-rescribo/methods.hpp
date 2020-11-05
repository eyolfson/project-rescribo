#ifndef PROJECT_RESCRIBO_METHODS_HPP
#define PROJECT_RESCRIBO_METHODS_HPP

#include <cstdint>
#include <memory>
#include <vector>

namespace project_rescribo {

class ClassFile;
class Method;

class Methods {
public:
	Methods(const uint8_t** buffer, uint16_t count, ClassFile* class_file);
	~Methods();

	std::vector<std::unique_ptr<Method>>& get() {
		return methods;
	}

	void add(std::unique_ptr<Method> method) {
		methods.push_back(std::move(method));
	}

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

private:
	std::vector<std::unique_ptr<Method>> methods;
};

}

#endif
