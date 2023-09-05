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
			MEMMOD_BYTE(0x4309FD, (val + 5), 10);
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
}