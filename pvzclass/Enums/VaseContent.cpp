#include "VaseContent.h"

const char* VaseContent::ToString(VaseContent vasec)
{
	switch (vasec)
	{
	case VaseContent::None:
		return "aseContentNone";
	case VaseContent::Plant:
		return "Plant";
	case VaseContent::Zombie:
		return "Zombie";
	case VaseContent::Sun:
		return "Sun";
	default:
		return "InValid_Value_Of_VaseContent";
	}
}
