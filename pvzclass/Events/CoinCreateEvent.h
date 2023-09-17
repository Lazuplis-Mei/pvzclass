#pragma once
#include "TemplateEvent.h"

// Coin创建事件
// 参数：触发事件的Coin
// 无返回值
class CoinCreateEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Coin>)>>
{
public:
	CoinCreateEvent();
	bool handle(EventHandler handler);
};

CoinCreateEvent::CoinCreateEvent()
{
	address = 0x40CCCE;
}

bool CoinCreateEvent::handle(EventHandler handler)
{
	if (handler.context.Eip != address) return false;
	auto coin = std::make_shared<PVZ::Coin>(handler.context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](coin);
	}
	afterHandle(handler);
	return true;
}
