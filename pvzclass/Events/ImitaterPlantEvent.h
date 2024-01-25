#pragma once
#include "TemplateEvent.h"

// 模仿者即将生成新植物的事件。
// 多个事件之间植物会串联修改。
// 该事件需要测试。
// @param 触发事件的模仿者（注意：不是即将生成的新植物）、是否取消该事件。
// @return 更新后触发事件的模仿者。
class ImitaterPlantEvent : public TemplateEvent<std::function<
	SPT<PVZ::Plant>(SPT<PVZ::Plant>, bool&)> >
{
public:
	ImitaterPlantEvent();
	void handle(CONTEXT& context) override;
};

