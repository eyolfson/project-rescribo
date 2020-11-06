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

#ifndef PROJECT_RESCRIBO_STACK_MAP_TABLE_HPP
#define PROJECT_RESCRIBO_STACK_MAP_TABLE_HPP

#include "attribute.hpp"

#include <cstdint>
#include <memory>

namespace project_rescribo {

class Code;
class Instruction;
class StackMapTable;

class VariableInfo {
public:
	enum class Kind : uint8_t {
		Top = 0,
		Integer = 1,
		Float = 2,
		Double = 3,
		Long = 4,
		Null = 5,
		UninitializedThis = 6,
		Object = 7,
		Uninitialized = 8,
	};
	VariableInfo(Kind kind) : kind(kind) {}
	virtual ~VariableInfo() {}
	Kind get_kind() const {
		return kind;
	}

	virtual uint32_t get_byte_size() const = 0;
	virtual void write_buffer(uint8_t** buffer) const = 0;

	static std::unique_ptr<VariableInfo> make(const uint8_t** buffer,
	                                          Code* code);
private:
	Kind kind;
};

class TopVariableInfo : public VariableInfo {
public:
	TopVariableInfo() : VariableInfo(Kind::Top) {}

	static bool classof(const VariableInfo* variable_info) {
		return variable_info->get_kind() == Kind::Top;
	}

	virtual uint32_t get_byte_size() const override {
		return 1; // tag(1)
	}

	virtual void write_buffer(uint8_t** buffer) const override;
};

class IntegerVariableInfo : public VariableInfo {
public:
	IntegerVariableInfo() : VariableInfo(Kind::Integer) {}

	static bool classof(const VariableInfo* variable_info) {
		return variable_info->get_kind() == Kind::Integer;
	}

	virtual uint32_t get_byte_size() const override {
		return 1; // tag(1)
	}

	virtual void write_buffer(uint8_t** buffer) const override;
};

class FloatVariableInfo : public VariableInfo {
public:
	FloatVariableInfo() : VariableInfo(Kind::Float) {}

	static bool classof(const VariableInfo* variable_info) {
		return variable_info->get_kind() == Kind::Float;
	}

	virtual uint32_t get_byte_size() const override {
		return 1; // tag(1)
	}

	virtual void write_buffer(uint8_t** buffer) const override;
};

class DoubleVariableInfo : public VariableInfo {
public:
	DoubleVariableInfo() : VariableInfo(Kind::Double) {}

	static bool classof(const VariableInfo* variable_info) {
		return variable_info->get_kind() == Kind::Double;
	}

	virtual uint32_t get_byte_size() const override {
		return 1; // tag(1)
	}

	virtual void write_buffer(uint8_t** buffer) const override;
};

class LongVariableInfo : public VariableInfo {
public:
	LongVariableInfo() : VariableInfo(Kind::Long) {}

	static bool classof(const VariableInfo* variable_info) {
		return variable_info->get_kind() == Kind::Long;
	}

	virtual uint32_t get_byte_size() const override {
		return 1; // tag(1)
	}

	virtual void write_buffer(uint8_t** buffer) const override;
};

class NullVariableInfo : public VariableInfo {
public:
	NullVariableInfo() : VariableInfo(Kind::Null) {}

	static bool classof(const VariableInfo* variable_info) {
		return variable_info->get_kind() == Kind::Null;
	}

	virtual uint32_t get_byte_size() const override {
		return 1; // tag(1)
	}

	virtual void write_buffer(uint8_t** buffer) const override;
};

class UninitializedThisVariableInfo : public VariableInfo {
public:
	UninitializedThisVariableInfo()
	: VariableInfo(Kind::UninitializedThis) {}

	static bool classof(const VariableInfo* variable_info) {
		return variable_info->get_kind() == Kind::UninitializedThis;
	}

	virtual uint32_t get_byte_size() const override {
		return 1; // tag(1)
	}

	virtual void write_buffer(uint8_t** buffer) const override;
};

class ObjectVariableInfo : public VariableInfo {
public:
	ObjectVariableInfo(uint16_t index)
	: VariableInfo(Kind::Object), index(index) {}

	static bool classof(const VariableInfo* variable_info) {
		return variable_info->get_kind() == Kind::Object;
	}

	virtual uint32_t get_byte_size() const override {
		return 3; // tag(1) + cpool_index(2)
	}

