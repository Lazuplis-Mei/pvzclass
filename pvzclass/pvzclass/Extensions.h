#pragma once
#include "PVZ.h"

#define MEMMOD_BYTE(address,v,rv) PVZ::Memory::WriteMemory<byte>(address,b?v:rv)
#define JO 112
#define JZ 116

void EnableBackgroundRunning(BOOLEAN b = true)
{
	MEMMOD_BYTE(0x54EBA8, JO, JZ);
}