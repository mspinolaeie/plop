//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CellPartPicture.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Picture"
#pragma resource "*.dfm"
TCellPartPictureForm *CellPartPictureForm;
//---------------------------------------------------------------------------
__fastcall TCellPartPictureForm::TCellPartPictureForm(TComponent* Owner)
    : TPictureForm(Owner)
{
}
//---------------------------------------------------------------------------

