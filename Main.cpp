//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Dlg_Version.h"
#include "libxl_functions.h"
#include "common_functions.h"
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
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
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
	Notebook_Send->PageIndex = 0;
	Notebook_Recv->PageIndex = 0;

	// Init Variables...
	m_sock_UDP = INVALID_SOCKET;
	m_UdpThread = NULL;
	m_LocalIPstr = "";
	m_ServerIPstr = "";
	m_ServerPort = 0;
	m_LocalPort = 0;
	memset(m_SendBuf, 0, UDP_SEND_BUF_SIZE);
	memset(m_RecvBuf, 0, UDP_RECV_BUF_SIZE);
	m_SendProtocolSize = 0;
	m_RecvProtocolSize = 0;


	// Init Grids
	InitGrids();

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



	// Config Excel File Init
	if(InitConfigExcelFile()) {
		// Load Sheet Routine
		if(LoadConfigSheet() == false) {
			PrintMsg(L"Fail to load config sheet");
			return;
		}

		// Load Protocol Sheet Routine
	}

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

	// Release Libxl
	if(m_Book) {
		m_Book->release();
		m_Book = NULL;
	}
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

	// Input Comm Information
	t_sockaddr_in.sin_family = AF_INET;
	t_sockaddr_in.sin_addr.s_addr = inet_addr(m_LocalIPstr.c_str());
	t_sockaddr_in.sin_port = htons(m_LocalPort);

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
	ExtractCommInformation();

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

void __fastcall TFormMain::ExtractCommInformation() {

	// Common
	struct sockaddr_in t_sockaddr_in;
	memset(&t_sockaddr_in, 0, sizeof(t_sockaddr_in));

	// Extract User Input Information
	m_LocalPort = (unsigned short)ed_LocalPort->IntValue;
	m_ServerPort = (unsigned short)ed_ServerPort->IntValue;

	t_sockaddr_in.sin_addr.S_un.S_un_b.s_b1 = (BYTE)ed_Local_IP_1->IntValue;
	t_sockaddr_in.sin_addr.S_un.S_un_b.s_b2 = (BYTE)ed_Local_IP_2->IntValue;
	t_sockaddr_in.sin_addr.S_un.S_un_b.s_b3 = (BYTE)ed_Local_IP_3->IntValue;
	t_sockaddr_in.sin_addr.S_un.S_un_b.s_b4 = (BYTE)ed_Local_IP_4->IntValue;
	m_LocalIPstr = inet_ntoa(t_sockaddr_in.sin_addr);

	t_sockaddr_in.sin_addr.S_un.S_un_b.s_b1 = (BYTE)ed_Server_IP_1->IntValue;
	t_sockaddr_in.sin_addr.S_un.S_un_b.s_b2 = (BYTE)ed_Server_IP_2->IntValue;
	t_sockaddr_in.sin_addr.S_un.S_un_b.s_b3 = (BYTE)ed_Server_IP_3->IntValue;
	t_sockaddr_in.sin_addr.S_un.S_un_b.s_b4 = (BYTE)ed_Server_IP_4->IntValue;
	m_ServerIPstr = inet_ntoa(t_sockaddr_in.sin_addr);
}
//---------------------------------------------------------------------------

bool __fastcall TFormMain::InitConfigExcelFile() {

	m_Book = xlCreateXMLBook();
	if(m_Book) {
		m_Book->setKey(L"JungWook Son", L"windows-2124230806c1e30f66bf6365a7l1hdm8");
		if(m_Book->load(L"Config.xlsx")) {
			//if(LoadSheet(L"Test")) PrintMsg(L"Success to load sheet");
		} else {
			PrintMsg(L"Fail to Load Excel File");
			return false;
		}
	} else {
		PrintMsg(L"Fail to Create Book");
		return false;
	}
	PrintMsg(L"Config File Init Complete");
	return true;
}
//---------------------------------------------------------------------------

