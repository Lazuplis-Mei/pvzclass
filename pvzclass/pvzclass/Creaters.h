#pragma once
#include "PVZ.h"


#define MOV_ECX_PTR_ADDR(address) 0x8B,0xD,INUMBER(address)
#define INVOKE_BYTE_BYTE(address,b1,b2) PUSH(b2),PUSH(b1),INVOKE(address)
inline short makeshort(byte b1, byte b2)
{
	return (b2 << 8) + b1;
}

#define CREATEZOMBIE INVOKE_BYTE_BYTE(0x42A0F0,0,0)
#define MOV_EAX_EBX 0x8B,0xC3
#define POP_EBX 0x5B
#define RETN(v) 0xC2,v,0



PVZ::Zombie* CreateZombie(ZombieType::ZombieType type, int row, byte column);