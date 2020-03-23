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
	typedef PVZ::Zombie Zombie;
	std::vector<Plant*> getAllPlants();
	std::vector<Zombie*> getAllZombies();
	bool equals(Plant* a, Plant* b);
	typedef std::vector<void (*)(Plant*)> vecplant;
	typedef std::vector<void (*)()> vecvoid;
	typedef std::vector<void (*)(int)> vecint;
	typedef std::vector<void (*)(Zombie*)> veczombie;
	std::vector<Plant*> list;
	std::vector<Zombie*> zombielist;
	int address;
	/*Starts the events.*/
	vecplant	functionPlantPlantEvent;
	vecplant	functionPlantRemoveEvent;
	vecplant	functionPlantUpgradeEvent;
	vecvoid		functionLevelOpenEvent;
	vecvoid		functionLevelCloseEvent;
	vecint		functionLevelWaveEvent;
	veczombie	functionZombieSpawnEvent;
	veczombie	functionZombieRemoveEvent;
	void		invokePlantPlantEvent(Plant*);
	void		invokePlantRemoveEvent(Plant*);
	void		invokePlantUpgradeEvent(Plant*);
	void		invokeLevelOpenEvent();
	void		invokeLevelCloseEvent();
	void		invokeLevelWaveEvent(int);
	void		invokeZombieSpawnEvent(Zombie*);
	void		invokeZombieRemoveEvent(Zombie*);
	/*end of the events.*/
	void update()
	{
		updateLevels();
		//For some reason, we should first invoke
		updatePlants();
		updateZombies();
	}
	void updatePlants();
	void updateLevels();
	void updateZombies();
	
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
	void	registerZombieSpawnEvent(void function(Zombie*));
	void	registerZombieRemoveEvent(void function(Zombie*));
	/*end of the events.*/
};
