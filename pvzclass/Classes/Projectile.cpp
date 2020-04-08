#include "../PVZ.h"

PVZ::Projectile::Projectile(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0xC8) + indexoraddress * 0x94;
#if _DEBUG
	DebugType = Type;
#endif
}

void PVZ::Projectile::OnFire()
{
	SETARG(__asm__OnFire, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__OnFire));
}
