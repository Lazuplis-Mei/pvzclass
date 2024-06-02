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

	// ����һ��������
	PButtonListener MakeListener(ButtonListener* listener);

	// ����һ����ť
	// listener����ť�¼�������
	// theId��һ����ťId
	// ���أ���ť�ĵ�ַ
	PButton MakeButton(Draw::PString str, PButtonListener listener, int theId);

	// ������ͼ��ť
	// image**Address����Ӧ״̬��Image��ʹ��Draw.h��ش��빹��
	// ���أ���ť�ĵ�ַ
	PButton MakeImageButton(Draw::PImage down, Draw::PImage over, Draw::PImage normal,
		DWORD fontAddress, Draw::PString str, PButtonListener listener, int theId);

	// �Ƴ��ؼ�
	void FreeButton(PButton button);

	// ���ð�ť�Ĵ�С
	void ResizeButton(PButton button, int x, int y, int width, int height);

	// ���ؼ�����Manager
	void AddToManager(PButton button);

	// ���ؼ���Manager���Ƴ�
	void RemoveFromManager(PButton button);
}
