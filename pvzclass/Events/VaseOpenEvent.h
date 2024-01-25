#pragma once
#include "TemplateEvent.h"

// 开罐子事件。
// 多个事件之间罐子会串联修改。
// @param 触发事件的罐子、是否取消该事件。
// @return 更新后被打开的罐子。
class VaseOpenEvent : public TemplateEvent<std::function<
	SPT<PVZ::Vase>(SPT<PVZ::Vase>, bool&)> >
{
public:
	VaseOpenEvent();
	void handle(CONTEXT& context) override;
};

