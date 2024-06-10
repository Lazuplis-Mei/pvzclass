#pragma once
#include "DLLEvent.h"

// Coin创建事件
// 参数：触发事件的Coin
// 无返回值
class CoinCreateEvent : public DLLEvent
{
public:
	CoinCreateEvent();
};

CoinCreateEvent::CoinCreateEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onCoinCreate");
	hookAddress = 0x40CCCE;
	RegisterType args[] = { R_EAX };
	start2(procAddress, STRING(args));
}
