int StupidSwitch = 0;
void __declspec(naked) Stupid_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_Stupid_asm");
#endif
__asm
{
Cmp  [StupidSwitch], 00
Je   Return
Cmp  [THE_VIP], 00
Jne  Super
Mov  Edx, [0x00e1cab8]
Test Edx, Edx
Je   Return
Cmp  [Edx+0x2C], 00
Jg   Return
Super:
Xor  Edx, Edx
Mov  Ecx, 0x0000EA60
Lea  Ecx, [Esi+0x000002C0]
Push 0x00981B44
Ret

Return:
Push 0x00981B2F
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}






int MobJumpSwitch = 0;
void __declspec(naked) MobJump_asm()
{
__asm
{
Push 05
Xor  Edx, Edx
Pop  Ecx
Div  Ecx
Test Edx, Edx
Cmp  [MobJumpSwitch], 1   //怪不跳
Je   NoJump
Cmp  [MobJumpSwitch], 2   //怪狂跳
Je   DoJump
Push 0x00982ED5           // Test Edx, Edx
Ret

NoJump:
Push 0x00982EE2           // Jne To...
Ret

DoJump:
Push 0x00982ED9           // Mov  Ecx, Esi
Ret
}
}






int MobKBSwitch = 0;
void __declspec(naked) MobKB_asm()
{
__asm
{
Cmp  [MobKBSwitch], 01    //不KB
Je   NoKB
Cmp  [MobKBSwitch], 02    //絕對KB
Je   DoKB
Push 0x00610721
Ret

NoKB:
Push 0x00610734           //Xor Edx, Edx
Ret

DoKB:
Push 0x00610738
Ret
}
}

     


int ItemFilterSwitch = 0;
int *ItemFilterList_adr = NULL;
int ItemFilterCount = 0;
void __declspec(naked) ItemFilter_asm()
{
__asm
{
// 8B 45 ?? 8B 75 ?? 88 46 ?? 83 F8 01
db 0x8B,0x45,0xE4,0x8B,0x75,0xB0,0x88,0x46,0x1C,0x83,0xF8,0x01,0x74,0x09,0x83,0xF8,0x02,0x74,0x04,0x32,0xC0,0xEB,0x02,0xB0,0x01,0x88,0x46,0x1D,0x89,0x7E,0x20,0x8B,0x7D,0x08,0x8B,0xCF
mov eax, 0x00408b13
call eax
movzx eax,al
mov ecx,edi
mov [esi+0x30],eax
mov eax, 0x00408b6f
call eax

Push Esi
Push Ebx

Cmp  Eax, 50000
Jle  Return
Cmp  [ItemFilterSwitch], 0
Je   Return
Mov  Esi, [ItemFilterList_adr]
Xor  Ebx, Ebx
LoopCheck:
Cmp  Ebx, [ItemFilterCount]
Jge  Return
Cmp  [Esi], Eax
Je   RemoveItem
Add  Esi, 04

Inc  Ebx
Jmp  LoopCheck

RemoveItem:
Xor  Eax, Eax
Return:
Pop  Ebx
Pop  Esi

Push 0x004EF010
Ret
}
}






int StupidMain = (int)Stupid_asm;
int MobJumpMain = (int)MobJump_asm;
int MobKBMain = (int)MobKB_asm;
int ItemFilterMain = (int)ItemFilter_asm;
void __declspec(naked) Blast_asm()
{
#ifdef VMProtectSDK
//VMProtectBegin("_Blast_asm");
#endif
__asm
{
/******************************
 *                            *
 *  更新記得改Return Address  *
 *                            *
 ******************************/
Cmp  [Esp+0x24], 0x00981B2F // 33 d2 b9 60 ea 00 00 f7 f1
Je   Stupid
Cmp  [Esp+0x24], 0x00982ECE // 6a 05 33 d2 59 f7 f1 85 d2
Je   MobJump
Cmp  [Esp+0x3C], 0x00610721 // 83 7D ?? 01 75 ?? 8B 4D ?? E8 ?? ?? ?? FF 39
Je   MobKB
Cmp  [Esp+0x6C], 0x004EEFDA // 8b 45 ?? 8b 75 ?? 88 46 ?? 83
Je   ItemFilter

BlastBack:
Push 0x0072C5C3
Ret

Stupid:
Push [StupidMain]
Pop  [Esp+0x24]
Jmp  BlastBack

MobJump:
Push [MobJumpMain]
Pop  [Esp+0x24]
Jmp  BlastBack

MobKB:
Push [MobKBMain]
Pop  [Esp+0x3C]
Jmp  BlastBack

ItemFilter:
Push [ItemFilterMain]
Pop  [Esp+0x6C]
Jmp  BlastBack
}
#ifdef VMProtectSDK
//VMProtectEnd();
#endif
}
