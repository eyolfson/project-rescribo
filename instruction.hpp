#ifndef PROJECT_TOTUS_INSTRUCTION_HPP
#define PROJECT_TOTUS_INSTRUCTION_HPP

#include <cstdint>
#include <memory>
#include <vector>

namespace project_totus {

class ClassFile;
class Code;
class ConstantPool;
class ConstantPoolUtf8;
class Method;

class Instruction {
public:
	enum class Kind : uint8_t {
		Nop = 0x00,
		AConst_Null = 0x01,
		IConst_M1 = 0x02,
		IConst_0 = 0x03,
		IConst_1 = 0x04,
		IConst_2 = 0x05,
		IConst_3 = 0x06,
		IConst_4 = 0x07,
		IConst_5 = 0x08,
		LConst_0 = 0x09,
		LConst_1 = 0x0A,
		FConst_0 = 0x0B,
		FConst_1 = 0x0C,
		FConst_2 = 0x0D,
		DConst_0 = 0x0E,
		DConst_1 = 0x0F,
		BIPush  = 0x10,
		SIPush  = 0x11,
		Ldc = 0x12,
		Ldc_W = 0x13,
		Ldc2_W = 0x14,
		ILoad = 0x15,
		LLoad = 0x16,
		FLoad = 0x17,
		DLoad = 0x18,
		ALoad = 0x19,
		ILoad_0 = 0x1A,
		ILoad_1 = 0x1B,
		ILoad_2 = 0x1C,
		ILoad_3 = 0x1D,
		LLoad_0 = 0x1E,
		LLoad_1 = 0x1F,
		LLoad_2 = 0x20,
		LLoad_3 = 0x21,
		FLoad_0 = 0x22,
		FLoad_1 = 0x23,
		FLoad_2 = 0x24,
		FLoad_3 = 0x25,
		DLoad_0 = 0x26,
		DLoad_1 = 0x27,
		DLoad_2 = 0x28,
		DLoad_3 = 0x29,
		ALoad_0 = 0x2A,
		ALoad_1 = 0x2B,
		ALoad_2 = 0x2C,
		ALoad_3 = 0x2D,
		IALoad = 0x2E,
		LALoad = 0x2F,
		FALoad = 0x30,
		DALoad = 0x31,
		AALoad = 0x32,
		BALoad = 0x33,
		CALoad = 0x34,
		SALoad = 0x35,
		IStore = 0x36,
		LStore = 0x37,
		FStore = 0x38,
		DStore = 0x39,
		AStore = 0x3A,
		IStore_0 = 0x3B,
		IStore_1 = 0x3C,
		IStore_2 = 0x3D,
		IStore_3 = 0x3E,
		LStore_0 = 0x3F,
		LStore_1 = 0x40,
		LStore_2 = 0x41,
		LStore_3 = 0x42,
		FStore_0 = 0x43,
		FStore_1 = 0x44,
		FStore_2 = 0x45,
		FStore_3 = 0x46,
		DStore_0 = 0x47,
		DStore_1 = 0x48,
		DStore_2 = 0x49,
		DStore_3 = 0x4A,
		AStore_0 = 0x4B,
		AStore_1 = 0x4C,
		AStore_2 = 0x4D,
		AStore_3 = 0x4E,
		IAStore = 0x4F,
		LAStore = 0x50,
		FAStore = 0x51,
		DAStore = 0x52,
		AAStore = 0x53,
		BAStore = 0x54,
		CAStore = 0x55,
		SAStore = 0x56,
		Pop = 0x57,
		Pop2 = 0x58,
		Dup = 0x59,
		Dup_X1 = 0x5A,
		Dup_X2 = 0x5B,
		Dup2 = 0x5C,
		Dup2_X1 = 0x5D,
		Dup2_X2 = 0x5E,
		Swap = 0x5F,
		IAdd = 0x60,
		LAdd = 0x61,
		FAdd = 0x62,
		DAdd = 0x63,
		ISub = 0x64,
		LSub = 0x65,
		FSub = 0x66,
		DSub = 0x67,
		IMul = 0x68,
		LMul = 0x69,
		FMul = 0x6A,
		DMul = 0x6B,
		IDiv = 0x6C,
		LDiv = 0x6D,
		FDiv = 0x6E,
		DDiv = 0x6F,
		IRem = 0x70,
		LRem = 0x71,
		FRem = 0x72,
		DRem = 0x73,
		INeg = 0x74,
		LNeg = 0x75,
		FNeg = 0x76,
		DNeg = 0x77,
		IShl = 0x78,
		LShl = 0x79,
		IShr = 0x7A,
		LShr = 0x7B,
		IUShr = 0x7C,
		LUShr = 0x7D,
		IAnd = 0x7E,
		LAnd = 0x7F,
		IOr = 0x80,
		LOr = 0x81,
		IXor = 0x82,
		LXor = 0x83,
		IInc = 0x84,
		I2L = 0x85,
		I2F = 0x86,
		I2D = 0x87,
		L2I = 0x88,
		L2F = 0x89,
		L2D = 0x8A,
		F2I = 0x8B,
		F2L = 0x8C,
		F2D = 0x8D,
		D2I = 0x8E,
		D2L = 0x8F,
		D2F = 0x90,
		I2B = 0x91,
		I2C = 0x92,
		I2S = 0x93,
		LCmp = 0x94,
		FCmpL = 0x95,
		FCmpG = 0x96,
		DCmpL = 0x97,
		DCmpG = 0x98,
		IfEq = 0x99,
		IfNe = 0x9A,
		IfLt = 0x9B,
		IfGe = 0x9C,
		IfGt = 0x9D,
		IfLe = 0x9E,
		If_ICmpEq = 0x9F,
		If_ICmpNe = 0xA0,
		If_ICmpLt = 0xA1,
		If_ICmpGe = 0xA2,
		If_ICmpGt = 0xA3,
		If_ICmpLe = 0xA4,
		If_ACmpEq = 0xA5,
		If_ACmpNe = 0xA6,
		Goto = 0xA7,
		Jsr = 0xA8,
		Ret = 0xA9,
		TableSwitch = 0xAA,
		LookupSwitch = 0xAB,
		IReturn = 0xAC,
		LReturn = 0xAD,
		FReturn = 0xAE,
		DReturn = 0xAF,
		AReturn = 0xB0,
		Return = 0xB1,
		GetStatic = 0xB2,
		PutStatic = 0xB3,
		GetField = 0xB4,
		PutField = 0xB5,
		InvokeVirtual = 0xB6,
		InvokeSpecial = 0xB7,
		InvokeStatic = 0xB8,
		InvokeInterface = 0xB9,
		InvokeDynamic = 0xBA,
		New = 0xBB,
		NewArray = 0xBC,
		ANewArray = 0xBD,
		ArrayLength = 0xBE,
		AThrow = 0xBF,
		CheckCast = 0xC0,
		InstanceOf = 0xC1,
		MonitorEnter = 0xC2,
		MonitorExit = 0xC3,
		Wide = 0xC4,
		MultiANewArray = 0xC5,
		IfNull = 0xC6,
		IfNonNull = 0xC7,
		Goto_W = 0xC8,
		Jsr_W = 0xC9,
	};
	Instruction(Kind kind, Code* code) : kind(kind), code(code) {}
	virtual ~Instruction();
	Kind get_kind() const {
		return kind;
	}
	Code* get_code() const {
		return code;
	}
	Method* get_method() const;
	ClassFile* get_class_file() const;
	ConstantPool* get_constant_pool() const;
	virtual uint16_t get_byte_size() const = 0;
	virtual const char* get_mnemonic() const = 0;
	virtual int8_t get_stack_delta() const;
	virtual void write_buffer(uint8_t** buffer) const = 0;

