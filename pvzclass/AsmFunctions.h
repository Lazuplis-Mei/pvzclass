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
#define INVOKE_DWORD_BYTE(address,d,b) PUSH(b),PUSHDWORD(d),INVOKE(address)
#define INVOKE_DWORD_BYTE_BYTE(address,d,b1,b2) PUSH(b2),PUSH(b1),PUSHDWORD(d),INVOKE(address)
#define INVOKE_DWORD_BYTE_DWORD(address,d1,b,d2) PUSHDWORD(d2),PUSH(b),PUSHDWORD(d1),INVOKE(address)
#define INVOKE_DWORD_DWORD(address,d1,d2) PUSHDWORD(d2),PUSHDWORD(d1),INVOKE(address)
#define INVOKE_DWORD_DWORD_BYTE(address,d1,d2,b) PUSH(b),PUSHDWORD(d2),PUSHDWORD(d1),INVOKE(address)
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
#define JOFAR(d) 0xF,0x80,INUMBER(d)
#define JNOFAR(d) 0xF,0x81,INUMBER(d)
#define JBFAR(d) 0xF,0x82,INUMBER(d)
#define JNBFAR(d) 0xF,0x83,INUMBER(d)
#define JEFAR(d) 0xF,0x84,INUMBER(d)
#define JNEFAR(d) 0xF,0x85,INUMBER(d)
#define JNAFAR(d) 0xF,0x86,INUMBER(d)
#define JAFAR(d) 0xF,0x87,INUMBER(d)
#define JSFAR(d) 0xF,0x88,INUMBER(d)
#define JNSFAR(d) 0xF,0x89,INUMBER(d)
#define JPFAR(d) 0xF,0x8A,INUMBER(d)
#define JNPFAR(d) 0xF,0x8B,INUMBER(d)
#define JLFAR(d) 0xF,0x8C,INUMBER(d)
#define JNLFAR(d) 0xF,0x8D,INUMBER(d)
#define JNGFAR(d) 0xF,0x8E,INUMBER(d)
#define JGFAR(d) 0xF,0x8F,INUMBER(d)
#define TEST_AL_AL 0x84,0xC0

#define PUSH_EUX(ux) 0x50+(ux)
#define POP_EUX(ux) 0x58+(ux)

#define POP_PTR(address) 0x8F,5,INUMBER(address)

#define MOV_EUX(ux,d) 0xB8+(ux),INUMBER(d)
#define MOV_EUX_EVX(ux,vx) 0x8B,0xC0+(ux)*8+(vx)
#define MOV_EUX_PTR_ADDR(ux,d) 0x8B,5+(ux)*8,INUMBER(d)
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
#define TEST_EUX_EVX(ux,vx) 0x85,0xC0+(ux)+(vx)*8

#define CALL_EUX(ux) 0xFF,0xD0+(ux)

//Not for esp
#define PUSH_PTR_EUX_ADD_V(ux,v) 0xFF,0x70+(ux),v
#define PUSH_PTR_EUX_ADD(ux,v) 0xFF,0xB0+(ux),INUMBER(v)
#define POP_PTR_EUX_ADD_V(ux,v) 0x8F,0x40+(ux),v
#define POP_PTR_EUX_ADD(ux,v) 0x8F,0x80+(ux),INUMBER(v)

#define MOV_EUX_PTR_EVX_ADD_V(ux,vx,b) 0x8B,0x40+(ux)*8+(vx),b
#define MOV_EUX_PTR_EVX_ADD(ux,vx,d) 0x8B,0x80+(ux)*8+(vx),INUMBER(d)
#define MOV_PTR_EUX_ADD_V(ux,v1,v2) 0xC7,0x40+(ux),v1,INUMBER(v2)
#define MOV_PTR_EUX_ADD(ux,v1,v2) 0xC7,0x80+(ux),INUMBER(v1),INUMBER(v2)
#define CMP_PTR_EUX_ADD_V_V(ux,v1,v2) 0x83,0x78+(ux),v1,v2
#define CMP_PTR_EUX_ADD__V(ux,v1,v2) 0x83,0xB8+(ux),INUMBER(v1),v2
#define CMP_PTR_EUX_ADD(ux,v1,v2) 0x81,0xB8+(ux),INUMBER(v1),INUMBER(v2)
#define ADD_EUX_PTR_EVX_ADD_V(ux,vx,b) 3,0x40+(ux)*8+(vx),b
#define ADD_PTR_EUX_ADD_V_EVX(ux,b,vx) 1,0x40+(ux)+(vx)*8,b
#define ADD_PTR_EUX_ADD_V_V(ux,v1,v2) 0x83,0x40+(ux),v1,v2
#define ADD_PTR_EUX_ADD(ux,v1,v2) 0x81,0x80+(ux),INUMBER(v1),INUMBER(v2)
#define SUB_PTR_EUX_ADD_V_V(ux,v1,v2) 0x83,0x68+(ux),v1,v2
#define SUB_PTR_EUX_ADD(ux,v1,v2) 0x81,0xA8+(ux),INUMBER(v1),INUMBER(v2)

