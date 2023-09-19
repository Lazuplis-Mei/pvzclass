#include "Draw.h"

void Draw::writeString(DWORD address, std::vector<String> strings)
{
	sort(strings.begin(), strings.end(), [](String a, String b)->bool
		{
			return a.size < b.size;
		});
	for (int i = 0; i < strings.size(); i++)
	{
		PVZ::Memory::WriteMemory<int>(address, strings[i].x);
		PVZ::Memory::WriteMemory<int>(address + 4, strings[i].y);
		PVZ::Memory::WriteMemory<int>(address + 8, strings[i].size);
		PVZ::Memory::WriteMemory<int>(address + 12, strings[i].red);
		PVZ::Memory::WriteMemory<int>(address + 16, strings[i].green);
		PVZ::Memory::WriteMemory<int>(address + 20, strings[i].blue);
		PVZ::Memory::WriteArray<char>(address + 24, strings[i].s, strlen(strings[i].s) + 1);
		address += 128;
	}
	PVZ::Memory::WriteMemory<char>(address + 24, 0);
}
