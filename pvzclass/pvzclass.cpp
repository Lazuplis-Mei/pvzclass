#include "pvzclass.h"
#include "Events/EventHandler.h"
#include "Events/DrawUITopEvent.h"
#include <iostream>
#include <thread>

using namespace std;

void hello(shared_ptr<PVZ::Graphics> graphic)
{
	graphic->SetColor(255, 255, 255);
	graphic->DrawString(256, 256, "hello,world!", 13);
}

void listener(shared_ptr<PVZ::Graphics> graphic)
{
	thread t(hello, graphic);
	t.detach();
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
