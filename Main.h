//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <GIFImg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblFaceBook;
	TButton *btnSaveSetting;
	TButton *btnLoadSetting;
	TTimer *tmrInit;
	TPageControl *pageHacks;
	TTabSheet *tabProtect;
	TCheckBox *chkAutoHP;
	TCheckBox *chkAutoMP;
	TLabel *Label4;
	TLabel *Label3;
	TCheckBox *chkGod;
	TCheckBox *chkNoKB;
	TTabSheet *tabNormal;
	TLabel *Label1;
	TLabel *Label2;
	TCheckBox *chkStupid;
	TComboBox *cmbJump;
	TComboBox *cmbMobKB;
	TCheckBox *chkMoveFast;
	TCheckBox *chkFollow;
	TTrackBar *trackMoveFast;
	TTimer *tmrAutoDrink;
	TTabSheet *tabFilter;
	TEdit *txtHP;
	TEdit *txtMP;
	TCheckBox *chkImmediateFull;
	TGroupBox *groupVIP;
	TCheckBox *chkMobNoFightBack;
	TCheckBox *chkSuperStupid;
	TCheckBox *chkDoubleAttack;
	TLabel *lblUser;
	TCheckBox *chkReduceHurts;
	TCheckBox *chkNoDelayFinalAttack;
	TLabel *Label6;
	TButton *btnVIP;
	TCheckBox *chkFullGod;
	TCheckBox *chkItemVac;
	TListBox *lstItemFilter;
	TCheckBox *chkItemFilter;
	TButton *btnAddItem;
	TLabel *Label5;
	TLabel *lblCharacterID;
	TImage *imgBar1;
	TImage *imgBar2;
	TImage *imgBar3;
	TImage *imgBarHP;
	TImage *imgBarMP;
	TImage *imgBarEXP;
	TLabel *lblHP;
	TLabel *lblMP;
	TLabel *lblEXP;
	TLabel *lblLevel;
	TCheckBox *chkMobVac;
	TTabSheet *tabAutoKeys;
	TCheckBox *chkAutoKey1;
	TEdit *txtAutoKey1;
	TLabel *Label7;
	TCheckBox *chkAutoKey2;
	TEdit *txtAutoKey2;
	TLabel *Label8;
	TCheckBox *chkAutoKey3;
	TEdit *txtAutoKey3;
	TLabel *Label9;
	TCheckBox *chkAutoKey4;
	TEdit *txtAutoKey4;
	TLabel *Label10;
	TCheckBox *chkAutoKey5;
	TEdit *txtAutoKey5;
	TLabel *Label11;
	TCheckBox *chkAutoKey6;
	TEdit *txtAutoKey6;
	TLabel *Label12;
	TCheckBox *chkAutoKey7;
	TEdit *txtAutoKey7;
	TLabel *Label13;
	TCheckBox *chkAutoKey8;
	TEdit *txtAutoKey8;
	TLabel *Label14;
	TCheckBox *chkAutoKey9;
	TEdit *txtAutoKey9;
	TLabel *Label15;
	TButton *btnResetSkill;
	TMemo *Memo1;
	TCheckBox *chkNodelayBuff;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall lblFaceBookClick(TObject *Sender);
	void __fastcall btnSaveSettingClick(TObject *Sender);
	void __fastcall btnLoadSettingClick(TObject *Sender);
	void __fastcall tmrInitTimer(TObject *Sender);
	void __fastcall tmrAutoDrinkTimer(TObject *Sender);
	void __fastcall chkAutoHPClick(TObject *Sender);
	void __fastcall chkAutoMPClick(TObject *Sender);
	void __fastcall chkNoKBClick(TObject *Sender);
	void __fastcall chkMoveFastClick(TObject *Sender);
	void __fastcall chkGodClick(TObject *Sender);
	void __fastcall chkStupidClick(TObject *Sender);
	void __fastcall cmbJumpChange(TObject *Sender);
	void __fastcall cmbMobKBChange(TObject *Sender);
	void __fastcall chkFollowClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall trackMoveFastChange(TObject *Sender);
	void __fastcall chkImmediateFullClick(TObject *Sender);
	void __fastcall chkSuperStupidClick(TObject *Sender);
	void __fastcall chkDoubleAttackClick(TObject *Sender);
	void __fastcall chkReduceHurtsClick(TObject *Sender);
	void __fastcall chkNoDelayFinalAttackClick(TObject *Sender);
	void __fastcall btnVIPClick(TObject *Sender);
	void __fastcall chkMobNoFightBackClick(TObject *Sender);
	void __fastcall chkFullGodClick(TObject *Sender);
	void __fastcall chkItemVacClick(TObject *Sender);
	void __fastcall btnAddItemClick(TObject *Sender);
	void __fastcall lstItemFilterKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall chkItemFilterClick(TObject *Sender);
	void __fastcall chkMobVacClick(TObject *Sender);
	void __fastcall chkAutoKeyClick(TObject *Sender);
	void __fastcall txtAutoKeyChange(TObject *Sender);
	void __fastcall btnResetSkillClick(TObject *Sender);
	void __fastcall chkNodelayBuffClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
