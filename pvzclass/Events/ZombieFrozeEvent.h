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

ZombieFrozeEvent::ZombieFrozeEvent()
{
	address = 0x5323C0;
}

#if defined(_WIN64)
void ZombieFrozeEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Rax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie);
	}
}
#else
void ZombieFrozeEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie);
	}
}
#endif