#pragma once
namespace GriditemType
{

	enum GriditemType
	{
		Grave = 1,
		Crater,
		GriditemLadder,
		PortalBlue,
		PortalYellow,
		AquariumBrain = 6,
		Vase,
		Snail = 10,
		Rake = 11,
		IZBrain = 12,
	};

	extern const char* ToString(GriditemType griditemt);

}
