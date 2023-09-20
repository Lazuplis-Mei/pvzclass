#include "pvzclass.h"
#include "Events/EventHandler.h"
#include "Events/DrawUITopEvent.h"
#include <iostream>
#include <thread>

using namespace std;

PVZ* pvz;

void listener()
{
	shared_ptr<PVZ::Plant> plants[256];
	int num = pvz->GetAllPlants(plants);
	vector<Draw::String> vs;
	for (int i = 0; i < num; i++)
	{
		Draw::String s;
		s.x = plants[i]->ImageX;
		s.y = plants[i]->ImageY;
		s.size = 8;
		s.red = 0xFF;
		s.green = 0xFF;
		s.blue = 0xFF;
		sprintf_s(s.s, "生命:%d\0", plants[i]->Hp);
		vs.push_back(s);
	}
	Draw::writeString(vs);
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	pvz = new PVZ(pid);

	Draw::init(10);

	DrawUITopEvent e;
	e.addListener(listener);

	EventHandler handler;
	handler.addEvent(make_shared<DrawUITopEvent>(e));
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
