#pragma once
namespace DamageType
{

	enum DamageType
	{
		Direct,
		Side,
		Sputter,
		Direct_Ice = 4,
		Side_Ice,
		Sputter_Ice,
	};

	extern const char* ToString(DamageType damaget);

}