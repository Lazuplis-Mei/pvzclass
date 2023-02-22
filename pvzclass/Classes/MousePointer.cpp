#include "../PVZ.h"

PVZ::MousePointer::MousePointer(int address) : GameObject()
{
	BaseAddress = Memory::ReadMemory<int>(address + 0x138);
}

SPT<PVZ::Animation> PVZ::MousePointer::GetAnimation()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x48);
	return (((ID & 0xFFFF0000) == 0) ? nullptr : MKS<Animation>(ID & 0x00FFFF));
}
