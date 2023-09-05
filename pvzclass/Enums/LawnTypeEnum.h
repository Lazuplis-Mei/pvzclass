#pragma once
namespace LawnType
{

	enum LawnType
	{
		None = -1,
		Nothing,
		Grass,
		Unsodded,
		Water,
	};

	extern const char* ToString(LawnType lawnt);
}