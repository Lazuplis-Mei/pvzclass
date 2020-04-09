#include "events.h"
#include <iostream>

int wave;
void EventHandler::InvokeLevelOpenEvent()
{
	int lim = FunctionLevelOpenEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionLevelOpenEventHigh[i]())
			return;
	lim = FunctionLevelOpenEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionLevelOpenEventMid[i]())
			return;
	lim = FunctionLevelOpenEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionLevelOpenEventLow[i]())
			return;
}
void EventHandler::InvokeLevelCloseEvent()
{
	int lim = FunctionLevelCloseEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionLevelCloseEventHigh[i]())
			return; 
	lim = FunctionLevelOpenEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionLevelCloseEventMid[i]())
			return;
	lim = FunctionLevelCloseEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionLevelCloseEventLow[i]())
			return;
}
void EventHandler::InvokeLevelWaveEvent(int wave)
{
	int lim = FunctionLevelWaveEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionLevelWaveEventHigh[i](wave))
			return;
	lim = FunctionLevelWaveEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionLevelWaveEventMid[i](wave))
			return;
	lim = FunctionLevelWaveEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionLevelWaveEventLow[i](wave))
			return;
}
void EventHandler::InvokeLevelStartEvent()
{
	int lim = FunctionLevelStartEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionLevelStartEventHigh[i]())
			return;
	lim = FunctionLevelStartEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionLevelStartEventMid[i]())
			return;
	lim = FunctionLevelStartEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionLevelStartEventLow[i]())
			return;
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
		IsStarted = 0;
		InvokeLevelCloseEvent();
	}
	if (Address)
	{
		//std::cerr << pvz->WaveCount << "\n";
		//pvz->GetWave 
		if (!IsStarted && pvz->GameState == 3)
		{
			IsStarted = 1;
			InvokeLevelStartEvent();
		}

		if (wave != pvz->RefreshedWave)
		{
			wave = pvz->RefreshedWave;
			InvokeLevelWaveEvent(wave);
		}
	}
}
void EventHandler::RegisterLevelOpenEvent(bool function(), int level)
{
	if (level == Event_Low)
		FunctionLevelOpenEventLow.push_back(function);
	else if (level == Event_Mid)
		FunctionLevelOpenEventMid.push_back(function);
	else if (level == Event_High)
		FunctionLevelOpenEventHigh.push_back(function);
}

void EventHandler::RegisterLevelCloseEvent(bool function(), int level)
{
	if (level == Event_Low)
		FunctionLevelCloseEventLow.push_back(function);
	else if (level == Event_Mid)
		FunctionLevelCloseEventMid.push_back(function);
	else if (level == Event_High)
		FunctionLevelCloseEventHigh.push_back(function);
}

void EventHandler::RegisterLevelWaveEvent(bool function(int), int level)
{
	if (level == Event_Low)
		FunctionLevelWaveEventLow.push_back(function);
	else if (level == Event_Mid)
		FunctionLevelWaveEventMid.push_back(function);
	else if (level == Event_High)
		FunctionLevelWaveEventHigh.push_back(function);
}

void EventHandler::RegisterLevelStartEvent(bool function(), int level)
{
	if (level == Event_Low)
		FunctionLevelStartEventLow.push_back(function);
	else if (level == Event_Mid)
		FunctionLevelStartEventMid.push_back(function);
	else if (level == Event_High)
		FunctionLevelStartEventHigh.push_back(function);
}
