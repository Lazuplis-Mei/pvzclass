#include "events.h"
#include <iostream>

int wave;
void EventHandler::InvokeLevelOpenEvent()
{
	int lim = FunctionLevelOpenEvent.size();
	for (int i = 0; i < lim; i++)
		FunctionLevelOpenEvent[i]();
}
void EventHandler::InvokeLevelCloseEvent()
{
	int lim = FunctionLevelCloseEvent.size();
	for (int i = 0; i < lim; i++)
		FunctionLevelCloseEvent[i]();
}
void EventHandler::InvokeLevelWaveEvent(int wave)
{
	int lim = FunctionLevelWaveEvent.size();
	for (int i = 0; i < lim; i++)
		FunctionLevelWaveEvent[i](wave);
}
void EventHandler::UpdateLevels()
{
	//std::cerr << address << " " << pvz->BaseAddress << std::endl;
	if (Address == NULL && pvz->BaseAddress != NULL)
	{
		Address = pvz->BaseAddress;
		wave = pvz->WaveCount;
		InvokeLevelOpenEvent();
	}
	//std::cerr << address << "!" << pvz->BaseAddress << std::endl;
	if (Address != NULL && pvz->BaseAddress == NULL)
	{
		Address = NULL;
		InvokeLevelCloseEvent();
	}
	if (Address)
	{
		//std::cerr << pvz->WaveCount << "\n";
		//pvz->GetWave 
		if (wave != pvz->RefreshedWave)
		{
			wave = pvz->RefreshedWave;
			InvokeLevelWaveEvent(wave);
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
