//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PlopExec.h"
#include "Run.h"
#include "MeshPicture.h"
#include "SupportPicture.h"
#include "ContourPicture.h"
#include "ColorPicture.h"
#include "CellPartPicture.h"
#include "MeshEdit.h"
#include "PartDimension.h"

#include "Debug.h"
#include "QuadPicture.h"

#pragma package(smart_init)

extern TRunForm *RunForm;
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall PlopExec::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall PlopExec::PlopExec(bool CreateSuspended)
    : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall PlopExec::Finished (TObject *Sender)
{   RunForm->ExecFinished ();
}
//---------------------------------------------------------------------------

void _fastcall PlopExec::UpdatePics(void)
{
    MeshPictureForm->SetNewPicAvail ();
    SupportPictureForm->SetNewPicAvail ();
    ColorPictureForm->SetNewPicAvail ();
    ContourPictureForm->SetNewPicAvail ();
    CellPartPictureForm->SetNewPicAvail ();
    PartDimensionForm->SetNewPicAvail ();
    QuadPictureForm->SetNewPicAvail ();

}
//---------------------------------------------------------------------------

void _fastcall PlopExec::UpdatePicsSync(void)
{   Synchronize ((TThreadMethod)&UpdatePics);
}


//---------------------------------------------------------------------------
void __fastcall PlopExec::Execute()
{   int i;

	OnTerminate = Finished;

    for (i = 0; i < ndebugs; i++) {
        if (debugs [i] && debug_file == NULL) {
            if (debug_file == NULL) {
				(void) Application->MessageBox (L"You forgot to set the debug file. I'm going to croak now.",
					  L"you stupid donkey", MB_OK + MB_ICONEXCLAMATION);
                return;
            }
        }
    }
	try
    {   init_default_basis ();

	    plate_init ();
		run_plate ();
    }
    catch (plop_terminate p)
	{   (void) Application->MessageBox (L"Plop has been terminated.", L"Plop Error",
               MB_OK + MB_ICONEXCLAMATION);
        return;
    }

    RunForm->UpdateError ();
    Synchronize ((TThreadMethod)&UpdatePics);
}
//---------------------------------------------------------------------------

void __fastcall PlopExec::UpdateOptStatus(void)
{   RunForm->UpdateOptStatus ();
}
//---------------------------------------------------------------------------

void __fastcall PlopExec::UpdateOptStatusSync(void)
{   Synchronize ((TThreadMethod)&UpdateOptStatus);
}

//---------------------------------------------------------------------------
void __fastcall PlopExec::UpdateStatusSync (void)
{   RunForm->UpdateStatus (StatusPos);
}

//---------------------------------------------------------------------------

void __fastcall PlopExec::UpdateStatus (int n)
{   StatusPos = n;
    Synchronize ((TThreadMethod)&UpdateStatusSync);
}

//---------------------------------------------------------------------------

void UpdateSparseStat (int n)
{   RunForm->ExecThread->UpdateStatus (n);
}
//---------------------------------------------------------------------------

void __fastcall PlopExec::UpdateMonte (void)
{   RunForm->UpdateMonteSync ();
}
//---------------------------------------------------------------------------
void __fastcall PlopExec::UpdateMonteSync (void)
{   Synchronize ((TThreadMethod) &UpdateMonte);
}

//---------------------------------------------------------------------------

void terminate_plop (void)
{   throw plop_terminate (0);
}
//---------------------------------------------------------------------------
void __fastcall PlopExec::UpdateCellEditOptVars (void)
{   CellEditForm->UpdateFromOpt ();
}

//---------------------------------------------------------------------------
void __fastcall PlopExec::UpdateCellEditOptVarsSync (void)
{   Synchronize ((TThreadMethod) &UpdateCellEditOptVars);
}

//---------------------------------------------------------------------------

void UpdateCellEditOptVars (void)
{   RunForm->ExecThread->UpdateCellEditOptVarsSync ();
}

