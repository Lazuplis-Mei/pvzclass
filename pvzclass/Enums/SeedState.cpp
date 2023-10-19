#include "SeedState.h"

const char* SeedState::ToString(SeedState scenet)
{
	switch (scenet)
	{
	case SeedState::FlyingToBank:
		return "FlyingToBank";
	case SeedState::InBank:
		return "InBank";
	case SeedState::FlyingToChooser:
		return "FlyingToChooser";
	case SeedState::InChooser:
		return "InChooser";
	case SeedState::Hidden:
		return "Hidden";
	default:
		return "InValid_Value_Of_SeedState";
	}
}