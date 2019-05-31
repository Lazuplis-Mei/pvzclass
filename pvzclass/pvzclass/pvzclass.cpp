// pvzclass.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "ProcessOpener.h"
#include "PVZ.h"
#include <iostream>

using namespace std;
int main()
{
	DWORD pid = ProcessOpener::Open();
	PVZ* pPVZ = new PVZ(pid);
	cout << pPVZ->Sun;
	pPVZ->Sun = 1000;
	
}
