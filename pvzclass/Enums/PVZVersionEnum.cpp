#include "PVZVersionEnum.h"

const char* PVZVersion::ToString(PVZVersion pvzver)
{
	switch (pvzver)
	{
	case PVZVersion::V1_0_0_1051:
		return "V1_0_0_1051";
	case PVZVersion::V1_2_0_1065:
		return "V1_2_0_1065";
	case PVZVersion::V1_2_0_1073:
		return "V1_2_0_1073";
	case PVZVersion::CHINESE_ENHANCED:
		return "中文年度加强版";
	case PVZVersion::CHINESE_VISCOSITY:
		return "粘度汗化版";
	case PVZVersion::UnknowOrNotPVZ:
		return "UnknowOrNotPVZ";
	default:
		return "InValid_Value_Of_PVZVersion";
	}
}
