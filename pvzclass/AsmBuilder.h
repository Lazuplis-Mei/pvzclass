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
		code.resize(100);
	};
	AsmBuilder(DWORD bytes)
	{
		code = AsmCode();
		code.resize(bytes);
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
			this->code += {0xC3};
		else
			this->code += {0xC2, dist, 0};
	}
	void Nop()
	{
		this->code += {0x90};
	}

	void MovReg(byte reg, int val)
	{
		reg += 0xB8;
		this->code += {reg, INUMBER(val)};
	}

	void Invoke(DWORD address)
	{
		this->code += {0xE8, INUMBER(2), 0xEB, 6, 0x68, INUMBER(address), 0xC3};
	}

};