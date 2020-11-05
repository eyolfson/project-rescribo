#include "attribute.hpp"

#include "annotation.hpp"
#include "annotations.hpp"
#include "buffer.hpp"
#include "casting.hpp"
#include "class_file.hpp"
#include "code.hpp"
#include "constant_pool.hpp"
#include "field.hpp"
#include "method.hpp"
#include "stack_map_table.hpp"

using namespace project_rescribo;

std::unique_ptr<Attribute>
Attribute::make(const uint8_t** buffer, ClassFile* class_file) {
	uint16_t attribute_name_index = next_u16(buffer);
	uint32_t attribute_length = next_u32(buffer);

	ConstantPool* constant_pool = class_file->get_constant_pool();
	auto name_entry = constant_pool->get_entry(attribute_name_index);
	ConstantPoolUtf8* name = cast<ConstantPoolUtf8>(name_entry);

	const uint8_t* attribute_start = *buffer;
	std::unique_ptr<Attribute> attribute;
	if (name->equals("BootstrapMethods")) {
		attribute = std::make_unique<BootstrapMethods>(
			buffer, attribute_name_index, class_file
		);
	}
	else if (name->equals("Deprecated")) {
		attribute = std::make_unique<Deprecated>(buffer,
		                                         attribute_name_index);
	}
	else if (name->equals("EnclosingMethod")) {
		attribute = std::make_unique<EnclosingMethod>(
			buffer, attribute_name_index, class_file
		);
	}
	else if (name->equals("InnerClasses")) {
		attribute = std::make_unique<InnerClasses>(buffer,
		                                           attribute_name_index,
		                                           class_file);
	}
	else if (name->equals("NestHost")) {
		attribute = std::make_unique<NestHost>(
			buffer, attribute_name_index, class_file
		);
	}
	else if (name->equals("NestMembers")) {
		attribute = std::make_unique<NestMembers>(
			buffer, attribute_name_index, class_file
		);
	}
	else if (name->equals("RuntimeInvisibleAnnotations")) {
		attribute = std::make_unique<RuntimeInvisibleAnnotations>(
			buffer,
			attribute_name_index,
			constant_pool
		);
	}
	else if (name->equals("RuntimeVisibleAnnotations")) {
		attribute = std::make_unique<RuntimeVisibleAnnotations>(
			buffer,
			attribute_name_index,
			constant_pool
		);
	}
	else if (name->equals("Signature")) {
		attribute = std::make_unique<Signature>(buffer,
		                                        attribute_name_index);
	}
	else if (name->equals("SourceFile")) {
		attribute = std::make_unique<SourceFile>(buffer,
		                                         attribute_name_index);
	}
	else if (name->equals("Synthetic")) {
		attribute = std::make_unique<Synthetic>(buffer,
		                                        attribute_name_index);
	}
	else if (name->equals("Scala")) {
		attribute = std::make_unique<Scala>(
			buffer, attribute_name_index
		);
	}
	else if (name->equals("ScalaInlineInfo")) {
		attribute = std::make_unique<ScalaInlineInfo>(
			buffer, attribute_name_index, class_file
		);
	}
	else if (name->equals("ScalaSig")) {
		attribute = std::make_unique<ScalaSig>(
			buffer, attribute_name_index, class_file
		);
	}
	else {
		name->print();
		assert(false && "Unexpected class file attribute");
	}

	assert(attribute_length == (attribute->get_byte_size() - 6));

	assert((*buffer - attribute_start) == attribute_length
	       && "Incomplete attribute read");
	return attribute;
}

