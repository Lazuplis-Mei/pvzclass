#pragma once
#include "DLLEvent.h"

// 豌豆穿过火炬树桩的着火事件
// 参数：即将变为火球的豌豆
// 无返回值
class PeaOnFireEvent : public DLLEvent
{
public:
	PeaOnFireEvent();
};

PeaOnFireEvent::PeaOnFireEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onPeaOnFire");
	hookAddress = 0x46ECB0;
	rawlen = 5;
	BYTE code[] = { PUSH_ECX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
