#include "PVZ.h"


PVZ::PVZ(DWORD pid)
{
	processId = pid;
	Memory::hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
}

PVZ::~PVZ()
{
	CloseHandle(Memory::hProcess);
}
