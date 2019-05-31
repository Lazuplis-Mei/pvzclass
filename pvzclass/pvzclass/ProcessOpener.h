#pragma once
#include <windows.h>
class ProcessOpener
{
public:
	static LPCWSTR ProcessName;
	static LPCWSTR WindowTitle;
	static LPCWSTR Directory;
	static LPCWSTR ExecuteableName;
	static DWORD OpenByProcessName(LPCWSTR processName);
	static DWORD OpenByWindowTitle(LPCWSTR processName);
	static DWORD OpenByFilePath(LPCWSTR directory, LPCWSTR executeableName);
	static DWORD Open();
};