std::unique_ptr<Attribute>
Attribute::make(const uint8_t** buffer, Field* field) {
	uint16_t attribute_name_index = next_u16(buffer);
	uint32_t attribute_length = next_u32(buffer);
	assert(attribute_name_index != 0);

	ClassFile* class_file = field->get_class_file();
	ConstantPool* constant_pool = class_file->get_constant_pool();
	auto name_entry = constant_pool->get_entry(attribute_name_index);
	ConstantPoolUtf8* name = cast<ConstantPoolUtf8>(name_entry);

	const uint8_t* attribute_start = *buffer;
	std::unique_ptr<Attribute> attribute;
	if (name->equals("ConstantValue")) {
		attribute = std::make_unique<ConstantValue>(
			buffer,
			attribute_name_index
		);
	}
	else if (name->equals("Deprecated")) {
		attribute = std::make_unique<Deprecated>(buffer,
		                                         attribute_name_index);
	}
	else if (name->equals("RuntimeInvisibleAnnotations")) {
		attribute = std::make_unique<RuntimeInvisibleAnnotations>(
			buffer,
			attribute_name_index,
			constant_pool
		);
	}
	else if (name->equals("RuntimeVisibleAnnotations")) {
		attribute = std::make_unique<RuntimeVisibleAnnotations>(
			buffer,
			attribute_name_index,
			field->get_constant_pool()
		);
	}
	else if (name->equals("RuntimeVisibleTypeAnnotations")) {
		attribute = std::make_unique<RuntimeVisibleTypeAnnotations>(
			buffer,
			attribute_name_index,
			field
		);
	}
	else if (name->equals("Signature")) {
		attribute = std::make_unique<Signature>(buffer,
		                                        attribute_name_index);
	}
	else if (name->equals("Synthetic")) {
		attribute = std::make_unique<Synthetic>(buffer,
		                                        attribute_name_index);
	}
	else {
		name->print();
		assert(false && "Unexpected field attribute");
	}

	assert(attribute_length == (attribute->get_byte_size() - 6));

	assert((*buffer - attribute_start) == attribute_length
	       && "Incomplete attribute read");
	return attribute;
}

std::unique_ptr<Attribute>
Attribute::make(const uint8_t** buffer, Method* method) {
	uint16_t attribute_name_index = next_u16(buffer);
	uint32_t attribute_length = next_u32(buffer);

	ClassFile* class_file = method->get_class_file();
	ConstantPool* constant_pool = class_file->get_constant_pool();
	auto name_entry = constant_pool->get_entry(attribute_name_index);
	ConstantPoolUtf8* name = cast<ConstantPoolUtf8>(name_entry);

	const uint8_t* attribute_start = *buffer;
	std::unique_ptr<Attribute> attribute;
	if (name->equals("AnnotationDefault")) {
		attribute = std::make_unique<AnnotationDefault>(
			buffer, attribute_name_index, method
		);
	}
	else if (name->equals("Code")) {
		attribute = std::make_unique<Code>(buffer,
		                                   attribute_name_index,
		                                   method);

	}
	else if (name->equals("Deprecated")) {
		attribute = std::make_unique<Deprecated>(buffer,
		                                         attribute_name_index);
	}
	else if (name->equals("Exceptions")) {
		attribute = std::make_unique<Exceptions>(
			buffer, attribute_name_index, method
		);
	}
	else if (name->equals("MethodParameters")) {
		attribute = std::make_unique<MethodParameters>(
			buffer, attribute_name_index, method
		);
	}
	else if (name->equals("RuntimeInvisibleAnnotations")) {
		attribute = std::make_unique<RuntimeInvisibleAnnotations>(
			buffer,
			attribute_name_index,
			constant_pool
		);
	}
	else if (name->equals("RuntimeInvisibleParameterAnnotations")) {
		attribute
		= std::make_unique<RuntimeInvisibleParameterAnnotations>(
			buffer,
			attribute_name_index,
			constant_pool
		);
	}
	else if (name->equals("RuntimeVisibleAnnotations")) {
		attribute = std::make_unique<RuntimeVisibleAnnotations>(
			buffer,
			attribute_name_index,
			constant_pool
		);
	}
	else if (name->equals("RuntimeVisibleTypeAnnotations")) {
		attribute = std::make_unique<RuntimeVisibleTypeAnnotations>(
			buffer,
			attribute_name_index,
			method
		);
	}
	else if (name->equals("RuntimeVisibleParameterAnnotations")) {
		attribute
		= std::make_unique<RuntimeVisibleParameterAnnotations>(
			buffer,
			attribute_name_index,
			constant_pool
		);
	}
	else if (name->equals("Signature")) {
		attribute = std::make_unique<Signature>(buffer,
		                                        attribute_name_index);
	}
	else if (name->equals("Synthetic")) {
		attribute = std::make_unique<Synthetic>(buffer,
		                                        attribute_name_index);
	}
	else {
		name->print();
		assert(false && "Unexpected method attribute");
	}

	if (attribute_length != (attribute->get_byte_size() - 6)) {
		name->print();
	}

	assert(attribute_length == (attribute->get_byte_size() - 6));

	assert((*buffer - attribute_start) == attribute_length
	       && "Incomplete attribute read");
	return attribute;
}

