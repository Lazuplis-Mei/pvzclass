#pragma once
#include "DLLEvent.h"

// �㶹���������׮���Ż��¼�
// ������������Ϊ������㶹
// �޷���ֵ
class PeaOnFireEvent : public DLLEvent
{
public:
	PeaOnFireEvent();
};

PeaOnFireEvent::PeaOnFireEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onPeaOnFire");
	hookAddress = 0x46ECB0;
	rawlen = 5;
	BYTE code[] = { PUSH_ECX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
