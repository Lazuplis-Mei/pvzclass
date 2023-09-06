#include "GriditemState.h"

const char* GriditemState::ToString(GriditemState griditemState)
{
	switch (griditemState)
	{
	case GriditemState::Normal:
		return "Normal";
	case GriditemState::CraterSpecial:
		return "CraterSpecial";
	case GriditemState::PortalClosed:
		return "PortalClosed";
	case GriditemState::VaseSkinUnknow:
		return "VaseSkinUnknow";
	case GriditemState::VaseSkinLeaf:
		return "VaseSkinLeaf";
	case GriditemState::VaseSkinZombie:
		return "VaseSkinZombie";
	case GriditemState::SquirrelWaiting:
		return "SquirrelWaiting";
	case GriditemState::SquirrelPeeking:
		return "SquirrelPeeking";
	case GriditemState::SquirrelRunningUp:
		return "SquirrelRunningUp";
	case GriditemState::SquirrelRunningDown:
		return "SquirrelRunningDown";
	case GriditemState::SquirrelRunningLeft:
		return "SquirrelRunningLeft";
	case GriditemState::SquirrelRunningRight:
		return "SquirrelRunningRight";
	case GriditemState::SquirrelCaught:
		return "SquirrelCaught";
	case GriditemState::SquirrelZombie:
		return "SquirrelZombie";
	case GriditemState::ZenToolWateringCan:
		return "ZenToolWateringCan";
	case GriditemState::ZenToolFertilizer:
		return "ZenToolFertilizer";
	case GriditemState::ZenToolBugSpray:
		return "ZenToolBugSpray";
	case GriditemState::ZenToolPhonograph:
		return "ZenToolPhonograph";
	case GriditemState::ZenToolGoldWateringCan:
		return "ZenToolGoldWateringCan";
	case GriditemState::SnailWalkingLeft:
		return "SnailWalkingLeft";
	case GriditemState::SnailTurningLeft:
		return "SnailTurningLeft";
	case GriditemState::SnailWalkingRight:
		return "SnailWalkingRight";
	case GriditemState::SnailTurningRight:
		return "SnailTurningRight";
	case GriditemState::SnailSleeping:
		return "SnailSleeping";
	case GriditemState::SnailFallingAsleep:
		return "SnailFallingAsleep";
	case GriditemState::SnailWakingUp:
		return "SnailWakingUp";
	case GriditemState::RakeAttracting:
		return "RakeAttracting";
	case GriditemState::RakeWaiting:
		return "RakeWaiting";
	case GriditemState::RakeTriggered:
		return "RakeTriggered";
	case GriditemState::IZBrainSquished:
		return "IZBrainSquished";
	default:
		return "InValid_Value_Of_GriditemState";
	}
}
