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

	typedef DWORD PButton;
	typedef DWORD PButtonListener;

	// 创建一个监听器
	PButtonListener MakeListener(ButtonListener* listener);

	// 创建一个按钮
	// listener：按钮事件监听器
	// theId：一个按钮Id
	// 返回：按钮的地址
	PButton MakeButton(Draw::PString str, PButtonListener listener, int theId);

	// 创建贴图按钮
	// image**Address：对应状态的Image，使用Draw.h相关代码构建
	// 返回：按钮的地址
	PButton MakeImageButton(Draw::PImage down, Draw::PImage over, Draw::PImage normal,
		DWORD fontAddress, Draw::PString str, PButtonListener listener, int theId);

	// 移除控件
	void FreeButton(PButton button);

	// 重置按钮的大小
	void ResizeButton(PButton button, int x, int y, int width, int height);

	// 将控件加入Manager
	void AddToManager(PButton button);

	// 将控件从Manager中移除
	void RemoveFromManager(PButton button);
}
