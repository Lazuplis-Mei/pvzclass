#include "pvzclass.h"
#include <iostream>
#include "events.h"

using namespace std;
PVZ *pvz;

void onNutDead(Plant* plant)
{
	if (plant->Type == PlantType::Wallnut)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				Creater::CreateProjectile(ProjectileType::Cactus, plant->Row, plant->X, i * 36, 10);
			}
		}
	}
	else if(plant->Type == PlantType::Tallnut)
	{
		Creater::CreateExplosion(plant->X, plant->Y, 2);
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				Creater::CreateProjectile(ProjectileType::Melon, plant->Row, plant->X, i * 36, 10);
			}
		}
	}
}

void onBloverPlant(Plant* plant)
{
	if (plant->Type == PlantType::Blover)
	{
		PVZ::Zombie* zombies[1000];
		int num = pvz->GetAllZombies(zombies);
		while(num--)
		{
			zombies[num]->FixedCountdown = max(zombies[num]->FixedCountdown,10);
			int hp, maxhp;
			zombies[num]->GetBodyHp(&hp, &maxhp);
			zombies[num]->SetBodyHp(max(hp-10,0), maxhp);
		}
	}
}

void onEnergyBeen(Plant* plant)
{
	using namespace PlantType;
	if (plant->Type == CoffeeBean)
	{
		PVZ::Plant* plants[1000];
		int num = pvz->GetAllPlants(plants);
		while (num--)
		{
			if (plants[num]->Row == plant->Row && plants[num]->Column == plant->Column && plants[num]->Type != CoffeeBean)
			{
				switch (plants[num]->Type)
				{
				case Peashooter:
					for (int i = 0; i < 20; i++)
					{
						Creater::CreateProjectile(ProjectileType::Pea, plants[num]->X, plants[num]->Y, 0, 20);
					}
					break;
				}
			}
		}
	}
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid)
		return 1;
	pvz = new PVZ(pid);
	EventHandler eventBus(pvz);
	Creater::AsmInit();
	eventBus.RegisterPlantPlantEvent(onBloverPlant);
	eventBus.RegisterPlantPlantEvent(onEnergyBeen);
	while (true)
	{
		eventBus.Run();
	}
	delete pvz;
	return 0;
}