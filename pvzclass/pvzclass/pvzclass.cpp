#include "ProcessOpener.h"
#include "PVZ.h"
#include <iostream>
using namespace std;

int main()
{

	DWORD pid = ProcessOpener::Open();

	if (pid)
	{
		PVZ* pPVZ = new PVZ(pid);



		delete pPVZ;
	}
	return 0;
}
