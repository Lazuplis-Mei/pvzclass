#pragma once
#include "../PVZ.h"
#include <iostream>

using std::cout;
using std::hex;
using std::endl;

class DLLEvent
{
public:
	const char* procname;
	int rawlen, newlen, hookAddress;
	BYTE* hookCode, * newCode;
	void end();

protected:
	BYTE* rawCode;
	int procAddress, newAddress;
	void prepare();
	void start();
};

inline void DLLEvent::prepare()
{
	procAddress = PVZ::Memory::GetProcAddress(procname);
	newAddress = PVZ::Memory::AllocMemory();
	rawCode = new BYTE[rawlen];
}

inline void DLLEvent::start()
{
	PVZ::Memory::ReadArray<BYTE>(hookAddress, rawCode, rawlen);
	PVZ::Memory::WriteArray<BYTE>(hookAddress, hookCode, rawlen);
	PVZ::Memory::WriteArray<BYTE>(newAddress, newCode, newlen);
}

inline void DLLEvent::end()
{
	PVZ::Memory::WriteArray<BYTE>(hookAddress, rawCode, rawlen);
	PVZ::Memory::FreeMemory(newAddress);
}