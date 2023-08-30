#include "pvzclass.h"
#include "DebugEvents/ZombieEatEvent.h"
#include "DebugEvents/ZombieHitEvent.h"
#include "DebugEvents/ProjectileCreateEvent.h"
#include "DebugEvents/PlantShootEvent.h"
#include <iostream>

using namespace std;

void listener0(shared_ptr<PVZ::Zombie> zombie, shared_ptr<PVZ::Plant> plant)
{
	cout << ZombieType::ToString(zombie->Type) << " 啃食了 ";
}

void listener1(shared_ptr<PVZ::Zombie> zombie, shared_ptr<PVZ::Plant> plant)
{
	cout << PlantType::ToString(plant->Type) << endl;
}

int listener2(shared_ptr<PVZ::Zombie> zombie, DamageType::DamageType type, int amount)
{
	cout << ZombieType::ToString(zombie->Type) << " 受到了 ";
	return amount * 2;
}

int listener3(shared_ptr<PVZ::Zombie> zombie, DamageType::DamageType type, int amount)
{
	cout << amount << " 点伤害，类型为：" << DamageType::ToString(type) << endl;
	return amount;
}

void listener4(shared_ptr<PVZ::Projectile> projectile)
{
	cout << "生成了一个 " << ProjectileType::ToString(projectile->Type) << " 类型的子弹\n";
}

void listener5(shared_ptr<PVZ::Plant> plant)
{
	cout << PlantType::ToString(plant->Type) << " 开火了\n";
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ* pvz = new PVZ(pid);

	DebugEventHandler handler;
	handler.start();
	ZombieEatEvent e1;
	e1.start();
	e1.addListener(listener0);
	e1.addListener(listener1);
	ZombieHitEvent e2;
	e2.start();
	e2.addListener(listener2);
	e2.addListener(listener3);
	ProjectileCreateEvent e3;
	e3.start();
	e3.addListener(listener4);
	PlantShootEvent e4;
	e4.start();
	e4.addListener(listener5);

  while (true)
	{
		// cout << "R";
		if (handler.run(1))
		{
			/*cout << handler.debugEvent.u.Exception.dwFirstChance << " "
				<< hex << handler.debugEvent.u.Exception.ExceptionRecord.ExceptionCode << dec << " "
				<< handler.debugEvent.u.Exception.ExceptionRecord.ExceptionFlags << " "
				<< handler.debugEvent.u.Exception.ExceptionRecord.ExceptionAddress << endl;*/
			e1.handle(handler);
			e2.handle(handler);
			e3.handle(handler);
			e4.handle(handler);
			handler.resume();
		}
	}

	e1.end();
	e2.end();
	e3.end();
	e4.end();
	handler.stop();
	delete pvz;
	return 0;
}
