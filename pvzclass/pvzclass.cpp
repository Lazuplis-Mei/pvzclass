#include "pvzclass.h"
#include <iostream>
#include <thread>

using namespace std;

PVZ* pvz;

BYTE __asm__[]
{
	MOV_EAX(0),
	INVOKE(0x44E1B0),
	RET
};

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	pvz = new PVZ(pid);

	// 42712B 判定是否僵尸进入传送门
	// 42713E 判定是否能找到另一个传送门
	
	auto portal1 = Creator::CreatePortal(2, 2);
	auto portal2 = Creator::CreatePortal(4, 4, 1);

	Sleep(5000);

	portal1->Close();
	portal2->Close();

	delete pvz;
	return 0;
}
