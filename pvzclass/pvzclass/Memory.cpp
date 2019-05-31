#include "PVZ.h"
HANDLE PVZ::Memory::hProcess = NULL;
int PVZ::Memory::ReadInteger(int address)
{
	int puffer;
	ReadProcessMemory(hProcess, (LPCVOID)address, &puffer, sizeof(int), NULL);
	return puffer;
}

BOOL PVZ::Memory::WriteInteger(int address, int value)
{
	return WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(int), NULL);
}

int PVZ::Memory::ReadPointer(int baseaddress, int offset)
{
	return ReadInteger(ReadInteger(baseaddress) + offset);
}

int PVZ::Memory::ReadPointer(int baseaddress, int offset, int offset1)
{
	return ReadInteger(ReadPointer(baseaddress, offset) + offset1);
}

int PVZ::Memory::ReadPointer(int baseaddress, int offset, int offset1, int offset2)
{
	return ReadInteger(ReadPointer(baseaddress, offset, offset1) + offset2);
}

