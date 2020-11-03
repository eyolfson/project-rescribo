#include "instruction.hpp"

#include "buffer.hpp"
#include "casting.hpp"
#include "class_file.hpp"
#include "code.hpp"
#include "constant_pool.hpp"
#include "method.hpp"

#include <cassert>

using namespace project_totus;

// https://docs.oracle.com/javase/specs/jvms/se11/html/jvms-6.html
std::unique_ptr<Instruction> Instruction::make(const uint8_t** buffer,
                                               Code* code) {
	switch (Kind(next_u8(buffer))) {
	case Kind::Nop: {
		return std::make_unique<Nop>(code);
	}
	case Kind::AConst_Null: {
		return std::make_unique<AConst_Null>(code);
	}
	case Kind::IConst_M1: {
		return std::make_unique<IConst_M1>(code);
	}
	case Kind::IConst_0: {
		return std::make_unique<IConst_0>(code);
	}
	case Kind::IConst_1: {
		return std::make_unique<IConst_1>(code);
	}
	case Kind::IConst_2: {
		return std::make_unique<IConst_2>(code);
	}
	case Kind::IConst_3: {
		return std::make_unique<IConst_3>(code);
	}
	case Kind::IConst_4: {
		return std::make_unique<IConst_4>(code);
	}
	case Kind::IConst_5: {
		return std::make_unique<IConst_5>(code);
	}
	case Kind::LConst_0: {
		return std::make_unique<LConst_0>(code);
	}
	case Kind::LConst_1: {
		return std::make_unique<LConst_1>(code);
	}
	case Kind::FConst_0: {
		return std::make_unique<FConst_0>(code);
	}
	case Kind::FConst_1: {
		return std::make_unique<FConst_1>(code);
	}
	case Kind::FConst_2: {
		return std::make_unique<FConst_2>(code);
	}
	case Kind::DConst_0: {
		return std::make_unique<DConst_0>(code);
	}
	case Kind::DConst_1: {
		return std::make_unique<DConst_1>(code);
	}
	case Kind::BIPush : {
		uint8_t value = next_u8(buffer);
		return std::make_unique<BIPush>(code, value);
	}
	case Kind::SIPush : {
		uint16_t value = next_u16(buffer);
		return std::make_unique<SIPush>(code, value);
	}
	case Kind::Ldc: {
		uint8_t index = next_u8(buffer);
		return std::make_unique<Ldc>(code, index);
	}
	case Kind::Ldc_W: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<Ldc_W>(code, index);
	}
	case Kind::Ldc2_W: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<Ldc2_W>(code, index);
	}
	case Kind::ILoad: {
		uint8_t index = next_u8(buffer);
		return std::make_unique<ILoad>(code, index);
	}
	case Kind::LLoad: {
		uint8_t index = next_u8(buffer);
		return std::make_unique<LLoad>(code, index);
	}
	case Kind::FLoad: {
		uint8_t index = next_u8(buffer);
		return std::make_unique<FLoad>(code, index);
	}
	case Kind::DLoad: {
		uint8_t index = next_u8(buffer);
		return std::make_unique<DLoad>(code, index);
	}
	case Kind::ALoad: {
		uint8_t index = next_u8(buffer);
		return std::make_unique<ALoad>(code, index);
	}
	case Kind::ILoad_0: {
		return std::make_unique<ILoad_0>(code);
	}
	case Kind::ILoad_1: {
		return std::make_unique<ILoad_1>(code);
	}
	case Kind::ILoad_2: {
		return std::make_unique<ILoad_2>(code);
	}
	case Kind::ILoad_3: {
		return std::make_unique<ILoad_3>(code);
	}
	case Kind::LLoad_0: {
		return std::make_unique<LLoad_0>(code);
	}
	case Kind::LLoad_1: {
		return std::make_unique<LLoad_1>(code);
	}
	case Kind::LLoad_2: {
		return std::make_unique<LLoad_2>(code);
	}
	case Kind::LLoad_3: {
		return std::make_unique<LLoad_3>(code);
	}
	case Kind::FLoad_0: {
		return std::make_unique<FLoad_0>(code);
	}
	case Kind::FLoad_1: {
		return std::make_unique<FLoad_1>(code);
	}
	case Kind::FLoad_2: {
		return std::make_unique<FLoad_2>(code);
	}
	case Kind::FLoad_3: {
		return std::make_unique<FLoad_3>(code);
	}
	case Kind::DLoad_0: {
		return std::make_unique<DLoad_0>(code);
	}
	case Kind::DLoad_1: {
		return std::make_unique<DLoad_1>(code);
	}
	case Kind::DLoad_2: {
		return std::make_unique<DLoad_2>(code);
	}
	case Kind::DLoad_3: {
		return std::make_unique<DLoad_3>(code);
	}
	case Kind::ALoad_0: {
		return std::make_unique<ALoad_0>(code);
	}
	case Kind::ALoad_1: {
		return std::make_unique<ALoad_1>(code);
	}
	case Kind::ALoad_2: {
		return std::make_unique<ALoad_2>(code);
	}
	case Kind::ALoad_3: {
		return std::make_unique<ALoad_3>(code);
	}
	case Kind::IALoad: {
		return std::make_unique<IALoad>(code);
	}
	case Kind::LALoad: {
		return std::make_unique<LALoad>(code);
	}
	case Kind::FALoad: {
		return std::make_unique<FALoad>(code);
	}
	case Kind::DALoad: {
		return std::make_unique<DALoad>(code);
	}
	case Kind::AALoad: {
		return std::make_unique<AALoad>(code);
	}
	case Kind::BALoad: {
		return std::make_unique<BALoad>(code);
	}
	case Kind::CALoad: {
		return std::make_unique<CALoad>(code);
	}
	case Kind::SALoad: {
		return std::make_unique<SALoad>(code);
	}
	case Kind::IStore: {
		uint8_t index = next_u8(buffer);
		return std::make_unique<IStore>(code, index);
	}
	case Kind::LStore: {
		uint8_t index = next_u8(buffer);
		return std::make_unique<LStore>(code, index);
	}
	case Kind::FStore: {
		uint8_t index = next_u8(buffer);
		return std::make_unique<FStore>(code, index);
	}
	case Kind::DStore: {
		uint8_t index = next_u8(buffer);
		return std::make_unique<DStore>(code, index);
	}
	case Kind::AStore: {
		uint8_t index = next_u8(buffer);
		return std::make_unique<AStore>(code, index);
	}
	case Kind::IStore_0: {
		return std::make_unique<IStore_0>(code);
	}
	case Kind::IStore_1: {
		return std::make_unique<IStore_1>(code);
	}
	case Kind::IStore_2: {
		return std::make_unique<IStore_2>(code);
	}
	case Kind::IStore_3: {
		return std::make_unique<IStore_3>(code);
	}
	case Kind::LStore_0: {
		return std::make_unique<LStore_0>(code);
	}
	case Kind::LStore_1: {
		return std::make_unique<LStore_1>(code);
	}
	case Kind::LStore_2: {
		return std::make_unique<LStore_2>(code);
	}
	case Kind::LStore_3: {
		return std::make_unique<LStore_3>(code);
	}
	case Kind::FStore_0: {
		return std::make_unique<FStore_0>(code);
	}
	case Kind::FStore_1: {
		return std::make_unique<FStore_1>(code);
	}
	case Kind::FStore_2: {
		return std::make_unique<FStore_2>(code);
	}
	case Kind::FStore_3: {
		return std::make_unique<FStore_3>(code);
	}
	case Kind::DStore_0: {
		return std::make_unique<DStore_0>(code);
	}
	case Kind::DStore_1: {
		return std::make_unique<DStore_1>(code);
	}
	case Kind::DStore_2: {
		return std::make_unique<DStore_2>(code);
	}
	case Kind::DStore_3: {
		return std::make_unique<DStore_3>(code);
	}
	case Kind::AStore_0: {
		return std::make_unique<AStore_0>(code);
	}
	case Kind::AStore_1: {
		return std::make_unique<AStore_1>(code);
	}
	case Kind::AStore_2: {
		return std::make_unique<AStore_2>(code);
	}
	case Kind::AStore_3: {
		return std::make_unique<AStore_3>(code);
	}
	case Kind::IAStore: {
		return std::make_unique<IAStore>(code);
	}
	case Kind::LAStore: {
		return std::make_unique<LAStore>(code);
	}
	case Kind::FAStore: {
		return std::make_unique<FAStore>(code);
	}
	case Kind::DAStore: {
		return std::make_unique<DAStore>(code);
	}
	case Kind::AAStore: {
		return std::make_unique<AAStore>(code);
	}
	case Kind::BAStore: {
		return std::make_unique<BAStore>(code);
	}
	case Kind::CAStore: {
		return std::make_unique<CAStore>(code);
	}
	case Kind::SAStore: {
		return std::make_unique<SAStore>(code);
	}
	case Kind::Pop: {
		return std::make_unique<Pop>(code);
	}
	case Kind::Pop2: {
		return std::make_unique<Pop2>(code);
	}
	case Kind::Dup: {
		return std::make_unique<Dup>(code);
	}
	case Kind::Dup_X1: {
		return std::make_unique<Dup_X1>(code);
	}
	case Kind::Dup_X2: {
		return std::make_unique<Dup_X2>(code);
	}
	case Kind::Dup2: {
		return std::make_unique<Dup2>(code);
	}
	case Kind::Dup2_X1: {
		return std::make_unique<Dup2_X1>(code);
	}
	case Kind::Dup2_X2: {
		return std::make_unique<Dup2_X2>(code);
	}
	case Kind::Swap: {
		return std::make_unique<Swap>(code);
	}
	case Kind::IAdd: {
		return std::make_unique<IAdd>(code);
	}
	case Kind::LAdd: {
		return std::make_unique<LAdd>(code);
	}
	case Kind::FAdd: {
		return std::make_unique<FAdd>(code);
	}
	case Kind::DAdd: {
		return std::make_unique<DAdd>(code);
	}
	case Kind::ISub: {
		return std::make_unique<ISub>(code);
	}
	case Kind::LSub: {
		return std::make_unique<LSub>(code);
	}
	case Kind::FSub: {
		return std::make_unique<FSub>(code);
	}
	case Kind::DSub: {
		return std::make_unique<DSub>(code);
	}
	case Kind::IMul: {
		return std::make_unique<IMul>(code);
	}
	case Kind::LMul: {
		return std::make_unique<LMul>(code);
	}
	case Kind::FMul: {
		return std::make_unique<FMul>(code);
	}
	case Kind::DMul: {
		return std::make_unique<DMul>(code);
	}
	case Kind::IDiv: {
		return std::make_unique<IDiv>(code);
	}
	case Kind::LDiv: {
		return std::make_unique<LDiv>(code);
	}
	case Kind::FDiv: {
		return std::make_unique<FDiv>(code);
	}
	case Kind::DDiv: {
		return std::make_unique<DDiv>(code);
	}
	case Kind::IRem: {
		return std::make_unique<IRem>(code);
	}
	case Kind::LRem: {
		return std::make_unique<LRem>(code);
	}
	case Kind::FRem: {
		return std::make_unique<FRem>(code);
	}
	case Kind::DRem: {
		return std::make_unique<DRem>(code);
	}
	case Kind::INeg: {
		return std::make_unique<INeg>(code);
	}
	case Kind::LNeg: {
		return std::make_unique<LNeg>(code);
	}
	case Kind::FNeg: {
		return std::make_unique<FNeg>(code);
	}
	case Kind::DNeg: {
		return std::make_unique<DNeg>(code);
	}
	case Kind::IShl: {
		return std::make_unique<IShl>(code);
	}
	case Kind::LShl: {
		return std::make_unique<LShl>(code);
	}
	case Kind::IShr: {
		return std::make_unique<IShr>(code);
	}
	case Kind::LShr: {
		return std::make_unique<LShr>(code);
	}
	case Kind::IUShr: {
		return std::make_unique<IUShr>(code);
	}
	case Kind::LUShr: {
		return std::make_unique<LUShr>(code);
	}
	case Kind::IAnd: {
		return std::make_unique<IAnd>(code);
	}
	case Kind::LAnd: {
		return std::make_unique<LAnd>(code);
	}
	case Kind::IOr: {
		return std::make_unique<IOr>(code);
	}
	case Kind::LOr: {
		return std::make_unique<LOr>(code);
	}
	case Kind::IXor: {
		return std::make_unique<IXor>(code);
	}
	case Kind::LXor: {
		return std::make_unique<LXor>(code);
	}
	case Kind::IInc: {
		uint8_t index = next_u8(buffer);
		int8_t value = next_u8(buffer);
		return std::make_unique<IInc>(code, index, value);
	}
	case Kind::I2L: {
		return std::make_unique<I2L>(code);
	}
	case Kind::I2F: {
		return std::make_unique<I2F>(code);
	}
	case Kind::I2D: {
		return std::make_unique<I2D>(code);
	}
	case Kind::L2I: {
		return std::make_unique<L2I>(code);
	}
	case Kind::L2F: {
		return std::make_unique<L2F>(code);
	}
	case Kind::L2D: {
		return std::make_unique<L2D>(code);
	}
	case Kind::F2I: {
		return std::make_unique<F2I>(code);
	}
	case Kind::F2L: {
		return std::make_unique<F2L>(code);
	}
	case Kind::F2D: {
		return std::make_unique<F2D>(code);
	}
	case Kind::D2I: {
		return std::make_unique<D2I>(code);
	}
	case Kind::D2L: {
		return std::make_unique<D2L>(code);
	}
	case Kind::D2F: {
		return std::make_unique<D2F>(code);
	}
	case Kind::I2B: {
		return std::make_unique<I2B>(code);
	}
	case Kind::I2C: {
		return std::make_unique<I2C>(code);
	}
	case Kind::I2S: {
		return std::make_unique<I2S>(code);
	}
	case Kind::LCmp: {
		return std::make_unique<LCmp>(code);
	}
	case Kind::FCmpL: {
		return std::make_unique<FCmpL>(code);
	}
	case Kind::FCmpG: {
		return std::make_unique<FCmpG>(code);
	}
	case Kind::DCmpL: {
		return std::make_unique<DCmpL>(code);
	}
	case Kind::DCmpG: {
		return std::make_unique<DCmpG>(code);
	}
	case Kind::IfEq: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<IfEq>(code, offset);
	}
	case Kind::IfNe: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<IfNe>(code, offset);
	}
	case Kind::IfLt: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<IfLt>(code, offset);
	}
	case Kind::IfGe: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<IfGe>(code, offset);
	}
	case Kind::IfGt: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<IfGt>(code, offset);
	}
	case Kind::IfLe: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<IfLe>(code, offset);
	}
	case Kind::If_ICmpEq: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<If_ICmpEq>(code, offset);
	}
	case Kind::If_ICmpNe: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<If_ICmpNe>(code, offset);
	}
	case Kind::If_ICmpLt: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<If_ICmpLt>(code, offset);
	}
	case Kind::If_ICmpGe: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<If_ICmpGe>(code, offset);
	}
	case Kind::If_ICmpGt: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<If_ICmpGt>(code, offset);
	}
	case Kind::If_ICmpLe: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<If_ICmpLe>(code, offset);
	}
	case Kind::If_ACmpEq: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<If_ACmpEq>(code, offset);
	}
	case Kind::If_ACmpNe: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<If_ACmpNe>(code, offset);
	}
	case Kind::Goto: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<Goto>(code, offset);
	}
	case Kind::Jsr: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<Jsr>(code, offset);
	}
	case Kind::Ret: {
		uint8_t index = next_u8(buffer);
		return std::make_unique<Ret>(code, index);
	}
	case Kind::TableSwitch: {
		uint8_t padding = 3 - (code->get_next_bci() % 4);
		for (uint8_t i = 0; i < padding; ++i) {
			next_u8(buffer);
		}
		int32_t default_offset = next_u32(buffer);
		int32_t low = next_u32(buffer);
		int32_t high = next_u32(buffer);
		uint32_t num_offsets = high - low + 1;
		std::vector<int32_t> offsets;
		for (uint32_t i = 0; i < num_offsets; ++i) {
			offsets.push_back(next_u32(buffer));
		}
		return std::make_unique<TableSwitch>(
			code, padding, default_offset, low, high,
			std::move(offsets)
		);
	}
	case Kind::LookupSwitch: {
		uint8_t padding = 3 - (code->get_next_bci() % 4);
		for (uint8_t i = 0; i < padding; ++i) {
			next_u8(buffer);
		}
		int32_t default_offset = next_u32(buffer);
		int32_t npairs = next_u32(buffer);
		std::vector<int32_t> matches;
		std::vector<int32_t> offsets;
		for (int32_t i = 0; i < npairs; ++i) {
			matches.push_back(next_u32(buffer));
			offsets.push_back(next_u32(buffer));
		}
		return std::make_unique<LookupSwitch>(
			code, padding, default_offset,
			std::move(matches), std::move(offsets)
		);
	}
	case Kind::IReturn: {
		return std::make_unique<IReturn>(code);
	}
	case Kind::LReturn: {
		return std::make_unique<LReturn>(code);
	}
	case Kind::FReturn: {
		return std::make_unique<FReturn>(code);
	}
	case Kind::DReturn: {
		return std::make_unique<DReturn>(code);
	}
	case Kind::AReturn: {
		return std::make_unique<AReturn>(code);
	}
	case Kind::Return: {
		return std::make_unique<Return>(code);
	}
	case Kind::GetStatic: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<GetStatic>(code, index);
	}
	case Kind::PutStatic: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<PutStatic>(code, index);
	}
	case Kind::GetField: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<GetField>(code, index);
	}
	case Kind::PutField: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<PutField>(code, index);
	}
	case Kind::InvokeVirtual: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<InvokeVirtual>(code, index);
	}
	case Kind::InvokeSpecial: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<InvokeSpecial>(code, index);
	}
	case Kind::InvokeStatic: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<InvokeStatic>(code, index);
	}
	case Kind::InvokeInterface: {
		uint16_t index = next_u16(buffer);
		uint8_t count = next_u8(buffer);
		assert(count != 0);
		uint8_t byte4 = next_u8(buffer);
		assert(byte4 == 0);
		return std::make_unique<InvokeInterface>(code, index, count);
	}
	case Kind::InvokeDynamic: {
		uint16_t index = next_u16(buffer);
		uint8_t byte3 = next_u8(buffer);
		assert(byte3 == 0);
		uint8_t byte4 = next_u8(buffer);
		assert(byte4 == 0);
		return std::make_unique<InvokeDynamic>(code, index);
	}
	case Kind::New: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<New>(code, index);
	}
	case Kind::NewArray: {
		uint8_t atype = next_u8(buffer);
		return std::make_unique<NewArray>(code, atype);
	}
	case Kind::ANewArray: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<ANewArray>(code, index);
	}
	case Kind::ArrayLength: {
		return std::make_unique<ArrayLength>(code);
	}
	case Kind::AThrow: {
		return std::make_unique<AThrow>(code);
	}
	case Kind::CheckCast: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<CheckCast>(code, index);
	}
	case Kind::InstanceOf: {
		uint16_t index = next_u16(buffer);
		return std::make_unique<InstanceOf>(code, index);
	}
	case Kind::MonitorEnter: {
		return std::make_unique<MonitorEnter>(code);
	}
	case Kind::MonitorExit: {
		return std::make_unique<MonitorExit>(code);
	}
	case Kind::Wide: {
		switch (Kind(next_u8(buffer))) {
		case Kind::ALoad: {
			uint16_t index = next_u16(buffer);
			return std::make_unique<WideALoad>(code, index);
		}
		case Kind::AStore: {
			uint16_t index = next_u16(buffer);
			return std::make_unique<WideAStore>(code, index);
		}
		case Kind::DLoad: {
			uint16_t index = next_u16(buffer);
			return std::make_unique<WideDLoad>(code, index);
		}
		case Kind::DStore: {
			uint16_t index = next_u16(buffer);
			return std::make_unique<WideDStore>(code, index);
		}
		case Kind::FLoad: {
			uint16_t index = next_u16(buffer);
			return std::make_unique<WideFLoad>(code, index);
		}
		case Kind::FStore: {
			uint16_t index = next_u16(buffer);
			return std::make_unique<WideFStore>(code, index);
		}
		case Kind::IInc: {
			uint16_t index = next_u16(buffer);
			uint16_t value = next_u16(buffer);
			return std::make_unique<WideIInc>(code, index, value);
		}
		case Kind::ILoad: {
			uint16_t index = next_u16(buffer);
			return std::make_unique<WideILoad>(code, index);
		}
		case Kind::IStore: {
			uint16_t index = next_u16(buffer);
			return std::make_unique<WideIStore>(code, index);
		}
		case Kind::LLoad: {
			uint16_t index = next_u16(buffer);
			return std::make_unique<WideLLoad>(code, index);
		}
		case Kind::LStore: {
			uint16_t index = next_u16(buffer);
			return std::make_unique<WideLStore>(code, index);
		}
		case Kind::Ret: {
			uint16_t index = next_u16(buffer);
			return std::make_unique<WideRet>(code, index);
		}
		default: {
			assert(false && "Invalid wide instruction");
		}
		}
	}
	case Kind::MultiANewArray: {
		uint16_t index = next_u16(buffer);
		uint8_t dimensions = next_u8(buffer);
		assert(dimensions >= 1);
		return std::make_unique<MultiANewArray>(code, index,
		                                        dimensions);
	}
	case Kind::IfNull: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<IfNull>(code, offset);
	}
	case Kind::IfNonNull: {
		int16_t offset = next_u16(buffer);
		return std::make_unique<IfNonNull>(code, offset);
	}
	case Kind::Goto_W: {
		int32_t offset = next_u32(buffer);
		return std::make_unique<Goto_W>(code, offset);
	}
	case Kind::Jsr_W: {
		int32_t offset = next_u32(buffer);
		return std::make_unique<Jsr_W>(code, offset);
	}
	}
	assert(false && "Undefined instruction");
}

