#pragma once
#include "../PVZ.h"

namespace PVZ
{
	//选关界面。
	class ChallengeScreen : public Widget
	{
	public:
		ChallengeScreen(int address) : Widget(address) {};
		SPT<PVZApp> GetPVZApp();
		PROPERTY(ChallengePage::ChallengePage, __get_Page, __set_Page) Page;
	};
	SPT<ChallengeScreen> GetChallengeScreen();
}