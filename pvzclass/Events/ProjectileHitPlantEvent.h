#pragma once
#include "DLLEvent.h"

// �ӵ�����ֲ���¼�
// �������ӵ��뱻���е�ֲ��
// ����ֵ�������е�ֲ���ַ��0Ϊ�ж�δ����
// �����������ֲ��Ҳ��������һЩ����˼������
class ProjectileHitPlantEvent : public DLLEvent
{
public:
	ProjectileHitPlantEvent();
};

ProjectileHitPlantEvent::ProjectileHitPlantEvent()
{
	// �����ؼ��е�һ���ط�
	PVZ::Memory::WriteMemory<BYTE>(0x46CBBF, 0xEB);
	PVZ::Memory::WriteMemory<BYTE>(0x46CBC0, 0x63);
	PVZ::Memory::WriteMemory<BYTE>(0x46CC18, 0xEB);
	PVZ::Memory::WriteMemory<BYTE>(0x46CC19, 0x0A);
	int procAddress = PVZ::Memory::GetProcAddress("onProjectileHitPlant");
	hookAddress = 0x46CC28;
	rawlen = 6;
	BYTE code[] = { CMP_EAX_DWORD(0), JE(22), PUSH_EAX, PUSH_EBP,
		INVOKE(procAddress), ADD_ESP(8), MOV_PTR_ESP_ADD_V_EUX(0, 28) };
	start(STRING(code));
}
