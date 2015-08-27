//---------------------------------------------------------------------------

#ifndef FunctionsH
#define FunctionsH
#define ics(adr, func) (*(long*)adr = (long)func) ;
#define R(adr) (*(long*)adr)
#define P(adr, off) ( R( (R(adr) + off) ) )

typedef __stdcall int (*GETINFOCALL)();

void Hook2GetHwnd();
void SendPacket(char* data, int len);
extern GETINFOCALL GetTicket;
void ShowText(char* text, int color);
void ChangeChannel(char channel);
int GetMobCount();
int GetMapId();
char* __declspec(naked) __stdcall GetItemNameByItemId(int ItemId);
//---------------------------------------------------------------------------
#endif
