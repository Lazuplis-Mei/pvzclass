// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

void onCoinCollect(DWORD coinAddress)
{
	auto coin = std::make_shared<PVZ::Coin>(coinAddress);
	char s[64];
	sprintf(s, "%X coin collected!", coinAddress);
	DWORD pid = ProcessOpener::Open();
	PVZ::InitPVZ(pid);
	PVZ::Memory::immediateExecute = true;
	Creator::CreateCaption(s, strlen(s), CaptionStyle::BottomWhite);
}
