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
	rawlen = 8;
	BYTE code[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