#define MOV_BYTE_PTR_EUX_ADD_V_V(ux,v1,v2) 0xC6,0x40+(ux),v1,v2
#define CMP_BYTE_PTR_EUX_ADD__V(ux,v1,v2) 0x80,0xB8+(ux),INUMBER(v1),v2

#define INC_PTR_EUX_ADD(ux,v) 0xFF,0x80+(ux),INUMBER(v)
//End not

#pragma endregion

#pragma region asm eax

#define ADD_EAX_DWORD(d) 5,INUMBER(d)
#define CMP_EAX_DWORD(d) 0x3D,INUMBER(d)

#pragma endregion

#pragma region asm esp

#define PUSH_PTR_ESP_ADD_V(v) 0xFF,0x74,0x24,v
#define PUSH_PTR_ESP_ADD(v) 0xFF,0xB4,0x24,INUMBER(v)
#define POP_PTR_ESP_ADD_V(v) 0x8F,0x44,0x24,v
#define POP_PTR_ESP_ADD(v) 0x8F,0x84,0x24,INUMBER(v)

#define MOV_PTR_ESP_ADD_V(v1,v2) 0xC7,0x44,0x24,v1,INUMBER(v2)
#define MOV_PTR_ESP_ADD(v1,v2) 0xC7,0x84,0x24,INUMBER(v1),INUMBER(v2)

#define CMP_PTR_ESP_ADD_V_V(v1,v2) 0x83,0x7C,0x24,v1,v2
#define CMP_PTR_ESP_ADD__V(v1,v2) 0x83,0xBC,0x24,INUMBER(v1),v2

#define MOV_BYTE_PTR_ESP_ADD_V_V(v1,v2) 0xC6,0x44,0x24,v1,v2
#define CMP_BYTE_PTR_ESP_ADD__V(v1,v2) 0x80,0xBC,0x24,INUMBER(v1),v2

#define ADD_EUX_PTR_ESP_ADD_V(ux,b) 3,0x44+(ux)*8+,0x24,b

#define INC_PTR_ESP_ADD(v) 0xFF,0x84,0x24,INUMBER(v)

#pragma endregion

#pragma region asm float

#define F_ST0 0
#define F_ST1 1
#define F_ST2 2
#define F_ST3 3
#define F_ST4 4
#define F_ST5 5
#define F_ST6 6
#define F_ST7 7

#define FLD1 0xD9,0XE8
#define FLDL2T 0xD9,0XE9
#define FLDL2E 0xD9,0XEA
#define FLDPI 0xD9,0xEB
#define FLDLG2 0xD9,0XEC
#define FLDLN2 0xD9,0XED
#define FLDZ 0xD9,0XEE
#define FNOP 0xD9,0xD0
#define FCHS 0xD9,0xE0
#define FABSc 0xD9,0xE1
#define F2XM1 0xD9,0XF0
#define FRNDINT 0xD9,0xFC
#define FSQRT 0xD9,0xFA
#define FSIN 0xD9,0xFA
#define FCOS 0xD9,0xFA

#define FLD_ST(st) 0xD9,0xC0+(st)
#define FST_ST(st) 0xDD,0xD0+(st)
#define FSTP_ST(st) 0xDD,0xDC+(st)
#define FXCH_ST(st) 0xD9,0xC8+(st)
#define FADD_STZ_ST(st) 0xD8,0xC0+(st)
#define FADD_ST_STZ(st) 0xDC,0xC0+(st)
#define FMUL_STZ_ST(st) 0xD8,0xC8+(st)
#define FMUL_ST_STZ(st) 0xDC,0xC8+(st)
#define FSUB_STZ_ST(st) 0xD8,0xE0+(st)
#define FSUB_ST_STZ(st) 0xDC,0xE8+(st)
#define FSUBR_STZ_ST(st) 0xD8,0xE8+(st)
#define FSUBR_ST_STZ(st) 0xDC,0xE0+(st)
#define FDIV_STZ_ST(st) 0xD8,0xF0+(st)
#define FDIV_ST_STZ(st) 0xDC,0xF8+(st)
#define FDIVR_STZ_ST(st) 0xD8,0xF8+(st)
#define FDIVR_ST_STZ(st) 0xDC,0xF0+(st)

