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
	RegisterType args[] = { R_EAX };
	start2(procAddress, STRING(args));
}