	virtual void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class UninitializedVariableInfo : public VariableInfo {
public:
	UninitializedVariableInfo(Instruction* instruction)
	: VariableInfo(Kind::Uninitialized), instruction(instruction) {}

	static bool classof(const VariableInfo* variable_info) {
		return variable_info->get_kind() == Kind::Uninitialized;
	}

	virtual uint32_t get_byte_size() const override {
		return 3; // tag(1) + offset(2)
	}

	virtual void write_buffer(uint8_t** buffer) const override;

	uint16_t get_offset() const;
private:
	Instruction* instruction;
};

class StackMapFrame {
public:
	enum class Kind {
		Same,
		SameLocals1StackItem,
		SameLocals1StackItemExtended,
		Chop,
		SameFrameExtended,
		Append,
		FullFrame,
	};
	StackMapFrame(Kind kind, uint8_t type, StackMapTable* stack_map_table)
	: kind(kind), type(type), stack_map_table(stack_map_table) {}
	virtual ~StackMapFrame() {}
	Kind get_kind() const {
		return kind;
	}
	uint8_t get_type() const {
		return type;
	}
	StackMapTable* get_stack_map_table() const {
		return stack_map_table;
	}
	Instruction* get_instruction() const {
		return instruction;
	}
	void set_instruction(Instruction* i) {
		instruction = i;
	}
	virtual uint16_t get_offset_delta() const = 0;
	virtual void set_offset_delta(uint16_t o) = 0;
	virtual uint32_t get_byte_size() const = 0;
	virtual void write_buffer(uint8_t** buffer) const = 0;

	static std::unique_ptr<StackMapFrame> make(
		const uint8_t** buffer, StackMapTable* stack_map_table
	);
protected:
	void set_type(uint8_t t) {
		type = t;
	}
private:
	Kind kind;
	uint8_t type;
	StackMapTable* stack_map_table;

	Instruction* instruction;
};

class StackMapSame : public StackMapFrame {
public:
	StackMapSame(uint8_t type, StackMapTable* stack_map_table)
	: StackMapFrame(Kind::Same, type, stack_map_table) {}

	static bool classof(const StackMapFrame* stack_map_frame) {
		return stack_map_frame->get_kind() == Kind::Same;
	}

	uint16_t get_offset_delta() const override {
		return get_type();
	}
	bool is_valid(uint16_t o) {
		return o <= 63;
	}
	void set_offset_delta(uint16_t o) override;
	virtual uint32_t get_byte_size() const override {
		return 1; // frame_type(1)
	}

	virtual void write_buffer(uint8_t** buffer) const override;
};

class StackMapSameLocals1StackItem : public StackMapFrame {
public:
	StackMapSameLocals1StackItem(uint8_t type,
	                             StackMapTable* stack_map_table,
				     std::unique_ptr<VariableInfo> stack)
	: StackMapFrame(Kind::SameLocals1StackItem, type, stack_map_table),
	  stack(std::move(stack)) {}

	static bool classof(const StackMapFrame* stack_map_frame) {
		return stack_map_frame->get_kind()
		       == Kind::SameLocals1StackItem;
	}

	uint16_t get_offset_delta() const override {
		return get_type() - 64;
	}
	bool is_valid(uint16_t o) {
		return o <= 63;
	}
	void set_offset_delta(uint16_t o) override;
	virtual uint32_t get_byte_size() const override;

	std::unique_ptr<VariableInfo> move_stack() {
		return std::move(stack);
	}

	virtual void write_buffer(uint8_t** buffer) const override;

private:
	std::unique_ptr<VariableInfo> stack;
};

class StackMapSameLocals1StackItemExtended : public StackMapFrame {
public:
	StackMapSameLocals1StackItemExtended(
		uint8_t type,
		StackMapTable* stack_map_table,
		uint16_t offset_delta,
		std::unique_ptr<VariableInfo> stack)
	: StackMapFrame(Kind::SameLocals1StackItemExtended, type,
	                stack_map_table),
	  offset_delta(offset_delta),
	  stack(std::move(stack)) {}

	static bool classof(const StackMapFrame* stack_map_frame) {
		return stack_map_frame->get_kind()
	               == Kind::SameLocals1StackItemExtended;
	}