bool __fastcall TFormMain::LoadConfigSheet() {

	// Common
	UnicodeString tempStr = L"";
	libxl::Sheet* t_pSheet = NULL;
	libxl::Format* t_pFormat = NULL;
	int t_RowStart = 3; // USER DEFINE
	int t_RowEnd = 0;
	int t_gridRow = 1;

	// Load Sheet
	t_pSheet = getSheetByName(m_Book, L"Config");
	if(!t_pSheet) {
		return false;
	}

	// Get Last Row Information
	t_RowEnd = t_pSheet->lastRow();
	//tempStr.sprintf(L"Last Row : %d", t_RowEnd);
	//PrintMsg(tempStr);

	// Load Send Protocol List
	for(int i = t_RowStart ; i < t_RowEnd ; i++) {

		// Pre Break;
		tempStr = getCellValue(t_pSheet, i, 2);
		if(tempStr == L"") break;

		grid_SendProtocolList->Cells[0][t_gridRow] = getCellValue(t_pSheet, i, 1);
		grid_SendProtocolList->Cells[1][t_gridRow] = getCellValue(t_pSheet, i, 2);
		grid_SendProtocolList->Cells[2][t_gridRow] = getCellValue(t_pSheet, i, 3);
		grid_SendProtocolList->Cells[3][t_gridRow] = getCellValue(t_pSheet, i, 4);
		t_gridRow++;
	}

	// Load Recv Protocol List
	t_gridRow = 1; // USER DEFINE
	for(int i = t_RowStart ; i < t_RowEnd ; i++) {

		// Pre Break;
		tempStr = getCellValue(t_pSheet, i, 9);
		if(tempStr == L"") break;

		grid_RecvProtocolList->Cells[0][t_gridRow] = getCellValue(t_pSheet, i, 8);
		grid_RecvProtocolList->Cells[1][t_gridRow] = getCellValue(t_pSheet, i, 9);
		grid_RecvProtocolList->Cells[2][t_gridRow] = getCellValue(t_pSheet, i, 10);
		grid_RecvProtocolList->Cells[3][t_gridRow] = getCellValue(t_pSheet, i, 11);
		t_gridRow++;
	}

	return true;
}
//---------------------------------------------------------------------------

