#pragma once
namespace LawnType
{

	enum LawnType
	{
		None = -1,
		Grass = 1,
		Unsodded,
		Water,
	};

	extern const char* ToString(LawnType lawnt);
}