Instruction::~Instruction() {
}

Method* Instruction::get_method() const {
	return code->get_method();
}

ClassFile* Instruction::get_class_file() const {
	return get_method()->get_class_file();
}

ConstantPool* Instruction::get_constant_pool() const {
	return get_class_file()->get_constant_pool();
}

int8_t Instruction::get_stack_delta() const {
	assert(false && "Unimplemented");
	return 0;
}

ConstantPoolUtf8* InvokeInstruction::get_descriptor() const {
	ConstantPool* constant_pool = get_constant_pool();
	ConstantPoolEntry* entry = constant_pool->get_entry(get_index());
	uint16_t name_and_type_index;
	if (ConstantPoolInterfaceMethodref* interface_methodref
	    = dyn_cast<ConstantPoolInterfaceMethodref>(entry)) {
		name_and_type_index
			= interface_methodref->get_name_and_type_index();
	}
	else if (ConstantPoolInvokeDynamic* invoke_dynamic
	         = dyn_cast<ConstantPoolInvokeDynamic>(entry)) {
		name_and_type_index = invoke_dynamic->get_name_and_type_index();
	}
	else if (ConstantPoolMethodref* methodref
	         = dyn_cast<ConstantPoolMethodref>(entry)) {
		name_and_type_index = methodref->get_name_and_type_index();
	}
	else {
		assert(false && "Unexpected constant pool entry");
	}
	ConstantPoolNameAndType* name_and_type = cast<ConstantPoolNameAndType>(
		constant_pool->get_entry(name_and_type_index)
	);
	ConstantPoolUtf8* descriptor = cast<ConstantPoolUtf8>(
		constant_pool->get_entry(name_and_type->get_descriptor_index())
	);
	return descriptor;
}

