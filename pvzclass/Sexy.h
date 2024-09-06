#pragma once
#include "PVZ.h"
#include "Draw.h"
#define WIDGETMANAGER PVZ::Memory::ReadPointer(0x6A9EC0, 0x320)

namespace Sexy
{
	/*
		监听器函数设置方式：
		void __stdcall 监听器函数名(参数列表)
		例如用于 DepressListener 的监听器函数：
		void __stdcall listenerFunc(int id) 
		用以下方式设置监听器：
		Sexy::ButtonListener listener;
		listener.DepressListener = (int)listenerFunc;
		注意：以上方式仅限dll中。
	*/

	// 建议只修改抬起事件
	struct ButtonListener
	{
		DWORD PressListener2 = 0x401000;
		DWORD PressListener1 = 0x42FB50;
		// int 按钮ID
		DWORD DepressListener = 0x42FB50;
		DWORD DownTickListener = 0x42FB50;
		DWORD MouseEnterListener = 0x42FB50;
		DWORD MouseLeaveListener = 0x42FB50;
		DWORD MouseMoveListener = 0x483370;
	};

	// 建议不要修改
	struct EditListener
	{
		DWORD EditWidgetText = 0x4566F0;
		DWORD AllowKey = 0x42FBC0;
		DWORD AllowChar = 0x42FBC0;
		DWORD AllowText = 0x42FBC0;
	};

	struct CheckboxListener
	{
		// int 复选框ID, bool 是否被选上
		DWORD CheckboxChecked = 0x4566F0;
	};

	struct ListListener
	{
		// int 列表ID, int 被按下的序号, int 点击次数（1单击2双击）
		DWORD ListClicked = 0x483370;
		// int 列表ID
		DWORD ListClosed = 0x42FB50;
		// int 列表ID, int 老的序号, int 新的序号
		DWORD ListHiliteChanged = 0x483370;
	};

	typedef DWORD PWidget;
	typedef PWidget PButton;
	typedef PWidget PDialog;
	typedef PWidget PEdit;
	typedef PWidget PCheckbox;
	typedef PWidget PList;
	typedef DWORD PButtonListener;
	typedef DWORD PEditListener;
	typedef DWORD PCheckboxListener;
	typedef DWORD PListListener;

	// 创建一个监听器
	PButtonListener MakeButtonListener(ButtonListener* listener);

	PEditListener MakeEditListener(EditListener* listener);

	PCheckboxListener MakeCheckboxListener(CheckboxListener* listener);

	PListListener MakeListListener(ListListener* listener);

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

	// 创建对话框
	// buttonMode：0(NONE) | 1(YES_NO) | 2(OK_CANCEL) | 3(FOOTER)
	// 其中：YES OK FOOTER 对应的buttonId是1000，NO CANCEL是1001
	// modal：0或1，为1时其他窗口将无法响应点击事件且不可获得焦点
	// dialogId：对话框Id，0-50为原版Id，建议从100开始
	PDialog MakeDialog(int buttonMode, Draw::PString footer, Draw::PString lines,
		Draw::PString header, int modal, int dialogId);

	// 创建输入框
	// 必须附着在某个Dialog中
	// 背景的绘制需要配合DialogDrawEvent使用
	PEdit MakeEdit(PDialog dialog, PEditListener listener);

	// 获取字符串
	Draw::PString GetEditString(PEdit edit);

	// 创建勾选框
	// checked为是否默认勾选
	// 勾选框在Resize时的宽为40，高为35
	PCheckbox MakeCheckbox(int checked, PCheckboxListener listener, int theId);

	// 勾选框是否勾选
	bool IsCheckboxChecked(PCheckbox checkbox);

	// 设置勾选框是否勾选
	// tellListener可以控制是否由监听器处理
	void setCheckboxChecked(PCheckbox checkbox, bool checked, bool tellListener);

	// 创建列表
	PList MakeList(PListListener listener);

	// 为列表list加一行line
	// alphabetical为是否按照字母表顺序插入
	// 返回值为插入行在列表中的序号
	int AddListLine(PList list, Draw::PString line, bool alphabetical);

	// 设置列表每一行的高度
	void SetListLineHeight(PList list, int height);

	// 设置列表对齐
	// 0左对齐 1居中对齐 2右对齐
	void SetListJustify(PList list, int justify);

	// 设置/获取列表的当前选项
	void SetListSelected(PList list, int id);
	int GetListSelected(PList list);

	// 移除控件
	void FreeWidget(PWidget widget);

	// 重置控件的大小
	void ResizeWidget(PWidget widget, int x, int y, int width, int height);

	// 将控件作为目标控件的子控件
	// 全局Manager为WIDGETMANAGER
	void AddToWidget(PWidget widget, PWidget father);

	// 将控件从目标控件的子控件中移除
	// 全局Manager为WIDGETMANAGER
	void RemoveFromWidget(PWidget widget, PWidget father);
}
