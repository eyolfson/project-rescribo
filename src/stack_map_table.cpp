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

#include "stack_map_table.hpp"

#include "buffer.hpp"
#include "casting.hpp"
#include "code.hpp"

#include <cassert>

using namespace project_rescribo;

std::unique_ptr<VariableInfo> VariableInfo::make(const uint8_t** buffer,
                                                 Code* code) {
	switch (Kind(next_u8(buffer))) {
	case Kind::Top: {
		return std::make_unique<TopVariableInfo>();
	}
	case Kind::Integer: {
		return std::make_unique<IntegerVariableInfo>();
	}
	case Kind::Float: {
		return std::make_unique<FloatVariableInfo>();
	}
	case Kind::Double: {
		return std::make_unique<DoubleVariableInfo>();
	}
	case Kind::Long: {
		return std::make_unique<LongVariableInfo>();
	}
	case Kind::Null: {
		return std::make_unique<NullVariableInfo>();
	}
	case Kind::UninitializedThis: {
		return std::make_unique<UninitializedThisVariableInfo>();
	}
	case Kind::Object: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<ObjectVariableInfo>(index);
	}
	case Kind::Uninitialized: {
		uint16_t offset = next_u16(buffer);
		Instruction* instruction = code->get_instruction(offset);
		return std::make_unique<UninitializedVariableInfo>(instruction);
	}
	default:
		assert(false && "Unexpected variable info");
	}
}

void TopVariableInfo::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IntegerVariableInfo::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FloatVariableInfo::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DoubleVariableInfo::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LongVariableInfo::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void NullVariableInfo::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void UninitializedThisVariableInfo::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void ObjectVariableInfo::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, index);
}

uint16_t UninitializedVariableInfo::get_offset() const {
	return instruction->get_bci();
}

void UninitializedVariableInfo::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

std::unique_ptr<StackMapFrame>
StackMapFrame::make(const uint8_t** buffer, StackMapTable* stack_map_table) {
	uint8_t type = next_u8(buffer);
	if (type <= 63) {
		return std::make_unique<StackMapSame>(type, stack_map_table);
	}
	else if (type <= 127) {
		std::unique_ptr<VariableInfo> stack
		= VariableInfo::make(buffer, stack_map_table->get_code());
		return std::make_unique<StackMapSameLocals1StackItem>(
			type, stack_map_table, std::move(stack)
		);
	}
	else if (type <= 246) {
		assert(false && "Unimplemented");
		return nullptr;
	}
	else if (type == 247) {
		uint16_t offset_delta = next_u16(buffer);
		std::unique_ptr<VariableInfo> stack
		= VariableInfo::make(buffer, stack_map_table->get_code());
		return std::make_unique<StackMapSameLocals1StackItemExtended>(
			type, stack_map_table, offset_delta, std::move(stack)
		);
	}
	else if (type <= 250) {
		uint16_t offset_delta = next_u16(buffer);
		return std::make_unique<StackMapChop>(type,
		                                      stack_map_table,
		                                      offset_delta);
	}
	else if (type == 251) {
		uint16_t offset_delta = next_u16(buffer);
		return std::make_unique<StackMapSameFrameExtended>(
			type, stack_map_table, offset_delta
		);
	}
	else if (type <= 254) {
		uint16_t offset_delta = next_u16(buffer);
		std::vector<std::unique_ptr<VariableInfo>> locals;
		for (uint32_t i = 0; i < (type - 251u); ++i) {
			locals.push_back(
				VariableInfo::make(buffer,
				                   stack_map_table->get_code())
			);
		}
		return std::make_unique<StackMapAppend>(type,
		                                        stack_map_table,
		                                        offset_delta,
		                                        std::move(locals));
	}
	else /* (type == 255) */ {
		uint16_t offset_delta = next_u16(buffer);
		uint16_t number_of_locals = next_u16(buffer);
		std::vector<std::unique_ptr<VariableInfo>> locals;
		for (uint32_t i = 0; i < number_of_locals; ++i) {
			locals.push_back(
				VariableInfo::make(buffer,
				                   stack_map_table->get_code())
			);
		}
		uint16_t number_of_stack_items = next_u16(buffer);
		std::vector<std::unique_ptr<VariableInfo>> stack_items;
		for (uint32_t i = 0; i < number_of_stack_items; ++i) {
			stack_items.push_back(
				VariableInfo::make(buffer,
				                   stack_map_table->get_code())
			);
		}
		return std::make_unique<StackMapFullFrame>(
			type,
			stack_map_table,
			offset_delta,
			std::move(locals),
			std::move(stack_items)
		);
	}
}

StackMapTable::StackMapTable(const uint8_t** buffer,
                             uint16_t attribute_name_index,
                             Code* code)
