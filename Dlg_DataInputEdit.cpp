//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Dlg_DataInputEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvEdit"
#pragma link "AdvGlassButton"
#pragma resource "*.dfm"
TFormDataInputEdit *FormDataInputEdit;
//---------------------------------------------------------------------------
__fastcall TFormDataInputEdit::TFormDataInputEdit(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

__fastcall TFormDataInputEdit::TFormDataInputEdit(BYTE* _pBuffer, int _ByteIdx, int _ByteSize, int _BitIdx, int _BitSize)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

#if 0
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

#endif







