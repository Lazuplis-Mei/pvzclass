#pragma once
#include "PVZ.h"
#include <vector>
#include <queue>
#include <string>
#include <map>

class Event;
typedef PVZ::Plant Plant;
typedef PVZ::Zombie Zombie;
typedef PVZ::Projectile Projectile;
typedef std::vector<bool (*)(Plant*)> vecplant;
typedef std::vector<bool (*)()> vecvoid;
typedef std::vector<bool (*)(int)> vecint;
typedef std::vector<bool (*)(Zombie*)> veczombie;
typedef std::vector<bool (*)(Projectile*)> vecproj;
typedef void(*listener)(Event*);

#define Event_Low 1
#define Event_Mid 2
#define Event_High 3

/*
**testing**
The EventHandler API
*/
class Event
{
public:
	bool CancleState;
	std::string name;
};

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
	std::map<std::string, std::vector<listener> > listenersLow;
	std::map<std::string, std::vector<listener>> listenersMid;
	std::map<std::string, std::vector<listener>> listenersHigh;
	int Address;
	bool Started;
	bool IsStarted;
	void InvokeEvent(Event *event,bool isDelete=false);
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
	void RegistryListeners(std::string event,listener lis,int Level=Event_Low);
	/*end of the events.*/
};

class EventPlantPlant : public Event
{
public:
	Plant* plant;
	EventPlantPlant(Plant* p)
	{
		name="PlantPlant";
		plant=p;
	}
};

class EventPlantRemove : public Event
{
public:
	Plant* plant;
	EventPlantRemove(Plant* p) 
	{
		name="PlantRemove";
		plant=p;
	}
};

class EventPlantUpgrade : public Event
{
public:
	Plant* plant;
	EventPlantUpgrade(Plant* p)
	{
		name="PlantUpgrade";
		plant=p;
	}
};

class EventLevelOpen : public Event
{
public:
	EventLevelOpen()
	{
		name="LevelOpen";
	}
};

class EventLevelClose : public Event
{
public:
	EventLevelClose()
	{
		name="LevelClose";
	}
};

class EventLevelWave : public Event
{
public:
	int wave;
	EventLevelWave(int wave)
	{
		this->wave=wave;
		name="LevelWave";
	}
};

class EventLevelStart : public Event
{
public:
	EventLevelStart()
	{
		name="LevelStart";
	}
};

class EventProjectileFire : public Event
{
public:
	Projectile* projectile;
	EventProjectileFire(Projectile* projectile)
	{
		name="ProjectileFire";
		this->projectile = projectile;
	}
};

class EventProjectileRemove : public Event
{
public:
	Projectile* projectile;
	EventProjectileRemove(Projectile* projectile)
	{
		name="ProjectileRemove";
		this->projectile = projectile;
	}
};

class EventZombieSpawn : public Event
{
public:
	Zombie* zombie;
	EventZombieSpawn(Zombie* zombie)
	{
		name="ZombieSpawn";
		this->zombie = zombie;
	}
};

class EventZombieRemove : public Event
{
public:
	Zombie* zombie;
	EventZombieRemove(Zombie* zombie)
	{
		name="ZombieRemove";
		this->zombie = zombie;
	}
};

class EventZombieDead : public Event
{
public:
	Zombie* zombie;
	EventZombieDead(Zombie* zombie)
	{
		name="ZombieDead";
		this->zombie = zombie;
	}
};

class EventZombieHypnotized : public Event
{
public:
	Zombie* zombie;
	EventZombieHypnotized(Zombie* zombie)
	{
		name="ZombieHypnotized";
		this->zombie = zombie;
	}
};