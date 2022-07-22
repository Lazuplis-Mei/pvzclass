#include "events.h"

void EventHandler::InvokeEvent(Event *event,bool isDelete)
{
    std::vector<listener> vec = this->listenersHigh[event->name];
    for(int i=0;i<vec.size();i++){
        vec[i](event, pvz);
        if(event->CancleState)
        {
            if(isDelete)
                delete event;
            return;
        }
    }
    vec = this->listenersMid[event->name];
    for(int i=0;i<vec.size();i++){
        vec[i](event, pvz);
        if(event->CancleState)
        {
            if(isDelete)
                delete event;
            return;
        }
    }
    vec = this->listenersLow[event->name];
    for(int i=0;i<vec.size();i++){
        vec[i](event, pvz);
        if(event->CancleState)
        {
            if(isDelete)
                delete event;
            return;
        }
    }

    if(isDelete)
    {
        delete event;
    }
}
 
void EventHandler::RegistryListeners(std::string event,listener lis,int Level)
{
    switch(Level)
    {
        case Event_Low:
            this->listenersLow[event].push_back(lis);
            break;
        case Event_Mid:
            this->listenersMid[event].push_back(lis);
            break;
        case Event_High:
            this->listenersHigh[event].push_back(lis);
            break;
    }
}


std::string EventPlantPlant::Name = "PlantPlant";
std::string EventPlantRemove::Name = "PlantRemove";
std::string EventPlantUpgrade::Name = "PlantUpgrade";
std::string EventPlantDamage::Name = "PlantDamage";
std::string EventPlantDead::Name = "PlantDead";
std::string EventPlantPotatoMineSproutOuted::Name = "PlantPotatoMineSproutOuted";
std::string EventPlantScaredyShroomScared::Name = "PlantScaredyShroomScared";

std::string EventLevelOpen::Name = "LevelOpen";
std::string EventLevelRestart::Name = "LevelRestart";
std::string EventLevelClose::Name = "LevelClose";
std::string EventLevelWave::Name = "LevelWave";
std::string EventLevelStart::Name = "LevelStart";

std::string EventProjectileFire::Name = "ProjectileFire";
std::string EventProjectileSpawn::Name = "ProjectileSpawn";
std::string EventProjectileRemove::Name = "ProjectileRemove";

std::string EventZombieSpawn::Name = "ZombieSpawn";
std::string EventZombieDamage::Name = "ZombieDamage";
std::string EventZombieHypnotized::Name = "ZombieHypnotized";
std::string EventZombieRemove::Name = "ZombieRemove";
std::string EventZombieDead::Name = "ZombieDead";
std::string EventZombieNewspaperDestoryed::Name = "ZombieNewspaperDestoryed";
std::string EventZombieNewspaperAngried::Name = "ZombieNewspaperAngried";
std::string EventZombiePoleVaultingJumped::Name = "ZombiePoleVaultingJumped";
std::string EventZombiePoleVaultingWalked::Name = "ZombiePoleVaultingWalked";