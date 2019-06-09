#include "PVZ.h"

PVZ::Projectile::Projectile(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(Memory::ReadMemory<int>(PVZ_BASE + 0x768) + 0xC8) + indexoraddress * 0x94;
#if _DEBUG
	DebugType = Type;
#endif
}

void PVZ::Projectile::OnFire()
{
	/*************************/
}
