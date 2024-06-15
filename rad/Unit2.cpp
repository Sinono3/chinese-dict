//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TAddNewEntryWindow *AddNewEntryWindow;
//---------------------------------------------------------------------------
__fastcall TAddNewEntryWindow::TAddNewEntryWindow(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TAddNewEntryWindow::FieldRequieredWarning(TObject *Sender)
{
	if (CharEditBox->Text == "")
	{
	FieldRequieredLabel->Visible = true;
	}
	else
	{
	FieldRequieredLabel->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAddNewEntryWindow::CancelClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TAddNewEntryWindow::ClearEditButton1Click(TObject *Sender)
{
	CharEditBox->Text=="";
}
//---------------------------------------------------------------------------
void __fastcall TAddNewEntryWindow::ClearEditButton2Click(TObject *Sender)
{
	PinyinEditBox->Text=="";
}
//---------------------------------------------------------------------------
void __fastcall TAddNewEntryWindow::ClearEditButton3Click(TObject *Sender)
{
	DefEditBox->Text=="";
}
//---------------------------------------------------------------------------
