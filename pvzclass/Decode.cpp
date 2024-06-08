#include "Mixin.h"

using namespace PVZ;
using namespace PVZ::Mixin;

#include <iostream>

#define RF_ASSERT(expression) if (! (expression)) {std::cout<<"[ERROR] assert(" << #expression << ") failed!" << std::endl; return false;}

enum class VendorType {
	ANY,
	AMD,
	INTEL
};

struct DecodeStream {
	BYTE *buf;
	size_t size;
	int cnt;
	LookupTableEntry *lt;
	int bits;
	VendorType vendor;

	DecodeStream(BYTE *buf, size_t size, int cnt, LookupTableEntry *lt, int bits, VendorType vendor)
		: buf(buf), size(size), cnt(cnt), lt(lt), bits(bits), vendor(vendor)
	{
		lt = lt;
	}

	// 取数据
	template<typename T>
	bool FetchData(T *data) {
		// 判断是否超出界限
		RF_ASSERT(cnt + sizeof(T) <= size);

		*data = *(T *)(buf + cnt);
		return true;
	}

	// 表示已取
	template<typename T>
	bool Consume() {
		// 判断是否超出界限
		RF_ASSERT(cnt + sizeof(T) <= size);

		cnt += sizeof(T);
		return true;
	}
};

static inline bool AnalyseOperandMode(DecodeStream &ds, InsAnalysis &ins, WORD *idx) {
	if (ds.bits == 64) {
		*idx = ins.pfx.rex.w ? 64 : ((ins.pfx.operand != 0) ? 16 : 32);
	}
	else if (ds.bits == 32) {
		*idx = (ins.pfx.operand != 0) ? 16 : 32;
	}
	else if (ds.bits == 16) {
		*idx = (ins.pfx.operand != 0) ? 32 : 16;
	}
	else {
		// unreachable
		RF_ASSERT(false);
	}
	return true;
}

static inline bool AnalyseAddressMode(DecodeStream &ds, InsAnalysis &ins, WORD *idx) {
	if (ds.bits == 64) {
		*idx = (ins.pfx.address != 0) ? 32 : 64;
	}
	else if (ds.bits == 32) {
		*idx = (ins.pfx.address != 0) ? 16 : 32;
	}
	else if (ds.bits == 16) {
		*idx = (ins.pfx.address != 0) ? 32 : 16;
	}
	else {
		// unreachable
		RF_ASSERT(false);
	}
	return true;
}

static inline bool AnalyseOperandSize(DecodeStream &ds, InsAnalysis &ins, WORD osize, WORD *size) {
	switch (osize) {
	case OperandSize::V:
		*size = ins.operand_size;
		break;
	case OperandSize::Z:
		*size = ins.operand_size == 16 ? 16 : 32;
		break;
	case OperandSize::Y:
		*size = ins.operand_size == 16 ? 32 : ins.operand_size;
		break;
	case OperandSize::RDQ:
		*size = ins.operand_size == 64 ? 64 : 32;
		break;
	case OperandSize::X:
		//TODO: Complete it
		return false;
	default:
		*size = osize;
		break;
	}
	return true;
}

static inline bool AnalyseMnemonic(DecodeStream &ds, InsAnalysis &ins) {
	// 3DNOW!指令
	if (ins.definition.mnemonic == MnemonicCode::MC_3DNOW) {
		// TODO: Complete it
	}
	// SWAPGS: 64位特供
	RF_ASSERT(ins.definition.mnemonic != MnemonicCode::MC_SWAPGS || ds.bits != 64);
	return true;
}

