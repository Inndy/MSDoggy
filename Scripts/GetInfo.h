// ICS: [00C80FD8] = 00867D24, End At 00867F74


int HpNow = 0,
	HpFull = 0,
	MpNow = 0,
	MpFull = 0,
	ExpNow = 0,
	ExpFull = 0,
	LevelNow = 0;

void __declspec(naked) _GetInfo()
{
__asm
{
Add  Esp, 04
Pop  [HpNow]
Pop  [HpFull]
Pop  [MpNow]
Pop  [MpFull]
Pop  [ExpNow]
Pop  [ExpFull]
Sub  Esp, 0x1C
Push 0x00863217
Ret
}
}

long Doggy_00a169a9 = 0x00a169a9;
long Doggy_00422812 = 0x00422812;
long Doggy_0042189f = 0x0042189f;
long Doggy_0042fdb1 = 0x0042fdb1;
long Doggy_00422c7a = 0x00422c7a;
long Doggy_0046b7f5 = 0x0046b7f5;
long Doggy_0046b7bd = 0x0046b7bd;
long Doggy_00860df2 = 0x00860df2;
long Doggy_004c8a25 = 0x004c8a25;
long Doggy_006f0595 = 0x006f0595;
long Doggy_0040582b = 0x0040582b;
long Doggy_004c8a10 = 0x004c8a10;
long Doggy_00863217 = (long)_GetInfo;
long Doggy_004068da = 0x004068da;
long Doggy_006fe6fd = 0x006fe6fd;
long Doggy_0085e685 = 0x0085e685;
long Doggy_0085f55f = 0x0085f55f;
long Doggy_00866199 = 0x00866199;
long Doggy_0085ebfe = 0x0085ebfe;
long Doggy_00a16a81 = 0x00a16a81;


