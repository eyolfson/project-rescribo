#include "code.hpp"

#include "attribute.hpp"
#include "buffer.hpp"
#include "casting.hpp"
#include "class_file.hpp"
#include "constant_pool.hpp"
#include "instruction.hpp"
#include "method.hpp"
#include "stack_map_table.hpp"

#include <cassert>

using namespace project_rescribo;

Code::Code(const uint8_t** buffer,
           uint16_t attribute_name_index,
           Method* method)
: Attribute(Kind::Code, attribute_name_index), method(method),
  line_number_table(nullptr), stack_map_table(nullptr) {
	max_stack = next_u16(buffer);
	max_locals = next_u16(buffer);

	uint32_t bci = 0;
	uint32_t code_length = next_u32(buffer);
	const uint8_t* code_start = *buffer;
	while ((*buffer - code_start) != code_length) {
		instructions.push_back(Instruction::make(buffer, this));
		assert(instructions.back() != nullptr);
		instructions.back()->set_bci(bci);
		instruction_map.insert({bci, instructions.back().get()});
		assert(instructions.back()->get_byte_size() != 0);
		bci += instructions.back()->get_byte_size();
		next_bci = bci; // Needed to calculate lookup / table switch
	}
	assert(next_bci <= INT32_MAX);
	for (const auto& instruction : instructions) {
		if (BranchInstruction* branch
		    = dyn_cast<BranchInstruction>(instruction.get())) {
			set_branch_target(branch);
		}
		else if (LookupSwitch* lookup_switch
		         = dyn_cast<LookupSwitch>(instruction.get())) {
			set_lookup_switch_targets(lookup_switch);
		}
		else if (TableSwitch* table_switch
		         = dyn_cast<TableSwitch>(instruction.get())) {
			set_table_switch_targets(table_switch);
		}
	}

	uint16_t exception_table_length = next_u16(buffer);
	for (uint32_t i = 0; i < exception_table_length; ++i) {
		uint16_t start_pc = next_u16(buffer);
		Instruction* start = get_instruction(start_pc);
		uint16_t end_pc = next_u16(buffer);
		Instruction* end = nullptr;
		if (end_pc != next_bci) {
			end = get_instruction(end_pc);
		}
		uint16_t handler_pc = next_u16(buffer);
		Instruction* handler = get_instruction(handler_pc);
		uint16_t catch_type = next_u16(buffer);
		exception_table.push_back({start, end, handler, catch_type});
	}
	uint16_t attributes_count = next_u16(buffer);
	attributes = std::make_unique<Attributes>(buffer,
	                                          attributes_count,
	                                          this);

	for (auto&& attribute : attributes->get()) {
		if (LineNumberTable* lnt =
		    dyn_cast<LineNumberTable>(attribute.get())) {
			assert(line_number_table == nullptr);
			line_number_table = lnt;
		}
		if (StackMapTable* smt =
		         dyn_cast<StackMapTable>(attribute.get())) {
			assert(stack_map_table == nullptr);
			stack_map_table = smt;
		}
	}
}

Code::Code(Method* method)
: Attribute(Kind::Code, 0), method(method),
  line_number_table(nullptr), stack_map_table(nullptr) {
	ConstantPool* constant_pool = get_constant_pool();
	set_attribute_name_index(
		constant_pool->get_or_create_utf8_index("Code")
	);
	max_stack = 0;
	max_locals = 0;
	attributes = std::make_unique<Attributes>();

	InstructionInserter inserter(this, instructions.end());
	inserter.insert_return();
	sync();
}

void Code::set_branch_target(BranchInstruction* branch) {
	Instruction* target = get_instruction(branch->get_bci()
	                                      + branch->get_offset());
	branch->set_target(target);
}

void Code::set_lookup_switch_targets(LookupSwitch* lookup_switch) {
	uint32_t bci = lookup_switch->get_bci();
	Instruction* default_target = get_instruction(
		bci + lookup_switch->get_default_offset()
	);
	lookup_switch->set_default_target(default_target);
	for (int32_t offset : lookup_switch->get_offsets()) {
		Instruction* target = get_instruction(bci + offset);
		lookup_switch->push_back_target(target);
	}
}