bool DecodePrefix(DecodeStream &ds, InsAnalysis &ins) {
	bool done = false;
	BYTE cur;

	while (!done) {
		RF_ASSERT(ds.FetchData<BYTE>(&cur));

		// 判断是否为前缀
		// F0为Lock前缀
		// F2 F3为Repeat前缀
		// 2E, 26, 36, 3E为段重载前缀
		// 66为操作数大小重载前缀
		// 67为地址大小重载前缀
		if (cur == 0xF0) {
			ins.pfx.lock = cur;
		}
		else if (cur == 0xF0) {
			ins.pfx.str = cur;
		}
		else if (
			cur == 0x2E || cur == 0x26 ||
			cur == 0x36 || cur == 0x3E ||
			cur == 0x64 || cur == 0x65
			) {
			ins.pfx.segment = cur;
		}
		else if (cur == 0x66) {
			ins.pfx.operand = cur;
		}
		else if (cur == 0x67) {
			ins.pfx.address = cur;
		}
		else {
			done = true;
		}

		if (!done) {
			RF_ASSERT(ds.Consume<BYTE>());
		}
		else {
			// 最后一个字节 判断是否为REX
			if (ds.bits == 64 && (cur & 0xF0) == 0x40) {
				ins.pfx.rex.raw = cur;
				ins.pfx.rex.w = ((cur >> 3) & 0x1);
				ins.pfx.rex.r = ((cur >> 2) & 0x1);
				ins.pfx.rex.x = ((cur >> 1) & 0x1);
				ins.pfx.rex.b = (cur & 0x1);
				RF_ASSERT(ds.Consume<BYTE>())
			}
		}
	}

	return true;
}

bool DecodeSIB(DecodeStream &ds, InsAnalysis &ins) {
	BYTE sib;
	RF_ASSERT(ds.FetchData<BYTE>(&sib));
	RF_ASSERT(ds.Consume<BYTE>());

	ins.sib.scale = (sib >> 6) & 0x03;
	ins.sib.index = (sib >> 3) & 0x07;
	ins.sib.base = sib & 0x07;
	ins.sib.raw = sib;
	return true;
}

bool TestModrm(DecodeStream &ds, InsAnalysis &ins) {
	if (!ins.modrm_decoded) {
		BYTE modrm;
		RF_ASSERT(ds.FetchData<BYTE>(&modrm));
		RF_ASSERT(ds.Consume<BYTE>());

		ins.modrm.mod = (modrm >> 6) & 0x03;
		ins.modrm.reg = (modrm >> 3) & 0x07;
		ins.modrm.rm  = modrm & 0x07;
		ins.modrm.raw = modrm;

		ins.modrm_decoded = true;
	}
	return true;
}

bool AnalysePfxRep(DecodeStream &ds, InsAnalysis &ins) {
	if (ins.pfx.str == 0xf3) {
		if (PfxBits::STR(ins.definition.prefix)) {
			ins.pfx.rep = 0xf3;
		}
		else {
			ins.pfx.repe = 0xf3;
		}
	}
	else if (ins.pfx.str == 0xf2) {
		ins.pfx.repne = 0xf3;
	}
	return true;
}

bool AnalyseMode(DecodeStream &ds, InsAnalysis &ins) {
	if (ds.bits == 16) {
		ins.operand_size = (ins.pfx.operand != 0) ? 32 : 16;
		ins.address_size = (ins.pfx.address != 0) ? 32 : 16;
	}
	else if (ds.bits == 32) {
		ins.operand_size = (ins.pfx.operand != 0) ? 16 : 32;
		ins.address_size = (ins.pfx.address != 0) ? 16 : 32;
	}
	else if (ds.bits == 64) {
		//TODO: Complete it
		return false;
	}
	else {
		// unreachable
		RF_ASSERT(false);
	}
	return true;
}

bool DecodeOperand_CodeA(DecodeStream &ds, InsAnalysis &ins, Operand *opr) {
	// 16bits seg16:off16
	// 32bits seg16:off32
	if (ins.operand_size == 16) {
		opr->type = OperandType::O_PTR;
		opr->size = OperandSize::D;

		RF_ASSERT(ds.FetchData<WORD>(&opr->imm.ptr16.segment));
		RF_ASSERT(ds.Consume<WORD>());
		RF_ASSERT(ds.FetchData<WORD>(&opr->imm.ptr16.offset));
		RF_ASSERT(ds.Consume<WORD>());
	}
	else if (ins.operand_size == 32) {
		opr->type = OperandType::O_PTR;
		opr->size = OperandSize::A;

		RF_ASSERT(ds.FetchData<WORD>(&opr->imm.ptr32.segment));
		RF_ASSERT(ds.Consume<WORD>());
		RF_ASSERT(ds.FetchData<DWORD>(&opr->imm.ptr32.offset));
		RF_ASSERT(ds.Consume<DWORD>());
	}
	return true;
}