bool __fastcall TFormMain::LoadSheet(UnicodeString _SheetName, int _tag) {

	// Common
	TAdvStringGrid* p_grid = NULL;
	UnicodeString tempStr = L"";
	if(_tag == 0) {
		p_grid = grid_Protocol_Send;
	} else {
		p_grid = grid_Protocol_Recv;
	}

	libxl::Sheet* t_pSheet = NULL;
	libxl::Format* t_pFormat = NULL;
	int t_RowLast = 0;
	int t_TotalByteCount = 0;
	bool t_bIsMerge = false;

	int t_RowStart = 0;
	int t_RowEnd = 0;
	int t_ColStart = 0;
	int t_ColEnd = 0;

	int t_gridRow = 0;
	int t_gridCol = 0;

	int t_merge_row_first = 0;
	int t_merge_col_first = 0;
	int t_merge_row_last = 0;
	int t_merge_col_last = 0;

	int t_H_gap = 0;
	int t_V_gap = 0;

	// Load Sheet
	t_pSheet = getSheetByName(m_Book, _SheetName.w_str());
	if(!t_pSheet) {
		tempStr = L"Fail to Load sheet : ";
		tempStr += _SheetName;
		PrintMsg(tempStr);
		return false;
	}

	// Get Last Row Information
	t_RowLast = t_pSheet->lastRow();
	tempStr.sprintf(L"Last Row : %d", t_RowLast);
	PrintMsg(tempStr);

	// Get Row/Col Information
	t_RowStart = DEFAULT_PROTOCOL_INFO_LINE_COUNT;
	t_RowEnd = t_RowLast;
	t_ColStart = DEFAULT_PROTOCOL_COL_START + 1; // +1 means real data area.
	t_ColEnd = DEFAULT_PROTOCOL_COL_START + 9; // 8 + 1 == 9

	// Set Row Count
	t_TotalByteCount = t_RowLast - DEFAULT_PROTOCOL_INFO_LINE_COUNT;
	p_grid->RowCount = t_TotalByteCount + 1; // +1 is Fixed Row

	// Load Byte Index and Print it into Grid
	for(int i = 0 ; i < t_TotalByteCount ; i++) {
		tempStr = getCellValue(t_pSheet, i + DEFAULT_PROTOCOL_INFO_LINE_COUNT, 2);
		p_grid->Cells[0][i + 1] = tempStr;
	}

	// Merge Sync
	t_gridRow = 1;
	t_gridCol = 1;
	for(int row = t_RowStart ; row < t_RowEnd ; row++) {
		for(int col = t_ColStart ; col < t_ColEnd ; col++) {
			t_bIsMerge = t_pSheet->getMerge(row, col, &t_merge_row_first, &t_merge_row_last, &t_merge_col_first, &t_merge_col_last);
			t_gridCol = col - t_ColStart + 1;
			tempStr = getCellValue(t_pSheet, row, col);
			p_grid->Cells[t_gridCol][t_gridRow] = tempStr;

			if(t_bIsMerge) {
				t_H_gap = t_merge_col_last - t_merge_col_first + 1; // +1 is essential
				t_V_gap = t_merge_row_last - t_merge_row_first;
				p_grid->MergeCells(t_gridCol, t_gridRow, t_H_gap, t_V_gap + 1);
				col += (t_H_gap - 1);
				row += t_V_gap;
				t_gridRow += t_V_gap;
			}
		}
		t_gridRow++;
	}

	return true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::InitGrids() {

	grid_SendProtocolList->Cells[0][0] = L"Idx";
	grid_SendProtocolList->Cells[1][0] = L"Protocol Name";
	grid_SendProtocolList->Cells[2][0] = L"Sheet Name";
	grid_SendProtocolList->Cells[3][0] = L"Size(Byte)";

	grid_RecvProtocolList->Cells[0][0] = L"Idx";
	grid_RecvProtocolList->Cells[1][0] = L"Protocol Name";
	grid_RecvProtocolList->Cells[2][0] = L"Sheet Name";
	grid_RecvProtocolList->Cells[3][0] = L"Size(Byte)";

	grid_Protocol_Send->Cells[0][0] = L"BYTE";
	grid_Protocol_Send->Cells[1][0] = L"Bit 7";
	grid_Protocol_Send->Cells[2][0] = L"Bit 6";
	grid_Protocol_Send->Cells[3][0] = L"Bit 5";
	grid_Protocol_Send->Cells[4][0] = L"Bit 4";
	grid_Protocol_Send->Cells[5][0] = L"Bit 3";
	grid_Protocol_Send->Cells[6][0] = L"Bit 2";
	grid_Protocol_Send->Cells[7][0] = L"Bit 1";
	grid_Protocol_Send->Cells[8][0] = L"Bit 0";

	grid_Protocol_Recv->Cells[0][0] = L"BYTE";
	grid_Protocol_Recv->Cells[1][0] = L"Bit 7";
	grid_Protocol_Recv->Cells[2][0] = L"Bit 6";
	grid_Protocol_Recv->Cells[3][0] = L"Bit 5";
	grid_Protocol_Recv->Cells[4][0] = L"Bit 4";
	grid_Protocol_Recv->Cells[5][0] = L"Bit 3";
	grid_Protocol_Recv->Cells[6][0] = L"Bit 2";
	grid_Protocol_Recv->Cells[7][0] = L"Bit 1";
	grid_Protocol_Recv->Cells[8][0] = L"Bit 0";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_Back_SendClick(TObject *Sender)
{
	Notebook_Send->PageIndex = 0;
	lb_Send_Title->Caption = L"Send Protocol List";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::btn_Back_RecvClick(TObject *Sender)
{
	Notebook_Recv->PageIndex = 0;
	lb_Recv_Title->Caption = L"Recv Protocol List";
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ChangeMouseCursor_ProtocolList(TObject *Sender, TShiftState Shift,
		  int X, int Y)
{
	TAdvStringGrid* p_grid = (TAdvStringGrid*)Sender;

	int t_Row = 0;
	int t_Col = 0;

	p_grid->MouseToCell(X, Y, t_Col, t_Row);
	if(t_Col < 0 || t_Row < 0) {
	    p_grid->Cursor = crDefault;
		return;
	}
	if(t_Col == 0 || t_Row == 0 || p_grid->Cells[t_Col][t_Row] == L"") {
		p_grid->Cursor = crDefault;
	} else {
		p_grid->Cursor = crHandPoint;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ChangeMouseCursor_ProtocolList_Out(TObject *Sender)
{
	TAdvStringGrid *p_grid = (TAdvStringGrid*)Sender;
	p_grid->Cursor = crDefault;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ProtocolListDbClick(TObject *Sender, int ARow, int ACol)
{
	// Common
	TAdvStringGrid* p_grid = (TAdvStringGrid*)Sender;
	UnicodeString tempStr = L"";
	UnicodeString t_ProtocolName = L"";
	UnicodeString t_ProtocolSize = L"";
	int t_Tag = p_grid->Tag;
	if(t_Tag == 0) {
		// Send Protocol List
		p_grid = grid_SendProtocolList;
	} else {
		// Recv Protocol List
		p_grid = grid_RecvProtocolList;
	}

	// Pre Return
	if(ARow == 0 || ACol == 0) return;
	tempStr = p_grid->Cells[ACol][ARow];
	if(tempStr == L"") return;

	// Extract Target Protocol Information (for print information into title label)
	t_ProtocolName = p_grid->Cells[1][ARow];
	t_ProtocolSize = p_grid->Cells[3][ARow];

	// Extract Target Sheet Name
	tempStr = p_grid->Cells[2][ARow];

	if(LoadSheet(tempStr, t_Tag) == false) {
		ShowMessage(L"There is no sheet");
		return;
	}




	// Final Routine
	if(t_Tag == 0) {
		// Send Protocol List
		Notebook_Send->PageIndex = 1;
		tempStr = L"Send Protocol Name : ";
		tempStr += t_ProtocolName;
		tempStr += L"            Size : ";
		tempStr += t_ProtocolSize;
		tempStr += L" Byte";
		m_SendProtocolSize = StrToInt(t_ProtocolSize);
		lb_Send_Title->Caption = tempStr;
	} else {
		// Recv Protocol List
		Notebook_Recv->PageIndex = 1;
		tempStr = L"Recv Protocol Name : ";
		tempStr += t_ProtocolName;
		tempStr += L"            Size : ";
		tempStr += t_ProtocolSize;
		tempStr += L" Byte";
		m_RecvProtocolSize = StrToInt(t_ProtocolSize);
		lb_Recv_Title->Caption = tempStr;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::GetAlignment_ProtocolGrid(TObject *Sender, int ARow, int ACol,
          TAlignment &HAlign, TVAlignment &VAlign)
{
	HAlign = taCenter;
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::OnMouseMove_Protocol(TObject *Sender, TShiftState Shift,
		  int X, int Y)
{
	// Mouse Move
	m_ClickedX = X;
	m_ClickedY = Y;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::OnClickCell_Protocol(TObject *Sender, int ARow, int ACol)
{
	m_ClickedRow = ARow;
	m_ClickedCol = ACol;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::RightClick_Protocol(TObject *Sender, int ARow, int ACol)
{
	// Right Click Routine


	// Pre Return
	if(ARow <= 0 || ACol <= 0) return;

	// Common
	TAdvStringGrid* p_grid = (TAdvStringGrid*)Sender;
	int t_Tag = p_grid->Tag;
	DWORD t_dword = 0; // Parameter For Func : SendMessage().

	WORD t_Lword = m_ClickedX; // X
	WORD t_Hword = m_ClickedY; // Y

	t_dword = t_Hword;
	t_dword = (t_dword << 16) | t_Lword;

	SendMessage(p_grid->Handle, WM_LBUTTONDOWN, MK_LBUTTON, t_dword);


	// HB Test Routine Start
	//if(m_bProtocolGridCtrlKeyDown) {
	//	CheckandRunORStopHB(m_ClickedRow, m_ClickedCol);
	//	return;
	//}
	// HB Test Routine END



	// Real Processing...
	DWORD t_Option = 0;

	// Declare & Init Variables
	//bool t_bTurnOn = false;
	//if(p_grid->Colors[m_ClickedCol][m_ClickedRow] == clLime) {
	//	t_bTurnOn = false;
	//} else {
	//	t_bTurnOn = true;
	//}

	//DoTestDeviceProtocol(p_grid, m_ClickedRow, m_ClickedCol, t_bTurnOn, t_Option);
	SendMessage(p_grid->Handle, WM_LBUTTONUP, MK_LBUTTON, t_dword); // Release Mouse Clicked Status (2019-05-13 mjw)


	// Test Code
	//p_grid->Colors[m_ClickedCol][m_ClickedRow] = clLime;
	UnicodeString tempStr = L"";
	tempStr.sprintf(L"ARow : %d, ACol : %d", ARow, ACol);
	PrintMsg(tempStr);

	tempStr.sprintf(L"CRow : %d, CCol : %d", m_ClickedRow, m_ClickedCol);
	PrintMsg(tempStr);

	ToggleBufferData(p_grid, m_ClickedRow, m_ClickedCol);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ToggleBufferData(TAdvStringGrid* _pGrid, int _Row, int _Col) {

	// Common
	TAdvStringGrid* p_grid = _pGrid;
	int t_Tag = p_grid->Tag;
	int t_DataSize = 0;
	BYTE* t_pBuffer = NULL;

	if(t_Tag == SEND_PROTOCOL_TYPE) {
		t_DataSize = m_SendProtocolSize;
		t_pBuffer = m_SendBuf;
	} else if(t_Tag == RECV_PROTOCOL_TYPE) {
		t_DataSize = m_RecvProtocolSize;
		t_pBuffer = m_RecvBuf;
	}

	// Check Merge
	if(p_grid->IsMergedCell(_Col, _Row)) {
		if(t_pBuffer[_Row - 1] == 0) {
			t_pBuffer[_Row - 1] = 0xFF;
		} else {
			t_pBuffer[_Row - 1] = 0x00;
		}
	} else {
		t_pBuffer[_Row - 1] = _BitToggle(t_pBuffer[_Row - 1], _Col - 1);
	}
	DisplayBufferDataIntoGrid(t_Tag);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::tm_SendDataViewTimer(TObject *Sender)
{
	DisplayBufferDataIntoGrid(SEND_PROTOCOL_TYPE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::DisplayBufferDataIntoGrid(int _type) {

	// Common
	UnicodeString tempStr = L"";
	UnicodeString t_FinalStr = L"";
	TAdvStringGrid* p_grid = NULL;
	int t_DataSize = 0;
	int t_GridRow = 1;
	int t_GridCol = 1;
	BYTE* t_pBuffer = NULL;

	// Cell Merge Variables
	TPoint t_point;
	int t_Span_X = 0;
	int t_Span_Y = 0;


	if(_type == SEND_PROTOCOL_TYPE) {
		p_grid = grid_Protocol_Send;
		t_DataSize = m_SendProtocolSize;
		t_pBuffer = m_SendBuf;
	} else if(_type == RECV_PROTOCOL_TYPE) {
		p_grid = grid_Protocol_Recv;
		t_DataSize = m_RecvProtocolSize;
		t_pBuffer = m_RecvBuf;
	}

	// Memory Allocate
	BYTE* t_Buffer = new BYTE[t_DataSize];
	memcpy(t_Buffer, t_pBuffer, t_DataSize);


	while(t_GridRow <= t_DataSize) {

		// Check Cell is Merged

		if(p_grid->IsMergedCell(t_GridCol, t_GridRow)) {
			t_point = p_grid->CellSpan(t_GridCol, t_GridRow);
			t_Span_X = t_point.x;
			t_Span_Y = t_point.y;

			if(t_Span_Y > 0) { // More than 1 Byte Merge
				switch(t_Span_Y) {
					case 1: // 2 BTYE
						// Color Setting
						if(t_Buffer[t_GridRow - 1] == 0 && t_Buffer[t_GridRow - 1 + 1] == 0) {
							p_grid->Colors[t_GridCol][t_GridRow] = clWhite;
						} else {
							p_grid->Colors[t_GridCol][t_GridRow] = clLime;
						}

						// Value Setting
						t_FinalStr = ExtractOriginSignalName(p_grid->Cells[t_GridCol][t_GridRow]);
						tempStr.sprintf(L"\n%02X%02X", t_Buffer[t_GridRow - 1], t_Buffer[t_GridRow + 1 - 1]);
						t_FinalStr += tempStr;
						p_grid->Cells[t_GridCol][t_GridRow] = t_FinalStr;
						t_GridRow += 2;
						continue;
						break;

					case 3:
						// Later...
						break;

					default:
						break;
				}
			} else { // Less than 1 Byte Merge
				switch(t_Span_X) {
					default:
						break;

					case 7: // (8 Bit : 1 Byte)
						// Color Setting
						if(t_Buffer[t_GridRow - 1] == 0) {
							p_grid->Colors[t_GridCol][t_GridRow] = clWhite;
						} else {
							p_grid->Colors[t_GridCol][t_GridRow] = clLime;
						}

						// Value Setting
						t_FinalStr = ExtractOriginSignalName(p_grid->Cells[t_GridCol][t_GridRow]);
						tempStr.sprintf(L"\n%02X", t_Buffer[t_GridRow - 1]);
						t_FinalStr += tempStr;
						p_grid->Cells[t_GridCol][t_GridRow] = t_FinalStr;
						t_GridRow++;
						continue;
						break;

					case 4:
						break;


				}

			}

		} else {
			if(_BitCheck(t_Buffer[t_GridRow - 1], t_GridCol - 1)) {
				p_grid->Colors[t_GridCol][t_GridRow] = clLime;
			} else {
				p_grid->Colors[t_GridCol][t_GridRow] = clWhite;
			}
		}



		if(++t_GridCol == 9) {
			t_GridCol = 1;
			t_GridRow++;
		}
	}





	// Release Allocated Memory
	delete t_Buffer;
}
//---------------------------------------------------------------------------

UnicodeString TFormMain::ExtractOriginSignalName(UnicodeString _str) {
	UnicodeString t_FinalStr = _str;
	for(int i = 0 ; i < _str.Length() ; i++) {
		if(_str.IsDelimiter(L"\n", i)) {
			t_FinalStr = _str.SubString(0, i - 1);
			break;
		}
	}
	return t_FinalStr;
}
//---------------------------------------------------------------------------
