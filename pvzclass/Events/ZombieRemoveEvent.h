#pragma once
#include "DLLEvent.h"

// ��ʬ���Ƴ��¼�
// �����������¼��Ľ�ʬ
// �޷���ֵ
// ��ʬ���Ƴ���ԭ����ֶ�������ʹ�ǹؿ���ʬԤ������Ľ�ʬ���Ƴ�Ҳ�ᴥ�����¼�
class ZombieRemoveEvent : public DLLEvent
{
public:
	ZombieRemoveEvent();
};

ZombieRemoveEvent::ZombieRemoveEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieRemove");
	hookAddress = 0x530510;
	rawlen = 6;
	BYTE code[] = { PUSH_ECX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
