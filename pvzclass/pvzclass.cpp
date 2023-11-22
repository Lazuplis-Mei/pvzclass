#include "pvzclass.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ::InitPVZ(pid);

	EnableBackgroundRunning();
	auto app = PVZ::GetPVZApp();
	while (app->GameState != PVZGameState::Playing) Sleep(10);

	while (true)
	{
		PVZ::Memory::immediateExecute = true;
		PVZ::Memory::WaitPVZ();
		for (int row = 0; row < 5; row++)
		{
			for (int col = 1; col < 9; col++)
			{
				Creator::CreateZombie(ZombieType::Zombie, row, col);
			}
		}
		PVZ::Memory::ResumePVZ();
		system("pause");
	}

	PVZ::QuitPVZ();
	return 0;
}
