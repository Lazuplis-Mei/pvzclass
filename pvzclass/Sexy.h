#pragma once
#include "pvzclass.h"

namespace Sexy
{
	struct ButtonListener
	{
		DWORD PressListener2 = 0x401000;
		DWORD PressListener1 = 0x42FB50;
		DWORD DepressListener = 0x42FB50;
		DWORD DownTickListener = 0x42FB50;
		DWORD MouseEnterListener = 0x42FB50;
		DWORD MouseLeaveListener = 0x42FB50;
		DWORD MouseMoveListener = 0x483370;
	};

	// 创建一个按钮
	// label：要显示的文本，以'\0'结尾
	// listener：按钮事件监听器
	// theId：一个按钮Id
	// address：文本、虚函数表等的起始地址，需要在析构时释放内存
	// 返回：按钮的地址
	int MakeButton(const char* label, ButtonListener* listener, int theId, int& address);

	// 移除控件
	void FreeButton(DWORD buttonAddress, DWORD address);

	// 重置按钮的大小
	void ResizeButton(DWORD buttonAddress, int x, int y, int width, int height);

	// 将控件加入Manager
	void AddToManager(DWORD address);

	// 将控件从Manager中移除
	void RemoveFromManager(DWORD address);
}
