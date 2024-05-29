#include "Draw.h"
#include <iostream>

BYTE __asm__ToString[]
{
	PUSHDWORD(0),
	MOV_ECX(0),
	INVOKE(0x404450),
	RET
};

void Draw::ToString(DWORD fromAddress, DWORD toAddress)
{
	SETARG(__asm__ToString, 1) = fromAddress;
	SETARG(__asm__ToString, 6) = toAddress;
	PVZ::Memory::Execute(STRING(__asm__ToString));
}

BYTE __asm__StringWidth[]
{
	PUSHDWORD(0),
	MOV_ECX(0),
	INVOKE(0x58DF70),
	RET
};

void Draw::StringWidth(DWORD stringAddress, DWORD imageFontAddress)
{
	SETARG(__asm__StringWidth, 1) = stringAddress;
	SETARG(__asm__StringWidth, 6) = imageFontAddress;
	PVZ::Memory::Execute(STRING(__asm__StringWidth));
}

BYTE __asm__SetColor[]
{
	PUSHDWORD(0),
	MOV_EDX(0),
	MOV_ECX(0),
	MOV_EAX(0),
	INVOKE(0x5643D0),
	MOV_ECX(0),
	INVOKE(0x586CC0),
	RET
};

void Draw::SetColor(DWORD r, DWORD g, DWORD b, DWORD colorAddress, DWORD graphics)
{
	SETARG(__asm__SetColor, 1) = r;
	SETARG(__asm__SetColor, 6) = g;
	SETARG(__asm__SetColor, 11) = b;
	SETARG(__asm__SetColor, 16) = colorAddress;
	SETARG(__asm__SetColor, 34) = graphics;
	PVZ::Memory::Execute(STRING(__asm__SetColor));
}

BYTE __asm__DrawString[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	MOV_EAX(0),
	INVOKE(0x587120),
	RET
};

void Draw::DrawString(DWORD x, DWORD y, DWORD stringAddress, DWORD graphics)
{
	SETARG(__asm__DrawString, 1) = y;
	SETARG(__asm__DrawString, 6) = x;
	SETARG(__asm__DrawString, 11) = stringAddress;
	SETARG(__asm__DrawString, 16) = graphics;
	PVZ::Memory::Execute(STRING(__asm__DrawString));
}