#define FLD_PTR_ADDR(address) 0xD9,5,INUMBER(address)
#define FILD_PTR_ADDR(address) 0xDB,5,INUMBER(address)
#define FST_PTR_ADDR(address) 0xD9,0x15,INUMBER(address)
#define FSTP_PTR_ADDR(address) 0xD9,0x1D,INUMBER(address)
#define FIST_PTR_ADDR(address) 0xDB,0x15,INUMBER(address)
#define FISTP_PTR_ADDR(address) 0xDB,0x1D,INUMBER(address)
#define FADD_PTR_ADDR(address) 0xD8,5,INUMBER(address)
#define FMUL_PTR_ADDR(address) 0xD8,0x0D,INUMBER(address)
#define FSUB_PTR_ADDR(address) 0xD8,0x25,INUMBER(address)
#define FSUBR_PTR_ADDR(address) 0xD8,0x2D,INUMBER(address)
#define FDIV_PTR_ADDR(address) 0xD8,0x35,INUMBER(address)
#define FDIVR_PTR_ADDR(address) 0xD8,0x3D,INUMBER(address)
#define FISUB_PTR_ADDR(address) 0xDA,0x25,INUMBER(address)
#define FISUBR_PTR_ADDR(address) 0xDA,0x2D,INUMBER(address)

//Not for esp
#define FLD_PTR_EUX_ADD_V(ux,b) 0xD9,0x40+(ux),b
#define FLD_PTR_EUX_ADD(ux,d) 0xD9,0x80+(ux),INUMBER(d)
#define FST_PTR_EUX_ADD_V(ux,b) 0xD9,0x50+(ux),b
#define FST_PTR_EUX_ADD(ux,d) 0xD9,0x90+(ux),INUMBER(d)
#define FSTP_PTR_EUX_ADD_V(ux,b) 0xD9,0x58+(ux),b
#define FSTP_PTR_EUX_ADD(ux,d) 0xD9,0x98+(ux),INUMBER(d)
#define FILD_PTR_EUX_ADD_V(ux,b) 0xDB,0x40+(ux),b
#define FILD_PTR_EUX_ADD(ux,d) 0xDB,0x80+(ux),INUMBER(d)
#define FIST_PTR_EUX_ADD_V(ux,b) 0xDB,0x50+(ux),b
#define FIST_PTR_EUX_ADD(ux,d) 0xDB,0x90+(ux),INUMBER(d)
#define FISTP_PTR_EUX_ADD_V(ux,b) 0xDB,0x58+(ux),b
#define FISTP_PTR_EUX_ADD(ux,d) 0xDB,0x98+(ux),INUMBER(d)
#define FADD_PTR_EUX_ADD_V(ux,b) 0xD8,0x40+(ux),b
#define FADD_PTR_EUX_ADD(ux,d) 0xD8,0x80+(ux),INUMBER(d)
#define FMUL_PTR_EUX_ADD_V(ux,b) 0xD8,0x48+(ux),b
#define FMUL_PTR_EUX_ADD(uz,d) 0xD8,0x88+(ux),INUMBER(d)
#define FSUB_PTR_EUX_ADD_V(ux,b) 0xD8,0x60+(ux),b
#define FSUB_PTR_EUX_ADD(ux,d) 0xD8,0xA0+(ux),INUMBER(d)
#define FSUBR_PTR_EUX_ADD_V(ux,b) 0xD8,0x68+(ux),b
#define FSUBR_PTR_EUX_ADD(ux,d) 0xD8,0xA8+(ux),INUMBER(d)
#define FISUB_PTR_EUX_ADD_V(ux,b) 0xDA,0x60+(ux),b
#define FISUB_PTR_EUX_ADD(ux,d) 0xDA,0xA0+(ux),INUMBER(d)
#define FISUBR_PTR_EUX_ADD_V(ux,b) 0xDA,0x68+(ux),b
#define FISUBR_PTR_EUX_ADD(ux,d) 0xDA,0xA8+(ux),INUMBER(d)
#define FDIV_PTR_EUX_ADD_V(ux,b) 0xD8,0x70+(ux),b
#define FDIV_PTR_EUX_ADD(ux,d) 0xD8,0xB0+(ux),INUMBER(d)
#define FDIVR_PTR_EUX_ADD_V(ux,b) 0xD8,0x78+(ux),b
#define FDIVR_PTR_EUX_ADD(ux,d) 0xD8,0xB8+(ux),INUMBER(d)
//End not

