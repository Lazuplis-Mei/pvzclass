#include "Draw.h"
#include <iostream>

BYTE Draw::color[16];

BYTE __asm__ToString[]
{
	PUSHDWORD(0),
	MOV_ECX(0),
	INVOKE(0x404450),
	RET
};

Draw::PString Draw::ToString(const char* str)
{
	int len = strlen(str);
	DWORD fromAddress = PVZ::Memory::AllocMemory(0, len + 1);
	PVZ::Memory::WriteArray<const char>(fromAddress, str, len + 1);
	PString toAddress = PVZ::Memory::AllocMemory(0, 0x1C);
	SETARG(__asm__ToString, 1) = fromAddress;
	SETARG(__asm__ToString, 6) = toAddress;
	PVZ::Memory::Execute(STRING(__asm__ToString));
	PVZ::Memory::FreeMemory(fromAddress);
	return toAddress;
}

char* Draw::ToChar(PString str)
{
	int size = PVZ::Memory::ReadMemory<int>(str + 0x18);
	DWORD address = 0;
	if (size < 16) address = str + 4;
	else address = PVZ::Memory::ReadMemory<DWORD>(str + 4);
	int len = PVZ::Memory::ReadMemory<int>(str + 0x14);
	char* result = new char[len + 1];
	PVZ::Memory::ReadArray<char>(address, result, len);
	result[len] = 0;
	return result;
}

BYTE __asm__StringWidth[]
{
	PUSHDWORD(0),
	MOV_ECX(0),
	INVOKE(0x58DF70),
	RET
};

void Draw::StringWidth(PString str, DWORD imageFontAddress)
{
	SETARG(__asm__StringWidth, 1) = str;
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

void Draw::SetColor(DWORD r, DWORD g, DWORD b, DWORD graphics)
{
	SETARG(__asm__SetColor, 1) = r;
	SETARG(__asm__SetColor, 6) = g;
	SETARG(__asm__SetColor, 11) = b;
	SETARG(__asm__SetColor, 16) = (int)color;
	SETARG(__asm__SetColor, 34) = graphics;
	PVZ::Memory::Execute(STRING(__asm__SetColor));
}

BYTE __asm__GetSharedImage[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	MOV_ECX_PTR_ADDR(0x6A9EC0),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0x10C),
	CALL_EUX(2),
	RET
};

Draw::PSharedImageRef Draw::GetSharedImage(DWORD isnewAddress, PString variant, PString filename)
{
	SETARG(__asm__GetSharedImage, 1) = isnewAddress;
	SETARG(__asm__GetSharedImage, 6) = variant;
	SETARG(__asm__GetSharedImage, 11) = filename;
	PSharedImageRef imageRef = PVZ::Memory::AllocMemory(0, 4);
	SETARG(__asm__GetSharedImage, 16) = imageRef;
	PVZ::Memory::Execute(STRING(__asm__GetSharedImage));
	return imageRef;
}

BYTE __asm__SharedImageRefToImage[]
{
	MOV_ECX(0),
	INVOKE(0x59A980),
	MOV_PTR_ADDR_EAX(0),
	RET
};

Draw::PImage Draw::SharedImageRefToImage(PSharedImageRef imageRef)
{
	SETARG(__asm__SharedImageRefToImage, 1) = imageRef;
	SETARG(__asm__SharedImageRefToImage, 19) = PVZ::Memory::Variable;
	return PVZ::Memory::Execute(STRING(__asm__SharedImageRefToImage));
}

BYTE __asm__FreeImage[]
{
	MOV_ESI(0),
	INVOKE(0x59A8C0),
	RET
};

void Draw::FreeImage(PSharedImageRef imageRef)
{
	SETARG(__asm__FreeImage, 1) = imageRef;
	PVZ::Memory::Execute(STRING(__asm__FreeImage));
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

void Draw::DrawString(DWORD x, DWORD y, PString str, DWORD graphics)
{
	SETARG(__asm__DrawString, 1) = y;
	SETARG(__asm__DrawString, 6) = x;
	SETARG(__asm__DrawString, 11) = str;
	SETARG(__asm__DrawString, 16) = graphics;
	PVZ::Memory::Execute(STRING(__asm__DrawString));
}

BYTE __asm__DrawImage[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	MOV_EBX(0),
	MOV_EAX(0),
	INVOKE(0x587150),
	RET
};

void Draw::DrawImage(DWORD x, DWORD y, PImage image, DWORD graphics)
{
	SETARG(__asm__DrawImage, 1) = y;
	SETARG(__asm__DrawImage, 6) = x;
	SETARG(__asm__DrawImage, 11) = image;
	SETARG(__asm__DrawImage, 16) = graphics;
	PVZ::Memory::Execute(STRING(__asm__DrawImage));
}

BYTE __asm__DrawLine[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	INVOKE(0x587080),
	RET
};

void Draw::DrawLine(int startx, int starty, int endx, int endy, DWORD graphics)
{
	SETARG(__asm__DrawLine, 1) = endy;
	SETARG(__asm__DrawLine, 6) = endx;
	SETARG(__asm__DrawLine, 11) = startx;
	SETARG(__asm__DrawLine, 16) = graphics;
	PVZ::Memory::WriteMemory<double>(PVZ::Memory::Variable, starty);
	PVZ::Memory::WriteMemory<DWORD>(0x5870A4, PVZ::Memory::Variable);
	PVZ::Memory::Execute(STRING(__asm__DrawLine));
	PVZ::Memory::WriteMemory<DWORD>(0x5870A4, 0x65B8F8);
}

BYTE __asm__DrawRect[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	MOV_EAX(0),
	INVOKE(0x586DE0),
	RET
};

void Draw::DrawRect(int x, int y, int width, int height, DWORD graphics)
{
	SETARG(__asm__DrawRect, 1) = height;
	SETARG(__asm__DrawRect, 6) = width;
	SETARG(__asm__DrawRect, 11) = y;
	SETARG(__asm__DrawRect, 16) = x;
	SETARG(__asm__DrawRect, 21) = graphics;
	PVZ::Memory::Execute(STRING(__asm__DrawRect));	
}

BYTE __asm__FillRect[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	MOV_EAX(0),
	INVOKE(0x586D50),
	RET
};

void Draw::FillRect(int x, int y, int width, int height, DWORD graphics)
{
	SETARG(__asm__FillRect, 1) = height;
	SETARG(__asm__FillRect, 6) = width;
	SETARG(__asm__FillRect, 11) = y;
	SETARG(__asm__FillRect, 16) = x;
	SETARG(__asm__FillRect, 21) = graphics;
	PVZ::Memory::Execute(STRING(__asm__FillRect));
}

BYTE __asm__DrawTextBox[]
{
	PUSHDWORD(0),
	MOV_ECX(0),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0x04),
	CALL_EUX(2),
	MOV_EBX_EAX,
	MOV_EUX_PTR_ADDR(0, 0x6A7890),
	PUSHDWORD(0),
	INVOKE(0x587900),
	RET
};

void Draw::DrawTextBox(DWORD edit, DWORD graphics)
{
	int rect = PVZ::Memory::AllocMemory(0, 16);
	SETARG(__asm__DrawTextBox, 1) = rect;
	SETARG(__asm__DrawTextBox, 6) = edit;
	SETARG(__asm__DrawTextBox, 29) = graphics;
	PVZ::Memory::Execute(STRING(__asm__DrawTextBox));
	PVZ::Memory::FreeMemory(rect);
}
