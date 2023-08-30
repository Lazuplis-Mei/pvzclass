#pragma once
#include "BaseEvent.h"

class PlantShootEvent : public BaseEvent<std::function<
	void(std::shared_ptr<PVZ::Plant>)>>
{
public:
	PlantShootEvent();
	bool handle(DebugEventHandler handler);
};

PlantShootEvent::PlantShootEvent()
{
	address = 0x466E0D;
}

bool PlantShootEvent::handle(DebugEventHandler handler)
{
	if (handler.context.Eip != address) return false;
	auto plant = std::make_shared<PVZ::Plant>(handler.context.Ebp);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](plant);
	}
	afterHandle(handler);
	return true;
}
