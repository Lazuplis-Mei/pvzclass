#include "..\PVZ.h"

PVZ::CardSlot::SeedCard::SeedCard(int address)
{
	BaseAddress = address;
}

void PVZ::CardSlot::SeedCard::GetCollision(CollisionBox* collbox)
{
	collbox->X = NULL;
	collbox->Y = NULL;
	collbox->Width = Memory::ReadMemory<int>(BaseAddress + 0x14);
	collbox->Height = Memory::ReadMemory<int>(BaseAddress + 0x18);
}

void PVZ::CardSlot::SeedCard::SetCollision(CollisionBox* collbox)
{
	Memory::WriteMemory<int>(BaseAddress + 0x14, collbox->Width);
	Memory::WriteMemory<int>(BaseAddress + 0x18, collbox->Height);
}
