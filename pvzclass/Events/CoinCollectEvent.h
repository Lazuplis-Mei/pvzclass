#pragma once
#include "DLLEvent.h"
#include "../Mixin.h"

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
	hookAddress = 0x432060;
	int procAddress = PVZ::Memory::GetProcAddress("onCoinCollect");
	// Coin::Collect(ecx = this)
	RegisterType args[] = { R_ECX };
	start2(procAddress, STRING(args));
}
