//---------------------------------------------------------------------------
#ifndef CellPartPictureH
#define CellPartPictureH
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
class TCellPartPictureForm : public TPictureForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TCellPartPictureForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCellPartPictureForm *CellPartPictureForm;
//---------------------------------------------------------------------------
#endif
