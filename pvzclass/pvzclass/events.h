#pragma once
#include "PVZ.h"
#include <vector>
#include <queue>
/*
**testing**
The EventHandler API
*/
class EventHandler
{
private:
	PVZ* pvz;
	typedef PVZ::Plant Plant;
	std::vector<Plant*> getAllPlants();
	bool equals(Plant* a, Plant* b);
	typedef std::vector<void (*)(Plant*)> vecplant;
	typedef std::vector<void (*)()> vecvoid;
	typedef std::vector<void (*)(int)> vecint;
	std::vector<Plant*> list;
	int address;
	/*Starts the events.*/
	vecplant	functionPlantPlantEvent;
	vecplant	functionPlantRemoveEvent;
	vecplant	functionPlantUpgradeEvent;
	vecvoid		functionLevelOpenEvent;
	vecvoid		functionLevelCloseEvent;
	vecint		functionLevelWaveEvent;
	void		invokePlantPlantEvent(Plant*);
	void		invokePlantRemoveEvent(Plant*);
	void		invokePlantUpgradeEvent(Plant*);
	void		invokeLevelOpenEvent();
	void		invokeLevelCloseEvent();
	void		invokeLevelWaveEvent(int);
	/*end of the events.*/
	void update()
	{
		updateLevels();
		//For some reason, we should first invoke
		updatePlants();
	}
	void updatePlants();
	void updateLevels();
	
public:
	EventHandler(PVZ* pvz)
	{
		this->pvz = pvz;
		list = getAllPlants();
		address = pvz->BaseAddress;
	}
	~EventHandler()
	{

	}
	void run()
	{
		update();
	}
	/*Starts the events.*/
	/*You should never access ANY api in Remove event.*/
	void	registerPlantPlantEvent(void function(Plant*));
	void	registerPlantRemoveEvent(void function(Plant*));
	void	registerPlantUpgradeEvent(void function(Plant*));
	void	registerLevelOpenEvent(void function());
	void	registerLevelCloseEvent(void function());
	void	registerLevelWaveEvent(void function(int));
	/*end of the events.*/
};
