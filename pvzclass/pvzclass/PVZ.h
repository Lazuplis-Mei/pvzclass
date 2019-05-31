#pragma once
#include <windows.h>
#define PROPERTY(type,getmethod,setmethod) type getmethod();void setmethod(type value);__declspec(property(get=getmethod, put=setmethod)) type
#define PROPERTYBINDING(type,getmethod,getter,setmethod,setter) type getmethod(){return getter;};void setmethod(type value){setter;};__declspec(property(get=getmethod, put=setmethod)) type
#define READONLYPROPERTY(type,getmethod) type getmethod();__declspec(property(get=getmethod)) type
#define READONLYPROPERTYBINDING(type,getmethod,getter) type getmethod(){return getter;};__declspec(property(get=getmethod)) type
#define WRITEONLYPROPERTYBINDING(type,setmethod,setter) void setmethod(type value){setter;};__declspec(property(put=setmethod)) type
class PVZ
{
	DWORD processId;
	class Memory
	{
	public:
		static HANDLE hProcess;
		static int ReadInteger(int address);
		static BOOL WriteInteger(int address, int value);
		//add more method

		static int ReadPointer(int baseaddress, int offset);
		static int ReadPointer(int baseaddress, int offset, int offset1);
		static int ReadPointer(int baseaddress, int offset, int offset1, int offset2);
	};
public:
	PVZ(DWORD pid);
	~PVZ();
	READONLYPROPERTYBINDING(
		int,
		__get_BaseAddress,
		Memory::ReadPointer(0x6A9EC0, 0x768)) BaseAddress;
	PROPERTYBINDING(int, 
		__get_Sun, 
		Memory::ReadInteger(BaseAddress + 0x5560), 
		__set_Sun, 
		Memory::WriteInteger(BaseAddress + 0x5560, value)) Sun;
};

