//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AutoCell.h"

#include <stdio.h>
#include "MeshEdit.h"
#include "Run.h"
#include "Debug.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAutoCellForm *AutoCellForm;


extern void err_msg (const char *m);

//---------------------------------------------------------------------------
__fastcall TAutoCellForm::TAutoCellForm(TComponent* Owner)
    : TForm(Owner)
{   ActivePanel = ActivePanelDiam;
    MirrorSizePanel->Show ();
    CellTypePanel->Hide ();
    LeftButton->Hide ();
	RightButton->Caption = "Next >>";
}
//---------------------------------------------------------------------------


void __fastcall TAutoCellForm::RightButtonClick(TObject *Sender)
{   double d;
	char str [max_line_len];
    int angle_flag;
    int rel_force_flag;
    AnsiString PlopAutoCellBase;

    PlopAutoCellBase = CellEditForm->AutoCellLoc;
	DebugMsg ("Autocell reg entry: ");
	DebugMsg (PlopAutoCellBase.c_str ());
	DebugMsg ("\n");

// #define PlopAutoCellBase    "d:\\plop\\gui_plop\\autocell\\cell"

    if (ActivePanel == ActivePanelCell)
	{   if (swscanf (DiamEdit->Text.c_str (), L" %lg", &d) != 1)
        {   LeftButtonClick (LeftButton);
            DiamEdit->Show ();
            DiamEdit->SetFocus ();
            DiamEdit->SelectAll ();
            err_msg ("Diameter does not contain a valid number!");
            return;
         }
         else
            diameter = d;
		if (swscanf (ThickEdit->Text.c_str (), L" %lg", &d) != 1)
        {   LeftButtonClick (LeftButton);
            ThickEdit->Show ();
            ThickEdit->SetFocus ();
            ThickEdit->SelectAll ();
            err_msg ("Thickness does not contain a valid number!");
            return;
         }
         else
            thickness = d;
		if (swscanf (FocalEdit->Text.c_str (), L" %lg", &d) != 1)
        {   LeftButtonClick (LeftButton);
            FocalEdit->Show ();
            FocalEdit->SetFocus ();
            FocalEdit->SelectAll ();
            err_msg ("Focal length does not contain a valid number!");
            return;
        }
        else
            focal_length = d;
		if (swscanf (SecEdit->Text.c_str (), L" %lg", &d) != 1)
		{   LeftButtonClick (LeftButton);
			SecEdit->Show ();
			SecEdit->SetFocus ();
			SecEdit->SelectAll ();
			err_msg ("Secondary diameter does not contain a valid number!");
			return;
		 }
		 else
			obstruction_diam = d;
		if (HoleEdit->Text != "" && swscanf (HoleEdit->Text.c_str (), L" %lg", &d) != 1)
		{   LeftButtonClick (LeftButton);
			HoleEdit->Show ();
			HoleEdit->SetFocus ();
			HoleEdit->SelectAll ();
			err_msg ("Hole diameter does not contain a valid number!");
			return;
		 }
		 else
			hole_diameter = d;
		 if (CellPointsRadioGroup->ItemIndex == -1)
         {  CellPointsRadioGroup->Show ();
            err_msg ("Select a cell type!");
            return;
         }
         angle_flag = AngleCheckBox->Checked;
         rel_force_flag = ForceCheckBox->Checked;
         sprintf (str, "%s_%d_%d_%d.gr", PlopAutoCellBase.c_str (), CellPointsRadioGroup->ItemIndex,
            angle_flag, rel_force_flag);
         try
         {   read_info (str);
             CellEditForm->GrOpenFile = "";
             CellEditForm->LoadFromPlop ();
             CellEditForm->CellEditScrollBarResize (CellEditForm->NumSupportRing);
             CellEditForm->CellPartScrollBarResize (CellEditForm->PartNumParts, Sender);
             CellEditForm->FileIsChanged = false;
         }
         catch (PlopException p)
         {   err_msg ("Unable to load the plop file.\nAutomatic cell generation of this type of is not yet implemented in Plop.");
            return;
         }

         CellEditForm->DiamNumState.NEValue = DiamEdit->Text;
         CellEditForm->DiamNumEdit->NumEditLoad (&CellEditForm->DiamNumState);

         CellEditForm->ThickNumState.NEValue = ThickEdit->Text;
         CellEditForm->ThickNumEdit->NumEditLoad (&CellEditForm->ThickNumState);

         CellEditForm->FocalNumState.NEValue = FocalEdit->Text;
         CellEditForm->FocalNumEdit->NumEditLoad (&CellEditForm->FocalNumState);

         CellEditForm->ObsNumState.NEValue = SecEdit->Text;
         CellEditForm->ObsNumEdit->NumEditLoad (&CellEditForm->ObsNumState);

		 CellEditForm->HoleNumState.NEValue = HoleEdit->Text;
		 CellEditForm->HoleNumEdit->NumEditLoad (&CellEditForm->HoleNumState);

		 Close ();

         RunForm->Show ();
    }
    else
    {   ActivePanel = ActivePanelDiam;
        MirrorSizePanel->Hide ();
		CellTypePanel->Show ();
		LeftButton->Show ();
		RightButton->Caption = "Done";
		ActivePanel = ActivePanelCell;
    }
}
//---------------------------------------------------------------------------

void __fastcall TAutoCellForm::LeftButtonClick(TObject *Sender)
{
    ActivePanel = ActivePanelDiam;
    CellTypePanel->Hide ();
    MirrorSizePanel->Show ();
    LeftButton->Hide ();
    RightButton->Caption = "Next >>";
}
//---------------------------------------------------------------------------

void __fastcall TAutoCellForm::MiddleButtonClick(TObject *Sender)
{
    Close ();    
}
//---------------------------------------------------------------------------



