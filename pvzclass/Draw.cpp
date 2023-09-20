#include "Draw.h"
#include <iostream>

DWORD Draw::pointerAddress;
DWORD Draw::imageFontAddress;
DWORD Draw::colorAddress;
DWORD Draw::tempAddress;
DWORD Draw::codeAddress;
DWORD Draw::dataAddress;

void Draw::writeString(std::vector<String> strings)
{
	sort(strings.begin(), strings.end(), [](String a, String b)->bool
		{
			return a.size < b.size;
		});
	DWORD address = dataAddress;
	for (int i = 0; i < strings.size(); i++)
	{
		PVZ::Memory::WriteMemory<int>(address, strings[i].x);
		PVZ::Memory::WriteMemory<int>(address + 4, strings[i].y);
		PVZ::Memory::WriteMemory<int>(address + 8, strings[i].size);
		PVZ::Memory::WriteMemory<int>(address + 12, strings[i].red);
		PVZ::Memory::WriteMemory<int>(address + 16, strings[i].green);
		PVZ::Memory::WriteMemory<int>(address + 20, strings[i].blue);
		PVZ::Memory::WriteArray<char>(address + 24, strings[i].s, strlen(strings[i].s) + 1);
		address += 128;
	}
	PVZ::Memory::WriteMemory<char>(address + 24, 0);
}

BYTE __asm__char2string[]
{
	PUSHDWORD(0),
	MOV_ECX(0),
	INVOKE(0x404450),
	RET
};

BYTE __asm__createColor[]
{
	PUSHDWORD(0xFF),
	MOV_EDX(0xFF),
	MOV_ECX(0xFF),
	MOV_EAX(0),
	INVOKE(0x5643D0),
	RET
};

BYTE __asm__drawString[]
{
	PUSHAD,
	MOV_PTR_ADDR(0, 0),
	MOV_ECX_PTR_ADDR(0),
	MOV_EAX(0x19FA98),
	INVOKE(0x586CB0), // 35

	PUSHDWORD(0),
	MOV_ECX_PTR_ADDR(0),
	INVOKE(0x58DF70), // 59

	MOV_EAX(0),
	MOV_ECX(0x19FA98),
	INVOKE(0x586CC0), // 82

	MOV_EBX_PTR_ADDR(0),
	0x83, 0xC3, 0x18, // ADD ebx,18
	0x83, 0x3B, 0x00, // CMP [ebx],0
	0x74, 194-96, // JE 96

	PUSH_EBX,
	MOV_ECX(0),
	INVOKE(0x404450), // 115

	MOV_EBX_PTR_ADDR(0),
	0xFF, 0x73, 0x14,
	0x8B, 0x53, 0x10,
	0x8B, 0x4B, 0x0C,
	MOV_EAX(0),
	INVOKE(0x5643D0), // 148
	
	MOV_EBX_PTR_ADDR(0),
	0xFF, 0x73, 0x04,
	0xFF, 0x33,
	PUSHDWORD(0),
	MOV_EAX(0x19FA98),
	INVOKE(0x587120), // 182

	0x81, 0x05, INUMBER(0), INUMBER(128),
	0xEB, 82-194, // JMP 194

	POPAD,
	INVOKE(0x41AA40),
	PUSHDWORD(0x4172FB),
	RET
};

BYTE __asm__4172F6[]
{
	0xE9, INUMBER(0)
};

void Draw::init(int pages)
{
	DWORD address = PVZ::Memory::AllocMemory();
	pointerAddress = address;
	imageFontAddress = address + 4;
	colorAddress = address + 8;
	tempAddress = address + 24;
	codeAddress = address + 152;
	dataAddress = PVZ::Memory::AllocMemory(pages);

	PVZ::Memory::WriteMemory<DWORD>(imageFontAddress,
		PVZ::Memory::ReadMemory<DWORD>(0x6A72EC));

	SETARG(__asm__char2string, 1) = dataAddress + 24;
	SETARG(__asm__char2string, 6) = tempAddress;
	PVZ::Memory::Execute(STRING(__asm__char2string));

	SETARG(__asm__createColor, 16) = colorAddress;
	PVZ::Memory::Execute(STRING(__asm__createColor));

	SETARG(__asm__drawString, 3) = pointerAddress;
	SETARG(__asm__drawString, 7) = dataAddress;
	SETARG(__asm__drawString, 13) = imageFontAddress;
	SETARG(__asm__drawString, 36) = tempAddress;
	SETARG(__asm__drawString, 42) = imageFontAddress;
	SETARG(__asm__drawString, 60) = colorAddress;
	SETARG(__asm__drawString, 84) = pointerAddress;
	SETARG(__asm__drawString, 98) = tempAddress;
	SETARG(__asm__drawString, 117) = pointerAddress;
	SETARG(__asm__drawString, 131) = colorAddress;
	SETARG(__asm__drawString, 150) = pointerAddress;
	SETARG(__asm__drawString, 160) = tempAddress;
	SETARG(__asm__drawString, 184) = pointerAddress;

	PVZ::Memory::WriteArray<BYTE>(codeAddress, STRING(__asm__drawString));

	SETARG(__asm__4172F6, 1) = codeAddress - 0x4172F6 - 5;
	PVZ::Memory::WriteArray<BYTE>(0x4172F6, STRING(__asm__4172F6));
}
