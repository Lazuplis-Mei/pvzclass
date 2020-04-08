#include "MotionType.h"

const char* MotionType::ToString(MotionType motiont)
{
	switch (motiont)
	{
	case MotionType::Direct:
		return "Direct";
	case MotionType::Throw:
		return "Throw";
	case MotionType::Slide:
		return "Slide";
	case MotionType::Left:
		return "Left";
	case MotionType::LeftSlide:
		return "LeftSlide";
	case MotionType::Float:
		return "Float";
	case MotionType::Slow:
		return "Slow";
	case MotionType::Track:
		return "Track";
	default:
		return "InValid_Value_Of_MotionType";
	}
}
