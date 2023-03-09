#pragma once
namespace CaptionStyle
{

	enum CaptionStyle
	{
		Lowermiddle = 1,
		LowermiddleStay,
		Lowerpart,
		Later,
		LaterStay,
		Bottom,
		BottomFast,
		Stay,
		TallFast,
		Tall10Sec,
		Tall8Sec,
		Center,
		CenterFast,
		BottomWhite,
		CenterRed,
		TopYellow,
		ZenGarden,
	};

	extern const char* ToString(CaptionStyle captions);

}