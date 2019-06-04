#include "PVZ.h"
#include "MainFuntions.h"

PVZ::PVZ(DWORD pid)
{
	Memory::processId = pid;
	Memory::hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	Memory::Variable = Memory::AllocMemory();
}

PVZ::~PVZ()
{
	CloseHandle(Memory::hProcess);
	Memory::FreeMemory(Memory::Variable);
}

#pragma region background methods

const char* PVZ::__get_Version()
{
	return "0.3.0.190604";
}

PVZVersion PVZ::__get_GameVersion()
{
	int ver = Memory::ReadMemory<int>(0x552013);
	switch (ver)
	{
	case 0xC35EDB74:
		return V1_0_0_1051;
	case 0x86831977:
		return V1_2_0_1065;
	case 0x3B000001:
		return V1_2_0_1073;
	case 0x878B0000:
		return 中文年度加强版;
	case 0xA48F:
		return 粘度汗化版;
	default:
		return UnknowOrNotPVZ;
	}
}

double PVZ::__get_MusicVolume()
{
	return Memory::ReadMemory<double>(PVZ_BASE + 0xD0);
}

void PVZ::__set_MusicVolume(double value)
{
	Memory::WriteMemory<double>(PVZ_BASE + 0xD0, value);
	SETARG(__asm__set_MusicVolume, 1) = PVZ_BASE;
	Memory::Execute(STRING(__asm__set_MusicVolume));
}

double PVZ::__get_SoundFXVolume()
{
	return Memory::ReadMemory<double>(PVZ_BASE + 0xD8);
}

void PVZ::__set_SoundFXVolume(double value)
{
	Memory::WriteMemory<double>(PVZ_BASE + 0xD8, value);
	SETARG(__asm__set_MusicVolume, 1) = PVZ_BASE;
	Memory::Execute(STRING(__asm__set_MusicVolume));
}

SceneType PVZ::__get_LevelScene()
{
	return Memory::ReadMemory<SceneType>(BaseAddress + 0x554C);
}

void PVZ::__set_LevelScene(SceneType value)
{
	Memory::WriteMemory<SceneType>(BaseAddress + 0x554C, value);
	SETARG(__asm_set_LevelScene, 1) = BaseAddress;
	Memory::Execute(STRING(__asm_set_LevelScene));
}

#pragma endregion

#pragma region Lawn Class

PVZ::Lawn::Lawn(int baseaddress)
{
	BaseAddress = baseaddress;
};

LawnType PVZ::Lawn::GetGridType(int row, int column)
{
	if (row >= 0 && row < 6 && column >= 0 && column < 9)
		return Memory::ReadMemory<LawnType>(BaseAddress + 0x168 + 4 * (6 * column + row));
	return LawnTypeNone;
};

void PVZ::Lawn::SetGridType(int column, int row, LawnType type)
{
	if (row >= 0 && row < 6 && column >= 0 && column < 9)
		Memory::WriteMemory<LawnType>(BaseAddress + 0x168 + 4 * (6 * column + row), type);
	
};

RouteType PVZ::Lawn::GetRouteType(int route)
{
	if (route >= 0 && route < 6)
		return Memory::ReadMemory<RouteType>(BaseAddress + 0x5D8 + 4 * route);
	return RouteTypeNone;
};

void PVZ::Lawn::SetRouteType(int route, RouteType type)
{
	if (route >= 0 && route < 6)
		Memory::WriteMemory<RouteType>(BaseAddress + 0x5D8 + 4 * route, type);
};

#pragma endregion

#pragma region Icetrace Class

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

#pragma endregion

#pragma region Wave Class

PVZ::Wave::Wave(int baseaddress)
{
	BaseAddress = baseaddress;
}

int PVZ::Wave::__get_Count()
{
	int i = 0;
	for (; i < 50; i++)
	{
		ZombieType ztype = Memory::ReadMemory<ZombieType>(BaseAddress + i * 4);
		if (ztype == ZombieTypeNone)break;
	}
	return i;
};

void PVZ::Wave::GetAll(ZombieType* ztypes)
{
	int count = Count;
	for (int i = 0; i < count; i++)
	{
		ZombieType ztype = Memory::ReadMemory<ZombieType>(BaseAddress + i * 4);
		ztypes[i] = ztype;
	}
}

void PVZ::Wave::SetAll(ZombieType* ztypes, size_t length)
{
	int len = min(length, 50);
	for (int i = 0; i < len; i++)
		Memory::WriteMemory<ZombieType>(BaseAddress + i * 4, ztypes[i]);
	if (len < 50)Memory::WriteMemory<ZombieType>(BaseAddress + len * 4, ZombieTypeNone);
}

ZombieType PVZ::Wave::Get(int index)
{
	if (index >= 0 && index < Count)
		return Memory::ReadMemory<ZombieType>(BaseAddress + index * 4);
	return ZombieTypeNone;
}

void PVZ::Wave::Set(int index, ZombieType ztype)
{
	if (index >= 0 && index < Count)
		Memory::WriteMemory<ZombieType>(BaseAddress + index * 4, ztype);
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
		Set(count - 1, ZombieTypeNone);
	}
}

void PVZ::Wave::Add(ZombieType ztype)
{
	int count = Count;
	if (count < 50)
	{
		Memory::WriteMemory<ZombieType>(BaseAddress + count * 4, ztype);
		if (count < 49)Memory::WriteMemory<ZombieType>(BaseAddress + (count + 1) * 4, ZombieTypeNone);
	}
}

#pragma endregion

#pragma region methods

void PVZ::Memory::IngectDll(LPCSTR dllname)
{
	int Address = PVZ::Memory::AllocMemory();
	SETARG(__asm__InjectDll, 1) = Address + 0x13;
	lstrcpyA((LPSTR)(__asm__InjectDll + 0x13), dllname);
	WriteArray<byte>(Address, STRING(__asm__InjectDll));
	WriteMemory<byte>(0x552014, 0xFE);
	CreateThread(Address);
	WriteMemory<byte>(0x552014, 0xDB);
	FreeMemory(Address);
}

PVZ::Lawn* PVZ::GetLawn()
{
	return new Lawn(BaseAddress);
}

PVZ::Icetrace* PVZ::GetIcetrace()
{
	return new Icetrace(BaseAddress);
}

PVZ::Wave* PVZ::GetWave(int index)
{
	/*must less than WaveNum*/
	return new Wave(BaseAddress + 0x6B4 + index * 200);
}

void PVZ::GetZombieSeed(ZombieType* ztypes)
{
	int p = 0;
	for (int i = 0; i < 33; i++)
	{
		if (Memory::ReadMemory<byte>(BaseAddress + 0x54D4 + i))
		{
			ztypes[p] = ZombieType(i);
			p++;
		}
	}
}

void PVZ::Earthquake(int horizontalAmplitude, int verticalAmplitude, int duration)
{
	Memory::WriteMemory<int>(BaseAddress + 0x5540, duration);
	Memory::WriteMemory<int>(BaseAddress + 0x5544, horizontalAmplitude);
	Memory::WriteMemory<int>(BaseAddress + 0x5548, verticalAmplitude);
}

#pragma endregion