std::unique_ptr<Attribute>
Attribute::make(const uint8_t** buffer, Code* code) {
	uint16_t attribute_name_index = next_u16(buffer);
	uint32_t attribute_length = next_u32(buffer);

	Method* method = code->get_method();
	ClassFile* class_file = method->get_class_file();
	ConstantPool* constant_pool = class_file->get_constant_pool();
	auto name_entry = constant_pool->get_entry(attribute_name_index);
	ConstantPoolUtf8* name = cast<ConstantPoolUtf8>(name_entry);

	const uint8_t* attribute_start = *buffer;
	std::unique_ptr<Attribute> attribute;
	if (name->equals("LineNumberTable")) {
		attribute = std::make_unique<LineNumberTable>(
			buffer, attribute_name_index, code
		);
	}
	else if (name->equals("LocalVariableTable")) {
		attribute = std::make_unique<LocalVariableTable>(
			buffer, attribute_name_index, code
		);
	}
	else if (name->equals("LocalVariableTypeTable")) {
		attribute = std::make_unique<LocalVariableTypeTable>(
			buffer, attribute_name_index, code
		);
	}
	else if (name->equals("RuntimeVisibleTypeAnnotations")) {
		attribute = std::make_unique<RuntimeVisibleTypeAnnotations>(
			buffer,
			attribute_name_index,
			code
		);
	}
	else if (name->equals("StackMapTable")) {
		attribute = std::make_unique<StackMapTable>(
			buffer, attribute_name_index, code
		);
	}
	else {
		name->print();
		assert(false && "Unexpected code attribute");
	}

	assert(attribute_length == (attribute->get_byte_size() - 6));

	assert((*buffer - attribute_start) == attribute_length
	       && "Incomplete attribute read");
	return attribute;
}

Attribute::~Attribute() = default;

AnnotationDefault::AnnotationDefault(
	const uint8_t** buffer,
	uint16_t attribute_name_index,
	Method* method)
: Attribute(Kind::AnnotationDefault, attribute_name_index), method(method) {
	default_value = ElementValue::make(buffer, method->get_constant_pool());
}

uint32_t AnnotationDefault::get_byte_size() const {
	uint32_t result = 6;
	result += default_value->get_byte_size();
	return result;
}

void AnnotationDefault::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, default_value->get_byte_size());
	default_value->write_buffer(buffer);
}

BootstrapMethods::BootstrapMethods(const uint8_t** buffer,
                                   uint16_t attribute_name_index,
                                   ClassFile* class_file)
: Attribute(Kind::BootstrapMethods, attribute_name_index),
  class_file(class_file) {
	uint16_t num_bootstrap_methods = next_u16(buffer);
	for (uint32_t i = 0; i < num_bootstrap_methods; ++i) {
		uint16_t bootstrap_method_ref = next_u16(buffer);
		uint16_t num_bootstrap_arguments = next_u16(buffer);
		std::vector<uint16_t> bootstrap_arguments;
		for (uint32_t j = 0; j < num_bootstrap_arguments; ++j) {
			bootstrap_arguments.push_back(next_u16(buffer));
		}
		bootstrap_methods.push_back({
			bootstrap_method_ref,
			std::move(bootstrap_arguments)
		});
	}
}

void BootstrapMethods::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, get_byte_size() - 6);
	next_u16(buffer, bootstrap_methods.size());
	for (const auto& entry : bootstrap_methods) {
		next_u16(buffer, entry.bootstrap_method_ref);
		next_u16(buffer, entry.bootstrap_arguments.size());
		for (uint16_t bootstrap_argument : entry.bootstrap_arguments) {
			next_u16(buffer, bootstrap_argument);
		}
	}
}

