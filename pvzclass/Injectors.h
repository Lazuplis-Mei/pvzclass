#pragma once
#include<cstdio>
#include<cstring>
#include "PVZ.h"

class Injector
{
	private:
		unsigned int ReplaceRange;
	public:
		unsigned int InjectPos, FromPos;
		Injector()
		{
			ReplaceRange = InjectPos = FromPos = 0;
			return;
		}
		Injector(int OriPTR, int OriLen)
		{
			InjectPos = 0;
			FromPos = OriPTR, this->ReplaceRange = OriLen;
			int tmpl = OriLen - 5;
			if (tmpl < 0)
			{
				std::printf("YOU ARE FINDING FAULT WITH ME DELIBERATELY, AREN'T YOU!\n YOU INJECT IT OR NOT!\n");
				return;
			}
			byte tmp[1024];
			InjectPos = PVZ::Memory::AllocMemory();
			PVZ::Memory::WriteMemory<unsigned long long>(InjectPos + 0x340, 1099511413736);
			PVZ::Memory::ReadArray<byte>(OriPTR, tmp, OriLen);
			PVZ::Memory::WriteArray(InjectPos + 0x345, tmp, OriLen);
			PVZ::Memory::WriteMemory<byte>(InjectPos + 0x345 + OriLen, 0x68);
			PVZ::Memory::WriteMemory<int>(InjectPos + 0x346 + OriLen, OriPTR + OriLen);
			PVZ::Memory::WriteMemory<byte>(InjectPos + 0x34A + OriLen, RET);
			PVZ::Memory::WriteMemory<byte>(InjectPos, RET);
			PVZ::Memory::WriteMemory<byte>(OriPTR, 0xE9);
			PVZ::Memory::WriteMemory<unsigned int>(OriPTR + 1, InjectPos - OriPTR + 0x33B);
			for (register int i = 1; i <= tmpl; i++)
				PVZ::Memory::WriteMemory(OriPTR + i + 4, NOP);
			return;
		}
		~Injector()
		{
			this->Remove();
			return;
		}
		inline void Insert(byte* ASMCode, int CodeLen)
		{
			if(InjectPos)
				PVZ::Memory::WriteArray(InjectPos, ASMCode, CodeLen);
			return;
		}
		inline void Erase()
		{
			if (InjectPos)
				PVZ::Memory::WriteMemory<byte>(InjectPos, RET);
			return;
		}
		inline void Remove()
		{
			byte tmp[1024];
			PVZ::Memory::ReadArray<byte>(InjectPos + 0x345, tmp, ReplaceRange);
			PVZ::Memory::WriteArray<byte>(FromPos, tmp, ReplaceRange);
			PVZ::Memory::FreeMemory(InjectPos);
			return;
		}
};