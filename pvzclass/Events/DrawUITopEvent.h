#pragma once
#include "DLLEvent.h"

// 绘制顶层UI事件
// 无参数与返回值
// 请与Draw.h配合使用
class DrawUITopEvent : public DLLEvent
{
public:
	DrawUITopEvent();
};

DrawUITopEvent::DrawUITopEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onDrawUITop");
	hookAddress = 0x41ACDF;
	rawlen = 5;
	BYTE code[] = { PUSH_PTR_ESP_ADD_V(40), INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