void __declspec(naked) GetInfo_asm()
{
// Head  // 6a 24 b8 ?? ?? ?? 00 e8 ?? ?? ?? 00 8b d9 8b 3d ?? ?? ?? 00 8d
// End   // C2 04 00 56 8D B1 ?? ?? 00 00 8B CE E8
// Hook  // e8 ?? ?? ff ff 83 ec 20 8b cc 89 65 ?? 68 00 01 00 00 68
// Level // 50 E8 ?? ?? ?? FF 33 C9 41
__asm
{
DB   0x6a,0x24                                              //00867D24 - push 24
DB   0xb8,0x0e,0xc0,0xad,0x00                               //00867D26 - mov eax,00adc00e
Call Doggy_00a169a9                                         //00867D2B - call 00a169a9
DB   0x8b,0xd9                                              //00867D30 - mov ebx,ecx
DB   0x8b,0x3d,0xe0,0x81,0xe1,0x00                          //00867D32 - mov edi,[00e181e0] : 00E2AB58
DB   0x8d,0x45,0xd8                                         //00867D38 - lea eax,[ebp-28]
DB   0x50                                                   //00867D3B - push eax
DB   0x8b,0xcf                                              //00867D3C - mov ecx,edi
Call Doggy_00422812                                         //00867D3E - call 00422812
DB   0x33,0xc9                                              //00867D43 - xor ecx,ecx
DB   0x39,0x48,0x04                                         //00867D45 - cmp [eax+04],ecx
DB   0x0f,0x94,0xc1                                         //00867D48 - sete cl
DB   0x8b,0xf1                                              //00867D4B - mov esi,ecx
DB   0x8d,0x4d,0xd8                                         //00867D4D - lea ecx,[ebp-28]
Call Doggy_0042189f                                         //00867D50 - call 0042189f
DB   0x85,0xf6                                              //00867D55 - test esi,esi
jne Doggy00867f6f                                           //00867D57 - jne 00867f6f
DB   0x8d,0x45,0xd0                                         //00867D5D - lea eax,[ebp-30]
DB   0x50                                                   //00867D60 - push eax
DB   0x8b,0xcf                                              //00867D61 - mov ecx,edi
Call Doggy_00422812                                         //00867D63 - call 00422812
DB   0x8b,0x70,0x04                                         //00867D68 - mov esi,[eax+04]
DB   0x8d,0x4d,0xd0                                         //00867D6B - lea ecx,[ebp-30]
Call Doggy_0042189f                                         //00867D6E - call 0042189f
DB   0x8d,0x87,0xc0,0x21,0x00,0x00                          //00867D73 - lea eax,[edi+000021c0]
DB   0x89,0x45,0xdc                                         //00867D79 - mov [ebp-24],eax
Call Doggy_0042fdb1                                         //00867D7C - call 0042fdb1
DB   0x85,0xc0                                              //00867D81 - test eax,eax
je Doggy00867ded                                            //00867D83 - je 00867ded
DB   0x83,0xb8,0xb4,0x01,0x00,0x00,0x16                     //00867D85 - cmp dword ptr [eax+000001b4],16
jne Doggy00867ded                                           //00867D8C - jne 00867ded
DB   0x51                                                   //00867D8E - push ecx
DB   0x8b,0xcc                                              //00867D8F - mov ecx,esp
DB   0x83,0x21,0x00                                         //00867D91 - and dword ptr [ecx],00
DB   0x89,0x65,0xe0                                         //00867D94 - mov [ebp-20],esp
DB   0x6a,0xff                                              //00867D97 - push ff
DB   0x8d,0x46,0x04                                         //00867D99 - lea eax,[esi+04]
DB   0x50                                                   //00867D9C - push eax
Call Doggy_00422c7a                                         //00867D9D - call 00422c7a
DB   0xff,0x76,0x27                                         //00867DA2 - push [esi+27]
DB   0x83,0x65,0xfc,0x00                                    //00867DA5 - and dword ptr [ebp-04],00
DB   0x8d,0x46,0x23                                         //00867DA9 - lea eax,[esi+23]
DB   0x50                                                   //00867DAC - push eax
Call Doggy_0046b7f5                                         //00867DAD - call 0046b7f5
DB   0xff,0x76,0x27                                         //00867DB2 - push [esi+27]
DB   0x0f,0xb7,0xc0                                         //00867DB5 - movzx eax,ax
DB   0x89,0x45,0xec                                         //00867DB8 - mov [ebp-14],eax
DB   0x8d,0x46,0x23                                         //00867DBB - lea eax,[esi+23]
DB   0x50                                                   //00867DBE - push eax
Call Doggy_0046b7f5                                         //00867DBF - call 0046b7f5
DB   0x0f,0xbf,0x8e,0xdc,0x00,0x00,0x00                     //00867DC4 - movsx ecx,word ptr [esi+000000dc]
DB   0x0f,0xb7,0xc0                                         //00867DCB - movzx eax,ax
DB   0x83,0xc4,0x10                                         //00867DCE - add esp,10
DB   0x98                                                   //00867DD1 - cwde
DB   0x51                                                   //00867DD2 - push ecx
DB   0x0f,0xbf,0x4d,0xec                                    //00867DD3 - movsx ecx,word ptr [ebp-14]
DB   0x99                                                   //00867DD7 - cdq
DB   0x51                                                   //00867DD8 - push ecx
DB   0xb9,0xe8,0x03,0x00,0x00                               //00867DD9 - mov ecx,000003e8
DB   0xf7,0xf9                                              //00867DDE - idiv ecx
DB   0x48                                                   //00867DE0 - dec eax
DB   0xf7,0xd8                                              //00867DE1 - neg eax
DB   0x1b,0xc0                                              //00867DE3 - sbb eax,eax
DB   0x83,0xe0,0x50                                         //00867DE5 - and eax,50
DB   0x83,0xc0,0x78                                         //00867DE8 - add eax,78
jmp Doggy00867e39                                           //00867DEB - jmp 00867e39
Doggy00867ded:
DB   0x51                                                   //00867DED - push ecx
DB   0x8b,0xcc                                              //00867DEE - mov ecx,esp
DB   0x83,0x21,0x00                                         //00867DF0 - and dword ptr [ecx],00
DB   0x89,0x65,0xe0                                         //00867DF3 - mov [ebp-20],esp
DB   0x6a,0xff                                              //00867DF6 - push ff
DB   0x8d,0x46,0x04                                         //00867DF8 - lea eax,[esi+04]
DB   0x50                                                   //00867DFB - push eax
Call Doggy_00422c7a                                         //00867DFC - call 00422c7a
DB   0xff,0x76,0x27                                         //00867E01 - push [esi+27]
DB   0x8d,0x46,0x23                                         //00867E04 - lea eax,[esi+23]
DB   0x50                                                   //00867E07 - push eax
DB   0xc7,0x45,0xfc,0x01,0x00,0x00,0x00                     //00867E08 - mov [ebp-04],00000001
Call Doggy_0046b7f5                                         //00867E0F - call 0046b7f5
DB   0xff,0x76,0x1f                                         //00867E14 - push [esi+1f]
DB   0x0f,0xb7,0xc0                                         //00867E17 - movzx eax,ax
DB   0x89,0x45,0xec                                         //00867E1A - mov [ebp-14],eax
DB   0x8d,0x46,0x1d                                         //00867E1D - lea eax,[esi+1d]
DB   0x50                                                   //00867E20 - push eax
Call Doggy_0046b7bd                                         //00867E21 - call 0046b7bd
DB   0x0f,0xbf,0x8e,0xdc,0x00,0x00,0x00                     //00867E26 - movsx ecx,word ptr [esi+000000dc]
DB   0x83,0xc4,0x10                                         //00867E2D - add esp,10
DB   0x51                                                   //00867E30 - push ecx
DB   0x0f,0xbf,0x4d,0xec                                    //00867E31 - movsx ecx,word ptr [ebp-14]
DB   0x51                                                   //00867E35 - push ecx
DB   0x0f,0xb6,0xc0                                         //00867E36 - movzx eax,al
Doggy00867e39:
DB   0x83,0x4d,0xfc,0xff                                    //00867E39 - or dword ptr [ebp-04],ff
DB   0x50                                                   //00867E3D - push eax
DB   0x8b,0xcb                                              //00867E3E - mov ecx,ebx
Call Doggy_00860df2                                         //00867E40 - call 00860df2
DB   0xff,0x76,0x1f                                         //00867E45 - push [esi+1f]
DB   0x8d,0x46,0x1d                                         //00867E48 - lea eax,[esi+1d]
DB   0x50                                                   //00867E4B - push eax
Call Doggy_0046b7bd                                         //00867E4C - call 0046b7bd
DB   0x59                                                   //00867E51 - pop ecx
DB   0x59                                                   //00867E52 - pop ecx
DB   0x3c,0x32                                              //00867E53 - cmp al,32
jna Doggy00867e5d                                           //00867E55 - jna 00867e5d
DB   0x83,0x65,0xf0,0x00                                    //00867E57 - and dword ptr [ebp-10],00
jmp Doggy00867e67                                           //00867E5B - jmp 00867e67
Doggy00867e5d:
DB   0x8b,0xce                                              //00867E5D - mov ecx,esi
Call Doggy_004c8a25                                         //00867E5F - call 004c8a25
DB   0x89,0x45,0xf0                                         //00867E64 - mov [ebp-10],eax
Doggy00867e67:
DB   0xff,0x76,0x1f                                         //00867E67 - push [esi+1f]
DB   0x8d,0x46,0x1d                                         //00867E6A - lea eax,[esi+1d]
DB   0x50                                                   //00867E6D - push eax
Call Doggy_0046b7bd                                         //00867E6E - call 0046b7bd
DB   0x0f,0xb6,0xc0                                         //00867E73 - movzx eax,al
Mov  [LevelNow], Eax
DB   0x50                                                   //00867E76 - push eax
Call Doggy_006f0595                                         //00867E77 - call 006f0595
DB   0x33,0xc9                                              //00867E7C - xor ecx,ecx
DB   0x41                                                   //00867E7E - inc ecx
DB   0x83,0xc4,0x0c                                         //00867E7F - add esp,0c
DB   0x3b,0xc1                                              //00867E82 - cmp eax,ecx
DB   0x89,0x45,0xec                                         //00867E84 - mov [ebp-14],eax
jg Doggy00867e8c                                            //00867E87 - jg 00867e8c
DB   0x89,0x4d,0xec                                         //00867E89 - mov [ebp-14],ecx
Doggy00867e8c:
DB   0xff,0xb7,0x68,0x21,0x00,0x00                          //00867E8C - push [edi+00002168]
DB   0x8d,0x87,0x60,0x21,0x00,0x00                          //00867E92 - lea eax,[edi+00002160]
DB   0x50                                                   //00867E98 - push eax
Call Doggy_0040582b                                         //00867E99 - call 0040582b
DB   0xff,0x76,0x6b                                         //00867E9E - push [esi+6b]
DB   0x89,0x45,0xe8                                         //00867EA1 - mov [ebp-18],eax
DB   0x8d,0x46,0x63                                         //00867EA4 - lea eax,[esi+63]
DB   0x50                                                   //00867EA7 - push eax
Call Doggy_0040582b                                         //00867EA8 - call 0040582b
DB   0xff,0xb7,0x5c,0x21,0x00,0x00                          //00867EAD - push [edi+0000215c]
DB   0x81,0xc7,0x54,0x21,0x00,0x00                          //00867EB3 - add edi,00002154
DB   0x57                                                   //00867EB9 - push edi
DB   0x89,0x45,0xe4                                         //00867EBA - mov [ebp-1c],eax
Call Doggy_0040582b                                         //00867EBD - call 0040582b
DB   0xff,0x76,0x53                                         //00867EC2 - push [esi+53]
DB   0x8b,0xf8                                              //00867EC5 - mov edi,eax
DB   0x8d,0x46,0x4b                                         //00867EC7 - lea eax,[esi+4b]
DB   0x50                                                   //00867ECA - push eax
Call Doggy_0040582b                                         //00867ECB - call 0040582b
DB   0x83,0xc4,0x20                                         //00867ED0 - add esp,20
DB   0xff,0x75,0xf0                                         //00867ED3 - push [ebp-10]
DB   0x8b,0xce                                              //00867ED6 - mov ecx,esi
DB   0xff,0x75,0xec                                         //00867ED8 - push [ebp-14]
DB   0x89,0x45,0xe0                                         //00867EDB - mov [ebp-20],eax
Call Doggy_004c8a10                                         //00867EDE - call 004c8a10
DB   0x50                                                   //00867EE3 - push eax
DB   0xff,0x75,0xe8                                         //00867EE4 - push [ebp-18]
DB   0x8b,0xcb                                              //00867EE7 - mov ecx,ebx
DB   0xff,0x75,0xe4                                         //00867EE9 - push [ebp-1c]
DB   0x57                                                   //00867EEC - push edi
DB   0xff,0x75,0xe0                                         //00867EED - push [ebp-20]
Call Doggy_00863217                                         //00867EF0 - call 00863217
DB   0x83,0xec,0x20                                         //00867EF5 - sub esp,20
DB   0x8b,0xcc                                              //00867EF8 - mov ecx,esp
DB   0x89,0x65,0xe0                                         //00867EFA - mov [ebp-20],esp
DB   0x68,0x00,0x01,0x00,0x00                               //00867EFD - push 00000100
DB   0x68,0xa4,0x9b,0xe2,0x00                               //00867F02 - push 00e29ba4
Call Doggy_004068da                                         //00867F07 - call 004068da
DB   0x8b,0x4d,0xdc                                         //00867F0C - mov ecx,[ebp-24]
Call Doggy_006fe6fd                                         //00867F0F - call 006fe6fd
DB   0x99                                                   //00867F14 - cdq
DB   0xb9,0x10,0x27,0x00,0x00                               //00867F15 - mov ecx,00002710
DB   0xf7,0xf9                                              //00867F1A - idiv ecx
DB   0x8d,0x8b,0x08,0x20,0x00,0x00                          //00867F1C - lea ecx,[ebx+00002008]
DB   0x85,0xc0                                              //00867F22 - test eax,eax
jle Doggy00867f31                                           //00867F24 - jle 00867f31
DB   0x6a,0x01                                              //00867F26 - push 01
Call Doggy_0085e685                                         //00867F28 - call 0085e685
DB   0x6a,0x00                                              //00867F2D - push 00
jmp Doggy00867f3a                                           //00867F2F - jmp 00867f3a
Doggy00867f31:
DB   0x6a,0x00                                              //00867F31 - push 00
Call Doggy_0085e685                                         //00867F33 - call 0085e685
DB   0x6a,0x01                                              //00867F38 - push 01
Doggy00867f3a:
DB   0x8d,0x8b,0xf0,0x1f,0x00,0x00                          //00867F3A - lea ecx,[ebx+00001ff0]
Call Doggy_0085e685                                         //00867F40 - call 0085e685
DB   0x8d,0xb3,0x68,0x21,0x00,0x00                          //00867F45 - lea esi,[ebx+00002168]
DB   0x8b,0xce                                              //00867F4B - mov ecx,esi
Call Doggy_0085f55f                                         //00867F4D - call 0085f55f
DB   0x85,0xc0                                              //00867F52 - test eax,eax
jne Doggy00867f5d                                           //00867F54 - jne 00867f5d
DB   0x8b,0xce                                              //00867F56 - mov ecx,esi
Call Doggy_00866199                                         //00867F58 - call 00866199
Doggy00867f5d:
DB   0xa1,0xc4,0xcd,0xe1,0x00                               //00867F5D - mov eax,[00e1cdc4] : 00000000
DB   0xff,0xb0,0x44,0x01,0x00,0x00                          //00867F62 - push [eax+00000144]
DB   0x8b,0xcb                                              //00867F68 - mov ecx,ebx
Call Doggy_0085ebfe                                         //00867F6A - call 0085ebfe
Doggy00867f6f:
Call Doggy_00a16a81                                         //00867F6F - call 00a16a81
DB   0xc2,0x04,0x00                                         //00867F74 - ret 0004
}
}
