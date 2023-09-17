#pragma once
namespace GriditemState
{

	enum GriditemState
	{
		Normal,
		CraterSpecial,
		PortalClosed,
		VaseSkinUnknow,
		VaseSkinLeaf,
		VaseSkinZombie,
		SquirrelWaiting,
		SquirrelPeeking,
		SquirrelRunningUp,
		SquirrelRunningDown,
		SquirrelRunningLeft,
		SquirrelRunningRight,
		SquirrelCaught,
		SquirrelZombie,
		ZenToolWateringCan,
		ZenToolFertilizer,
		ZenToolBugSpray,
		ZenToolPhonograph,
		ZenToolGoldWateringCan,
		SnailWalkingLeft,
		SnailTurningLeft,
		SnailWalkingRight,
		SnailTurningRight,
		SnailSleeping,
		SnailFallingAsleep,
		SnailWakingUp,
		RakeAttracting,
		RakeWaiting,
		RakeTriggered,
		IZBrainSquished,
	};

	extern const char* ToString(GriditemState griditemState);

}
