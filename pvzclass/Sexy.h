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

	// ����һ����ť
	// label��Ҫ��ʾ���ı�����'\0'��β
	// listener����ť�¼�������
	// theId��һ����ťId
	// address���ı����麯����ȵ���ʼ��ַ����Ҫ������ʱ�ͷ��ڴ�
	// ���أ���ť�ĵ�ַ
	int MakeButton(const char* label, ButtonListener* listener, int theId, int& address);

	// �Ƴ��ؼ�
	void FreeButton(DWORD buttonAddress, DWORD address);

	// ���ð�ť�Ĵ�С
	void ResizeButton(DWORD buttonAddress, int x, int y, int width, int height);

	// ���ؼ�����Manager
	void AddToManager(DWORD address);

	// ���ؼ���Manager���Ƴ�
	void RemoveFromManager(DWORD address);
}
