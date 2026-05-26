//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PlopExecDone.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRunFinishedForm *RunFinishedForm;
//---------------------------------------------------------------------------
__fastcall TRunFinishedForm::TRunFinishedForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TRunFinishedForm::OKButtonClick(TObject *Sender)
{
    Close ();    
}
//---------------------------------------------------------------------------
