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
	RegisterType args[] = { R_ESI };
	start2(procAddress, STRING(args));
}
