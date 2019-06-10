#include "PVZ.h"

PVZ::Lawnmover::Lawnmover(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(Memory::ReadMemory<int>(PVZ_BASE + 0x768) + 0x100) + indexoraddress * 0x48;
#if _DEBUG
	DebugType = Type;
#endif
}