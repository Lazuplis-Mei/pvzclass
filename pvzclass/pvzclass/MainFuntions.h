#pragma once

#pragma region asm define

#define INUMBER(num) num&0xFF,(num&0xFF00)>>8,(num&0xFF0000)>>16,(num&0xFF000000)>>24
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
#define MOV_EAX_PTR 0xA1
#define MOV_PTR_ADDR_EAX 0xA3

#define INVOKE(address) CALL(2),JMP(6),PUSHDWORD(address),RET
#define INVOKE_1(address,b) PUSH(b),INVOKE(address)

#pragma endregion

#pragma region functions

#define SETMUSICVOLUME INVOKE_1(0x554D00,0)

#pragma endregion

byte __asm__set_MusicVolume[] = {
	MOV_ECX(0),
	SETMUSICVOLUME,
	RET
};

byte __asm__InjectDll[200] = {
	PUSHDWORD(0),
	INVOKE((int)LoadLibraryA),
	RET
};