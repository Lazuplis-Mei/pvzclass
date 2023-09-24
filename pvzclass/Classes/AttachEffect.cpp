#include "../PVZ.h"

PVZ::AttachEffect::AttachEffect(int address)
{
	BaseAddress = address;
}

int PVZ::AttachEffect::GetBaseAddress()
{
	return BaseAddress;
}