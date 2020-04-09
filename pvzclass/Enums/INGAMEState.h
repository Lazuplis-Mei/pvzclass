#pragma once
namespace INGAMEState
{

	enum INGAMEState
	{
		None,
		Starting,
		Finished,
		Disappearing,
	};

	extern const char* ToString(INGAMEState ingames);

}