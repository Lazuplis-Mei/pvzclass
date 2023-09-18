#include "../PVZ.h"
#include <cstdio>

PVZ::Graphics::Graphics(DWORD address)
{
	BaseAddress = address;
}

byte __asm__set__color[]
{
	MOV_EAX_PTR(0),
	ADD_EAX_DWORD(30),
	MOV_ECX(0),
	MOV_EDX(0),
	PUSHDWORD(0),
	INVOKE(0x5643D0),
	MOV_ECX_PTR_ADDR(0),
	INVOKE(0x586CC0)
};

// 将Graphic现在的Color修改为指定颜色
void PVZ::Graphics::SetColor(int red, int green, int blue)
{
	SETARG(__asm__set__color, 1) = BaseAddress;
	SETARG(__asm__set__color, 11) = red;
	SETARG(__asm__set__color, 16) = green;
	SETARG(__asm__set__color, 21) = blue;
	SETARG(__asm__set__color, 40) = BaseAddress;
	Memory::Execute(STRING(__asm__set__color));
}

byte __asm__DrawString[]
{
	PUSHDWORD(0),
	LEA_ECX_ESP_ADD(0x30),
	INVOKE(0x404450),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSH_EAX,
	MOV_EAX_PTR(0),
	INVOKE(0x587120)
};

// 在屏幕上输出字符串，每次屏幕刷新都要调用
void PVZ::Graphics::DrawString(int x, int y, const char* str, int length)
{
	Memory::WriteArray<const char>(PVZ::Memory::Variable + 100, str, length);
	SETARG(__asm__DrawString, 1) = Memory::Variable + 100;
	SETARG(__asm__DrawString, 23) = y;
	SETARG(__asm__DrawString, 28) = x;
	SETARG(__asm__DrawString, 34) = BaseAddress;
	for (int i = 0; i < 51; i++)
		printf("%X ", __asm__DrawString[i]);
	Memory::Execute(STRING(__asm__DrawString));
}