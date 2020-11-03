#ifndef PROJECT_TOTUS_CONSTANT_POOL_ENTRY_HPP
#define PROJECT_TOTUS_CONSTANT_POOL_ENTRY_HPP

#include <cstdint>
#include <memory>
#include <vector>

namespace project_totus {

class ConstantPoolEntry {
public:
	enum class Kind : uint8_t{
		Utf8 = 1,
		Integer = 3,
		Float = 4,
		Long = 5,
		Double = 6,
		Class = 7,
		String = 8,
		Fieldref = 9,
		Methodref = 10,
		InterfaceMethodref = 11,
		NameAndType = 12,
		MethodHandle = 15,
		MethodType = 16,
		Dynamic = 17,
		InvokeDynamic = 18
	};
	ConstantPoolEntry(Kind kind) : kind(kind) {}
	virtual ~ConstantPoolEntry() {}
	Kind get_kind() const {
		return kind;
	}

	bool is_8_byte() const {
		return kind == Kind::Long || kind == Kind::Double;
	}

	virtual uint32_t get_byte_size() const = 0;
	virtual void write_buffer(uint8_t** buffer) const = 0;

	static std::unique_ptr<ConstantPoolEntry> make(const uint8_t** buffer);
private:
	const Kind kind;
};

class ConstantPoolUtf8 : public ConstantPoolEntry {
public:
	ConstantPoolUtf8(std::vector<uint8_t> bytes)
		: ConstantPoolEntry(Kind::Utf8), bytes(bytes) {}
	bool equals(const char *str) const;

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::Utf8;
	}

	const uint8_t* get_data() const {
		return bytes.data();
	}
	uint16_t get_length() const {
		return static_cast<uint16_t>(bytes.size());
	}

	virtual uint32_t get_byte_size() const { return 1 + 2 + bytes.size(); }
	virtual void write_buffer(uint8_t** buffer) const;

	void print() const;
private:
	std::vector<uint8_t> bytes;
};

class ConstantPoolInteger : public ConstantPoolEntry {
public:
	ConstantPoolInteger(uint32_t bytes)
		: ConstantPoolEntry(Kind::Integer), bytes(bytes) {}
	uint32_t get_bytes() const {
		return bytes;
	}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::Integer;
	}

	// tag(1) + bytes(4)
	virtual uint32_t get_byte_size() const { return 5; }
	virtual void write_buffer(uint8_t** buffer) const;
private:
	uint32_t bytes;
};

class ConstantPoolFloat : public ConstantPoolEntry {
public:
	ConstantPoolFloat(uint32_t bytes)
		: ConstantPoolEntry(Kind::Float), bytes(bytes) {}
	uint32_t get_bytes() const {
		return bytes;
	}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::Float;
	}

	// tag(1) + bytes(4)
	virtual uint32_t get_byte_size() const { return 5; }
	virtual void write_buffer(uint8_t** buffer) const;
private:
	uint32_t bytes;
};

class ConstantPoolLong : public ConstantPoolEntry {
public:
	ConstantPoolLong(uint64_t bytes)
		: ConstantPoolEntry(Kind::Long), bytes(bytes) {}
	uint64_t get_bytes() const {
		return bytes;
	}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::Long;
	}

	// tag(1) + high(4) + low(4)
	virtual uint32_t get_byte_size() const { return 9; }
	virtual void write_buffer(uint8_t** buffer) const;
private:
	uint64_t bytes;
};

class ConstantPoolDouble : public ConstantPoolEntry {
public:
	ConstantPoolDouble(uint64_t bytes)
		: ConstantPoolEntry(Kind::Double), bytes(bytes) {}
	uint64_t get_bytes() const {
		return bytes;
	}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::Double;
	}

	// tag(1) + high(4) + low(4)
	virtual uint32_t get_byte_size() const { return 9; }
	virtual void write_buffer(uint8_t** buffer) const;
private:
	uint64_t bytes;
};

class ConstantPoolClass : public ConstantPoolEntry {
public:
	ConstantPoolClass(uint16_t name_index)
		: ConstantPoolEntry(Kind::Class), name_index(name_index) {}
	uint16_t get_name_index() const {
		return name_index;
	}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::Class;
	}

	// tag(1) + name_index(2)
	virtual uint32_t get_byte_size() const { return 3; }
	virtual void write_buffer(uint8_t** buffer) const;
private:
	uint16_t name_index;
};

class ConstantPoolString : public ConstantPoolEntry {
public:
	ConstantPoolString(uint16_t string_index)
		: ConstantPoolEntry(Kind::String), string_index(string_index) {}
	uint16_t get_string_index() const {
		return string_index;
	}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::String;
	}

	// tag(1) + str_index(2)
	virtual uint32_t get_byte_size() const { return 3; }
	virtual void write_buffer(uint8_t** buffer) const;
private:
	uint16_t string_index;
};

class ConstantPoolRef : public ConstantPoolEntry {
public:
	ConstantPoolRef(Kind kind, uint16_t class_index,
	                uint16_t name_and_type_index)
	: ConstantPoolEntry(kind), class_index(class_index),
	  name_and_type_index(name_and_type_index) {}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::Fieldref
		       || entry->get_kind() == Kind::Methodref
		       || entry->get_kind() == Kind::InterfaceMethodref;
	}

	virtual uint32_t get_byte_size() const override { return 5; }
	virtual void write_buffer(uint8_t** buffer) const override;

	uint16_t get_class_index() const {
		return class_index;
	}
	uint16_t get_name_and_type_index() const {
		return name_and_type_index;
	}

