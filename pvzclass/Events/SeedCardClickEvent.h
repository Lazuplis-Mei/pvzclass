#pragma once
#include "TemplateEvent.h"

// 卡槽中的卡片被点击事件
// 参数：SeedCard
// 无返回值
class SeedCardClickEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::CardSlot::SeedCard>)>>
{
public:
	SeedCardClickEvent();
	void handle(CONTEXT& context) override;
};

SeedCardClickEvent::SeedCardClickEvent()
{
	address = 0x412236;
}

void SeedCardClickEvent::handle(CONTEXT& context)
{
	auto seedcard = std::make_shared<PVZ::CardSlot::SeedCard>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](seedcard);
	}
}