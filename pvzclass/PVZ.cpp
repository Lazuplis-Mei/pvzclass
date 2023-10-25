#include "PVZ.h"

namespace PVZ
{

void InitPVZ(DWORD pid)
{
	Memory::processId = pid;
	Memory::hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	Memory::mainwindowhandle = Memory::ReadMemory<HWND>(PVZ_BASE + 0x350);
	Memory::Variable = Memory::AllocMemory();

	DEBUG_EVENT debugEvent;
	DebugActiveProcess(Memory::processId);
	WaitForDebugEvent(&debugEvent, -1);
	ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
	DebugActiveProcessStop(PVZ::Memory::processId);

	Memory::mainThreadId = debugEvent.dwThreadId;
	Memory::hThread = OpenThread(THREAD_ALL_ACCESS, true, debugEvent.dwThreadId);
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
	return "beta_1.15.0.3.231026";
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

int PVZ::GameObject::GetBaseAddress()
{
	return this->BaseAddress;
}