ConstantValue::ConstantValue(const uint8_t** buffer,
                             uint16_t attribute_name_index)
: Attribute(Kind::ConstantValue, attribute_name_index) {
	index = next_u16(buffer);
}

void ConstantValue::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 2);
	next_u16(buffer, index);
}

Deprecated::Deprecated(const uint8_t** buffer,
                       uint16_t attribute_name_index)
: Attribute(Kind::Deprecated, attribute_name_index) {
}

void Deprecated::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 0);
}

EnclosingMethod::EnclosingMethod(const uint8_t** buffer,
                                 uint16_t attribute_name_index,
                                 ClassFile* class_file)
: Attribute(Kind::EnclosingMethod, attribute_name_index),
  class_file(class_file) {
	class_index = next_u16(buffer);
	method_index = next_u16(buffer);
}

void EnclosingMethod::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 4);
	next_u16(buffer, class_index);
	next_u16(buffer, method_index);
}

InnerClasses::InnerClasses(const uint8_t** buffer,
                           uint16_t attribute_name_index,
                           ClassFile* class_file)
: Attribute(Kind::InnerClasses, attribute_name_index), class_file(class_file) {
	uint16_t number_of_classes = next_u16(buffer);
	for (uint32_t i = 0; i < number_of_classes; ++i) {
		uint16_t inner_class_info_index = next_u16(buffer);
		uint16_t outer_class_info_index = next_u16(buffer);
		uint16_t inner_name_index = next_u16(buffer);
		Access inner_class_access_flags = Access(next_u16(buffer));
		classes.push_back({
			inner_class_info_index,
			outer_class_info_index,
			inner_name_index,
			inner_class_access_flags,
		});
	}
}

void InnerClasses::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 2 + 8 * classes.size());
	next_u16(buffer, classes.size());
	for (const auto& entry : classes) {
		next_u16(buffer, entry.inner_class_info_index);
		next_u16(buffer, entry.outer_class_info_index);
		next_u16(buffer, entry.inner_name_index);
		next_u16(buffer, entry.inner_class_access_flags.get_flags());
	}
}

Exceptions::Exceptions(const uint8_t** buffer,
                       uint16_t attribute_name_index,
                       Method* method)
: Attribute(Kind::Exceptions, attribute_name_index), method(method) {
	uint16_t number_of_exceptions = next_u16(buffer);
	for (uint32_t i = 0; i < number_of_exceptions; ++i) {
		exception_index_table.push_back(next_u16(buffer));
	}
}

void Exceptions::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 2 + 2 * exception_index_table.size());
	next_u16(buffer, exception_index_table.size());
	for (uint16_t entry : exception_index_table) {
		next_u16(buffer, entry);
	}
}

LineNumberTable::LineNumberTable(const uint8_t** buffer,
                                 uint16_t attribute_name_index,
                                 Code* code)
: Attribute(Kind::LineNumberTable, attribute_name_index), code(code) {
	uint16_t line_number_table_length = next_u16(buffer);
	for (uint32_t i = 0; i < line_number_table_length; ++i) {
		uint16_t start_pc = next_u16(buffer);
		uint16_t line_number = next_u16(buffer);
		line_number_table.push_back({start_pc, line_number});
	}
}

void LineNumberTable::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 2 + 4 * line_number_table.size());

	next_u16(buffer, line_number_table.size());
	for (const auto& entry : line_number_table) {
		next_u16(buffer, entry.start_pc);
		next_u16(buffer, entry.line_number);
	}
}

LocalVariableTable::LocalVariableTable(const uint8_t** buffer,
                                       uint16_t attribute_name_index,
                                       Code* code)
