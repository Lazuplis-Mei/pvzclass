#include "MainFuntions.h"

byte __asm__set_MusicVolume[] =
{
	MOV_ECX(0),
	SET_MUSICVOLUME,
	RET
};

byte __asm__InjectDll[200] =
{
	LOADLIBRARYA,
	RET
};

byte __asm_set__LevelScene[] =
{
	MOV_ESI(0),
	SET_LEVELSCENE,
	RET
};

byte __asm__Win[] =
{
	MOV_ECX(0),
	WIN,
	RET
};

byte __asm__Hit[] =
{
	MOV_ESI(0),
	MOV_EAX(0),
	HIT,
	RET
};

byte __asm__Blast[] =
{
	MOV_ECX(0),
	BLAST,
	RET
};

byte __asm__Butter[] =
{
	MOV_EAX(0),
	BUTTER,
	RET
};

byte __asm__CreateEffect[] =
{
	CREATEEFFECT,
	RET
};

byte __asm__SetStatic[] =
{
	MOV_EAX_PTR(0),
	SETSTATIC,
	RET,
};

byte __asm__Shoot[] =
{
	SHOOT,
	MOV_PTR_ADDR_ECX(0),
	RET,
};