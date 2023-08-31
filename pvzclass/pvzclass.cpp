#include "pvzclass.h"
#include "Events/ZombieEatEvent.h"
#include "Events/ZombieHitEvent.h"
#include "Events/ProjectileCreateEvent.h"
#include "Events/PlantShootEvent.h"
#include "Events/PlantCreateEvent.h"
#include "Events/PlantRemoveEvent.h"
#include "Events/CoinCreateEvent.h"
#include "Events/PeaOnFireEvent.h"
#include "Events/ProjectileRemoveEvent.h"
#include "Events/CoinCollectEvent.h"
#include "Events/CoinRemoveEvent.h"
#include "Events/ZombieBlastEvent.h"
#include "Events/ZombieButterEvent.h"
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

void listener6(shared_ptr<PVZ::Plant> plant)
{
	cout << PlantType::ToString(plant->Type) << " 被种植了\n";
}

void listener7(shared_ptr<PVZ::Coin> coin)
{
	cout << CoinType::ToString(coin->Type) << " 出现了\n";
}

void listener8(shared_ptr<PVZ::Plant> plant)
{
	cout << PlantType::ToString(plant->Type) << " 移除了\n";
}

void listener9(shared_ptr<PVZ::Projectile> projectile)
{
	cout <<  ProjectileType::ToString(projectile->Type) << " 转换为了火焰豌豆\n";
}

void listener10(shared_ptr<PVZ::Projectile> projectile)
{
	cout << ProjectileType::ToString(projectile->Type) << " 被移除了\n";
}

void listener11(shared_ptr<PVZ::Coin> coin)
{
	cout << CoinType::ToString(coin->Type) << " 被收集了\n";
}

void listener12(shared_ptr<PVZ::Coin> coin)
{
	cout << CoinType::ToString(coin->Type) << " 消失了\n";
}

void listener13(shared_ptr<PVZ::Zombie> zombie)
{
	cout << ZombieType::ToString(zombie->Type) << " 受到了灰烬伤害\n";
}

void listener14(shared_ptr<PVZ::Zombie> zombie)
{
	cout << ZombieType::ToString(zombie->Type) << " 被黄油命中了\n";
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ* pvz = new PVZ(pid);

	EventHandler handler;
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
	PlantCreateEvent e5;
	e5.start();
	e5.addListener(listener6);
	CoinCreateEvent e6;
	e6.start();
	e6.addListener(listener7);
	PlantRemoveEvent e7;
	e7.start();
	e7.addListener(listener8);
	PeaOnFireEvent e8;
	e8.start();
	e8.addListener(listener9);
	ProjectileRemoveEvent e9;
	e9.start();
	e9.addListener(listener10);
	CoinCollectEvent e10;
	e10.start();
	e10.addListener(listener11);
	CoinRemoveEvent e11;
	e11.start();
	e11.addListener(listener12);
	ZombieBlastEvent e12;
	e12.start();
	e12.addListener(listener13);
	ZombieButterEvent e13;
	e13.start();
	e13.addListener(listener14);

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
			e5.handle(handler);
			e6.handle(handler);
			e7.handle(handler);
			e8.handle(handler);
			e9.handle(handler);
			e10.handle(handler);
			e11.handle(handler);
			e12.handle(handler);
			e13.handle(handler);
			handler.resume();
		}
	}

	e1.end();
	e2.end();
	e3.end();
	e4.end();
	e5.end();
	e6.end();
	e7.end();
	e8.end();
	e9.end();
	e10.end();
	e11.end();
	e12.end();
	e13.end();
	handler.stop();
	delete pvz;
	return 0;
}
