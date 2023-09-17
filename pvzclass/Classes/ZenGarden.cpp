#include "..\PVZ.h"

PVZ::ZenGarden::ZenGarden(int address)
{
	BaseAddress = address;
}

bool PVZ::ZenGarden::IsFull(bool consider_items)
{
	SETARG(__asm__ZenGarder_IsFull, 1) = BaseAddress;
	__asm__ZenGarder_IsFull[3] = consider_items ? 1 : 0;
	SETARG(__asm__ZenGarder_IsFull, 21) = PVZ::Memory::Variable;
	return(Memory::Execute(STRING(__asm__ZenGarder_IsFull)) == 1);
}

SPT<PVZ::Snail> PVZ::ZenGarden::GetSnail()
{
	if (PVZBASEADDRESS == 0)
		return(nullptr);
	SETARG(__asm__ZenGarder_GetSnail, 1) = BaseAddress;
	SETARG(__asm__ZenGarder_GetSnail, 19) = PVZ::Memory::Variable;
	return(MKS<PVZ::Snail>(Memory::Execute(STRING(__asm__ZenGarder_GetSnail))));
}
