#pragma once
#include "TemplateEvent.h"

// 僵尸被黄油命中事件
// 参数：触发事件的僵尸
// 无返回值
class ZombieButterEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Zombie>)>>
{
public:
	ZombieButterEvent();
	void handle(CONTEXT& context) override;
};

ZombieButterEvent::ZombieButterEvent()
{
	address = 0x5326D0;
}

void ZombieButterEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie);
	}
}