	uint16_t get_offset_delta() const override {
		return offset_delta;
	}
	void set_offset_delta(uint16_t o) override {
		offset_delta = o;
	}
	virtual uint32_t get_byte_size() const override;

	virtual void write_buffer(uint8_t** buffer) const override;

private:
	uint16_t offset_delta;
	std::unique_ptr<VariableInfo> stack;
};

class StackMapChop : public StackMapFrame {
public:
	StackMapChop(uint8_t type,
	             StackMapTable* stack_map_table,
	             uint16_t offset_delta)
	  : StackMapFrame(Kind::Chop, type, stack_map_table),
	    offset_delta(offset_delta) {}

	static bool classof(const StackMapFrame* stack_map_frame) {
		return stack_map_frame->get_kind() == Kind::Chop;
	}

	uint8_t get_k() const {
		return 251 - get_type();
	}
	uint16_t get_offset_delta() const override {
		return offset_delta;
	}
	void set_offset_delta(uint16_t o) override {
		offset_delta = o;
	}
	virtual uint32_t get_byte_size() const override {
		return 3; // frame_type(1) + offset_delta(2)
	}

	virtual void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t offset_delta;
};

class StackMapSameFrameExtended : public StackMapFrame {
public:
	StackMapSameFrameExtended(uint8_t type,
	                          StackMapTable* stack_map_table,
	                          uint16_t offset_delta)
	: StackMapFrame(Kind::SameFrameExtended, type, stack_map_table),
	  offset_delta(offset_delta) {}

	static bool classof(const StackMapFrame* stack_map_frame) {
		return stack_map_frame->get_kind() == Kind::SameFrameExtended;
	}

	uint16_t get_offset_delta() const override {
		return offset_delta;
	}
	void set_offset_delta(uint16_t o) override {
		offset_delta = o;
	}
	virtual uint32_t get_byte_size() const override {
		return 3;
	}
	virtual void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t offset_delta;
};

class StackMapAppend : public StackMapFrame {
public:
	StackMapAppend(uint8_t type,
	               StackMapTable* stack_map_table,
	               uint16_t offset_delta,
	               std::vector<std::unique_ptr<VariableInfo>> locals)
	  : StackMapFrame(Kind::Append, type, stack_map_table),
	    offset_delta(offset_delta),
	    locals(std::move(locals)) {}

	static bool classof(const StackMapFrame* stack_map_frame) {
		return stack_map_frame->get_kind() == Kind::Append;
	}

	uint16_t get_offset_delta() const override {
		return offset_delta;
	}
	void set_offset_delta(uint16_t o) override {
		offset_delta = o;
	}
	virtual uint32_t get_byte_size() const override;
	virtual void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t offset_delta;
	std::vector<std::unique_ptr<VariableInfo>> locals;
};

class StackMapFullFrame : public StackMapFrame {
public:
	StackMapFullFrame(
		uint8_t type,
		StackMapTable* stack_map_table,
		uint16_t offset_delta,
		std::vector<std::unique_ptr<VariableInfo>> locals,
		std::vector<std::unique_ptr<VariableInfo>> stack_items
	)
	: StackMapFrame(Kind::FullFrame, type, stack_map_table),
	  offset_delta(offset_delta),
	  locals(std::move(locals)),
	  stack_items(std::move(stack_items)) {}

	static bool classof(const StackMapFrame* stack_map_frame) {
		return stack_map_frame->get_kind() == Kind::FullFrame;
	}

	uint16_t get_offset_delta() const override {
		return offset_delta;
	}
	void set_offset_delta(uint16_t o) override {
		offset_delta = o;
	}
	virtual uint32_t get_byte_size() const override;
	virtual void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t offset_delta;
	std::vector<std::unique_ptr<VariableInfo>> locals;
	std::vector<std::unique_ptr<VariableInfo>> stack_items;
};

class StackMapTable : public Attribute {
public:
	StackMapTable(const uint8_t** buffer,
	              uint16_t attribute_name_index,
	              Code* code);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::StackMapTable;
	}

	Code* get_code() const {
		return code;
	}

	StackMapFrame* get_stack_frame_at(Instruction* instruction) const;

	virtual uint32_t get_byte_size() const override;
	virtual void write_buffer(uint8_t** buffer) const override;

	void sync_offset_delta();
private:
	Code* code;
	std::vector<std::unique_ptr<StackMapFrame>> entries;
};

}

#endif
