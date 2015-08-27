extern int THE_VIP;
#include "Scripts\GetInfo.h"
#include "Scripts\Blast.h"





int NoKBSwitch = 0;
void __declspec(naked) NoKB_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_NoKB_asm");
#endif
__asm
{
Cmp  [NoKBSwitch], 00
Je   Back
Ret  0x0014

Back:
Push 0x0097BB75
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}






int MoveFastSwitch = 0;
int MFFakeTime = 0;
int MFRate = 4;
void __declspec(naked) MoveFast_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_MoveFast_asm");
#endif
__asm
{
Cmp  [MoveFastSwitch], 00
Je   Return
Cmp  [Esp], 0x009326E7
Jne  Return
Add  Esp, 4
Push Esi
Mov  Esi, [MFRate]
Cmp  [THE_VIP], 1
Je   NoLimitSpeed
Cmp  Esi, 5
Jle  SpeedChk
Mov  Esi, 5
NoLimitSpeed:

SpeedChk:
Test Esi, Esi
Je   Normal

Dec  Esi
Push Esi
Push Ecx
Push Eax
Call dword ptr [Eax]
Pop  Eax
Pop  Ecx
Pop  Esi
Jmp  SpeedChk

Normal:
Pop  Esi
Push 0x009326E7
Ret

Return:
Push 0x0097C43D // 53 56 57 8b f9 8d 77 ?? 8b 06 8b ce ff 50
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}

void __declspec(naked) MFFakeTime_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_MFFakeTime_asm");
#endif
__asm
{
Add  [MFFakeTime], 510
Add  Eax, [MFFakeTime]
Push 0x009a8db6
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}






int MobFollowSwitch = 0;
int MobFollowX = 0;
#ifndef BlackMapleStory
int Pause = 0;        
#endif
#ifdef BlackMapleStory
extern int Pause;
#endif
extern int MobVacSwitch, VacX;
void __declspec(naked) MobFollow_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_MobFollow_asm");
#endif
__asm
{
Cmp  [Pause], 0
Jne  Return
Cmp  [MobVacSwitch], 00
Jne  VacFollow
Cmp  [MobFollowSwitch], 00
Je   Return
Cmp  [Ecx+0x000002A8], 0x01
Je   Control
Cmp  [Ecx+0x000002A8], 0x03
Je   Control
Jmp  Return

VacFollow:
Mov  Eax, [VacX]
Jmp  Follow

Control:
Mov  Eax, [MobFollowX]
Follow:
Sub  Eax, 5
Cmp  [Ecx+0x000006A4], Eax
Jl   GoRight
Add  Eax, 10
Cmp  [Ecx+0x000006A4], Eax
Jg   GoLeft
Jmp  GoStop

GoLeft:
Mov  [Ecx+0x000000FC], 0xFFFFFFFF
Jmp  Return

GoRight:
Mov  [Ecx+0x000000FC], 0x00000001
Jmp  Return

GoStop:
Mov  [Ecx+0x000000FC], 0x00000000
Jmp  Return

Return:
Push 0x009856D5	// 55 8B EC 51 53 56 57 FF 75 08
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}






int DoubleAttackSwitch = 0;
void __declspec(naked) UnlimitedWeapon_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_UnlimitedWeapon_asm");
#endif
__asm
{
Cmp [THE_VIP], 0
Je  ICS
Mov [Ebp-0x00000224], 1
Cmp [DoubleAttackSwitch], 00
Je  CRCReturn
Mov [Ebp-0x00000220], 1

CRCReturn:
Push 0x00915D43
Push 0x008FC369
Ret

ICS:
Cmp [esp+0x10],0x00915D43
Jne Return
Mov [Ebp-0x00000224], 1

Return:
Push 0x00521B01
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}





int MPFakeTime = 0;
int MPNextTime = 0;
int GetXYCALL = 0x004A3704;
int PickCall = 0x004EC355;
int ImmediateFullSwitch = 0;
void __declspec(naked) MP_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_MultiPickMain_asm");
#endif
__asm
{
Add  Esp, 4
Call [GetXYCALL]

Cmp  [THE_VIP], 00
Je   NOTVIP1
Mov  Ecx, 16
Jmp  LoopPick

NOTVIP1:
Mov  Ecx, 3

LoopPick:
Dec  Ecx
Test Ecx, Ecx
Je   NormalPick
Push Ecx
Push Eax

Push Eax
Mov  Ecx, [MPFakeTime]
Mov  Eax, [0x00E1CFF0]
Add  [Eax+0x1C], Ecx
Mov  Ecx, [0x00E20510]
Call [PickCall]
Test Eax, Eax
Je   NoPick
Mov  Eax, [0x00E181E0]
And  [Eax+0x20DC], 0
NoPick:
Mov  Ecx, [MPFakeTime]
Mov  Eax, [0x00E1CFF0]
Sub  [Eax+0x1C], Ecx
Add  [MPFakeTime], 30
Pop  Eax
Pop  Ecx
Jmp  LoopPick

NormalPick:
Cmp  [THE_VIP], 00
Jne  Return

Push Eax
Mov  Eax, [0x00E181E0]
And  [Eax+0x20DC], 0
And  [Eax+0x20E0], 0
Mov  Ecx, [0x00E20510]
Call [PickCall]
Return:
Push 0x00930767
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}

void __declspec(naked) MultiPick_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_MultiPick_asm");
#endif
__asm
{
Cmp  [Esp], 0x0093075F
Je   MultiPick
Cmp  [Esp], 0x0093E6E3
Je   ImmediateFull

Back:
Push 0x004A3704
Ret

ImmediateFull:
Cmp  [ImmediateFullSwitch], 00
Je   Back
And  [Esi+0x000070EC], 00
Jmp  Back

MultiPick:
Mov  Eax, [0x00E1CFF0]
Mov  Eax, [Eax+0x1C]
Cmp  Eax, [MPNextTime]
Jl   Back
Add  Eax, 30
Mov  [MPNextTime], Eax
Jmp  MP_asm
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}






int SuperStupidSwitch = 0;
int MobAggroSwitch = 0;
void __declspec(naked) SuperStupid_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_SuperStupid_asm");
#endif
__asm
{
cmp  dword ptr [esp+0x48], 0x00985B05 // 3b c7 75 ? 33 c0 eb ? 83 be ? ? ? ? 06
jne  My_Ret

Cmp  [SuperStupidSwitch], 0
Je   My_Ret

mov  [esi+0x000002B0], 00 // 39 be ?? ?? 00 00 74 ?? 8d 8e ?? ?? 00 00 e8 ?? ?? ?? ff 85 c0

My_Ret:
push 0x0097C7BB
ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}





int ReduceHurtsSwitch = 0;
int MobNoFightBackSwitch = 0;
void __declspec(naked) ReduceHurts_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_ReduceHurts_asm");
#endif
__asm
{
Cmp  [Esp], 0x009238A9
Je   ReduceHurt
Cmp  [Esp+0x58], 0x00613F4E
Jne  Return
Cmp  [THE_VIP], 1
Jne  Return
Cmp  [MobNoFightBackSwitch], 0
Je   Return
Mov  [Esp+0x58], 0x00614148
Jmp  Return

ReduceHurt:
Cmp  [ReduceHurtsSwitch], 0
Je   Return
Mov  Eax, [Ebp+0x58]
Shr  Eax, 2 // 損血量 / 4
Sub  [Ebp+0x58], Eax
Return:
Push 0x008F9C92
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}




