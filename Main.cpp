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
	if(CreateUDPSocket() == false) return;

	// Create T Client Thread
	//if(CreateClientThread() == false) return;

	PrintMsg(L"Init Complete");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ExitProgram() {

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PrintMsg(UnicodeString _str) {
	int t_Line = memo->Lines->Add(_str);
	memo->SetCursor(0, t_Line);
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


	return true;
}
//---------------------------------------------------------------------------
