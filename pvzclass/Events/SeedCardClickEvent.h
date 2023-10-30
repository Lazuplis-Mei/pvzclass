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