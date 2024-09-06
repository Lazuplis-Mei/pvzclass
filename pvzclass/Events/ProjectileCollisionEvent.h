#pragma once
#include "DLLEvent.h"

// �ӵ���ײ����¼�
// �������ӵ���ַ
// ����ֵ��0�˺���ʬ 1�˺�ֲ�ˮƽ�� 2�˺�ֲ�Ͷ����
// ����¼������Զ����ӵ��Ƿ��������ֲ����߽�ʬ������
// ����ԭ���������н�ʬ���ӵ����ͳɹ����н�ʬ����Ҫ�޸�DamageAbility
class ProjectileCollisionEvent : public DLLEvent
{
public:
	ProjectileCollisionEvent();
	void end();

private:
	BYTE *rawCode1, *rawCode2, *rawCode3;
	int newAddress1, hookAddress1, rawlen1;
	int newAddress2, hookAddress2, rawlen2;
	int newAddress3, hookAddress3, rawlen3;
};

ProjectileCollisionEvent::ProjectileCollisionEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onProjectileCollision");

	// �޸�ˮƽ��ײ��������жϣ�Ϊ0���н�ʬ����0����ֲ��
	rawlen1 = 10;
	rawCode1 = new BYTE[rawlen1];
	newAddress1 = PVZ::Memory::AllocMemory();
	hookAddress1 = 0x46CFC5;
	PVZ::Memory::ReadArray<BYTE>(hookAddress1, rawCode1, rawlen1);
	BYTE jmpto1[] = { JMPFAR(newAddress1 - (hookAddress1 + 5)), NOP, NOP, NOP, NOP, NOP };
	PVZ::Memory::WriteArray<BYTE>(hookAddress1, STRING(jmpto1));
	BYTE newcode1[] =
	{
		PUSHAD,
		PUSH_EBP,
		INVOKE(procAddress),
		ADD_ESP(4),
		CMP_EUX(0, 0),
		POPAD,
		PUSH_EBP,
		JEFAR(0x46D058 - (newAddress1 + 29)),
		JMPFAR(0x46CFCF - (newAddress1 + 34))
	};
	PVZ::Memory::WriteArray<BYTE>(newAddress1, STRING(newcode1));

	// �޸�Ͷ����ײ��������жϣ�Ϊ0���н�ʬ����0����ֲ��
	rawlen2 = 10;
	rawCode2 = new BYTE[rawlen2];
	newAddress2 = newAddress1 + 0x40;
	hookAddress2 = 0x46D63E;
	PVZ::Memory::ReadArray<BYTE>(hookAddress2, rawCode2, rawlen2);
	BYTE jmpto2[] = { JMPFAR(newAddress2 - (hookAddress2 + 5)), NOP, NOP, NOP, NOP, NOP };
	PVZ::Memory::WriteArray<BYTE>(hookAddress2, STRING(jmpto2));
	BYTE newcode2[] =
	{
		PUSHAD,
		PUSH_EBP,
		INVOKE(procAddress),
		ADD_ESP(4),
		CMP_EUX(0, 0),
		POPAD,
		JNEFAR(0x46D656 - (newAddress2 + 28)),
		JMPFAR(0x46D648 - (newAddress2 + 33))
	};
	PVZ::Memory::WriteArray<BYTE>(newAddress2, STRING(newcode2));

	// �޸���ײ���ֲ�����ȼ���Ϊ1�ǿ�ʳ˳��Ϊ2��Ͷ��˳��
	rawlen3 = 7;
	rawCode3 = new BYTE[rawlen3];
	newAddress3 = newAddress2 + 0x40;
	hookAddress3 = 0x46CB5D;
	PVZ::Memory::ReadArray<BYTE>(hookAddress3, rawCode3, rawlen3);
	BYTE jmpto3[] = { JMPFAR(newAddress3 - (hookAddress3 + 5)), NOP, NOP };
	PVZ::Memory::WriteArray<BYTE>(hookAddress3, STRING(jmpto3));
	BYTE newcode3[] =
	{
		PUSHAD,
		PUSH_EBP,
		INVOKE(procAddress),
		ADD_ESP(4),
		CMP_EUX(0, 1),
		POPAD,
		0x8B, 0x7E, 0x1C,
		JMPFAR(0x46CB64 - (newAddress3 + 30))
	};
	PVZ::Memory::WriteArray<BYTE>(newAddress3, STRING(newcode3));
}

void ProjectileCollisionEvent::end()
{
	PVZ::Memory::WriteArray<BYTE>(hookAddress1, rawCode1, rawlen1);
	PVZ::Memory::WriteArray<BYTE>(hookAddress2, rawCode2, rawlen2);
	PVZ::Memory::WriteArray<BYTE>(hookAddress3, rawCode3, rawlen3);
	PVZ::Memory::FreeMemory(newAddress1);
}
