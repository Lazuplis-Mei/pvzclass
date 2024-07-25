#pragma once
#include "DLLEvent.h"

// Coin消失事件
// 参数：消失的Coin
// 无返回值
// Coin消失原因很多：被收集后、时间到了等都会使其消失
class CoinRemoveEvent : public DLLEvent
{
public:
	CoinRemoveEvent();
};

CoinRemoveEvent::CoinRemoveEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onCoinRemove");
	hookAddress = 0x432DD0;
	rawlen = 7;
	BYTE code[] = { PUSH_ESI, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
