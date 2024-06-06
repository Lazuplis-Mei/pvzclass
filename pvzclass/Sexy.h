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

	typedef DWORD PWidget;
	typedef PWidget PButton;
	typedef PWidget PDialog;
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

	// �����Ի���
	// buttonMode��0(NONE) | 1(YES_NO) | 2(OK_CANCEL) | 3(FOOTER)
	// ���У�YES OK FOOTER ��Ӧ��buttonId��1000��NO CANCEL��1001
	// modal��0��1��Ϊ1ʱ�������ڽ��޷���Ӧ����¼��Ҳ��ɻ�ý���
	// dialogId���Ի���Id��0-50Ϊԭ��Id�������100��ʼ
	PDialog MakeDialog(int buttonMode, Draw::PString footer, Draw::PString lines,
		Draw::PString header, int modal, int dialogId);

	// �Ƴ��ؼ�
	void FreeWidget(PWidget widget);

	// ���ð�ť�Ĵ�С
	void ResizeButton(PButton button, int x, int y, int width, int height);

	// ���ؼ�����Manager
	void AddToManager(PWidget widget);

	// ���ؼ���Manager���Ƴ�
	void RemoveFromManager(PWidget widget);
}
