#pragma once
#include "DLLEvent.h"

// �ӵ���ʧ�¼�
// ��������ʧ���ӵ�
// ����ֵ��1ȡ���ӵ���ʧ��0�ӵ�������ʧ
// �ӵ���ʧ��ԭ����ֶ��������н�ʬ�������Ļ�ȶ��ᴥ��
// ����ʱע�ⲻҪȡ����Щ�����Ļ�����Ƴ����ӵ�����ʧ�¼�
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
	BYTE code[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4), TEST_AL_AL, JE(2), POPAD, RET };
	start(STRING(code));
}
