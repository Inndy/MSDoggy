#include "MultiMS.h"

void* FakeDump_adr = NULL;
int DumpEnd = 0;
int FakeDump_offset = 0;
//---------------------------------------------------------------------------
void __declspec(naked) MSCRC1(){
#ifdef VMProtectSDK
VMProtectBegin("MSCRC1");
#endif
__asm{
// MSCRC2
cmp edx,0x00A3377F
jl OtherCheck
cmp edx,0x00A33786
jg OtherCheck

add edx,[FakeDump_offset]
jmp MSCRC1Ret

// SendPacket: 0x004965D2
OtherCheck:
cmp edx,0x004965CF // -3
jl MSCRC1Ret
cmp edx,0x004965d6 // +4
jg MSCRC1Ret

add edx,[FakeDump_offset]

MSCRC1Ret:
//MSCRC1原本動作
push [edx]
push 0x011D6D3D
ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __declspec(naked) MSCRC2(){
#ifdef VMProtectSDK
VMProtectBegin("MSCRC2");
#endif
__asm{
Cmp  Ecx, 0x00401000
Jl   Back
Cmp  Ecx, [DumpEnd]
Jg   Back

Add  Ecx, [FakeDump_offset]

Back:
Mov  Dl, [Ecx]
Add  Dl, 01
Push 0x00A33787
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __declspec(naked) FuckHS(){
#ifdef VMProtectSDK
VMProtectBegin("FuckHS");
#endif
__asm{
Mov  dword ptr [0x00A059A6], 0xFD5C8D89
Mov  word ptr [0x00A059AA], 0xFFFF
Mov  Ecx, 0x00A059A6
Add  Ecx, [FakeDump_offset]
Mov  dword ptr [Ecx], 0xFD5C8D89
Mov  word ptr [Ecx+4], 0xFFFF
Sub  Ecx, Ecx
Xor  Ecx, 0x201E80
Shl  Ecx, 1
Push 0x00A059A6
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void FuckChecking() {
#ifdef VMProtectSDK
VMProtectBegin("FuckChecking");
#endif
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQueryEx(GetCurrentProcess(),(PVOID)0x00401000,&mbi,sizeof(MEMORY_BASIC_INFORMATION));
	DumpEnd = 0x00401000 + mbi.RegionSize;
	FakeDump_adr = malloc(mbi.RegionSize);
	memcpy(FakeDump_adr, (LPVOID)0x00401000, mbi.RegionSize);
	FakeDump_offset = (int)FakeDump_adr - 0x00401000;
	AsmJump(0x011DEDC9, MSCRC1, 2); // e9 ?? ?? ?? ?? ff 32 e9 ?? ?? ff ff
	AsmJump(0x00A33782, MSCRC2, 0); // 8a 11 80 c2 01
	AsmJump(0x00A059A6, FuckHS, 1); // 89 8D ?? ?? FF FF C7 85 ?? ?? FF FF ?? ?? FF FF 8B 55
	EnableMultiMS();
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