private:
	uint16_t class_index;
	uint16_t name_and_type_index;
};

class ConstantPoolFieldref : public ConstantPoolRef {
public:
	ConstantPoolFieldref(uint16_t class_index, uint16_t name_and_type_index)
	: ConstantPoolRef(Kind::Fieldref, class_index, name_and_type_index) {}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::Fieldref;
	}
};

class ConstantPoolMethodref : public ConstantPoolRef {
public:
	ConstantPoolMethodref(uint16_t class_index,
	                      uint16_t name_and_type_index)
	: ConstantPoolRef(Kind::Methodref, class_index, name_and_type_index) {}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::Methodref;
	}
};

class ConstantPoolInterfaceMethodref : public ConstantPoolRef {
public:
	ConstantPoolInterfaceMethodref(uint16_t class_index,
	                               uint16_t name_and_type_index)
	: ConstantPoolRef(Kind::InterfaceMethodref, class_index,
	  name_and_type_index) {}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::InterfaceMethodref;
	}
};

class ConstantPoolNameAndType : public ConstantPoolEntry {
public:
	ConstantPoolNameAndType(uint16_t name_index, uint16_t descriptor_index)
		: ConstantPoolEntry(Kind::NameAndType), name_index(name_index),
		  descriptor_index(descriptor_index) {}
	uint16_t get_name_index() const {
		return name_index;
	}
	uint16_t get_descriptor_index() const {
		return descriptor_index;
	}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::NameAndType;
	}

	// tag(1) + name_index(2) + desc_index(2)
	virtual uint32_t get_byte_size() const { return 5; }
	virtual void write_buffer(uint8_t** buffer) const;
private:
	uint16_t name_index;
	uint16_t descriptor_index;
};

class ConstantPoolMethodHandle : public ConstantPoolEntry {
public:
	ConstantPoolMethodHandle(uint8_t reference_kind,
	                         uint16_t reference_index)
		: ConstantPoolEntry(Kind::MethodHandle),
		  reference_kind(reference_kind),
		  reference_index(reference_index) {}
	uint8_t get_reference_kind() const {
		return reference_kind;
	}
	uint16_t get_reference_index() const {
		return reference_index;
	}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::MethodHandle;
	}

	// tag(1) + ref_kind(1) + ref_index(2)
	virtual uint32_t get_byte_size() const { return 4; }
	virtual void write_buffer(uint8_t** buffer) const;
private:
	uint8_t reference_kind;
	uint16_t reference_index;
};

class ConstantPoolMethodType : public ConstantPoolEntry {
public:
	ConstantPoolMethodType(uint16_t descriptor_index)
		: ConstantPoolEntry(Kind::MethodType),
		  descriptor_index(descriptor_index) {}
	uint16_t get_descriptor_index() const {
		return descriptor_index;
	}


	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::MethodType;
	}

	// tag(1) + desc_index(2)
	virtual uint32_t get_byte_size() const { return 3; }
	virtual void write_buffer(uint8_t** buffer) const;
private:
	uint16_t descriptor_index;
};

class ConstantPoolDynamic : public ConstantPoolEntry {
public:
	ConstantPoolDynamic(uint16_t bootstrap_method_attr_index,
	                    uint16_t name_and_type_index)
		: ConstantPoolEntry(Kind::Dynamic),
		  bootstrap_method_attr_index(bootstrap_method_attr_index),
		  name_and_type_index(name_and_type_index) {}
	uint16_t get_bootstrap_method_attr_index() const {
		return bootstrap_method_attr_index;
	}
	uint16_t get_name_and_type_index() const {
		return name_and_type_index;
	}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::Dynamic;
	}

	// tag(1) + bootstrap_method_attr_index(2) + name_and_type_index(2)
	virtual uint32_t get_byte_size() const { return 5; }
	virtual void write_buffer(uint8_t** buffer) const;
private:
	uint16_t bootstrap_method_attr_index;
	uint16_t name_and_type_index;
};

class ConstantPoolInvokeDynamic : public ConstantPoolEntry {
public:
	ConstantPoolInvokeDynamic(uint16_t bootstrap_method_attr_index,
	                          uint16_t name_and_type_index)
		: ConstantPoolEntry(Kind::InvokeDynamic),
		  bootstrap_method_attr_index(bootstrap_method_attr_index),
		  name_and_type_index(name_and_type_index) {}
	uint16_t get_bootstrap_method_attr_index() const {
		return bootstrap_method_attr_index;
	}
	uint16_t get_name_and_type_index() const {
		return name_and_type_index;
	}

	static bool classof(const ConstantPoolEntry *entry) {
		return entry->get_kind() == Kind::InvokeDynamic;
	}
	// tag(1) + bootstrap_method_attr_index(2) + name_and_type_index(2)
	virtual uint32_t get_byte_size() const { return 5; }
	virtual void write_buffer(uint8_t** buffer) const;
private:
	uint16_t bootstrap_method_attr_index;
	uint16_t name_and_type_index;
};

}

#endif
