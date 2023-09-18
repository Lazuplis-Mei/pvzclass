#include "pvzclass.h"
#include "Events/EventHandler.h"
#include "Events/DrawUITopEvent.h"
#include <iostream>

using namespace std;

void listener(shared_ptr<PVZ::Graphics> graphic)
{
	graphic->DrawString(256, 256, "hello, world!", 13);
}


int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ* pvz = new PVZ(pid);

	DrawUITopEvent e;
	e.addListener(listener);

	EventHandler handler;
	handler.addEvent(make_shared<DrawUITopEvent>(e));
	handler.start();

	while (true)
	{
		handler.run(1);
	}

	handler.stop();
	delete pvz;
	return 0;
}
