#pragma once
#include "DLLEvent.h"

// 僵尸灰烬事件
// 参数：触发事件的僵尸
// 无返回值
// 僵尸受到灰烬伤害就会触发
class ZombieBlastEvent : public DLLEvent
{
public:
	ZombieBlastEvent();
};

ZombieBlastEvent::ZombieBlastEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieBlast");
	hookAddress = 0x532B70;
	rawlen = 6;
	BYTE code[] = { PUSH_ECX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
