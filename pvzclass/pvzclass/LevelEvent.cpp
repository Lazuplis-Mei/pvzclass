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
		InvokeEvent(FunctionLevelOpenEvent, );
	}
	//std::cerr << address << "!" << pvz->BaseAddress << std::endl;
	if (Address != NULL && pvz->BaseAddress == NULL)
	{
		Address = NULL;
		IsStarted = 0;
		InvokeEvent(FunctionLevelCloseEvent, );
	}
	if (Address)
	{
		//std::cerr << pvz->WaveCount << "\n";
		//pvz->GetWave 
		if (!IsStarted && pvz->GameState == 3)
		{
			IsStarted = 1;
			InvokeEvent(FunctionLevelStartEvent, );
		}

		if (wave != pvz->RefreshedWave)
		{
			wave = pvz->RefreshedWave;
			InvokeEvent(FunctionLevelWaveEvent, wave);
		}
	}
}
void EventHandler::RegisterLevelOpenEvent(void function())
{
	FunctionLevelOpenEvent.push_back(function);
}

void EventHandler::RegisterLevelCloseEvent(void function())
{
	FunctionLevelCloseEvent.push_back(function);
}

void EventHandler::RegisterLevelWaveEvent(void function(int))
{
	FunctionLevelWaveEvent.push_back(function);
}

void EventHandler::RegisterLevelStartEvent(void function())
{
	FunctionLevelStartEvent.push_back(function);
}
