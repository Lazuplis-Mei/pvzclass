#include "PVZ.h"


PVZ::PVZ(DWORD pid)
{
	Memory::processId = pid;
	Memory::hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	Memory::mainwindowhandle = Memory::ReadMemory<HWND>(PVZ_BASE + 0x350);
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
	return "1.6.0.190725";
}

PVZVersion::PVZVersion PVZ::__get_GameVersion()
{
	int ver = Memory::ReadMemory<int>(0x552013);
	switch (ver)
	{
	case 0xC35EDB74:
		return PVZVersion::V1_0_0_1051;
	case 0x86831977:
		return PVZVersion::V1_2_0_1065;
	case 0x3B000001:
		return PVZVersion::V1_2_0_1073;
	case 0x878B0000:
		return PVZVersion::CHINESE_ENHANCED;
	case 0xA48F:
		return PVZVersion::CHINESE_VISCOSITY;
	default:
		return PVZVersion::UnknowOrNotPVZ;
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

SceneType::SceneType PVZ::__get_LevelScene()
{
	return Memory::ReadMemory<SceneType::SceneType>(BaseAddress + 0x554C);
}

void PVZ::__set_LevelScene(SceneType::SceneType value)
{
	Memory::WriteMemory<SceneType::SceneType>(BaseAddress + 0x554C, value);
	SETARG(__asm__set__LevelScene, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__set__LevelScene));
}

int PVZ::__get_WaveCount()
{
	return Memory::ReadMemory<int>(BaseAddress + 0x5564);
}

void PVZ::__set_WaveCount(int value)
{
	if (value >= 0 && value <= WaveCount)
	{
		Memory::WriteMemory<int>(BaseAddress + 0x5564, value);
		Memory::WriteMemory<int>(BaseAddress + 0x5610, value * 150 / WaveCount);
	}
}

#pragma endregion

#pragma region methods

void PVZ::Memory::InjectDll(LPCSTR dllname)
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
	if (index >= 0 && index <= WaveCount)
		return new Wave(BaseAddress + 0x6B4 + index * 200);
	else
		return NULL;
}

void PVZ::GetZombieSeed(ZombieType::ZombieType* ztypes)
{
	int p = 0;
	for (int i = 0; i < 33; i++)
	{
		if (Memory::ReadMemory<byte>(BaseAddress + 0x54D4 + i))
		{
			ztypes[p] = ZombieType::ZombieType(i);
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

void PVZ::Assault(int countdown)
{
	Memory::WriteMemory<int>(BaseAddress + 0x5574, countdown);
}

void PVZ::Win()
{
	SETARG(__asm__Win, 1) = BaseAddress;
	if (LevelId > 0 && LevelId < 16)
	{
		if (GameState == PVZGameState::Playing)Memory::Execute(STRING(__asm__Win));
	}
	else Memory::Execute(STRING(__asm__Win));
}

void PVZ::Bell(int countdown)
{
	Memory::WriteMemory<int>(BaseAddress + 0x5750, countdown);
}

PVZ::Mouse* PVZ::GetMouse()
{
	return new Mouse(Memory::ReadPointer(0x6A9EC0, 0x320));
}

int PVZ::GetAllZombies(Zombie* zombies[])
{
	int maxnum = Memory::ReadMemory<int>(BaseAddress + 0x94);
	int j = 0;
	for (int i = 0; i < maxnum; i++)
	{
		if (!Memory::ReadPointer(BaseAddress + 0x90, 0xEC + 0x15C * i))
		{
			zombies[j] = new PVZ::Zombie(i);
			j++;
		}
	}
	return j;
}

int PVZ::GetAllPlants(Plant* plants[])
{
	int maxnum = Memory::ReadMemory<int>(BaseAddress + 0xB0);
	int j = 0;
	for (int i = 0; i < maxnum; i++)
	{
		if (!Memory::ReadMemory<byte>(Memory::ReadMemory<int>(BaseAddress + 0xAC) + 0x141 + 0x14C * i))
		{
			plants[j] = new PVZ::Plant(i);
			j++;
		}
	}
	return j;
}

int PVZ::GetAllProjectile(Projectile* projectiles[])
{
	int maxnum = Memory::ReadMemory<int>(BaseAddress + 0xCC);
	int j = 0;
	for (int i = 0; i < maxnum; i++)
	{
		if (!Memory::ReadPointer(BaseAddress + 0xC8, 0x50 + 0x94 * i))
		{
			projectiles[j] = new PVZ::Projectile(i);
			j++;
		}
	}
	return j;
}

int PVZ::GetAllCoins(Coin* coins[])
{
	int maxnum = Memory::ReadMemory<int>(BaseAddress + 0xE8);
	int j = 0;
	for (int i = 0; i < maxnum; i++)
	{
		if (!Memory::ReadPointer(BaseAddress + 0xE4, 0x38 + 0xD8 * i))
		{
			coins[j] = new PVZ::Coin(i);
			j++;
		}
	}
	return j;
}

int PVZ::GetAllLawnmovers(Lawnmover* lawnmovers[])
{
	int maxnum = Memory::ReadMemory<int>(BaseAddress + 0x104);
	int j = 0;
	for (int i = 0; i < maxnum; i++)
	{
		if (!Memory::ReadPointer(BaseAddress + 0x100, 0x30 + 0x48 * i))
		{
			lawnmovers[j] = new PVZ::Lawnmover(i);
			j++;
		}
	}
	return j;
}

int PVZ::GetAllGriditems(Griditem* griditems[])
{
	int maxnum = Memory::ReadMemory<int>(BaseAddress + 0x120);
	int j = 0;
	for (int i = 0; i < maxnum; i++)
	{
		if (!Memory::ReadPointer(BaseAddress + 0x11C, 0x20 + 0xEC * i))
		{
			griditems[j] = new PVZ::Griditem(i);
			j++;
		}
	}
	return j;
}

PVZ::MousePointer* PVZ::GetMousePointer()
{
	return new MousePointer(BaseAddress);
}

PVZ::Caption* PVZ::GetCaption()
{
	return new Caption(BaseAddress);
}

PVZ::CardSlot* PVZ::GetCardSlot()
{
	return new CardSlot(BaseAddress);
}

PVZ::Miscellaneous* PVZ::GetMiscellaneous()
{
	return new Miscellaneous(BaseAddress);
}

PVZ::SaveData* PVZ::GetSaveData()
{
	return new SaveData(Memory::ReadPointer(0x6A9EC0, 0x82C));
}

PVZ::Music* PVZ::GetMusic()
{
	return new Music(Memory::ReadPointer(0x6A9EC0, 0x83C));
}



#pragma endregion