#define FLD_PTR_ESP_ADD_V(b) 0xD9,0x44,0x24,b
#define FLD_PTR_ESP_ADD(d) 0xD9,0x84,0x24,INUMBER(d)
#define FST_PTR_ESP_ADD_V(b) 0xD9,0x54,0x24,b
#define FST_PTR_ESP_ADD(d) 0xD9,0x94,0x24,INUMBER(d)
#define FSTP_PTR_ESP_ADD_V(b) 0xD9,0x5C,0x24,b
#define FSTP_PTR_ESP_ADD(d) 0xD9,0x9C,0x24,INUMBER(d)
#define FILD_PTR_ESP_ADD_V(b) 0xDB,0x44,0x24,b
#define FILD_PTR_ESP_ADD(d) 0xDB,0x84,0x24,INUMBER(d)
#define FIST_PTR_ESP_ADD_V(b) 0xDB,0x54,0x24,b
#define FIST_PTR_ESP_ADD(d) 0xDB,0x94,0x24,INUMBER(d)
#define FISTP_PTR_ESP_ADD_V(b) 0xDB,0x5C,0x24,b
#define FISTP_PTR_ESP_ADD(d) 0xDB,0x9C,0x24,INUMBER(d)
#define FADD_PTR_ESP_ADD_V(b) 0xD8,0x44,0x24,b
#define FADD_PTR_ESP_ADD(d) 0xD8,0x84,0x24,INUMBER(d)
#define FMUL_PTR_ESP_ADD_V(b) 0xD8,0x4C,0x24,b
#define FMUL_PTR_ESP_ADD(d) 0xD8,0x8C,0x24,INUMBER(d)
#define FSUB_PTR_ESP_ADD_V(b) 0xD8,0x64,0x24,b
#define FSUB_PTR_ESP_ADD(d) 0xD8,0xA4,0x24,INUMBER(d)
#define FSUBR_PTR_ESP_ADD_V(b) 0xD8,0x6C,0x24,b
#define FSUBR_PTR_ESP_ADD(d) 0xD8,0xAC,0x24,INUMBER(d)
#define FISUB_PTR_ESP_ADD_V(b) 0xDA,0x64,0x24,b
#define FISUB_PTR_ESP_ADD(d) 0xDA,0xA4,0x24,INUMBER(d)
#define FISUBR_PTR_ESP_ADD_V(b) 0xDA,0x6C,0x24,b
#define FISUBR_PTR_ESP_ADD(d) 0xDA,0xAC,0x24,INUMBER(d)
#define FDIV_PTR_ESP_ADD_V(b) 0xD8,0x74,0x24,b
#define FDIV_PTR_ESP_ADD(d) 0xD8,0xB4,0x24,INUMBER(d)
#define FDIVR_PTR_ESP_ADD_V(b) 0xD8,0x7C,0x24,b
#define FDIVR_PTR_ESP_ADD(d) 0xD8,0xBC,0x24,INUMBER(d)

#pragma endregion

#pragma region functions

#define SET_MUSICVOLUME INVOKE_BYTE(0x554D00,0)
#define LOADLIBRARYA INVOKE_DWORD((int)LoadLibraryA,0)
#define REANIMATION_DIE INVOKE(0x4733F0)
#define REANIMATION_ASSIGnGROUPPREFIX INVOKE_DWORD_DWORD_BYTE(0x473A40,0,0,0)
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
#define VASE_OPEN INVOKE_DWORD_DWORD(0x429AC0,0,0)
#define CARDSLOT_SET_CARDSCOUNT INVOKE(0x489CD0)
#define ZENGARDEN_ISFULL INVOKE_BYTE(0x51D740,0)
#define ZENGARDER_GETSNAIL INVOKE(0x520CF0)

#pragma endregion

extern byte __asm__set_MusicVolume[21];

extern byte __asm__InjectDll[200];

extern byte __asm__Reanimation__Die[19];

extern byte __asm__Reanimation__AssignGroupToPrefix[26];

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

extern byte __asm__ZenGarder_GetSnail[24];

extern byte __asm__Vase_Open[24];