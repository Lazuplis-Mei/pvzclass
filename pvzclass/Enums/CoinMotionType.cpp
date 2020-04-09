#include "CoinMotionType.h"

const char* CoinMotionType::ToString(CoinMotionType coinmt)
{
	switch (coinmt)
	{
	case CoinMotionType::Fastfall:
		return "Fastfall";
	case CoinMotionType::Slowfall:
		return "Slowfall";
	case CoinMotionType::Product:
		return "Product";
	case CoinMotionType::Spray:
		return "Spray";
	case CoinMotionType::Collected:
		return "Collected";
	case CoinMotionType::DelayCollected:
		return "DelayCollected";
	default:
		return "InValid_Value_Of_CoinMotionType";
	}
}