void Code::set_table_switch_targets(TableSwitch* table_switch) {
	uint32_t bci = table_switch->get_bci();
	Instruction* default_target = get_instruction(
		bci + table_switch->get_default_offset()
	);
	table_switch->set_default_target(default_target);
	for (int32_t offset : table_switch->get_offsets()) {
		Instruction* target = get_instruction(bci + offset);
		table_switch->push_back_target(target);
	}
}

ClassFile* Code::get_class_file() const {
	return method->get_class_file();
}

ConstantPool* Code::get_constant_pool() const {
	return get_class_file()->get_constant_pool();
}

Instruction* Code::get_instruction(uint32_t bci) const {
	assert(instruction_map.count(bci));
	return instruction_map.at(bci);
}

void Code::sync_instruction_bcis() {
	uint32_t bci = 0;
	instruction_map.clear();
	for (const auto& instruction : instructions) {
		instruction->set_bci(bci);
		instruction_map.insert({bci, instruction.get()});
		if (LookupSwitch* lookup_switch
		    = dyn_cast<LookupSwitch>(instruction.get())) {
			uint8_t padding = 3 - (bci % 4);
			lookup_switch->set_padding(padding);
		}
		else if (TableSwitch* table_switch
		         = dyn_cast<TableSwitch>(instruction.get())) {
			uint8_t padding = 3 - (bci % 4);
			table_switch->set_padding(padding);
		}
		bci += instruction->get_byte_size();
	}
	next_bci = bci;
}

void Code::sync_branch_offset(BranchInstruction* branch) {
	branch->set_offset(branch->get_target()->get_bci()
	                   - branch->get_bci());
}

void Code::sync_lookup_switch_offsets(LookupSwitch* lookup_switch) {
	uint32_t bci = lookup_switch->get_bci();
	lookup_switch->set_default_offset(
		lookup_switch->get_default_target()->get_bci() - bci
	);

	lookup_switch->clear_offsets();
	for (Instruction* target : lookup_switch->get_targets()) {
		lookup_switch->push_back_offset(target->get_bci() - bci);
	}
}

void Code::sync_table_switch_offsets(TableSwitch* table_switch) {
	uint32_t bci = table_switch->get_bci();
	table_switch->set_default_offset(
		table_switch->get_default_target()->get_bci() - bci
	);

	table_switch->clear_offsets();
	for (Instruction* target : table_switch->get_targets()) {
		table_switch->push_back_offset(target->get_bci() - bci);
	}
}

void Code::sync_instruction_offsets() {
	for (const auto& instruction : instructions) {
		if (BranchInstruction* branch
		    = dyn_cast<BranchInstruction>(instruction.get())) {
			sync_branch_offset(branch);
		}
		else if (LookupSwitch* lookup_switch
		         = dyn_cast<LookupSwitch>(instruction.get())) {
			sync_lookup_switch_offsets(lookup_switch);
		}
		else if (TableSwitch* table_switch
		         = dyn_cast<TableSwitch>(instruction.get())) {
			sync_table_switch_offsets(table_switch);
		}
	}
}

void Code::replace_branch_targets(BranchInstruction* branch,
                                  Instruction* old_target,
                                  Instruction* new_target) {
	if (branch->get_target() == old_target) {
		branch->set_target(new_target);
	}
}

void Code::replace_lookup_switch_targets(LookupSwitch* lookup_switch,
                                         Instruction* old_target,
                                         Instruction* new_target) {
	if (lookup_switch->get_default_target() == old_target) {
		lookup_switch->set_default_target(new_target);
	}
	for (auto& target : lookup_switch->get_targets()) {
		if (target == old_target) {
			target = new_target;
		}
	}
}

void Code::replace_table_switch_targets(TableSwitch* table_switch,
                                        Instruction* old_target,
                                        Instruction* new_target) {
	if (table_switch->get_default_target() == old_target) {
		table_switch->set_default_target(new_target);
	}
	for (auto& target : table_switch->get_targets()) {
		if (target == old_target) {
			target = new_target;
		}
	}
}

