// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

void init()
{
	PVZ::Memory::localExecute = true;
	PVZ::Memory::mainwindowhandle = PVZ::Memory::ReadMemory<HWND>(PVZ_BASE + 0x350);
	PVZ::Memory::Variable = PVZ::Memory::AllocMemory(4);
	PVZ::Memory::immediateExecute = true;
}

void onAppUpdate(DWORD appAddress)
{
	auto app = std::make_shared<PVZ::PVZApp>(appAddress);
}

void onCoinCollect(DWORD coinAddress)
{
	auto coin = std::make_shared<PVZ::Coin>(coinAddress);
}

void onCoinCreate(DWORD coinAddress)
{
	auto coin = std::make_shared<PVZ::Coin>(coinAddress);
}

void onCoinRemove(DWORD coinAddress)
{
	auto coin = std::make_shared<PVZ::Coin>(coinAddress);
}

int onDialogButtonDepress(int buttonId, int dialogId)
{
	return 0;
}

void onDialogDraw(DWORD graphics, Sexy::PDialog dialog)
{
}

void onDrawUITop(DWORD graphics)
{
}

void onNewGame()
{
	auto app = PVZ::GetPVZApp();
	app->LevelId = PVZLevel::Ice_Level;
}

void onPlantCreate(DWORD plantAddress)
{
	auto plant = std::make_shared<PVZ::Plant>(plantAddress);
}

int onPlantReload(DWORD plantAddress, int cd)
{
	auto plant = std::make_shared<PVZ::Plant>(plantAddress);
	return cd;
}

void onPlantShoot(DWORD plantAddress)
{
	auto plant = std::make_shared<PVZ::Plant>(plantAddress);
}

void onPlantRemove(DWORD plantAddress)
{
	auto plant = std::make_shared<PVZ::Plant>(plantAddress);
}

void onPeaOnFire(DWORD projectileAddress)
{
	auto projectile = std::make_shared<PVZ::Projectile>(projectileAddress);
}

void onProjectileCreate(DWORD projectileAddress)
{
	auto projectile = std::make_shared<PVZ::Projectile>(projectileAddress);
}

DWORD onProjectileHitPlant(DWORD projectileAddress, DWORD plantAddress)
{
	auto projectile = std::make_shared<PVZ::Projectile>(projectileAddress);
	auto plant = std::make_shared<PVZ::Plant>(plantAddress);
	return plant->GetBaseAddress();
}

DWORD onProjectileHitZombie(DWORD projectileAddress, DWORD zombieAddress)
{
	auto projectile = std::make_shared<PVZ::Projectile>(projectileAddress);
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
	return zombie->GetBaseAddress();
}

int onProjectileRemove(DWORD projectileAddress)
{
	auto projectile = std::make_shared<PVZ::Projectile>(projectileAddress);
	return 0;
}

void onGameObjectsUpdate(DWORD boardAddress)
{
	auto board = std::make_shared<PVZ::Board>(boardAddress);
}

void onSeedCardClick(DWORD seedcardAddress)
{
	auto seedcard = std::make_shared<PVZ::CardSlot::SeedCard>(seedcardAddress);
}

void onZombieBlast(DWORD zombieAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
}

void onZombieButter(DWORD zombieAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
}

void onZombieDecelerate(DWORD zombieAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
}

void onZombieEat(DWORD zombieAddress, DWORD plantAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
	auto plant = std::make_shared<PVZ::Plant>(plantAddress);
}

void onZombieFroze(DWORD zombieAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
}

int onZombieHit(DWORD zombieAddress, DWORD typeCode, DWORD amount)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
	auto type = (DamageType::DamageType)typeCode;
	return amount;
}

void onZombieHypnotize(DWORD zombieAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
}

void onZombieRemove(DWORD zombieAddress)
{
	auto zombie = std::make_shared<PVZ::Zombie>(zombieAddress);
}
