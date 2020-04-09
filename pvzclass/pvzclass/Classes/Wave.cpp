#include "../PVZ.h"


PVZ::Wave::Wave(int baseaddress)
{
	BaseAddress = baseaddress;
}

int PVZ::Wave::__get_Count()
{
	int i = 0;
	for (; i < 50; i++)
	{
		ZombieType::ZombieType ztype = Memory::ReadMemory<ZombieType::ZombieType>(BaseAddress + i * 4);
		if (ztype == ZombieType::None)break;
	}
	return i;
};

void PVZ::Wave::GetAll(ZombieType::ZombieType* ztypes)
{
	int count = Count;
	for (int i = 0; i < count; i++)
	{
		ZombieType::ZombieType ztype = Memory::ReadMemory<ZombieType::ZombieType>(BaseAddress + i * 4);
		ztypes[i] = ztype;
	}
}

void PVZ::Wave::SetAll(ZombieType::ZombieType* ztypes, size_t length)
{
	int len = min(length, 50);
	for (int i = 0; i < len; i++)
		Memory::WriteMemory<ZombieType::ZombieType>(BaseAddress + i * 4, ztypes[i]);
	if (len < 50)Memory::WriteMemory<ZombieType::ZombieType>(BaseAddress + len * 4, ZombieType::None);
}

ZombieType::ZombieType PVZ::Wave::Get(int index)
{
	if (index >= 0 && index < Count)
		return Memory::ReadMemory<ZombieType::ZombieType>(BaseAddress + index * 4);
	return ZombieType::None;
}

void PVZ::Wave::Set(int index, ZombieType::ZombieType ztype)
{
	if (index >= 0 && index < Count)
		Memory::WriteMemory<ZombieType::ZombieType>(BaseAddress + index * 4, ztype);
}

void PVZ::Wave::Del(int index)
{
	int count = Count;
	if (index >= 0 && index < count)
	{
		for (int i = index; i < count; i++)
		{
			Set(i, Get(i + 1));
		}
		Set(count - 1, ZombieType::None);
	}
}

void PVZ::Wave::Add(ZombieType::ZombieType ztype)
{
	int count = Count;
	if (count < 50)
	{
		Memory::WriteMemory<ZombieType::ZombieType>(BaseAddress + count * 4, ztype);
		if (count < 49)Memory::WriteMemory<ZombieType::ZombieType>(BaseAddress + (count + 1) * 4, ZombieType::None);
	}
}
