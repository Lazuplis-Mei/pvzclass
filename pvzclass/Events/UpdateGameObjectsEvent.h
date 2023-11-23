#pragma once
#include "TemplateEvent.h"

// 更新 GameObject 事件。
// 时序上先于 PVZ 本体的更新函数。
// 该事件不可被取消。
// 该事件需要测试。
// @param 更新的 Board。
class UpdateGameObjectsEvent : public TemplateEvent<std::function<
	void(SPT<PVZ::Board>)> >
{
public:
	UpdateGameObjectsEvent();
	void handle(CONTEXT& context) override;
};