uint16_t InvokeInstruction::get_num_args() const {
	ConstantPoolUtf8* descriptor = get_descriptor();
	const uint8_t* data = descriptor->get_data();
	uint16_t length = descriptor->get_length();
	uint16_t num_args = 0;
	bool is_class = false;
	assert(data[0] == '(');
	for (uint32_t i = 1; i < length; ++i) {
		uint8_t byte = data[i];
		if (byte == ')') {
			break;
		}
		else if (is_class && (byte == ';')) {
			is_class = false;
		}
		else if (is_class) {
			continue;
		}
		else if (byte == '[') {
			continue;
		}
		else if (byte == 'B') {
			++num_args;
		}
		else if (byte == 'C') {
			++num_args;
		}
		else if (byte == 'D') {
			++num_args;
		}
		else if (byte == 'F') {
			++num_args;
		}
		else if (byte == 'I') {
			++num_args;
		}
		else if (byte == 'J') {
			++num_args;
		}
		else if (byte == 'L') {
			++num_args;
			is_class = true;
		}
		else if (byte == 'S') {
			++num_args;
		}
		else if (byte == 'Z') {
			++num_args;
		}
		else {
			assert(false && "Unexpected argument");
		}
	}
	return num_args;
}

bool InvokeInstruction::is_void() const {
	ConstantPoolUtf8* descriptor = get_descriptor();
	const uint8_t* data = descriptor->get_data();
	uint16_t length = descriptor->get_length();
	return data[length - 1] == 'V';
}

