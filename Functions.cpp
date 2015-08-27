//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Functions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include "VMProtectSDK.h"

HWND MSHWND;
int GetHwnd_Back_2 = 0;

typedef struct PACKET_ {
	int		NUL1;
	char*   Data;
	int		Len;
	int 	NUL2;
} PACKET;

void __declspec(naked) _GetHwnd_1()
{
#ifdef VMProtectSDK
VMProtectBegin("__GetHwnd_1");
#endif
__asm
{
Cmp  [Esp], 0x009A9D87	// 8B ?? ?? 89 ?? 04 C6 45 fc 00
Je   GetHwndHook
Jmp  CreateWindowExA

GetHwndHook:
Add  Esp, 4
Call CreateWindowExA
Mov  [MSHWND], Eax
//Push [GetHwnd_Back_2]
//Pop  [0x00E19800]
Push 0x009A9D87
Ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}

/*void __declspec(naked) _GetHwnd_2()
{
#ifdef VMProtectSDK
VMProtectBegin("__GetHwnd_2");
#endif
__asm
{
Cmp  [Esp], 0x00990B73	// 8B 4D ?? 89 01 33 C0 40 8B
Je   GetHwndHook
Jmp  dword ptr [GetHwnd_Back_2]
GetHwndHook:
Push [Esp+04]
Pop  [MSHWND]
Push [GetHwnd_Back_2]
Pop  [0x00E19800]
Jmp  dword ptr [GetHwnd_Back_2]
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}*/

void Hook2GetHwnd()
{
#ifdef VMProtectSDK
VMProtectBegin("Hook2GetHwnd");
#endif
	try {
		*(int*)0x00e25e20 = (int)_GetHwnd_1;
		/*GetHwnd_Back_2 = *(int*)0x00E19800;	//DefWindowProcA
		*(int*)0x00E19800 = (int)_GetHwnd_2;*/
	} catch(...) { TerminateProcess(GetCurrentProcess(), 0); }
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}

/*void SendPacket(char* data, int len)
{
#ifdef VMProtectSDK
VMProtectBegin("SendPacket");
#endif
//	try {
		PACKET pack = {0};
		pack.Data = data;
		pack.Len = len;
		__asm {
			Lea  Eax, [pack]
			Push Ecx
			Push Eax
			Mov  Eax, 0x004262F2
			Call Eax
			Add  Esp, 04
			Pop  Ecx
        }
//	} catch(...) {  }
#ifdef VMProtectSDK
VMProtectEnd();
#endif
	return;
}

void ChangeChannel(char channel)
{
#ifdef VMProtectSDK
VMProtectBegin("ChangeChannel");
#endif
	// 48 00 [Channel*1] [Time*4]
	int t = GetTicket();
	char* buff = (char*)malloc(7);
	*(short*)buff = 0x48; // [2/2] // 6a ?? 8d 4d ?? e8 ?? ?? ?? 00 ff 75 08
	buff[2] = channel;
	*(int*)&buff[3] = t + 3000;
	SendPacket(buff, 7);
	free(buff);
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}*/
/*
void Talk(char* msg)
{
#ifdef VMProtectSDK
VMProtectBegin("Talk");
#endif
	// 5C 00 [Time*4] [Length*2] [Buffer]
	int l = strlen(msg);
	int t = GetTicket();
	char* buff = (char*)malloc(l+9);
	*(short*)buff = 0x5C; // 6a ?? 8d 4d ?? e8 ?? ?? ?? 00 c7
	*(int*)&buff[2] = t;
	*(short*)&buff[6] = l;
	strcpy(&buff[8], msg);
	SendPacket(buff, l+9);
	free(buff);
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}

void Smile(int id)
{
#ifdef VMProtectSDK
VMProtectBegin("Smile");
#endif
	int SmileCall_ = 0x009D4DD3; // 6A 10 B8 ?? ?? ?? 00 E8 ?? ?? ?? 00 8B F9 8B 35 ?? ?? ?? 00 85 f6 0f 84
	__asm{
		PUSHAD
		MOV  ECX, [0x00e0bc00] // a1 ?? ?? ?? 00 c3 8b 41 04 c3 8b 41 04 c3 8b 41 04 c3 8b 41 04 c3
		PUSH -1
		PUSH 0
		PUSH [id]
		CALL SmileCall_
		POPAD
	}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
	return;
}

void Smile()
{
	static NextTicket = 0;
	if(GetTicket() > NextTicket)
	{
        NextTicket = GetTicket() + 600;
		Smile(2);
	}
}
*/
void ShowText(char* text, int color)
{/*
#ifdef VMProtectSDK
VMProtectBegin("ShowText");
#endif
try
{
	if(*(int*)0x00E10778 == 0) // 39 1d ?? ?? ?? 00 74 ?? 51 51 8b c4
    	return;
	int ShowTextCall_ = 0x008620D5;	// 6A 54 B8 ?? ?? ?? 00 E8 ?? ?? ?? 00 8B ?? 33 DB 89 5D ?? 89 5D ?? 89 5D ?? 6A FF
	__asm{
		Push 0
		Push 0
		Push 0
		Push -1
		Push [Ebp+0x0C] //00:白色 01:綠色 02:粉紅色 03:橘色 04:淺粉紅 05:淺綠 06:灰色 07:黃色 08:淺黃色 09:藍色 0A:灰白底黑字 0B:淺粉紅 0C:灰藍底藍字
		Push [Ebp+0x08]
		Mov  Ecx, [0x00E10778]
		Call dword ptr [ShowTextCall_]
	}
}
catch(...)
{

}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
	return;*/
}

GETINFOCALL GetTicket = (GETINFOCALL)0x009562DD; // A1 ?? ?? ?? ?? 8B 40 ?? C3

int GetMobCount()
{
	try
	{                 
		return P(0x00e1cabc, 0x24);
	} catch(...) { return -1; }
}

int GetMapId()
{
	try {
		int MapId = P(0x00e20700, 0x10C0);
		return (MapId < 999999999 ? MapId : -1);
	} catch(...) { return -1; }
}

// 物品編號取得物品名稱
// 8B 0D ?? ?? ?? ?? 50 8D 45 ?? 50 E8 ?? ?? ?? FF 83 65 ?? 00 50
char* __declspec(naked) __stdcall GetItemNameByItemId(int ItemId)
{
__asm {
push ebp
mov ebp,esp
push ecx // tmpMem
push ebx
push ecx
push edi
mov ebx,[ebp+0x08]
mov ecx,[0x00f6c604]
push ebx
lea eax,[ebp-0x04]
push eax
xor edi,edi
mov eax,0x005c52b1
call eax
mov eax,[ebp-0x04]
pop edi
pop ecx
pop ebx
mov esp,ebp
pop ebp
ret 0x0004
}
return NULL;
}
