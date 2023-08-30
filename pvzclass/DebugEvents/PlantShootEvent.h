#pragma once
#include "BaseEvent.h"

// 植物射击事件
// 参数：触发事件的植物
// 无返回值
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
