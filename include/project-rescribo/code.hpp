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

#ifndef PROJECT_RESCRIBO_CODE_HPP
#define PROJECT_RESCRIBO_CODE_HPP

#include <cstdint>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

#include "attribute.hpp"
#include "attributes.hpp"
#include "instruction.hpp"

namespace project_rescribo {

class Attributes;
class BranchInstruction;
class LineNumberTable;
class LookupSwitch;
class Method;
class StackMapTable;
class TableSwitch;

class Code : public Attribute {
public:
	struct ExceptionTableEntry {
		Instruction* start;
		Instruction* end;
		Instruction* handler;
		uint16_t catch_type;
	};

	Code(const uint8_t** buffer, uint16_t attribute_name_index, Method* method);
	Code(Method* method);

	static bool classof(const Attribute* attribute) {
		return attribute->get_kind() == Kind::Code;
	}

	Method* get_method() const {
		return method;
	}
	ClassFile* get_class_file() const;
	ConstantPool* get_constant_pool() const;

	uint32_t get_next_bci() const {
		return next_bci;
	}

	Instruction* get_instruction(uint32_t bci) const;

	virtual uint32_t get_byte_size() const {
		return 18 + next_bci +
		       attributes->get_byte_size() +
		       8 * exception_table.size();
	}

	uint16_t get_max_stack() const {
		return max_stack;
	}
	void set_max_stack(uint16_t v) {
		max_stack = v;
	}
	uint16_t get_max_locals() const {
		return max_locals;
	}
	void set_max_locals(uint16_t v) {
		max_locals = v;
	}

	virtual void write_buffer(uint8_t** buffer) const;
private:
	Method* method;
	LineNumberTable* line_number_table;
	StackMapTable* stack_map_table;

	uint16_t max_stack;
	uint16_t max_locals;
	typedef std::list<std::unique_ptr<Instruction>> Instructions;
	Instructions instructions;
	std::vector<ExceptionTableEntry> exception_table;
	std::unique_ptr<Attributes> attributes;

	uint32_t next_bci;
	std::unordered_map<uint32_t, Instruction*> instruction_map;

	void set_branch_target(BranchInstruction* branch);
	void set_lookup_switch_targets(LookupSwitch* lookup_switch);
	void set_table_switch_targets(TableSwitch* table_switch);

	void sync_instruction_bcis();
	void sync_branch_offset(BranchInstruction* branch);
	void sync_lookup_switch_offsets(LookupSwitch* lookup_switch);
	void sync_table_switch_offsets(TableSwitch* table_switch);
	void sync_instruction_offsets();

	void replace_targets(Instruction* old_target, Instruction* new_target);
	void replace_branch_targets(BranchInstruction* branch,
	                            Instruction* old_target,
	                            Instruction* new_target);
	void replace_lookup_switch_targets(LookupSwitch* lookup_switch,
	                                   Instruction* old_target,
	                                   Instruction* new_target);
	void replace_table_switch_targets(TableSwitch* table_switch,
	                                  Instruction* old_target,
	                                  Instruction* new_target);

	bool fix_branch_offsets(BranchInstruction* branch,
	                        Instructions::iterator iter);
	bool fix_lookup_switch_offsets(LookupSwitch* lookup_switch);
	bool fix_table_switch_offsets(TableSwitch* table_switch);

	Instructions::iterator get_objectref_top(
		Instructions::iterator iter,
		InvokeInstruction* invoke_instruction
	);

public:
	bool fix_offsets();
	void sync();

	class InstructionInserter {
	public:
		InstructionInserter(Code* code,
		                    Instructions::iterator insertion_point)
		: code(code), insertion_point(insertion_point) {}

		void insert_aaload();
		void insert_aastore();
		void insert_aconst_null();
		void insert_aload(uint8_t index);
		void insert_aload_0();
		void insert_aload_1();
		void insert_aload_2();
		void insert_aload_3();
		void insert_anewarray(uint16_t index);
		void insert_areturn();
		void insert_arraylength();
		void insert_astore(uint8_t index);
		void insert_astore_0();
		void insert_astore_1();
		void insert_astore_2();
		void insert_astore_3();
		void insert_athrow();
		void insert_baload();
		void insert_bastore();
		void insert_bipush(uint8_t value);
		void insert_caload();
		void insert_castore();
		void insert_checkcast(uint16_t index);
		void insert_d2f();
		void insert_d2i();
		void insert_d2l();
		void insert_dadd();
		void insert_daload();
		void insert_dastore();
		void insert_dup();
		void insert_dup_x1();
		void insert_dup_x2();
		void insert_dup2();
		void insert_dup2_x1();
		void insert_dup2_x2();
		void insert_getstatic(uint16_t index);
		void insert_goto_w(Instruction* target);
		void insert_iconst_0();
		void insert_iconst_1();
		void insert_ifeq(Instruction* target);
		void insert_invokestatic(uint16_t index);
		void insert_ldc(uint16_t index);
		void insert_nop();
		void insert_pop();
		void insert_putstatic(uint16_t index);
		void insert_return();
		void insert_sipush(uint16_t value);

		void insert_method_name_and_descriptor_ldc(
			InvokeInstruction* invoke_instruction
		);
		void insert_original_type_checkcast(
			InvokeInstruction* invoke_instruction
		);
	private:
		Code* code;
		Instructions::iterator insertion_point;
	};

	InstructionInserter create_front_inserter() {
		return InstructionInserter(this, instructions.begin());
	}
};

}

#endif
