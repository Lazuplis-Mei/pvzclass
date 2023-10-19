#include "../PVZ.h"

SPT<PVZ::Board> PVZ::SeedChooserScreen::GetBoard()
{
	return(MKS<PVZ::Board>(Memory::ReadMemory<int>(BaseAddress + 0x0D14)));
}

SPT<PVZ::SeedChooserScreen::ChosenSeed> PVZ::SeedChooserScreen::GetChosenSeed(int num)
{
	return(MKS<PVZ::SeedChooserScreen::ChosenSeed>(BaseAddress + 0xA4 + num * 0x3C));
}
