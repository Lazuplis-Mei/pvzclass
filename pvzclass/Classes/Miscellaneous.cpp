#include "..\PVZ.h"

PVZ::Miscellaneous::Miscellaneous(int address)
{
	BaseAddress = Memory::ReadMemory<int>(address + 0x160);
}

int PVZ::Miscellaneous::GetBaseAddress()
{
	return BaseAddress;
}

namespace PVZ
{
	bool Miscellaneous::SetMemSize(int NewSize)
	{
		if(NewSize < Miscellaneous::MemSize)
			return(false);
		Memory::WriteMemory<int>(0x00408232, NewSize);
		Memory::WriteMemory<int>(0x00481C39, NewSize);

		byte __asm__inject[]
		{
			MOV_PTR_EUX_ADD_V_EVX(REG_EDI, REG_EBX, 0x50),
			0x8D, 0x87, INUMBER(0x0AC),
			PUSHDWORD(NewSize - 0x0AC),
			PUSH_EBX,
			PUSH_EAX,
			CALL(0x00206E0E),
			ADD_ESP(0x0C),
			NOP,
			NOP,
			NOP
		};
		Memory::WriteArray(0x0041F1FD, STRING(__asm__inject));
		return(true);
	}
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
