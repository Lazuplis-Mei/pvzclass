#include "../PVZ.h"

int PVZ::TrackInstance::GetBaseAddress()
{
	return BaseAddress;
}

PVZ::TrackInstance::TrackInstance(int idoraddress)
{
	if (idoraddress >= 1024)
		this->BaseAddress = idoraddress;
	else
		this->BaseAddress = Memory::ReadPointer(0x6A9EC0, 0x820, 0xC, 0) + idoraddress * 0x30C;	
}

SPT<PVZ::Attachment> PVZ::TrackInstance::GetAttachment()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x40);
	return (((ID & 0xFFFF0000) == 0) ? nullptr : MKS<PVZ::Attachment>(ID & 0x00FFFF));
}
