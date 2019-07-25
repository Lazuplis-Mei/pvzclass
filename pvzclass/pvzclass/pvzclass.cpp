#include "pvzclass.h"
#include <iostream>
#include <math.h>

using namespace std;
typedef bool (*GWhere) (PVZ::Griditem*);
bool IsSnail(PVZ::Griditem* griditem)
{
	return griditem->Type == GriditemType::Snail;
}
int WhereAllGriditems(PVZ* pvz, GWhere condition, PVZ::Griditem* griditems[])
{
	PVZ::Griditem* allgriditems[100];
	int len = pvz->GetAllGriditems(allgriditems);
	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (condition(allgriditems[i]))
		{
			griditems[j] = allgriditems[i];
			j++;
		}
	}
	return j;
}



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
		/*
		在蜗牛范围(110)内的僵尸每1秒持续受到1次冰冻伤害并冻结，离开范围后解除冰冻伤害
		*/
		while (pPVZ->BaseAddress)
		{
			PVZ::Griditem* allsnails[10];
			int len = WhereAllGriditems(pPVZ, IsSnail, allsnails);
			for (int i = 0; i < len; i++)
			{
				PVZ::Snail* snail = (PVZ::Snail*)allsnails[i];
				PVZ::Zombie* zombies[100];
				int num = pPVZ->GetAllZombies(zombies);
				for (int i = 0; i < num; i++)
				{
					CollisionBox cbox;
					zombies[i]->GetCollision(&cbox);
					float a = zombies[i]->X + cbox.Width / 2 - snail->X;
					float b = snail->Y - (zombies[i]->Y + cbox.Height / 2);
					float c = sqrt(a * a + b * b);
					if (c <= 110 && zombies[i]->Temp >= 100)
					{
						zombies[i]->Hit(20, DamageType::Sputter_Ice);
						zombies[i]->FrozenCountdown = 300;
						zombies[i]->Butter();
						zombies[i]->FixedCountdown = 0;
						zombies[i]->Temp = 0;
					}
					zombies[i]->Temp++;
				}
			}
			Sleep(10);//1cs
		}
		delete pPVZ;
	}
	return 0;
}
