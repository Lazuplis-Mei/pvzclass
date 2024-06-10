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
	int procAddress = PVZ::Memory::GetProcAddress("onCoinCollect");
	// 0x432060: Coin::Collect(ecx = this)
	hookAddress = 0x432060;
	RegisterType args[] = { R_ECX };
	start2(procAddress, STRING(args));
}