// 通用寄存器
bool DecodeGPR(DecodeStream &ds, InsAnalysis &ins, WORD size, DWORD cnt, RegisterType *reg) {
	*reg = R_NONE;
	if (size == 64) {
		// 64bits: r*x,r*(rax,rbx,...,r9,r10,...)型寄存器
		*reg = (RegisterType)(R_RAX + cnt);
	}
	else if (size == 32) {
		// 32bits: e*x(eax,ebx,...)型寄存器
		*reg = (RegisterType)(R_EAX + cnt);
	}
	else if (size == 16) {
		// 16bits: *x(ax,bx,...)型寄存器
		*reg = (RegisterType)(R_AX + cnt);
	}
	else if (size == 8) {
		// 8bits: *l,*h(al,bl,...,ah,bh,...)型寄存器
		if (ds.bits == 64 && (ins.pfx.rex.raw != 0)) {
			if (cnt >= 4) *reg = (RegisterType)(R_SPL + cnt - 4);
			else          *reg = (RegisterType)(R_AL + cnt - 4);
		}
		else {
			*reg = (RegisterType)(R_AL + cnt - 4);
		}
	}
	else {
		RF_ASSERT(false);
	}
	return true;
}

// 寄存器
bool DecodeReg(DecodeStream &ds, InsAnalysis &ins, Operand *opr, WORD osize, RegisterGroup group, DWORD cnt) {
	WORD size;
	RF_ASSERT(AnalyseOperandSize(ds, ins, osize, &size));

	RegisterType reg;
	if (group == RegisterGroup::GPR) {
		RF_ASSERT(DecodeGPR(ds, ins, size, cnt, &reg));
	}
	else {
		RegisterType base;
		switch (group) {
		case RegisterGroup::MMX:
			cnt &= 7;
			base = R_MM0;
			break;
		case RegisterGroup::XMM:
			base = (size == OperandSize::QQ) ? R_YMM0 : R_XMM0;
			break;
		case RegisterGroup::CR:
			base = R_CR0;
			break;
		case RegisterGroup::DB:
			base = R_DR0;
			break;
		case RegisterGroup::SEG:
			cnt &= 7;
			// 总共只有六个段寄存器
			RF_ASSERT(cnt > 5);
			base = R_ES;
			break;
		default:
			RF_ASSERT(false);
			break;
		}
		reg = (RegisterType)(base + cnt);
	}

	opr->type = O_REG;
	opr->base = reg;
	opr->size = size;

	return true;
}

// 立即值
bool DecodeImm(DecodeStream &ds, InsAnalysis &ins, Operand *opr, WORD osize) {
	RF_ASSERT(AnalyseOperandSize(ds, ins, osize, &opr->size));
	opr->type = O_IMM;

	switch (opr->size) {
	case 8:
		RF_ASSERT(ds.FetchData<BYTE>(&opr->imm.val8));
		RF_ASSERT(ds.Consume<BYTE>());
		break;
	case 16:
		RF_ASSERT(ds.FetchData<WORD>(&opr->imm.val16));
		RF_ASSERT(ds.Consume<WORD>());
		break;
	case 32:
		RF_ASSERT(ds.FetchData<DWORD>(&opr->imm.val32));
		RF_ASSERT(ds.Consume<DWORD>());
		break;
	case 64:
		RF_ASSERT(ds.FetchData<QWORD>(&opr->imm.val64));
		RF_ASSERT(ds.Consume<QWORD>());
		break;
	default:
		RF_ASSERT(false);
	}
	return true;
}

