#include "../PVZ.h"

PVZ::MousePointer::MousePointer(int address)
{
	BaseAddress = Memory::ReadMemory<int>(address + 0x138);
}