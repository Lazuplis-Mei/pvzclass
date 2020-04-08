#include "../PVZ.h"


PVZ::Mouse::Mouse(int baseaddress)
{
	BaseAddress = baseaddress;
}

void PVZ::Mouse::WMClick(short x, short y)
{
	SetForegroundWindow(Memory::mainwindowhandle);
	SendMessage(Memory::mainwindowhandle, WM_LBUTTONDOWN, NULL, MAKELONG(x, y));
	SendMessage(Memory::mainwindowhandle, WM_LBUTTONUP, NULL, MAKELONG(x, y));
}

void PVZ::Mouse::GameClick(int x, int y)
{
	SETARG(__asm__GameClick, 1) = Memory::ReadPointer(0x6A9EC0, 0x320);
	SETARG(__asm__GameClick, 6) = y;
	SETARG(__asm__GameClick,16) = x;
	Memory::Execute(STRING(__asm__GameClick));
}

void PVZ::Mouse::MoveTo(int x, int y)
{
	POINT point;
	point.x = x;
	point.y = y;
	ClientToScreen(Memory::mainwindowhandle, &point);
	SetCursorPos(point.x, point.y);
}