// Displacement项
bool DecodeDisplacement(DecodeStream &ds, InsAnalysis &ins, Operand *opr, WORD osize) {
	RF_ASSERT(AnalyseOperandSize(ds, ins, osize, &opr->size));
	opr->type = O_IMM;

	switch (opr->size) {
	case 8:
		opr->disp_size = 8;
		RF_ASSERT(ds.FetchData<BYTE>(&opr->imm.val8));
		RF_ASSERT(ds.Consume<BYTE>());
		break;
	case 16:
		opr->disp_size = 16;
		RF_ASSERT(ds.FetchData<WORD>(&opr->imm.val16));
		RF_ASSERT(ds.Consume<WORD>());
		break;
	case 32:
		opr->disp_size = 32;
		RF_ASSERT(ds.FetchData<DWORD>(&opr->imm.val32));
		RF_ASSERT(ds.Consume<DWORD>());
		break;
	case 64:
		opr->disp_size = 64;
		RF_ASSERT(ds.FetchData<QWORD>(&opr->imm.val64));
		RF_ASSERT(ds.Consume<QWORD>());
		break;
	default:
		opr->disp_size = 0;
		RF_ASSERT(false);
	}
	return true;
}

// ModRM Reg项
bool DecodeModRM_Reg(DecodeStream &ds, InsAnalysis &ins, Operand *opr, WORD osize, RegisterGroup group) {
	RF_ASSERT(TestModrm(ds, ins));
	DWORD rm = ((ins.pfx.rex.r << 3) | ins.modrm.reg);
	return DecodeReg(ds, ins, opr, osize, group, rm);
}

// ModRM RM项
bool DecodeModRM_RM(DecodeStream &ds, InsAnalysis &ins, Operand *opr, WORD osize, RegisterGroup group) {
	RF_ASSERT(TestModrm(ds, ins));

	// mod, rm
	DWORD mod = ins.modrm.mod;
	DWORD rm = ((ins.pfx.rex.r << 3) | ins.modrm.rm);

	// mod = 0b11, rm段表示一个寄存器
	if (mod == 3) {
		RF_ASSERT(DecodeReg(ds, ins, opr, osize, group, rm));
		return true;
	}

	// mod != 0b11, 则是对内存的访问
	opr->type = O_MEM;
	RF_ASSERT(AnalyseOperandSize(ds, ins, osize, &opr->size));

	size_t size = 0;

	if (ins.address_size == 64) {
		opr->base = (RegisterType)(R_RAX + rm);
		if (mod == 1) {
			size = 8;
		}
		else if (mod == 2) {
			size = 32;
		}
		else if (mod == 0 && (rm & 7) == 5) {
			opr->base = R_RIP;
			size = 32;
		}
		else {
			size = 0;
		}

		// 处理sib
		if ((rm & 7) == 4) {
			DecodeSIB(ds, ins);

			// base, index
			opr->scale = (1 << ins.sib.scale);
			opr->base = (RegisterType)(R_RAX + (ins.sib.base | (ins.pfx.rex.b << 3)));
			opr->index = (RegisterType)(R_RAX + (ins.sib.index | (ins.pfx.rex.x << 3)));

			// RSP不能作为index,只能作为base
			if (opr->index == R_RSP) {
				opr->index = R_NONE;
				opr->scale = 0;
			}

			// 以RBP与R13为base(特殊情况)
			if (opr->base == R_RBP || opr->base == R_R13) {
				if (mod == 0) {
					opr->base = R_NONE;
				}
				if (mod == 1) {
					size = 8;
				}
				else {
					size = 32;
				}
			}
		}
		else {
			opr->index = R_NONE;
			opr->scale = 0;
		}
	}
	else if (ins.address_size == 32) {
		opr->base = (RegisterType)(R_EAX + rm);
		if (mod == 1) {
			size = 8;
		}
		else if (mod == 2) {
			size = 32;
		}
		else if (mod == 0 && rm == 5) {
			opr->base = R_NONE;
			size = 32;
		}
		else {
			size = 0;
		}

		// 处理sib
		if ((rm & 7) == 4) {
			DecodeSIB(ds, ins);

			// base, index
			opr->scale = (1 << ins.sib.scale);
			opr->base = (RegisterType)(R_RAX + (ins.sib.base | (ins.pfx.rex.b << 3)));
			opr->index = (RegisterType)(R_RAX + (ins.sib.index | (ins.pfx.rex.x << 3)));

			// ESP不能作为index,只能作为base
			if (opr->index == R_ESP) {
				opr->index = R_NONE;
				opr->scale = 0;
			}

			// 以EBP为base(特殊情况)
			if (opr->base == R_EBP) {
				if (mod == 0) {
					opr->base = R_NONE;
				}
				if (mod == 1) {
					size = 8;
				}
				else {
					size = 32;
				}
			}
		}
		else {
			opr->index = R_NONE;
			opr->scale = 0;
		}
	}
	else if (ins.address_size == 16) {
		const RegisterType bases[] = {
			R_BX, R_BX, R_BP, R_BP,
			R_SI, R_DI, R_BP, R_BX
		};
		const RegisterType indices[] = {
			R_SI, R_DI, R_SI, R_DI,
			R_NONE, R_NONE, R_NONE, R_NONE
		};
		opr->base = bases[rm & 7];
		opr->index = indices[rm & 7];
		opr->scale = 0;
		if (mod == 0 && rm == 6) {
			size = 16;
			opr->base = R_NONE;
		}
		else if (mod == 1) {
			size = 8;
		}
		else if (mod == 2) {
			size = 16;
		}
	}
	else {
		RF_ASSERT(false);
	}

	if (size != 0) {
		return DecodeDisplacement(ds, ins, opr, size);
	}
	else {
		opr->disp_size = 0;
	}

	return true;
}

