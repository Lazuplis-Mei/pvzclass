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