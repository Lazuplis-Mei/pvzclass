#pragma once
#include "DLLEvent.h"

// 卡槽中的卡片被点击事件
// 参数：SeedCard
// 无返回值
class SeedCardClickEvent : public DLLEvent
{
public:
	SeedCardClickEvent();
};

SeedCardClickEvent::SeedCardClickEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onSeedCardClick");
	hookAddress = 0x488590;
	rawlen = 8;
	BYTE code[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
