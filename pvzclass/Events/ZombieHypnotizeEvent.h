#pragma once
#include "DLLEvent.h"

// 僵尸被魅惑事件
// 参数：触发事件的僵尸
// 无返回值
class ZombieHypnotizeEvent : public DLLEvent
{
public:
	ZombieHypnotizeEvent();
};

ZombieHypnotizeEvent::ZombieHypnotizeEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieHypnotize");
	hookAddress = 0x52FA60;
	rawlen = 10;
	BYTE code[] = { PUSH_ESI, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
