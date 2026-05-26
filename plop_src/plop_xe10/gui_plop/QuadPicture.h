//---------------------------------------------------------------------------

#ifndef QuadPictureH
#define QuadPictureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Picture.h"
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TQuadPictureForm : public TPictureForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TQuadPictureForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQuadPictureForm *QuadPictureForm;
//---------------------------------------------------------------------------
#endif
