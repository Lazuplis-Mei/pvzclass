#include "../PVZ.h"

int PVZ::Griditem::GetBaseAddress()
{
	return BaseAddress;
}

PVZ::Griditem::Griditem(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0x11C) + indexoraddress * 0xEC;
}

SPT<PVZ::Board> PVZ::Griditem::GetBoard()
{
	return(MKS<PVZ::Board>(Memory::ReadMemory<int>(BaseAddress + 4)));
}

void PVZ::Griditem::Remove()
{
	SETARG(__asm__Griditem__Remove, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Griditem__Remove));
}

void PVZ::Vase::Open()
{
	SETARG(__asm__Vase_Open, 1) = BaseAddress;
	SETARG(__asm__Vase_Open, 6) = Memory::ReadPointer(BaseAddress + 4, 0x160);
	Memory::Execute(STRING(__asm__Vase_Open));
}

byte __asm__PortalClose[]
{
	MOV_ESI(0),
	INVOKE(0x44E360),
	RET
};

void PVZ::Portal::Close()
{
	SETARG(__asm__PortalClose, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__PortalClose));
}