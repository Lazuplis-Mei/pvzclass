#pragma once
#include "DLLEvent.h"

// �ӵ���ʧ�¼�
// ��������ʧ���ӵ�
// �޷���ֵ
// �ӵ���ʧ��ԭ����ֶ��������н�ʬ�������Ļ�ȶ��ᴥ��
class ProjectileRemoveEvent : public DLLEvent
{
public:
	ProjectileRemoveEvent();
};

ProjectileRemoveEvent::ProjectileRemoveEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onProjectileRemove");
	hookAddress = 0x46EB20;
	RegisterType args[] = { R_EAX };
	start2(procAddress, STRING(args));
}
