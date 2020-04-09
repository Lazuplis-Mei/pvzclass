#include "..\PVZ.h"

PVZ::CardSlot::CardSlot(int address)
{
	BaseAddress = Memory::ReadMemory<int>(address + 0x144);
}

PVZ::CardSlot::SeedCard* PVZ::CardSlot::GetCard(int index)
{
	if (index >= 0 && index < 10)
		return new SeedCard(BaseAddress + 0x24 + index * 0x50);
	else
		return NULL;
}
