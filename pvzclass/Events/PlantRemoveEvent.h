#pragma once
#include "TemplateEvent.h"

// 植物消失事件
// 参数：触发事件的植物
// 无返回值
// 植物消失原因多种多样：被铲掉、被啃食、一次性植物生效、紫卡植物升级等都会触发
class PlantRemoveEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Plant>)>>
{
public:
	PlantRemoveEvent();
	bool handle(EventHandler handler);
};

PlantRemoveEvent::PlantRemoveEvent()
{
	address = 0x4679B9;
}

bool PlantRemoveEvent::handle(EventHandler handler)
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
