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
#define JNZ(b) 0x75,b
#define JMPFAR(d) 0xE9,INUMBER(d)
#define RET 0xC3
#define RETN(v) 0xC2,v,0
#define MOV_EAX_EBX 0x8B,0xC3
#define MOV_EAX_PTR(d) 0xA1,INUMBER(d)
#define MOV_PTR_ADDR_EAX(address) 0xA3,INUMBER(address)
#define MOV_PTR_ADDR_ECX(address) 0x89,0xD,INUMBER(address)
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
#define INVOKE_DWORD_DWORD_BYTE_BYTE(address,d1,d2,b1,b2) PUSH(b2),PUSH(b1),PUSHDWORD(d2),PUSHDWORD(d1),INVOKE(address)
#define INVOKE_DWORD_DWORD_DWORD_DWORD(address,d1,d2,d3,d4) PUSHDWORD(d4),PUSHDWORD(d3),PUSHDWORD(d2),PUSHDWORD(d1),INVOKE(address)
#define INVOKE_BYTE_BYTE(address,b1,b2) PUSH(b2),PUSH(b1),INVOKE(address)
#define INVOKE_DWORD_BYTE_BYTE_BYTE(address,d,b1,b2,b3) PUSH(b3),PUSH(b2),PUSH(b1),PUSHDWORD(d),INVOKE(address)
#define INVOKE_DWORD_DWORD_BYTE_BYTE_BYTE(address,d1,d2,b1,b2,b3) PUSH(b3),PUSH(b2),PUSH(b1),PUSHDWORD(d2),PUSHDWORD(d1),INVOKE(address)
#define INVOKE_DWORD_BYTE_DWORD_DWORD_DWORD_BYTE_BYTE_BYTE(address,d1,b1,d2,d3,d4,b2,b3,b4) PUSH(b4),PUSH(b3),PUSH(b2),PUSHDWORD(d4),PUSHDWORD(d3),PUSHDWORD(d2),PUSH(b1),PUSHDWORD(d1),INVOKE(address)

#pragma endregion

#pragma region functions

#define SET_MUSICVOLUME INVOKE_BYTE(0x554D00,0)
#define LOADLIBRARYA INVOKE_DWORD((int)LoadLibraryA,0)
#define SET_LEVELSCENE INVOKE(0x40A160)
#define WIN INVOKE(0x40C3E0)
#define HIT INVOKE_DWORD(0x5317C0,0)
#define BLAST INVOKE(0x532B70)
#define BUTTER INVOKE(0x5326D0)
#define CREATEEFFECT INVOKE_DWORD(0x4666A0,0)
#define SETSTATIC INVOKE_DWORD(0x42A530,0)
#define SHOOT INVOKE_DWORD_DWORD_BYTE_BYTE(0x466E00,0,0,0,0)
#define ONFIRE INVOKE(0x46ECB0)
#define COLLECT INVOKE(0x432060)
#define GAMECLICK INVOKE_DWORD(0x539390,0)
#define MUSICSETTYPE INVOKE(0x45B750)
#define ZOMBIE_SETANIMATION INVOKE_DWORD_BYTE_BYTE_BYTE(0x528B00,0,0,14,0)
#define PLANT_SETANIMATION INVOKE_DWORD_BYTE_BYTE(0x45FD90,0,0,0)

#pragma endregion

extern byte __asm__set_MusicVolume[21];

extern byte __asm__InjectDll[200];

extern byte __asm__set__LevelScene[19];

extern byte __asm__Win[19];

extern byte __asm__Hit[29];

extern byte __asm__Blast[19];

extern byte __asm__Butter[19];

extern byte __asm__CreateEffect[19];

extern byte __asm__SetStatic[24];

extern byte __asm__Shoot[34];

extern byte __asm__OnFire[19];

extern  byte __asm__Collect[19];

extern byte __asm__GameClick[34];

extern byte __asm__Music__set_Type[24];

extern byte __asm__Zombie__setAnimation[100];

extern byte __asm__Plant__setAnimation[100];