//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Dlg_Version.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxClasses"
#pragma link "cxControls"
#pragma link "cxGraphics"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "dxBar"
#pragma link "dxRibbon"
#pragma link "dxRibbonCustomizationForm"
#pragma link "dxRibbonSkins"
#pragma link "dxSkinBlack"
#pragma link "dxSkinBlue"
#pragma link "dxSkinBlueprint"
#pragma link "dxSkinCaramel"
#pragma link "dxSkinCoffee"
#pragma link "dxSkinDarkRoom"
#pragma link "dxSkinDarkSide"
#pragma link "dxSkinDevExpressDarkStyle"
#pragma link "dxSkinDevExpressStyle"
#pragma link "dxSkinFoggy"
#pragma link "dxSkinGlassOceans"
#pragma link "dxSkinHighContrast"
#pragma link "dxSkiniMaginary"
#pragma link "dxSkinLilian"
#pragma link "dxSkinLiquidSky"
#pragma link "dxSkinLondonLiquidSky"
#pragma link "dxSkinMcSkin"
#pragma link "dxSkinMetropolis"
#pragma link "dxSkinMetropolisDark"
#pragma link "dxSkinMoneyTwins"
#pragma link "dxSkinOffice2007Black"
#pragma link "dxSkinOffice2007Blue"
#pragma link "dxSkinOffice2007Green"
#pragma link "dxSkinOffice2007Pink"
#pragma link "dxSkinOffice2007Silver"
#pragma link "dxSkinOffice2010Black"
#pragma link "dxSkinOffice2010Blue"
#pragma link "dxSkinOffice2010Silver"
#pragma link "dxSkinOffice2013DarkGray"
#pragma link "dxSkinOffice2013LightGray"
#pragma link "dxSkinOffice2013White"
#pragma link "dxSkinPumpkin"
#pragma link "dxSkinsCore"
#pragma link "dxSkinsDefaultPainters"
#pragma link "dxSkinsdxBarPainter"
#pragma link "dxSkinsdxRibbonPainter"
#pragma link "dxSkinSeven"
#pragma link "dxSkinSevenClassic"
#pragma link "dxSkinSharp"
#pragma link "dxSkinSharpPlus"
#pragma link "dxSkinSilver"
#pragma link "dxSkinSpringTime"
#pragma link "dxSkinStardust"
#pragma link "dxSkinSummer2008"
#pragma link "dxSkinTheAsphaltWorld"
#pragma link "dxSkinValentine"
#pragma link "dxSkinVisualStudio2013Blue"
#pragma link "dxSkinVisualStudio2013Dark"
#pragma link "dxSkinVisualStudio2013Light"
#pragma link "dxSkinVS2010"
#pragma link "dxSkinWhiteprint"
#pragma link "dxSkinXmas2008Blue"
#pragma link "AdvMemo"
#pragma link "AdvGlassButton"
#pragma link "AdvEdit"
#pragma link "CurvyControls"
#pragma link "AdvSmoothComboBox"
#pragma link "AdvSmoothListBox"
#pragma resource "*.dfm"
#pragma link "libxl.lib"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
	InitProgram();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::InitProgram() {

	// Common
	UnicodeString tempStr = L"";

	// Setting Default Notebook Page
	Notebook_Main->PageIndex = 0;

	// Init Variables...
	m_sock_UDP = INVALID_SOCKET;


	// Socket Init
	WSADATA data;
	WORD version;
	int ret = 0;

	version = MAKEWORD(2, 2);
	ret = WSAStartup(version, &data);
	if(ret != 0) {
		ret = WSAGetLastError();
		if(ret == WSANOTINITIALISED) {
			tempStr.sprintf(L"Socket not initialised (error code : %d)", ret);
			PrintMsg(tempStr);
		} else {
			tempStr.sprintf(L"Socket error (error code : %d)", ret);
			PrintMsg(tempStr);
		}
	} else {
		PrintMsg(L"Socket init success");
	}

	// Create UDP Socket
	//if(CreateUDPSocket() == false) return;

	// Create UDP Thread
	//if(CreateUDPThread() == false) return;

	PrintMsg(L"Init Complete");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ExitProgram() {

	// Delete Socket
	if(m_sock_UDP != INVALID_SOCKET) {
		closesocket(m_sock_UDP);
		m_sock_UDP = INVALID_SOCKET;
	}

	// Delete Thread
	if(m_UdpThread != NULL) {
		m_UdpThread->DoTerminate();
		m_UdpThread->Terminate();
		delete m_UdpThread;
		m_UdpThread = NULL;
	}

	// Socket Clean Up
	WSACleanup();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintMsg(UnicodeString _str) {
	int t_Line = memo_Msg->Lines->Add(_str);
	memo_Msg->SetCursor(0, t_Line);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ClickMenuButton(TObject *Sender)
{
	TdxBarLargeButton* p_Btn = (TdxBarLargeButton*)Sender;
	Notebook_Main->PageIndex = p_Btn->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::dxBarLargeButton1Click(TObject *Sender)
{
	TFormVersion* p_Dlg = new TFormVersion(NULL);
	p_Dlg->ShowModal();
	delete p_Dlg;
}
//---------------------------------------------------------------------------

bool __fastcall TFormMain::CreateUDPSocket() {

	// Pre return
	if(m_sock_UDP != INVALID_SOCKET) {
		PrintMsg(L"Socket exists already");
		return false;
	}

	// Common
	UnicodeString tempStr = L"";
	AnsiString t_AnsiStr = "";
	unsigned short t_Port = 0;

	struct sockaddr_in t_sockaddr_in;
	memset(&t_sockaddr_in, 0, sizeof(t_sockaddr_in));

	// Extract User Input Information
	t_sockaddr_in.sin_addr.S_un.S_un_b.s_b1 = (BYTE)ed_Local_IP_1->IntValue;
	t_sockaddr_in.sin_addr.S_un.S_un_b.s_b2 = (BYTE)ed_Local_IP_2->IntValue;
	t_sockaddr_in.sin_addr.S_un.S_un_b.s_b3 = (BYTE)ed_Local_IP_3->IntValue;
	t_sockaddr_in.sin_addr.S_un.S_un_b.s_b4 = (BYTE)ed_Local_IP_4->IntValue;
	t_sockaddr_in.sin_family = AF_INET;
	t_sockaddr_in.sin_port = htons((unsigned short)ed_LocalPort->IntValue);

	// Create Socket
	m_sock_UDP = socket(AF_INET, SOCK_DGRAM, 0);
	if(m_sock_UDP == INVALID_SOCKET) {
		PrintMsg(L"Fail to create socket");
		return false;
	}

	// Set Socket Option : REUSE
	int t_opt_reuse = 1;
	if(setsockopt(m_sock_UDP, SOL_SOCKET, SO_REUSEADDR,(char *)&t_opt_reuse, sizeof(t_opt_reuse)) == SOCKET_ERROR) {
		PrintMsg(L"Fail to set socket option (REUSE)");
		return false;
	}

	// Bind
	if(bind(m_sock_UDP, (struct sockaddr*)&t_sockaddr_in, sizeof(t_sockaddr_in)) < 0) {
		PrintMsg(L"Bind error");
		return false;
	}
	tempStr = L"Bind Local IP : ";
	tempStr += inet_ntoa(t_sockaddr_in.sin_addr);
	PrintMsg(tempStr);
	return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintThreadLogMessage(TMessage &_msg) {

	unsigned int t_wParam = _msg.WParam;
	int t_lParam = _msg.LParam;

	UnicodeString tempStr = L"";
	UnicodeString *p = NULL;
	p = (UnicodeString*)t_wParam;
	tempStr = *p;
	PrintMsg(tempStr);
}
//---------------------------------------------------------------------------

bool __fastcall TFormMain::CreateUDPThread() {

	// Common
	UnicodeString tempStr = L"";

	// Create Thread
	if(m_UdpThread != NULL) {
		tempStr.sprintf(L"Client Thread is already exists.");
		PrintMsg(tempStr);
		return false;
	}

	// Creating Client Thread
	m_UdpThread = new CUdpSocketThread(&m_sock_UDP);

	return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_SendClick(TObject *Sender)
{

	// Pre Return
	if(m_sock_UDP == INVALID_SOCKET) {
		PrintMsg(L"There is no socket");
		return;
	}

	// Common
	UnicodeString t_Str = L"";
	AnsiString t_AnsiStr = "";
	static unsigned char t_Counter = 0;
	unsigned char t_Type = StrToInt(ed_Type->Text);

	struct sockaddr_in	t_sockaddr_in;
	memset(&t_sockaddr_in, 0, sizeof(t_sockaddr_in));
	t_sockaddr_in.sin_family = AF_INET;
	t_sockaddr_in.sin_addr.s_addr = inet_addr(IP_SERVER);
	t_sockaddr_in.sin_port = htons(UDP_SERVER_PORT);

	BYTE t_Buffer[20] = {0, };
	t_Buffer[0] = 0x47;
	t_Buffer[1] = 0x42;
	t_Buffer[2] = 0x44;
	t_Buffer[3] = 0x31;
	t_Buffer[4] = ++t_Counter;
	t_Buffer[5] = t_Type;

	int t_SendSize = 20;

	t_SendSize = sendto(m_sock_UDP, t_Buffer, 20, 0, (struct sockaddr*)&t_sockaddr_in, sizeof(t_sockaddr_in));
	t_Str.sprintf(L"[SEND] Req Type : %d, Count : %d, Size : %d", t_Type, t_Counter, t_SendSize);
	PrintMsg(t_Str);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_CreateClick(TObject *Sender)
{
	// Create Socket
	switch(cb_Protocol->SelectedItemIndex) {
		case 0: // UDP
			if(CreateUDPSocket()) {
				if(CreateUDPThread() == false) {
					PrintMsg(L"Fail to Create UDP Thread");
				}
			}
			break;

		case 1:	// TCP
			PrintMsg(L"TCP not yet");
			break;

		case 2: // Multicast
			PrintMsg(L"Multicast not yet");
			break;

		default:
			break;
	}
}
//---------------------------------------------------------------------------

