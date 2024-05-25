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
	rawlen = 8;
	BYTE code[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
