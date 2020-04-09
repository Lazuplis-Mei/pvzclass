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
		Brain = 6,
		Vase,
		Snail = 10,
		Rake = 11,
	};

	extern const char* ToString(GriditemType griditemt);

}