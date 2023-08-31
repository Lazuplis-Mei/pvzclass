#pragma once
#include "BaseEvent.h"

// 植物创建事件
// 参数：触发事件的植物
// 无返回值
class PlantCreateEvent : public BaseEvent<std::function<
	void(std::shared_ptr<PVZ::Plant>)>>
{
public:
	PlantCreateEvent();
	bool handle(EventHandler handler);
};

PlantCreateEvent::PlantCreateEvent()
{
	address = 0x40D190;
}

bool PlantCreateEvent::handle(EventHandler handler)
{
	if (handler.context.Eip != address) return false;
	auto plant = std::make_shared<PVZ::Plant>(handler.context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](plant);
	}
	afterHandle(handler);
	return true;
}
