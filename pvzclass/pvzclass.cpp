#include "pvzclass.h"
#include "HookEvents/ZombieHitEvent.h"
#include <iostream>

using namespace std;

int listener0(shared_ptr<PVZ::Zombie> zombie, DamageType::DamageType type, int amount)
{
	cout << "listener0 触发，伤害翻倍" << endl;
	amount *= 2;
	return amount;
}

int listener1(shared_ptr<PVZ::Zombie> zombie, DamageType::DamageType type, int amount)
{
	cout << "listener1 触发" << endl;
	return amount;
}

int listener2(shared_ptr<PVZ::Zombie> zombie, DamageType::DamageType type, int amount)
{
	cout << "listener2 触发" << endl;
	cout << ZombieType::ToString(zombie->Type) << " 受到了 " << amount << " 点伤害，类型为 " << DamageType::ToString(type) << endl;
	return amount;
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ* pvz = new PVZ(pid);

	ZombieHitEvent e;
	e.start();
	e.addListener(listener0);
	e.addListener(listener1);
	e.addListener(listener2);
	e.removeListener(1);

	while (true)
	{
		e.run();
	}

	e.end();
	delete pvz;
	return 0;
}
