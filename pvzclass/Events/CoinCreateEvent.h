#pragma once
#include "DLLEvent.h"

// Coin�����¼�
// �����������¼���Coin
// �޷���ֵ
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
