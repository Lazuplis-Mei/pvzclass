#pragma once
#include "PVZ.h"
#include <vector>
#include <queue>
/*testing*/
class EventHandler
{
private:
	PVZ* pvz;
	typedef PVZ::Plant Plant;
	std::vector<Plant> getAllPlants();
	bool equals(Plant a, Plant b);
	typedef std::vector<void (*)(Plant)> vecplant;
	/*Starts the events.*/
	vecplant functionPlantPlantEvent;
	vecplant functionPlantRemoveEvent;
	vecplant functionPlantUpgradeEvent;
	void invokePlantPlantEvent(Plant);
	void invokePlantRemoveEvent(Plant);
	void invokePlantUpgradeEvent(Plant);
	/*end of the events.*/
	void update();
	
public:
	EventHandler(PVZ* pvz);
	~EventHandler();
	void run();
	/*Starts the events.*/
	void registerPlantPlantEvent(void function(Plant));
	//Warning : You should never access any API of the Plant
	void registerPlantRemoveEvent(void function(Plant));
	void registerPlantUpgradeEvent(void function(Plant));
	/*end of the events.*/
};
