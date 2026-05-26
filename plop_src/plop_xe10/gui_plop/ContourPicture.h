//---------------------------------------------------------------------------
#ifndef ContourPictureH
#define ContourPictureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Picture.h"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TContourPictureForm : public TPictureForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TContourPictureForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TContourPictureForm *ContourPictureForm;
//---------------------------------------------------------------------------
#endif