int GodSwitch = 0;
int GodTime = 0;
int FullGod = 0;
void __declspec(naked) God30_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_God30_asm");
#endif
__asm
{
Cmp  [GodSwitch], 0
Je   Return
Cmp  [Esp], 0x00921C7E // 下面ICS點的返回位置 [1/2] e8 ? ? ? ? 85 c0 0f 85 ? ? ? ? 8b 83 ? ? 00 00 83 e0 fe 83 f8 12 0f 84 ?? ?? 00 00 e8 ?? ?? ?? 00 8b ?? 8b ?? 8b ?? ff 50 10 8b c8 e8 ?? ?? ?? ff 85 c0 0f 85
Jne  Return
Cmp  [FullGod], 0
Jne  God

Call GetTicket // 時間
Cmp  Eax, [GodTime]
Jl   God

Add  Eax, 30000
Mov  [GodTime], Eax
Jmp  Return

God: // 無敵
Mov  [Esp], 0x0092406C // ICS下面的JMP jne 00896AB4

Return: // 正常損血
Push 0x00931AFE  // ICS: call dword ptr [eax+10]
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}






int FinalAttackSkillID = 0;
void __declspec(naked) OverAttack_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_OverAttack_asm");
#endif
__asm
{
db 0x8B,0x45,0x10,0x8B,0x75,0xF4,0x8B,0x4D,0xF0,0x89,0x86,0x40,0x5F,0x00,0x00,0x89,0xBE,0x44,0x5F,0x00,0x00,0x89,0x8E,0x48,0x5F,0x00,0x00
mov [FinalAttackSkillID],edi
db 0x5F,0x5E,0x5B,0xC9,0xC2,0x10,0x00
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}







int NoDelayFinalAttackSwitch = 0;
void __declspec(naked) NoDelayFinalAttack_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_NoDelayFinalAttack_asm");
#endif
__asm
{
Push 0x00933B76
DB   0x55                                                   //00939D29 - push ebp
DB   0x8b,0xec                                              //00939D2A - mov ebp,esp
DB   0x83,0xec,0x10                                         //00939D2C - sub esp,10
DB   0x53                                                   //00939D2F - push ebx
DB   0x56                                                   //00939D30 - push esi
DB   0x57                                                   //00939D31 - push edi
DB   0x8b,0xf1                                              //00939D32 - mov esi,ecx
Mov  Eax,0x009562dd                                         //00939D34 - call 009562dd
Call Eax
DB   0x8b,0x0d,0xe0,0x81,0xe1,0x00                          //00939D39 - mov ecx,[00e181e0] : 00E2AB58
DB   0x8b,0xd8                                              //00939D3F - mov ebx,eax
DB   0x8d,0x45,0xf0                                         //00939D41 - lea eax,[ebp-10]
DB   0x50                                                   //00939D44 - push eax
Mov  Eax,0x00422812                                         //00939D45 - call 00422812
Call Eax
DB   0x8b,0x40,0x04                                         //00939D4A - mov eax,[eax+04]
DB   0x8d,0x4d,0xf0                                         //00939D4D - lea ecx,[ebp-10]
DB   0x89,0x45,0xf8                                         //00939D50 - mov [ebp-08],eax
Mov  Eax,0x0042189f                                         //00939D53 - call 0042189f
Call Eax
DB   0x33,0xff                                              //00939D58 - xor edi,edi
Cmp  [NoDelayFinalAttackSwitch], 0
Je   Normal
Push [FinalAttackSkillID]
Pop  [esi+0x5F44]       // Cmp [Esi+XXXXXXXX], Edi

Normal:
Push 0x00939D72 // Push [Esi+XXXXXXXX]
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}






