#pragma once
#include "PVZ.h"
#include <vector>
#include <queue>

typedef PVZ::Plant Plant;
typedef PVZ::Zombie Zombie;
typedef PVZ::Projectile Projectile;
typedef std::vector<bool (*)(Plant*)> vecplant;
typedef std::vector<bool (*)()> vecvoid;
typedef std::vector<bool (*)(int)> vecint;
typedef std::vector<bool (*)(Zombie*)> veczombie;
typedef std::vector<bool (*)(Projectile*)> vecproj;

#define Event_Low 1
#define Event_Mid 2
#define Event_High 3

/*
**testing**
The EventHandler API
*/

class EventHandler
{
private:
	PVZ* pvz;
	std::vector<Plant*> GetAllPlants();
	std::vector<Zombie*> GetAllZombies();
	std::vector<Projectile*> GetAllProjectiles();//wait for Projectile event
	std::vector<Plant*> PlantList;
	std::vector<Zombie*> ZombieList;
	std::vector<Projectile*> ProjectileList;//wait for projectile event
	int Address;
	bool Started;
	bool IsStarted;
	/*Starts the events.*/
	vecplant    FunctionPlantPlantEventLow;
	vecplant    FunctionPlantRemoveEventLow;
	vecplant    FunctionPlantUpgradeEventLow;
	vecvoid     FunctionLevelOpenEventLow;
	vecvoid     FunctionLevelCloseEventLow;
	vecint      FunctionLevelWaveEventLow;
	vecvoid	    FunctionLevelStartEventLow;
	veczombie   FunctionZombieSpawnEventLow;
	veczombie   FunctionZombieRemoveEventLow;
	veczombie   FunctionZombieDeadEventLow;
	veczombie	FunctionZombieHypnotizedEventLow;
	vecproj     FunctionProjectileFireEventLow;
	vecproj     FunctionProjectileRemoveEventLow;

	vecplant    FunctionPlantPlantEventMid;
	vecplant    FunctionPlantRemoveEventMid;
	vecplant    FunctionPlantUpgradeEventMid;
	vecvoid     FunctionLevelOpenEventMid;
	vecvoid     FunctionLevelCloseEventMid;
	vecint      FunctionLevelWaveEventMid;
	vecvoid	    FunctionLevelStartEventMid;
	veczombie   FunctionZombieSpawnEventMid;
	veczombie   FunctionZombieRemoveEventMid;
	veczombie   FunctionZombieDeadEventMid;
	veczombie	FunctionZombieHypnotizedEventMid;
	vecproj     FunctionProjectileFireEventMid;
	vecproj     FunctionProjectileRemoveEventMid;

	vecplant    FunctionPlantPlantEventHigh;
	vecplant    FunctionPlantRemoveEventHigh;
	vecplant    FunctionPlantUpgradeEventHigh;
	vecvoid     FunctionLevelOpenEventHigh;
	vecvoid     FunctionLevelCloseEventHigh;
	vecint      FunctionLevelWaveEventHigh;
	vecvoid	    FunctionLevelStartEventHigh;
	veczombie   FunctionZombieSpawnEventHigh;
	veczombie   FunctionZombieRemoveEventHigh;
	veczombie   FunctionZombieDeadEventHigh;
	veczombie	FunctionZombieHypnotizedEventHigh;
	vecproj     FunctionProjectileFireEventHigh;
	vecproj     FunctionProjectileRemoveEventHigh;
	void        InvokePlantPlantEvent(Plant*);
	void        InvokePlantRemoveEvent(Plant*);
	void        InvokePlantUpgradeEvent(Plant*);
	void        InvokeLevelOpenEvent();
	void        InvokeLevelCloseEvent();
	void        InvokeLevelWaveEvent(int);
	void        InvokeLevelStartEvent();
	void        InvokeZombieSpawnEvent(Zombie*);
	void        InvokeZombieRemoveEvent(Zombie*);
	void	    InvokeZombieDeadEvent(Zombie*);
	void		InvokeZombieHypnotizedEvent(Zombie*);
	void        InvokeProjectileFireEvent(Projectile*);
	void        InvokeProjectileRemoveEvent(Projectile*);
	/*end of the events.*/
	void Update()
	{
		UpdateLevels();
		//For some reason, we should first invoke
		UpdatePlants();
		UpdateZombies();
		UpdateProjectiles();
	}
	void UpdatePlants();
	void UpdateLevels();
	void UpdateZombies();
	void UpdateProjectiles();
	
public:
	EventHandler(PVZ* pvz)
	{
		this->pvz = pvz;
		Address = 0;
		Started = 0;
		IsStarted = 0;
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
	void	RegisterPlantPlantEvent(bool function(Plant*), int level);
	void	RegisterPlantRemoveEvent(bool function(Plant*), int level);
	void	RegisterPlantUpgradeEvent(bool function(Plant*), int level);
	void	RegisterLevelOpenEvent(bool function(), int level);
	void	RegisterLevelCloseEvent(bool function(), int level);
	void	RegisterLevelWaveEvent(bool function(int), int level);
	void    RegisterLevelStartEvent(bool function(), int level);
	void	RegisterZombieSpawnEvent(bool function(Zombie*), int level);
	void	RegisterZombieDeadEvent(bool function(Zombie*), int level);
	void	RegisterZombieHypnotizedEvent(bool function(Zombie*), int level);
	void	RegisterZombieRemoveEvent(bool function(Zombie*), int level);
	void    RegisterProjectileFireEvent(bool function(Projectile*), int level);
	void    RegisterProjectileRemoveEvent(bool function(Projectile*), int level);
	/*end of the events.*/
};
