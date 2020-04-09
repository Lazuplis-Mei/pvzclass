#include "VaseSkin.h"

const char* VaseSkin::ToString(VaseSkin vases)
{
	switch (vases)
	{
	case VaseSkin::VaseSkinUnknow:
		return "VaseSkinUnknow";
	case VaseSkin::VaseSkinLeaf:
		return "VaseSkinLeaf";
	case VaseSkin::VaseSkinZombie:
		return "VaseSkinZombie";
	default:
		return "InValid_Value_Of_VaseSkin";
	}
}
