#pragma once
#include "TemplateEvent.h"

// 解谜关卡完成事件
// 参数：触发事件时的 Miscellaneous，X坐标，Y坐标
// 返回值：更新后的Y坐标
// 多个事件之间Y坐标会串联修改
class PuzzlePhaseCompleteEvent : public TemplateEvent<std::function<
	int(SPT<PVZ::Miscellaneous>, int, int)>>
{
public:
	PuzzlePhaseCompleteEvent();
	void handle(CONTEXT& context) override;
};