#pragma once
#include "DLLEvent.h"

// ���ƶ���UI�¼�
// �޲����뷵��ֵ
// ����Draw.h���ʹ��
class DrawUITopEvent : public DLLEvent
{
public:
	DrawUITopEvent();
};

DrawUITopEvent::DrawUITopEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onDrawUITop");
	hookAddress = 0x41ACDF;
	rawlen = 5;
	BYTE code[] = { PUSH_PTR_ESP_ADD_V(40), INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
