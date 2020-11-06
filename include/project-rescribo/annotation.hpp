/*
 * Copyright 2019-2020 Jonathan Eyolfson
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 3 as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PROJECT_RESCRIBO_ANNOTATION_HPP
#define PROJECT_RESCRIBO_ANNOTATION_HPP

#include <cstdint>
#include <memory>
#include <vector>

namespace project_rescribo {

class Annotation;
class Code;
class ConstantPool;
class Field;
class Instruction;
class Method;

class ElementValue {
public:
	enum class Kind {
		ConstValueIndex,
		EnumConstValue,
		ClassInfoIndex,
		AnnotationValue,
		ArrayValue,
	};

	ElementValue(Kind kind, uint8_t tag, ConstantPool* constant_pool)
	: kind(kind), tag(tag), constant_pool(constant_pool) {}
	virtual ~ElementValue();

	static std::unique_ptr<ElementValue> make(const uint8_t** buffer,
	                                          ConstantPool* constant_pool);

	virtual uint32_t get_byte_size() const = 0;
	virtual void write_buffer(uint8_t** buffer) const = 0;

	Kind get_kind() const {
		return kind;
	}
	uint8_t get_tag() const {
		return tag;
	}
	ConstantPool* get_constant_pool() const {
		return constant_pool;
	}

private:
	Kind kind;
	uint8_t tag;
	ConstantPool* constant_pool;
};

class AnnotationValue : public ElementValue {
public:
	AnnotationValue(uint8_t tag, std::unique_ptr<Annotation> value,
	                ConstantPool* constant_pool)
	: ElementValue(Kind::AnnotationValue, tag, constant_pool),
	  value(std::move(value)) {}

	static bool classof(const ElementValue* element_value) {
		return element_value->get_kind() == Kind::AnnotationValue;
	}

	uint32_t get_byte_size() const override;
	void write_buffer(uint8_t** buffer) const override;

private:
	std::unique_ptr<Annotation> value;
};

class ArrayValue : public ElementValue {
public:
	ArrayValue(uint8_t tag,
	           std::vector<std::unique_ptr<ElementValue>> value,
	           ConstantPool* constant_pool)
	: ElementValue(Kind::ArrayValue, tag, constant_pool),
	  value(std::move(value)) {}

	static bool classof(const ElementValue* element_value) {
		return element_value->get_kind() == Kind::ArrayValue;
	}

	uint32_t get_byte_size() const override;
	void write_buffer(uint8_t** buffer) const override;

private:
	std::vector<std::unique_ptr<ElementValue>> value;
};

class ConstValueIndex : public ElementValue {
public:
	ConstValueIndex(uint8_t tag, uint16_t index,
	                ConstantPool* constant_pool)
	: ElementValue(Kind::ConstValueIndex, tag, constant_pool),
	  index(index) {}

	static bool classof(const ElementValue* element_value) {
		return element_value->get_kind() == Kind::ConstValueIndex;
	}

	uint32_t get_byte_size() const override {
		return 3;
	}
	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class ClassInfoIndex : public ElementValue {
public:
	ClassInfoIndex(uint8_t tag, uint16_t index,
	               ConstantPool* constant_pool)
	: ElementValue(Kind::ClassInfoIndex, tag, constant_pool),
	  index(index) {}

	static bool classof(const ElementValue* element_value) {
		return element_value->get_kind() == Kind::ClassInfoIndex;
	}

	uint32_t get_byte_size() const override {
		return 3;
	}
	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class EnumConstValue : public ElementValue {
public:
	EnumConstValue(uint8_t tag, uint16_t type_name_index,
	               uint16_t value_name_index, ConstantPool* constant_pool)
	: ElementValue(Kind::EnumConstValue, tag, constant_pool),
	  type_name_index(type_name_index), value_name_index(value_name_index) {
	}

	static bool classof(const ElementValue* element_value) {
		return element_value->get_kind() == Kind::EnumConstValue;
	}

	uint32_t get_byte_size() const override {
		return 5;
	}
	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_type_name_index() const {
		return type_name_index;
	}
	uint16_t get_value_name_index() const {
		return value_name_index;
	}
private:
	uint16_t type_name_index;
	uint16_t value_name_index;
};

class ElementValuePair {
public:
	ElementValuePair(const uint8_t** buffer, ConstantPool* constant_pool);
	~ElementValuePair();

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

	uint16_t get_name_index() const {
		return name_index;
	}

private:
	uint16_t name_index;
	std::unique_ptr<ElementValue> value;
};

class ElementValuePairs {
public:
	ElementValuePairs(const uint8_t** buffer, ConstantPool* constant_pool);
	~ElementValuePairs();

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

private:
	std::vector<std::unique_ptr<ElementValuePair>> element_value_pairs;
};

class Annotation {
public:
	Annotation(const uint8_t** buffer, ConstantPool* constant_pool);
	~Annotation();

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

	ConstantPool* get_constant_pool() const {
		return constant_pool;
	}
private:
	ConstantPool* constant_pool;
	uint16_t type_index;
	std::unique_ptr<ElementValuePairs> element_value_pairs;
};

class TypePath {
public:
	struct Entry {
		uint8_t type_path_kind;
		uint8_t type_argument_index;
	};

	TypePath(const uint8_t** buffer);
	~TypePath();

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

private:
	std::vector<Entry> entries;
};

class TypeTarget {
public:
	enum class Kind {
		TypeParameter,
		Supertype,
		TypeParameterBound,
		Empty,
		FormalParameter,
		Throws,
		LocalVar,
		Catch,
		Offset,
		TypeArgument,
	};

	TypeTarget(Kind kind, uint8_t type, std::unique_ptr<TypePath> path)
	: kind(kind), type(type), path(std::move(path)) {}
	virtual ~TypeTarget();

	static std::unique_ptr<TypeTarget> make(const uint8_t** buffer,
	                                        ConstantPool* constant_pool);
	static std::unique_ptr<TypeTarget> make(const uint8_t** buffer,
	                                        Field* field);
	static std::unique_ptr<TypeTarget> make(const uint8_t** buffer,
	                                        Method* method);
	static std::unique_ptr<TypeTarget> make(const uint8_t** buffer,
	                                        Code* code);

	virtual uint32_t get_byte_size() const = 0;
	virtual void write_buffer(uint8_t** buffer) const = 0;

	Kind get_kind() const {
		return kind;
	}
	uint8_t get_type() const {
		return type;
	}
	TypePath* get_path() const {
		return path.get();
	}

private:
	Kind kind;
	uint8_t type;
	std::unique_ptr<TypePath> path;
};

class EmptyTarget : public TypeTarget{
public:
	EmptyTarget(uint8_t type, std::unique_ptr<TypePath> path)
	: TypeTarget(Kind::Empty, type, std::move(path)) {}

	virtual uint32_t get_byte_size() const override;
	virtual void write_buffer(uint8_t** buffer) const override;
};

class FormalParameterTarget : public TypeTarget{
public:
	FormalParameterTarget(uint8_t type, uint8_t index,
	                      std::unique_ptr<TypePath> path)
	: TypeTarget(Kind::FormalParameter, type, std::move(path)),
	  index(index) {}

	virtual uint32_t get_byte_size() const override;
	virtual void write_buffer(uint8_t** buffer) const override;

	uint8_t get_index() const {
		return index;
	}
private:
	uint8_t index;
};

class LocalVarTarget : public TypeTarget{
public:
	struct Entry {
		Instruction* start;
		Instruction* end;
		uint16_t index;
	};

	LocalVarTarget(uint8_t type, Code* code, std::vector<Entry> entries,
	               std::unique_ptr<TypePath> path)
	: TypeTarget(Kind::LocalVar, type, std::move(path)),
	  code(code), entries(std::move(entries)) {}

	virtual uint32_t get_byte_size() const override;
	virtual void write_buffer(uint8_t** buffer) const override;

private:
	Code* code;
	std::vector<Entry> entries;
};

class TypeAnnotation {
public:
	TypeAnnotation(const uint8_t** buffer, ConstantPool* constant_pool);
	TypeAnnotation(const uint8_t** buffer, Field* field);
	TypeAnnotation(const uint8_t** buffer, Method* method);
	TypeAnnotation(const uint8_t** buffer, Code* code);
	~TypeAnnotation();

	uint32_t get_byte_size() const;
	void write_buffer(uint8_t** buffer) const;

	TypeTarget* get_target() const {
		return target.get();
	}
	uint16_t get_type_index() const {
		return type_index;
	}
	ElementValuePairs* get_element_value_pairs() const {
		return element_value_pairs.get();
	}
private:
	std::unique_ptr<TypeTarget> target;
	uint16_t type_index;
	std::unique_ptr<ElementValuePairs> element_value_pairs;
};

}

#endif
