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

	// 修改代码
	BOOL status = Memory::WriteArray<BYTE>(region_start, writting_code, region_len);
	delete[] writting_code;
	return status == TRUE;
}

#define MAX_INSTRUCTION_SIZE (15)

InsAnalysis PVZ::Mixin::Fetch(int ins_addr, BYTE *ins_data) {
	// 一次性取15个字节,以应对足够长的指令
	BYTE buf[MAX_INSTRUCTION_SIZE];
	Memory::ReadArray<BYTE>(ins_addr, buf, MAX_INSTRUCTION_SIZE);

	InsAnalysis ins = {};

	if (!Decode(buf, MAX_INSTRUCTION_SIZE, &ins)) {
		// 进行错误处理
	}

	// 将ins原数据写入ins_data中
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
	// 长度至少为5才能容纳
	if (region_end - region_start < 5) {
		return false;
	}
	int entrypoint = CodePlacingAddress();
	
	// 跳转至目标点
	int offset = entrypoint - region_start;
	BYTE JmpTo[] = { JMPFAR(entrypoint - (region_start + 5)) };
	if (!Modify(region_start, region_end, STRING(JmpTo))) {
		return false;
	}
	
	// 写入目标指令
	Memory::WriteArray<BYTE>(CodePlacingAddress(), code, code_len);
	CodePlacingAddress() += code_len;

	// 写入返回指令
	BYTE JmpBack[] = { JMPFAR(region_end - (CodePlacingAddress() + 5)) };
	Memory::WriteArray<BYTE>(CodePlacingAddress(), STRING(JmpBack));
	CodePlacingAddress() += STRING_LEN(JmpBack);


	return true;
}

bool PVZ::Mixin::Insert(int targetpoint, BYTE *code, size_t code_len, BYTE **origin_code, size_t *origin_code_len) {
	// 首先向后寻找直至长度足以放置jmp指令
	int total_len = 0;
	while (total_len < 5) {
		InsAnalysis ins = Fetch(targetpoint + total_len, NULL);
		total_len += ins.len;
	}

	BYTE *buf = new BYTE[total_len];
	PVZ::Memory::ReadArray<BYTE>(targetpoint, buf, total_len);

	int entrypoint = CodePlacingAddress();

	// 跳转至目标点
	int offset = entrypoint - targetpoint;
	BYTE JmpTo[] = { JMPFAR(entrypoint - (targetpoint + 5)) };
	if (!Modify(targetpoint, targetpoint + total_len, STRING(JmpTo))) {
		return false;
	}

	// 写入目标指令
	Memory::WriteArray<BYTE>(CodePlacingAddress(), code, code_len);
	CodePlacingAddress() += code_len;

	// 写入被替换的指令
	Memory::WriteArray<BYTE>(CodePlacingAddress(), buf, total_len);
	CodePlacingAddress() += total_len;

	// 写入返回指令
	BYTE JmpBack[] = { JMPFAR(targetpoint + total_len - (CodePlacingAddress() + 5)) };
	Memory::WriteArray<BYTE>(CodePlacingAddress(), STRING(JmpBack));
	CodePlacingAddress() += STRING_LEN(JmpBack);

	// 如果要求原来的代码
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
