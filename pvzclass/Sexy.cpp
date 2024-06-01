#include "Sexy.h"

BYTE __asm__MakeButton[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	INVOKE(0x448620),
	ADD_ESP(0x0C),
	MOV_PTR_ADDR_EAX(0),
	RET
};

int Sexy::MakeButton(const char* label, ButtonListener* listener, int theId, int& address)
{
	int len = strlen(label) + 1;
	int page = len / 0x400 + 1;
	address = PVZ::Memory::AllocMemory(page * 2 + 1);
	PVZ::Memory::WriteArray<const char>(address, label, len);
	Draw::ToString(address, address + 0x400);
	SETARG(__asm__MakeButton, 1) = address + 0x400;
	PVZ::Memory::WriteMemory<DWORD>(address + 0x800, address + 0x810);
	PVZ::Memory::WriteMemory<ButtonListener>(address + 0x810, *listener);
	SETARG(__asm__MakeButton, 6) = address + 0x800;
	SETARG(__asm__MakeButton, 11) = theId;
	SETARG(__asm__MakeButton, 32) = PVZ::Memory::Variable;
	return PVZ::Memory::Execute(STRING(__asm__MakeButton));
}

BYTE __asm__FreeButton[]
{
	PUSH(1),
	MOV_ECX(0),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0),
	CALL_EUX(2),
	RET
};

void Sexy::FreeButton(DWORD buttonAddress, DWORD address)
{
	SETARG(__asm__FreeButton, 3) = buttonAddress;
	PVZ::Memory::Execute(STRING(__asm__FreeButton));
	PVZ::Memory::FreeMemory(address);
}

BYTE __asm__ResizeButton[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	MOV_ECX(0),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0xA0),
	CALL_EUX(2),
	RET
};

void Sexy::ResizeButton(DWORD buttonAddress, int x, int y, int width, int height)
{
	SETARG(__asm__ResizeButton, 1) = height;
	SETARG(__asm__ResizeButton, 6) = width;
	SETARG(__asm__ResizeButton, 11) = y;
	SETARG(__asm__ResizeButton, 16) = x;
	SETARG(__asm__ResizeButton, 21) = buttonAddress;
	PVZ::Memory::Execute(STRING(__asm__ResizeButton));
}

BYTE __asm__AddToManager[]
{
	PUSHDWORD(0),
	MOV_ECX_PTR_ADDR(0x6A9EC0),
	MOV_EUX_PTR_EVX_ADD(1, 1, 0x320),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0x0C),
	CALL_EUX(2),
	RET
};

void Sexy::AddToManager(DWORD address)
{
	SETARG(__asm__AddToManager, 1) = address;
	PVZ::Memory::Execute(STRING(__asm__AddToManager));
}

BYTE __asm__RemoveFromManager[]
{
	PUSHDWORD(0),
	MOV_ECX_PTR_ADDR(0x6A9EC0),
	MOV_EUX_PTR_EVX_ADD(1, 1, 0x320),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0x10),
	CALL_EUX(2),
	RET
};

void Sexy::RemoveFromManager(DWORD address)
{
	SETARG(__asm__RemoveFromManager, 1) = address;
	PVZ::Memory::Execute(STRING(__asm__RemoveFromManager));
}