int8_t InvokeInstruction::get_stack_delta() const {
	uint16_t num_args = get_num_args();
	assert(num_args < INT8_MAX);
	int8_t stack_delta = -num_args;
	if (has_objectref()) {
		stack_delta -= 1;
	}
	if (!is_void()) {
		stack_delta += 1;
	}
	return stack_delta;
}

int32_t BranchInstruction::get_offset() const {
	assert(!is_invalid_offset());
	return offset;
}

bool BranchInstruction::is_invalid_offset() const {
	bool wide = is_wide();
	const Goto* goto_instruction = dyn_cast<Goto>(this);
	if (goto_instruction && goto_instruction->is_extended()) {
		wide = true;
	}

	if (wide) {
		return offset > INT32_MAX;
	}
	else {
		return offset > INT16_MAX;
	}
}

uint16_t Goto::get_byte_size() const {
	if (!extended) {
		return 3;
	}
	else {
		return 5;
	}
}

const char* Goto::get_mnemonic() const {
	if (!extended) {
		return "goto";
	}
	else {
		return "goto_w";
	}
}

const char* If_ICmpNe::get_mnemonic() const {
	if (!inverted) {
		return "if_icmpne";
	}
	else {
		return "if_icmpeq";
	}
}

uint16_t LookupSwitch::get_byte_size() const {
	uint32_t result = 1 + padding + 8 + matches.size() * 8;
	assert(result <= UINT16_MAX);
	return result;
}

