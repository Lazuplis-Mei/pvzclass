#pragma once

#pragma region asm define

#define MOV_EAX 0xB8
#define MOV_ECX 0xB9
#define MOV_EBX 0xBB
#define MOV_ESI 0xBE
#define MOV_EDI 0xBF
#define PUSHAD 0x60
#define POPAD 0x61
#define PUSH 0x6A
#define PUSHDWORD 0x68
#define CALL 0xE8
#define JMP 0xEB
#define JMPFAR 0xE9
#define RET 0xC3
#define MOV_EAX_PTR 0xA1
#define MOV_PTR_ADDR_EAX 0xA3

#define ADDRESS(hh,hl,lh,ll) ll,lh,hl,hh
#define VALUE(num) num,0,0,0

#pragma endregion

#pragma region functions

#define SETMUSICVolume PUSHDWORD,ADDRESS(0,0x55,0x4D,0)




#pragma endregion

byte __asm__set_MusicVolume[] = {
	PUSH, 0,
	MOV_ECX, VALUE(0),
	CALL, VALUE(2),
	JMP, 6,
	SETMUSICVolume,
	RET,
	RET
};