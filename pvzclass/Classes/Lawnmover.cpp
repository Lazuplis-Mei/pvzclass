#include "../PVZ.h"

PVZ::Lawnmover::Lawnmover(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0x100) + indexoraddress * 0x48;
}

int PVZ::Lawnmover::GetBaseAddress()
{
	return BaseAddress;
}

SPT<PVZ::Animation> PVZ::Lawnmover::GetAnimation()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x1C);
	return ((ID_RANK(ID) == 0) ? nullptr : MKS<Animation>(ID_INDEX(ID)));
}

void PVZ::Lawnmover::Die()
{
	SETARG(__asm__Lawnmover_Die, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Lawnmover_Die));
	return;
}