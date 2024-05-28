// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
typedef unsigned char byte;
#include "../pvzclass/pvzclass.h"

extern "C"
{
	__declspec(dllexport) void init();
	__declspec(dllexport) void onCoinCollect(DWORD coinAddress);
	__declspec(dllexport) void onCoinCreate(DWORD coinAddress);
	__declspec(dllexport) void onCoinRemove(DWORD coinAddress);
	__declspec(dllexport) void onDrawUITop(DWORD graphics);
	__declspec(dllexport) void onPlantCreate(DWORD plantAddress);
	__declspec(dllexport) int onPlantReload(DWORD plantAddress, int cd);
	__declspec(dllexport) void onPlantRemove(DWORD plantAddress);
	__declspec(dllexport) void onPlantShoot(DWORD plantAddress);
	__declspec(dllexport) void onPeaOnFire(DWORD projectileAddress);
	__declspec(dllexport) void onProjectileCreate(DWORD projectileAddress);
	__declspec(dllexport) void onProjectileHitZombie(DWORD projectileAddress, DWORD zombieAddress);
	__declspec(dllexport) void onProjectileRemove(DWORD projectileAddress);
	__declspec(dllexport) void onGameObjectsUpdate(DWORD boardAddress);
	__declspec(dllexport) void onSeedCardClick(DWORD seedcardAddress);
	__declspec(dllexport) void onZombieBlast(DWORD zombieAddress);
	__declspec(dllexport) void onZombieButter(DWORD zombieAddress);
	__declspec(dllexport) void onZombieDecelerate(DWORD zombieAddress);
	__declspec(dllexport) void onZombieEat(DWORD zombieAddress, DWORD plantAddress);
	__declspec(dllexport) void onZombieFroze(DWORD zombieAddress);
	__declspec(dllexport) int onZombieHit(DWORD zombieAddress, DWORD typeCode, DWORD amount);
	__declspec(dllexport) void onZombieHypnotize(DWORD zombieAddress);
	__declspec(dllexport) void onZombieRemove(DWORD zombieAddress);
}

#endif //PCH_H
