#pragma once
#include "DLLEvent.h"

// ��ʬ�ҽ��¼�
// �����������¼��Ľ�ʬ
// �޷���ֵ
// ��ʬ�ܵ��ҽ��˺��ͻᴥ��
class ZombieBlastEvent : public DLLEvent
{
public:
	ZombieBlastEvent();
};

ZombieBlastEvent::ZombieBlastEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieBlast");
	hookAddress = 0x532B70;
	RegisterType args[] = { R_ECX };
	start2(procAddress, STRING(args));
}
