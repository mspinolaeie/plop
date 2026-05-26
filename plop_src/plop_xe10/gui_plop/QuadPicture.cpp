//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "QuadPicture.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Picture"
#pragma resource "*.dfm"
TQuadPictureForm *QuadPictureForm;
//---------------------------------------------------------------------------
__fastcall TQuadPictureForm::TQuadPictureForm(TComponent* Owner)
	: TPictureForm(Owner)
{
}
//---------------------------------------------------------------------------
