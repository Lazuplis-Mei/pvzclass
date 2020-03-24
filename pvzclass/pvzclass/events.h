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
	std::vector<Plant*> GetAllPlants();
	std::vector<Zombie*> GetAllZombies();
	bool Equals(Plant* a, Plant* b);
	typedef std::vector<void (*)(Plant*)> vecplant;
	typedef std::vector<void (*)()> vecvoid;
	typedef std::vector<void (*)(int)> vecint;
	typedef std::vector<void (*)(Zombie*)> veczombie;
	std::vector<Plant*> List;
	std::vector<Zombie*> ZombieList;
	int Address;
	bool Started;
	/*Starts the events.*/
	vecplant	FunctionPlantPlantEvent;
	vecplant	FunctionPlantRemoveEvent;
	vecplant	FunctionPlantUpgradeEvent;
	vecvoid		FunctionLevelOpenEvent;
	vecvoid		FunctionLevelCloseEvent;
	vecint		FunctionLevelWaveEvent;
	veczombie	FunctionZombieSpawnEvent;
	veczombie	FunctionZombieRemoveEvent;
	void		InvokePlantPlantEvent(Plant*);
	void		InvokePlantRemoveEvent(Plant*);
	void		InvokePlantUpgradeEvent(Plant*);
	void		InvokeLevelOpenEvent();
	void		InvokeLevelCloseEvent();
	void		InvokeLevelWaveEvent(int);
	void		InvokeZombieSpawnEvent(Zombie*);
	void		InvokeZombieRemoveEvent(Zombie*);
	/*end of the events.*/
	void Update()
	{
		UpdateLevels();
		//For some reason, we should first invoke
		UpdatePlants();
		UpdateZombies();
	}
	void UpdatePlants();
	void UpdateLevels();
	void UpdateZombies();
	
public:
	EventHandler(PVZ* pvz)
	{
		this->pvz = pvz;
		Address = 0;
		Started = 0;
	}
	~EventHandler()
	{

	}
	void Run()
	{
		Update();
	}
	/*Starts the events.*/
	/*You should never access ANY api in Remove event.*/
	void	RegisterPlantPlantEvent(void function(Plant*));
	void	RegisterPlantRemoveEvent(void function(Plant*));
	void	RegisterPlantUpgradeEvent(void function(Plant*));
	void	RegisterLevelOpenEvent(void function());
	void	RegisterLevelCloseEvent(void function());
	void	RegisterLevelWaveEvent(void function(int));
	void	RegisterZombieSpawnEvent(void function(Zombie*));
	void	RegisterZombieRemoveEvent(void function(Zombie*));
	/*end of the events.*/
};
