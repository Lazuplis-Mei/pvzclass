#include "../PVZ.h"

PVZ::Lawnmover::Lawnmover(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0x100) + indexoraddress * 0x48;
#if _DEBUG
	DebugType = Type;
#endif
}

SPT<PVZ::Animation> PVZ::Lawnmover::GetAnimation()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x1C);
	return ((ID_RANK(ID) == 0) ? nullptr : MKS<Animation>(ID_INDEX(ID)));
}
