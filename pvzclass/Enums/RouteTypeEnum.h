#pragma once
namespace RouteType
{

	enum RouteType
	{
		None = -1,
		NoZombie,
		Land,
		Pool,
	};

	extern const char* ToString(RouteType routet);

}