#pragma once
#include "TemplateEvent.h"

// 僵尸被魅惑事件
// 参数：触发事件的僵尸
// 无返回值
class ZombieHypnotizeEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Zombie>)>>
{
public:
	ZombieHypnotizeEvent();
	void handle(CONTEXT& context) override;
};