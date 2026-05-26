//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Run.h"
#include "MeshPicture.h"
#include "SupportPicture.h"
#include "ContourPicture.h"
#include "ColorPicture.h"
#include "MeshEdit.h"

#include <stdio.h>
#include <process.h>
#include <dir.h>
#include <string.h>

#include "global.h"
#include "plot.h"
#include "plate_global.h"
#include "PlopExecDone.h"
#include "SparseStat.h"
#include "CellPartPicture.h"
#include "PartDimension.h"
#include "plop_parms.h"
#include "grid_gen.h"
#include "QuadPicture.h"
#include "Z88ColorPicture.h"

extern void err_msg (const char *msg);
extern void warn_msg (const char *);
extern void LockPlopData (int);
extern void UnlockPlopData (void);

extern void copy_plot_data (void);

extern void DebugMsg (const char *m);
wchar_t* __fastcall UnicodeOf(const char* c);
char* __fastcall AnsiOf(wchar_t* w);

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRunForm *RunForm;
//---------------------------------------------------------------------------
__fastcall TRunForm::TRunForm(TComponent* Owner)
    : TForm(Owner)
{    SolverProgressBar->Max = SparseStateSteps;

	HaveOutput = false;
	z88_input_files_valid = 0;

}
//---------------------------------------------------------------------------



void __fastcall TRunForm::MeshMenuItemClick(TObject *Sender)
{
    MeshPictureForm->Show ();
}
//---------------------------------------------------------------------------

void __fastcall TRunForm::SupportsMenuItemClick(TObject *Sender)
{
   SupportPictureForm->Show ();
}
//---------------------------------------------------------------------------

void __fastcall TRunForm::ContourMenuItemClick(TObject *Sender)
{
    ContourPictureForm->Show ();
}
//---------------------------------------------------------------------------

void __fastcall TRunForm::ColorPlotMenuItemClick(TObject *Sender)
{
	ColorPictureForm->Show ();
}
//---------------------------------------------------------------------------

void __fastcall TRunForm::UpdateError(void)
{   char str [100];
    int i;

    sprintf (str, "%g", plate_err_vis_rms);
    ErrRMSVisEdit->Text = str;
    sprintf (str, "%g", plate_err_vis_p_v);
    ErrPVVisEdit->Text = str;
    sprintf (str, "%1.8g", plate_refocus_focal_length);
    RefocusFocalEdit->Text = str;

    if (calculate_zernike_flag)
    {   ZernikeListBox->Items->Clear ();
        for (i = 0; i < zernike_order; i++)
        {   sprintf (str, "Z%-3d           %20.12g", i + 1, zernike_coeff [i]);
            ZernikeListBox->Items->Add (str);
        }
	}

    UpdateWindow (Handle);
}
//---------------------------------------------------------------------------
void __fastcall TRunForm::UpdateZ88Error(void)
{   char str [100];
	int i;

	sprintf (str, "%g", z88_plot_err_vis_rms);
	ErrZ88RMSEdit->Text = str;
	sprintf (str, "%g", z88_plot_err_vis_p_v);
	ErrZ88PVEdit->Text = str;

	UpdateWindow (Handle);
}
//---------------------------------------------------------------------------
void __fastcall TRunForm::UpdatePics(void)
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
void __fastcall TRunForm::UpdateOptStatus(void)
{   char str [100];

    if (n_opt_evals == -1)
    {   RunForm->NumOptEdit->Text = "";
        RunForm->OptStepEdit->Text = "";
    }
    else
    {    sprintf (str, "%d", n_opt_evals);
        RunForm->NumOptEdit->Text = str;
        sprintf (str, "%lg", last_opt_step);
        RunForm->OptStepEdit->Text = str;
    }
    UpdateWindow (Handle);

    if (UpdateDisplay)
    {   RunForm->ExecThread->UpdatePicsSync ();
    }
}

