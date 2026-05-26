//---------------------------------------------------------------------------
#ifndef MeshPictureH
#define MeshPictureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Picture.h"
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TMeshPictureForm : public TPictureForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TMeshPictureForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMeshPictureForm *MeshPictureForm;
//---------------------------------------------------------------------------
#endif
