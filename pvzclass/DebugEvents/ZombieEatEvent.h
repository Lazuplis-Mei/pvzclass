#pragma once
#include "BaseEvent.h"

class ZombieEatEvent : public BaseEvent<std::function<
	void(std::shared_ptr<PVZ::Zombie>, std::shared_ptr<PVZ::Plant>)>>
{
public:
	ZombieEatEvent();
	bool handle(DEBUG_EVENT& debugEvent, CONTEXT& context, HANDLE hThread);
};

ZombieEatEvent::ZombieEatEvent()
{
	address = 0x52F689;
}

bool ZombieEatEvent::handle(DEBUG_EVENT& debugEvent, CONTEXT& context, HANDLE hThread)
{
	if (context.Eip != address) return false;
	auto zombie = std::make_shared<PVZ::Zombie>(context.Edi);
	auto plant = std::make_shared<PVZ::Plant>(context.Ecx);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie, plant);
	}
	afterHandle(debugEvent, context, hThread);
	return true;
}