: Attribute(Kind::StackMapTable, attribute_name_index), code(code) {
	uint16_t number_of_entries = next_u16(buffer);
	for (uint64_t i = 0; i < number_of_entries; ++i) {
		entries.push_back(StackMapFrame::make(buffer, this));
	}

	/* Set the instructions for all the frames */
	uint32_t bci = 0;
	bool previous_frame_is_initial = true;
	for (const auto& entry : entries) {
		StackMapFrame* frame = entry.get();

		if (previous_frame_is_initial) {
			bci += frame->get_offset_delta();
		}
		else {
			bci += frame->get_offset_delta() + 1;
		}

		Instruction* instruction = code->get_instruction(bci);
		frame->set_instruction(instruction);

		if (previous_frame_is_initial) {
			previous_frame_is_initial = false;
		}
	}
}

void StackMapSame::set_offset_delta(uint16_t o) {
	assert(o <= 63);
	set_type(o);
}

void StackMapSame::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_type());
}

void StackMapSameLocals1StackItem::set_offset_delta(uint16_t o) {
	assert(o <= 63);
	set_type(o + 64);
}

uint32_t StackMapSameLocals1StackItem::get_byte_size() const {
	uint32_t result = 1;
	result += stack->get_byte_size();
	return result;
}

void StackMapSameLocals1StackItem::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_type());
	stack->write_buffer(buffer);
}

uint32_t StackMapSameLocals1StackItemExtended::get_byte_size() const {
	uint32_t result = 3;
	result += stack->get_byte_size();
	return result;
}

void StackMapSameLocals1StackItemExtended::write_buffer(
	uint8_t** buffer
) const {
	next_u8(buffer, get_type());
	next_u16(buffer, offset_delta);
	stack->write_buffer(buffer);
}

void StackMapChop::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_type());
	next_u16(buffer, offset_delta);
}

void StackMapSameFrameExtended::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_type());
	next_u16(buffer, offset_delta);
}

uint32_t StackMapAppend::get_byte_size() const {
	uint32_t result = 3; // frame_type(1) + offset_delta(2) + locals
	for (const auto& l : locals) {
		result += l->get_byte_size();
	}
	return result;
}

void StackMapAppend::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_type());
	next_u16(buffer, offset_delta);
	for (const auto& var_info : locals) {
		var_info->write_buffer(buffer);
	}
}

uint32_t StackMapFullFrame::get_byte_size() const {
	// frame_type(1) + offset_delta(2) + number of locals(2) +
	// locals + num_stack_items(2) + stack_items
	uint32_t result = 7;

	for (const auto& l : locals) {
		result += l->get_byte_size();
	}
	for (const auto& item : stack_items) {
		result += item->get_byte_size();
	}

	return result;
}

void StackMapFullFrame::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, get_type());
	next_u16(buffer, offset_delta);
	next_u16(buffer, locals.size());
	for (const auto& var_info : locals) {
		var_info->write_buffer(buffer);
	}
	next_u16(buffer, stack_items.size());
	for (const auto& item : stack_items) {
		item->write_buffer(buffer);
	}
}

StackMapFrame*
StackMapTable::get_stack_frame_at(Instruction* instruction) const {
	for (const auto& frame : entries) {
		if (frame->get_instruction() == instruction) {
			return frame.get();
		}
	}
	return nullptr;
}

uint32_t StackMapTable::get_byte_size() const {
	uint32_t result = 0;
	result += 8;
	for (const auto& entry : entries) {
		result += entry->get_byte_size();
	}
	return result;
}

void StackMapTable::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());

	// length not including the first 6 bytes
	uint32_t len = 2;
	for (const auto& frame : entries) {
		len += frame->get_byte_size();
	}
	next_u32(buffer, len);

	next_u16(buffer, entries.size());
	for (const auto& frame : entries) {
		frame->write_buffer(buffer);
	}
}

void StackMapTable::sync_offset_delta() {
	bool previous_frame_is_initial = true;
	uint32_t previous_bci = 0;
	for (auto& entry : entries) {
		StackMapFrame* frame = entry.get();
		assert(frame->get_instruction());

		uint32_t bci = frame->get_instruction()->get_bci();
		uint16_t new_offset_delta = bci - previous_bci;
		if (!previous_frame_is_initial) {
			new_offset_delta -= 1;
		}

		StackMapSame* same = dyn_cast<StackMapSame>(frame);
		StackMapSameLocals1StackItem* same_locals
			= dyn_cast<StackMapSameLocals1StackItem>(frame);
		if (same && !same->is_valid(new_offset_delta)) {
			Instruction* target = frame->get_instruction();
			entry = std::make_unique<StackMapSameFrameExtended>(
				251, this, new_offset_delta
			);
			entry->set_instruction(target);
		}
		else if (same_locals
		         && !same_locals->is_valid(new_offset_delta)) {
			std::unique_ptr<VariableInfo> stack
				= same_locals->move_stack();
			Instruction* target = frame->get_instruction();
			entry = std::make_unique<
				StackMapSameLocals1StackItemExtended>(
					247, this, new_offset_delta,
					std::move(stack)
				);
			entry->set_instruction(target);
		}
		else {
			frame->set_offset_delta(new_offset_delta);
		}

		if (previous_frame_is_initial) {
			previous_frame_is_initial = false;
		}
		previous_bci = bci;
	}
}
