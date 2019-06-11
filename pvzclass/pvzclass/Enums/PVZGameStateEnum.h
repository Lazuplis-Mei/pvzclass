#pragma once
namespace PVZGameState
{

	enum PVZGameState
	{
		Loading,
		MainMenu,
		Preparing,
		Playing,
		Losing,
		Won,
		MVPlaying,
		SelectingLevel,
	};

	extern const char* ToString(PVZGameState pvzgs);

}