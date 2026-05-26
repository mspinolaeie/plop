//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ContourPicture.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Picture"
#pragma resource "*.dfm"
TContourPictureForm *ContourPictureForm;
//---------------------------------------------------------------------------
__fastcall TContourPictureForm::TContourPictureForm(TComponent* Owner)
    : TPictureForm(Owner)
{
}
//---------------------------------------------------------------------------
