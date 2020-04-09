#include "AsmFuntions.h"

byte __asm__set_MusicVolume[]
{
	MOV_ECX(0),
	SET_MUSICVOLUME,
	RET
};

byte __asm__InjectDll[200]
{
	LOADLIBRARYA,
	RET
};

byte __asm__set__LevelScene[]
{
	MOV_ESI(0),
	SET_LEVELSCENE,
	RET
};

byte __asm__Win[]
{
	MOV_ECX(0),
	WIN,
	RET
};

byte __asm__Hit[]
{
	MOV_ESI(0),
	MOV_EAX(0),
	HIT,
	RET
};

byte __asm__Blast[]
{
	MOV_ECX(0),
	BLAST,
	RET
};

byte __asm__Butter[]
{
	MOV_EAX(0),
	BUTTER,
	RET
};

byte __asm__CreateEffect[]
{
	CREATEEFFECT,
	RET
};

byte __asm__SetStatic[]
{
	MOV_EAX_PTR(0),
	SETSTATIC,
	RET,
};

byte __asm__Shoot[]
{
	SHOOT,
	MOV_PTR_ADDR_ECX(0),
	RET,
};

byte __asm__OnFire[]
{
	MOV_ECX(0),
	ONFIRE,
	RET,
};

byte __asm__Collect[]
{
	MOV_ECX(0),
	COLLECT,
	RET,
};

byte __asm__GameClick[]
{
	MOV_ECX(0),
	MOV_EAX(0),
	MOV_EBX(1),
	GAMECLICK,
	RET,
};

byte __asm__Music__set_Type[]
{
	MOV_EDI(0),
	MOV_EAX(0),
	MUSICSETTYPE,
	RET,
};

byte __asm__Zombie__setAnimation[100]
{
	MOV_EDI(0),
	ZOMBIE_SETANIMATION,
	RET,
};

byte __asm__Plant__setAnimation[100]
{
	MOV_EAX(0),
	MOV_ECX(0),
	PLANT_SETANIMATION,
	RET,
};