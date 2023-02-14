#include <Windows.h>

#pragma region asm define

#define INUMBER(num) (byte)(num&0xFF),(byte)((num&0xFF00)>>8),(byte)((num&0xFF0000)>>16),(byte)((num&0xFF000000)>>24)
#define MOV_EAX(d) 0xB8,INUMBER(d)
#define MOV_ECX(d) 0xB9,INUMBER(d)
#define MOV_EBX(d) 0xBB,INUMBER(d)
#define MOV_ESI(d) 0xBE,INUMBER(d)
#define MOV_EDI(d) 0xBF,INUMBER(d)
#define POP_EBX 0x5B
#define PUSHAD 0x60
#define POPAD 0x61
#define PUSH(b) 0x6A,b
#define PUSH_PTR(address) 0xFF,0x35,INUMBER(address)
#define PUSHDWORD(d) 0x68,INUMBER(d)
#define CALL(d) 0xE8,INUMBER(d)
#define JMP(b) 0xEB,b
#define JMPFAR(d) 0xE9,INUMBER(d)
#define RET 0xC3
#define RETN(v) 0xC2,v,0
#define NOP 0x90
#define MOV_EAX_EBX 0x8B,0xC3
#define MOV_EAX_PTR(d) 0xA1,INUMBER(d)
#define MOV_PTR_ADDR_EAX(address) 0xA3,INUMBER(address)
#define MOV_PTR_ADDR_ECX(address) 0x89,0xD,INUMBER(address)
#define MOV_PTR_ADDR_ESI(address) 0x89,0x35,INUMBER(address)
#define MOV_ECX_PTR_ADDR(address) 0x8B,0xD,INUMBER(address)
#define MOV_PTR_EAX_ADD(v1,v2) 0xC7,0x40,v1,INUMBER(v2)
#define FILD_PTR(address) 0xDB,5,INUMBER(address)
#define FDIV_PTR(address) 0xD8,0x35,INUMBER(address)
#define FSTP_PTR_EAX_ADD(v) 0xD9,0x58,v
#define ADD_ESP(v) 0x83,0xC4,v
#define LEA_ECX_ESP_ADD(v) 0x8D,0x4C,0x24,v
#define LEA_EDX_ESP_ADD(v) 0x8D,0x54,0x24,v
#define MOV_PTR_ESI_ADD(v1,v2) 0xC7,0x86,INUMBER(v1),INUMBER(v2)
#define MOV_PTR_EAX_ADD_V_ECX(v) 0x89,0x48,v
#define MOV_PTR_EAX_ADD_V_V(v1,v2) 0xC7,0x40,v1,INUMBER(v2)

#define INVOKE(address) CALL(2),JMP(6),PUSHDWORD(address),RET
#define INVOKE_BYTE(address,b) PUSH(b),INVOKE(address)
#define INVOKE_DWORD(address,d) PUSHDWORD(d),INVOKE(address)
#define INVOKE_DWORD_BYTE_BYTE(address,d,b1,b2) PUSH(b2),PUSH(b1),PUSHDWORD(d),INVOKE(address)
#define INVOKE_DWORD_BYTE_DWORD(address,d1,b,d2) PUSHDWORD(d2),PUSH(b),PUSHDWORD(d1),INVOKE(address)
#define INVOKE_DWORD_DWORD_DWORD(address,d1,d2,d3) PUSHDWORD(d3),PUSHDWORD(d2),PUSHDWORD(d1),INVOKE(address)
#define INVOKE_DWORD_DWORD_BYTE_BYTE(address,d1,d2,b1,b2) PUSH(b2),PUSH(b1),PUSHDWORD(d2),PUSHDWORD(d1),INVOKE(address)
#define INVOKE_DWORD_DWORD_DWORD_DWORD(address,d1,d2,d3,d4) PUSHDWORD(d4),PUSHDWORD(d3),PUSHDWORD(d2),PUSHDWORD(d1),INVOKE(address)
#define INVOKE_BYTE_BYTE(address,b1,b2) PUSH(b2),PUSH(b1),INVOKE(address)
#define INVOKE_DWORD_BYTE_BYTE_BYTE(address,d,b1,b2,b3) PUSH(b3),PUSH(b2),PUSH(b1),PUSHDWORD(d),INVOKE(address)
#define INVOKE_DWORD_DWORD_BYTE_BYTE_BYTE(address,d1,d2,b1,b2,b3) PUSH(b3),PUSH(b2),PUSH(b1),PUSHDWORD(d2),PUSHDWORD(d1),INVOKE(address)
#define INVOKE_DWORD_BYTE_DWORD_DWORD_DWORD_BYTE_BYTE_BYTE(address,d1,b1,d2,d3,d4,b2,b3,b4) PUSH(b4),PUSH(b3),PUSH(b2),PUSHDWORD(d4),PUSHDWORD(d3),PUSHDWORD(d2),PUSH(b1),PUSHDWORD(d1),INVOKE(address)

