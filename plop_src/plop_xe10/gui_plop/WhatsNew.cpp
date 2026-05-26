//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WhatsNew.h"
#include "MeshEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWhatsNewForm *WhatsNewForm;
//---------------------------------------------------------------------------
__fastcall TWhatsNewForm::TWhatsNewForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TWhatsNewForm::OKButtonClick(TObject *Sender)
{
	Close ();	
}
//---------------------------------------------------------------------------

void __fastcall TWhatsNewForm::FormCreate(TObject *Sender)
{
	if (CellEditForm->IsFirstRun ()) {
		Show ();
	}
}
//---------------------------------------------------------------------------