: Attribute(Kind::LocalVariableTable, attribute_name_index), code(code) {
	uint16_t line_number_table_length = next_u16(buffer);
	for (uint32_t i = 0; i < line_number_table_length; ++i) {
		uint16_t start_pc = next_u16(buffer);
		Instruction* start = code->get_instruction(start_pc);
		uint16_t length = next_u16(buffer);
		Instruction* end = nullptr;
		if ((start_pc + length) != code->get_next_bci()) {
			end = code->get_instruction(start_pc + length);
		}
		uint16_t name_index = next_u16(buffer);
		uint16_t descriptor_index = next_u16(buffer);
		uint16_t index = next_u16(buffer);
		local_variable_table.push_back({
			start,
			end,
			name_index,
			descriptor_index,
			index
		});
	}
}

void LocalVariableTable::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 2 + 10 * local_variable_table.size());
	next_u16(buffer, local_variable_table.size());
	for (const auto& entry : local_variable_table) {
		next_u16(buffer, entry.start->get_bci());
		uint16_t length;
		if (entry.end) {
			length = entry.end->get_bci() - entry.start->get_bci();
		}
		else {
			length = code->get_next_bci() - entry.start->get_bci();
		}
		next_u16(buffer, length);
		next_u16(buffer, entry.name_index);
		next_u16(buffer, entry.descriptor_index);
		next_u16(buffer, entry.index);
	}
}

LocalVariableTypeTable::LocalVariableTypeTable(const uint8_t** buffer,
                                               uint16_t attribute_name_index,
                                               Code* code)
: Attribute(Kind::LocalVariableTypeTable, attribute_name_index), code(code) {
	uint16_t line_number_table_length = next_u16(buffer);
	for (uint32_t i = 0; i < line_number_table_length; ++i) {
		uint16_t start_pc = next_u16(buffer);
		Instruction* start = code->get_instruction(start_pc);
		uint16_t length = next_u16(buffer);
		Instruction* end = nullptr;
		if ((start_pc + length) != code->get_next_bci()) {
			end = code->get_instruction(start_pc + length);
		}
		uint16_t name_index = next_u16(buffer);
		uint16_t signature_index = next_u16(buffer);
		uint16_t index = next_u16(buffer);
		local_variable_type_table.push_back({
			start,
			end,
			name_index,
			signature_index,
			index
		});
	}
}

void LocalVariableTypeTable::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 2 + 10 * local_variable_type_table.size());
	next_u16(buffer, local_variable_type_table.size());
	for (const auto& entry : local_variable_type_table) {
		next_u16(buffer, entry.start->get_bci());
		uint16_t length;
		if (entry.end) {
			length = entry.end->get_bci() - entry.start->get_bci();
		}
		else {
			length = code->get_next_bci() - entry.start->get_bci();
		}
		next_u16(buffer, length);
		next_u16(buffer, entry.name_index);
		next_u16(buffer, entry.signature_index);
		next_u16(buffer, entry.index);
	}
}

NestHost::NestHost(const uint8_t** buffer,
                   uint16_t attribute_name_index,
                   ClassFile* class_file)
: Attribute(Kind::NestHost, attribute_name_index), class_file(class_file) {
	host_class_index = next_u16(buffer);
}

void NestHost::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 2);
	next_u16(buffer, host_class_index);
}

MethodParameters::MethodParameters(const uint8_t** buffer,
                                   uint16_t attribute_name_index,
                                   Method* method)
: Attribute(Kind::MethodParameters, attribute_name_index), method(method) {
	uint8_t parameters_count = next_u8(buffer);
	for (uint32_t i = 0; i < parameters_count; ++i) {
		parameters.push_back({next_u16(buffer), next_u16(buffer)});
	}
}

void MethodParameters::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 1 + 4 * parameters.size());
	assert(parameters.size() <= 255);
	next_u8(buffer, parameters.size());
	for (const Entry& entry : parameters) {
		next_u16(buffer, entry.name_index);
		next_u16(buffer, entry.access_flags);
	}
}

NestMembers::NestMembers(const uint8_t** buffer,
                         uint16_t attribute_name_index,
                         ClassFile* class_file)
: Attribute(Kind::NestMembers, attribute_name_index), class_file(class_file) {
	uint16_t number_of_exceptions = next_u16(buffer);
	for (uint32_t i = 0; i < number_of_exceptions; ++i) {
		classes.push_back(next_u16(buffer));
	}
}

