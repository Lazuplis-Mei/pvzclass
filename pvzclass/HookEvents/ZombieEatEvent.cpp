#include "ZombieEatEvent.h"

BYTE hook_7000A0[] = {
	0x89,0x3D,0x94,0x00,0x70,0x00,0x89,0x0D,
	0x98,0x00,0x70,0x00,0xC7,0x05,0x9C,0x00,
	0x70,0x00,0x01,0x00,0x00,0x00,0x83,0x3D,
	0x9C,0x00,0x70,0x00,0x01,0x74,0xF7,0xE8,
	0x7C,0xFA,0xE2,0xFF,0xE9,0xC5,0xF5,0xE2,
	0xFF };

BYTE hook_52F689[] = { 0xE9,0x12,0x0A,0x1D,0x00 };

BYTE hook_52F689_raw[] = { 0xE8,0xB2,0x04,0x00,0x00 };

void ZombieEatEvent::start()
{
	PVZ::Memory::WriteArray<BYTE>(0x7000A0, hook_7000A0, 41);
	PVZ::Memory::WriteArray<BYTE>(0x52F689, hook_52F689, 5);
}

void ZombieEatEvent::run()
{
	int code = PVZ::Memory::ReadMemory<DWORD>(0x70009C);
	if (code == 0) return;

	auto zombie = std::make_shared<PVZ::Zombie>(PVZ::Memory::ReadMemory<DWORD>(0x700094));
	auto plant = std::make_shared<PVZ::Plant>(PVZ::Memory::ReadMemory<DWORD>(0x700098));

	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie, plant);
	}

	PVZ::Memory::WriteMemory<DWORD>(0x70009C, 0);
}

void ZombieEatEvent::end()
{
	PVZ::Memory::WriteArray<BYTE>(0x52F689, hook_52F689_raw, 5);
}