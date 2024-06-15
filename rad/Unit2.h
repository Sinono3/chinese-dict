//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TAddNewEntryWindow : public TForm
{
__published:	// IDE-managed Components
	TLabel *CharLabel;
	TLabel *PinyinLabel;
	TLabel *DefLabel;
	TEdit *CharEditBox;
	TEdit *PinyinEditBox;
	TEdit *DefEditBox;
	TLabel *AddNewEntryWindowLabel;
	TButton *CancelButton;
	TButton *AcceptButton;
	TLabel *FieldRequieredLabel;
	TClearEditButton *ClearEditButton1;
	TClearEditButton *ClearEditButton2;
	TClearEditButton *ClearEditButton3;
	void __fastcall FieldRequieredWarning(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall ClearEditButton1Click(TObject *Sender);
	void __fastcall ClearEditButton2Click(TObject *Sender);
	void __fastcall ClearEditButton3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TAddNewEntryWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAddNewEntryWindow *AddNewEntryWindow;
//---------------------------------------------------------------------------
#endif
