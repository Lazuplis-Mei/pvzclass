#pragma once
#include "TemplateEvent.h"

// 植物射击事件
// 参数：触发事件的植物
// 无返回值
class PlantShootEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Plant>)>>
{
public:
	PlantShootEvent();
	void handle(CONTEXT& context) override;
};

PlantShootEvent::PlantShootEvent()
{
	address = 0x466E0D;
}

#if defined(_WIN64)
void PlantShootEvent::handle(CONTEXT& context)
{
	auto plant = std::make_shared<PVZ::Plant>(context.Rbp);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](plant);
	}
}
#else
void PlantShootEvent::handle(CONTEXT& context)
{
	auto plant = std::make_shared<PVZ::Plant>(context.Ebp);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](plant);
	}
}
#endif