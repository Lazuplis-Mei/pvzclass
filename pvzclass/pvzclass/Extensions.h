#pragma once
#include "PVZ.h"
#include "Creaters.h"


#define MEMMOD_BYTE(address,v,rv) PVZ::Memory::WriteMemory<byte>(address,b?v:rv)
#define MEMMOD_INT(address,v,rv) PVZ::Memory::WriteMemory<int>(address,b?v:rv)
#define MEMMOD_SHORT(address,v,rv) PVZ::Memory::WriteMemory<short>(address,b?v:rv)
#define JO 112
#define JZ 116
#define JNE 117
#define JUMP 235
#define JLE 126

void EnableBackgroundRunning(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x54EBA8, JO, JZ);
}

void ShowHiddenLevel(BOOLEAN b = true)
{
	MEMMOD_BYTE(b ? 0x42DF5D : 0x54EBA8, 56, 136);
}

void EnablePortal(PVZ* pvz, BOOLEAN b = true)
{
	if (b)Creater::__CreatePortal(pvz);
	MEMMOD_BYTE(0x467665, JO, JNE);
	MEMMOD_BYTE(0x41FFB4, JO, JNE);
	MEMMOD_BYTE(0x4248CE, JO, JNE);
}

void FixPortal(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x4276DD, 0, 255);
}

void SetSunMax(int sunmax)
{
	PVZ::Memory::WriteMemory<int>(0x430A1F, sunmax);
	PVZ::Memory::WriteMemory<int>(0x430A2B, sunmax);
}

void RemoveSunUpperLimit(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x430A23, JUMP, JLE);
	MEMMOD_BYTE(0x430A78, JUMP, JLE);
	MEMMOD_BYTE(0x48CAB0, JUMP, JLE);
}

void OverlapPlanting(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x40FE30, 129, 132);
	MEMMOD_BYTE(0x42A2D9, 141, 132);
	MEMMOD_BYTE(0x438E40, JUMP, JZ);
}

void IgnoreResources(BOOLEAN b = true)
{
	MEMMOD_INT(0x41BA72, -214234000, -215282561);
	MEMMOD_BYTE(0x41BAC0, 145, 158);
	MEMMOD_BYTE(0x42487F, JUMP, JZ);
	MEMMOD_BYTE(0x427A92, 128, 143);
	MEMMOD_BYTE(0x427DFD, 128, 143);
	MEMMOD_BYTE(0x48CAA5, 57, 41);
	PVZ::Memory::WriteMemory<LONGLONG>(0x48C7A0, b ? 174109865281658857 : 173951535625964815);
}

void CancelCardCooldown(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x487296, JO, JLE);
	MEMMOD_BYTE(0x488250, JUMP, JNE);
	MEMMOD_BYTE(0x488E76, 1, 0);
}

void ConveyorBeltNoDelay(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x422D20, 128, 143);
	MEMMOD_BYTE(0x489CA1, 51, 133);
}

void FullScreenFog(BOOLEAN b = true)
{
	MEMMOD_SHORT(0x41A476, 16363, 1397);
	MEMMOD_INT(0x41C1C0, 12828723, 9208203);
	MEMMOD_BYTE(0x41A4BA, 0, 4);
	if (b)
		for (int i = 0; i < 64; i++)
			PVZ::Memory::WriteMemory<int>(PVZBASEADDRESS + 0xC8 + 4 * i, 0);
}

void BlockZombie(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x4265DC, JUMP, JZ);
}

byte __vaseperspect_set[10]{ 0xC7, 0x47, 0x4C,0x64, 0, 0, 0, 0x5E, 0x59,0xC3 };
byte __vaseperspect_reset[10]{ 0x85, 0xC0, 0x7E, 6, 0x83, 0xC0, 0xFF, 0x89, 0x47, 0x4C };

void VasePerspect(BOOLEAN b = true)
{
	if (b)PVZ::Memory::WriteArray<byte>(0x44E5CC, STRING(__vaseperspect_set));
	else PVZ::Memory::WriteArray<byte>(0x44E5CC, STRING(__vaseperspect_reset));
}

void LockShovel(PVZ::MousePointer* mousepointer, BOOLEAN b = true)
{
	if (b)mousepointer->Type = MouseType::Shovel;
	PVZ::Memory::WriteMemory<LONGLONG>(0x41233D, b ? -8029759805927192901 : 586669480753);
}

byte __autocollect_set[26]
{
	PUSHAD,
	0x8B,0xC8,
	0x83,0x79,0x58,0x10,
    0x74, 5,
	INVOKE(0x432060),
	POPAD,
	RETN(0x10),
};

byte __autocollect_reset[3]{ 0xC2, 0x10, 0 };

void AutoCollect(PVZ* pvz, BOOLEAN b = true)
{
	if (b)
	{
		PVZ::Coin* coins[100];
		int len = pvz->GetAllCoins(coins);
		for (int i = 0; i < len; i++)
			coins[i]->Collect();
		PVZ::Memory::WriteMemory<byte>(0x40CCDA, 0xE9);
		PVZ::Memory::WriteMemory<int>(0x40CCDB, PVZ::Memory::Variable + 300 - 4 - 0x40CCDB);
		PVZ::Memory::WriteArray<byte>(PVZ::Memory::Variable + 300, STRING(__autocollect_set));
	}
	else
		PVZ::Memory::WriteArray<byte>(0x40CCDA, STRING(__autocollect_reset));
}