// 仅偏移
bool DecodeMemOffset(DecodeStream &ds, InsAnalysis &ins, Operand *opr, WORD osize) {
	opr->type = O_MEM;
	opr->base = R_NONE;
	opr->index = R_NONE;
	opr->scale = 0;
	RF_ASSERT(AnalyseOperandSize(ds, ins, osize, &opr->size));
	return DecodeDisplacement(ds, ins, opr, ins.address_size);
}

bool DecodeOperand(DecodeStream &ds, InsAnalysis &ins, OperandDefinition &def, Operand *opr) {
	opr->type = OperandType::O_NONE;

	switch (def.code) {
	case OperandCode::A:
		RF_ASSERT(DecodeOperand_CodeA(ds, ins, opr));
		break;
	case OperandCode::sI:
	case OperandCode::I:
		DecodeImm(ds, ins, opr, def.size);
		break;
	case OperandCode::I1:
		opr->imm.val32 = 1;
		opr->type = O_CONST;
		break;
	case OperandCode::I3:
		opr->imm.val32 = 3;
		opr->type = O_CONST;
		break;
	case OperandCode::J:
		DecodeImm(ds, ins, opr, def.size);
		opr->type = O_JIMM;
		break; 
	case OperandCode::F:
		ins.far_flag = true;
	case OperandCode::M:
		TestModrm(ds, ins);
		RF_ASSERT(ins.modrm.mod != 3);
	case OperandCode::E:
		DecodeModRM_RM(ds, ins, opr, def.size, RegisterGroup::GPR);
		break;
	case OperandCode::G:
		DecodeModRM_Reg(ds, ins, opr, def.size, RegisterGroup::GPR);
		break;
	case OperandCode::N:
		TestModrm(ds, ins);
		RF_ASSERT(ins.modrm.mod != 3);
		DecodeModRM_RM(ds, ins, opr, def.size, RegisterGroup::MMX);
		break;
	case OperandCode::Q:
		DecodeModRM_RM(ds, ins, opr, def.size, RegisterGroup::MMX);
		break;
	case OperandCode::P:
		DecodeModRM_Reg(ds, ins, opr, def.size, RegisterGroup::MMX);
		break;
	case OperandCode::U:
		TestModrm(ds, ins);
		RF_ASSERT(ins.modrm.mod != 3);
		DecodeModRM_RM(ds, ins, opr, def.size, RegisterGroup::XMM);
		break;
	case OperandCode::W:
		DecodeModRM_RM(ds, ins, opr, def.size, RegisterGroup::XMM);
		break;
	case OperandCode::V:
		DecodeModRM_Reg(ds, ins, opr, def.size, RegisterGroup::XMM);
		break;
	case OperandCode::S:
		DecodeModRM_Reg(ds, ins, opr, def.size, RegisterGroup::SEG);
		break;
	case OperandCode::MR: {
		TestModrm(ds, ins);
		WORD osize = (ins.modrm.mod == 3) ? MxRegSize(def.size) : MxMemSize(def.size);
		RF_ASSERT(DecodeModRM_RM(ds, ins, opr, osize, RegisterGroup::GPR));
		break;
	}
	case OperandCode::MU: {
		TestModrm(ds, ins);
		WORD osize = (ins.modrm.mod == 3) ? MxRegSize(def.size) : MxMemSize(def.size);
		RF_ASSERT(DecodeModRM_RM(ds, ins, opr, osize, RegisterGroup::XMM));
		break;
	}
	case OperandCode::O:
		DecodeMemOffset(ds, ins, opr, def.size);
		break;
	case OperandCode::R0:
	case OperandCode::R1:
	case OperandCode::R2:
	case OperandCode::R3:
	case OperandCode::R4:
	case OperandCode::R5:
	case OperandCode::R6:
	case OperandCode::R7: {
		DWORD num = (DWORD)def.code - (DWORD)OperandCode::R0;
		DWORD cnt = (ins.pfx.rex.b << 3) | num;
		DecodeReg(ds, ins, opr, def.size, RegisterGroup::GPR, cnt);
		break;
	}
	case OperandCode::AL:
	case OperandCode::AX:
	case OperandCode::eAX:
	case OperandCode::rAX:
		DecodeReg(ds, ins, opr, def.size, RegisterGroup::GPR, 0);
		break;
	case OperandCode::CL:
	case OperandCode::CX:
	case OperandCode::eCX:
	case OperandCode::rCX:
		DecodeReg(ds, ins, opr, def.size, RegisterGroup::GPR, 1);
		break;
	case OperandCode::DL:
	case OperandCode::DX:
	case OperandCode::eDX:
	case OperandCode::rDX:
		DecodeReg(ds, ins, opr, def.size, RegisterGroup::GPR, 2);
		break;
	case OperandCode::R:
		TestModrm(ds, ins);
		RF_ASSERT(ins.modrm.mod != 3);
		DecodeModRM_RM(ds, ins, opr, def.size, RegisterGroup::GPR);
		break;
	case OperandCode::C:
		DecodeModRM_Reg(ds, ins, opr, def.size, RegisterGroup::CR);
		break;
	case OperandCode::D:
		DecodeModRM_Reg(ds, ins, opr, def.size, RegisterGroup::DB);
		break;
	case OperandCode::ES:
	case OperandCode::CS:
	case OperandCode::DS:
	case OperandCode::SS:
	case OperandCode::FS:
	case OperandCode::GS: {
		// 64位只允许使用fs与gs
		RF_ASSERT(ds.bits != 64 || def.code == OperandCode::FS || def.code == OperandCode::GS);

		opr->type = O_REG;
		DWORD num = (DWORD)def.code - (DWORD)OperandCode::ES;
		opr->base = (RegisterType)(R_ES + num);
		opr->size = 16;
		break;
	}
	case OperandCode::ST0:
	case OperandCode::ST1:
	case OperandCode::ST2:
	case OperandCode::ST3:
	case OperandCode::ST4:
	case OperandCode::ST5:
	case OperandCode::ST6:
	case OperandCode::ST7: {
		opr->type = O_REG;
		DWORD num = (DWORD)def.code - (DWORD)OperandCode::ST0;
		opr->base = (RegisterType)(R_ST0 + num);
		opr->size = 80;
		break;
	}
	case OperandCode::L:
		// TODO: Complete it
		return false;
	case OperandCode::H:
		// TODO: Complete it
		return false;
	default:
		opr->type = O_NONE;
		break;
	}
	return true;
}

