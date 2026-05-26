//---------------------------------------------------------------------------
#ifndef ColorPictureH
#define ColorPictureH
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
class TColorPictureForm : public TPictureForm
{
__published:	// IDE-managed Components

private:	// User declarations
	
public:		// User declarations
    __fastcall TColorPictureForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TColorPictureForm *ColorPictureForm;
//---------------------------------------------------------------------------
#endif
