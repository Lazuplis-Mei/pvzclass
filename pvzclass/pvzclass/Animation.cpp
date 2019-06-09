#include "PVZ.h"

PVZ::Animation::Animation(int idoraddress)
{
	if (idoraddress > 1024)
		BaseAddress = idoraddress;
	else
		BaseAddress = Memory::ReadPointer(0x6A9EC0, 0x820, 8, 0) + idoraddress * 0xA0;
}