#include "ProcessOpener.h"
#include "PVZ.h"
using namespace std;


int main()
{
	DWORD pid = ProcessOpener::Open();
	PVZ* pPVZ = new PVZ(pid);

	PVZ::Lawn* lawn = pPVZ->GetLawn();

	for (int i = 0; i < 6; i++)
	{
		cout << lawn->GetRouteType(i) << " | ";
		for (int j = 0; j < 9; j++)
		{
			cout << lawn->GetGridType(i, j) << " ";
		}
		cout << endl;
	}
	

	PVZ::Icetrace* icetarce = pPVZ->GetIcetrace();

	for (int i = 0; i < 6; i += 2)
	{
		icetarce->SetX(i, 400);
		icetarce->SetDisappearCountdown(i, 1000);
	}
	
}
