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
	rawlen = 6;
	BYTE code[] = { PUSH_ECX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