void NestMembers::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 2 + 2 * classes.size());
	next_u16(buffer, classes.size());
	for (uint16_t entry : classes) {
		next_u16(buffer, entry);
	}
}

RuntimeInvisibleAnnotations::RuntimeInvisibleAnnotations(
	const uint8_t** buffer,
	uint16_t attribute_name_index,
	ConstantPool* constant_pool)
: Attribute(Kind::RuntimeInvisibleAnnotations, attribute_name_index) {
	annotations = std::make_unique<Annotations>(buffer,
	                                            constant_pool);
}

uint32_t RuntimeInvisibleAnnotations::get_byte_size() const {
	uint32_t result = 6;
	result += annotations->get_byte_size();
	return result;
}

void RuntimeInvisibleAnnotations::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, annotations->get_byte_size());
	annotations->write_buffer(buffer);
}

RuntimeInvisibleParameterAnnotations::RuntimeInvisibleParameterAnnotations(
	const uint8_t** buffer,
	uint16_t attribute_name_index,
	ConstantPool* constant_pool)
: Attribute(Kind::RuntimeInvisibleParameterAnnotations, attribute_name_index) {
	uint8_t num_parameters = next_u8(buffer);
	for (int i = 0; i < num_parameters; ++i) {
		parameter_annotations.push_back(
			std::make_unique<Annotations>(buffer, constant_pool)
		);
	}
}

uint32_t RuntimeInvisibleParameterAnnotations::get_byte_size() const {
	uint32_t result = 7;
	for (const auto& annotations : parameter_annotations) {
		result += annotations->get_byte_size();
	}
	return result;
}

void
RuntimeInvisibleParameterAnnotations::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, get_byte_size() - 6);
	next_u8(buffer, parameter_annotations.size());
	for (const auto& annotations : parameter_annotations) {
		annotations->write_buffer(buffer);
	}
}

RuntimeVisibleAnnotations::RuntimeVisibleAnnotations(
	const uint8_t** buffer,
	uint16_t attribute_name_index,
	ConstantPool* constant_pool)
: Attribute(Kind::RuntimeVisibleAnnotations, attribute_name_index) {
	annotations = std::make_unique<Annotations>(buffer,
	                                            constant_pool);
}

uint32_t RuntimeVisibleAnnotations::get_byte_size() const {
	uint32_t result = 6;
	result += annotations->get_byte_size();
	return result;
}

void RuntimeVisibleAnnotations::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, annotations->get_byte_size());
	annotations->write_buffer(buffer);
}

RuntimeVisibleParameterAnnotations::RuntimeVisibleParameterAnnotations(
	const uint8_t** buffer,
	uint16_t attribute_name_index,
	ConstantPool* constant_pool)
: Attribute(Kind::RuntimeVisibleParameterAnnotations, attribute_name_index) {
	uint8_t num_parameters = next_u8(buffer);
	for (int i = 0; i < num_parameters; ++i) {
		parameter_annotations.push_back(
			std::make_unique<Annotations>(buffer, constant_pool)
		);
	}
}

uint32_t RuntimeVisibleParameterAnnotations::get_byte_size() const {
	uint32_t result = 7;
	for (const auto& annotations : parameter_annotations) {
		result += annotations->get_byte_size();
	}
	return result;
}

void RuntimeVisibleParameterAnnotations::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, get_byte_size() - 6);
	next_u8(buffer, parameter_annotations.size());
	for (const auto& annotations : parameter_annotations) {
		annotations->write_buffer(buffer);
	}
}

RuntimeVisibleTypeAnnotations::RuntimeVisibleTypeAnnotations(
	const uint8_t** buffer,
	uint16_t attribute_name_index,
	ConstantPool* constant_pool)
: Attribute(Kind::RuntimeVisibleTypeAnnotations, attribute_name_index) {
	annotations = std::make_unique<TypeAnnotations>(buffer,
	                                                constant_pool);
}

RuntimeVisibleTypeAnnotations::RuntimeVisibleTypeAnnotations(
	const uint8_t** buffer,
	uint16_t attribute_name_index,
	Field* field)
: Attribute(Kind::RuntimeVisibleTypeAnnotations, attribute_name_index) {
	annotations = std::make_unique<TypeAnnotations>(buffer,
	                                                field);
}

