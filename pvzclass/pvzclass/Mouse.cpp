#include "PVZ.h"


PVZ::Mouse::Mouse(int baseaddress)
{
	BaseAddress = baseaddress;
}

void PVZ::Mouse::WMClick(short x, short y)
{
	SendMessage(Memory::mainwindowhandle, WM_LBUTTONDOWN, NULL, MAKELONG(x, y));
	SendMessage(Memory::mainwindowhandle, WM_LBUTTONUP, NULL, MAKELONG(x, y));
}
