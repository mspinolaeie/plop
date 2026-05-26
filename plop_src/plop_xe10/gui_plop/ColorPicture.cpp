//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ColorPicture.h"

#include "plate_global.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Picture"
#pragma resource "*.dfm"
TColorPictureForm *ColorPictureForm;
//---------------------------------------------------------------------------
__fastcall TColorPictureForm::TColorPictureForm(TComponent* Owner)
    : TPictureForm(Owner)
{
}

