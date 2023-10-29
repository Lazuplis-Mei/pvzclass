#pragma once
#include "TemplateEvent.h"

// 绘制顶层UI事件
// 无参数与返回值
// 请与Draw.h配合使用
class DrawUITopEvent : public TemplateEvent<std::function<
	void(void)>>
{
public:
	DrawUITopEvent();
	void handle(CONTEXT& context) override;
};