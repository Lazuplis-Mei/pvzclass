#pragma once
#include "TemplateEvent.h"

// 僵尸被冻结事件
// 参数：触发事件的僵尸
// 无返回值
class ZombieFrozeEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Zombie>)>>
{
public:
	ZombieFrozeEvent();
	void handle(CONTEXT& context) override;
};