uint16_t TableSwitch::get_byte_size() const {
	uint32_t result = 1 + padding + 12 + (high - low + 1) * 4;
	assert(result <= UINT16_MAX);
	return result;
}

void AALoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void AAStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void AConst_Null::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void ALoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
}

void ALoad_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void ALoad_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void ALoad_2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void ALoad_3::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void ANewArray::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, index);
}

void AReturn::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void ArrayLength::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void AStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
}

void AStore_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void AStore_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void AStore_2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void AStore_3::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void AThrow::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void BALoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void BAStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void BIPush::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, value);
}

void CALoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void CAStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void CheckCast::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, index);
}

void D2F::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void D2I::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void D2L::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DAdd::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DALoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DAStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DCmpG::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DCmpL::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DConst_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DConst_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DDiv::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DLoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
}

void DLoad_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DLoad_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DLoad_2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DLoad_3::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DMul::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DNeg::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DRem::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DReturn::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
}

void DStore_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DStore_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DStore_2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DStore_3::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void DSub::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void Dup::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void Dup_X1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void Dup_X2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void Dup2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void Dup2_X1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void Dup2_X2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void F2D::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void F2I::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void F2L::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FAdd::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FALoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FAStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FCmpG::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FCmpL::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FConst_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FConst_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FConst_2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FDiv::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FLoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
}

