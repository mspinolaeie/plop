//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Z88ColorPicture.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ColorPicture"
#pragma resource "*.dfm"
TZ88ColorPictureForm *Z88ColorPictureForm;
//---------------------------------------------------------------------------
__fastcall TZ88ColorPictureForm::TZ88ColorPictureForm(TComponent* Owner)
	: TColorPictureForm(Owner)
{
}
//---------------------------------------------------------------------------

