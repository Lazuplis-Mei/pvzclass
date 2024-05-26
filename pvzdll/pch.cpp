// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

void init()
{
	DWORD pid = ProcessOpener::Open();
	PVZ::InitPVZ(pid);
	PVZ::Memory::immediateExecute = true;
}

void onCoinCollect(DWORD coinAddress)
{
	auto coin = std::make_shared<PVZ::Coin>(coinAddress);
	char s[64];
	sprintf(s, "%X coin collected!", coinAddress);
	Creator::CreateCaption(s, strlen(s), CaptionStyle::BottomWhite);
}

void onCoinCreate(DWORD coinAddress)
{
	auto coin = std::make_shared<PVZ::Coin>(coinAddress);
	char s[64];
	sprintf(s, "%X coin created!", coinAddress);
	Creator::CreateCaption(s, strlen(s), CaptionStyle::BottomWhite);
}

void onCoinRemove(DWORD coinAddress)
{
	auto coin = std::make_shared<PVZ::Coin>(coinAddress);
	char s[64];
	sprintf(s, "%X coin removed!", coinAddress);
	Creator::CreateCaption(s, strlen(s), CaptionStyle::BottomWhite);
}

void onPlantCreate(DWORD plantAddress)
{
	auto plant = std::make_shared<PVZ::Plant>(plantAddress);
	char s[64];
	sprintf(s, "%s created!\0", PlantType::ToString(plant->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onPlantShoot(DWORD plantAddress)
{
	auto plant = std::make_shared<PVZ::Plant>(plantAddress);
	char s[64];
	sprintf(s, "%s shot!\0", PlantType::ToString(plant->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onPlantRemove(DWORD plantAddress)
{
	auto plant = std::make_shared<PVZ::Plant>(plantAddress);
	char s[64];
	sprintf(s, "%s removed!\0", PlantType::ToString(plant->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}
