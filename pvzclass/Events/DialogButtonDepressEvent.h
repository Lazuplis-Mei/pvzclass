#pragma once
#include "DLLEvent.h"

// �Ի��еİ�ť�����¼�����Ӧ������ҵ����ť���ɿ��Ĳ���
// buttonID��1000����ȷ�ϣ�1001����ȡ��
// dialogID���Ի����id
// ԭ����Ϸ�еĶԻ���Ҳ�ᴥ������¼�����ȷ��dialogIDΨһ
// �������ֵ��0����ȡ��ԭ����Ϸ�ĺ�������
class DialogButtonDepressEvent : public DLLEvent
{
public:
	DialogButtonDepressEvent();
};

DialogButtonDepressEvent::DialogButtonDepressEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onDialogButtonDepress");
	hookAddress = 0x5464A0;
	rawlen = 9;
	BYTE code[] =
	{
		PUSH_PTR_ESP_ADD_V(36), PUSH_PTR_ESP_ADD_V(44), INVOKE(procAddress), ADD_ESP(8),
		TEST_AL_AL, JE(4), POPAD, RETN(8)
	};
	start(STRING(code));
}
