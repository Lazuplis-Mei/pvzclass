#pragma once
#include "DLLEvent.h"

// ��ʬ���Ȼ��¼�
// �����������¼��Ľ�ʬ
// �޷���ֵ
class ZombieHypnotizeEvent : public DLLEvent
{
public:
	ZombieHypnotizeEvent();
};

ZombieHypnotizeEvent::ZombieHypnotizeEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieHypnotize");
	hookAddress = 0x52FA60;
	RegisterType args[] = { R_ESI };
	start2(procAddress, STRING(args));
}
