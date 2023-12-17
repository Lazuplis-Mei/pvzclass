#include "../PVZ.h"

HANDLE PVZ::Memory::hProcess = NULL;
DWORD PVZ::Memory::processId = 0;
HANDLE PVZ::Memory::hThread = NULL;
DWORD PVZ::Memory::mainThreadId = 0;
int PVZ::Memory::Variable = 0;
HWND PVZ::Memory::mainwindowhandle = NULL;
bool PVZ::Memory::immediateExecute = false;

int PVZ::Memory::ReadPointer(int baseaddress, int offset)
{
	return ReadMemory<int>(ReadMemory<int>(baseaddress) + offset);
}

int PVZ::Memory::ReadPointer(int baseaddress, int offset, int offset1)
{
	return ReadMemory<int>(ReadPointer(baseaddress, offset) + offset1);
}

int PVZ::Memory::ReadPointer(int baseaddress, int offset, int offset1, int offset2)
{
	return ReadMemory<int>(ReadPointer(baseaddress, offset, offset1) + offset2);
}

BOOL PVZ::Memory::AllAccess(int address)
{
	DWORD op = PAGE_READONLY;
	return VirtualProtectEx(hProcess, (LPVOID)address, PAGE_SIZE, PAGE_EXECUTE_READWRITE, &op);
}

int PVZ::Memory::AllocMemory(int pages)
{
	return (int)VirtualAllocEx(hProcess, 0, PAGE_SIZE * pages, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
}

void PVZ::Memory::CreateThread(int address)
{
	HANDLE hThread;
	DWORD ret;
	hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)address, NULL, 0, NULL);
	if (hThread)
	{
		do 
			ret = WaitForSingleObject(hThread, 100);
		while (ret == WAIT_TIMEOUT);
		CloseHandle(hThread);
	}
}

void PVZ::Memory::FreeMemory(int address)
{
	VirtualFreeEx(hProcess, (LPVOID)address, 0, MEM_RELEASE);
}

int PVZ::Memory::Execute(byte asmCode[], int length)
{
	int Address = AllocMemory();
	WriteArray<byte>(Address, asmCode, length);
	if (!immediateExecute) WaitPVZ();
	CreateThread(Address);
	if (!immediateExecute) ResumePVZ();
	FreeMemory(Address);
	return ReadMemory<int>(Variable);
}

void PVZ::Memory::WaitPVZ()
{
	WriteMemory<BYTE>(Variable + 0x530, 1);
	while (ReadMemory<BYTE>(Variable + 0x540) == 0);
}

void PVZ::Memory::ResumePVZ()
{
	WriteMemory<BYTE>(Variable + 0x530, 0);
}