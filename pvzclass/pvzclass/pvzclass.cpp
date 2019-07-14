#include "pvzclass.h"
#include <iostream>
#include <time.h> 

using namespace std;


PVZ::Zombie* GetFirstZombie()
{
	int len = PVZ::Memory::ReadMemory<int>(PVZBASEADDRESS + 0x94);
	for (int i = 0; i < len; i++)
	{
		PVZ::Zombie* zombie = new PVZ::Zombie(i);
		if (!zombie->NotExist && zombie->NotDying)return zombie;
	}
	return NULL;
}

int main()
{

	DWORD pid = ProcessOpener::Open();
	
	if (pid)
	{
		PVZ* pPVZ = new PVZ(pid);

		if (pPVZ->BaseAddress)
		{
			PVZ::CardSlot* cardslot = pPVZ->GetCardSlot();
			for (int i = 0; i < cardslot->CardsCount; i++)
			{
				PVZ::CardSlot::SeedCard* card = cardslot->GetCard(i);
				//卡槽全部变成模仿者
				if (card->ContentCard != CardType::Imitater)
				{
					card->ContentCardImitative = card->ContentCard;
					card->ContentCard = CardType::Imitater;
				}
				else
				{
					card->ContentCard = card->ContentCardImitative;
				}
			}
			PVZ::Plant* plant = Creater::CreatePlant(PlantType::Squash, 2, 4);
			Sleep(1000);
			plant->SetAnimation("anim_lookright", APA_LOOP,10);
			plant->State = 3;
			plant->AttributeCountdown = 100;
		}
		delete pPVZ;
	}
	return 0;
}
