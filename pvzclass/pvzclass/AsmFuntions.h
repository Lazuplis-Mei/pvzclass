#include <Windows.h>

#pragma region asm define

#define INUMBER(num) (byte)(num&0xFF),(byte)((num&0xFF00)>>8),(byte)((num&0xFF0000)>>16),(byte)((num&0xFF000000)>>24)
#define MOV_EAX(d) 0xB8,INUMBER(d)
#define MOV_ECX(d) 0xB9,INUMBER(d)
#define MOV_EBX(d) 0xBB,INUMBER(d)
#define MOV_ESI(d) 0xBE,INUMBER(d)
#define MOV_EDI(d) 0xBF,INUMBER(d)
#define PUSHAD 0x60
#define POPAD 0x61
#define PUSH(b) 0x6A,b
#define PUSHDWORD(d) 0x68,INUMBER(d)
#define CALL(d) 0xE8,INUMBER(d)
#define JMP(b) 0xEB,b
#define JMPFAR(d) 0xE9,INUMBER(d)
#define RET 0xC3
#define MOV_EAX_PTR(d) 0xA1,INUMBER(d)
#define MOV_PTR_ADDR_EAX 0xA3
#define MOV_PTR_ADDR_ECX(address) 0x89,0xD,INUMBER(address)

#define INVOKE(address) CALL(2),JMP(6),PUSHDWORD(address),RET
#define INVOKE_BYTE(address,b) PUSH(b),INVOKE(address)
#define INVOKE_DWORD(address,d) PUSHDWORD(d),INVOKE(address)
#define INVOKE_DWORD_DWORD_BYTE_BYTE(address,d1,d2,b1,b2) PUSH(b2),PUSH(b1),PUSHDWORD(d2),PUSHDWORD(d1),INVOKE(address)

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

#pragma endregion

extern byte __asm__set_MusicVolume[21];

extern byte __asm__InjectDll[200];

extern byte __asm_set__LevelScene[19];

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