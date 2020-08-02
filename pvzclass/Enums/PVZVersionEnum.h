#pragma once
namespace PVZVersion
{

	enum PVZVersion
	{
		V1_0_0_1051,
		V1_2_0_1065,
		V1_2_0_1073,
		CHINESE_ENHANCED,
		CHINESE_VISCOSITY,
		UnknowOrNotPVZ,
	};

	extern const char* ToString(PVZVersion pvzver);

}