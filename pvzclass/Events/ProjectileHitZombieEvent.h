#pragma once
#include "DLLEvent.h"

// �ӵ����н�ʬ�¼�
// �������ӵ��뱻���еĽ�ʬ
// ����ֵ�������еĽ�ʬ��ַ��0Ϊ�ж�δ����
// �������������ʬҲ��������һЩ����˼������
class ProjectileHitZombieEvent : public DLLEvent
{
public:
	ProjectileHitZombieEvent();
};

ProjectileHitZombieEvent::ProjectileHitZombieEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onProjectileHitZombie");
	hookAddress = 0x46CE74;
	rawlen = 6;
	BYTE code[] = { CMP_EAX_DWORD(0), JE(22), PUSH_EAX, PUSH_EBP,
		INVOKE(procAddress), ADD_ESP(8), MOV_PTR_ESP_ADD_V_EUX(0, 28) };
	start(STRING(code));
}
