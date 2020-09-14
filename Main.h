//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include "libxl.h"
#include "Define.h"
#include "UdpSocketThread.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "cxClasses.hpp"
#include "cxControls.hpp"
#include "cxGraphics.hpp"
#include "cxLookAndFeelPainters.hpp"
#include "cxLookAndFeels.hpp"
#include "dxBar.hpp"
#include "dxRibbon.hpp"
#include "dxRibbonCustomizationForm.hpp"
#include "dxRibbonSkins.hpp"
#include "dxSkinBlack.hpp"
#include "dxSkinBlue.hpp"
#include "dxSkinBlueprint.hpp"
#include "dxSkinCaramel.hpp"
#include "dxSkinCoffee.hpp"
#include "dxSkinDarkRoom.hpp"
#include "dxSkinDarkSide.hpp"
#include "dxSkinDevExpressDarkStyle.hpp"
#include "dxSkinDevExpressStyle.hpp"
#include "dxSkinFoggy.hpp"
#include "dxSkinGlassOceans.hpp"
#include "dxSkinHighContrast.hpp"
#include "dxSkiniMaginary.hpp"
#include "dxSkinLilian.hpp"
#include "dxSkinLiquidSky.hpp"
#include "dxSkinLondonLiquidSky.hpp"
#include "dxSkinMcSkin.hpp"
#include "dxSkinMetropolis.hpp"
#include "dxSkinMetropolisDark.hpp"
#include "dxSkinMoneyTwins.hpp"
#include "dxSkinOffice2007Black.hpp"
#include "dxSkinOffice2007Blue.hpp"
#include "dxSkinOffice2007Green.hpp"
#include "dxSkinOffice2007Pink.hpp"
#include "dxSkinOffice2007Silver.hpp"
#include "dxSkinOffice2010Black.hpp"
#include "dxSkinOffice2010Blue.hpp"
#include "dxSkinOffice2010Silver.hpp"
#include "dxSkinOffice2013DarkGray.hpp"
#include "dxSkinOffice2013LightGray.hpp"
#include "dxSkinOffice2013White.hpp"
#include "dxSkinPumpkin.hpp"
#include "dxSkinsCore.hpp"
#include "dxSkinsDefaultPainters.hpp"
#include "dxSkinsdxBarPainter.hpp"
#include "dxSkinsdxRibbonPainter.hpp"
#include "dxSkinSeven.hpp"
#include "dxSkinSevenClassic.hpp"
#include "dxSkinSharp.hpp"
#include "dxSkinSharpPlus.hpp"
#include "dxSkinSilver.hpp"
#include "dxSkinSpringTime.hpp"
#include "dxSkinStardust.hpp"
#include "dxSkinSummer2008.hpp"
#include "dxSkinTheAsphaltWorld.hpp"
#include "dxSkinValentine.hpp"
#include "dxSkinVisualStudio2013Blue.hpp"
#include "dxSkinVisualStudio2013Dark.hpp"
#include "dxSkinVisualStudio2013Light.hpp"
#include "dxSkinVS2010.hpp"
#include "dxSkinWhiteprint.hpp"
#include "dxSkinXmas2008Blue.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "AdvMemo.hpp"
#include "AdvGlassButton.hpp"
#include "AdvEdit.hpp"
#include "CurvyControls.hpp"
#include "AdvSmoothComboBox.hpp"
#include "AdvSmoothListBox.hpp"
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class CUdpSocketThread;
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TdxRibbonTab *MenuTab_1;
	TdxRibbon *MainRibbonMenu;
	TdxBarManager *BarMgr;
	TPanel *___pnBase;
	TNotebook *Notebook_Main;
	TAdvMemo *memo;
	TPanel *__pnBase_00_Start;
	TPanel *__pnBase_01_View;
	TPanel *__pnBase_02_Setting;
	TPanel *__pnBase_03_Test;
	TPanel *__pnBase_04_;
	TdxBar *BarMgrBar1;
	TdxBarLargeButton *MenuBtn_01;
	TdxBarLargeButton *MenuBtn_02;
	TdxBarLargeButton *MenuBtn_03;
	TdxBarLargeButton *MenuBtn_04;
	TdxBarLargeButton *MenuBtn_05;
	TdxBar *BarMgrBar2;
	TdxBarLargeButton *dxBarLargeButton1;
	TAdvMemo *memo_Msg;
	TLabel *lb_Title_Start_1;
	TAdvSmoothComboBox *cb_Protocol;
	TLabel *lb_Title_Start_2;
	TAdvEdit *ed_Local_IP_1;
	TAdvEdit *ed_Local_IP_2;
	TAdvEdit *ed_Local_IP_3;
	TAdvEdit *ed_Local_IP_4;
	TLabel *lb_Title_Start_3;
	TAdvEdit *ed_Server_IP_1;
	TAdvEdit *ed_Server_IP_2;
	TAdvEdit *ed_Server_IP_3;
	TAdvEdit *ed_Server_IP_4;
	TLabel *lb_Title_Start_4;
	TLabel *lb_Title_Start_5;
	TAdvEdit *ed_LocalPort;
	TAdvEdit *ed_ServerPort;
	TAdvGlassButton *btn_Create;
	TAdvGlassButton *btn_Send;
	TAdvEdit *ed_Type;
	TNotebook *Notebook_Send;
	TNotebook *Notebook_Recv;
	TPanel *_pnBase_S_01;
	TPanel *_pnBase_R_01;
	TPanel *_pnBase_S_02;
	TPanel *_pnBase_S_03;
	TPanel *_pnBase_R_02;
	TPanel *_pnBase_R_03;
	TAdvStringGrid *grid_Protocol_Send;
	TAdvStringGrid *grid_Protocol_Recv;
	TAdvGlassButton *btn_Back_Send;
	TAdvGlassButton *btn_Back_Recv;
	TAdvStringGrid *grid_SendProtocolList;
	TAdvStringGrid *grid_RecvProtocolList;
	TLabel *lb_Send_Title;
	TLabel *lb_Recv_Title;
	void __fastcall ClickMenuButton(TObject *Sender);
	void __fastcall dxBarLargeButton1Click(TObject *Sender);
	void __fastcall btn_SendClick(TObject *Sender);
	void __fastcall btn_CreateClick(TObject *Sender);
	void __fastcall btn_Back_SendClick(TObject *Sender);
	void __fastcall btn_Back_RecvClick(TObject *Sender);
	void __fastcall ChangeMouseCursor_ProtocolList(TObject *Sender, TShiftState Shift,
          int X, int Y);
	void __fastcall ChangeMouseCursor_ProtocolList_Out(TObject *Sender);
	void __fastcall ProtocolListDbClick(TObject *Sender, int ARow, int ACol);
	void __fastcall GetAlignment_ProtocolGrid(TObject *Sender, int ARow, int ACol, TAlignment &HAlign,
          TVAlignment &VAlign);


private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);

// START
public:	// Basic Functions
	void __fastcall InitProgram();
	void __fastcall ExitProgram();
	void __fastcall PrintMsg(UnicodeString _str);
	void __fastcall ExtractCommInformation();
	void __fastcall InitGrids();


public: // Socket
	SOCKET m_sock_UDP;
	bool __fastcall CreateUDPSocket();
	bool __fastcall CreateUDPThread();
	CUdpSocketThread* m_UdpThread;
	AnsiString m_LocalIPstr;
	AnsiString m_ServerIPstr;
	unsigned short m_ServerPort;
	unsigned short m_LocalPort;
	BYTE m_SendBuf[1500];
	BYTE m_RecvBuf[1500];

public: // Libxl
	libxl::Book* m_Book;
	bool __fastcall InitConfigExcelFile();
	bool __fastcall LoadConfigSheet();
	bool __fastcall LoadSheet(UnicodeString _SheetName, int _tag);






public: // User Message Handler
	void __fastcall PrintThreadLogMessage(TMessage &_msg);

BEGIN_MESSAGE_MAP
	MESSAGE_HANDLER(MSG_LOG_FROM_THREAD, TMessage, PrintThreadLogMessage)
END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
