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
	hookAddress = 0x432060;
	int procAddress = PVZ::Memory::GetProcAddress("onCoinCollect");
	// Coin::Collect(ecx = this)
	RegisterType args[] = { R_ECX };
	start2(procAddress, STRING(args));
}
