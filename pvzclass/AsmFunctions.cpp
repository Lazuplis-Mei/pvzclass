#include "AsmFunctions.h"

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

byte __asm__Lose[]
{
	PUSH(0),
	PUSHDWORD(0),
	LOSE,
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

byte __asm__Decelerate[]
{
	MOV_EAX(0),
	DECELERATE,
	RET
};

byte __asm__Froze[]
{
	MOV_EAX(0),
	FROZE,
	RET
};


byte __asm__Hypnotize[]
{
	MOV_ESI(0),
	HYPNOTIZE,
	RET
};

byte __asm__Zombie__Remove[]
{
	MOV_ECX(0),
	ZOMBIE_REMOVE,
	RET
};

byte __asm__CanDecelerate[]
{
	MOV_ESI(0),
	CANDELECERATE,
	MOV_PTR_ADDR_EAX(0),
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

byte __asm__Smash[]
{
	SMASH,
	RET
};

byte __asm__Plant__Remove[]
{
	PLANT_REMOVE,
	RET
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

byte __asm__Projectile__Remove[]
{
	MOV_EAX(0),
	PROJECTILE_REMOVE,
	RET
};

byte __asm__Collect[]
{
	MOV_ECX(0),
	COLLECT,
	RET,
};

byte __asm__Plantable[]
{
	MOV_EUX(REG_EAX, 0),
	PLANTABLE,
	MOV_PTR_ADDR_EAX(0),
	RET
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

byte __asm__Griditem__Remove[]
{
	MOV_EUX(REG_ESI, 0),
	GRIDITEM_REMOVE,
	RET
};

byte __asm__CardSlot__set_CardsCount[]
{
	MOV_EUX(REG_EAX, 0),
	MOV_EUX(REG_ESI, 0),
	CARDSLOT_SET_CARDSCOUNT,
	RET
};