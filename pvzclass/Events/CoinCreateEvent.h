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
	void handle(CONTEXT& context) override;
};

CoinCreateEvent::CoinCreateEvent()
{
	address = 0x40CCCE;
}

#if defined(_WIN64)
void CoinCreateEvent::handle(CONTEXT& context)
{
	auto coin = std::make_shared<PVZ::Coin>(context.Rax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](coin);
	}
}
#else
void CoinCreateEvent::handle(CONTEXT& context)
{
	auto coin = std::make_shared<PVZ::Coin>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](coin);
	}
}
#endif