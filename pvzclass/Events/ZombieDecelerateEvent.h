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

ZombieDecelerateEvent::ZombieDecelerateEvent()
{
	address = 0x530950;
}

void ZombieDecelerateEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie);
	}
}