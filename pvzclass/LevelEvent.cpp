#include "events.h"
#include <iostream>

int wave;

void EventHandler::UpdateLevels()
{
	//std::cerr << address << " " << pvz->BaseAddress << std::endl;
	if (Address == NULL && pvz->BaseAddress != NULL)
	{
		Address = pvz->BaseAddress;
		wave = pvz->WaveCount;
		InvokeEvent(new EventLevelOpen(),true);
		PlantList = GetAllPlants();
		ZombieList = GetAllZombies();
		ProjectileList = GetAllProjectiles();
	}
	//std::cerr << address << "!" << pvz->BaseAddress << std::endl;
	if (Address != NULL && pvz->BaseAddress == NULL)
	{
		Address = NULL;
		IsStarted = 0;
		InvokeEvent(new EventLevelClose(),true);
	}
	if (Address)
	{
		//std::cerr << pvz->WaveCount << "\n";
		//pvz->GetWave 
		if (!IsStarted && pvz->GameState == PVZGameState::Preparing)
		{
			IsStarted = 1;
			InvokeEvent(new EventLevelStart(),true);
		}

		if (wave != pvz->RefreshedWave && IsStarted)
		{
			wave = pvz->RefreshedWave;
			InvokeEvent(new EventLevelWave(wave),true);
		}
	}
}
