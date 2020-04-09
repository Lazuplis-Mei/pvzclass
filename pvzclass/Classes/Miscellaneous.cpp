#include "..\PVZ.h"

PVZ::Miscellaneous::Miscellaneous(int address)
{
	BaseAddress = Memory::ReadMemory<int>(address + 0x160);
}

BOOLEAN PVZ::Miscellaneous::HaveCrater(int row, int column)
{
	if (row >= 0 && row < 6 && column >= 0 && column < 9)
		return Memory::ReadMemory<byte>(BaseAddress + 0x14 + 6 * column + row);
	return false;
}

void PVZ::Miscellaneous::SetCrater(int row, int column, BOOLEAN b)
{
	if (row >= 0 && row < 6 && column >= 0 && column < 9)
		Memory::WriteMemory<byte>(BaseAddress + 0x14 + 6 * column + row, b);
}
