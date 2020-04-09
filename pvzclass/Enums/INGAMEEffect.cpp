#include "INGAMEEffect.h"

const char* INGAMEEffect::ToString(INGAMEEffect ingamee)
{
	switch (ingamee)
	{
	case INGAMEEffect::None:
		return "INGAMEEffectNone";
	case INGAMEEffect::FadeIn:
		return "FadeIn";
	case INGAMEEffect::Completed:
		return "Completed";
	case INGAMEEffect::FadeOut:
		return "FadeOut";
	case INGAMEEffect::Disappeared:
		return "Disappeared";
	default:
		return "InValid_Value_Of_INGAMEEffect";
	}
}
