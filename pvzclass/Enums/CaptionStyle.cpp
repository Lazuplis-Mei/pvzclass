#include "CaptionStyle.h"

const char* CaptionStyle::ToString(CaptionStyle captions)
{
	switch (captions)
	{
	case CaptionStyle::Lowermiddle:
		return "Lowermiddle";
	case CaptionStyle::Lowerpart:
		return "Lowerpart";
	case CaptionStyle::Bottom:
		return "Bottom";
	case CaptionStyle::Center:
		return "Center";
	case CaptionStyle::BottomWhite:
		return "BottomWhite";
	case CaptionStyle::CenterRed:
		return "CenterRed";
	case CaptionStyle::TopYellow:
		return "TopYellow";
	default:
		return "InValid_Value_Of_CaptionStyle";
	}
}
