#pragma once
#include "TemplateEvent.h"

// 植物被碾压事件。
// 多个事件之间植物会串联修改。
// 该事件需要测试。
// @param 触发事件的植物、是否取消该事件。
// @return 更新后被碾压的植物。
class PlantSquishEvent : public TemplateEvent<std::function<
	SPT<PVZ::Plant>(SPT<PVZ::Plant>, bool&)> >
{
public:
	PlantSquishEvent();
	void handle(CONTEXT& context) override;
};

