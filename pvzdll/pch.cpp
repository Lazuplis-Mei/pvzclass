// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

int isnewAddress;
Draw::PString filename;
Draw::PSharedImageRef imageRef;
Draw::PImage image;
void init()
{
	PVZ::Memory::localExecute = true;
	PVZ::Memory::mainwindowhandle = PVZ::Memory::ReadMemory<HWND>(PVZ_BASE + 0x350);
	PVZ::Memory::Variable = PVZ::Memory::AllocMemory(4);
	PVZ::Memory::immediateExecute = true;

	filename = Draw::ToString("images/test.png");
	imageRef = Draw::GetSharedImage(isnewAddress, filename, filename);
	image = Draw::SharedImageRefToImage(imageRef);
}

void onCoinCollect(DWORD coinAddress)
{
	auto coin = std::make_shared<PVZ::Coin>(coinAddress);
	char s[64];
	sprintf(s, "%X coin collected!\0", coinAddress);
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onCoinCreate(DWORD coinAddress)
{
	auto coin = std::make_shared<PVZ::Coin>(coinAddress);
	char s[64];
	sprintf(s, "%X coin created!\0", coinAddress);
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onCoinRemove(DWORD coinAddress)
{
	auto coin = std::make_shared<PVZ::Coin>(coinAddress);
	char s[64];
	sprintf(s, "%X coin removed!\0", coinAddress);
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

Draw::PColor color = 0;
void onDrawUITop(DWORD graphics)
{
	Draw::PString label = Draw::ToString("Hello, world!\0");
	Draw::StringWidth(label, PVZ::Memory::ReadMemory<DWORD>(0x6A7224));
	if (color) PVZ::Memory::FreeMemory(color);
	color = Draw::SetColor(255, 255, 255, graphics);
	Draw::DrawString(400, 300, label, graphics);
	Draw::DrawImage(100, 100, image, graphics);
	Draw::DrawLine(1, 600, 800, 1, graphics);
	Draw::DrawRect(100, 400, 200, 100, graphics);
	Draw::FillRect(500, 100, 100, 200, graphics);
}

void onNewGame()
{
	auto app = PVZ::GetPVZApp();
	app->LevelId = PVZLevel::Ice_Level;
}

void __stdcall listenerFunc(int id)
{
	Creator::CreateCaption("Press!\0", 8, CaptionStyle::BottomWhite);
}

Sexy::ButtonListener listener;
Sexy::PButtonListener plistener;
Sexy::PButton button;
void onPlantCreate(DWORD plantAddress)
{
	auto plant = std::make_shared<PVZ::Plant>(plantAddress);
	listener.PressListener1 = (int)listenerFunc;
	plistener = Sexy::MakeListener(&listener);
	button = Sexy::MakeImageButton(image, image, image,
		PVZ::Memory::ReadMemory<DWORD>(0x6A72D8), filename, plistener, 0);
	Sexy::AddToManager(button);
	Sexy::ResizeButton(button, 350, 250, 100, 100);
}

int onPlantReload(DWORD plantAddress, int cd)
{
	auto plant = std::make_shared<PVZ::Plant>(plantAddress);
	char s[64];
	cd /= 2;
	sprintf(s, "%s reload %d!\0", PlantType::ToString(plant->Type), cd);
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
	return cd;
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
	Sexy::RemoveFromManager(button);
	Sexy::FreeButton(button);
	PVZ::Memory::FreeMemory(plistener);
}

void onPeaOnFire(DWORD projectileAddress)
{
	auto projectile = std::make_shared<PVZ::Projectile>(projectileAddress);
	char s[64];
	sprintf(s, "%s is on fire!\0", ProjectileType::ToString(projectile->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onProjectileCreate(DWORD projectileAddress)
{
	auto projectile = std::make_shared<PVZ::Projectile>(projectileAddress);
	int a = PVZ::Memory::ReadMemory<int>(0x700000);
	PVZ::Memory::WriteMemory<int>(0x700000, a + 1);
	int b[9];
	PVZ::Memory::ReadArray<int>(0x700004, b, 36);
	for (int i = 0; i < 9; i++) b[i] += i + 2;
	PVZ::Memory::WriteArray<int>(0x700004, b, 36);
}

void onProjectileHitZombie(DWORD projectileAddress, DWORD zombieAddress)
{
	auto projectile = std::make_shared<PVZ::Projectile>(projectileAddress);
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
	char s[64];
	sprintf(s, "%s hit %s!\0", ProjectileType::ToString(projectile->Type), ZombieType::ToString(zombie->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onProjectileRemove(DWORD projectileAddress)
{
	auto projectile = std::make_shared<PVZ::Projectile>(projectileAddress);
	char s[64];
	sprintf(s, "%s removed!\0", ProjectileType::ToString(projectile->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onGameObjectsUpdate(DWORD boardAddress)
{
	auto board = std::make_shared<PVZ::Board>(boardAddress);
	char s[64];
	sprintf(s, "%d\0", board->PlayingTime);
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onSeedCardClick(DWORD seedcardAddress)
{
	auto seedcard = std::make_shared<PVZ::CardSlot::SeedCard>(seedcardAddress);
	char s[64];
	sprintf(s, "%s clicked\0", CardType::ToString(seedcard->ContentCard));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onZombieBlast(DWORD zombieAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
	char s[64];
	sprintf(s, "%s blasted!\0", ZombieType::ToString(zombie->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onZombieButter(DWORD zombieAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
	char s[64];
	sprintf(s, "%s buttered!\0", ZombieType::ToString(zombie->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onZombieDecelerate(DWORD zombieAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
	char s[64];
	sprintf(s, "%s decelerated!\0", ZombieType::ToString(zombie->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onZombieEat(DWORD zombieAddress, DWORD plantAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
	auto plant = std::make_shared<PVZ::Plant>(plantAddress);
	char s[64];
	sprintf(s, "%s eats %s!\0", ZombieType::ToString(zombie->Type), PlantType::ToString(plant->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onZombieFroze(DWORD zombieAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
	char s[64];
	sprintf(s, "%s froze!\0", ZombieType::ToString(zombie->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

int onZombieHit(DWORD zombieAddress, DWORD typeCode, DWORD amount)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
	auto type = (DamageType::DamageType)typeCode;
	amount *= 2;
	char s[64];
	sprintf(s, "%s %s %d!\0", ZombieType::ToString(zombie->Type), DamageType::ToString(type), amount);
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
	return amount;
}

void onZombieHypnotize(DWORD zombieAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
	char s[64];
	sprintf(s, "%s hypnotized!\0", ZombieType::ToString(zombie->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}

void onZombieRemove(DWORD zombieAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
	char s[64];
	sprintf(s, "%s removed!\0", ZombieType::ToString(zombie->Type));
	Creator::CreateCaption(s, strlen(s) + 1, CaptionStyle::BottomWhite);
}