//---------------------------------------------------------------------------

void UpdateRunOptStatus (int n_ev, double rel_step)
{   copy_plot_data ();
	RunForm->n_opt_evals = n_ev;
    RunForm->last_opt_step = rel_step;
    RunForm->ExecThread->UpdateOptStatusSync ();
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TRunForm::ExecFinished (void)
{   StartButton->Enabled = true;
    PauseButton->Enabled = false;
    AbortButton->Enabled = false;
    CellEditForm->FileOpenItem->Enabled = true;
    CellEditForm->FileSaveItem->Enabled = true;
    CellEditForm->FileSaveAsItem->Enabled = true;

	CellEditForm->PlopRunningFlag = false;
	RunZ88Button->Enabled = z88_input_files_valid;



    if (HaveOutput)
    {   fclose (output_file);
        HaveOutput = false;
        output_file = stdout;
    }
    RunFinishedForm->ShowModal ();

}
//---------------------------------------------------------------------------


void __fastcall TRunForm::StartButtonClick(TObject *Sender)
{   int MbResult;

	RunZ88Button->Enabled = false;
	z88_input_files_valid = 0;
	
    DebugMsg ("start run\n");
    if (CellEditForm->CellPageControl->ActivePage ==
        CellEditForm->TextTabSheet)
    {   warn_msg ("Can't run Plop while edit as text is active\n"
        "Please select another page");
        return;
    }

    StartButton->Enabled = false;

    please_stop_plop = 0;
    
    ErrRMSVisEdit->Text = "";
	ErrPVVisEdit->Text = "";
	ErrZ88PVEdit->Text = "";
	ErrZ88RMSEdit->Text = "";
    OptStepEdit->Text = "";
    NumOptEdit->Text = "";
    RefocusFocalEdit->Text = "";

    MonteNumDoneEdit->Text = "";
    MonteAvgEdit->Text = "";
    MonteMaxEdit->Text = "";

	swscanf (MonteNumEdit->Text.c_str (), L" %d", &n_monte_tests);

   (void) UpdateWindow (Handle); 

	if (UseBasisCheckBox->Checked && CellEditForm->NumBasis == 0)
	{	CellEditForm->AutoBasisButtonClick (Sender);
	}

    use_p_v_error = PVCheckBox->Checked;
    refocus_flag =  RefocusCheckBox->Checked;
	refocus_xyr_flag =  RefocusXYRCheckBox->Checked;
	generate_z88_input_flag = GenZ88InputCheckBox->Checked;

	if (CellEditForm->CopyToPlop (false))
	{   (void) Application->MessageBox (L"Unable to execute because of errors",
			 L"Plop Error", MB_OK + MB_ICONERROR);
        StartButton->Enabled = true;
        return;
    }
	if (generate_z88_input_flag && (n_mesh_depth < 2 || n_mesh_depth > max_mesh_depth)) {
		(void) Application->MessageBox (L"Bad z88 mesh depth", L"Plop Error", MB_OK + MB_ICONERROR);
        StartButton->Enabled = true;
		return;
	}

	calculate_zernike_flag = ZernikeCheckBox->Checked;
	if (calculate_zernike_flag)
	{   if (swscanf (ZernikeOrderEdit->Text.c_str (), L" %d", &zernike_order) != 1)
		{   (void) Application->MessageBox (L"Missing the Zernike order",
					L"Plop Error", MB_OK + MB_ICONERROR);
			StartButton->Enabled = true;
			 return;
		}
		if (zernike_order > max_refocus_distortion_order)
			zernike_order = max_refocus_distortion_order;
	}
	trace_opt = OptTraceCheckBox->Checked;
	grid_gen_using_basis = UseBasisCheckBox->Checked;

	if (SaveOutputCheckBox->Checked && SaveOutputComboBox->Text != "")
	{   output_file = fopen (AnsiOf (SaveOutputComboBox->Text.c_str ()), "wt");
		if (SaveOutputComboBox->Items->Count == 0 ||
			SaveOutputComboBox->Items->Strings [0] !=
			 SaveOutputComboBox->Text)
		{   SaveOutputComboBox->Items->Insert (0, SaveOutputComboBox->Text);
		}
		HaveOutput = true;
	}
	else
	{   output_file = stdout;
		HaveOutput = false;
	}

	SolverProgressBar->Position = 0;

	ExecThread = new PlopExec (true);
	ExecThread->Priority = tpIdle;
	ExecThread->FreeOnTerminate = true;
	ExecThread->Resume();

	PauseButton->Enabled = true;
	AbortButton->Enabled = true;
	CellEditForm->FileOpenItem->Enabled = false;
	CellEditForm->FileSaveItem->Enabled = false;
	CellEditForm->FileSaveAsItem->Enabled = false;

	CellEditForm->PlopRunningFlag = true;

}
//---------------------------------------------------------------------------

void __fastcall TRunForm::UpdateCellCheckBoxClick(TObject *Sender)
{
	UpdateDisplay = UpdateCellCheckBox->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TRunForm::SaveOutputButtonClick(TObject *Sender)
{
	if (TraceOpenDialog->Execute ())
	{   SaveOutputComboBox->Items->Insert (0, TraceOpenDialog->FileName);
		SaveOutputComboBox->ItemIndex = 0;
        SaveOutputCheckBox->Checked = true;
    }
}
//---------------------------------------------------------------------------


void __fastcall TRunForm::PauseButtonClick(TObject *Sender)
{
    // make sure we don't deadlock
    LockPlopData (10);

    ExecThread->Suspend ();
    ResumeButton->Enabled = true;
    PauseButton->Enabled = false;
    AbortButton->Enabled = false;

    UnlockPlopData ();
}
//---------------------------------------------------------------------------

void __fastcall TRunForm::ResumeButtonClick(TObject *Sender)
{
    ExecThread->Resume ();
    ResumeButton->Enabled = false;
    PauseButton->Enabled = true;
    AbortButton->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TRunForm::FormCreate(TObject *Sender)
{
	// Set styles for each of the graphics

	MeshPictureForm->PictureStyle = PicStyleMesh;
	SupportPictureForm->PictureStyle = PicStyleSupports;
	ColorPictureForm->PictureStyle = PicStyleColor;
	ContourPictureForm->PictureStyle = PicStyleContour;
	CellPartPictureForm->PictureStyle = PicStyleParts;
	QuadPictureForm->PictureStyle = PicStyleQuads;
	Z88ColorPictureForm->PictureStyle = PicStyleZ88Color;

	OptionsPageControl->ActivePage = RunOptionsTabSheet;
	UpdateDisplay = UpdateCellCheckBox->Checked;
	RefocusXYRCheckBox->Enabled = RefocusCheckBox->Checked;


	MeshPictureForm->SetPalette (&bw_cmap);
	SupportPictureForm->SetPalette (&bw_cmap);
	ColorPictureForm->SetPalette (&color_cmap);
	ContourPictureForm->SetPalette (&contour_cmap);
	CellPartPictureForm->SetPalette (&color_cmap);
	PartDimensionForm->SetPalette (&color_cmap);
	QuadPictureForm->SetPalette (&bw_cmap);
	Z88ColorPictureForm->SetPalette (&color_cmap);

	MeshPictureForm->ClearPic();
	SupportPictureForm->ClearPic();
	ColorPictureForm->ClearPic();
	ContourPictureForm->ClearPic();
	CellPartPictureForm->ClearPic();
	PartDimensionForm->ClearPic();
	QuadPictureForm->ClearPic();
	Z88ColorPictureForm->ClearPic();


}
//---------------------------------------------------------------------------
void __fastcall TRunForm::UpdateStatus (int n)
{   SolverProgressBar->Position = n;
}

//---------------------------------------------------------------------------

void __fastcall TRunForm::AbortButtonClick(TObject *Sender)
{
	 if (Application->MessageBox (L"Terminate Plop execution?",
             L"Plop Question", MB_OKCANCEL) == ID_OK)
        please_stop_plop = 1;
}
//---------------------------------------------------------------------------
void __fastcall TRunForm::UpdateMonteSync (void)
{   char str [100];

    sprintf (str, "%d", n_montes);
	MonteNumDoneEdit->Text = str;
    sprintf (str, "%lg", monte_avg_err);
    MonteAvgEdit->Text = str;
    sprintf (str, "%lg", monte_max_err);
    MonteMaxEdit->Text = str;
    UpdateWindow (Handle);

}

//---------------------------------------------------------------------------

void __fastcall TRunForm::UpdateMonte (int ntests, double avgerr, double maxerr)
{   n_montes = ntests;
    monte_avg_err = avgerr;
    monte_max_err = maxerr;
    ExecThread->UpdateMonteSync ();
}

//---------------------------------------------------------------------------

void  UpdateMonteDisplay (int ntests, double avgerr, double maxerr)
{   RunForm->UpdateMonte (ntests, avgerr, maxerr);
}

//---------------------------------------------------------------------------

void __fastcall TRunForm::RefocusCheckBoxClick(TObject *Sender)
{
    RefocusXYRCheckBox->Enabled = RefocusCheckBox->Checked;    
}


//---------------------------------------------------------------------------


void __fastcall TRunForm::SaveButtonClick(TObject *Sender)
{
    if (ZernikeOpenDialog->Execute ())
    {   ZernikeListBox->Items->SaveToFile (ZernikeOpenDialog->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TRunForm::CellPartsMenuItemClick(TObject *Sender)
{
    CellPartPictureForm->Show ();
    
}
//---------------------------------------------------------------------------


void __fastcall TRunForm::DimensionsMenuItemClick(TObject *Sender)
{
    PartDimensionForm->Show ();
}
//---------------------------------------------------------------------------


void __fastcall TRunForm::QuadsMenuItemClick(TObject *Sender)
{
	QuadPictureForm->Show ();	
}
//---------------------------------------------------------------------------


void __fastcall TRunForm::RunZ88ButtonClick(TObject *Sender)
{   int ret;
	char *str;
    char tmpstr [1000];
    char envstr [1000];
    int strpos;


    strcpy (tmpstr, CellEditForm->PlopLoc.c_str ());
    strcpy (tmpstr + strlen (tmpstr), z88i1_bin_name);
	DebugMsg ("z88i1bin = ");
    DebugMsg (tmpstr);
    DebugMsg ("\n");

    sprintf (envstr, "PLOPDIR=%s", CellEditForm->PlopLoc.c_str ());
    putenv (envstr);

	ret = spawnl (P_WAIT, tmpstr, tmpstr, NULL);
	if (ret != 0) {
		Application->MessageBox (L"Execute z88i1plop failed", L"Z88 Run Error", MB_OK + MB_ICONERROR);
		return;
	}

    strcpy (tmpstr, CellEditForm->PlopLoc.c_str ());
    strcpy (tmpstr + strlen (tmpstr), z88i2_bin_name);
	ret = spawnl (P_WAIT, tmpstr, tmpstr, NULL);
	if (ret != 0) {
		Application->MessageBox (L"Execute z88i2plop failed", L"Z88 Run Error", MB_OK + MB_ICONERROR);
		return;
	}
	load_z88_deflection_data (n_mesh_depth);
	UpdateZ88Error ();
    Z88ColorPictureForm->SetNewPicAvail ();
}
//---------------------------------------------------------------------------

void __fastcall TRunForm::Z88ColorMenuItemClick(TObject *Sender)
{
	Z88ColorPictureForm->Show ();

}

