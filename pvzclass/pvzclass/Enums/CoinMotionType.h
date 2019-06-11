#pragma once
namespace CoinMotionType
{

	enum CoinMotionType
	{
		Fastfall,
		Slowfall,
		Product,
		Spray,
		Collected,
		DelayCollected,
	};

	extern const char* ToString(CoinMotionType coinmt);

}