#include "PuzzlePhaseCompleteEvent.h"

PuzzlePhaseCompleteEvent::PuzzlePhaseCompleteEvent()
{
	address = 0x429980;
}

#if defined(_WIN64)
void PuzzlePhaseCompleteEvent::handle(CONTEXT& context)
{
	auto challenge = MKS<PVZ::Miscellaneous>(PVZ::Memory::ReadMemory<DWORD>(context.Rcx + 4));
	int gridX = context.Rax;
	int gridY = PVZ::Memory::ReadMemory<DWORD>(context.Rsp + 4);
	for (int i = 0; i < listeners.size(); i++)
	{
		gridY = listeners[i](challenge, gridX, gridY);
	}
	PVZ::Memory::WriteMemory<DWORD>(context.Rsp + 4, gridY);
}
#else
void PuzzlePhaseCompleteEvent::handle(CONTEXT& context)
{
	auto challenge = MKS<PVZ::Miscellaneous>(PVZ::Memory::ReadMemory<DWORD>(context.Ecx + 4));
	int gridX = context.Eax;
	int gridY = PVZ::Memory::ReadMemory<DWORD>(context.Esp + 4);
	for (int i = 0; i < listeners.size(); i++)
	{
		gridY = listeners[i](challenge, gridX, gridY);
	}
	PVZ::Memory::WriteMemory<DWORD>(context.Esp + 4, gridY);
}
#endif