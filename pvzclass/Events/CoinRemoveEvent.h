#pragma once
#include "DLLEvent.h"

// Coin��ʧ�¼�
// ��������ʧ��Coin
// �޷���ֵ
// Coin��ʧԭ��ࣺܶ���ռ���ʱ�䵽�˵ȶ���ʹ����ʧ
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
