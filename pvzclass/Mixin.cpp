#include "Mixin.h"

using namespace PVZ;
using namespace PVZ::Mixin;

bool PVZ::Mixin::Modify(int region_start, int region_end, BYTE* code, size_t code_len) {
	size_t region_len = region_end - region_start;
	if (region_len - region_end < code_len) {
		return false;
	}

	BYTE* writting_code = new BYTE[region_len];
	memset(writting_code, NOP, region_len);
	memcpy(writting_code, code, code_len);

	// �޸Ĵ���
	BOOL status = Memory::WriteArray<BYTE>(region_start, writting_code, region_len);
	delete[] writting_code;
	return status == TRUE;
}

#define MAX_INSTRUCTION_SIZE (15)

InsAnalysis PVZ::Mixin::Fetch(int ins_addr, BYTE *ins_data) {
	// һ����ȡ15���ֽ�,��Ӧ���㹻����ָ��
	BYTE buf[MAX_INSTRUCTION_SIZE];
	Memory::ReadArray<BYTE>(ins_addr, buf, MAX_INSTRUCTION_SIZE);

	InsAnalysis ins = {};

	if (!Decode(buf, MAX_INSTRUCTION_SIZE, &ins)) {
		// ���д�����
	}

	// ��insԭ����д��ins_data��
	if (ins_data != NULL) {
		memcpy(ins_data, buf, ins.len);
	}

	return ins;
}

static int codePlacingAddress = 0;

int& PVZ::Mixin::CodePlacingAddress() {
	if (codePlacingAddress == 0) {
		// pages 10 ~ 20 (40KB in total) belongs to mixin
		codePlacingAddress = Memory::AllocMemory(10, 0);
	}
	return codePlacingAddress;
}

bool PVZ::Mixin::Replace(int region_start, int region_end, BYTE *code, size_t code_len) {
	// ��������Ϊ5��������
	if (region_end - region_start < 5) {
		return false;
	}
	int entrypoint = CodePlacingAddress();
	
	// ��ת��Ŀ���
	int offset = entrypoint - region_start;
	BYTE JmpTo[] = { JMPFAR(entrypoint - (region_start + 5)) };
	if (!Modify(region_start, region_end, STRING(JmpTo))) {
		return false;
	}
	
	// д��Ŀ��ָ��
	Memory::WriteArray<BYTE>(CodePlacingAddress(), code, code_len);
	CodePlacingAddress() += code_len;

	// д�뷵��ָ��
	BYTE JmpBack[] = { JMPFAR(region_end - (CodePlacingAddress() + 5)) };
	Memory::WriteArray<BYTE>(CodePlacingAddress(), STRING(JmpBack));
	CodePlacingAddress() += STRING_LEN(JmpBack);


	return true;
}

bool PVZ::Mixin::Insert(int targetpoint, BYTE *code, size_t code_len, BYTE **origin_code, size_t *origin_code_len) {
	// �������Ѱ��ֱ���������Է���jmpָ��
	int total_len = 0;
	while (total_len < 5) {
		InsAnalysis ins = Fetch(targetpoint + total_len, NULL);
		total_len += ins.len;
	}

	BYTE *buf = new BYTE[total_len];
	PVZ::Memory::ReadArray<BYTE>(targetpoint, buf, total_len);

	int entrypoint = CodePlacingAddress();

	// ��ת��Ŀ���
	int offset = entrypoint - targetpoint;
	BYTE JmpTo[] = { JMPFAR(entrypoint - (targetpoint + 5)) };
	if (!Modify(targetpoint, targetpoint + total_len, STRING(JmpTo))) {
		return false;
	}

	// д��Ŀ��ָ��
	Memory::WriteArray<BYTE>(CodePlacingAddress(), code, code_len);
	CodePlacingAddress() += code_len;

	// д�뱻�滻��ָ��
	Memory::WriteArray<BYTE>(CodePlacingAddress(), buf, total_len);
	CodePlacingAddress() += total_len;

	// д�뷵��ָ��
	BYTE JmpBack[] = { JMPFAR(targetpoint + total_len - (CodePlacingAddress() + 5)) };
	Memory::WriteArray<BYTE>(CodePlacingAddress(), STRING(JmpBack));
	CodePlacingAddress() += STRING_LEN(JmpBack);

	// ���Ҫ��ԭ���Ĵ���
	if (origin_code != NULL && origin_code_len != NULL) {
		*origin_code_len = total_len;
		*origin_code = buf;
	}
	else {
		delete[] buf;
	}
	return true;
}

bool PVZ::Mixin::Redirect(int function_start, int function_end, int new_function_address) {
	BYTE JmpTo[] = { JMPFAR(new_function_address - (function_start + 5)) };
	return PVZ::Mixin::Modify(function_start, function_end, STRING(JmpTo));
}
