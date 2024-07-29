#include "Sexy.h"

Sexy::PButtonListener Sexy::MakeButtonListener(ButtonListener* listener)
{
	int address = PVZ::Memory::AllocMemory(0, 32);
	PVZ::Memory::WriteMemory<int>(address, address + 4);
	PVZ::Memory::WriteMemory<ButtonListener>(address + 4, *listener);
	return address;
}

Sexy::PEditListener Sexy::MakeEditListener(EditListener* listener)
{
	int address = PVZ::Memory::AllocMemory(0, 20);
	PVZ::Memory::WriteMemory<int>(address, address + 4);
	PVZ::Memory::WriteMemory<EditListener>(address + 4, *listener);
	return address;
}

Sexy::PCheckboxListener Sexy::MakeCheckboxListener(CheckboxListener* listener)
{
	int address = PVZ::Memory::AllocMemory(0, 8);
	PVZ::Memory::WriteMemory<int>(address, address + 4);
	PVZ::Memory::WriteMemory<CheckboxListener>(address + 4, *listener);
	return address;
}

BYTE __asm__MakeButton[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	INVOKE(0x448620),
	ADD_ESP(0x0C),
	MOV_PTR_ADDR_EAX(0),
	RET
};

Sexy::PButton Sexy::MakeButton(Draw::PString str, PButtonListener listener, int theId)
{
	SETARG(__asm__MakeButton, 1) = str;
	SETARG(__asm__MakeButton, 6) = listener;
	SETARG(__asm__MakeButton, 11) = theId;
	SETARG(__asm__MakeButton, 32) = PVZ::Memory::Variable;
	return PVZ::Memory::Execute(STRING(__asm__MakeButton));
}

BYTE __asm__MakeImageButton[]
{
	PUSHDWORD(0),
	MOV_EBX(0),
	MOV_EDI(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	INVOKE(0x448BC0),
	ADD_ESP(0x14),
	MOV_PTR_ADDR_EAX(0),
	RET
};

Sexy::PButton Sexy::MakeImageButton(Draw::PImage down, Draw::PImage over, Draw::PImage normal,
	DWORD fontAddress, Draw::PString str, PButtonListener listener, int theId)
{
	SETARG(__asm__MakeImageButton, 1) = down;
	SETARG(__asm__MakeImageButton, 6) = over;
	SETARG(__asm__MakeImageButton, 11) = normal;
	SETARG(__asm__MakeImageButton, 16) = fontAddress;
	SETARG(__asm__MakeImageButton, 21) = str;
	SETARG(__asm__MakeImageButton, 26) = listener;
	SETARG(__asm__MakeImageButton, 31) = theId;
	SETARG(__asm__MakeImageButton, 52) = PVZ::Memory::Variable;
	return PVZ::Memory::Execute(STRING(__asm__MakeImageButton));
}

BYTE __asm__MakeDialog[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	MOV_ECX_PTR_ADDR(0x6A9EC0),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0x64),
	CALL_EUX(2),
	MOV_PTR_ADDR_EAX(0),
	RET
};

Sexy::PDialog Sexy::MakeDialog(int buttonMode, Draw::PString footer, Draw::PString lines,
	Draw::PString header, int modal, int dialogId)
{
	SETARG(__asm__MakeDialog, 1) = buttonMode;
	SETARG(__asm__MakeDialog, 6) = footer;
	SETARG(__asm__MakeDialog, 11) = lines;
	SETARG(__asm__MakeDialog, 16) = header;
	SETARG(__asm__MakeDialog, 21) = modal;
	SETARG(__asm__MakeDialog, 26) = dialogId;
	SETARG(__asm__MakeDialog, 47) = PVZ::Memory::Variable;
	return PVZ::Memory::Execute(STRING(__asm__MakeDialog));
}

BYTE __asm__MakeEdit[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	INVOKE(0x4567B0),
	ADD_ESP(0x08),
	MOV_PTR_ADDR_EAX(0),
	RET
};

