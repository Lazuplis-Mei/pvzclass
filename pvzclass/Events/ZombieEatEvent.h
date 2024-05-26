#pragma once
#include "DLLEvent.h"

// 僵尸啃食植物事件
// 参数：触发事件的僵尸和植物
// 无返回值
class ZombieEatEvent : public DLLEvent
{
public:
	ZombieEatEvent();
};

ZombieEatEvent::ZombieEatEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieEat");
	hookAddress = 0x52FB40;
	rawlen = 7;
	BYTE code[] = { PUSH_ECX, PUSH_EDI, INVOKE(procAddress), ADD_ESP(8) };
	start(STRING(code));
}
