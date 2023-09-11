#pragma once
namespace MagnetItemType
{
	enum MagnetItemType
	{
		None,
		Pail_1,
		Pail_2,
		Pail_3,
		FootballHelmet_1,
		FootballHelmet_2,
		FootballHelmet_3,
		Door_1,
		Door_2,
		Door_3,
		Pogo_1,
		Pogo_2,
		Pogo_3,
		JackInTheBox,
		Ladder_1,
		Ladder_2,
		Ladder_3,
		LadderPlaced,
		SilverCoin,
		GoldCoin,
		Diamond,
		Pickaxe,
	};

	extern const char* ToString(MagnetItemType mitemtype);
};

