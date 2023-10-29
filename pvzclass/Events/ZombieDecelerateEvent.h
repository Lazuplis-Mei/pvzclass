#pragma once
#include "TemplateEvent.h"

// 僵尸被减速事件
// 参数：触发事件的僵尸
// 无返回值
class ZombieDecelerateEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Zombie>)>>
{
public:
	ZombieDecelerateEvent();
	void handle(CONTEXT& context) override;
};