bool DecodeOperands(DecodeStream &ds, InsAnalysis &ins) {
	RF_ASSERT(DecodeOperand(ds, ins, ins.definition.operand1, &ins.operands[0]));
	if (ins.operands[0].type != OperandType::O_NONE) {
		RF_ASSERT(DecodeOperand(ds, ins, ins.definition.operand2, &ins.operands[1]));
	}
	if (ins.operands[1].type != OperandType::O_NONE) {
		RF_ASSERT(DecodeOperand(ds, ins, ins.definition.operand3, &ins.operands[2]));
	}
	if (ins.operands[2].type != OperandType::O_NONE) {
		RF_ASSERT(DecodeOperand(ds, ins, ins.definition.operand4, &ins.operands[3]));
	}
	return true;
}

bool DecodeInstruction(DecodeStream &ds, InsAnalysis &ins, WORD tok) {
	RF_ASSERT((tok & 0x8000) == 0);

	ins.definition = InstructionTable[tok];
	RF_ASSERT(AnalysePfxRep(ds, ins));
	RF_ASSERT(AnalyseMode(ds, ins));
	RF_ASSERT(DecodeOperands(ds, ins));
	RF_ASSERT(AnalyseMnemonic(ds, ins));
	return true;
}

bool DecodeOpcode(DecodeStream &ds, InsAnalysis &ins);

