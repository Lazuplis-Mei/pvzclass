#include "pvzclass.h"
#include "Events/EventHandler.h"
#include "Events/SeedCardClickEvent.h"
#include <iostream>
#include <thread>

using namespace std;

PVZ* pvz;

void moreZombie()
{
	Creator::CreateZombie(ZombieType::Zombie, 2, 9);
}

void listener(shared_ptr<PVZ::CardSlot::SeedCard> seedcard)
{
	cout << pvz->GetMouse()->ClickState << " ";
	cout << seedcard->Index << " ";
	cout << CardType::ToString(seedcard->ContentCard) << "卡槽卡片被点击了" << endl;
	thread t(moreZombie);
	t.detach();
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	pvz = new PVZ(pid);

	SeedCardClickEvent e;
	e.addListener(listener);
	EventHandler handler;
	handler.addEvent(make_shared<SeedCardClickEvent>(e));
	handler.start();

	for (int i = 0; i < 1000; i++)
	{
		handler.run(1);
	}

	handler.stop();
	delete pvz;
	return 0;
}
