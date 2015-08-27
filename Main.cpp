//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <windows.h>
#include "inifiles.hpp"
#pragma hdrstop

#include "VMProtectSDK.h"
#include "Main.h"
#include "Functions.h"
#include "HackScripts.h"
#include "aes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
String mPath;
HINSTANCE dllinst;
extern HWND MSHWND;
typedef LRESULT (CALLBACK *WNDPROC)(HWND, UINT,WPARAM,LPARAM);
WNDPROC org_MSPROC;
int Inited = 0;
int THE_VIP = 0;
int ItemList[4096] = {0};
int KeySwitch[9] = {0}, KeyTick[9] = {0}, KeyTime[9] = {0};
#define CHARBASE	0x00e1847c
#define SKILLACTION	0x000004A4
#define SYSBASE		0x00e181e0
#define SUPERPICK	0x000020DC
String GameAccount;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
String StrBetween(String StrStart, String StrEnd, String Str)
{
	int Index1 = Str.Pos(StrStart);
	if (Index1 == -1)
		return "";
	Index1 += StrStart.Length();
	String Tmp = Str.SubString(Index1, Str.Length() - Index1 - 1);
	int Index2 = Tmp.Pos(StrEnd);
	if (Index2 == -1)
		return "";
	return Tmp.SubString(0, Index2 - 1);
}
//---------------------------------------------------------------------------
DWORD WINAPI CallFormProc(LPVOID lpParameter)
{
	static flag = true;
	if (flag)
	{
		Sleep(600);
		GameAccount = StrBetween(" 8484 BeanFun ", " ", GetCommandLine());
		frmMain = new TfrmMain(Application);
		frmMain->ShowModal();
		flag = false;
		return 1;
	}
	return 1;
}
//---------------------------------------------------------------------------
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
#ifdef VMProtectSDK
VMProtectBegin("DllEntryPoint");
#endif
	if (reason == DLL_PROCESS_ATTACH)
	{
		dllinst = hinst;
		CreateThread(NULL,0xFF,CallFormProc,NULL,0,NULL);
	}
	if (reason == DLL_PROCESS_DETACH)
	{
		ExitProcess(NULL);
		FreeLibrary(dllinst);
	}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
	return 1;
}
//---------------------------------------------------------------------------
LRESULT MSPROC(HWND hwnd, UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
		case WM_MOVE:
			RECT rect;
			GetWindowRect(MSHWND, &rect);
			frmMain->Left = rect.right;
			frmMain->Top = rect.top;
			break;
		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_F2:
					frmMain->chkMoveFast->Checked = !frmMain->chkMoveFast->Checked;
					break;
				case VK_F3:
					memset(KeyTick, 0, sizeof(KeyTick));
					break;
				case VK_F4:
					frmMain->chkFollow->Checked = !frmMain->chkFollow->Checked;
					break;
				case VK_F6:
					frmMain->btnAddItemClick(NULL);
					break;
				case VK_F12:
					frmMain->Visible = !frmMain->Visible;
					break;
            }
			break;
		case WM_CLOSE:
			TerminateProcess(GetCurrentProcess(), 0);
			break;
	}

	return org_MSPROC(hwnd, message, wParam, lParam);
}
//---------------------------------------------------------------------------
void AsmJump(const DWORD lpAddress, LPCVOID Function, int Nops)
{
	*(char*)lpAddress = 0xE9;
	*(int*)(lpAddress + 1) = (int)Function - (int)lpAddress - 5;
	for (int i = 0; i < Nops; i++) *((char*)lpAddress + 5 + i) = 0x90;
}
#include "CRC.h"
void OnlyNumberInput(TEdit *Obj)
{
	DWORD fstyle;
	fstyle = GetWindowLong(Obj->Handle, GWL_STYLE);
	SetWindowLong(Obj->Handle, GWL_STYLE, fstyle | ES_NUMBER | ES_CENTER);
}
void PressKey(long KeyCode)
{
	PostMessage(MSHWND, WM_KEYDOWN, KeyCode, 0x0000001 | (MapVirtualKey(KeyCode, 0) & 0xFF) << 16);
	PostMessage(MSHWND, WM_KEYUP  , KeyCode, 0xC000001 | (MapVirtualKey(KeyCode, 0) & 0xFF) << 16);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose = false;
	this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("FormCreate");
#endif
	//取得路徑
	char f[260] = {0};
	extern HINSTANCE dllinst;
	GetModuleFileName(dllinst, f, sizeof(f));
	mPath = ExtractFileDir(f);
    //初始表單設定
	this->Left = 806;
	this->Top = 0;
	OnlyNumberInput(txtHP);
	OnlyNumberInput(txtMP);
	OnlyNumberInput(txtAutoKey1);
	OnlyNumberInput(txtAutoKey2);
	OnlyNumberInput(txtAutoKey3);
	OnlyNumberInput(txtAutoKey4);
	OnlyNumberInput(txtAutoKey5);
	OnlyNumberInput(txtAutoKey6);
	OnlyNumberInput(txtAutoKey7);
	OnlyNumberInput(txtAutoKey8);
	OnlyNumberInput(txtAutoKey9);

#if VMPSWITCH==0
	lblUser->Caption = "Inndy";
	if (lblUser->Caption.Length() > 0)
		lblUser->Caption = lblUser->Caption;
	groupVIP->Visible = true;
	THE_VIP = 1;
#else
	try
	{
		TIniFile* ini = new TIniFile(mPath + "\\MSDoggy.ini");
		String Key = ini->ReadString("MSDoggy", "MSDoggyPlus", "");
		delete ini;
		if (Key.Length() > 0)
		{
			char RealKey[1024] = {0};
			AES *aes = new AES((unsigned char*)"reTn3Xx92UcBPdSNclXpzadbdLwvBt0ED6985wdrZZb43mk2FWkc3dUREjlNCuzyWd64cXJXDcdbbVfZn9qqltgJryJMHJWoVJocqlsAx0JrUiVWNGipN2oQPnItARUo");
			aes->InvCipher(Key.c_str(), RealKey);
			delete aes;
			VMProtectSerialNumberData Serial;
			VMProtectSetSerialNumber(RealKey);
			VMProtectGetSerialNumberData(&Serial, sizeof(Serial));
			if (Serial.nState == 0 && Serial.dtExpire.wYear == 2150 && Serial.dtExpire.bMonth == 2)
			{
				if (wcslen(Serial.wUserName)) lblUser->Caption = Serial.wUserName;
				btnVIP->Visible = false;
				groupVIP->Visible = true;
            	THE_VIP = 1;
            }
		}
	}
	catch(...)
	{

	}
#endif

	//功能初始化
	try
	{
		Hook2GetHwnd();
		ics(0x00C80FD8, GetInfo_asm);
		ics(0x00C8E104, NoKB_asm);
		ics(0x00C8E0AC, MoveFast_asm);
		ics(0x00F872AA, MFFakeTime_asm - 0x00F872A9 - 5);
		ics(0x00C8DA10, MobFollow_asm);
		ics(0x00C8A128, MultiPick_asm);
		ics(0x00C8A19C, ReduceHurts_asm);
		ics(0x00C8A15C, God30_asm);
		ics(0x00DFCA4C, Blast_asm);
//		ics(0x00C7FEB4, NoDelayBuff_asm);
		ItemFilterList_adr = ItemList;
		if (THE_VIP) {
            trackMoveFast->Max = 10;

			FuckChecking();
			ics(0x00C8D894, SuperStupid_asm);
			ics(0x00C74744, UltraMaking_asm);
			ics(0x00930CF6, NoMiningInterval_asm);
			AsmJump(0x00932614, NoDelayMining_asm, 0);

			AsmJump(0x008F5E55, OverAttack_asm, 0); // 6A 65 59 33 D2 F7 F1 FF 75 ?? 8B 4D
			AsmJump(0x00933B71, NoDelayFinalAttack_asm, 0); // E8 ?? ?? 00 00 8B CB E8 ?? ?? 00 00 8D

			AsmJump(0x00915D3E, UnlimitedWeapon_asm, 0);

			ics(0x00e25e64, ItemVac_asm);
			ics(0x00C8E248, FixedSSAction_asm);
			// 物品撿取立刻消失
			AsmJump(0x004EC8A4, (LPCVOID)0x004ECD7F /* Last Jne */ , 1); // 0F 84 ?? ?? 00 00 4F 4F 0F 84
			*(short*)0x004EC441 = 0x9090; // 物品定位 // 75 ?? 8b 45 08 2b 46 ?? 3d b8

			ics(0x00E25EC0, AutoLR_asm);
			
			// 33 FF C6 45 ?? 00
			// First: mov eax,[esi+00000XXX]
			AsmJump(0x006121FA, MobVac_asm, 1);
			DWORD WINAPI AutoAttackProc(LPVOID lpParameter);
			CreateThread(NULL,0xFF,AutoAttackProc,NULL,0,NULL);
		} else {
			DWORD WINAPI KeyProc(LPVOID lpParameter);
			CreateThread(NULL,0xFF,KeyProc,NULL,0,NULL);
			ics(0x00C0F6E0, UnlimitedWeapon_asm);
        }
	}
	catch(...)
	{
		TerminateProcess(GetCurrentProcess(), 0);
	}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}                      
