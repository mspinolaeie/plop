//---------------------------------------------------------------------------
#ifndef SupportPictureH
#define SupportPictureH
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
class TSupportPictureForm : public TPictureForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TSupportPictureForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSupportPictureForm *SupportPictureForm;
//---------------------------------------------------------------------------
#endif
