#include "ProcessOpener.h"
#include "PVZ.h"
#include <iostream>
using namespace std;

#define ENUMSTRING
#undef VNAME
#undef IDENTIFIER
#include "Enums.h"


int main()
{
	ProcessOpener::Directory = TEXT("D:\\植物大战僵尸\\Plants_Vs_Zombies_V1.0.0.1051_CN");
	DWORD pid = ProcessOpener::Open();

	if (pid)
	{
		PVZ* pPVZ = new PVZ(pid);
		if (PVZ::PVZ_BASE && pPVZ->BaseAddress)
		{
			cout << enumstring::SceneType[pPVZ->LevelScene];
			pPVZ->LevelScene = SceneType::Night;
		}
		delete pPVZ;
	}
	return 0;
}