RuntimeVisibleTypeAnnotations::RuntimeVisibleTypeAnnotations(
	const uint8_t** buffer,
	uint16_t attribute_name_index,
	Method* method)
: Attribute(Kind::RuntimeVisibleTypeAnnotations, attribute_name_index) {
	annotations = std::make_unique<TypeAnnotations>(buffer,
	                                                method);
}

RuntimeVisibleTypeAnnotations::RuntimeVisibleTypeAnnotations(
	const uint8_t** buffer,
	uint16_t attribute_name_index,
	Code* code)
: Attribute(Kind::RuntimeVisibleTypeAnnotations, attribute_name_index) {
	annotations = std::make_unique<TypeAnnotations>(buffer,
	                                                code);
}

uint32_t RuntimeVisibleTypeAnnotations::get_byte_size() const {
	uint32_t result = 6;
	result += annotations->get_byte_size();
	return result;
}

void RuntimeVisibleTypeAnnotations::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, annotations->get_byte_size());
	annotations->write_buffer(buffer);
}

Signature::Signature(const uint8_t** buffer, uint16_t attribute_name_index)
: Attribute(Kind::Signature, attribute_name_index) {
	signature_index = next_u16(buffer);
}

void Signature::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 2);
	next_u16(buffer, signature_index);
}

SourceFile::SourceFile(const uint8_t** buffer, uint16_t attribute_name_index)
: Attribute(Kind::SourceFile, attribute_name_index) {
	sourcefile_index = next_u16(buffer);
}

void SourceFile::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 2);
	next_u16(buffer, sourcefile_index);
}

Synthetic::Synthetic(const uint8_t** buffer, uint16_t attribute_name_index)
: Attribute(Kind::Synthetic, attribute_name_index) {
}

void Synthetic::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 0);
}

Scala::Scala(const uint8_t** buffer,
             uint16_t attribute_name_index)
: Attribute(Kind::Scala, attribute_name_index) {
}

void Scala::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 0);
}

ScalaInlineInfo::ScalaInlineInfo(const uint8_t** buffer,
                                 uint16_t attribute_name_index,
                                 ClassFile* class_file)
: Attribute(Kind::ScalaInlineInfo, attribute_name_index),
  class_file(class_file) {
	version = next_u8(buffer);
	assert(version == 1);
	flags = next_u8(buffer);
	if (flags & 0x04) {
		sam_name_index = next_u16(buffer);
		sam_descriptor_index = next_u16(buffer);
	}
	uint16_t entries_length = next_u16(buffer);
	for (uint32_t i = 0; i < entries_length; ++i) {
		uint16_t name_index = next_u16(buffer);
		uint16_t descriptor_index = next_u16(buffer);
		uint8_t value = next_u8(buffer);
		entries.push_back({name_index, descriptor_index, value});
	}
}

void ScalaInlineInfo::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	uint32_t length = 4 + 5 * entries.size();
	if (flags & 0x04) {
		length += 4;
	}
	next_u32(buffer, length);
	next_u8(buffer, version);
	next_u8(buffer, flags);
	if (flags & 0x04) {
		next_u16(buffer, sam_name_index);
		next_u16(buffer, sam_descriptor_index);
	}
	next_u16(buffer, entries.size());
	for (const auto& entry : entries) {
		next_u16(buffer, entry.name_index);
		next_u16(buffer, entry.descriptor_index);
		next_u8(buffer, entry.value);
	}
}

ScalaSig::ScalaSig(const uint8_t** buffer,
                   uint16_t attribute_name_index,
                   ClassFile* class_file)
: Attribute(Kind::ScalaSig, attribute_name_index),
  class_file(class_file) {
	major_version = next_u8(buffer);
	assert(major_version == 5);
	minor_version = next_u8(buffer);
	assert(minor_version == 0);
	value = next_u8(buffer);
	assert(value == 0);
}

void ScalaSig::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());
	next_u32(buffer, 3);
	next_u8(buffer, major_version);
	next_u8(buffer, minor_version);
	next_u8(buffer, value);
}
