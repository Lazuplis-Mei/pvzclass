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