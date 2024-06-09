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

#define MAX_INSTRUCTION_SIZE (15)

InsAnalysis PVZ::Mixin::Fetch(int ins_addr, BYTE *ins_data) {
	// һ����ȡ��
	BYTE buf[MAX_INSTRUCTION_SIZE];
	Memory::ReadArray<BYTE>(ins_addr, buf, MAX_INSTRUCTION_SIZE);

	InsAnalysis ins = {};

	Decode(buf, MAX_INSTRUCTION_SIZE, &ins);

	// ��insԭ����д��ins_data��
	if (ins_data != NULL) {
		memcpy(ins_data, buf, ins.len);
	}

	return ins;
}
