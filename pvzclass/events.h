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
typedef void(*listener)(Event*, PVZ*);

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

#define LISTENER(x) ((listener)x)

class EventHandler
{
private:
	PVZ* pvz;
	std::vector<SPT<Plant>> GetAllPlants();
	std::vector<SPT<Zombie>> GetAllZombies();
	std::vector<SPT<Projectile>> GetAllProjectiles();//wait for Projectile event
	std::vector<SPT<Plant>> PlantList;
	std::vector<SPT<Zombie>> ZombieList;
	std::vector<SPT<Projectile>> ProjectileList;//wait for projectile event
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
	void RegistryListeners(std::string event,listener lis,int Level = Event_Mid);
	template<typename EventType> void RegistryListeners(void(*lis)(EventType*, PVZ*), int Level = Event_Mid) {
		RegistryListeners(EventType::Name, LISTENER(lis), Level);
	}
	/*end of the events.*/
};

/*Plant Event*/
class EventPlantPlant : public Event
{
public:
	static std::string Name;
	Plant* plant;
	EventPlantPlant(Plant* plant) : plant(plant)
	{
		name = Name;
	}
};

class EventPlantRemove : public Event
{
public:
	static std::string Name;
	Plant* plant;
	EventPlantRemove(Plant* plant) : plant(plant)
	{
		name = Name;
	}
};

class EventPlantUpgrade : public Event
{
public:
	static std::string Name;
	Plant* plant;
	EventPlantUpgrade(Plant* plant) : plant(plant)
	{
		name = Name;
	}
};

class EventPlantDamage : public Event
{
public:
	static std::string Name;
	Plant* plant;
	Zombie* zombie;
	EventPlantDamage(Plant* plant, Zombie* zombie) : plant(plant), zombie(zombie)
	{
		name = Name;
	}
};

class EventPlantDead : public Event
{
public:
	static std::string Name;
	Plant* plant;
	Zombie* zombie;
	std::pair<int, int> last_pos;
	std::pair<int, int> last_row_column;
	EventPlantDead(Plant* plant, std::pair<int, int> last_pos, std::pair<int, int> last_row_column) : plant(plant), last_pos(last_pos), last_row_column(last_row_column)
	{
		name = Name;
	}
};

class EventPlantPotatoMineSproutOuted : public Event
{
public:
	static std::string Name;
	Plant* plant;
	EventPlantPotatoMineSproutOuted(Plant* plant) : plant(plant)
	{
		name = Name;
	}
};

/*Level Event*/
class EventLevelOpen : public Event
{
public:
	static std::string Name;
	EventLevelOpen()
	{
		name = Name;
	}
};

class EventLevelRestart : public Event
{
public:
	static std::string Name;
	EventLevelRestart()
	{
		name = Name;
	}
};

class EventLevelClose : public Event
{
public:
	static std::string Name;
	EventLevelClose()
	{
		name = Name;
	}
};

class EventLevelWave : public Event
{
public:
	static std::string Name;
	int wave;
	EventLevelWave(int wave) : wave(wave)
	{
		name = Name;
	}
};

class EventLevelStart : public Event
{
public:
	static std::string Name;
	EventLevelStart()
	{
		name = Name;
	}
};

/*Projectile Event*/
class EventProjectileFire : public Event
{
public:
	static std::string Name;
	Plant* plant;
	Projectile* projectile;
	EventProjectileFire(Projectile* projectile, Plant* plant) : projectile(projectile), plant(plant)
	{
		name = Name;
	}
};

class EventProjectileSpawn : public Event
{
public:
	static std::string Name;
	Projectile* projectile;
	EventProjectileSpawn(Projectile* projectile) : projectile(projectile)
	{
		name = Name;
	}
};

class EventProjectileRemove : public Event
{
public:
	static std::string Name;
	Projectile* projectile;
	EventProjectileRemove(Projectile* projectile) : projectile(projectile)
	{
		name = Name;
	}
};

/*Zombie Event*/
class EventZombieSpawn : public Event
{
public:
	static std::string Name;
	Zombie* zombie;
	EventZombieSpawn(Zombie* zombie) : zombie(zombie)
	{
		name = Name;
	}
};

class EventZombieRemove : public Event
{
public:
	static std::string Name;
	Zombie* zombie;
	EventZombieRemove(Zombie* zombie) : zombie(zombie)
	{
		name = Name;
	}
};

class EventZombieDead : public Event
{
public:
	static std::string Name;
	Zombie* zombie;
	EventZombieDead(Zombie* zombie) : zombie(zombie)
	{
		name = Name;
	}
};

class EventZombieHypnotized : public Event
{
public:
	static std::string Name;
	Zombie* zombie;
	EventZombieHypnotized(Zombie* zombie) : zombie(zombie)
	{
		name = Name;
	}
};

class EventZombieDamage : public Event
{
public:
	static std::string Name;
	Zombie* zombie;
	Projectile* projectile;
	EventZombieDamage(Zombie* zombie, Projectile* projectile) : zombie(zombie), projectile(projectile)
	{
		name = Name;
	}
};

class EventZombieNewspaperDestoryed : public Event
{
public:
	static std::string Name;
	Zombie* zombie;
	EventZombieNewspaperDestoryed(Zombie* zombie) : zombie(zombie)
	{
		name = Name;
	}
};

class EventZombieNewspaperAngried : public Event
{
public:
	static std::string Name;
	Zombie* zombie;
	EventZombieNewspaperAngried(Zombie* zombie) : zombie(zombie)
	{
		name = Name;
	}
};

class EventZombiePoleVaultingJumped : public Event
{
public:
	static std::string Name;
	Zombie* zombie;
	EventZombiePoleVaultingJumped(Zombie* zombie) : zombie(zombie)
	{
		name = Name;
	}
};

class EventZombiePoleVaultingWalked : public Event
{
public:
	static std::string Name;
	Zombie* zombie;
	EventZombiePoleVaultingWalked(Zombie* zombie) : zombie(zombie)
	{
		name = Name;
	}
};