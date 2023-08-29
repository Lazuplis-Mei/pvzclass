#pragma once
#include "BaseEvent.h"

class ZombieEatEvent : public BaseEvent<std::function<
	void(std::shared_ptr<PVZ::Zombie>, std::shared_ptr<PVZ::Plant>)>>
{
public:
	ZombieEatEvent();
	bool handle(DebugEventHandler handler);
};

ZombieEatEvent::ZombieEatEvent()
{
	address = 0x52F689;
}

bool ZombieEatEvent::handle(DebugEventHandler handler)
{
	if (handler.context.Eip != address) return false;
	auto zombie = std::make_shared<PVZ::Zombie>(handler.context.Edi);
	auto plant = std::make_shared<PVZ::Plant>(handler.context.Ecx);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie, plant);
	}
	afterHandle(handler);
	return true;
}