//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TCEdit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TCEdit::TCEdit (TComponent *AOwner) : TEdit (AOwner)
{   OnEnter = Entered;
    OnExit = Exited;
}

//---------------------------------------------------------------------------

void __fastcall TCEdit::Entered (TObject *Sender)
{   if (IdPtr != NULL && Tag != -1)
        *IdPtr = Tag;
}

//---------------------------------------------------------------------------

void __fastcall TCEdit::Exited (TObject *Sender)
{   if (IdPtr != NULL && Tag != -1)
        *IdPtr = -1;
}
