#pragma once
#include "DLLEvent.h"

// ����Dialog����ǰ������׷�ӻ���Edit
// ����ΪDialog�ĵ�ַ
class DialogDrawEvent : public DLLEvent
{
public:
	DialogDrawEvent();
};

DialogDrawEvent::DialogDrawEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onDialogDraw");
	hookAddress = 0x457995;
	rawlen = 5;
	BYTE code[] = { PUSH_EDI, PUSH_PTR_ESP_ADD_V(40), INVOKE(procAddress), ADD_ESP(8) };
	start(STRING(code));
}
