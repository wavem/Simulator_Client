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
					t_CurrentValue = m_pBuffer[m_ByteIdx] >> (m_BitIdx - 6) & 0x7F;
					break;
				case 6:
					t_CurrentValue = m_pBuffer[m_ByteIdx] >> (m_BitIdx - 5) & 0x3F;
					break;
				case 5:
					t_CurrentValue = m_pBuffer[m_ByteIdx] >> (m_BitIdx - 4) & 0x1F;
					break;
				case 4:
					t_CurrentValue = m_pBuffer[m_ByteIdx] >> (m_BitIdx - 3) & 0x0F;
					break;
				case 3:
					t_CurrentValue = m_pBuffer[m_ByteIdx] >> (m_BitIdx - 2) & 0x07;
					break;
				case 2:
					t_CurrentValue = m_pBuffer[m_ByteIdx] >> (m_BitIdx - 1) & 0x03;
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

void __fastcall TFormDataInputEdit::btn_InputClick(TObject *Sender)
{
	// Common
	int t_Value = ed_Data->IntValue;
	BYTE t_CurrentByte = 0;
	BYTE t_InputByte = 0;

	// Input Value Routine
	switch(m_ByteSize) {
		default:
			break;

		case 1:
		{
			t_CurrentByte = m_pBuffer[m_ByteIdx];
			t_InputByte = t_Value;
			switch(m_BitSize) {
				default:
					break;
				case 8:
					//memcpy(&(m_pBuffer[m_ByteIdx]), &t_Value, 1);
					break;
				case 7:
					t_InputByte = t_InputByte << (m_BitIdx - 6) & (0x7F << (m_BitIdx - 6));
					t_CurrentByte = t_CurrentByte & (0x01 << ((7 - m_BitIdx) * 7));
					t_InputByte |= t_CurrentByte;
					break;
				case 6:

					break;
				case 5:

					break;
				case 4:

					break;
				case 3:

					break;
				case 2:

					break;
			}
			memcpy(&(m_pBuffer[m_ByteIdx]), &t_InputByte, 1);
			break;
		}

		case 2:
			memcpy(&(m_pBuffer[m_ByteIdx]), &t_Value, 2);
			break;

		case 4:
			memcpy(&(m_pBuffer[m_ByteIdx]), &t_Value, 4);
			break;
	}

	this->Close();
}
//---------------------------------------------------------------------------

