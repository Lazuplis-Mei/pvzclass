#pragma once
#include "pvzclass.h"
#define WIDGETMANAGER PVZ::Memory::ReadPointer(0x6A9EC0, 0x320)

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

	struct EditListener
	{
		DWORD EditWidgetText = 0x4566F0;
		DWORD AllowKey = 0x42FBC0;
		DWORD AllowChar = 0x42FBC0;
		DWORD AllowText = 0x42FBC0;
	};

	typedef DWORD PWidget;
	typedef PWidget PButton;
	typedef PWidget PDialog;
	typedef PWidget PEdit;
	typedef DWORD PButtonListener;
	typedef DWORD PEditListener;

	// ����һ��������
	PButtonListener MakeButtonListener(ButtonListener* listener);

	PEditListener MakeEditListener(EditListener* listener);

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

	// ���������
	// ���븽����ĳ��Dialog��
	// �����Ļ�����Ҫ���DialogDrawEventʹ��
	PEdit MakeEdit(PDialog dialog, PEditListener listener);

	// ��ȡ�ַ���
	Draw::PString GetEditString(PEdit edit);

	// �Ƴ��ؼ�
	void FreeWidget(PWidget widget);

	// ���ÿؼ��Ĵ�С
	void ResizeWidget(PWidget widget, int x, int y, int width, int height);

	// ���ؼ���ΪĿ��ؼ����ӿؼ�
	// ȫ��ManagerΪWIDGETMANAGER
	void AddToWidget(PWidget widget, PWidget father);

	// ���ؼ���Ŀ��ؼ����ӿؼ����Ƴ�
	// ȫ��ManagerΪWIDGETMANAGER
	void RemoveFromWidget(PWidget widget, PWidget father);
}
