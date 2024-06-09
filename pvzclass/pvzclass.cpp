#include "pvzclass.h"
#include "Events/Events.h"
#include <iostream>
#include <thread>
#include "Mixin.h"
#include "Matchers.h"

using std::cout;
using std::endl;

void testbenchA() {
	//DisableInitialLawnmover();
	// jmp +0x87
	BYTE CODE[] = { JMPFAR(0x87) };

	const int FunctionAddress = 0x40BC70;
	// 0x40BC70: Board::InitLawnMowers(Board* this)
	PVZ::Mixin::Modify(FunctionAddress + 0x1C, FunctionAddress + 0x21, CODE, 5);

	PVZ::Mixin::InsAnalysis ins = PVZ::Mixin::Fetch(FunctionAddress, NULL);
	printf("%#08X:", FunctionAddress);
	cout << Mnemonics[ins.definition.mnemonic] << "; len = " << ins.len << endl;
	int CurrentAddress = FunctionAddress;
	for (int i = 0; i < 20; i++) {
		CurrentAddress += ins.len;
		ins = PVZ::Mixin::Fetch(CurrentAddress, NULL);
		printf("%#08X:", CurrentAddress);
		cout << Mnemonics[ins.definition.mnemonic] << "; len = " << ins.len << endl;
	}

	cout << "-------" << endl;

	int addr = PVZ::Mixin::Scan(PVZ::Mixin::Matchers::CountingMatcher<6>(),FunctionAddress, FunctionAddress + 0x200);
	ins = PVZ::Mixin::Fetch(addr, NULL);
	printf("%#08X:", addr);
	cout << Mnemonics[ins.definition.mnemonic] << "; len = " << ins.len << endl;

	addr = PVZ::Mixin::Scan(PVZ::Mixin::Matchers::MnemonicMatcher<MC_LEA>(), FunctionAddress, FunctionAddress + 0x200);
	ins = PVZ::Mixin::Fetch(addr, NULL);
	printf("%#08X:", addr);
	cout << Mnemonics[ins.definition.mnemonic] << "; len = " << ins.len << endl;

	addr = PVZ::Mixin::Scan(PVZ::Mixin::Matchers::CountingMnemonicMatcher<2,MC_MOV>(), FunctionAddress, FunctionAddress + 0x200);
	ins = PVZ::Mixin::Fetch(addr, NULL);
	printf("%#08X:", addr);
	cout << Mnemonics[ins.definition.mnemonic] << "; len = " << ins.len << endl;
}

void testbenchB() {
	PVZ::Memory::immediateExecute = true;
	PVZ::Memory::InjectDll("pvzdll.dll");
	PVZ::Memory::InvokeDllProc("init");
	EnableBackgroundRunning();
	DisableInitialLawnmover();
	DisableIceLevelFailSound();

	system("pause");
	DialogButtonDepressEvent();
	Draw::PString str = Draw::ToString("Hello, world!\0");
	Sexy::PDialog dialog = Sexy::MakeDialog(1, str, str, str, 0, 100);
	Sexy::AddToManager(dialog);
	system("pause");
	Sexy::RemoveFromManager(dialog);
	Sexy::FreeWidget(dialog);
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ::InitPVZ(pid);

	testbenchA();
	//testbenchB();
	system("pause");

	PVZ::QuitPVZ();
	return 0;
}
