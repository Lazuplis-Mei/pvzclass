#include "MagnetItemType.h"

const char* MagnetItemType::ToString(MagnetItemType mitemtype)
{
	switch (mitemtype)
	{
	case MagnetItemType::None:
		return "None";
	case MagnetItemType::Pail_1:
		return "Pail 1";
	case MagnetItemType::Pail_2:
		return "Pail 2";
	case MagnetItemType::Pail_3:
		return "Pail 3";
	case MagnetItemType::FootballHelmet_1:
		return "Footballelmet 1";
	case MagnetItemType::FootballHelmet_2:
		return "FootballHelmet 2";
	case MagnetItemType::FootballHelmet_3:
		return "FootballHelmet 3";
	case MagnetItemType::Door_1:
		return "Door 1";
	case MagnetItemType::Door_2:
		return "Door 2";
	case MagnetItemType::Door_3:
		return "Door 3";
	case MagnetItemType::Pogo_1:
		return "Pogo 1";
	case MagnetItemType::Pogo_2:
		return "Pogo 2";
	case MagnetItemType::Pogo_3:
		return "Pogo 3";
	case MagnetItemType::JackInTheBox:
		return "JackInTheBox";
	case MagnetItemType::Ladder_1:
		return "Ladder 1";
	case MagnetItemType::Ladder_2:
		return "Ladder 2";
	case MagnetItemType::Ladder_3:
		return "Ladder 3";
	case MagnetItemType::LadderPlaced:
		return "LadderPlaced";
	case MagnetItemType::SilverCoin:
		return "SilverCoin";
	case MagnetItemType::GoldCoin:
		return "GoldCoin";
	case MagnetItemType::Diamond:
		return "Diamond";
	case MagnetItemType::Pickaxe:
		return "Pickaxe";
	default:
		return "InValid_Value_Of_MagnetItemType";
	}
}
