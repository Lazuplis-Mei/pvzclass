#pragma once
#include "DLLEvent.h"

// Coin收集事件
// 参数：触发事件的Coin
// 无返回值
class CoinCollectEvent : public DLLEvent
{
public:
	CoinCollectEvent();
};

CoinCollectEvent::CoinCollectEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onCoinCollect");
	hookAddress = 0x432060;
	rawlen = 6;
	BYTE code[] = { PUSH_ECX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
