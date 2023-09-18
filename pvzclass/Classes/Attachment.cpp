#include "../PVZ.h"

int PVZ::Attachment::GetBaseAddress()
{
	return BaseAddress;
}

PVZ::Attachment::Attachment(int idoraddress)
{
	if (idoraddress > 1024)
		BaseAddress = idoraddress;
	else
		BaseAddress = Memory::ReadPointer(0x6A9EC0, 0x820, 0xC, 0) + idoraddress * 0x30C;
}

SPT<PVZ::Animation> PVZ::Attachment::GetAnimation()
{
	int ID = Memory::ReadMemory<int>(BaseAddress);
	return (((ID & 0xFFFF0000) == 0) ? nullptr : MKS<Animation>(ID & 0x00FFFF));
}
