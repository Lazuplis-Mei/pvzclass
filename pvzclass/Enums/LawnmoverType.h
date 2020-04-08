#pragma once
namespace LawnmoverType
{

	enum LawnmoverType
	{
		LawnCleaner,
		PoolCleaner,
		RoofCleaner,
		Trickedout,
	};

	extern const char* ToString(LawnmoverType lawnmovert);

}