#pragma endregion

#pragma region asm extra

#define REG_EAX 0
#define REG_ECX 1
#define REG_EDX 2
#define REG_EBX 3
#define REG_ESP 4
#define REG_EBP 5
#define REG_ESI 6
#define REG_EDI 7

#define JNO(b) 0x71,b
#define JB(b) 0x72,b
#define JNB(b) 0x73,b
#define JE(b) 0x74,b
#define JNZ(b) 0x75,b
#define JNA(b) 0x76,b
#define JA(b) 0x77,b
#define JS(b) 0x78,b
#define JNS(b) 0x79,b
#define JP(b) 0x7A,b
#define JNP(b) 0x7B,b
#define JL(b) 0x7C,b
#define JNL(b) 0x7D,b
#define JNG(b) 0x7E,b
#define JG(b) 0x7F,b
#define TEST_AL_AL 0x84,0xC0

#define PUSH_EUX(ux) 0x50+(ux)
#define POP_EUX(ux) 0x58+(ux)

#define MOV_EUX(ux,d) 0xB8+(ux),INUMBER(d)
#define MOV_EUX_EVX(ux,vx) 0x8B,0xC0+(ux)*8+(vx)
#define MOV_PTR_ADDR_EUX(ux,address) 0x89,5+(ux)*8,INUMBER(address)
#define MOV_PTR_ADDR(address,d) 0xC7,5,INUMBER(address),INUMBER(d)
#define CMP_EUX(ux,b) 0x83,0xF8+(ux),b
#define CMP_EUX_DWORD(ux,d) 0x81,0xF8+(ux),INUMBER(d)

#define ADD_EUX(ux,b) 0x83,0xC0+(ux),b
#define ADD_EUX_DWORD(ux,d) 0x81,0xC0+(ux),INUMBER(d)
#define ADD_EUX_EVX(ux,vx) 1,0xC0+(ux)+(vx)*8
#define SUB_EUX(ux,b) 0x83,0xE8+(ux),b
#define SUB_EUX_DWORD(ux,d) 0x81,0xE8+(ux),INUMBER(d)
#define SUB_EUX_EVX(ux,vx) 0x29,0xC0+(ux)+(vx)*8
#define IMUL_EUX_EVX_V(ux,vx,b) 0x6B,0xC0+(ux)*8+(vx),b
#define IMUL_EUX_EVX_DWORD(ux,vx,d) 0x69,0xC0+(ux)*8+(vx),INUMBER(d)

#define AND_EUX(ux,b) 0x83,0xE0+(ux),b
#define AND_EUX_DWORD(ux,d) 0x81,0xE0+(ux),INUMBER(d)
#define XOR_EUX_EVX(ux,vx) 0x31,0xC0+(ux)+(vx)*8
#define SHL_EUX(ux,b) 0xC1,0xE0+(ux),b
#define SHR_EUX(ux,b) 0xC1,0xE8+(ux),b
#define SAL_EUX(ux,b) 0xC1,0xF0+(ux),b
#define SAR_EUX(ux,b) 0xC1,0xF8+(ux),b

//Not for esp
#define MOV_EUX_PTR_EVX_ADD_V(ux,vx,b) 0x8B,0x40+(ux)*8+(vx),b//vx,NFesp
#define MOV_EUX_PTR_EVX_ADD(ux,vx,d) 0x8B,0x80+(ux)*8+(vx),INUMBER(d)//vx,NFesp
#define MOV_PTR_EUX_ADD_V(ux,v1,v2) 0xC7,0x40+(ux),v1,INUMBER(v2)
#define MOV_PTR_EUX_ADD(ux,v1,v2) 0xC7,0x80+(ux),INUMBER(v1),INUMBER(v2)
#define CMP_PTR_EUX_ADD_V_V(ux,v1,v2) 0x83,0x78+(ux),v1,v2
#define CMP_PTR_EUX_ADD(ux,v1,v2) 0x81,0xB8+(ux),INUMBER(v1),INUMBER(v2)
#define ADD_PTR_EUX_ADD_V_V(ux,v1,v2) 0x83,0x40+(ux),v1,v2
#define ADD_PTR_EUX_ADD(ux,v1,v2) 0x81,0x80+(ux),INUMBER(v1),INUMBER(v2)
#define SUB_PTR_EUX_ADD_V_V(ux,v1,v2) 0x83,0x68+(ux),v1,v2
#define SUB_PTR_EUX_ADD(ux,v1,v2) 0x81,0xA8+(ux),INUMBER(v1),INUMBER(v2)
//End not

