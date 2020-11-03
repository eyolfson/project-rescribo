#ifndef PROJECT_TOTUS_ATTRIBUTE_HPP
#define PROJECT_TOTUS_ATTRIBUTE_HPP

#include "access.hpp"

#include <cstdint>
#include <memory>
#include <vector>

namespace project_totus {

class Annotations;
class ClassFile;
class Code;
class ConstantPool;
class ElementValue;
class Field;
class Instruction;
class Method;
class TypeAnnotations;

class Attribute {
public:
	enum class Kind {
		ConstantValue,
		Code,
		StackMapTable,
		Exceptions,
		InnerClasses,
		EnclosingMethod,
		Synthetic,
		Signature,
		SourceFile,
		SourceDebugExtension,
		LineNumberTable,
		LocalVariableTable,
		LocalVariableTypeTable,
		Deprecated,
		RuntimeVisibleAnnotations,
		RuntimeInvisibleAnnotations,
		RuntimeVisibleParameterAnnotations,
		RuntimeInvisibleParameterAnnotations,
		RuntimeVisibleTypeAnnotations,
		RuntimeInvisibleTypeAnnotations,
		AnnotationDefault,
		BootstrapMethods,
		MethodParameters,
		Module,
		ModulePackages,
		ModuleMainClass,
		NestHost,
		NestMembers,
		Scala,
		ScalaInlineInfo,
		ScalaSig
	};
	Attribute(Kind kind, uint16_t attribute_name_index)
		: kind(kind), attribute_name_index(attribute_name_index) {}
	virtual ~Attribute();
	Kind get_kind() const {
		return kind;
	}
	uint16_t get_attribute_name_index() const {
		return attribute_name_index;
	}
	void set_attribute_name_index(uint16_t index) {
		attribute_name_index = index;
	}

	virtual uint32_t get_byte_size() const = 0;
	virtual void write_buffer(uint8_t** buffer) const = 0;

	static std::unique_ptr<Attribute> make(const uint8_t** buffer,
	                                       ClassFile* class_file);
	static std::unique_ptr<Attribute> make(const uint8_t** buffer,
	                                       Field* field);
	static std::unique_ptr<Attribute> make(const uint8_t** buffer,
	                                       Method* method);
	static std::unique_ptr<Attribute> make(const uint8_t** buffer,
	                                       Code* code);
private:
	Kind kind;
	uint16_t attribute_name_index;
};

class AnnotationDefault : public Attribute {
public:
	AnnotationDefault(const uint8_t** buffer,
	                  uint16_t attribute_name_index,
	                  Method* method);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::AnnotationDefault;
	}

	Method* get_method() const {
		return method;
	}

	virtual uint32_t get_byte_size() const override;
	virtual void write_buffer(uint8_t** buffer) const override;

private:
	Method* method;
	std::unique_ptr<ElementValue> default_value;
};

class BootstrapMethods : public Attribute {
public:
	struct Entry {
		uint16_t bootstrap_method_ref;
		std::vector<uint16_t> bootstrap_arguments;
	};

	BootstrapMethods(const uint8_t** buffer,
	                 uint16_t attribute_name_index,
	                 ClassFile* class_file);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::BootstrapMethods;
	}

	virtual uint32_t get_byte_size() const override {
		uint32_t result = 8;
		for (const auto& entry : bootstrap_methods) {
			result += 4 + 2 * entry.bootstrap_arguments.size();
		}
		return result;
	}
	virtual void write_buffer(uint8_t** buffer) const override;

	ClassFile* get_class_file() const {
		return class_file;
	}

private:
	ClassFile* class_file;
	std::vector<Entry> bootstrap_methods;
};

class ConstantValue : public Attribute {
public:
	ConstantValue(const uint8_t** buffer, uint16_t attribute_name_index);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::ConstantValue;
	}

	uint16_t get_index() const {
		return index;
	}

	virtual uint32_t get_byte_size() const override {
		return 8;
	}
	virtual void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t index;
};

class Deprecated : public Attribute {
public:
	Deprecated(const uint8_t** buffer,
		   uint16_t attribute_name_index);

	virtual uint32_t get_byte_size() const override {
		return 6;
	}
	virtual void write_buffer(uint8_t** buffer) const override;
};

class EnclosingMethod : public Attribute {
public:
	EnclosingMethod(const uint8_t** buffer,
	                uint16_t attribute_name_index,
	                ClassFile* class_file);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::EnclosingMethod;
	}

	virtual uint32_t get_byte_size() const override {
		return 10;
	}
	virtual void write_buffer(uint8_t** buffer) const override;

	ClassFile* get_class_file() const {
		return class_file;
	}

private:
	ClassFile* class_file;
	uint16_t class_index;
	uint16_t method_index;
};

class Exceptions : public Attribute {
public:
	Exceptions(const uint8_t** buffer,
	           uint16_t attribute_name_index,
	           Method* method);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::Exceptions;
	}

	Method* get_method() const {
		return method;
	}

	virtual uint32_t get_byte_size() const override {
		return 8 + 2 * exception_index_table.size();
	}
	virtual void write_buffer(uint8_t** buffer) const override;

