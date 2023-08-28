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
		Doesnt_Cause_Flash = 8,
		Doesnt_Leave_Body = 16,
		Direct_AntiVehicle = 32,
		Side_AntiVehicle,
		Sputter_AntiVehicle,
		Direct_Ice_AntiVehicle = 36,
		Side_Ice_AntiVehicle,
		Sputter_Ice_AntiVehicle,
	};

	extern const char* ToString(DamageType damaget);

}