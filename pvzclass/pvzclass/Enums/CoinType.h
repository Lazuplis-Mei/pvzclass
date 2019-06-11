#pragma once
namespace CoinType
{

	enum CoinType
	{
		SilverDollar = 1,
		GoldDollar,
		Diamond,
		NormalSun,
		MiniSun,
		LargeSun,
		Trophy = 8,
		Note = 15,
		PlantCard,
		PlantPresent,
		MoneyBag,
	};

	extern const char* ToString(CoinType coint);

}