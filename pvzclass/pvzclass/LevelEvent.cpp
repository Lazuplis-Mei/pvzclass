#include "events.h"
#include <iostream>

int wave;
void EventHandler::invokeLevelOpenEvent()
{
	int lim = functionLevelOpenEvent.size();
	for (int i = 0; i < lim; i++)
		functionLevelOpenEvent[i]();
}
void EventHandler::invokeLevelCloseEvent()
{
	int lim = functionLevelCloseEvent.size();
	for (int i = 0; i < lim; i++)
		functionLevelCloseEvent[i]();
}
void EventHandler::invokeLevelWaveEvent(int wave)
{
	int lim = functionLevelWaveEvent.size();
	for (int i = 0; i < lim; i++)
		functionLevelWaveEvent[i](wave);
}
void EventHandler::updateLevels()
{
	//std::cerr << address << " " << pvz->BaseAddress << std::endl;
	if (address == NULL && pvz->BaseAddress != NULL)
	{
		address = pvz->BaseAddress;
		wave = pvz->WaveCount;
		invokeLevelOpenEvent();
	}
	//std::cerr << address << "!" << pvz->BaseAddress << std::endl;
	if (address != NULL && pvz->BaseAddress == NULL)
	{
		address = NULL;
		invokeLevelCloseEvent();
	}
	if (address)
	{
		//std::cerr << pvz->WaveCount << "\n";
		//pvz->GetWave 
		if (wave != pvz->RefreshedWave)
		{
			wave = pvz->RefreshedWave;
			invokeLevelWaveEvent(wave);
		}
	}
}
void EventHandler::registerLevelOpenEvent(void function())
{
	functionLevelOpenEvent.push_back(function);
}

void EventHandler::registerLevelCloseEvent(void function())
{
	functionLevelCloseEvent.push_back(function);
}

void EventHandler::registerLevelWaveEvent(void function(int))
{
	functionLevelWaveEvent.push_back(function);
}
