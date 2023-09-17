#pragma once
namespace CoinType
{

	enum CoinType
	{
		None,
		SilverDollar,
		GoldDollar,
		Diamond,
		NormalSun,
		MiniSun,
		LargeSun,
		FinalSeedPacket,
		Trophy,
		Shovel,
		Almanac,
		CarKets,
		Vase,
		WateringCan,
		Taco,
		Note,
		PlantCard,
		PlantPresent,
		MoneyBag,
		SealedPresent,
		DiamondBag,
		SilverSunflower,
		GoldSunflower,
		Chocolate,
		AwardChocolate,
		PresentMinigames,
		PresentPuzzle
	};

	extern const char* ToString(CoinType coint);

}