void Code::replace_targets(Instruction* old_target, Instruction* new_target) {
	for (auto& entry : exception_table) {
		if (entry.handler == old_target) {
			entry.handler = new_target;
		}
	}

	for (const auto& instruction : instructions) {
		if (BranchInstruction* branch
		    = dyn_cast<BranchInstruction>(instruction.get())) {
			replace_branch_targets(branch, old_target, new_target);
		}
		else if (LookupSwitch* lookup_switch
		         = dyn_cast<LookupSwitch>(instruction.get())) {
			replace_lookup_switch_targets(lookup_switch,
			                              old_target,
			                              new_target);
		}
		else if (TableSwitch* table_switch
		         = dyn_cast<TableSwitch>(instruction.get())) {
			replace_table_switch_targets(table_switch,
			                             old_target,
			                             new_target);
		}
	}

	if (stack_map_table) {
		StackMapFrame* target_frame = stack_map_table
		                              ->get_stack_frame_at(old_target);
		if (target_frame
		    && target_frame->get_instruction() == old_target) {
			target_frame->set_instruction(new_target);
		}
	}

}

Code::Instructions::iterator Code::get_objectref_top(
	Instructions::iterator iter,
	InvokeInstruction* invoke_instruction
) {
	uint16_t num_args = invoke_instruction->get_num_args();
	int16_t stack_target = num_args;
	while (stack_target != 0) {
		--iter;
		Instruction* instruction = iter->get();
		/* TODO: Investigate this, as we're missing instrumentation */
		if (isa<AThrow>(instruction)) {
			return instructions.end();
		}
		else if (isa<BranchInstruction>(instruction)) {
			return instructions.end();
		}
		else if (isa<Dup_X1>(instruction)) {
			return instructions.end();
		}
		else if (isa<Dup_X2>(instruction)) {
			return instructions.end();
		}
		else if (isa<Dup2_X1>(instruction)) {
			return instructions.end();
		}
		else if (isa<Dup2_X2>(instruction)) {
			return instructions.end();
		}
		else if (isa<LookupSwitch>(instruction)) {
			return instructions.end();
		}
		else if (isa<Swap>(instruction)) {
			return instructions.end();
		}
		else if (isa<TableSwitch>(instruction)) {
			return instructions.end();
		}
		stack_target -= instruction->get_stack_delta();
	}
	return iter;
}

