#include "ChallengePage.hpp"

const char* ChallengePage::ToString(ChallengePage page)
{
	switch (page)
	{
	case ChallengePage::SURVIVAL:
		return "Survival";
	case ChallengePage::CHALLENGE:
		return "Challenge";
	case ChallengePage::LIMBO:
		return "Limbo";
	case ChallengePage::PUZZLE:
		return "Puzzle";
	default:
		return "InValid_Value_Of_ChallengePage";
	}
}
