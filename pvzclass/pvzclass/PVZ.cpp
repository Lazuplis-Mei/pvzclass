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
	return "0.4.0.190605";
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

#pragma region Animation Class

PVZ::Animation::Animation(int idoraddress)
{
	if (idoraddress > 1024)
		BaseAddress = idoraddress;
	else
		BaseAddress = Memory::ReadPointer(0x6A9EC0, 0x820, 8, 0) + idoraddress * 0xA0;
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

#pragma region Zombie Class

PVZ::Zombie::Zombie(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(Memory::ReadMemory<int>(PVZ_BASE + 0x768) + 0x90) + indexoraddress * 0x15C;
#if _DEBUG
	DebugType = Type;
#endif
}

void PVZ::Zombie::Light(int cs)
{
	Memory::WriteMemory<int>(BaseAddress + 0x54, cs);
}

void PVZ::Zombie::GetCollision(CollisionBox* collbox)
{
	collbox->X = Memory::ReadMemory<int>(BaseAddress + 0x8C);
	collbox->Y = Memory::ReadMemory<int>(BaseAddress + 0x90);
	collbox->Length = Memory::ReadMemory<int>(BaseAddress + 0x94);
	collbox->Height = Memory::ReadMemory<int>(BaseAddress + 0x98);
}

void PVZ::Zombie::SetCollision(CollisionBox* collbox)
{
	Memory::WriteMemory<int>(BaseAddress + 0x8C, collbox->X);
	Memory::WriteMemory<int>(BaseAddress + 0x90, collbox->Y);
	Memory::WriteMemory<int>(BaseAddress + 0x94, collbox->Length);
	Memory::WriteMemory<int>(BaseAddress + 0x98, collbox->Height);
}

void PVZ::Zombie::GetAttackCollision(CollisionBox* collbox)
{
	collbox->X = Memory::ReadMemory<int>(BaseAddress + 0x9C);
	collbox->Y = Memory::ReadMemory<int>(BaseAddress + 0xA0);
	collbox->Length = Memory::ReadMemory<int>(BaseAddress + 0xA4);
	collbox->Height = Memory::ReadMemory<int>(BaseAddress + 0xA8);
}

void PVZ::Zombie::SetAttackCollision(CollisionBox* collbox)
{
	Memory::WriteMemory<int>(BaseAddress + 0x9C, collbox->X);
	Memory::WriteMemory<int>(BaseAddress + 0xA0, collbox->Y);
	Memory::WriteMemory<int>(BaseAddress + 0xA4, collbox->Length);
	Memory::WriteMemory<int>(BaseAddress + 0xA8, collbox->Height);
}

void PVZ::Zombie::GetAccessoriesType1(AccessoriesType1* acctype1)
{
	acctype1->Type = Memory::ReadMemory<ZombieAccessoriesType1>(BaseAddress + 0xC4);
	acctype1->Hp = Memory::ReadMemory<int>(BaseAddress + 0xD0);
	acctype1->MaxHp = Memory::ReadMemory<int>(BaseAddress + 0xD4);
}

void PVZ::Zombie::SetAccessoriesType1(AccessoriesType1* acctype1)
{
	Memory::WriteMemory<ZombieAccessoriesType1>(BaseAddress + 0xC4, acctype1->Type);
	Memory::WriteMemory<int>(BaseAddress + 0xD0, acctype1->Hp);
	Memory::WriteMemory<int>(BaseAddress + 0xD4, acctype1->MaxHp);
}

void PVZ::Zombie::GetAccessoriesType2(AccessoriesType2* acctype2)
{
	acctype2->Type = Memory::ReadMemory<ZombieAccessoriesType2>(BaseAddress + 0xD8);
	acctype2->Hp = Memory::ReadMemory<int>(BaseAddress + 0xDC);
	acctype2->MaxHp = Memory::ReadMemory<int>(BaseAddress + 0xE0);
}

void PVZ::Zombie::SetAccessoriesType2(AccessoriesType2* acctype2)
{
	Memory::WriteMemory<ZombieAccessoriesType2>(BaseAddress + 0xD8, acctype2->Type);
	Memory::WriteMemory<int>(BaseAddress + 0xDC, acctype2->Hp);
	Memory::WriteMemory<int>(BaseAddress + 0xE0, acctype2->MaxHp);
	
}

void PVZ::Zombie::GetBodyHp(int* hp, int* maxhp)
{
	*hp = Memory::ReadMemory<int>(BaseAddress + 0xC8);
	*maxhp = Memory::ReadMemory<int>(BaseAddress + 0xCC);
}

void PVZ::Zombie::SetBodyHp(int hp, int maxhp)
{
	Memory::WriteMemory<int>(BaseAddress + 0xC8, hp);
	Memory::WriteMemory<int>(BaseAddress + 0xCC, maxhp);
}

void PVZ::Zombie::GetAnimation(PVZ::Animation* animation)
{
	animation = new Animation(Memory::ReadMemory<short>(BaseAddress + 0x118));
}

void PVZ::Zombie::Hit(int damge, DamageType type)
{
	SETARG(__asm_Hit, 1) = BaseAddress;
	SETARG(__asm_Hit, 6) = type;
	SETARG(__asm_Hit, 11) = damge;
	Memory::Execute(STRING(__asm_Hit));
}

void PVZ::Zombie::Blast()
{
	SETARG(__asm_Blast, 1) = BaseAddress;
	Memory::Execute(STRING(__asm_Blast));
}

void PVZ::Zombie::Butter()
{
	SETARG(__asm_Butter, 1) = BaseAddress;
	Memory::Execute(STRING(__asm_Butter));
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
	if (index >= 0 && index <= WaveCount)
		return new Wave(BaseAddress + 0x6B4 + index * 200);
	else
		return NULL;
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

void PVZ::Assault(int countdown)
{
	Memory::WriteMemory<int>(BaseAddress + 0x5574, countdown);
}

void PVZ::Win()
{
	SETARG(__asm_Win, 1) = BaseAddress;
	if (LevelId > 0 && LevelId < 16)
	{
		if (GameState == Playing)Memory::Execute(STRING(__asm_Win));
	}
	else Memory::Execute(STRING(__asm_Win));
}

void PVZ::Bell(int countdown)
{
	Memory::WriteMemory<int>(BaseAddress + 0x5750, countdown);
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



#pragma endregion

