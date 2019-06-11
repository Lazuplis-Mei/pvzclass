#include "..\PVZ.h"

PVZ::SaveData::SaveData(int baseaddress)
{
	BaseAddress = baseaddress;
}

void PVZ::SaveData::GetPVZUserName(char str[])
{
	Memory::ReadArray<char>(BaseAddress + 4, str, 12);
}

BOOLEAN PVZ::SaveData::HavePurpleCard(CardType::CardType purplecard)
{
	if (purplecard >= CardType::GatlingPea && purplecard <= CardType::CobCannon)
		return Memory::ReadMemory<int>(BaseAddress + 0x1C0 + (purplecard - 40) * 4);
	return false;
}