private:
	Method* method;
	std::vector<uint16_t> exception_index_table;
};

class InnerClasses : public Attribute {
public:
	struct Entry {
		uint16_t inner_class_info_index;
		uint16_t outer_class_info_index;
		uint16_t inner_name_index;
		Access inner_class_access_flags;
	};

	InnerClasses(const uint8_t** buffer,
	             uint16_t attribute_name_index,
	             ClassFile* class_file);

	virtual uint32_t get_byte_size() const override {
		return 8 + 8 * classes.size();
	}
	virtual void write_buffer(uint8_t** buffer) const override;

	ClassFile* get_class_file() const {
		return class_file;
	}
private:
	ClassFile* class_file;
	std::vector<Entry> classes;
};

class LineNumberTable : public Attribute {
public:
	struct Entry {
		uint16_t start_pc;
		uint16_t line_number;
	};

	LineNumberTable(const uint8_t** buffer,
	                uint16_t attribute_name_index,
	                Code* code);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::LineNumberTable;
	}

	Code* get_code() const {
		return code;
	}

	virtual uint32_t get_byte_size() const override {
		return 8 + 4 * line_number_table.size();
	}
	virtual void write_buffer(uint8_t** buffer) const override;
private:
	Code* code;
	std::vector<Entry> line_number_table;
};

class LocalVariableTable : public Attribute {
public:
	struct Entry {
		Instruction* start;
		Instruction* end;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t index;
	};

	LocalVariableTable(const uint8_t** buffer,
	                   uint16_t attribute_name_index,
	                   Code* code);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::LocalVariableTable;
	}

	Code* get_code() const {
		return code;
	}

	virtual uint32_t get_byte_size() const override {
		return 8 + 10 * local_variable_table.size();
	}
	virtual void write_buffer(uint8_t** buffer) const override;
private:
	Code* code;
	std::vector<Entry> local_variable_table;
};

class LocalVariableTypeTable : public Attribute {
public:
	struct Entry {
		Instruction* start;
		Instruction* end;
		uint16_t name_index;
		uint16_t signature_index;
		uint16_t index;
	};

	LocalVariableTypeTable(const uint8_t** buffer,
	                       uint16_t attribute_name_index,
	                       Code* code);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::LocalVariableTypeTable;
	}

	Code* get_code() const {
		return code;
	}

	virtual uint32_t get_byte_size() const override {
		return 8 + 10 * local_variable_type_table.size();
	}
	virtual void write_buffer(uint8_t** buffer) const override;
private:
	Code* code;
	std::vector<Entry> local_variable_type_table;
};

class MethodParameters : public Attribute {
public:
	struct Entry {
		uint16_t name_index;
		uint16_t access_flags;
	};

	MethodParameters(const uint8_t** buffer,
	                 uint16_t attribute_name_index,
	                 Method* method);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::MethodParameters;
	}

	Method* get_method() const {
		return method;
	}

	virtual uint32_t get_byte_size() const override {
		return 7 + 4 * parameters.size();
	}
	virtual void write_buffer(uint8_t** buffer) const override;

private:
	Method* method;
	std::vector<Entry> parameters;
};

class NestHost : public Attribute {
public:
	NestHost(const uint8_t** buffer,
	         uint16_t attribute_name_index,
	         ClassFile* class_file);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::NestHost;
	}

	virtual uint32_t get_byte_size() const override {
		return 8;
	}
	virtual void write_buffer(uint8_t** buffer) const override;

	ClassFile* get_class_file() const {
		return class_file;
	}

private:
	ClassFile* class_file;
	uint16_t host_class_index;
};

class NestMembers : public Attribute {
public:
	NestMembers(const uint8_t** buffer,
	            uint16_t attribute_name_index,
	            ClassFile* class_file);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::NestMembers;
	}

	virtual uint32_t get_byte_size() const override {
		return 8 + 2 * classes.size();
	}
	virtual void write_buffer(uint8_t** buffer) const override;

	ClassFile* get_class_file() const {
		return class_file;
	}

private:
	ClassFile* class_file;
	std::vector<uint16_t> classes;
};

class RuntimeInvisibleAnnotations : public Attribute {
public:
	RuntimeInvisibleAnnotations(const uint8_t** buffer,
	                            uint16_t attribute_name_index,
	                            ConstantPool* constant_pool);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind()
		       == Kind::RuntimeInvisibleAnnotations;
	}

	virtual uint32_t get_byte_size() const override;
	virtual void write_buffer(uint8_t** buffer) const override;

private:
	std::unique_ptr<Annotations> annotations;
};