bool DecodeOpcodeExt(DecodeStream &ds, InsAnalysis &ins, WORD tok) {
	// 普通指令
	if ((tok & 0x8000) == 0) {
		return DecodeInstruction(ds, ins, tok);
	}

	// 由GROUP标识的特殊指令 去掉GROUP标记获取相应查找表
	ds.lt = &LookupTable[((~0x8000) & tok)];

	// 3DNOW指令
	if (ds.lt->type == ITabType::_3DNOW) {
		// TODO: Complete it
		return false;
	}

	WORD idx;

	switch (ds.lt->type) {
	case ITabType::TABLE:
		RF_ASSERT(ds.Consume<BYTE>());
		return DecodeOpcode(ds, ins);
	case ITabType::MOD:
		RF_ASSERT(TestModrm(ds, ins));
		// if rm == 0b11, idx = 1, or idx = 0.
		idx = (ins.modrm.rm == 0x03) ? 1 : 0;
		break;
	case ITabType::REG:
		RF_ASSERT(TestModrm(ds, ins));
		idx = ins.modrm.reg;
		break;
	case ITabType::RM:
		RF_ASSERT(TestModrm(ds, ins));
		idx = ins.modrm.rm;
		break;
	case ITabType::MODE:
		// if bits == 64, idx = 1, or idx = 0
		idx = (ds.bits == 64) ? 1 : 0;
		break;
	case ITabType::OSIZE:
		RF_ASSERT(AnalyseOperandMode(ds, ins, &idx));
		break;
	case ITabType::ASIZE:
		RF_ASSERT(AnalyseAddressMode(ds, ins, &idx));
		break;
	case ITabType::X87:
		RF_ASSERT(TestModrm(ds, ins));
		idx = ins.modrm.raw - 0xC0;
		break;
	case ITabType::VENDOR:
		if (ds.vendor == VendorType::ANY) {
			// 选个能用的
			idx = (ds.lt->table[0] == 0) ? 1 : 0;
		}
		else if (ds.vendor == VendorType::AMD) {
			idx = 0;
		}
		else {
			idx = 1;
		}
		break;
	case ITabType::SSE:
		// TODO: Complete it
		return false;
	case ITabType::VEX:
		// TODO: Complete it
		return false;
	case ITabType::VEX_W:
		// TODO: Complete it
		return false;
	case ITabType::VEX_L:
		// TODO: Complete it
		return false;
	default:
		RF_ASSERT(false);
	}

	return DecodeOpcodeExt(ds, ins, ds.lt->table[idx]);
}

bool DecodeOpcode(DecodeStream &ds, InsAnalysis &ins) {
	// 获得当前字节, 查表判断类型
	BYTE cur;
	RF_ASSERT(ds.FetchData<BYTE>(&cur));
	RF_ASSERT(ds.Consume<BYTE>());
	RF_ASSERT(ds.lt->type == ITabType::TABLE);

	WORD tok = ds.lt->table[cur];
	return DecodeOpcodeExt(ds, ins, tok);
}

#include <iostream>

bool PVZ::Mixin::Decode(BYTE *buf, size_t bufsz, InsAnalysis *ins) {
	// 解码流
	DecodeStream ds(buf, bufsz, 0, &LookupTable[0], 32, VendorType::ANY);

	// 解析指令
	RF_ASSERT(DecodePrefix(ds, *ins));
	RF_ASSERT(DecodeOpcode(ds, *ins));

	ins->len = ds.cnt;
	return true;
}