Sexy::PEdit Sexy::MakeEdit(PDialog dialog, PEditListener listener)
{
	SETARG(__asm__MakeEdit, 1) = dialog;
	SETARG(__asm__MakeEdit, 6) = listener;
	SETARG(__asm__MakeEdit, 27) = PVZ::Memory::Variable;
	return PVZ::Memory::Execute(STRING(__asm__MakeEdit));
}

Draw::PString Sexy::GetEditString(PEdit edit)
{
	return edit + 0x8C;
}

BYTE __asm__MakeCheckbox[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	INVOKE(0x456860),
	ADD_ESP(0x0C),
	MOV_PTR_ADDR_EAX(0),
	RET
};

Sexy::PCheckbox Sexy::MakeCheckbox(int checked, PCheckboxListener listener, int theId)
{
	SETARG(__asm__MakeCheckbox, 1) = checked;
	SETARG(__asm__MakeCheckbox, 6) = listener;
	SETARG(__asm__MakeCheckbox, 11) = theId;
	SETARG(__asm__MakeCheckbox, 32) = PVZ::Memory::Variable;
	return PVZ::Memory::Execute(STRING(__asm__MakeCheckbox));
}

bool Sexy::IsCheckboxChecked(PCheckbox checkbox)
{
	return PVZ::Memory::ReadMemory<bool>(checkbox + 0x90);
}

BYTE __asm__setCheckboxChecked[]
{
	PUSH(0),
	PUSH(0),
	MOV_ECX(0),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0x118),
	CALL_EUX(2),
	RET
};

void Sexy::setCheckboxChecked(PCheckbox checkbox, bool checked, bool tellListener)
{
	__asm__setCheckboxChecked[1] = tellListener;
	__asm__setCheckboxChecked[3] = checked;
	SETARG(__asm__setCheckboxChecked, 5) = checkbox;
	PVZ::Memory::Execute(STRING(__asm__setCheckboxChecked));
}

BYTE __asm__FreeWidget[]
{
	PUSH(1),
	MOV_ECX(0),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0),
	CALL_EUX(2),
	RET
};

void Sexy::FreeWidget(PWidget widget)
{
	SETARG(__asm__FreeWidget, 3) = widget;
	PVZ::Memory::Execute(STRING(__asm__FreeWidget));
}

BYTE __asm__ResizeButton[]
{
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	PUSHDWORD(0),
	MOV_ECX(0),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0xA0),
	CALL_EUX(2),
	RET
};

void Sexy::ResizeWidget(PWidget widget, int x, int y, int width, int height)
{
	SETARG(__asm__ResizeButton, 1) = height;
	SETARG(__asm__ResizeButton, 6) = width;
	SETARG(__asm__ResizeButton, 11) = y;
	SETARG(__asm__ResizeButton, 16) = x;
	SETARG(__asm__ResizeButton, 21) = widget;
	PVZ::Memory::Execute(STRING(__asm__ResizeButton));
}

BYTE __asm__AddToWidget[]
{
	PUSHDWORD(0),
	MOV_ECX(0),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0x0C),
	CALL_EUX(2),
	RET
};

void Sexy::AddToWidget(PWidget widget, PWidget father)
{
	SETARG(__asm__AddToWidget, 1) = widget;
	SETARG(__asm__AddToWidget, 6) = father;
	PVZ::Memory::Execute(STRING(__asm__AddToWidget));
}

BYTE __asm__RemoveFromWidget[]
{
	PUSHDWORD(0),
	MOV_ECX(0),
	0x8B, 0x11, // mov edx,[ecx]
	MOV_EUX_PTR_EVX_ADD(2, 2, 0x10),
	CALL_EUX(2),
	RET
};

void Sexy::RemoveFromWidget(PWidget widget, PWidget father)
{
	SETARG(__asm__RemoveFromWidget, 1) = widget;
	SETARG(__asm__RemoveFromWidget, 6) = father;
	PVZ::Memory::Execute(STRING(__asm__RemoveFromWidget));
}