void FLoad_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FLoad_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FLoad_2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FLoad_3::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FMul::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FNeg::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FRem::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FReturn::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
}

void FStore_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FStore_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FStore_2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FStore_3::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void FSub::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void GetField::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, index);
}

void GetStatic::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, index);
}

void Goto::write_buffer(uint8_t** buffer) const {
	if (!extended) {
		next_u8(buffer, static_cast<uint8_t>(get_kind()));
		next_u16(buffer, get_offset());
	}
	else {
		next_u8(buffer, static_cast<uint8_t>(Kind::Goto_W));
		next_u32(buffer, get_offset());
	}
}

void Goto_W::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u32(buffer, get_offset());
}

void I2B::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void I2C::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void I2D::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void I2F::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void I2L::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void I2S::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IAdd::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IALoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IAnd::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IAStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IConst_M1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IConst_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IConst_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IConst_2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IConst_3::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IConst_4::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IConst_5::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IDiv::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void If_ACmpEq::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void If_ACmpNe::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void If_ICmpEq::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void If_ICmpNe::write_buffer(uint8_t** buffer) const {
	if (!inverted) {
		next_u8(buffer, static_cast<uint8_t>(get_kind()));
		next_u16(buffer, get_offset());
	}
	else {
		next_u8(buffer, static_cast<uint8_t>(Kind::If_ICmpEq));
		next_u16(buffer, get_offset());
	}
}

