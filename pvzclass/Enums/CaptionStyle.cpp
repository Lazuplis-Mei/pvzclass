#include "CaptionStyle.h"

const char* CaptionStyle::ToString(CaptionStyle captions)
{
	switch (captions)
	{
	case CaptionStyle::Lowermiddle:
		return "Lowermiddle";
	case CaptionStyle::LowermiddleStay:
		return "LowermiddleStay";
	case CaptionStyle::Lowerpart:
		return "Lowerpart";
	case CaptionStyle::Later:
		return "Later";
	case CaptionStyle::LaterStay:
		return "LaterStay";
	case CaptionStyle::Bottom:
		return "Bottom";
	case CaptionStyle::BottomFast:
		return "BottomFast";
	case CaptionStyle::Stay:
		return "Stay";
	case CaptionStyle::TallFast:
		return "TallFast";
	case CaptionStyle::Tall10Sec:
		return "Tall10Sec";
	case CaptionStyle::Tall8Sec:
		return "Tall8Sec";
	case CaptionStyle::Center:
		return "Center";
	case CaptionStyle::CenterFast:
		return "CenterFast";
	case CaptionStyle::BottomWhite:
		return "BottomWhite";
	case CaptionStyle::CenterRed:
		return "CenterRed";
	case CaptionStyle::TopYellow:
		return "TopYellow";
	case CaptionStyle::ZenGarden:
		return "ZenGarden";
	default:
		return "InValid_Value_Of_CaptionStyle";
	}
}
