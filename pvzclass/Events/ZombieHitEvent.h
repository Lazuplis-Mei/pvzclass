#pragma once
#include "DLLEvent.h"

// ��ʬ�����¼�
// �����������¼��Ľ�ʬ���˺����ͣ��˺���ֵ
// ����ֵ�����º���˺�ֵ
// ����¼�֮���˺��ᴮ���޸ģ���������˺�20
// ��һ��������������40���ڶ����¼����������˺���ֵ����40
// �粻�������޸ģ���ʬ�����ܵ�40���˺�
class ZombieHitEvent : public DLLEvent
{
public:
	ZombieHitEvent();
};

ZombieHitEvent::ZombieHitEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieHit");
	hookAddress = 0x5317C0;
	rawlen = 7;
	BYTE code[] = { PUSH_PTR_ESP_ADD_V(36), PUSH_EAX, PUSH_ESI, INVOKE(procAddress), ADD_ESP(12), MOV_PTR_ESP_ADD_V_EUX(0, 36)};
	start(STRING(code));
}