void If_ICmpLt::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void If_ICmpGe::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void If_ICmpGt::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void If_ICmpLe::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void IfEq::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void IfNe::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void IfLt::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void IfGe::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void IfGt::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void IfLe::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void IfNonNull::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void IfNull::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void IInc::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
	next_u8(buffer, value);
}

void ILoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
}

void ILoad_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void ILoad_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void ILoad_2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void ILoad_3::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IMul::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void INeg::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void InstanceOf::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, index);
}

void InvokeDynamic::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_index());
	next_u8(buffer, 0);
	next_u8(buffer, 0);
}

void InvokeInterface::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_index());
	next_u8(buffer, count);
	next_u8(buffer, 0);
}

void InvokeSpecial::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_index());
}

void InvokeStatic::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_index());
}

void InvokeVirtual::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_index());
}

void IOr::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IRem::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IReturn::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IShl::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IShr::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
}

void IStore_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IStore_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IStore_2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IStore_3::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void ISub::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IUShr::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void IXor::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void Jsr::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, get_offset());
}

void Jsr_W::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u32(buffer, get_offset());
}

void L2D::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void L2I::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void L2F::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LAdd::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LALoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LAnd::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LAStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LCmp::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LConst_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LConst_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void Ldc::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
}

void Ldc_W::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, index);
}

