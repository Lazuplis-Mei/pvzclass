#pragma once
#include "../PVZ.h"
#include "../Mixin.h"
#include <iostream>

using std::cout;
using std::hex;
using std::endl;

class DLLEvent
{
public:
	void end();

protected:
	int rawlen, hookAddress;
	void start(BYTE* code, int len);
	void start2(int procAddress, RegisterType args[], int argcnt);
private:
	BYTE* rawCode;
	static int newAddress;
};

int DLLEvent::newAddress = 0;

void DLLEvent::start(BYTE* code, int newlen)
{
	if (newAddress == 0) newAddress = PVZ::Memory::AllocMemory();
	rawCode = new BYTE[rawlen];
	PVZ::Memory::ReadArray<BYTE>(hookAddress, rawCode, rawlen);
	BYTE jmpto[] = { JMPFAR(newAddress - (hookAddress + 5)) };
	PVZ::Memory::WriteArray<BYTE>(hookAddress, jmpto, 5);
	for (int i = 5; i < rawlen; i++) PVZ::Memory::WriteMemory<BYTE>(hookAddress + i, NOP);
	BYTE jmpback[] = { JMPFAR(hookAddress - (newAddress + newlen + 7)) };
	PVZ::Memory::WriteMemory<BYTE>(newAddress, PUSHAD);
	PVZ::Memory::WriteArray<BYTE>(newAddress + 1, code, newlen);
	PVZ::Memory::WriteMemory<BYTE>(newAddress + newlen + 1, POPAD);
	PVZ::Memory::WriteArray<BYTE>(newAddress + newlen + 2, rawCode, rawlen);
	PVZ::Memory::WriteArray<BYTE>(newAddress + newlen + rawlen + 2, jmpback, 5);
	newAddress += newlen + rawlen + 0x10;
}

inline BYTE* ResolveRegisterPushing(RegisterType arg, BYTE *code, int *regsz) {
	switch (arg) {
	case R_EAX:
		*code = PUSH_EAX;
		*regsz = 4;
		return code + 1;
	case R_ECX:
		*code = PUSH_ECX;
		*regsz = 4;
		return code + 1;
	case R_EDX:
		*code = PUSH_EDX;
		*regsz = 4;
		return code + 1;
	case R_EBX:
		*code = PUSH_EBX;
		*regsz = 4;
		return code + 1;
	case R_ESP:
		*code = PUSH_ESP;
		*regsz = 4;
		return code + 1;
	case R_EBP:
		*code = PUSH_EBP;
		*regsz = 4;
		return code + 1;
	case R_ESI:
		*code = PUSH_ESI;
		*regsz = 4;
		return code + 1;
	case R_EDI:
		*code = PUSH_EDI;
		*regsz = 4;
		return code + 1;
	default:
		// 加入错误处理
		*regsz = 0;
		return code;
	}
}

inline void DLLEvent::start2(int procAddress, RegisterType args[], int argcnt) {
	BYTE code[64];

	BYTE *cur = code;
	*cur = PUSHAD;
	cur++;

	int argsz = 0;
	// 传递参数
	for (int i = 0; i < argcnt; i++) {
		int regsz = 0;
		cur = ResolveRegisterPushing(args[i], cur, &regsz);
		argsz += regsz;
	}
	BYTE remain_code[] = { INVOKE(procAddress), ADD_ESP(argsz), POPAD };
	memcpy(cur, STRING(remain_code));
	cur += STRING_LEN(remain_code);

	size_t _rawlen = 0;

	PVZ::Mixin::Insert(hookAddress, code, cur - code, &rawCode, &_rawlen);
	rawlen = _rawlen;
}

void DLLEvent::end()
{
	PVZ::Memory::WriteArray<BYTE>(hookAddress, rawCode, rawlen);
	PVZ::Memory::FreeMemory(newAddress);
}