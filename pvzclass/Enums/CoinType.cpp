#include "CoinType.h"

const char* CoinType::ToString(CoinType coint)
{
	switch (coint)
	{
	case CoinType::None:
		return "None";
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
	case CoinType::FinalSeedPacket:
		return "FinalSeedPacket";
	case CoinType::Trophy:
		return "Trophy";
	case CoinType::Shovel:
		return "Shovel";
	case CoinType::Almanac:
		return "Almanac";
	case CoinType::CarKets:
		return "CarKets";
	case CoinType::Vase:
		return "Vase";
	case CoinType::WateringCan:
		return "WateringCan";
	case CoinType::Taco:
		return "Taco";
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
	case CoinType::SilverSunflower:
		return "SilverSunflower";
	case CoinType::GoldSunflower:
		return "GoldSunflower";
	case CoinType::Chocolate:
		return "Chocolate";
	case CoinType::AwardChocolate:
		return "AwardChocolate";
	case CoinType::PresentMinigames:
		return "PresentMinigames";
	case CoinType::PresentPuzzle:
		return "PresentPuzzle";
	default:
		return "InValid_Value_Of_CoinType";
	}
}
