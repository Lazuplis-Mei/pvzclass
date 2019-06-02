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
};

PVZVersion PVZ::__get_Version()
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

PVZ::Lawn::Lawn(int baseaddress)
{
	BaseAddress = baseaddress;
};

LawnType PVZ::Lawn::GetGridType(int row, int column)
{
	if (row >= 0 && row < 6 && column >= 0 && column < 9)
		return Memory::ReadMemory<LawnType>(BaseAddress + 0x168 + 4 * (6 * column + row));
	return LawnType(-1);
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
	return RouteType(-1);
};

void PVZ::Lawn::SetRouteType(int route, RouteType type)
{
	if (route >= 0 && route < 6)
		Memory::WriteMemory<RouteType>(BaseAddress + 0x5D8 + 4 * route, type);
};

PVZ::Lawn* PVZ::GetLawn()
{
	return new Lawn(BaseAddress);
}

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

PVZ::Icetrace* PVZ::GetIcetrace()
{
	return new Icetrace(BaseAddress);
}

PVZ::Wave::Wave(int baseaddress)
{
	BaseAddress = baseaddress;
}

int PVZ::Wave::GetAll(ZombieType* ztypes)
{
	int i = 0;
	for (; i < 50; i++)
	{
		ZombieType ztype = Memory::ReadMemory<ZombieType>(BaseAddress + i * 4);
		if (ztype + 1)ztypes[i] = ztype;
	}
	return i;
}

void PVZ::Wave::SetAll(ZombieType* ztypes, size_t length)
{
	int len = length > 50 ? 50 : length;
	for (int i = 0; i < len; i++)
	{
		Memory::WriteMemory<ZombieType>(BaseAddress + i * 4, ztypes[i]);
	}
	if (len < 50)Memory::WriteMemory<ZombieType>(BaseAddress + (len + 1) * 4, ZombieType(-1));
}
