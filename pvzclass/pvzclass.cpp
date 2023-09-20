#include "pvzclass.h"
#include "Events/EventHandler.h"
#include "Events/DrawUITopEvent.h"
#include "Events/PlantReloadEvent.h"
#include <iostream>
#include <thread>

using namespace std;

PVZ* pvz;
int cooldown;

void listener1()
{
	vector<Draw::String> vs;
	Draw::String s;
	s.x = 40;
	s.y = 100;
	s.size = 8;
	s.red = 0xFF;
	s.green = 0;
	s.blue = 0;
	sprintf_s(s.s, "攻击间隔:%d\0", cooldown);
	vs.push_back(s);
	Draw::writeString(vs);
}

int listener2(std::shared_ptr<PVZ::Plant> plant, int cd)
{
	cooldown = cd;
	return 40;
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	pvz = new PVZ(pid);

	Draw::init(10);

	DrawUITopEvent e1;
	e1.addListener(listener1);

	PlantReloadEvent e2;
	e2.addListener(listener2);

	EventHandler handler;
	handler.addEvent(make_shared<DrawUITopEvent>(e1));
	handler.addEvent(make_shared<PlantReloadEvent>(e2));
	handler.start();

	while (true)
	{
		handler.run(1);
		pvz->ShowMoneyCountdown = 100;
	}

	handler.stop();
	delete pvz;
	return 0;
}
