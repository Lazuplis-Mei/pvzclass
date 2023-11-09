#pragma once
#include "PVZ.h"
#include "Extensions.h"

#define MEMREAD_BYTE(address) PVZ::Memory::ReadMemory<byte>(address)
#define MEMREAD_INT(address) PVZ::Memory::ReadMemory<int>(address)
namespace Const
{
	inline int ReadCoinValue(CoinType::CoinType type)
	{
		switch (type)
		{
		case(CoinType::SilverDollar):
			return(MEMREAD_INT(0x430A46));
		case(CoinType::GoldDollar):
			return(MEMREAD_BYTE(0x430A53) + 2);
		case(CoinType::Diamond):
			return(MEMREAD_BYTE(0x430A63));
		case(CoinType::NormalSun):
			return(MEMREAD_INT(0x4309F0));
		case(CoinType::MiniSun):
			return(MEMREAD_BYTE(0x4309FD) + 5);
		case(CoinType::LargeSun):
			return(MEMREAD_BYTE(0x430A0D));
		default:
			return(0);
		}
	}

	inline void WriteCoinValue(CoinType::CoinType type, byte val)
	{
		bool b = true;
		switch (type)
		{
		case(CoinType::SilverDollar):
			MEMMOD_INT(0x430A46, val, 1);
			break;
		case(CoinType::GoldDollar):
			MEMMOD_BYTE(0x430A53, (val - 2), 3);
			MEMMOD_INT(0x4329DC, val, 5);
			break;
		case(CoinType::Diamond):
			MEMMOD_BYTE(0x430A53, val, 64);
			MEMMOD_BYTE(0x4329EE, val, 64);
			break;
		case(CoinType::NormalSun):
			MEMMOD_INT(0x4309F0, val, 25);
			MEMMOD_INT(0x4329A9, val, 25);
			break;
		case(CoinType::MiniSun):
			MEMMOD_BYTE(0x4309FD, (val - 5), 10);
			MEMMOD_INT(0x4329B4, val, 15);
			break;
		case(CoinType::LargeSun):
			MEMMOD_BYTE(0x430A0D, val, 50);
			MEMMOD_BYTE(0x4329C6, val, 50);
			break;
		default:
			return;
		}
	}

	inline int GetZenGardenXPixel(int row, int column, SceneType::SceneType scene)
	{
		int baseaddress = 0;
		switch (scene)
		{
		case SceneType::MushroomGarden:
			baseaddress = 0x69E050;
			break;
		case SceneType::Aquarium:
			baseaddress = 0x69E0D0;
			break;
		case SceneType::ZenGarden:
			baseaddress = 0x69DE50;
		}
		return(MEMREAD_INT(baseaddress + row * 0x80 + column * 0x10));
	}

	inline int GetZenGardenYPixel(int row, int column, SceneType::SceneType scene)
	{
		int baseaddress = 0;
		switch (scene)
		{
		case SceneType::MushroomGarden:
			baseaddress = 0x69E050;
			break;
		case SceneType::Aquarium:
			baseaddress = 0x69E0D0;
			break;
		case SceneType::ZenGarden:
			baseaddress = 0x69DE50;
		}
		return(MEMREAD_INT(baseaddress + row * 0x80 + column * 0x10 + 4));
	}

	//@brief 获取指定关卡的初始场景类型。不支持冒险模式。
	//@param mode 关卡类型。
	//@return 该关卡的初始场景类型。
	inline SceneType::SceneType GetLevelScene(PVZLevel::PVZLevel mode)
	{
		byte num = MEMREAD_BYTE(0x40AAC0) - 1;
		switch (num)
		{
		case 5:
			num = 8;
			break;
		case 6:
			num = 5;
			break;
		case 8:
			num = 9;
			break;
		}
		return((SceneType::SceneType)num);
	}

	//@brief 设置指定关卡的初始场景类型。不支持冒险模式，无法设定为蘑菇圆场景。
	//@param mode 关卡类型。
	//@param type 设定的场景类型。
	//@return 是否设置成功。
	inline bool SetLevelScene(PVZLevel::PVZLevel mode, SceneType::SceneType type)
	{
		if (mode == PVZLevel::Adventure || type == SceneType::MushroomGarden)
			return(false);
		byte result;
		switch (type)
		{
		case SceneType::MoonNight:
			result = 7;
			break;
		case SceneType::Aquarium:
			result = 6;
			break;
		case SceneType::TreeofWisdom:
			result = 9;
			break;
		default:
			result = type + 1;
		}
		bool b = true;
		return(MEMMOD_BYTE(0x40AAC0 + mode, result, 0));
	}
}