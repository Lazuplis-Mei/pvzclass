#pragma once
#include "PVZ.h"
#include "Creators.h"


#define MEMMOD_BYTE(address,v,rv) PVZ::Memory::WriteMemory<byte>(address,b?v:rv)
#define MEMMOD_INT(address,v,rv) PVZ::Memory::WriteMemory<int>(address,b?v:rv)
#define MEMMOD_SHORT(address,v,rv) PVZ::Memory::WriteMemory<short>(address,b?v:rv)
#define JO 112
#define JZ 116
#define JNE 117
#define JUMP 235
#define JLE 126

using ThreeState::Enable;
using ThreeState::None;
using ThreeState::Disable;
using Memory = PVZ::Memory;

//启用/禁用砸罐子功能。
//包括罐子高亮、罐子可砸、小丑炸罐子、巨人砸罐子。
//@param state 功能的启用状态，缺省值为 Enable。
inline void EnableVaseBreak(ThreeState::ThreeState state = Enable)
{
	switch (state)
	{
	case Enable:
		Memory::WriteMemory<short>(0x40EB36, 0x1571);
		Memory::WriteMemory<byte>(0x411AE5, 0x80);

		Memory::WriteMemory<byte>(0x422183, JO);
		Memory::WriteMemory<short>(0x424791, 0x1471);

		Memory::WriteMemory<byte>(0x526CE0, JO);

		Memory::WriteMemory<short>(0x526DBB, 0x1571);
		Memory::WriteMemory<byte>(0x527257, JO);
		break;
	case None:
		Memory::WriteMemory<short>(0x40EB36, 0x057C);
		Memory::WriteMemory<byte>(0x411AE5, 0x84);

		Memory::WriteMemory<byte>(0x422183, JZ);
		Memory::WriteMemory<short>(0x424791, 0x057C);

		Memory::WriteMemory<byte>(0x526CE0, JZ);

		Memory::WriteMemory<short>(0x526DBB, 0x057C);
		Memory::WriteMemory<byte>(0x527257, JZ);
		break;
	case Disable:
		Memory::WriteMemory<short>(0x40EB36, 0x7871);
		Memory::WriteMemory<byte>(0x411AE5, 0x81);

		Memory::WriteMemory<byte>(0x422183, JUMP);
		Memory::WriteMemory<short>(0x424791, 0x1971);

		Memory::WriteMemory<byte>(0x526CE0, JUMP);

		Memory::WriteMemory<short>(0x526DBB, 0x5971);
		Memory::WriteMemory<byte>(0x527257, JUMP);
	}
}

//是否启用后台运行
inline void EnableBackgroundRunning(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x54EBA8, JO, JZ);
}

//是否显示隐藏关卡
inline void ShowHiddenLevel(BOOLEAN b = true)
{
	MEMMOD_BYTE(b ? 0x42DF5D : 0x54EBA8, 56, 136);
}

//是否启动传送门。若为“是”，则该方法会自动创建默认的传送门
inline void EnablePortal(BOOLEAN b = true)
{
	if (b && PVZ::GetBoard()->GetBaseAddress() != 0)Creator::__CreatePortal();
	MEMMOD_BYTE(0x467665, JO, JNE);
	MEMMOD_BYTE(0x41FFB4, JO, JNE);
	MEMMOD_BYTE(0x4248CE, JO, JNE);
}

//是否固定传送门
inline void FixPortal(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x4276DD, 0, 255);
}

inline void SetSunMax(int sunmax)
{
	PVZ::Memory::WriteMemory<int>(0x430A1F, sunmax);
	PVZ::Memory::WriteMemory<int>(0x430A2B, sunmax);
}

inline void RemoveSunUpperLimit(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x430A23, JUMP, JLE);
	MEMMOD_BYTE(0x430A78, JUMP, JLE);
	MEMMOD_BYTE(0x48CAB0, JUMP, JLE);
}

inline void OverlapPlanting(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x40FE30, 129, 132);
	MEMMOD_BYTE(0x42A2D9, 141, 132);
	MEMMOD_BYTE(0x438E40, JUMP, JZ);
}

inline void IgnoreResources(BOOLEAN b = true)
{
	MEMMOD_INT(0x41BA72, -214234000, -215282561);
	MEMMOD_BYTE(0x41BAC0, 145, 158);
	MEMMOD_BYTE(0x42487F, JUMP, JZ);
	MEMMOD_BYTE(0x427A92, 128, 143);
	MEMMOD_BYTE(0x427DFD, 128, 143);
	MEMMOD_BYTE(0x48CAA5, 57, 41);
	PVZ::Memory::WriteMemory<LONGLONG>(0x48C7A0, b ? 174109865281658857 : 173951535625964815);
}

inline void CancelCardCooldown(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x487296, JO, JLE);
	MEMMOD_BYTE(0x488250, JUMP, JNE);
	MEMMOD_BYTE(0x488E76, 1, 0);
}

inline void ConveyorBeltNoDelay(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x422D20, 128, 143);
	MEMMOD_BYTE(0x489CA1, 51, 133);
}

inline void FullScreenFog(BOOLEAN b = true)
{
	MEMMOD_SHORT(0x41A476, 16363, 1397);
	MEMMOD_INT(0x41C1C0, 12828723, 9208203);
	MEMMOD_BYTE(0x41A4BA, 0, 4);
	if (b)
		for (int i = 0; i < 64; i++)
			PVZ::Memory::WriteMemory<int>(PVZBASEADDRESS + 0xC8 + 4 * i, 0);
}

inline void BlockZombie(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x4265DC, JUMP, JZ);
}

inline void VasePerspect(BOOLEAN b = true)
{
	byte __vaseperspect_set[10]{ 0xC7, 0x47, 0x4C,0x64, 0, 0, 0, 0x5E, 0x59,0xC3 };
	byte __vaseperspect_reset[10]{ 0x85, 0xC0, 0x7E, 6, 0x83, 0xC0, 0xFF, 0x89, 0x47, 0x4C };
	if (b)PVZ::Memory::WriteArray<byte>(0x44E5CC, STRING(__vaseperspect_set));
	else PVZ::Memory::WriteArray<byte>(0x44E5CC, STRING(__vaseperspect_reset));
}

inline void LockShovel(PVZ::MousePointer* mousepointer, BOOLEAN b = true)
{
	if (b)mousepointer->Type = MouseType::Shovel;
	PVZ::Memory::WriteMemory<LONGLONG>(0x41233D, b ? -8029759805927192901 : 586669480753);
}

inline void AutoCollect(BOOLEAN b = true)
{
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
	if (b)
	{
		auto coins = PVZ::GetBoard()->GetAllCoins();
		for (int i = 0; i < coins.size(); i++)
			coins[i]->Collect();
		PVZ::Memory::WriteMemory<byte>(0x40CCDA, 0xE9);
		PVZ::Memory::WriteMemory<int>(0x40CCDB, PVZ::Memory::Variable + 300 - 4 - 0x40CCDB);
		PVZ::Memory::WriteArray<byte>(PVZ::Memory::Variable + 300, STRING(__autocollect_set));
	}
	else
		PVZ::Memory::WriteArray<byte>(0x40CCDA, STRING(__autocollect_reset));
}

inline void DisableInitialLawnmover(BOOLEAN b = true)
{
	MEMMOD_INT(0x40BC8C, 34793, 1965488771);
	MEMMOD_BYTE(0x40BC90, 0, 5);
}

inline void DisableIceLevelFailSound(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x42492D, JUMP, JNE);
}