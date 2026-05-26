//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
#include "MeshEdit.h"
#include "Debug.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------


void __fastcall TAboutBox::OKButtonClick(TObject *Sender)
{
Close();    
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::ProgramIconDblClick(TObject *Sender)
{
    if (CellEditForm->DebugMsgs == NULL)
    {   CellEditForm->DebugMsgs = (char *) malloc (1000000);
        CellEditForm->DebugMsgsNext = CellEditForm->DebugMsgs;
    }
    DebugForm->Show ();
}
//---------------------------------------------------------------------------




void __fastcall TAboutBox::FormCreate(TObject *Sender)
{
	Version->Caption = Version->Caption + CurrentVersion;
	CompileDateLabel->Caption = CellEditForm->GetCompileDate ();
}
//---------------------------------------------------------------------------