class RuntimeInvisibleParameterAnnotations : public Attribute {
public:
	RuntimeInvisibleParameterAnnotations(const uint8_t** buffer,
	                                     uint16_t attribute_name_index,
	                                     ConstantPool* constant_pool);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind()
		       == Kind::RuntimeInvisibleParameterAnnotations;
	}

	virtual uint32_t get_byte_size() const override;
	virtual void write_buffer(uint8_t** buffer) const override;

private:
	std::vector<std::unique_ptr<Annotations>> parameter_annotations;
};

class RuntimeVisibleAnnotations : public Attribute {
public:
	RuntimeVisibleAnnotations(const uint8_t** buffer,
	                          uint16_t attribute_name_index,
	                          ConstantPool* constant_pool);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::RuntimeVisibleAnnotations;
	}

	virtual uint32_t get_byte_size() const override;
	virtual void write_buffer(uint8_t** buffer) const override;

private:
	std::unique_ptr<Annotations> annotations;
};

class RuntimeVisibleParameterAnnotations : public Attribute {
public:
	RuntimeVisibleParameterAnnotations(const uint8_t** buffer,
	                                   uint16_t attribute_name_index,
	                                   ConstantPool* constant_pool);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind()
		       == Kind::RuntimeVisibleParameterAnnotations;
	}

	virtual uint32_t get_byte_size() const override;
	virtual void write_buffer(uint8_t** buffer) const override;

private:
	std::vector<std::unique_ptr<Annotations>> parameter_annotations;
};

class RuntimeVisibleTypeAnnotations : public Attribute {
public:
	RuntimeVisibleTypeAnnotations(const uint8_t** buffer,
	                              uint16_t attribute_name_index,
	                              ConstantPool* constant_pool);
	RuntimeVisibleTypeAnnotations(const uint8_t** buffer,
	                              uint16_t attribute_name_index,
	                              Field* field);
	RuntimeVisibleTypeAnnotations(const uint8_t** buffer,
	                              uint16_t attribute_name_index,
	                              Method* method);
	RuntimeVisibleTypeAnnotations(const uint8_t** buffer,
	                              uint16_t attribute_name_index,
	                              Code* code);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind()
		       == Kind::RuntimeVisibleTypeAnnotations;
	}

	virtual uint32_t get_byte_size() const override;
	virtual void write_buffer(uint8_t** buffer) const override;

private:
	std::unique_ptr<TypeAnnotations> annotations;
};

class Signature : public Attribute {
public:
	Signature(const uint8_t** buffer, uint16_t attribute_name_index);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::Signature;
	}

	uint16_t get_signature_index() const {
		return signature_index;
	}

	virtual uint32_t get_byte_size() const override {
		return 8;
	}
	virtual void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t signature_index;
};

class SourceFile : public Attribute {
public:
	SourceFile(const uint8_t** buffer, uint16_t attribute_name_index);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::SourceFile;
	}

	uint16_t get_sourcefile_index() const {
		return sourcefile_index;
	}

	// attribute_name_index(2) + attribute_length(4) + sourcefile_index(2)
	virtual uint32_t get_byte_size() const override {
		return 8;
	}
	virtual void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t sourcefile_index;
};

class Synthetic : public Attribute {
public:
	Synthetic(const uint8_t** buffer, uint16_t attribute_name_index);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::Synthetic;
	}

	virtual uint32_t get_byte_size() const override {
		return 6;
	}
	virtual void write_buffer(uint8_t** buffer) const override;
};

class Scala : public Attribute {
public:
	Scala(const uint8_t** buffer,
	      uint16_t attribute_name_index);

	virtual uint32_t get_byte_size() const override {
		return 6;
	}
	virtual void write_buffer(uint8_t** buffer) const override;
};

class ScalaInlineInfo : public Attribute {
public:
	struct Entry {
		uint16_t name_index;
		uint16_t descriptor_index;
		uint8_t value;
	};

	ScalaInlineInfo(const uint8_t** buffer,
	                uint16_t attribute_name_index,
	                ClassFile* class_file);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::ScalaInlineInfo;
	}

	virtual uint32_t get_byte_size() const override {
		uint32_t result = 6 + 4 + 5 * entries.size();
		if (flags & 0x04) {
			result += 4;
		}
		return result;
	}
	virtual void write_buffer(uint8_t** buffer) const override;

	ClassFile* get_class_file() const {
		return class_file;
	}

private:
	ClassFile* class_file;
	uint8_t version;
	uint8_t flags;
	uint16_t sam_name_index;
	uint16_t sam_descriptor_index;
	std::vector<Entry> entries;
};

class ScalaSig : public Attribute {
public:
	ScalaSig(const uint8_t** buffer,
	         uint16_t attribute_name_index,
	         ClassFile* class_file);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::ScalaSig;
	}

	virtual uint32_t get_byte_size() const override {
		return 6 + 3;
	}
	virtual void write_buffer(uint8_t** buffer) const override;

	ClassFile* get_class_file() const {
		return class_file;
	}

private:
	ClassFile* class_file;
	uint8_t major_version;
	uint8_t minor_version;
	uint8_t value;
};

}

#endif
