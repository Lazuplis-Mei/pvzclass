#pragma once
#include "DLLEvent.h"

// ��Ϸ����ĸ����¼�
// ���¼������Ƿ��ڹؿ��ڶ����������
class UpdateAppEvent : public DLLEvent
{
public:
	UpdateAppEvent();
};

UpdateAppEvent::UpdateAppEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onAppUpdate");
	hookAddress = 0x453A50;
	rawlen = 7;
	BYTE code[] = { PUSH_ECX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