#pragma endregion

#pragma region asm eax

#define ADD_EAX_DWORD(d) 5,INUMBER(d)

#pragma endregion

#pragma region functions

#define SET_MUSICVOLUME INVOKE_BYTE(0x554D00,0)
#define LOADLIBRARYA INVOKE_DWORD((int)LoadLibraryA,0)
#define REANIMATION_DIE INVOKE(0x4733F0)
#define SET_LEVELSCENE INVOKE(0x40A160)
#define WIN INVOKE(0x40C3E0)
#define LOSE INVOKE(0x413400)
#define HIT INVOKE_DWORD(0x5317C0,0)
#define BLAST INVOKE(0x532B70)
#define BUTTER INVOKE(0x5326D0)
#define DECELERATE INVOKE_BYTE(0x530950, 0)
#define FROZE INVOKE(0x5323C0)
#define HYPNOTIZE INVOKE(0x52FA60)
#define ZOMBIE_REMOVE INVOKE(0x530510)
#define CANDELECERATE INVOKE(0x531990)
#define CREATEEFFECT INVOKE_DWORD(0x4666A0,0)
#define SETSTATIC INVOKE_DWORD(0x42A530,0)
#define SMASH INVOKE_DWORD(0x462B80,0)
#define PLANT_REMOVE INVOKE_DWORD(0x4679B0,0)
#define SHOOT INVOKE_DWORD_DWORD_BYTE_BYTE(0x466E00,0,0,0,0)
#define ONFIRE INVOKE(0x46ECB0)
#define PROJECTILE_REMOVE INVOKE(0x46EB20)
#define COLLECT INVOKE(0x432060)
#define PLANTABLE INVOKE_DWORD_BYTE_DWORD(0x40E020,0,0,0)
#define GAMECLICK INVOKE_DWORD(0x539390,0)
#define MUSICSETTYPE INVOKE(0x45B750)
#define ZOMBIE_SETANIMATION INVOKE_DWORD_BYTE_BYTE_BYTE(0x528B00,0,0,14,0)
#define PLANT_SETANIMATION INVOKE_DWORD_BYTE_BYTE(0x45FD90,0,0,0)
#define GRIDITEM_REMOVE INVOKE(0x44D000)
#define CARDSLOT_SET_CARDSCOUNT INVOKE(0x489CD0)
#define ZENGARDEN_ISFULL INVOKE_BYTE(0x51D740,0)

#pragma endregion

extern byte __asm__set_MusicVolume[21];

extern byte __asm__InjectDll[200];

extern byte __asm__Reanimation__Die[19];

extern byte __asm__set__LevelScene[19];

extern byte __asm__Win[19];

extern byte __asm__Lose[21];

extern byte __asm__Hit[29];

extern byte __asm__Blast[19];

extern byte __asm__Butter[19];

extern byte __asm__Decelerate[21];

extern byte __asm__Froze[19];

extern byte __asm__Hypnotize[19];

extern byte __asm__Zombie__Remove[19];

extern byte __asm__CanDecelerate[24];

extern byte __asm__CreateEffect[19];

extern byte __asm__SetStatic[24];

extern byte __asm__Smash[19];

extern byte __asm__Plant__Remove[19];

extern byte __asm__Shoot[34];

extern byte __asm__OnFire[19];

extern byte __asm__Projectile__Remove[19];

extern byte __asm__Collect[19];

extern byte __asm__Plantable[36];

extern byte __asm__GameClick[34];

extern byte __asm__Music__set_Type[24];

extern byte __asm__Zombie__setAnimation[100];

extern byte __asm__Plant__setAnimation[100];

extern byte __asm__Griditem__Remove[19];

extern byte __asm__CardSlot__set_CardsCount[24];

extern byte __asm__ZenGarder_IsFull[26];