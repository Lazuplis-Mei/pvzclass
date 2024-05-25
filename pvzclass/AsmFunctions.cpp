#include "AsmFunctions.h"

byte __asm__set_MusicVolume[]
{
	MOV_ECX(0),
	SET_MUSICVOLUME,
	RET
};

byte __asm__InjectDll[]
{
	LOADLIBRARYA, // 18 byte
	MOV_PTR_ADDR_EAX(0), // 5 byte
	RET
};

byte __asm__GetProcAddress[]
{
	INVOKE_DWORD_DWORD((int)GetProcAddress, 0, 0), // 23 byte
	MOV_PTR_ADDR_EAX(0), // 5 byte
	RET
};

byte __asm__Reanimation__Die[]
{
	MOV_ECX(0),
	REANIMATION_DIE,
	RET
};

byte __asm__Reanimation__AttachTo[]
{
	MOV_EUX(REG_ESI, 0),
	MOV_EUX(REG_EDI, 0),
	MOV_EUX(REG_EAX, 0),
	PUSH_EUX(REG_EAX),
	MOV_EUX(REG_EAX, 0),
	PUSH_EUX(REG_EAX),
	REANIM_ATTACHTO,
	ADD_ESP(8),
	MOV_PTR_ADDR_EAX(0),
	RET
};

byte __asm__Reanimation__Play[]
{
	MOV_EUX(REG_EAX, 0),
	PUSH_EUX(REG_EAX),
	MOV_EAX(0),
	MOV_ESI(0),	
	REANIM_PLAY,
	RET
};

byte __asm__Reanimation__AssignGroupToPrefix[]
{
	REANIMATION_ASSIGnGROUPPREFIX,
	RET
};

byte __asm__Reanimation__FindTrackIndex[]
{
	MOV_EUX(REG_EBX, 0),
	REANIM_FINDTRACKINDEX,
	MOV_PTR_ADDR_EAX(0),
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

byte __asm__HitBody[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	INVOKE(0x5312D0),
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

byte __asm__Zombie_ReanimShowPrefix[]
{
	MOV_EUX(REG_EAX,0),
	ZOMBIE_REANIMSHOWPREFIX,
	RET
};

byte __asm__Zombie__Remove[]
{
	MOV_ECX(0),
	ZOMBIE_REMOVE,
	RET
};

byte __asm__Zombie__RemoveWithLoot[]
{
	MOV_ECX(0),
	ZOMBIE_REMOVEWITHLOOT,
	RET
};

byte __asm__Zombie__UpdateSpeed[]
{
	MOV_ESI(0),
	ZOMBIE_UPDATESPEED,
	RET
};

byte __asm__CanDecelerate[]
{
	MOV_ESI(0),
	CANDELECERATE,
	MOV_PTR_ADDR_EAX(0),
	RET
};

byte __asm__Zombie_EffectedBy[]
{
	MOV_ESI(0),
	ZOMBIE_EFFECTEDBY,
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

byte __asm__Plant_CalcLayer[]
{
	MOV_ESI(0),
	PLANT_CALCLAYER,
	MOV_PTR_ADDR_EAX(0),
	RET
};

byte __asm__Plant_SetSleeping[]
{
	MOV_EAX(0),
	PLANT_SETSLEEPING,
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

byte __asm__Lawnmover_Die[]
{
	MOV_EUX(REG_EAX, 0),
	LAWNMOVER_DIE,
	RET,
};

byte __asm__Griditem__Remove[]
{
	MOV_EUX(REG_ESI, 0),
	GRIDITEM_REMOVE,
	RET
};

byte __asm__Vase_Open[]
{
	VASE_OPEN,
	RET
};

byte __asm__CardSlot__set_CardsCount[]
{
	MOV_EUX(REG_EAX, 0),
	MOV_EUX(REG_ESI, 0),
	CARDSLOT_SET_CARDSCOUNT,
	RET
};

byte __asm__ZenGarder_IsFull[]
{
	MOV_EUX(REG_ESI, 0),
	ZENGARDEN_ISFULL,
	MOV_PTR_ADDR_EAX(0),
	RET
};

byte __asm__ZenGarder_GetSnail[]
{
	MOV_EUX(REG_EBX, 0),
	ZENGARDER_GETSNAIL,
	MOV_PTR_ADDR_EAX(0),
	RET,
};