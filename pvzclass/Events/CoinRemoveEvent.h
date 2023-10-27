#pragma once
#include "TemplateEvent.h"

// Coin消失事件
// 参数：消失的Coin
// 无返回值
// Coin消失原因很多：被收集后、时间到了等都会使其消失
class CoinRemoveEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Coin>)>>
{
public:
	CoinRemoveEvent();
	void handle(CONTEXT& context) override;
};

CoinRemoveEvent::CoinRemoveEvent()
{
	address = 0x432DD0;
}

#if defined(_WIN64)
void CoinRemoveEvent::handle(CONTEXT& context)
{
	auto coin = std::make_shared<PVZ::Coin>(context.Rsi);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](coin);
	}
}
#else
void CoinRemoveEvent::handle(CONTEXT& context)
{
	auto coin = std::make_shared<PVZ::Coin>(context.Esi);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](coin);
	}
}
#endif