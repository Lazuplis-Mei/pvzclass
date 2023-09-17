#pragma once
#include "TemplateEvent.h"

// 植物创建事件
// 参数：触发事件的植物
// 无返回值
class PlantCreateEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Plant>)>>
{
public:
	PlantCreateEvent();
	void handle(CONTEXT& context) override;
};

PlantCreateEvent::PlantCreateEvent()
{
	address = 0x40D190;
}

void PlantCreateEvent::handle(CONTEXT& context)
{
	auto plant = std::make_shared<PVZ::Plant>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](plant);
	}
}
