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
	// Common
	m_pBuffer = _pBuffer;
	m_ByteIdx = _ByteIdx;
	m_BitIdx = _BitIdx;
	m_ByteSize = _ByteSize;
	m_BitSize = _BitSize;
	int t_CurrentValue = 0;

	// Extract Current Value Routine
	switch(m_ByteSize) {
		default:
			break;

		case 1:
		{
			switch(m_BitSize) {
				case 8:
					t_CurrentValue = m_pBuffer[m_ByteIdx];
					break;
				case 7:
					t_CurrentValue = m_pBuffer[m_ByteIdx] >> (_BitIdx - 6) & 0x7F;
					break;
				case 6:
					t_CurrentValue = m_pBuffer[m_ByteIdx] >> (_BitIdx - 5) & 0x3F;
					break;
				case 5:
					t_CurrentValue = m_pBuffer[m_ByteIdx] >> (_BitIdx - 4) & 0x1F;
					break;
				case 4:
					t_CurrentValue = m_pBuffer[m_ByteIdx] >> (_BitIdx - 3) & 0x0F;
					break;
				case 3:
					t_CurrentValue = m_pBuffer[m_ByteIdx] >> (_BitIdx - 2) & 0x07;
					break;
				case 2:
					t_CurrentValue = m_pBuffer[m_ByteIdx] >> (_BitIdx - 1) & 0x03;
					break;
			}
			break;
		}

		case 2:
			memcpy(&t_CurrentValue, &(m_pBuffer[m_ByteIdx]), 2);
			break;

		case 4:
			memcpy(&t_CurrentValue, &(m_pBuffer[m_ByteIdx]), 4);
			break;
	}

	ed_Data->Text = IntToStr(t_CurrentValue);
}
//---------------------------------------------------------------------------
