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
	RegisterType args[] = { R_ESI };
	start2(procAddress, STRING(args));
}
