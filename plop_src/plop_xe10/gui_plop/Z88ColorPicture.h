//---------------------------------------------------------------------------

#ifndef Z88ColorPictureH
#define Z88ColorPictureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ColorPicture.h"
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TZ88ColorPictureForm : public TColorPictureForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TZ88ColorPictureForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TZ88ColorPictureForm *Z88ColorPictureForm;
//---------------------------------------------------------------------------
#endif
