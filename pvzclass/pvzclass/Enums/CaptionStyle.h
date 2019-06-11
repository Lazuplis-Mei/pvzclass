#pragma once
namespace CaptionStyle
{

	enum CaptionStyle
	{
		Lowermiddle = 1,
		Lowerpart = 3,
		Bottom = 6,
		Center = 12,
		BottomWhite = 14,
		CenterRed,
		TopYellow,
	};

	extern const char* ToString(CaptionStyle captions);

}