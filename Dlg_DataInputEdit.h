//---------------------------------------------------------------------------

#ifndef Dlg_DataInputEditH
#define Dlg_DataInputEditH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "AdvEdit.hpp"
#include "AdvGlassButton.hpp"
//---------------------------------------------------------------------------
class TFormDataInputEdit : public TForm
{
__published:	// IDE-managed Components
	TPanel *___pnBase_DataInputEdit;
	TAdvEdit *ed_Data;
	TAdvGlassButton *btn_Input;
private:	// User declarations
public:		// User declarations
	__fastcall TFormDataInputEdit(TComponent* Owner);
	__fastcall TFormDataInputEdit(BYTE* _pBuffer, int _ByteIdx, int _ByteSize, int _BitIdx, int _BitSize);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDataInputEdit *FormDataInputEdit;
//---------------------------------------------------------------------------
#endif
