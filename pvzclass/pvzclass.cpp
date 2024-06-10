#include "pvzclass.h"
#include "Events/Events.h"
#include <iostream>
#include <thread>
#include "Mixin.h"
#include "Matchers.h"

using std::cout;
using std::endl;

void testbenchA() {
	PVZ::Memory::immediateExecute = true;
	if (!PVZ::Memory::InjectDll("pvzdll.dll")) {
		printf("INJECT DLL FAILED!");
	}
	PVZ::Memory::InvokeDllProc("init");
	EnableBackgroundRunning();
	DisableInitialLawnmover();
	DisableIceLevelFailSound();

	system("pause");
	DialogButtonDepressEvent();
	system("pause");
	Draw::PString str = Draw::ToString("Hello, world!\0");
	Sexy::PDialog dialog = Sexy::MakeDialog(1, str, str, str, 0, 100);
	Sexy::AddToManager(dialog);
	system("pause");
	Sexy::RemoveFromManager(dialog);
	Sexy::FreeWidget(dialog);
}

void testbenchB() {
	// 0x40BC70: Board::InitLawnMowers(Board* this)
	const int FunctionAddress = 0x40BC70;

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

	// 定位到: 调用LawnApp::IsVaseBreakerLevel判断是否为破罐者关卡 将其替换为mov eax, 0,使其总为否
	addr = PVZ::Mixin::Scan(PVZ::Mixin::Matchers::CountingMnemonicMatcher<1, MC_CALL>(), FunctionAddress, FunctionAddress + 0x200);
	ins = PVZ::Mixin::Fetch(addr, NULL);
	BYTE CODE2[] = { MOV_EAX(0) };
	PVZ::Mixin::Modify(addr, addr + ins.len, CODE2, 5);

	system("pause");

}

void testbenchC() {
	// 0x40BC70: Board::InitLawnMowers(Board* this)
	const int FunctionAddress = 0x40BC70;

	//DisableInitialLawnmover();
	int target_address = FunctionAddress + 0x1C;
	int target_address_end = FunctionAddress + 0x1C + 0x05;

	int offset = target_address - PVZ::Mixin::CodePlacingAddress();

	// 所有的跳转指令都加上这个偏移量
	BYTE CODE[] = { 0xE9, INUMBER(0x87 + offset)};

	PVZ::Mixin::Replace(target_address, target_address_end, STRING(CODE));
}

void testbenchD() {
	PVZ::Memory::immediateExecute = true;
	if (!PVZ::Memory::InjectDll("pvzdll.dll")) {
		printf("INJECT DLL FAILED!");
	}
	PVZ::Memory::InvokeDllProc("init");
	EnableBackgroundRunning();
	DisableInitialLawnmover();
	DisableIceLevelFailSound();

	system("pause");
	ZombieRemoveEvent();
	system("pause");
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ::InitPVZ(pid);

	testbenchD();
	system("pause");

	PVZ::QuitPVZ();
	return 0;
}
