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
	rawlen = 5;
	BYTE code[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
