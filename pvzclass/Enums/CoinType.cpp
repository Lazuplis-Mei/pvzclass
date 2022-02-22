#include "CoinType.h"

const char* CoinType::ToString(CoinType coint)
{
	switch (coint)
	{
	case CoinType::SilverDollar:
		return "SilverDollar";
	case CoinType::GoldDollar:
		return "GoldDollar";
	case CoinType::Diamond:
		return "Diamond";
	case CoinType::NormalSun:
		return "NormalSun";
	case CoinType::MiniSun:
		return "MiniSun";
	case CoinType::LargeSun:
		return "LargeSun";
	case CoinType::Trophy:
		return "Trophy";
	case CoinType::Note:
		return "Note";
	case CoinType::PlantCard:
		return "PlantCard";
	case CoinType::PlantPresent:
		return "PlantPresent";
	case CoinType::MoneyBag:
		return "MoneyBag";
	case CoinType::SealedPresent:
		return "SealedPresent";
	case CoinType::DiamondBag:
		return "DiamondBag";
	default:
		return "InValid_Value_Of_CoinType";
	}
}