void Ldc2_W::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, index);
}

void LDiv::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LLoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
}

void LLoad_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LLoad_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LLoad_2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LLoad_3::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LMul::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LNeg::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LookupSwitch::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	for (uint8_t i = 0; i < padding; ++i) {
		next_u8(buffer, 0);
	}
	next_u32(buffer, default_offset);
	next_u32(buffer, matches.size());
	for (uint32_t i = 0; i < matches.size(); ++i) {
		next_u32(buffer, matches[i]);
		next_u32(buffer, offsets[i]);
	}
}

void LOr::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LRem::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LReturn::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LShl::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LShr::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
}

void LStore_0::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LStore_1::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LStore_2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LStore_3::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LSub::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LUShr::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void LXor::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void MonitorEnter::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void MonitorExit::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void MultiANewArray::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, index);
	next_u8(buffer, dimensions);
}

void New::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, index);
}

void NewArray::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, atype);
}

void Nop::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void Pop::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void Pop2::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void PutField::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, index);
}

void PutStatic::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, index);
}

void Ret::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, index);
}

void Return::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void SALoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void SAStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void SIPush::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u16(buffer, value);
}

void Swap::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
}

void TableSwitch::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	for (uint8_t i = 0; i < padding; ++i) {
		next_u8(buffer, 0);
	}
	next_u32(buffer, default_offset);
	next_u32(buffer, low);
	next_u32(buffer, high);
	for (int32_t offset : offsets) {
		next_u32(buffer, offset);
	}
}

void WideALoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, static_cast<uint8_t>(Kind::ALoad));
	next_u16(buffer, index);
}

void WideAStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, static_cast<uint8_t>(Kind::AStore));
	next_u16(buffer, index);
}

void WideDLoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, static_cast<uint8_t>(Kind::DLoad));
	next_u16(buffer, index);
}

void WideDStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, static_cast<uint8_t>(Kind::DStore));
	next_u16(buffer, index);
}

void WideFLoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, static_cast<uint8_t>(Kind::FLoad));
	next_u16(buffer, index);
}

void WideFStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, static_cast<uint8_t>(Kind::FStore));
	next_u16(buffer, index);
}

void WideIInc::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, static_cast<uint8_t>(Kind::IInc));
	next_u16(buffer, index);
	next_u16(buffer, value);
}

void WideILoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, static_cast<uint8_t>(Kind::ILoad));
	next_u16(buffer, index);
}

void WideIStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, static_cast<uint8_t>(Kind::IStore));
	next_u16(buffer, index);
}

void WideLLoad::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, static_cast<uint8_t>(Kind::LLoad));
	next_u16(buffer, index);
}

void WideLStore::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, static_cast<uint8_t>(Kind::LStore));
	next_u16(buffer, index);
}

void WideRet::write_buffer(uint8_t** buffer) const {
	next_u8(buffer, static_cast<uint8_t>(get_kind()));
	next_u8(buffer, static_cast<uint8_t>(Kind::Ret));
	next_u16(buffer, index);
}