void Code::InstructionInserter::insert_aload_0() {
	auto instruction = std::make_unique<ALoad_0>(code);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_aload_1() {
	auto instruction = std::make_unique<ALoad_1>(code);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_aload_2() {
	auto instruction = std::make_unique<ALoad_2>(code);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_aload_3() {
	auto instruction = std::make_unique<ALoad_3>(code);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_checkcast(uint16_t index) {
	auto instruction = std::make_unique<CheckCast>(code, index);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_dup() {
	auto instruction = std::make_unique<Dup>(code);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_getstatic(uint16_t index) {
	auto instruction = std::make_unique<GetStatic>(code, index);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_goto_w(Instruction* target) {
	auto instruction = std::make_unique<Goto_W>(code, target);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_iconst_0() {
	auto instruction = std::make_unique<IConst_0>(code);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_iconst_1() {
	auto instruction = std::make_unique<IConst_1>(code);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_ifeq(Instruction* target) {
	auto instruction = std::make_unique<IfEq>(code, target);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_invokestatic(uint16_t index) {
	auto instruction = std::make_unique<InvokeStatic>(code, index);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_ldc(uint16_t index) {
	auto instruction = std::make_unique<Ldc_W>(code, index);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_nop() {
	auto instruction = std::make_unique<Nop>(code);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_pop() {
	auto instruction = std::make_unique<Pop>(code);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_putstatic(uint16_t index) {
	auto instruction = std::make_unique<PutStatic>(code, index);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_return() {
	auto instruction = std::make_unique<Return>(code);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_sipush(uint16_t value) {
	auto instruction = std::make_unique<SIPush>(code, value);
	code->instructions.insert(insertion_point, std::move(instruction));
}

void Code::InstructionInserter::insert_method_name_and_descriptor_ldc(
	InvokeInstruction* invoke_instruction
) {
	ConstantPool* constant_pool = code->get_constant_pool();

	uint16_t ref_index = invoke_instruction->get_index();
	auto ref = cast<ConstantPoolRef>(constant_pool->get_entry(ref_index));
	uint16_t name_and_type_index = ref->get_name_and_type_index();
	auto name_and_type = cast<ConstantPoolNameAndType>(
		constant_pool->get_entry(name_and_type_index)
	);
	uint16_t name_index = constant_pool->get_or_create_string_index(
		name_and_type->get_name_index()
	);
	uint16_t descriptor_index = constant_pool->get_or_create_string_index(
		name_and_type->get_descriptor_index()
	);

	insert_ldc(name_index);
	insert_ldc(descriptor_index);
}

void Code::InstructionInserter::insert_original_type_checkcast(
	InvokeInstruction* invoke_instruction
) {
	ConstantPool* constant_pool = code->get_constant_pool();

	uint16_t ref_index = invoke_instruction->get_index();
	auto ref = cast<ConstantPoolRef>(constant_pool->get_entry(ref_index));

	insert_checkcast(ref->get_class_index());
}

void Code::sync() {
	sync_instruction_bcis();
	sync_instruction_offsets();
	if (stack_map_table) {
		stack_map_table->sync_offset_delta();
	}
}

bool Code::fix_offsets() {
	bool fixed = false;
	for (auto iter = instructions.begin();
	     iter != instructions.end();
	     ++iter) {
		Instruction* instruction = iter->get();
		if (BranchInstruction* branch
		    = dyn_cast<BranchInstruction>(instruction)) {
		  fixed = fixed || fix_branch_offsets(branch, iter);
		}
		else if (LookupSwitch* lookup_switch
		         = dyn_cast<LookupSwitch>(instruction)) {
			fixed = fixed
			        || fix_lookup_switch_offsets(lookup_switch);
		}
		else if (TableSwitch* table_switch
		         = dyn_cast<TableSwitch>(instruction)) {
			fixed = fixed || fix_table_switch_offsets(table_switch);
		}
	}
	return fixed;
}

bool Code::fix_branch_offsets(BranchInstruction* branch,
                              Instructions::iterator iter) {
	if (!branch->is_invalid_offset()) {
		return false;
	}

	if (Goto* goto_instruction = dyn_cast<Goto>(branch)) {
		goto_instruction->extend();
	}
	else if (If_ICmpNe* icmpne = dyn_cast<If_ICmpNe>(branch)) {
		Instruction* target = icmpne->get_target();

		auto insertion_point = std::next(iter);
		Instruction* new_target = insertion_point->get();

		InstructionInserter inserter(this, insertion_point);
		inserter.insert_goto_w(target);

		icmpne->invert();
		icmpne->set_target(new_target);

		assert(false && "Unimplemented analysis for fix branch offset");
	}
	else {
		assert(false && "Unknown fix branch offset");
	}
	return true;
}

bool Code::fix_lookup_switch_offsets(LookupSwitch* lookup_switch) {
	return false;
}

bool Code::fix_table_switch_offsets(TableSwitch* table_switch) {
	return false;
}

void Code::write_buffer(uint8_t** buffer) const {
	next_u16(buffer, get_attribute_name_index());

	// attribute len not including first 6 bytes
	uint32_t len = 12 + next_bci + 8 * exception_table.size()
		       + attributes->get_byte_size();
	next_u32(buffer, len);
	next_u16(buffer, max_stack);
	next_u16(buffer, max_locals);

	next_u32(buffer, next_bci); // code_length
	for (const auto& insn : instructions) {
		insn->write_buffer(buffer);
	}

	next_u16(buffer, exception_table.size());
	for (const auto& entry : exception_table) {
		next_u16(buffer, entry.start->get_bci());
		if (entry.end)  {
			next_u16(buffer, entry.end->get_bci());
		}
		else {
			next_u16(buffer, next_bci);
		}
		next_u16(buffer, entry.handler->get_bci());
		next_u16(buffer, entry.catch_type);
	}

	attributes->write_buffer(buffer);
}
