#pragma once
#include "TemplateEvent.h"

// Coin收集事件
// 参数：触发事件的Coin
// 无返回值
class CoinCollectEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Coin>)>>
{
public:
	CoinCollectEvent();
	void handle(CONTEXT& context) override;
};