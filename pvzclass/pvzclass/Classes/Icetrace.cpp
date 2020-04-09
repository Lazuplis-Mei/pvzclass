#include "../PVZ.h"

PVZ::Icetrace::Icetrace(int baseaddress)
{
	BaseAddress = baseaddress + 0x60C;
}

int PVZ::Icetrace::GetX(int route)
{
	if (route >= 0 && route < 6)
		return Memory::ReadMemory<int>(BaseAddress + route * 4);
	return -1;
}

void PVZ::Icetrace::SetX(int route, int x)
{
	if (route >= 0 && route < 6)
		Memory::WriteMemory<int>(BaseAddress + route * 4, x);
}

int PVZ::Icetrace::GetDisappearCountdown(int route)
{
	if (route >= 0 && route < 6)
		return Memory::ReadMemory<int>(BaseAddress + 0x18 + route * 4);
	return -1;
}

void PVZ::Icetrace::SetDisappearCountdown(int route, int cs)
{
	if (route >= 0 && route < 6)
		Memory::WriteMemory<int>(BaseAddress + 0x18 + route * 4, cs);
}

