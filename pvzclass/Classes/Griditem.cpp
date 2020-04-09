#include "../PVZ.h"

PVZ::Griditem::Griditem(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0x11C) + indexoraddress * 0xEC;
#if _DEBUG
	DebugType = Type;
#endif
}
