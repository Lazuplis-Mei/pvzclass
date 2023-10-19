#pragma once
namespace SeedState
{

	enum SeedState
	{
		FlyingToBank,
		InBank,
		FlyingToChooser,
		InChooser,
		Hidden
	};

	extern const char* ToString(SeedState seedstate);

}