#pragma once
#include "DLLEvent.h"

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
	hookAddress = 0x432060;
	rawlen = 6;
	BYTE code[] = { PUSH_ECX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
