#include "..\PVZ.h"

PVZ::CardSlot::SeedCard::SeedCard(int address)
{
	BaseAddress = address;
}

int PVZ::CardSlot::SeedCard::GetBaseAddress()
{
	return BaseAddress;
}

void PVZ::CardSlot::SeedCard::GetCollision(CollisionBox* collbox)
{
	collbox->X = NULL;
	collbox->Y = NULL;
	collbox->Width = Memory::ReadMemory<int>(BaseAddress + 0x10);
	collbox->Height = Memory::ReadMemory<int>(BaseAddress + 0x14);
}

void PVZ::CardSlot::SeedCard::SetCollision(CollisionBox* collbox)
{
	Memory::WriteMemory<int>(BaseAddress + 0x10, collbox->Width);
	Memory::WriteMemory<int>(BaseAddress + 0x14, collbox->Height);
}

void PVZ::CardSlot::SeedCard::EnterCoolDown(int duration)
{
	if (duration == -1)
	{
		PlantType::PlantType type = (PlantType::PlantType)ContentCard;
		if (type == PlantType::Imitater) type = (PlantType::PlantType)ContentCardImitative;
		duration = Memory::ReadMemory<int>(0x69F2C4 + 0x24 * type);
	}
	Enable = false;
	CoolDownInterval = duration;
	CoolDown = 0;
	Active = true;
}
