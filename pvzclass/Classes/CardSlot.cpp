#include "..\PVZ.h"

PVZ::CardSlot::CardSlot(int address)
{
	BaseAddress = Memory::ReadMemory<int>(address + 0x144);
}

int PVZ::CardSlot::GetBaseAddress()
{
	return BaseAddress;
}

void PVZ::CardSlot::SetCardsCount(int num)
{
	Memory::WriteMemory<byte>(0x0041BEE0, 0xC3);
	SETARG(__asm__CardSlot__set_CardsCount, 1) = num;
	SETARG(__asm__CardSlot__set_CardsCount, 6) = PVZ::Memory::ReadMemory<int>(PVZBASEADDRESS + 0x144);
	Memory::Execute(STRING(__asm__CardSlot__set_CardsCount));
	Memory::WriteMemory<byte>(0x0041BEE0, 0x56);
}

SPT<PVZ::CardSlot::SeedCard> PVZ::CardSlot::GetCard(int index)
{
	if (index >= 0 && index < 10)
		return MKS<SeedCard>(BaseAddress + 0x28 + index * 0x50);
	else
		return NULL;
}
