#include "../PVZ.h"

PVZ::Animation::Animation(int idoraddress)
{
	if (idoraddress > 1024)
		BaseAddress = idoraddress;
	else
		BaseAddress = Memory::ReadPointer(0x6A9EC0, 0x820, 8, 0) + idoraddress * 0xA0;
}

void PVZ::Animation::UnLock(int animprop)
{
	if (LOGICALINCLUDE(animprop, AP_ZOMBIESPEED))
		Memory::WriteMemory<LONGLONG>(0x52EFF0, -8029759185035983678);
	if (LOGICALINCLUDE(animprop, AP_ZOMBIECOLOR))
		Memory::WriteMemory<int>(0x52D3EA, -1869598485);
	if (LOGICALINCLUDE(animprop, AP_ZOMBIESCALE))
		Memory::WriteMemory<byte>(0x52C57E, 0x39);
	if (LOGICALINCLUDE(animprop, AP_PLANTCOLOR))
		Memory::WriteMemory<byte>(0x4636B4, 0x6B);
	if (LOGICALINCLUDE(animprop, AP_PLANTSCALE))
		Memory::WriteMemory<int>(0x463E1E, -1869607701);
}

void PVZ::Animation::Lock()
{
	Memory::WriteMemory<LONGLONG>(0x52EFF0, 1205015873675);
	Memory::WriteMemory<int>(0x52D3EA, 807683211);
	Memory::WriteMemory<byte>(0x52C57E, 0x14);
	Memory::WriteMemory<byte>(0x4636B4, 0x2B);
	Memory::WriteMemory<int>(0x463E1E, 405030105);
}

void PVZ::Animation::GetColor(Color* color)
{
	color->Alpha = Memory::ReadMemory<int>(BaseAddress + 0x48);
	color->Red = Memory::ReadMemory<int>(BaseAddress + 0x4C);
	color->Green = Memory::ReadMemory<int>(BaseAddress + 0x50);
	color->Blue = Memory::ReadMemory<int>(BaseAddress + 0x54);
}

void PVZ::Animation::SetColor(Color* color)
{
	Memory::WriteMemory<int>(BaseAddress + 0x48, color->Alpha);
	Memory::WriteMemory<int>(BaseAddress + 0x4C, color->Red);
	Memory::WriteMemory<int>(BaseAddress + 0x50, color->Green);
	Memory::WriteMemory<int>(BaseAddress + 0x54, color->Blue);
}
