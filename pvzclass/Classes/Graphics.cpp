#include "../PVZ.h"
#include <cstdio>

PVZ::Graphics::Graphics(DWORD address)
{
	BaseAddress = address;
}

byte __asm__set__color[]
{
	MOV_EAX(0),
	MOV_ECX(0),
	MOV_EDX(0),
	PUSHDWORD(0),
	INVOKE(0x5643D0),
	MOV_ECX(0),
	INVOKE(0x586CC0),
	RET
};

// 将Graphic现在的Color修改为指定颜色
void PVZ::Graphics::SetColor(int red, int green, int blue)
{
	DWORD colorAddress = PVZ::Memory::Variable + 100;
	SETARG(__asm__set__color, 1) = colorAddress;
	SETARG(__asm__set__color, 6) = red;
	SETARG(__asm__set__color, 11) = green;
	SETARG(__asm__set__color, 16) = blue;
	SETARG(__asm__set__color, 34) = BaseAddress;
	Memory::Execute(STRING(__asm__set__color));
}

byte __asm__DrawString[]
{
	PUSHDWORD(0),
	MOV_ECX(0),
	INVOKE(0x404450), // 5+5+13=23
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSH_EAX, // 23+5+5+1=34
	MOV_EAX(0),
	INVOKE(0x587120),
	RET
};

// 在屏幕上输出字符串，每次屏幕刷新都要调用
void PVZ::Graphics::DrawString(int x, int y, const char* str, int length)
{
	DWORD charAddress = PVZ::Memory::Variable + 100;
	DWORD stringAddress = PVZ::Memory::Variable + 200;
	Memory::WriteArray<const char>(charAddress, str, length);
	SETARG(__asm__DrawString, 1) = charAddress;
	SETARG(__asm__DrawString, 6) = stringAddress;
	SETARG(__asm__DrawString, 24) = y;
	SETARG(__asm__DrawString, 29) = x;
	SETARG(__asm__DrawString, 35) = BaseAddress;
	Memory::Execute(STRING(__asm__DrawString));
}