	uint32_t get_bci() const {
		return bci;
	}
	void set_bci(uint32_t i) {
		bci = i;
	}

	static std::unique_ptr<Instruction> make(const uint8_t** buffer,
	                                         Code* code);
private:
	Kind kind;
	Code* code;

	uint32_t bci;
};

class BranchInstruction : public Instruction {
public:
	BranchInstruction(Kind kind, Code* code, int32_t offset)
	: Instruction(kind, code), offset(offset) {}

	BranchInstruction(Kind kind, Code* code, Instruction* target)
	: Instruction(kind, code), target(target) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Goto
		       || instruction->get_kind() == Kind::Goto_W
		       || instruction->get_kind() == Kind::If_ACmpEq
		       || instruction->get_kind() == Kind::If_ACmpNe
		       || instruction->get_kind() == Kind::If_ICmpEq
		       || instruction->get_kind() == Kind::If_ICmpNe
		       || instruction->get_kind() == Kind::If_ICmpLt
		       || instruction->get_kind() == Kind::If_ICmpGe
		       || instruction->get_kind() == Kind::If_ICmpGt
		       || instruction->get_kind() == Kind::If_ICmpLe
		       || instruction->get_kind() == Kind::IfEq
		       || instruction->get_kind() == Kind::IfNe
		       || instruction->get_kind() == Kind::IfLt
		       || instruction->get_kind() == Kind::IfGe
		       || instruction->get_kind() == Kind::IfGt
		       || instruction->get_kind() == Kind::IfLe
		       || instruction->get_kind() == Kind::IfNonNull
		       || instruction->get_kind() == Kind::IfNull
		       || instruction->get_kind() == Kind::Jsr
		       || instruction->get_kind() == Kind::Jsr_W;
	}

	bool is_wide() const {
		return get_kind() == Kind::Goto_W
		       || get_kind() == Kind::Jsr_W;
	}

	Instruction* get_target() const {
		return target;
	}
	void set_target(Instruction* i) {
		target = i;
	}

	int32_t get_offset() const;
	void set_offset(int32_t o) {
		offset = o;
	}

	bool is_invalid_offset() const;
private:
	Instruction* target;
	int32_t offset;
};

class InvokeInstruction : public Instruction {
public:
	InvokeInstruction(Kind kind, Code* code, uint16_t index)
	: Instruction(kind, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::InvokeVirtual
		       || instruction->get_kind() == Kind::InvokeSpecial
		       || instruction->get_kind() == Kind::InvokeStatic
		       || instruction->get_kind() == Kind::InvokeInterface
		       || instruction->get_kind() == Kind::InvokeDynamic;
	}

	bool has_objectref() const {
		return get_kind() == Kind::InvokeVirtual
		       || get_kind() == Kind::InvokeInterface
		       || get_kind() == Kind::InvokeSpecial;
	}

	int8_t get_stack_delta() const override;

	uint16_t get_index() const {
		return index;
	}
	void set_index(uint16_t i) {
		index = i;
	}

	uint16_t get_num_args() const;
	bool is_void() const;

private:
	uint16_t index;

	ConstantPoolUtf8* get_descriptor() const;
};

class AALoad : public Instruction {
public:
	AALoad(Code* code) : Instruction(Kind::AALoad, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::AALoad;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "aaload";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}
	void write_buffer(uint8_t** buffer) const override;
};

class AAStore : public Instruction {
public:
	AAStore(Code* code) : Instruction(Kind::AAStore, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::AAStore;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "aastore";
	}
	int8_t get_stack_delta() const override {
		return -3;
	}
	void write_buffer(uint8_t** buffer) const override;
};

class AConst_Null : public Instruction {
public:
	AConst_Null(Code* code) : Instruction(Kind::AConst_Null, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::AConst_Null;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "aconst_null";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}
	void write_buffer(uint8_t** buffer) const override;
};

