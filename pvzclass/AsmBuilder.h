#pragma once
#include<string>
#include "AsmFunctions.h"

typedef std::basic_string<byte> AsmCode;

enum class AsmJMPType
{
	jo = 0,
	jno,
	jb,
	jnb,
	je,
	jne,
	jna,
	ja,
	js,
	jns,
	jp,
	jnp,
	jl,
	jnl,
	jng,
	jg,
	jmp = 0x7B,
};

// Todo : Improve it.
class AsmBuilder
{
private:
	AsmCode code;
public:
	AsmBuilder()
	{
		code = AsmCode();
		code.reserve(100);
	};
	AsmBuilder(DWORD bytes)
	{
		code = AsmCode();
		code.reserve(bytes);
	}
	AsmBuilder(byte asmCode[]) : code(asmCode) {};
	AsmBuilder(AsmBuilder& builder) : code(builder.GetCode()) {};

	AsmCode GetCode()
	{
		return(this->code);
	}
	const byte* Output()
	{
		return(this->code.c_str());
	}

	//Todo: 测试是否有效。
	//@brief 删除代码尾端若干字节的代码。
	//@brief 可能删除不完整的代码。你应当在操作前确认删除代码的长度。
	//@param length 删除的字节数。
	void DeleteCode(int length)
	{
		if (this->code.length() <= length)
		{
			this->code = { 0 };
			code.reserve(100);
		}
		else
			this->code.erase(this->code.length() - length);
	}

	void PushAD()
	{
		this->code += {0x60};
	}
	void PopAD()
	{
		this->code += {0x61};
	}
	void Push(byte val)
	{
		this->code += {0x6A, val};
	}
	void PushDWORD(int val)
	{
		this->code += {0x68, INUMBER(val)};
	}
	void PushPTR(DWORD address)
	{
		this->code += {0xFF, 0x35, INUMBER(address)};
	}
	void PopPTR(DWORD address)
	{
		this->code += {0x8F, 5, INUMBER(address)};
	}
	void PushReg(byte reg)
	{
		reg += 0x50;
		this->code += {reg};
	}
	void PopReg(byte reg)
	{
		reg += 0x58;
		this->code += {reg};
	}
	void Call(int RVA)
	{
		this->code += {0xE8, INUMBER(RVA)};
	}
	void Jmp(AsmJMPType jump, byte RVA)
	{
		byte type = static_cast<byte>(jump);
		byte tmp_code[2] = {type + 0x70, RVA };
		this->code += tmp_code;
	}
	void JmpFar(AsmJMPType jump, int RVA)
	{
		if (jump == AsmJMPType::jmp)
			this->code += {0xE9, INUMBER(RVA)};
		else
		{
			byte type = static_cast<byte>(jump) + 0x80;
			this->code += {0x0F, type, INUMBER(RVA)};
		}
	}
	void Ret(byte dist)
	{
		if (dist == 0)
			this->code += {RET};
		else
			this->code += {0xC2, dist, 0};
	}
	void Nop()
	{
		this->code += {NOP};
	}

	void MovRegFromImm(byte reg, int val)
	{
		reg += 0xB8;
		this->code += {reg, INUMBER(val)};
	}
	void MovRegFromReg(byte reg_to, byte reg_from)
	{
		byte code = 0xC0 + reg_to * 8 + reg_from;
		this->code += {0xB8, code};
	}
	void MovRegFromMem(byte reg, DWORD address)
	{
		if(reg == REG_EAX)
			this->code += {MOV_EAX_PTR(address)};
		else
		{
			byte type = 5 + reg * 8;
			this->code += {0x8B, type, INUMBER(address)};
		}
	}
	void MovMemFromReg(DWORD address, byte reg)
	{
		if (reg == REG_EAX)
			this->code += {MOV_PTR_ADDR_EAX(address)};
		else
		{
			byte type = 5 + reg * 8;
			this->code += {0x89, type, INUMBER(address)};
		}
	}
	void MovMemFromImm(DWORD address, int val)
	{
		this->code += {MOV_PTR_ADDR(address, val)};
	}

#pragma region calculation

	void CalcRegWithImm(byte calc_type, byte reg, int val)
	{
		static byte codes;
		if (-128 <= val && val <= 127)
			this->code += {0x83, byte(0xC0 + (calc_type) * 8 + (reg)), byte(val)};
		else if (reg == REG_EAX)
			this->code += {byte(5 + (calc_type) * 8), INUMBER(val)};
		else
			this->code += {0x81, byte(0xC0 + (calc_type) * 8 + (reg)), INUMBER(val)};
	}

#pragma endregion

	void TestAlAl()
	{
		this->code += {TEST_AL_AL};
	}

	void Invoke(DWORD address)
	{
		this->code += {0xE8, INUMBER(2), 0xEB, 6, 0x68, INUMBER(address), 0xC3};
	}

};