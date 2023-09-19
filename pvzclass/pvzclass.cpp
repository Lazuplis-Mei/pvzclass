#include "pvzclass.h"
#include "Events/EventHandler.h"
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
#include "Events/ZombieDecelerateEvent.h"
#include "Events/ZombieFrozeEvent.h"
#include "Events/ZombieHypnotizeEvent.h"
#include "Events/ZombieRemoveEvent.h"
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

void listener15(shared_ptr<PVZ::Zombie> zombie)
{
	cout << ZombieType::ToString(zombie->Type) << " 被减速了\n";
}

void listener16(shared_ptr<PVZ::Zombie> zombie)
{
	cout << ZombieType::ToString(zombie->Type) << " 被冻结了\n";
}

void listener17(shared_ptr<PVZ::Zombie> zombie)
{
	cout << ZombieType::ToString(zombie->Type) << " 被魅惑了\n";
}

void listener18(shared_ptr<PVZ::Zombie> zombie)
{
	cout << ZombieType::ToString(zombie->Type) << " 被消灭了\n";
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ* pvz = new PVZ(pid);

	SPT<PVZ::Plant> plant = MKS<PVZ::Plant>(0);
	plant->MoveTo(0, 0);

	EventHandler handler;
	ZombieEatEvent e1;
	e1.addListener(listener0);
	e1.addListener(listener1);
	handler.addEvent(make_shared<ZombieEatEvent>(e1));

	ZombieHitEvent e2;
	e2.addListener(listener2);
	e2.addListener(listener3);
	handler.addEvent(make_shared<ZombieHitEvent>(e2));

	ProjectileCreateEvent e3;
	e3.addListener(listener4);
	handler.addEvent(make_shared<ProjectileCreateEvent>(e3));

	PlantShootEvent e4;
	e4.addListener(listener5);
	handler.addEvent(make_shared<PlantShootEvent>(e4));

	PlantCreateEvent e5;
	e5.addListener(listener6);
	handler.addEvent(make_shared<PlantCreateEvent>(e5));

	CoinCreateEvent e6;
	e6.addListener(listener7);
	handler.addEvent(make_shared<CoinCreateEvent>(e6));

	PlantRemoveEvent e7;
	e7.addListener(listener8);
	handler.addEvent(make_shared<PlantRemoveEvent>(e7));

	PeaOnFireEvent e8;
	e8.addListener(listener9);
	handler.addEvent(make_shared<PeaOnFireEvent>(e8));

	ProjectileRemoveEvent e9;
	e9.addListener(listener10);
	handler.addEvent(make_shared<ProjectileRemoveEvent>(e9));

	CoinCollectEvent e10;
	e10.addListener(listener11);
	handler.addEvent(make_shared<CoinCollectEvent>(e10));

	CoinRemoveEvent e11;
	e11.addListener(listener12);
	handler.addEvent(make_shared<CoinRemoveEvent>(e11));

	ZombieBlastEvent e12;
	e12.addListener(listener13);
	handler.addEvent(make_shared<ZombieBlastEvent>(e12));

	ZombieButterEvent e13;
	e13.addListener(listener14);
	handler.addEvent(make_shared<ZombieButterEvent>(e13));

	ZombieDecelerateEvent e14;
	e14.addListener(listener15);
	handler.addEvent(make_shared<ZombieDecelerateEvent>(e14));

	ZombieFrozeEvent e15;
	e15.addListener(listener16);
	handler.addEvent(make_shared<ZombieFrozeEvent>(e15));

	ZombieHypnotizeEvent e16;
	e16.addListener(listener17);
	handler.addEvent(make_shared<ZombieHypnotizeEvent>(e16));

	ZombieRemoveEvent e17;
	e17.addListener(listener18);
	handler.addEvent(make_shared<ZombieRemoveEvent>(e17));

	handler.start();

	while (true)
	{
		handler.run(1);
	}

	handler.stop();
	delete pvz;
	return 0;
}
