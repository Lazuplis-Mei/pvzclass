#pragma once
#include "DLLEvent.h"

// 对话中的按钮弹起事件，对应的是玩家点击按钮并松开的操作
// buttonID：1000代表确认，1001代表取消
// dialogID：对话框的id
// 原本游戏中的对话框也会触发这个事件，须确保dialogID唯一
// 如果返回值非0，则取消原本游戏的后续处理
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
