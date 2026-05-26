//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SupportPicture.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Picture"
#pragma resource "*.dfm"
TSupportPictureForm *SupportPictureForm;
//---------------------------------------------------------------------------
__fastcall TSupportPictureForm::TSupportPictureForm(TComponent* Owner)
    : TPictureForm(Owner)
{
}
//---------------------------------------------------------------------------

