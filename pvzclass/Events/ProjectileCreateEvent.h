#pragma once
#include "DLLEvent.h"

// �ӵ������¼�
// ���������������ӵ�
// �޷���ֵ
class ProjectileCreateEvent : public DLLEvent
{
public:
	ProjectileCreateEvent();
};

ProjectileCreateEvent::ProjectileCreateEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onProjectileCreate");
	hookAddress = 0x40D652;
	rawlen = 5;
	BYTE code[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
