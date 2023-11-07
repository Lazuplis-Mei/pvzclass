#include "pvzclass.h"
#include "Events/EventHandler.h"
#include "Events/SeedCardClickEvent.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

void moreZombie()
{
	Creator::CreateZombie(ZombieType::Zombie, 2, 9);
}

void listener(SPT<PVZ::CardSlot::SeedCard> seedcard)
{
	cout << PVZ::GetMouse()->ClickState << " ";
	cout << seedcard->Index << " ";
	cout << CardType::ToString(seedcard->ContentCard) << "卡槽卡片被点击了" << endl;
	thread t(moreZombie);
	t.detach();
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ::InitPVZ(pid);

	EnableVaseBreak();

	SeedCardClickEvent e;
	e.addListener(listener);
	EventHandler handler;
	handler.addEvent(MKS<SeedCardClickEvent>(e));
	handler.start();

	for (int i = 0; i < 1000; i++)
	{
		handler.run(1);
	}

	handler.stop();
	PVZ::QuitPVZ();
	return 0;
}
