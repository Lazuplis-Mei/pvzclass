#include "PVZGameStateEnum.h"

const char* PVZGameState::ToString(PVZGameState pvzgs)
{
	switch (pvzgs)
	{
	case PVZGameState::Loading:
		return "Loading";
	case PVZGameState::MainMenu:
		return "MainMenu";
	case PVZGameState::Preparing:
		return "Preparing";
	case PVZGameState::Playing:
		return "Playing";
	case PVZGameState::Losing:
		return "Losing";
	case PVZGameState::Won:
		return "Won";
	case PVZGameState::MVPlaying:
		return "MVPlaying";
	case PVZGameState::SelectingLevel:
		return "SelectingLevel";
	default:
		return "InValid_Value_Of_PVZGameState";
	}
}