class ALoad : public Instruction {
public:
	ALoad(Code* code, uint8_t index)
	: Instruction(Kind::ALoad, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ALoad;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "aload";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	uint8_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
};

class ALoad_0 : public Instruction {
public:
	ALoad_0(Code* code) : Instruction(Kind::ALoad_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ALoad_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "aload_0";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class ALoad_1 : public Instruction {
public:
	ALoad_1(Code* code) : Instruction(Kind::ALoad_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ALoad_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "aload_1";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;

};

class ALoad_2 : public Instruction {
public:
	ALoad_2(Code* code) : Instruction(Kind::ALoad_2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ALoad_2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "aload_2";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class ALoad_3 : public Instruction {
public:
	ALoad_3(Code* code) : Instruction(Kind::ALoad_3, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ALoad_3;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "aload_3";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class ANewArray : public Instruction {
public:
	ANewArray(Code* code, uint16_t index)
	: Instruction(Kind::ANewArray, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ANewArray;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "anewarray";
	}
	int8_t get_stack_delta() const override {
		return 0;
	}

	uint16_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t index;
};

class AReturn : public Instruction {
public:
	AReturn(Code* code) : Instruction(Kind::AReturn, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::AReturn;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "areturn";
	}
	void write_buffer(uint8_t** buffer) const override;
};

class ArrayLength : public Instruction {
public:
	ArrayLength(Code* code) : Instruction(Kind::ArrayLength, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ArrayLength;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "arraylength";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class AStore : public Instruction {
public:
	AStore(Code* code, uint8_t index)
	: Instruction(Kind::AStore, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::AStore;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "astore";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	uint8_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
};

class AStore_0 : public Instruction {
public:
	AStore_0(Code* code) : Instruction(Kind::AStore_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::AStore_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "astore_0";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class AStore_1 : public Instruction {
public:
	AStore_1(Code* code) : Instruction(Kind::AStore_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::AStore_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "astore_1";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class AStore_2 : public Instruction {
public:
	AStore_2(Code* code) : Instruction(Kind::AStore_2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::AStore_2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "astore_2";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class AStore_3 : public Instruction {
public:
	AStore_3(Code* code) : Instruction(Kind::AStore_3, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::AStore_3;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "astore_3";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class AThrow : public Instruction {
public:
	AThrow(Code* code) : Instruction(Kind::AThrow, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::AThrow;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "athrow";
	}
	void write_buffer(uint8_t** buffer) const override;
};

class BALoad : public Instruction {
public:
	BALoad(Code* code) : Instruction(Kind::BALoad, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::BALoad;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "baload";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class BAStore : public Instruction {
public:
	BAStore(Code* code) : Instruction(Kind::BAStore, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::BAStore;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "bastore";
	}

	int8_t get_stack_delta() const override {
		return -3;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class BIPush  : public Instruction {
public:
	BIPush (Code* code, uint8_t value)
	: Instruction(Kind::BIPush , code), value(value) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::BIPush ;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "bipush";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	uint8_t get_value() const {
		return value;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t value;
};

class CALoad : public Instruction {
public:
	CALoad(Code* code) : Instruction(Kind::CALoad, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::CALoad;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "caload";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class CAStore : public Instruction {
public:
	CAStore(Code* code) : Instruction(Kind::CAStore, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::CAStore;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "castore";
	}

	int8_t get_stack_delta() const override {
		return -3;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class CheckCast : public Instruction {
public:
	CheckCast(Code* code, uint16_t index)
	: Instruction(Kind::CheckCast, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::CheckCast;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "checkcast";
	}
	int8_t get_stack_delta() const override {
		return 0;
	}

	uint16_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t index;
};

class D2F : public Instruction {
public:
	D2F(Code* code) : Instruction(Kind::D2F, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::D2F;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "d2f";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class D2I : public Instruction {
public:
	D2I(Code* code) : Instruction(Kind::D2I, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::D2I;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "d2i";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;

};

class D2L : public Instruction {
public:
	D2L(Code* code) : Instruction(Kind::D2L, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::D2L;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "d2l";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DAdd : public Instruction {
public:
	DAdd(Code* code) : Instruction(Kind::DAdd, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DAdd;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dadd";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DALoad : public Instruction {
public:
	DALoad(Code* code) : Instruction(Kind::DALoad, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DALoad;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "daload";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DAStore : public Instruction {
public:
	DAStore(Code* code) : Instruction(Kind::DAStore, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DAStore;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dastore";
	}

	int8_t get_stack_delta() const override {
		return -3;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DCmpG : public Instruction {
public:
	DCmpG(Code* code) : Instruction(Kind::DCmpG, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DCmpG;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dcmpg";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DCmpL : public Instruction {
public:
	DCmpL(Code* code) : Instruction(Kind::DCmpL, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DCmpL;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dcmpl";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DConst_0 : public Instruction {
public:
	DConst_0(Code* code) : Instruction(Kind::DConst_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DConst_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dconst_0";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DConst_1 : public Instruction {
public:
	DConst_1(Code* code) : Instruction(Kind::DConst_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DConst_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dconst_1";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DDiv : public Instruction {
public:
	DDiv(Code* code) : Instruction(Kind::DDiv, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DDiv;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "ddiv";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DLoad : public Instruction {
public:
	DLoad(Code* code, uint8_t index)
	: Instruction(Kind::DLoad, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DLoad;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "dload";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	uint8_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
};

class DLoad_0 : public Instruction {
public:
	DLoad_0(Code* code) : Instruction(Kind::DLoad_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DLoad_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dload_0";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DLoad_1 : public Instruction {
public:
	DLoad_1(Code* code) : Instruction(Kind::DLoad_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DLoad_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dload_1";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DLoad_2 : public Instruction {
public:
	DLoad_2(Code* code) : Instruction(Kind::DLoad_2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DLoad_2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dload_2";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DLoad_3 : public Instruction {
public:
	DLoad_3(Code* code) : Instruction(Kind::DLoad_3, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DLoad_3;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dload_3";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DMul : public Instruction {
public:
	DMul(Code* code) : Instruction(Kind::DMul, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DMul;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dmul";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DNeg : public Instruction {
public:
	DNeg(Code* code) : Instruction(Kind::DNeg, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DNeg;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dneg";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DRem : public Instruction {
public:
	DRem(Code* code) : Instruction(Kind::DRem, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DRem;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "drem";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;

};

class DReturn : public Instruction {
public:
	DReturn(Code* code) : Instruction(Kind::DReturn, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DReturn;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dreturn";
	}
	void write_buffer(uint8_t** buffer) const override;
};

class DStore : public Instruction {
public:
	DStore(Code* code, uint8_t index)
	: Instruction(Kind::DStore, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DStore;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "dstore";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	uint8_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
};

class DStore_0 : public Instruction {
public:
	DStore_0(Code* code) : Instruction(Kind::DStore_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DStore_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dstore_0";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DStore_1 : public Instruction {
public:
	DStore_1(Code* code) : Instruction(Kind::DStore_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DStore_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dstore_1";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DStore_2 : public Instruction {
public:
	DStore_2(Code* code) : Instruction(Kind::DStore_2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DStore_2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dstore_2";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;

};

class DStore_3 : public Instruction {
public:
	DStore_3(Code* code) : Instruction(Kind::DStore_3, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DStore_3;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dstore_3";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class DSub : public Instruction {
public:
	DSub(Code* code) : Instruction(Kind::DSub, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::DSub;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dsub";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;

};

class Dup : public Instruction {
public:
	Dup(Code* code) : Instruction(Kind::Dup, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Dup;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dup";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class Dup_X1 : public Instruction {
public:
	Dup_X1(Code* code) : Instruction(Kind::Dup_X1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Dup_X1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dup_x1";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class Dup_X2 : public Instruction {
public:
	Dup_X2(Code* code) : Instruction(Kind::Dup_X2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Dup_X2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dup_x2";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class Dup2 : public Instruction {
public:
	Dup2(Code* code) : Instruction(Kind::Dup2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Dup2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dup2";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class Dup2_X1 : public Instruction {
public:
	Dup2_X1(Code* code) : Instruction(Kind::Dup2_X1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Dup2_X1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dup2_x1";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class Dup2_X2 : public Instruction {
public:
	Dup2_X2(Code* code) : Instruction(Kind::Dup2_X2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Dup2_X2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "dup2_x2";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class F2D : public Instruction {
public:
	F2D(Code* code) : Instruction(Kind::F2D, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::F2D;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "f2d";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class F2I : public Instruction {
public:
	F2I(Code* code) : Instruction(Kind::F2I, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::F2I;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "f2i";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;

};

class F2L : public Instruction {
public:
	F2L(Code* code) : Instruction(Kind::F2L, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::F2L;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "f2l";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FAdd : public Instruction {
public:
	FAdd(Code* code) : Instruction(Kind::FAdd, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FAdd;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fadd";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FALoad : public Instruction {
public:
	FALoad(Code* code) : Instruction(Kind::FALoad, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FALoad;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "faload";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FAStore : public Instruction {
public:
	FAStore(Code* code) : Instruction(Kind::FAStore, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FAStore;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fastore";
	}

	int8_t get_stack_delta() const override {
		return -3;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FCmpG : public Instruction {
public:
	FCmpG(Code* code) : Instruction(Kind::FCmpG, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FCmpG;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fcmpg";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;

};

class FCmpL : public Instruction {
public:
	FCmpL(Code* code) : Instruction(Kind::FCmpL, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FCmpL;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fcmpl";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FConst_0 : public Instruction {
public:
	FConst_0(Code* code) : Instruction(Kind::FConst_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FConst_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fconst_0";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;

};

class FConst_1 : public Instruction {
public:
	FConst_1(Code* code) : Instruction(Kind::FConst_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FConst_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fconst_1";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FConst_2 : public Instruction {
public:
	FConst_2(Code* code) : Instruction(Kind::FConst_2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FConst_2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fconst_2";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FDiv : public Instruction {
public:
	FDiv(Code* code) : Instruction(Kind::FDiv, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FDiv;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fdiv";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;

};

class FLoad : public Instruction {
public:
	FLoad(Code* code, uint8_t index)
	: Instruction(Kind::FLoad, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FLoad;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "fload";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	uint8_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
};

class FLoad_0 : public Instruction {
public:
	FLoad_0(Code* code) : Instruction(Kind::FLoad_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FLoad_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fload_0";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FLoad_1 : public Instruction {
public:
	FLoad_1(Code* code) : Instruction(Kind::FLoad_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FLoad_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fload_1";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FLoad_2 : public Instruction {
public:
	FLoad_2(Code* code) : Instruction(Kind::FLoad_2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FLoad_2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fload_2";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FLoad_3 : public Instruction {
public:
	FLoad_3(Code* code) : Instruction(Kind::FLoad_3, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FLoad_3;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fload_3";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FMul : public Instruction {
public:
	FMul(Code* code) : Instruction(Kind::FMul, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FMul;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fmul";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FNeg : public Instruction {
public:
	FNeg(Code* code) : Instruction(Kind::FNeg, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FNeg;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fneg";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FRem : public Instruction {
public:
	FRem(Code* code) : Instruction(Kind::FRem, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FRem;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "frem";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FReturn : public Instruction {
public:
	FReturn(Code* code) : Instruction(Kind::FReturn, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FReturn;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "freturn";
	}
	void write_buffer(uint8_t** buffer) const override;
};

class FStore : public Instruction {
public:
	FStore(Code* code, uint8_t index)
	: Instruction(Kind::FStore, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FStore;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "fstore";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	uint8_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
};

class FStore_0 : public Instruction {
public:
	FStore_0(Code* code) : Instruction(Kind::FStore_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FStore_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fstore_0";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FStore_1 : public Instruction {
public:
	FStore_1(Code* code) : Instruction(Kind::FStore_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FStore_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fstore_1";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FStore_2 : public Instruction {
public:
	FStore_2(Code* code) : Instruction(Kind::FStore_2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FStore_2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fstore_2";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FStore_3 : public Instruction {
public:
	FStore_3(Code* code) : Instruction(Kind::FStore_3, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FStore_3;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fstore_3";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class FSub : public Instruction {
public:
	FSub(Code* code) : Instruction(Kind::FSub, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::FSub;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "fsub";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class GetField : public Instruction {
public:
	GetField(Code* code, uint16_t index)
	: Instruction(Kind::GetField, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::GetField;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "getfield";
	}
	int8_t get_stack_delta() const override {
		return 0;
	}

	uint16_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t index;
};

class GetStatic : public Instruction {
public:
	GetStatic(Code* code, uint16_t index)
	: Instruction(Kind::GetStatic, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::GetStatic;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "getstatic";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	uint16_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t index;
};

class Goto : public BranchInstruction {
public:
	Goto(Code* code, int16_t offset)
	: BranchInstruction(Kind::Goto, code, offset), extended(false) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Goto;
	}

	uint16_t get_byte_size() const override;
	const char* get_mnemonic() const override;
	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;

	bool is_extended() const {
		return extended;
	}
	void extend() {
		extended = true;
	}
private:
	bool extended;
};

class Goto_W : public BranchInstruction {
public:
	Goto_W(Code* code, int32_t offset)
	: BranchInstruction(Kind::Goto_W, code, offset) {}

	Goto_W(Code* code, Instruction* target)
	: BranchInstruction(Kind::Goto_W, code, target) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Goto_W;
	}

	uint16_t get_byte_size() const override {
		return 5;
	}
	const char* get_mnemonic() const override {
		return "goto_w";
	}
	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class I2B : public Instruction {
public:
	I2B(Code* code) : Instruction(Kind::I2B, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::I2B;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "i2b";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class I2C : public Instruction {
public:
	I2C(Code* code) : Instruction(Kind::I2C, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::I2C;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "i2c";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class I2D : public Instruction {
public:
	I2D(Code* code) : Instruction(Kind::I2D, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::I2D;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "i2d";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class I2F : public Instruction {
public:
	I2F(Code* code) : Instruction(Kind::I2F, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::I2F;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "i2f";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class I2L : public Instruction {
public:
	I2L(Code* code) : Instruction(Kind::I2L, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::I2L;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "i2l";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class I2S : public Instruction {
public:
	I2S(Code* code) : Instruction(Kind::I2S, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::I2S;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "i2s";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IAdd : public Instruction {
public:
	IAdd(Code* code) : Instruction(Kind::IAdd, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IAdd;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iadd";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IALoad : public Instruction {
public:
	IALoad(Code* code) : Instruction(Kind::IALoad, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IALoad;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iaload";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IAnd : public Instruction {
public:
	IAnd(Code* code) : Instruction(Kind::IAnd, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IAnd;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iand";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IAStore : public Instruction {
public:
	IAStore(Code* code) : Instruction(Kind::IAStore, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IAStore;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "istore";
	}

	int8_t get_stack_delta() const override {
		return -3;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IConst_M1 : public Instruction {
public:
	IConst_M1(Code* code) : Instruction(Kind::IConst_M1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IConst_M1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iconst_m1";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IConst_0 : public Instruction {
public:
	IConst_0(Code* code) : Instruction(Kind::IConst_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IConst_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iconst_0";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IConst_1 : public Instruction {
public:
	IConst_1(Code* code) : Instruction(Kind::IConst_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IConst_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iconst_1";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IConst_2 : public Instruction {
public:
	IConst_2(Code* code) : Instruction(Kind::IConst_2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IConst_2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iconst_2";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IConst_3 : public Instruction {
public:
	IConst_3(Code* code) : Instruction(Kind::IConst_3, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IConst_3;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iconst_3";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IConst_4 : public Instruction {
public:
	IConst_4(Code* code) : Instruction(Kind::IConst_4, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IConst_4;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iconst_4";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IConst_5 : public Instruction {
public:
	IConst_5(Code* code) : Instruction(Kind::IConst_5, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IConst_5;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iconst_5";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IDiv : public Instruction {
public:
	IDiv(Code* code) : Instruction(Kind::IDiv, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IDiv;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "idiv";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class If_ACmpEq : public BranchInstruction {
public:
	If_ACmpEq(Code* code, int16_t offset)
	: BranchInstruction(Kind::If_ACmpEq, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::If_ACmpEq;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "if_acmpeq";
	}
	int8_t get_stack_delta() const override {
		return -2;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class If_ACmpNe : public BranchInstruction {
public:
	If_ACmpNe(Code* code, int16_t offset)
	: BranchInstruction(Kind::If_ACmpNe, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::If_ACmpNe;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "if_acmpne";
	}
	int8_t get_stack_delta() const override {
		return -2;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class If_ICmpEq : public BranchInstruction {
public:
	If_ICmpEq(Code* code, int16_t offset)
	: BranchInstruction(Kind::If_ICmpEq, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::If_ICmpEq;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "if_icmpeq";
	}
	int8_t get_stack_delta() const override {
		return -2;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class If_ICmpNe : public BranchInstruction {
public:
	If_ICmpNe(Code* code, int16_t offset)
	: BranchInstruction(Kind::If_ICmpNe, code, offset), inverted(false) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::If_ICmpNe;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override;
	int8_t get_stack_delta() const override {
		return -2;
	}

	void write_buffer(uint8_t** buffer) const override;

	bool is_inverted() const {
		return inverted;
	}
	void invert() {
		inverted = true;
	}
private:
	bool inverted;
};

class If_ICmpLt : public BranchInstruction {
public:
	If_ICmpLt(Code* code, int16_t offset)
	: BranchInstruction(Kind::If_ICmpLt, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::If_ICmpLt;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "if_icmplt";
	}
	int8_t get_stack_delta() const override {
		return -2;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class If_ICmpGe : public BranchInstruction {
public:
	If_ICmpGe(Code* code, int16_t offset)
	: BranchInstruction(Kind::If_ICmpGe, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::If_ICmpGe;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "if_icmpge";
	}
	int8_t get_stack_delta() const override {
		return -2;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class If_ICmpGt : public BranchInstruction {
public:
	If_ICmpGt(Code* code, int16_t offset)
	: BranchInstruction(Kind::If_ICmpGt, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::If_ICmpGt;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "if_icmpgt";
	}
	int8_t get_stack_delta() const override {
		return -2;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class If_ICmpLe : public BranchInstruction {
public:
	If_ICmpLe(Code* code, int16_t offset)
	: BranchInstruction(Kind::If_ICmpLe, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::If_ICmpLe;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "if_icmple";
	}
	int8_t get_stack_delta() const override {
		return -2;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IfEq : public BranchInstruction {
public:
	IfEq(Code* code, int16_t offset)
	: BranchInstruction(Kind::IfEq, code, offset) {}

	IfEq(Code* code, Instruction* target)
	: BranchInstruction(Kind::IfEq, code, target) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IfEq;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "ifeq";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IfNe : public BranchInstruction {
public:
	IfNe(Code* code, int16_t offset)
	: BranchInstruction(Kind::IfNe, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IfNe;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "ifne";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IfLt : public BranchInstruction {
public:
	IfLt(Code* code, int16_t offset)
	: BranchInstruction(Kind::IfLt, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IfLt;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "iflt";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IfGe : public BranchInstruction {
public:
	IfGe(Code* code, int16_t offset)
	: BranchInstruction(Kind::IfGe, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IfGe;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "ifge";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IfGt : public BranchInstruction {
public:
	IfGt(Code* code, int16_t offset)
	: BranchInstruction(Kind::IfGt, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IfGt;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "ifgt";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IfLe : public BranchInstruction {
public:
	IfLe(Code* code, int16_t offset)
	: BranchInstruction(Kind::IfLe, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IfLe;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "ifle";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IfNonNull : public BranchInstruction {
public:
	IfNonNull(Code* code, int16_t offset)
	: BranchInstruction(Kind::IfNonNull, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IfNonNull;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "ifnonnull";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IfNull : public BranchInstruction {
public:
	IfNull(Code* code, int16_t offset)
	: BranchInstruction(Kind::IfNull, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IfNull;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "ifnull";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IInc : public Instruction {
public:
	IInc(Code* code, uint8_t index, int8_t value)
	: Instruction(Kind::IInc, code), index(index), value(value) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IInc;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "iinc";
	}
	int8_t get_stack_delta() const override {
		return 0;
	}

	uint8_t get_index() const {
		return index;
	}
	int8_t get_value() const {
		return value;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
	int8_t value;
};

class ILoad : public Instruction {
public:
	ILoad(Code* code, uint8_t index)
	: Instruction(Kind::ILoad, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ILoad;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "iload";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	uint8_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
};

class ILoad_0 : public Instruction {
public:
	ILoad_0(Code* code) : Instruction(Kind::ILoad_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ILoad_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iload_0";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class ILoad_1 : public Instruction {
public:
	ILoad_1(Code* code) : Instruction(Kind::ILoad_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ILoad_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iload_1";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class ILoad_2 : public Instruction {
public:
	ILoad_2(Code* code) : Instruction(Kind::ILoad_2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ILoad_2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iload_2";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class ILoad_3 : public Instruction {
public:
	ILoad_3(Code* code) : Instruction(Kind::ILoad_3, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ILoad_3;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iload_3";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IMul : public Instruction {
public:
	IMul(Code* code) : Instruction(Kind::IMul, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IMul;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "imul";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class INeg : public Instruction {
public:
	INeg(Code* code) : Instruction(Kind::INeg, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::INeg;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "ineg";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class InstanceOf : public Instruction {
public:
	InstanceOf(Code* code, uint16_t index)
	: Instruction(Kind::InstanceOf, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::InstanceOf;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "instanceof";
	}
	int8_t get_stack_delta() const override {
		return 0;
	}

	uint16_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t index;
};

class InvokeDynamic : public InvokeInstruction {
public:
	InvokeDynamic(Code* code, uint16_t index)
	: InvokeInstruction(Kind::InvokeDynamic, code, index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::InvokeDynamic;
	}

	uint16_t get_byte_size() const override {
		return 5;
	}
	const char* get_mnemonic() const override {
		return "invokedynamic";
	}

	void write_buffer(uint8_t** buffer) const override;
};

class InvokeInterface : public InvokeInstruction {
public:
	InvokeInterface(Code* code, uint16_t index, uint8_t count)
	: InvokeInstruction(Kind::InvokeInterface, code, index),
	  count(count) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::InvokeInterface;
	}

	uint16_t get_byte_size() const override {
		return 5;
	}
	const char* get_mnemonic() const override {
		return "invokeinterface";
	}

	uint8_t get_count() const {
		return count;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t count;
};

class InvokeSpecial : public InvokeInstruction {
public:
	InvokeSpecial(Code* code, uint16_t index)
	: InvokeInstruction(Kind::InvokeSpecial, code, index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::InvokeSpecial;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "invokespecial";
	}

	void write_buffer(uint8_t** buffer) const override;
};

class InvokeStatic : public InvokeInstruction {
public:
	InvokeStatic(Code* code, uint16_t index)
	: InvokeInstruction(Kind::InvokeStatic, code, index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::InvokeStatic;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "invokestatic";
	}

	void write_buffer(uint8_t** buffer) const override;
};

class InvokeVirtual : public InvokeInstruction {
public:
	InvokeVirtual(Code* code, uint16_t index)
	: InvokeInstruction(Kind::InvokeVirtual, code, index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::InvokeVirtual;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "invokevirtual";
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IOr : public Instruction {
public:
	IOr(Code* code) : Instruction(Kind::IOr, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IOr;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "ior";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IRem : public Instruction {
public:
	IRem(Code* code) : Instruction(Kind::IRem, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IRem;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "irem";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IReturn : public Instruction {
public:
	IReturn(Code* code) : Instruction(Kind::IReturn, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IReturn;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "ireturn";
	}
	void write_buffer(uint8_t** buffer) const override;
};

class IShl : public Instruction {
public:
	IShl(Code* code) : Instruction(Kind::IShl, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IShl;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "ishl";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IShr : public Instruction {
public:
	IShr(Code* code) : Instruction(Kind::IShr, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IShr;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "ishr";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IStore : public Instruction {
public:
	IStore(Code* code, uint8_t index)
	: Instruction(Kind::IStore, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IStore;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "istore";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	uint8_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
};

class IStore_0 : public Instruction {
public:
	IStore_0(Code* code) : Instruction(Kind::IStore_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IStore_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "istore_0";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IStore_1 : public Instruction {
public:
	IStore_1(Code* code) : Instruction(Kind::IStore_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IStore_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "istore_1";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IStore_2 : public Instruction {
public:
	IStore_2(Code* code) : Instruction(Kind::IStore_2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IStore_2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "istore_2";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IStore_3 : public Instruction {
public:
	IStore_3(Code* code) : Instruction(Kind::IStore_3, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IStore_3;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "istore_3";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class ISub : public Instruction {
public:
	ISub(Code* code) : Instruction(Kind::ISub, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::ISub;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "isub";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IUShr : public Instruction {
public:
	IUShr(Code* code) : Instruction(Kind::IUShr, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IUShr;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "iushr";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class IXor : public Instruction {
public:
	IXor(Code* code) : Instruction(Kind::IXor, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::IXor;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "ixor";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class Jsr : public BranchInstruction {
public:
	Jsr(Code* code, int16_t offset)
	: BranchInstruction(Kind::Jsr, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Jsr;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "jsr";
	}

	void write_buffer(uint8_t** buffer) const override;
};

class Jsr_W : public BranchInstruction {
public:
	Jsr_W(Code* code, int32_t offset)
	: BranchInstruction(Kind::Jsr_W, code, offset) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Jsr_W;
	}

	uint16_t get_byte_size() const override {
		return 5;
	}
	const char* get_mnemonic() const override {
		return "jsr_w";
	}

	void write_buffer(uint8_t** buffer) const override;
};

class L2D : public Instruction {
public:
	L2D(Code* code) : Instruction(Kind::L2D, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::L2D;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "l2d";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class L2I : public Instruction {
public:
	L2I(Code* code) : Instruction(Kind::L2I, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::L2I;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "l2i";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class L2F : public Instruction {
public:
	L2F(Code* code) : Instruction(Kind::L2F, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::L2F;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "l2f";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LAdd : public Instruction {
public:
	LAdd(Code* code) : Instruction(Kind::LAdd, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LAdd;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "ladd";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LALoad : public Instruction {
public:
	LALoad(Code* code) : Instruction(Kind::LALoad, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LALoad;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "laload";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LAnd : public Instruction {
public:
	LAnd(Code* code) : Instruction(Kind::LAnd, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LAnd;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "land";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LAStore : public Instruction {
public:
	LAStore(Code* code) : Instruction(Kind::LAStore, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LAStore;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lastore";
	}

	int8_t get_stack_delta() const override {
		return -3;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LCmp : public Instruction {
public:
	LCmp(Code* code) : Instruction(Kind::LCmp, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LCmp;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lcmp";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LConst_0 : public Instruction {
public:
	LConst_0(Code* code) : Instruction(Kind::LConst_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LConst_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lconst_0";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LConst_1 : public Instruction {
public:
	LConst_1(Code* code) : Instruction(Kind::LConst_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LConst_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lconst_1";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class Ldc : public Instruction {
public:
	Ldc(Code* code, uint8_t index)
	: Instruction(Kind::Ldc, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Ldc;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "ldc";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	uint8_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
};

class Ldc_W : public Instruction {
public:
	Ldc_W(Code* code, uint16_t index)
	: Instruction(Kind::Ldc_W, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Ldc_W;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "ldc_w";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	uint16_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t index;
};

class Ldc2_W : public Instruction {
public:
	Ldc2_W(Code* code, uint16_t index)
	: Instruction(Kind::Ldc2_W, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Ldc2_W;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "ldc2_w";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	uint16_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t index;
};

class LDiv : public Instruction {
public:
	LDiv(Code* code) : Instruction(Kind::LDiv, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LDiv;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "ldiv";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LLoad : public Instruction {
public:
	LLoad(Code* code, uint8_t index)
	: Instruction(Kind::LLoad, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LLoad;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "lload";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	uint8_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
};

class LLoad_0 : public Instruction {
public:
	LLoad_0(Code* code) : Instruction(Kind::LLoad_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LLoad_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lload_0";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LLoad_1 : public Instruction {
public:
	LLoad_1(Code* code) : Instruction(Kind::LLoad_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LLoad_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lload_1";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LLoad_2 : public Instruction {
public:
	LLoad_2(Code* code) : Instruction(Kind::LLoad_2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LLoad_2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lload_2";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LLoad_3 : public Instruction {
public:
	LLoad_3(Code* code) : Instruction(Kind::LLoad_3, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LLoad_3;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lload_3";
	}

	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LMul : public Instruction {
public:
	LMul(Code* code) : Instruction(Kind::LMul, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LMul;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lmul";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}
	void write_buffer(uint8_t** buffer) const override;
};

class LNeg : public Instruction {
public:
	LNeg(Code* code) : Instruction(Kind::LNeg, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LNeg;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lneg";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}
	void write_buffer(uint8_t** buffer) const override;
};

class LookupSwitch : public Instruction {
public:
	LookupSwitch(Code* code, uint8_t padding, int32_t default_offset,
	             std::vector<int32_t> matches, std::vector<int32_t> offsets)
	: Instruction(Kind::LookupSwitch, code), padding(padding),
	  default_offset(default_offset), matches(std::move(matches)),
	  offsets(std::move(offsets)) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LookupSwitch;
	}

	uint16_t get_byte_size() const override;
	const char* get_mnemonic() const override {
		return "lookupswitch";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}
	void write_buffer(uint8_t** buffer) const override;

	uint8_t get_padding() const {
		return padding;
	}
	void set_padding(uint8_t p) {
		padding = p;
	}

	int32_t get_default_offset() const {
		return default_offset;
	}
	void set_default_offset(int32_t o) {
		default_offset = o;
	}

	const std::vector<int32_t>& get_offsets() const {
		return offsets;
	}
	void clear_offsets() {
		offsets.clear();
	}
	void push_back_offset(int32_t o) {
		offsets.push_back(o);
	}

	Instruction* get_default_target() const{
		return default_target;
	}
	void set_default_target(Instruction* target) {
		default_target = target;
	}

	std::vector<Instruction*>& get_targets() {
		return targets;
	}
	void push_back_target(Instruction* target) {
		targets.push_back(target);
	}
private:
	uint8_t padding;
	int32_t default_offset;
	std::vector<int32_t> matches;
	std::vector<int32_t> offsets;

	Instruction* default_target;
	std::vector<Instruction*> targets;
};

class LOr : public Instruction {
public:
	LOr(Code* code) : Instruction(Kind::LOr, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LOr;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lor";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LRem : public Instruction {
public:
	LRem(Code* code) : Instruction(Kind::LRem, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LRem;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lrem";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LReturn : public Instruction {
public:
	LReturn(Code* code) : Instruction(Kind::LReturn, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LReturn;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lreturn";
	}
	void write_buffer(uint8_t** buffer) const override;
};

class LShl : public Instruction {
public:
	LShl(Code* code) : Instruction(Kind::LShl, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LShl;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lshl";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LShr : public Instruction {
public:
	LShr(Code* code) : Instruction(Kind::LShr, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LShr;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lshr";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LStore : public Instruction {
public:
	LStore(Code* code, uint8_t index)
	: Instruction(Kind::LStore, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LStore;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "lstore";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	uint8_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
};

class LStore_0 : public Instruction {
public:
	LStore_0(Code* code) : Instruction(Kind::LStore_0, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LStore_0;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lstore_0";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LStore_1 : public Instruction {
public:
	LStore_1(Code* code) : Instruction(Kind::LStore_1, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LStore_1;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lstore_1";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LStore_2 : public Instruction {
public:
	LStore_2(Code* code) : Instruction(Kind::LStore_2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LStore_2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lstore_2";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LStore_3 : public Instruction {
public:
	LStore_3(Code* code) : Instruction(Kind::LStore_3, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LStore_3;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lstore_3";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LSub : public Instruction {
public:
	LSub(Code* code) : Instruction(Kind::LSub, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LSub;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lsub";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LUShr : public Instruction {
public:
	LUShr(Code* code) : Instruction(Kind::LUShr, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LUShr;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lushr";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class LXor : public Instruction {
public:
	LXor(Code* code) : Instruction(Kind::LXor, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::LXor;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "lxor";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;

};

class MonitorEnter : public Instruction {
public:
	MonitorEnter(Code* code)
	: Instruction(Kind::MonitorEnter, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::MonitorEnter;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "monitorenter";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class MonitorExit : public Instruction {
public:
	MonitorExit(Code* code) : Instruction(Kind::MonitorExit, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::MonitorExit;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "monitorexit";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class MultiANewArray : public Instruction {
public:
	MultiANewArray(Code* code, uint16_t index, uint8_t dimensions)
	: Instruction(Kind::MultiANewArray, code), index(index),
	  dimensions(dimensions) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::MultiANewArray;
	}

	uint16_t get_byte_size() const override {
		return 4;
	}
	const char* get_mnemonic() const override {
		return "multianewarray";
	}

	int8_t get_stack_delta() const override {
		return -dimensions + 1;
	}

	uint16_t get_index() const {
		return index;
	}
	uint8_t get_dimensions() const {
		return dimensions;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t index;
	uint8_t dimensions;
};

class New : public Instruction {
public:
	New(Code* code, uint16_t index)
	: Instruction(Kind::New, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::New;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "new";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	uint16_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t index;
};

class NewArray : public Instruction {
public:
	NewArray(Code* code, uint8_t atype)
	: Instruction(Kind::NewArray, code), atype(atype) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::NewArray;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "newarray";
	}
	int8_t get_stack_delta() const override {
		return 0;
	}

	uint8_t get_atype() const {
		return atype;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t atype;
};

class Nop : public Instruction {
public:
	Nop(Code* code) : Instruction(Kind::Nop, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Nop;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "nop";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;

};

class Pop : public Instruction {
public:
	Pop(Code* code) : Instruction(Kind::Pop, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Pop;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "pop";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class Pop2 : public Instruction {
public:
	Pop2(Code* code) : Instruction(Kind::Pop2, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Pop2;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "pop2";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class PutField : public Instruction {
public:
	PutField(Code* code, uint16_t index)
	: Instruction(Kind::PutField, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::PutField;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "putfield";
	}
	int8_t get_stack_delta() const override {
		return -2;
	}

	uint16_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t index;
};

class PutStatic : public Instruction {
public:
	PutStatic(Code* code, uint16_t index)
	: Instruction(Kind::PutStatic, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::PutStatic;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "putstatic";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	uint16_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t index;
};

class Ret : public Instruction {
public:
	Ret(Code* code, uint8_t index)
	: Instruction(Kind::Ret, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Ret;
	}

	uint16_t get_byte_size() const override {
		return 2;
	}
	const char* get_mnemonic() const override {
		return "ret";
	}
	int8_t get_stack_delta() const override {
		return 0;
	}

	uint8_t get_index() const {
		return index;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint8_t index;
};

class Return : public Instruction {
public:
	Return(Code* code) : Instruction(Kind::Return, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Return;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "return";
	}
	void write_buffer(uint8_t** buffer) const override;
};

class SALoad : public Instruction {
public:
	SALoad(Code* code) : Instruction(Kind::SALoad, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::SALoad;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "saload";
	}

	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class SAStore : public Instruction {
public:
	SAStore(Code* code) : Instruction(Kind::SAStore, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::SAStore;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "sastore";
	}

	int8_t get_stack_delta() const override {
		return -3;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class SIPush  : public Instruction {
public:
	SIPush (Code* code, uint16_t value)
	: Instruction(Kind::SIPush , code), value(value) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::SIPush ;
	}

	uint16_t get_byte_size() const override {
		return 3;
	}
	const char* get_mnemonic() const override {
		return "sipush";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	uint16_t get_value() const {
		return value;
	}
	void write_buffer(uint8_t** buffer) const override;
private:
	uint16_t value;
};

class Swap : public Instruction {
public:
	Swap(Code* code) : Instruction(Kind::Swap, code) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Swap;
	}

	uint16_t get_byte_size() const override {
		return 1;
	}
	const char* get_mnemonic() const override {
		return "swap";
	}

	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;
};

class TableSwitch : public Instruction {
public:
	TableSwitch(Code* code, uint8_t padding, int32_t default_offset,
	            int32_t low, int32_t high, std::vector<int32_t> offsets)
	: Instruction(Kind::TableSwitch, code), padding(padding),
	  default_offset(default_offset), low(low), high(high),
	  offsets(std::move(offsets)) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::TableSwitch;
	}

	uint16_t get_byte_size() const override;
	const char* get_mnemonic() const override {
		return "tableswitch";
	}
	void write_buffer(uint8_t** buffer) const override;

	int8_t get_stack_delta() const override {
		return -1;
	}

	uint8_t get_padding() const {
		return padding;
	}
	int32_t get_default_offset() const {
		return default_offset;
	}
	const std::vector<int32_t>& get_offsets() const {
		return offsets;
	}
	void set_default_offset(int32_t o) {
		default_offset = o;
	}
	void clear_offsets() {
		offsets.clear();
	}
	void push_back_offset(int32_t o) {
		offsets.push_back(o);
	}
	void set_padding(uint8_t p) {
		padding = p;
	}

	Instruction* get_default_target() const{
		return default_target;
	}
	void set_default_target(Instruction* target) {
		default_target = target;
	}

	std::vector<Instruction*>& get_targets() {
		return targets;
	}
	void push_back_target(Instruction* target) {
		targets.push_back(target);
	}
private:
	uint8_t padding;
	int32_t default_offset;
	int32_t low;
	int32_t high;
	std::vector<int32_t> offsets;

	Instruction* default_target;
	std::vector<Instruction*> targets;
};

class WideALoad : public Instruction {
public:
	WideALoad(Code* code, uint16_t index)
	: Instruction(Kind::Wide, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Wide;
	}

	uint16_t get_byte_size() const override {
		return 4;
	}
	const char* get_mnemonic() const override {
		return "wide aload";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class WideAStore : public Instruction {
public:
	WideAStore(Code* code, uint16_t index)
	: Instruction(Kind::Wide, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Wide;
	}

	uint16_t get_byte_size() const override {
		return 4;
	}
	const char* get_mnemonic() const override {
		return "wide astore";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class WideDLoad : public Instruction {
public:
	WideDLoad(Code* code, uint16_t index)
	: Instruction(Kind::Wide, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Wide;
	}

	uint16_t get_byte_size() const override {
		return 4;
	}
	const char* get_mnemonic() const override {
		return "wide dload";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class WideDStore : public Instruction {
public:
	WideDStore(Code* code, uint16_t index)
	: Instruction(Kind::Wide, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Wide;
	}

	uint16_t get_byte_size() const override {
		return 4;
	}
	const char* get_mnemonic() const override {
		return "wide dstore";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class WideFLoad : public Instruction {
public:
	WideFLoad(Code* code, uint16_t index)
	: Instruction(Kind::Wide, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Wide;
	}

	uint16_t get_byte_size() const override {
		return 4;
	}
	const char* get_mnemonic() const override {
		return "wide fload";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class WideFStore : public Instruction {
public:
	WideFStore(Code* code, uint16_t index)
	: Instruction(Kind::Wide, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Wide;
	}

	uint16_t get_byte_size() const override {
		return 4;
	}
	const char* get_mnemonic() const override {
		return "wide fstore";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class WideIInc : public Instruction {
public:
	WideIInc(Code* code, uint16_t index, uint16_t value)
	: Instruction(Kind::Wide, code), index(index), value(value) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Wide;
	}

	uint16_t get_byte_size() const override {
		return 6;
	}
	const char* get_mnemonic() const override {
		return "wide iinc";
	}
	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
	uint16_t get_value() const {
		return value;
	}
private:
	uint16_t index;
	uint16_t value;
};

class WideILoad : public Instruction {
public:
	WideILoad(Code* code, uint16_t index)
	: Instruction(Kind::Wide, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Wide;
	}

	uint16_t get_byte_size() const override {
		return 4;
	}
	const char* get_mnemonic() const override {
		return "wide iload";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class WideIStore : public Instruction {
public:
	WideIStore(Code* code, uint16_t index)
	: Instruction(Kind::Wide, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Wide;
	}

	uint16_t get_byte_size() const override {
		return 4;
	}
	const char* get_mnemonic() const override {
		return "wide istore";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class WideLLoad : public Instruction {
public:
	WideLLoad(Code* code, uint16_t index)
	: Instruction(Kind::Wide, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Wide;
	}

	uint16_t get_byte_size() const override {
		return 4;
	}
	const char* get_mnemonic() const override {
		return "wide lload";
	}
	int8_t get_stack_delta() const override {
		return 1;
	}

	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class WideLStore : public Instruction {
public:
	WideLStore(Code* code, uint16_t index)
	: Instruction(Kind::Wide, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Wide;
	}

	uint16_t get_byte_size() const override {
		return 4;
	}
	const char* get_mnemonic() const override {
		return "wide lstore";
	}
	int8_t get_stack_delta() const override {
		return -1;
	}

	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

class WideRet : public Instruction {
public:
	WideRet(Code* code, uint16_t index)
	: Instruction(Kind::Wide, code), index(index) {}

	static bool classof(const Instruction* instruction) {
		return instruction->get_kind() == Kind::Wide;
	}

	uint16_t get_byte_size() const override {
		return 4;
	}
	const char* get_mnemonic() const override {
		return "wide ret";
	}
	int8_t get_stack_delta() const override {
		return 0;
	}

	void write_buffer(uint8_t** buffer) const override;

	uint16_t get_index() const {
		return index;
	}
private:
	uint16_t index;
};

}

#endif
