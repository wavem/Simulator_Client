//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Dlg_Version.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormVersion *FormVersion;
//---------------------------------------------------------------------------
__fastcall TFormVersion::TFormVersion(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormVersion::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_ESCAPE) this->Close();
}
//---------------------------------------------------------------------------

