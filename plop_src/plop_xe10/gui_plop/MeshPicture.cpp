//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MeshPicture.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Picture"
#pragma resource "*.dfm"
TMeshPictureForm *MeshPictureForm;
//---------------------------------------------------------------------------
__fastcall TMeshPictureForm::TMeshPictureForm(TComponent* Owner)
    : TPictureForm(Owner)
{
}
//---------------------------------------------------------------------------

