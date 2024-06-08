#include "Mixin.h"

using namespace PVZ;
using namespace PVZ::Mixin;

bool PVZ::Mixin::Modify(int region_start, int region_end, BYTE* code, size_t code_len) {
	size_t region_len = region_end - region_start;
	if (region_len - region_end < code_len) {
		return false;
	}

	BYTE* writting_code = new BYTE[region_len];
	memset(writting_code, 0, region_len);
	memcpy(writting_code, code, code_len);

	// �޸Ĵ���
	BOOL status = Memory::WriteArray<BYTE>(region_start, writting_code, region_len);
	return status == TRUE;
}

struct DecodeStream {
	BYTE *buf;
	size_t size;
	int cnt;

	DecodeStream(BYTE* buf, size_t size, int cnt) {

	}
	
	// ȡ����
	template<typename T> 
	T FetchData() {
		// �������� ����
		if (cnt + sizeof(T) > size) {
			throw "Out of Decode Stream Boundary";
		}

		T result = *(T *)(buf + cnt);

		return result;
	}

	// ��ʾ��ȡ
	template<typename T>
	void Consume() {
		cnt += sizeof(T);
	}
};

void DecodePrefix(DecodeStream &ds, InsAnalysis &ins) {
	bool done = false;

	while (!done) {
		BYTE cur = ds.FetchData<BYTE>();

		// �ж��Ƿ�Ϊǰ׺
		// F0ΪLockǰ׺
		// F2 F3ΪRepeatǰ׺
		// 2E, 26, 36, 3EΪ������ǰ׺
		// 66Ϊ��������С����ǰ׺
		// 67Ϊ��ַ��С����ǰ׺
		if (cur == 0xF0) {
			ins.pfx.lock = cur;
		}
		else if (cur == 0xF0) {
			ins.pfx.repeat = cur;
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
			ds.Consume<BYTE>();
		}
	}
}


void DecodeMODRM(DecodeStream &ds, InsAnalysis &ins) {
	BYTE modrm = ds.FetchData<BYTE>();
	ds.Consume<BYTE>();

	ins.modrm.mod = (modrm >> 6) & 0x03;
	ins.modrm.reg = (modrm >> 3) & 0x07;
	ins.modrm.rm  = modrm & 0x07;
}

void DecodeSIB(DecodeStream &ds, InsAnalysis &ins) {
	BYTE sib = ds.FetchData<BYTE>();
	ds.Consume<BYTE>();

	ins.sib.scale = (sib >> 6) & 0x03;
	ins.sib.index = (sib >> 3) & 0x07;
	ins.sib.base  = sib & 0x07;
}

void DecodeOpcode(DecodeStream &ds, InsAnalysis &ins) {
	// ��ȥǰ׺���׸��ֽڱض�Ϊopcode
	ins.opc.byte1 = ds.FetchData<BYTE>();
	ds.Consume<BYTE>();

	// �ڶ��ֽ�
	if (ins.opc.byte1 == 0xF) {

	}
}

#define MAX_INSTRUCTION_SIZE (15)

InsAnalysis PVZ::Mixin::Fetch(int ins_addr, BYTE *ins_data) {
	// һ����ȡ��
	BYTE buf[MAX_INSTRUCTION_SIZE];
	Memory::ReadArray<BYTE>(ins_addr, buf, MAX_INSTRUCTION_SIZE);

	// ������
	DecodeStream ds(buf, MAX_INSTRUCTION_SIZE, 0);

	InsAnalysis ins = {};

	// ����ָ��
	DecodePrefix(ds, ins);
	DecodeOpcode(ds, ins);

	return ins;
}