long Making00a169a9 = 0x00a169a9;long Making0045c8bb = 0x0045c8bb;long Making00440b54 = 0x00440b54;long Making00422812 = 0x00422812;long Making0042189f = 0x0042189f;long Making005d6d0c = 0x005d6d0c;long Making004545e0 = 0x004545e0;long Making0040f4dd = 0x0040f4dd;long Making00594c1d = 0x00594c1d;long Making0072faab = 0x0072faab;long Making0042056b = 0x0042056b;long Making00436841 = 0x00436841;long Making00423302 = 0x00423302;long Making009562dd = 0x009562dd;long Making0095ec3e = 0x0095ec3e;long Making007d9f7a = 0x007d9f7a;long Making0099185f = 0x0099185f;long Making007d97fb = 0x007d97fb;long Making0099238d = 0x0099238d;long Making00a16a81 = 0x00a16a81;
void __declspec(naked) UltraMaking_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_UltraMaking_asm");
#endif
__asm
{
DB   0x6a,0x18                                              //007DB421 - push 18
DB   0xb8,0x56,0x48,0xac,0x00                               //007DB423 - mov eax,00ac4856
Call Making00a169a9                                         //007DB428 - call 00a169a9
DB   0x8b,0xf1                                              //007DB42D - mov esi,ecx
DB   0x8b,0x8e,0x14,0x01,0x00,0x00                          //007DB42F - mov ecx,[esi+00000114]
Call Making0045c8bb                                         //007DB435 - call 0045c8bb
DB   0x8d,0x8e,0x18,0x01,0x00,0x00                          //007DB43A - lea ecx,[esi+00000118]
Call Making00440b54                                         //007DB440 - call 00440b54
DB   0x8b,0x86,0xa0,0x00,0x00,0x00                          //007DB445 - mov eax,[esi+000000a0]
DB   0x33,0xdb                                              //007DB44B - xor ebx,ebx
DB   0x2b,0xc3                                              //007DB44D - sub eax,ebx
je Doggy007db5c9                                            //007DB44F - je 007db5c9
DB   0x48                                                   //007DB455 - dec eax
DB   0x48                                                   //007DB456 - dec eax
jne Doggy007db5e3                                           //007DB457 - jne 007db5e3
DB   0x39,0x9e,0xa8,0x00,0x00,0x00                          //007DB45D - cmp [esi+000000a8],ebx
je Doggy007db5e3                                            //007DB463 - je 007db5e3
DB   0x39,0x9e,0xac,0x00,0x00,0x00                          //007DB469 - cmp [esi+000000ac],ebx
jng Doggy007db5e3                                           //007DB46F - jng 007db5e3
DB   0x89,0x5d,0xf0                                         //007DB475 - mov [ebp-10],ebx
DB   0x8b,0x0d,0xe0,0x81,0xe1,0x00                          //007DB478 - mov ecx,[00e181e0] : 00E2AB58
DB   0x8d,0x45,0xdc                                         //007DB47E - lea eax,[ebp-24]
DB   0x50                                                   //007DB481 - push eax
DB   0x89,0x5d,0xfc                                         //007DB482 - mov [ebp-04],ebx
Call Making00422812                                         //007DB485 - call 00422812
DB   0x8b,0x78,0x04                                         //007DB48A - mov edi,[eax+04]
DB   0x8d,0x4d,0xdc                                         //007DB48D - lea ecx,[ebp-24]
Call Making0042189f                                         //007DB490 - call 0042189f
DB   0x8b,0x8e,0x9c,0x00,0x00,0x00                          //007DB495 - mov ecx,[esi+0000009c]
DB   0x3b,0xcb                                              //007DB49B - cmp ecx,ebx
je Doggy007db4ab                                            //007DB49D - je 007db4ab
DB   0x8d,0x45,0xf0                                         //007DB49F - lea eax,[ebp-10]
DB   0x50                                                   //007DB4A2 - push eax
DB   0x6a,0x01                                              //007DB4A3 - push 01
DB   0x57                                                   //007DB4A5 - push edi
Call Making005d6d0c                                         //007DB4A6 - call 005d6d0c
Doggy007db4ab:
DB   0x8b,0x45,0xf0                                         //007DB4AB - mov eax,[ebp-10]
DB   0x3b,0xc3                                              //007DB4AE - cmp eax,ebx
je Doggy007db4e7                                            //007DB4B0 - je 007db4e7
DB   0x38,0x18                                              //007DB4B2 - cmp [eax],bl
je Doggy007db4e7                                            //007DB4B4 - je 007db4e7
DB   0x8d,0x45,0xf0                                         //007DB4B6 - lea eax,[ebp-10]
DB   0x6a,0x0b                                              //007DB4B9 - push 0b
DB   0x50                                                   //007DB4BB - push eax
Call Making004545e0                                         //007DB4BC - call 004545e0
DB   0x59                                                   //007DB4C1 - pop ecx
DB   0x89,0x9e,0xac,0x00,0x00,0x00                          //007DB4C2 - mov [esi+000000ac],ebx
Doggy007db4c8:
DB   0x59                                                   //007DB4C8 - pop ecx
Doggy007db4c9:
DB   0x8b,0x45,0xf0                                         //007DB4C9 - mov eax,[ebp-10]
DB   0x83,0x4d,0xfc,0xff                                    //007DB4CC - or dword ptr [ebp-04],ff
DB   0x3b,0xc3                                              //007DB4D0 - cmp eax,ebx
je Doggy007db5e3                                            //007DB4D2 - je 007db5e3
DB   0x83,0xc0,0xf4                                         //007DB4D8 - add eax,f4
DB   0x50                                                   //007DB4DB - push eax
Call Making0040f4dd                                         //007DB4DC - call 0040f4dd
DB   0x59                                                   //007DB4E1 - pop ecx
jmp Doggy007db5e3                                           //007DB4E2 - jmp 007db5e3
Doggy007db4e7:
DB   0x8b,0x86,0x9c,0x00,0x00,0x00                          //007DB4E7 - mov eax,[esi+0000009c]
DB   0x8b,0x40,0x10                                         //007DB4ED - mov eax,[eax+10]
DB   0xff,0x30                                              //007DB4F0 - push [eax]
DB   0x8b,0x0d,0xe4,0x81,0xe1,0x00                          //007DB4F2 - mov ecx,[00e181e4] : 00000000
DB   0x8d,0x45,0xe8                                         //007DB4F8 - lea eax,[ebp-18]
DB   0x50                                                   //007DB4FB - push eax
Call Making00594c1d                                         //007DB4FC - call 00594c1d
DB   0xff,0x86,0xb0,0x00,0x00,0x00                          //007DB501 - inc [esi+000000b0]
DB   0x8d,0x45,0xe4                                         //007DB507 - lea eax,[ebp-1c]
DB   0x68,0x72,0x16,0x00,0x00                               //007DB50A - push 00001672
DB   0x50                                                   //007DB50F - push eax
DB   0xc6,0x45,0xfc,0x01                                    //007DB510 - mov byte ptr [ebp-04],01
Call Making0072faab                                         //007DB514 - call 0072faab
DB   0x8b,0xc8                                              //007DB519 - mov ecx,eax
Call Making0042056b                                         //007DB51B - call 0042056b
DB   0x89,0x5d,0xec                                         //007DB520 - mov [ebp-14],ebx
DB   0xff,0xb6,0xb0,0x00,0x00,0x00                          //007DB523 - push [esi+000000b0]
DB   0x8b,0x00                                              //007DB529 - mov eax,[eax]
DB   0xff,0xb6,0xa4,0x00,0x00,0x00                          //007DB52B - push [esi+000000a4]
DB   0xc6,0x45,0xfc,0x03                                    //007DB531 - mov byte ptr [ebp-04],03
DB   0xff,0x75,0xe8                                         //007DB535 - push [ebp-18]
DB   0x50                                                   //007DB538 - push eax
DB   0x8d,0x45,0xec                                         //007DB539 - lea eax,[ebp-14]
DB   0x50                                                   //007DB53C - push eax
Call Making00436841                                         //007DB53D - call 00436841
DB   0x83,0xc4,0x14                                         //007DB542 - add esp,14
DB   0x50                                                   //007DB545 - push eax
DB   0x8d,0x8e,0x30,0x01,0x00,0x00                          //007DB546 - lea ecx,[esi+00000130]
Call Making00423302                                         //007DB54C - call 00423302
DB   0x8b,0x45,0xec                                         //007DB551 - mov eax,[ebp-14]
DB   0xc6,0x45,0xfc,0x02                                    //007DB554 - mov byte ptr [ebp-04],02
DB   0x3b,0xc3                                              //007DB558 - cmp eax,ebx
je Doggy007db566                                            //007DB55A - je 007db566
DB   0x83,0xc0,0xf4                                         //007DB55C - add eax,f4
DB   0x50                                                   //007DB55F - push eax
Call Making0040f4dd                                         //007DB560 - call 0040f4dd
DB   0x59                                                   //007DB565 - pop ecx
Doggy007db566:
DB   0x8b,0x45,0xe4                                         //007DB566 - mov eax,[ebp-1c]
DB   0xc6,0x45,0xfc,0x01                                    //007DB569 - mov byte ptr [ebp-04],01
DB   0x3b,0xc3                                              //007DB56D - cmp eax,ebx
je Doggy007db57b                                            //007DB56F - je 007db57b
DB   0x83,0xc0,0xf4                                         //007DB571 - add eax,f4
DB   0x50                                                   //007DB574 - push eax
Call Making0040f4dd                                         //007DB575 - call 0040f4dd
DB   0x59                                                   //007DB57A - pop ecx
Doggy007db57b:
DB   0x89,0x9e,0xa0,0x00,0x00,0x00                          //007DB57B - mov [esi+000000a0],ebx
Call Making009562dd                                         //007DB581 - call 009562dd
DB   0xff,0xb6,0x38,0x01,0x00,0x00                          //007DB586 - push [esi+00000138]
DB   0x89,0x86,0xb8,0x00,0x00,0x00                          //007DB58C - mov [esi+000000b8],eax
Call Making0095ec3e                                         //007DB592 - call 0095ec3e
DB   0x59                                                   //007DB597 - pop ecx
DB   0x8b,0xce                                              //007DB598 - mov ecx,esi
DB   0x89,0x86,0x34,0x01,0x00,0x00                          //007DB59A - mov [esi+00000134],eax
Call Making007d9f7a                                         //007DB5A0 - call 007d9f7a
DB   0x53                                                   //007DB5A5 - push ebx
DB   0x8b,0xce                                              //007DB5A6 - mov ecx,esi
Call Making0099185f                                         //007DB5A8 - call 0099185f
DB   0x8b,0x45,0xe8                                         //007DB5AD - mov eax,[ebp-18]
DB   0x88,0x5d,0xfc                                         //007DB5B0 - mov [ebp-04],bl
DB   0x3b,0xc3                                              //007DB5B3 - cmp eax,ebx
je Doggy007db4c9                                            //007DB5B5 - je 007db4c9
DB   0x83,0xc0,0xf4                                         //007DB5BB - add eax,f4
DB   0x50                                                   //007DB5BE - push eax
Call Making0040f4dd                                         //007DB5BF - call 0040f4dd
jmp Doggy007db4c8                                           //007DB5C4 - jmp 007db4c8
Doggy007db5c9:
Call Making009562dd                                         //007DB5C9 - call 009562dd
DB   0x2b,0x86,0xb8,0x00,0x00,0x00                          //007DB5CE - sub eax,[esi+000000b8]
DB   0x3b,0x86,0xbc,0x00,0x00,0x00                          //007DB5D4 - cmp eax,[esi+000000bc]
//jnge Doggy007db5e3                                          //007DB5DA - jnge 007db5e3
DB   0x8b,0xce                                              //007DB5DC - mov ecx,esi
Call Making007d97fb                                         //007DB5DE - call 007d97fb
Doggy007db5e3:
DB   0x8b,0xce                                              //007DB5E3 - mov ecx,esi
Call Making0099238d                                         //007DB5E5 - call 0099238d
Call Making00a16a81                                         //007DB5EA - call 00a16a81
DB   0xc3                                                   //007DB5EF - ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}





long Doggy_0048b66d = 0x0048b66d;
long Doggy_00408b6f = 0x00408b6f;
void __declspec(naked) NoMiningInterval_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_NoMiningInterval_asm");
#endif
__asm
{
push [ebp+0x0c]
push 0x00930c56
DB   0x56                                                   //00909982 - push esi
DB   0x57                                                   //00909983 - push edi
DB   0x8b,0xf1                                              //00909984 - mov esi,ecx
DB   0x8b,0x0d,0xe0,0x81,0xe1,0x00                          //00909986 - mov ecx,[00e181e0] : 00E2AB58
DB   0x6a,0x00                                              //0090998C - push 00
Call Doggy_0048b66d                                         //0090998E - call 0048b66d
DB   0x8b,0x4c,0x24,0x0c                                    //00909993 - mov ecx,[esp+0c]
Call Doggy_00408b6f                                         //00909997 - call 00408b6f
DB   0x8b,0x4c,0x24,0x0c                                    //0090999C - mov ecx,[esp+0c]
DB   0x8b,0xf8                                              //009099A0 - mov edi,eax
Call Doggy_00408b6f                                         //009099A2 - call 00408b6f
Push 0x009099AC
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}






long Doggy_00694581 = 0x00694581;
long Doggy_0043183c = 0x0043183c;
long Doggy_006935ff = 0x006935ff;
long Doggy_0069596e = 0x0069596e;
long Doggy_008f662a = 0x008f662a;
void __declspec(naked) NoDelayMining_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_NoDelayMining_asm");
#endif
__asm
{
Push 0x00932619
DB   0x55                                                   //008FFF88 - push ebp
DB   0x8b,0xec                                              //008FFF89 - mov ebp,esp
DB   0x83,0xec,0x18                                         //008FFF8B - sub esp,18
DB   0x53                                                   //008FFF8E - push ebx
DB   0x56                                                   //008FFF8F - push esi
DB   0x8b,0xf1                                              //008FFF90 - mov esi,ecx
DB   0x33,0xdb                                              //008FFF92 - xor ebx,ebx
DB   0x39,0x9e,0xd4,0x73,0x00,0x00                          //008FFF94 - cmp [esi+000073d4],ebx
je Doggy0090008c                                            //008FFF9A - je 0090008c
DB   0x8b,0x0d,0xdc,0x06,0xe2,0x00                          //008FFFA0 - mov ecx,[00e206dc] : 00000000
DB   0x57                                                   //008FFFA6 - push edi
DB   0x8d,0x45,0xe8                                         //008FFFA7 - lea eax,[ebp-18]
DB   0x50                                                   //008FFFAA - push eax
Call Doggy_00694581                                         //008FFFAB - call 00694581
DB   0x8d,0x45,0xe8                                         //008FFFB0 - lea eax,[ebp-18]
DB   0x50                                                   //008FFFB3 - push eax
DB   0xff,0x15,0x1c,0x33,0xb3,0x00                          //008FFFB4 - call dword ptr [00b3331c] : 77D298FE
DB   0x85,0xc0                                              //008FFFBA - test eax,eax
jne Doggy0090007f                                           //008FFFBC - jne 0090007f
DB   0x8d,0x45,0xf8                                         //008FFFC2 - lea eax,[ebp-08]
DB   0x50                                                   //008FFFC5 - push eax
DB   0x8d,0x8e,0xc0,0x23,0x00,0x00                          //008FFFC6 - lea ecx,[esi+000023c0]
Call Doggy_0043183c                                         //008FFFCC - call 0043183c
DB   0xff,0x70,0x04                                         //008FFFD1 - push [eax+04]
DB   0xff,0x30                                              //008FFFD4 - push [eax]
DB   0x8d,0x45,0xe8                                         //008FFFD6 - lea eax,[ebp-18]
DB   0x50                                                   //008FFFD9 - push eax
DB   0xff,0x15,0x18,0x33,0xb3,0x00                          //008FFFDA - call dword ptr [00b33318] : 77D29719
DB   0x85,0xc0                                              //008FFFE0 - test eax,eax
je Doggy0090007f                                            //008FFFE2 - je 0090007f
DB   0x8b,0x0d,0xdc,0x06,0xe2,0x00                          //008FFFE8 - mov ecx,[00e206dc] : 00000000
DB   0x53                                                   //008FFFEE - push ebx
Call Doggy_006935ff                                         //008FFFEF - call 006935ff
DB   0x33,0xff                                              //008FFFF4 - xor edi,edi
DB   0x47                                                   //008FFFF6 - inc edi
DB   0x85,0xc0                                              //008FFFF7 - test eax,eax
je Doggy00900082                                            //008FFFF9 - je 00900082
DB   0x39,0xbe,0xd4,0x73,0x00,0x00                          //008FFFFF - cmp [esi+000073d4],edi
jne Doggy0090008b                                           //00900005 - jne 0090008b
DB   0x39,0x9e,0xd8,0x73,0x00,0x00                          //0090000B - cmp [esi+000073d8],ebx
jle Doggy00900082                                           //00900011 - jle 00900082
DB   0x8b,0x86,0xe4,0x73,0x00,0x00                          //00900013 - mov eax,[esi+000073e4]
DB   0x3d,0x15,0x01,0x00,0x00                               //00900019 - cmp eax,00000115
jnge Doggy00900027                                          //0090001E - jnge 00900027
DB   0x3d,0x16,0x01,0x00,0x00                               //00900020 - cmp eax,00000116
jle Doggy00900035                                           //00900025 - jle 00900035
Doggy00900027:
DB   0x3d,0xb3,0x01,0x00,0x00                               //00900027 - cmp eax,000001b3
jnge Doggy00900082                                          //0090002C - jnge 00900082
DB   0x3d,0xb6,0x01,0x00,0x00                               //0090002E - cmp eax,000001b6
jg Doggy00900082                                            //00900033 - jg 00900082
Doggy00900035:
DB   0x8b,0x86,0xdc,0x73,0x00,0x00                          //00900035 - mov eax,[esi+000073dc]
DB   0x3b,0xc3                                              //0090003B - cmp eax,ebx
jle Doggy00900075                                           //0090003D - jle 00900075
//DB   0x39,0x45,0x08                                         //0090003F - cmp [ebp+08],eax
//jnge Doggy00900075                                          //00900042 - jnge 00900075
//DB   0x39,0x9e,0xe0,0x73,0x00,0x00                          //00900044 - cmp [esi+000073e0],ebx
//jg Doggy0090004f                                            //0090004A - jg 0090004f
//DB   0x53                                                   //0090004C - push ebx
//jmp Doggy00900083                                           //0090004D - jmp 00900083
Doggy0090004f:
DB   0x8b,0x0d,0xdc,0x06,0xe2,0x00                          //0090004F - mov ecx,[00e206dc] : 00000000
Call Doggy_0069596e                                         //00900055 - call 0069596e
DB   0x85,0xc0                                              //0090005A - test eax,eax
je Doggy00900082                                            //0090005C - je 00900082
DB   0xff,0x8e,0xe0,0x73,0x00,0x00                          //0090005E - dec [esi+000073e0]
DB   0xa1,0xdc,0x06,0xe2,0x00                               //00900064 - mov eax,[00e206dc] : 00000000
DB   0x8b,0x40,0x5c                                         //00900069 - mov eax,[eax+5c]
DB   0x03,0x45,0x08                                         //0090006C - add eax,[ebp+08]
DB   0x89,0x86,0xdc,0x73,0x00,0x00                          //0090006F - mov [esi+000073dc],eax
Doggy00900075:
DB   0x39,0x9e,0xdc,0x73,0x00,0x00                          //00900075 - cmp [esi+000073dc],ebx
jg Doggy0090008b                                            //0090007B - jg 0090008b
jmp Doggy00900082                                           //0090007D - jmp 00900082
Doggy0090007f:
DB   0x33,0xff                                              //0090007F - xor edi,edi
DB   0x47                                                   //00900081 - inc edi
Doggy00900082:
DB   0x57                                                   //00900082 - push edi
Doggy00900083:
DB   0x57                                                   //00900083 - push edi
DB   0x8b,0xce                                              //00900084 - mov ecx,esi
Call Doggy_008f662a                                         //00900086 - call 008f662a
Doggy0090008b:
DB   0x5f                                                   //0090008B - pop edi
Doggy0090008c:
DB   0x5e                                                   //0090008C - pop esi
DB   0x5b                                                   //0090008D - pop ebx
DB   0xc9                                                   //0090008E - leave
DB   0xc2,0x04,0x00                                         //0090008F - ret 0004
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}








int ItemVacSwitch = 0;
void __declspec(naked) MyPtInRect(){__asm{
db 0x55, 0x8B, 0xEC, 0x8B, 0x45, 0x08, 0x85, 0xC0, 0x74, 0x20, 0x8B, 0x4D, 0x0C, 0x3B, 0x08, 0x7C, 0x19, 0x3B, 0x48, 0x08
db 0x7D, 0x14, 0x8B, 0x4D, 0x10, 0x3B, 0x48, 0x04, 0x7C, 0x0C, 0x3B, 0x48, 0x0C, 0x7D, 0x07, 0x33, 0xC0, 0x40, 0x5D, 0xC2
db 0x0C, 0x00, 0x33, 0xC0, 0xEB, 0xF8
}}
void __declspec(naked) ItemVac_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_ItemVac_asm");
#endif
__asm
{
cmp [esp],0x004EC48E // 85 c0 75 ?? 83 4d fc ff 8d 4d ?? e8 ?? ?? ff ff 83 7d f0 00 0f 85
je SetItemXY
cmp [esp],0x004EB736 // 85 C0 74 07 39 5D ?? 75
jne MyPtInRect
xor eax,eax
inc eax
ret 0x000c

SetItemXY:
cmp [ItemVacSwitch], 0
jne ItemVac
jmp MyPtInRect
ItemVac:
mov eax,[esp+0x08]
mov [ebx],eax
mov eax,[esp+0x0C]
mov [ebx+0x04],eax
xor eax,eax
inc eax
ret 0x000c
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}


void __declspec(naked) FixedSSAction_asm()
{
#ifdef VMProtectSDK
VMProtectBegin("_FixedSSAction_asm");
#endif
__asm
{
cmp [esp],0x0097C47B // 85 C0 74 ?? 8B 06 5F
jne NormalReturn
cmp [ItemVacSwitch], 0
je  NormalReturn
add esp, 04
mov eax, 0x009894C6
call eax
xor eax,eax
Push 0x0097C47B
Ret

NormalReturn:
Push 0x009894C6 // 55 8B EC 83 EC ?? 53 8B 1D ?? ?? ?? 00 56 8B F1 57
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}









int VacX, VacY;
int MobVacSwitch = 0;
void __declspec(naked) MobVac_asm() {
#ifdef VMProtectSDK
VMProtectBegin("_MobVac_asm");
#endif
__asm {
mov eax,[esi+0x00000730]
pushad

cmp [MobVacSwitch],0
je NormalBack

Test Esi, Esi
Je   NormalBack
Mov  Eax, [Esi]
Test Eax, Eax
Je   NormalBack
Cmp  [Eax], 0x009845C6 // 56 8B F1 E8 ?? ?? FF FF F6 44 24 08 01 74 0B 56 B9 ?? ?? ?? 00 E8 ?? ?? ?? FF 8B C6 5E C2 04 00 6A 04 B8 ?? ?? ?? 00 E8 ?? ?? ?? 00 68 ?? 07 00 00
Jne  NormalBack

// 只吸一次
Cmp  [Esi+0x04], 01
Je   NormalBack

// 檢測怪物類型
Cmp  [Esi+0x000002A8], 01 // 走怪
Je   MobVac
Cmp  [Esi+0x000002A8], 03 // 跳怪
Je   MobVac
Jmp  NormalBack

MobVac:
mov eax,esi
mov ebx,eax
mov ecx,ebx
add eax,0x10
add ecx,0x10
mov edi,[eax]
Push 00
Push 00
Push 00
Push 00
Push [VacY]
Push [VacX]
Push 06
mov [Esi+4],01
Call dword ptr [Edi+0x84]
NormalBack:
popad
push 0x00612200
ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}




int CharX = 0, CharY = 0;
void __declspec(naked) GetXY()
{
#ifdef VMProtectSDK
VMProtectBegin("GetXY");
#endif
	__asm
	{
		Sub  Esp, 08
		Mov  Eax, Esp
		Pushad
		Mov  Ebx, 0x004A3704
		Mov  Ecx, [0x00e1847c] // CharBase
		Test Ecx, Ecx
		Je   _Exit
		Add  Ecx, 4
		Push Eax
		Call Ebx
		Push [Eax]
		Pop  [CharX]
		Push [Eax+4]
		Pop  [CharY]
_Exit:
		Popad
		Add  Esp, 08
		Ret
	}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}




int LRStep = 0, LRTick = 0;
void __declspec(naked) AutoLR_asm() {
__asm {
Cmp  [MobVacSwitch], 0
Je   Back2GetFocus
Cmp  [Esp], 0x009895B7
Je   AutoLR
Back2GetFocus:
Jmp  GetFocus
/* LRStep
 *   1 往右
 *   2 等待往左
 *   3 往左
 *   4 等待往右
 */
AutoLR:
Add  Esp, 0x04
Pushad
Call GetXY
Cmp  [LRStep], 1
Je   Step1
Cmp  [LRStep], 2
Je   Step2
Cmp  [LRStep], 3
Je   Step3
Cmp  [LRStep], 4
Je   Step4
Jmp  GoStop

Step1:
Mov  Eax, [VacX]
Add  Eax, 50
Cmp  [CharX], Eax
Jl   GoRight
Mov  [LRStep], 2
Call GetTicket
Add  Eax, 10000
Mov  [LRTick], Eax
Jmp  GoLeft

Step2:
Call GetTicket
Cmp  [LRTick], Eax
Jg   GoStop
Mov  [LRStep], 3
Jmp  GoLeft

Step3:
Mov  Eax, [VacX]
Sub  Eax, 50
Cmp  [CharX], Eax
Jg   GoLeft
Mov  [LRStep], 4
Call GetTicket
Add  Eax, 10000
Mov  [LRTick], Eax
Jmp  GoRight

Step4:
Call GetTicket
Cmp  [LRTick], Eax
Jg   GoStop
Mov  [LRStep], 1
Jmp  GoRight

GoStop:
Mov  [Ebp-0x04], 0x00000000
Jmp  Back
GoLeft:
Mov  [Ebp-0x04], 0xFFFFFFFF
Jmp  Back
GoRight:
Mov  [Ebp-0x04], 0x00000001
Jmp  Back

Back:
Popad
Push 0x0098988A
Ret
}
}



#include "Functions.h"

long NoDelayBuffSwitch = 0;
long NDelay00a11105=0x00a11105,NDelay006dcb13=0x006dcb13,NDelay0049ea16=0x0049ea16,NDelay0049eac9=0x0049eac9,NDelay004e79ed=0x004e79ed,NDelay004e8077=0x004e8077,NDelay0092fe08=0x0092fe08,NDelay00421033=0x00421033,NDelay0042185e=0x0042185e,NDelay006ae7d3=0x006ae7d3,NDelay008ed5eb=0x008ed5eb,NDelay006adbc9=0x006adbc9,NDelay0042fdc0=0x0042fdc0,NDelay0072c863=0x0072c863,NDelay00420581=0x00420581,NDelay004545f7=0x004545f7,NDelay0040f4dd=0x0040f4dd,NDelay006567a4=0x006567a4,NDelay0094fb19=0x0094fb19,NDelay00412ab6=0x00412ab6,NDelay00412a98=0x00412a98,NDelay00427b21=0x00427b21,NDelay004964a6=0x004964a6,NDelay00426d00=0x00426d00,NDelay00a0f711=0x00a0f711;
void __declspec(naked) NoDelayBuff_asm() {
#ifdef VMProtectSDK
VMProtectBegin("_NoDelayBuff");
#endif
__asm {
/*Cmp  [NoDelayBuffSwitch], 0
Je   Return
Cmp  [Esp], 0x00933D15
Je   Hook
Return:
Push 0x008C351B
Ret

Hook:
Add  Esp, 04
Call [Eax+0x20]
Xor  Eax, Eax
Dec  Eax
Mov  [Esi+0x000004A0], Eax

DB   0x83,0xbe,0xb0,0x45,0x00,0x00,0x00                     //00933D15 - cmp dword ptr [esi+000045b0],00
je Doggy00933d8c                                            //00933D1C - je 00933d8c
Call NDelay00a11105                                         //00933D1E - call 00a11105
DB   0x50                                                   //00933D23 - push eax
DB   0xff,0x75,0x0c                                         //00933D24 - push [ebp+0c]
DB   0x8b,0xcb                                              //00933D27 - mov ecx,ebx
Call NDelay006dcb13                                         //00933D29 - call 006dcb13
DB   0x51                                                   //00933D2E - push ecx
DB   0x8b,0xcc                                              //00933D2F - mov ecx,esp
DB   0x89,0x65,0xe8                                         //00933D31 - mov [ebp-18],esp
DB   0x50                                                   //00933D34 - push eax
DB   0x51                                                   //00933D35 - push ecx
Call NDelay0049ea16                                         //00933D36 - call 0049ea16
DB   0x59                                                   //00933D3B - pop ecx
DB   0x59                                                   //00933D3C - pop ecx
Call NDelay0049eac9                                         //00933D3D - call 0049eac9
DB   0x59                                                   //00933D42 - pop ecx
DB   0x89,0x45,0xe8                                         //00933D43 - mov [ebp-18],eax
DB   0x85,0xc0                                              //00933D46 - test eax,eax
jnge Doggy00933d4f                                          //00933D48 - jnge 00933d4f
DB   0x83,0xf8,0x1f                                         //00933D4A - cmp eax,1f
jnge Doggy00933d53                                          //00933D4D - jnge 00933d53
Doggy00933d4f:
DB   0x83,0x65,0xe8,0x00                                    //00933D4F - and dword ptr [ebp-18],00
Doggy00933d53:
DB   0x8b,0x8e,0xb0,0x45,0x00,0x00                          //00933D53 - mov ecx,[esi+000045b0]
DB   0x8b,0xbe,0x9c,0x04,0x00,0x00                          //00933D59 - mov edi,[esi+0000049c]
Call NDelay004e79ed                                         //00933D5F - call 004e79ed
DB   0x8b,0x8e,0xb0,0x45,0x00,0x00                          //00933D64 - mov ecx,[esi+000045b0]
DB   0x8b,0xd0                                              //00933D6A - mov edx,eax
DB   0x33,0xd7                                              //00933D6C - xor edx,edi
DB   0x83,0xe2,0x01                                         //00933D6E - and edx,01
DB   0x6a,0x00                                              //00933D71 - push 00
DB   0x33,0xd0                                              //00933D73 - xor edx,eax
DB   0x52                                                   //00933D75 - push edx
Call NDelay004e8077                                         //00933D76 - call 004e8077
DB   0xff,0x75,0xe8                                         //00933D7B - push [ebp-18]
DB   0x8b,0x8e,0xb0,0x45,0x00,0x00                          //00933D7E - mov ecx,[esi+000045b0]
Call NDelay0092fe08                                         //00933D84 - call 0092fe08
DB   0x8b,0x7d,0xf0                                         //00933D89 - mov edi,[ebp-10]
Doggy00933d8c:
DB   0x8d,0x8e,0x90,0x00,0x00,0x00                          //00933D8C - lea ecx,[esi+00000090]
Call NDelay00421033                                         //00933D92 - call 00421033
DB   0x83,0xf8,0xff                                         //00933D97 - cmp eax,ff
jle Doggy00933de3                                           //00933D9A - jle 00933de3
DB   0x83,0xbe,0x24,0x04,0x00,0x00,0x00                     //00933D9C - cmp dword ptr [esi+00000424],00
jne Doggy00933de3                                           //00933DA3 - jne 00933de3
DB   0x8d,0x8e,0x90,0x00,0x00,0x00                          //00933DA5 - lea ecx,[esi+00000090]
Call NDelay00421033                                         //00933DAB - call 00421033
DB   0x8b,0xf8                                              //00933DB0 - mov edi,eax
DB   0x6b,0xff,0x18                                         //00933DB2 - imul edi,edi,18
DB   0x81,0xc7,0xc0,0x0d,0xe1,0x00                          //00933DB5 - add edi,00e10dc0
DB   0x83,0x7f,0x0c,0x00                                    //00933DBB - cmp dword ptr [edi+0c],00
je Doggy00933ddc                                            //00933DBF - je 00933ddc
DB   0x8d,0x8e,0x90,0x00,0x00,0x00                          //00933DC1 - lea ecx,[esi+00000090]
Call NDelay0042185e                                         //00933DC7 - call 0042185e
DB   0x8b,0x40,0x08                                         //00933DCC - mov eax,[eax+08]
DB   0x0f,0xaf,0x47,0x10                                    //00933DCF - imul eax,[edi+10]
DB   0x99                                                   //00933DD3 - cdq
DB   0xf7,0x7f,0x0c                                         //00933DD4 - idiv [edi+0c]
DB   0x89,0x45,0x08                                         //00933DD7 - mov [ebp+08],eax
jmp Doggy00933de0                                           //00933DDA - jmp 00933de0
Doggy00933ddc:
DB   0x83,0x65,0x08,0x00                                    //00933DDC - and dword ptr [ebp+08],00
Doggy00933de0:
DB   0x8b,0x7d,0xf0                                         //00933DE0 - mov edi,[ebp-10]
Doggy00933de3:
DB   0x8b,0x03                                              //00933DE3 - mov eax,[ebx]
DB   0x3d,0x6e,0x6a,0x23,0x00                               //00933DE5 - cmp eax,00236a6e
jne Doggy00933df6                                           //00933DEA - jne 00933df6
DB   0x83,0x7d,0x10,0x00                                    //00933DEC - cmp dword ptr [ebp+10],00
je Doggy00933fbe                                            //00933DF0 - je 00933fbe
Doggy00933df6:
DB   0x50                                                   //00933DF6 - push eax
Call NDelay006ae7d3                                         //00933DF7 - call 006ae7d3
DB   0x59                                                   //00933DFC - pop ecx
DB   0x85,0xc0                                              //00933DFD - test eax,eax
je Doggy00933e35                                            //00933DFF - je 00933e35
DB   0x8b,0x07                                              //00933E01 - mov eax,[edi]
DB   0x8d,0x4d,0xec                                         //00933E03 - lea ecx,[ebp-14]
DB   0x51                                                   //00933E06 - push ecx
DB   0x8b,0xcf                                              //00933E07 - mov ecx,edi
DB   0xff,0x50,0x10                                         //00933E09 - call dword ptr [eax+10]
DB   0x8d,0x4d,0xd8                                         //00933E0C - lea ecx,[ebp-28]
DB   0x89,0x45,0xe8                                         //00933E0F - mov [ebp-18],eax
DB   0x8b,0x07                                              //00933E12 - mov eax,[edi]
DB   0x51                                                   //00933E14 - push ecx
DB   0x8b,0xcf                                              //00933E15 - mov ecx,edi
DB   0xff,0x50,0x10                                         //00933E17 - call dword ptr [eax+10]
DB   0xff,0x70,0x04                                         //00933E1A - push [eax+04]
DB   0x8b,0x45,0xe8                                         //00933E1D - mov eax,[ebp-18]
DB   0xff,0x30                                              //00933E20 - push [eax]
DB   0x8d,0x8e,0x94,0x61,0x00,0x00                          //00933E22 - lea ecx,[esi+00006194]
Call NDelay008ed5eb                                         //00933E28 - call 008ed5eb
DB   0x85,0xc0                                              //00933E2D - test eax,eax
jne _00933bf6                                                 //00933E2F - je 00933bf6
Doggy00933e35:
DB   0xff,0x33                                              //00933E35 - push [ebx]
Call NDelay006adbc9                                         //00933E37 - call 006adbc9
DB   0x59                                                   //00933E3C - pop ecx
DB   0x85,0xc0                                              //00933E3D - test eax,eax
je Doggy00933e93                                            //00933E3F - je 00933e93
Call NDelay0042fdc0                                         //00933E41 - call 0042fdc0
DB   0xf7,0x80,0xbc,0x01,0x00,0x00,0x00,0x02,0x00,0x00      //00933E46 - test [eax+000001bc],0200
je Doggy00933e93                                            //00933E50 - je 00933e93
DB   0x8d,0x45,0x0c                                         //00933E52 - lea eax,[ebp+0c]
DB   0x68,0xe3,0x10,0x00,0x00                               //00933E55 - push 000010e3
DB   0x50                                                   //00933E5A - push eax
Call NDelay0072c863                                         //00933E5B - call 0072c863
DB   0x8b,0xc8                                              //00933E60 - mov ecx,eax
Call NDelay00420581                                         //00933E62 - call 00420581
DB   0x83,0x65,0xfc,0x00                                    //00933E67 - and dword ptr [ebp-04],00
DB   0x6a,0x0b                                              //00933E6B - push 0b
DB   0x50                                                   //00933E6D - push eax
Call NDelay004545f7                                         //00933E6E - call 004545f7
DB   0x8b,0x45,0x0c                                         //00933E73 - mov eax,[ebp+0c]
DB   0x83,0x4d,0xfc,0xff                                    //00933E76 - or dword ptr [ebp-04],ff
DB   0x59                                                   //00933E7A - pop ecx
DB   0x59                                                   //00933E7B - pop ecx
DB   0x85,0xc0                                              //00933E7C - test eax,eax
je _00933bf6                                                 //00933E7E - je 00933bf6
DB   0x83,0xc0,0xf4                                         //00933E84 - add eax,f4
DB   0x50                                                   //00933E87 - push eax
Call NDelay0040f4dd                                         //00933E88 - call 0040f4dd
DB   0x59                                                   //00933E8D - pop ecx
jmp _00933bf6                                                //00933E8E - jmp 00933bf6
Doggy00933e93:
DB   0x68,0xa6,0x00,0x00,0x00                               //00933E93 - push 000000a6
DB   0x8d,0x4d,0xc0                                         //00933E98 - lea ecx,[ebp-40]
Call NDelay006567a4                                         //00933E9B - call 006567a4
DB   0xc7,0x45,0xfc,0x01,0x00,0x00,0x00                     //00933EA0 - mov [ebp-04],00000001
Call NDelay0094fb19                                         //00933EA7 - call 0094fb19
DB   0x50                                                   //00933EAC - push eax
DB   0x8d,0x4d,0xc0                                         //00933EAD - lea ecx,[ebp-40]
Call NDelay00412ab6                                         //00933EB0 - call 00412ab6
DB   0xff,0x33                                              //00933EB5 - push [ebx]
DB   0x8d,0x4d,0xc0                                         //00933EB7 - lea ecx,[ebp-40]
Call NDelay00412ab6                                         //00933EBA - call 00412ab6
DB   0xff,0x75,0x0c                                         //00933EBF - push [ebp+0c]
DB   0x8d,0x4d,0xc0                                         //00933EC2 - lea ecx,[ebp-40]
Call NDelay00412a98                                         //00933EC5 - call 00412a98
DB   0xff,0x33                                              //00933ECA - push [ebx]
Call NDelay006ae7d3                                         //00933ECC - call 006ae7d3
DB   0x59                                                   //00933ED1 - pop ecx
DB   0x85,0xc0                                              //00933ED2 - test eax,eax
je Doggy00933f05                                            //00933ED4 - je 00933f05
DB   0x8b,0x07                                              //00933ED6 - mov eax,[edi]
DB   0x8d,0x4d,0xd8                                         //00933ED8 - lea ecx,[ebp-28]
DB   0x51                                                   //00933EDB - push ecx
DB   0x8b,0xcf                                              //00933EDC - mov ecx,edi
DB   0xff,0x50,0x10                                         //00933EDE - call dword ptr [eax+10]
DB   0x0f,0xb7,0x00                                         //00933EE1 - movzx eax,word ptr [eax]
DB   0x50                                                   //00933EE4 - push eax
DB   0x8d,0x4d,0xc0                                         //00933EE5 - lea ecx,[ebp-40]
Call NDelay00427b21                                         //00933EE8 - call 00427b21
DB   0x8b,0x07                                              //00933EED - mov eax,[edi]
DB   0x8d,0x4d,0xd0                                         //00933EEF - lea ecx,[ebp-30]
DB   0x51                                                   //00933EF2 - push ecx
DB   0x8b,0xcf                                              //00933EF3 - mov ecx,edi
DB   0xff,0x50,0x10                                         //00933EF5 - call dword ptr [eax+10]
DB   0x0f,0xb7,0x40,0x04                                    //00933EF8 - movzx eax,word ptr [eax+04]
DB   0x50                                                   //00933EFC - push eax
DB   0x8d,0x4d,0xc0                                         //00933EFD - lea ecx,[ebp-40]
Call NDelay00427b21                                         //00933F00 - call 00427b21
Doggy00933f05:
DB   0x8b,0x03                                              //00933F05 - mov eax,[ebx]
DB   0x3d,0xa1,0xba,0x3e,0x00                               //00933F07 - cmp eax,003ebaa1
je Doggy00933f1c                                            //00933F0C - je 00933f1c
DB   0x3d,0x1f,0x51,0xd7,0x00                               //00933F0E - cmp eax,00d7511f
je Doggy00933f1c                                            //00933F13 - je 00933f1c
DB   0x3d,0x70,0x5c,0x4f,0x00                               //00933F15 - cmp eax,004f5c70
jne Doggy00933f27                                           //00933F1A - jne 00933f27
Doggy00933f1c:
DB   0xff,0x75,0x1c                                         //00933F1C - push [ebp+1c]
DB   0x8d,0x4d,0xc0                                         //00933F1F - lea ecx,[ebp-40]
Call NDelay00412ab6                                         //00933F22 - call 00412ab6
Doggy00933f27:
DB   0x33,0xff                                              //00933F27 - xor edi,edi
DB   0x39,0x7d,0x10                                         //00933F29 - cmp [ebp+10],edi
je Doggy00933f55                                            //00933F2C - je 00933f55
DB   0xff,0x75,0x10                                         //00933F2E - push [ebp+10]
DB   0x8d,0x4d,0xc0                                         //00933F31 - lea ecx,[ebp-40]
Call NDelay00412a98                                         //00933F34 - call 00412a98
DB   0x81,0x3b,0x59,0x43,0x23,0x00                          //00933F39 - cmp [ebx],00234359
jne Doggy00933f55                                           //00933F3F - jne 00933f55
DB   0xff,0x75,0x08                                         //00933F41 - push [ebp+08]
DB   0x8d,0x4d,0xc0                                         //00933F44 - lea ecx,[ebp-40]
Call NDelay00427b21                                         //00933F47 - call 00427b21
DB   0x57                                                   //00933F4C - push edi
DB   0x8d,0x4d,0xc0                                         //00933F4D - lea ecx,[ebp-40]
Call NDelay00412a98                                         //00933F50 - call 00412a98
Doggy00933f55:
DB   0x8b,0x75,0x14                                         //00933F55 - mov esi,[ebp+14]
DB   0x3b,0xf7                                              //00933F58 - cmp esi,edi
jnge Doggy00933f7c                                          //00933F5A - jnge 00933f7c
DB   0x56                                                   //00933F5C - push esi
DB   0x8d,0x4d,0xc0                                         //00933F5D - lea ecx,[ebp-40]
Call NDelay00412a98                                         //00933F60 - call 00412a98
DB   0x85,0xf6                                              //00933F65 - test esi,esi
jle Doggy00933f7c                                           //00933F67 - jle 00933f7c
Doggy00933f69:
DB   0x8b,0x45,0x18                                         //00933F69 - mov eax,[ebp+18]
DB   0xff,0x34,0xb8                                         //00933F6C - push [eax+edi*4]
DB   0x8d,0x4d,0xc0                                         //00933F6F - lea ecx,[ebp-40]
Call NDelay00412ab6                                         //00933F72 - call 00412ab6
DB   0x47                                                   //00933F77 - inc edi
DB   0x3b,0xfe                                              //00933F78 - cmp edi,esi
jnge Doggy00933f69                                          //00933F7A - jnge 00933f69
Doggy00933f7c:
DB   0xff,0x75,0x08                                         //00933F7C - push [ebp+08]
DB   0x8d,0x4d,0xc0                                         //00933F7F - lea ecx,[ebp-40]
Call NDelay00427b21                                         //00933F82 - call 00427b21
DB   0x6a,0x00                                              //00933F87 - push 00
DB   0x8d,0x4d,0xc0                                         //00933F89 - lea ecx,[ebp-40]
Call NDelay00412a98                                         //00933F8C - call 00412a98
DB   0x8b,0x0d,0xcc,0xbf,0xe0,0x00                          //00933F91 - mov ecx,[00e0bfcc] : 00000000
DB   0x8d,0x45,0xc0                                         //00933F97 - lea eax,[ebp-40]
DB   0x50                                                   //00933F9A - push eax
//SendPacket
//Call NDelay004964a6                                         //00933F9B - call 004964a6
Push 0x00933FB2 // Ret
Push 0x004964a6 // Call
Ret
//DB   0x81,0x3b,0xaa,0x12,0x16,0x02                          //00933FA0 - cmp [ebx],021612aa
//je Doggy00933fb2                                            //00933FA6 - je 00933fb2
//DB   0x8b,0x4d,0xe0                                         //00933FA8 - mov ecx,[ebp-20]
//DB   0x6a,0x01                                              //00933FAB - push 01
//Call NDelay0048b540                                         //00933FAD - call 0048b540
//Doggy00933fb2:
DB   0x83,0x4d,0xfc,0xff                                    //00933FB2 - or dword ptr [ebp-04],ff
DB   0x8d,0x4d,0xc4                                         //00933FB6 - lea ecx,[ebp-3c]
Call NDelay00426d00                                         //00933FB9 - call 00426d00
Doggy00933fbe:
DB   0x33,0xc0                                              //00933FBE - xor eax,eax
DB   0x40                                                   //00933FC0 - inc eax
Call NDelay00a0f711                                         //00933FC1 - call 00a0f711
DB   0xc2,0x1c,0x00                                         //00933FC6 - ret 001c
_00933bf6:
push 0x00933bf6
ret*/
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
