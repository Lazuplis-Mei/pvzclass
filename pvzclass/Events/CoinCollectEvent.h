#pragma once
#include "DLLEvent.h"
#include "../Mixin.h"

// Coin�ռ��¼�
// �����������¼���Coin
// �޷���ֵ
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
