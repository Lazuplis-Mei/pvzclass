#include "..\PVZ.h"

PVZ::Caption::Caption(int address)
{
	BaseAddress = Memory::ReadMemory<int>(address + 0x140);
}


void PVZ::Caption::GetText(char str[])
{
	Memory::ReadArray<char>(BaseAddress + 4, str, 0x80);
}

void PVZ::Caption::SetText(const char str[])
{
	Memory::WriteArray<const char>(BaseAddress + 4, str, 0x80);
}