//---------------------------------------------------------------------------
void __fastcall TfrmMain::tmrInitTimer(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("tmrInit");
#endif
	if (!org_MSPROC) {
		if (MSHWND) {
			Sleep(100);
			org_MSPROC = (WNDPROC)GetWindowLong(MSHWND, GWL_WNDPROC);
			SetWindowLong(MSHWND, GWL_WNDPROC, (long)MSPROC);
			SetWindowPos(MSHWND, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOSENDCHANGING | SWP_NOZORDER);
			RECT rect;
			GetWindowRect(MSHWND, &rect);
			frmMain->Left = rect.right;
			frmMain->Top = rect.top;
		} else {
			HWND PlayHwnd;
			PlayHwnd = FindWindow("StartUpDlgClass", "MapleStory");
			if (PlayHwnd)
				PostMessage(PlayHwnd, WM_CLOSE, 0, 0);
		}
	}
	try {
    	extern int HpFull;
		char *CharacterID = NULL;
		if (HpFull) {
			__asm {
				Mov  Eax, [SYSBASE]
				Test Eax, Eax
				Je   ___Exit
				Mov  Eax, [Eax+0x000020F0]
				Test Eax, Eax
				Je   ___Exit
				Add  Eax, 0x04
				Mov  [CharacterID], Eax
			___Exit:
			}
		}
		if (R(CHARBASE) && org_MSPROC && CharacterID > (char*)0x00401000) {
			lblCharacterID->Caption = CharacterID;
			lblCharacterID->Caption = "ID:" + lblCharacterID->Caption;
			tmrInit->Enabled = false;
			tmrAutoDrink->Enabled = true;
			Inited = 1;
			btnLoadSettingClick(NULL);
		}
	} catch(...) {  }
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::lblFaceBookClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("lblFaceBookClick");
#endif
	((TLabel*)Sender)->Font->Color = clRed;
	ShellExecute(0, "open", "http:\/\/www.facebook.com\/MSDoggy4TWMS", 0, 0, SW_SHOW);
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnSaveSettingClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("btnSaveSettingClick");
#endif
	TIniFile* ini = new TIniFile(mPath + "\\MSDoggy_" + GameAccount + ".ini");
	for(int i = 0; i < ComponentCount; i++)
	{
		if (Components[i]->Tag == 0x999 && THE_VIP == 0)
        	continue;
		if (Components[i]->ClassNameIs("TEdit"))
		{
			ini->WriteString("MSDoggy", Components[i]->Name, ((TEdit*)Components[i])->Text);
		} else if (Components[i]->ClassNameIs("TCheckBox"))
		{
			ini->WriteBool("MSDoggy", Components[i]->Name, ((TCheckBox*)Components[i])->Checked);
		} else if (Components[i]->ClassNameIs("TComboBox"))
		{
			ini->WriteInteger("MSDoggy", Components[i]->Name, ((TComboBox*)Components[i])->ItemIndex);
		} else if (Components[i]->ClassNameIs("TTrackBar"))
		{
			ini->WriteInteger("MSDoggy", Components[i]->Name, ((TTrackBar*)Components[i])->Position);
		}
	}
	ini->WriteInteger("MSDoggy", "MobFollowX", MobFollowX);
	delete ini;
	lstItemFilter->Items->SaveToFile(mPath + "\\ItemFilter_" + GameAccount + ".txt");
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnLoadSettingClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("btnLoadSettingClick");
#endif
	TIniFile* ini = new TIniFile(mPath + "\\MSDoggy_" + GameAccount + ".ini");
	for(int i = ComponentCount - 1; i > 0; i--)
	{
		if (Components[i]->ClassNameIs("TEdit"))
		{
			((TEdit*)Components[i])->Text = ini->ReadString("MSDoggy", Components[i]->Name, "");
		} else if (Components[i]->ClassNameIs("TCheckBox"))
		{
			((TCheckBox*)Components[i])->Checked = ini->ReadBool("MSDoggy", Components[i]->Name, false);
		} else if (Components[i]->ClassNameIs("TComboBox"))
		{
			((TComboBox*)Components[i])->ItemIndex = ini->ReadInteger("MSDoggy", Components[i]->Name, 0);
		} else if (Components[i]->ClassNameIs("TTrackBar"))
		{
			((TTrackBar*)Components[i])->Position = ini->ReadInteger("MSDoggy", Components[i]->Name, 0);
		}
	}
	MobFollowX = ini->ReadInteger("MSDoggy", "MobFollowX", 0);
	cmbMobKBChange(NULL);
	cmbJumpChange(NULL);
	delete ini;
	if (FileExists(mPath + "\\ItemFilter_" + GameAccount + ".txt")) {
		lstItemFilter->Items->LoadFromFile(mPath + "\\ItemFilter_" + GameAccount + ".txt");
		void ReloadItems();
		ReloadItems();
	}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::tmrAutoDrinkTimer(TObject *Sender)
{
	extern int HpNow, HpFull, MpNow, MpFull, ExpNow, ExpFull, LevelNow;
	try {
		imgBarHP->Width = (174 * HpNow) / HpFull;
		imgBarMP->Width = (174 * MpNow) / MpFull;
		double ExpWidth = ExpNow;
		ExpWidth *= 174;
		ExpWidth /= ExpFull;
		imgBarEXP->Width = (int)ExpWidth;
		lblHP->Caption = "[" + IntToStr(HpNow) + "/" + IntToStr(HpFull) + "]";
		lblMP->Caption = "[" + IntToStr(MpNow) + "/" + IntToStr(MpFull) + "]";
		lblEXP->Caption = "[" + IntToStr(ExpNow) + "/" + IntToStr(ExpFull) + "]";
		lblLevel->Caption = "Lv." + IntToStr(LevelNow);
	} catch (...) {  }

	if (HpNow < txtHP->Tag && txtHP->Tag < HpFull && chkAutoHP->Checked)
		PressKey(33);	//PageUp
	if (MpNow < txtMP->Tag && txtMP->Tag < MpFull && chkAutoMP->Checked)
		PressKey(34);	//PageDown
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkAutoHPClick(TObject *Sender)
{
	if (chkAutoHP->Checked)
	{
		try
		{
			txtHP->Tag = StrToInt(txtHP->Text);
		}
		catch(...)
		{
			MessageBox(this->Handle, "錯誤的數值", "錯誤", MB_ICONERROR);
			chkAutoHP->Checked = false;
		}
	}
	txtHP->Enabled = !chkAutoHP->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkAutoMPClick(TObject *Sender)
{
	if (chkAutoMP->Checked)
	{
		try
		{
			txtMP->Tag = StrToInt(txtMP->Text);
		}
		catch(...)
		{
			MessageBox(this->Handle, "錯誤的數值", "錯誤", MB_ICONERROR);
			chkAutoMP->Checked = false;
		}
	}
	txtMP->Enabled = !chkAutoMP->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkNoKBClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkNoKB");
#endif
	NoKBSwitch = chkNoKB->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkMoveFastClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkMoveFast");
#endif
	MoveFastSwitch = chkMoveFast->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkGodClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkGod");
#endif
	GodSwitch = chkGod->Checked;
	chkFullGod->Enabled = chkGod->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkStupidClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkStupid");
#endif
	StupidSwitch = chkStupid->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::cmbJumpChange(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("cmbJump");
#endif
	MobJumpSwitch = cmbJump->ItemIndex;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::cmbMobKBChange(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("cmbMobKB");
#endif
	MobKBSwitch = cmbMobKB->ItemIndex;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkFollowClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkFollow");
#endif
	if (chkMobVac->Checked) return;
	try
	{
		GetXY();
		if (chkFollow->Checked)
			if (R(CHARBASE))
				MobFollowX = CharX;
		MobFollowSwitch = chkFollow->Checked;
	} catch(...) {  }
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkImmediateFullClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkImmediateFull");
#endif
	ImmediateFullSwitch = chkImmediateFull->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::trackMoveFastChange(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("trackMoveFast");
#endif
	extern int MFRate;
	MFRate = trackMoveFast->Position;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkSuperStupidClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkSuperStupid");
#endif
	SuperStupidSwitch = chkSuperStupid->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkDoubleAttackClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkDoubleAttack");
#endif
	DoubleAttackSwitch = chkDoubleAttack->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkReduceHurtsClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkReduceHurts");
#endif
	ReduceHurtsSwitch = chkReduceHurts->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkNoDelayFinalAttackClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkNoDelayFinalAttack");
#endif
	NoDelayFinalAttackSwitch = chkNoDelayFinalAttack->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnVIPClick(TObject *Sender)
{
#if VMPSWITCH==1
VMProtectBegin("btnVIPClick");
	btnVIP->Visible = false;
	char myKey[1024] = {0};
	VMProtectGetCurrentHWID(myKey, sizeof(myKey));
	int l = strlen(myKey);
	char mFile[256];
	strcpy(mFile, mPath.c_str());
	strcat(mFile, "\\Key.txt");
	FILE* fp = fopen(mFile, "w");
	fwrite(myKey, l, 1, fp);
	fclose(fp);
	ShellExecute(NULL, "open", mFile, NULL, NULL, SW_SHOW);
	lblFaceBookClick(Sender);
	MessageBox(this->Handle, "MSDoggyVIP詳情請洽官方粉絲團...\n**請透過本程式下方之連結進入MSDoggy粉絲專頁以免受騙...\n粉絲專頁網址：http://facebook.com/MSDoggy4TWMS/", "Tips...", MB_ICONINFORMATION | MB_SETFOREGROUND);
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkMobNoFightBackClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkMobNoFightBack");
#endif
	MobNoFightBackSwitch = chkMobNoFightBack->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkFullGodClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkFullGod");
#endif
	FullGod = chkFullGod->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkItemVacClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkItemVac");
#endif
	ItemVacSwitch = chkItemVac->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//--------------------------------------------------------------------------- 
void AddItem(int ItemID)
{
	char tmp[256];
	sprintf(tmp, "%d // %s", ItemID, GetItemNameByItemId(ItemID));
	frmMain->lstItemFilter->Items->Add(tmp);
}
//---------------------------------------------------------------------------
void ReloadItems()
{
	TStrings *Items = frmMain->lstItemFilter->Items;
	ItemFilterCount = Items->Count;

	for (int i = 0; i < ItemFilterCount; i++) {
		sscanf(Items->Strings[i].c_str(), "%d", &ItemList[i]);
		for (int j = 0; j < i; j++) {
			if (ItemList[i] == ItemList[j]) {
				Items->Delete(i);
				i--;
				ItemFilterCount--;               
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnAddItemClick(TObject *Sender)
{
	if (*(long*)CHARBASE) {
		int ItemID = P(CHARBASE, 0x5F00);
		AddItem(ItemID);
		ReloadItems();		
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::lstItemFilterKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_DELETE) {
		if (lstItemFilter->ItemIndex == -1) return;
		lstItemFilter->Items->Delete(lstItemFilter->ItemIndex);
		ReloadItems();
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkItemFilterClick(TObject *Sender)
{
	ItemFilterSwitch = chkItemFilter->Checked;
}
//---------------------------------------------------------------------------
void ForceAct() {
	if (*(int*)CHARBASE)
		((int**)CHARBASE)[0][SKILLACTION>>2] = -1;
	if (*(int*)SYSBASE)
		((int**)SYSBASE)[0][SUPERPICK>>2] = 0;
}
//---------------------------------------------------------------------------
void CheckKeys() {
	try {
		for (int i = 0; i < 9; i++) {
            if (KeyTick[i] < GetTicket() && KeySwitch[i]) {
				Sleep(1000);
				break;
			}
		}
			
		for (int i = 0; i < 9; i++) {
			if (KeyTick[i] < GetTicket() && KeySwitch[i]) {
				ForceAct();
				PressKey('1' + i);
				KeyTick[i] = GetTicket() + KeyTime[i] * 999;
				for (int j = 0; j < 60; j++) {
					ForceAct();
					Sleep(10);
				}
			}
		}
	} catch (...) {  }
}
//---------------------------------------------------------------------------
DWORD WINAPI KeyProc(LPVOID lpParameter) {
	while (!Inited) Sleep(0);
	while (true) {
		CheckKeys();
		Sleep(10);
    }
}
//---------------------------------------------------------------------------
DWORD WINAPI AutoAttackProc(LPVOID lpParameter) {
	while (!Inited) Sleep(0);
	while (true) {
		if (MobVacSwitch == 0) { CheckKeys(); Sleep(10); continue; }
		if (LRStep == 2 || LRStep == 4) {
			CheckKeys();
			if (GetMobCount() > 1) PressKey(VK_CONTROL);
			Sleep(20);
		} else {
			PressKey('Z');
			Sleep(2);
        }
	}
}                                  
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkMobVacClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkMobVac");
#endif
	try
	{
		if (chkMobVac->Checked) {
			if (R(CHARBASE)) {
				GetXY();
				VacX = CharX;
				VacY = CharY - 2;
			}
		}
		LRStep = 1;
		LRTick = 0;
		MobVacSwitch = chkMobVac->Checked;
	} catch(...) {  }
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkAutoKeyClick(TObject *Sender)
{
	TCheckBox *sender = (TCheckBox*)Sender;
	int index = sender->Tag;
	KeySwitch[index] = sender->Checked;
	KeyTick[index] = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::txtAutoKeyChange(TObject *Sender)
{
	TEdit *sender = (TEdit*)Sender;
	int index = sender->Tag;
	sscanf(sender->Text.c_str(), "%d", &KeyTime[index]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnResetSkillClick(TObject *Sender)
{
	memset(KeyTick, 0, sizeof(KeyTick));
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkNodelayBuffClick(TObject *Sender)
{
#ifdef VMProtectSDK
VMProtectBegin("chkNodelayBuff");
#endif
	NoDelayBuffSwitch = chkNodelayBuff->Checked;
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}
//---------------------------------------------------------------------------
