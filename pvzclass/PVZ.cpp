#include "PVZ.h"

/*
	0x530: active 为1时阻塞游戏更新，执行完Execute之后改为0
	0x540: enable 为1时代表可以执行Execute
*/
byte __asm__Execute[]
{
	0xC6, 0x05, 0, 0, 0, 0, 0x01, // mov byte ptr [Variable+0x540], 1
	0x80, 0x3D, 0, 0, 0, 0, 0x00, // cmp byte ptr [Variable+0x530], 0
	0x75, 0xF7, // jne last line
	0xC6, 0x05, 0, 0, 0, 0, 0x00, // mov byte ptr [Variable+0x540], 0
	0x6A, 0xFF, 0x68, 0x35, 0xFA, 0x64, 0x00, // original code
	0xE9, 0, 0, 0, 0 // jmp 0x415D47
};

byte __asm__UpdateHook[]
{
	0xE9, 0, 0, 0, 0, 0x66, 0x90
};

namespace PVZ
{
	void InitPVZ(DWORD pid)
	{
		Memory::processId = pid;
		Memory::hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
		Memory::mainwindowhandle = Memory::ReadMemory<HWND>(PVZ_BASE + 0x350);
		Memory::Variable = Memory::AllocMemory(4);
		Memory::mainThreadId = Memory::ReadMemory<DWORD>(PVZ_BASE + 0x33C);
		Memory::hThread = OpenThread(THREAD_ALL_ACCESS, true, Memory::mainThreadId);

		Memory::immediateExecute = false;
		Memory::localExecute = false;
		SETARG(__asm__Execute, 2) = Memory::Variable + 0x540;
		SETARG(__asm__Execute, 9) = Memory::Variable + 0x530;
		SETARG(__asm__Execute, 18) = Memory::Variable + 0x540;
		SETARG(__asm__Execute, 31) = 0x415D47 - Memory::Variable - 0x520 - 3;
		Memory::WriteArray<BYTE>(Memory::Variable + 0x500, STRING(__asm__Execute));
		SETARG(__asm__UpdateHook, 1) = Memory::Variable + 0x500 - 0x415D40 - 5;
		Memory::WriteArray<BYTE>(0x415D40, STRING(__asm__UpdateHook));
	}

	void QuitPVZ()
	{
		CloseHandle(Memory::hProcess);
		Memory::FreeMemory(Memory::Variable);
	}
}

#pragma region background methods

const char* PVZ::PVZutil::__get_Version()
{
	return "1.15.3.240125";
}

PVZVersion::PVZVersion PVZ::PVZutil::__get_GameVersion()
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

#pragma endregion

#pragma region methods

bool PVZ::Memory::InjectDll(const char* dllname)
{
	SETARG(__asm__InjectDll, 1) = Variable + 0x600;
	SETARG(__asm__InjectDll, 19) = Variable;
	int len = strlen(dllname);
	WriteArray<const char>(Variable + 0x600, dllname, len);
	WriteMemory<char>(Variable + 0x600 + len, 0);
	DLLAddress = Execute(STRING(__asm__InjectDll));
	return DLLAddress != 0;
}

int PVZ::Memory::GetProcAddress(const char* procname)
{
	SETARG(__asm__GetProcAddress, 1) = Variable + 0x600;
	SETARG(__asm__GetProcAddress, 6) = DLLAddress;
	SETARG(__asm__GetProcAddress, 24) = Variable;
	int len = strlen(procname);
	WriteArray<const char>(Variable + 0x600, procname, len);
	WriteMemory<char>(Variable + 0x600 + len, 0);
	return Execute(STRING(__asm__GetProcAddress));
}

int PVZ::Memory::InvokeDllProc(const char* procname)
{
	int address = GetProcAddress(procname);
	if (address == 0) return -1;
	byte asmcode[] = { INVOKE(address), RET };
	return PVZ::Memory::Execute(STRING(asmcode));
}

SPT<PVZ::PVZApp> PVZ::GetPVZApp()
{
	return MKS<PVZApp>(PVZ::Memory::ReadMemory<DWORD>(0x6A9EC0));
}

SPT<PVZ::Mouse> PVZ::GetMouse()
{
	return MKS<Mouse>(Memory::ReadPointer(0x6A9EC0, 0x320));
}

SPT<PVZ::Board> PVZ::GetBoard()
{
	int address = PVZBASEADDRESS;
	return(address == 0 ? nullptr : MKS<Board>(address));
}

SPT<PVZ::SeedChooserScreen> PVZ::GetSeedChooserScreen()
{
	int address = Memory::ReadPointer(0x6A9EC0, 0x774);
	return(address == 0 ? nullptr : MKS<SeedChooserScreen>(address));
}

SPT<PVZ::ZenGarden> PVZ::GetZenGarden()
{
	return MKS<ZenGarden>(Memory::ReadPointer(0x6A9EC0, 0x81C));
}

SPT<PVZ::PlantDefinition> PVZ::GetPlantDefinition(PlantType::PlantType type)
{
	return MKS<PlantDefinition>(type);
}

SPT<PVZ::ZombieDefinition> PVZ::GetZombieDefinition(ZombieType::ZombieType type)
{
	return MKS<ZombieDefinition>(type);
}

SPT<PVZ::ProjectileDefinition> PVZ::GetProjectileDefinition(ProjectileType::ProjectileType type)
{
	return MKS<ProjectileDefinition>(type);
}

SPT<PVZ::ChallengeDefinition> PVZ::GetChallengeDefinition(PVZLevel::PVZLevel mode)
{
	return MKS<ChallengeDefinition>(mode);
}

SPT<PVZ::SaveData> PVZ::GetSaveData()
{
	return MKS<SaveData>(Memory::ReadPointer(0x6A9EC0, 0x82C));
}

SPT<PVZ::Music> PVZ::GetMusic()
{
	return MKS<Music>(Memory::ReadPointer(0x6A9EC0, 0x83C));
}

#pragma endregion