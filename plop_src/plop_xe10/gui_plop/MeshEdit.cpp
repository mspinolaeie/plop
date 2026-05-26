//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MeshEdit.h"
#include <stdlib.h>
#include <shellapi.h>
#include "About.h"
#include "AutoCell.h"
#include "Run.h"
#include <stdio.h>
#include <string.h>
#include "ColorPicture.h"
#include "MeshPicture.h"
#include "ContourPicture.h"
#include "SupportPicture.h"
#include "CellPartPicture.h"
#include "PartDimension.h"


#include "plate_global.h"
#include <locale.h>
#include "QuadPicture.h"
#include "Z88ColorPicture.h"
#include "WhatsNew.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define my_max(x,y) ((x)>(y)?(x):(y))
#define my_min(x,y) ((x)<(y)?(x):(y))


TCellEditForm *CellEditForm;

extern LPTSTR GuiPlopArgsT;

extern int check_part_descrs (void);
extern void DebugMsg (const char *);
wchar_t* __fastcall UnicodeOf(const char* c);
char* __fastcall AnsiOf(wchar_t* w);
wchar_t plop_comment_file_buff_w [max_comments_len];
wchar_t plop_text_file_buff_w [max_plop_file_len];

//---------------------------------------------------------------------------
const char *material_names [] = {
    "Pyrex 7740",
    "Zerodur",
	"Plate Glass",
    "Fused Silica",
    "Duran 50",
    ""
    };

double material_density [] = {
    2.23e-6,
    2.48e-6,
    2.45e-6,
    2.22e-6,
    2.23e-6,
    0};

double material_modulus [] = {
    6400,
    9100,
    6000,
    7400,
    6300,
    0};

double material_poisson [] = {
    0.2,
    0.24,
    0.22,
    0.17,
    0.2,
    0};

char CurrentVersion [] = "3.0.6";

//---------------------------------------------------------------------------
void err_msg (const char *s)
{   wchar_t *sw;

	sw = UnicodeOf (s);
	(void) Application->MessageBox (sw, L"Plop Error",
             MB_OK + MB_ICONERROR);
}
//---------------------------------------------------------------------------
// show a message and return true if user chose OK

bool err_can_msg (const char *s, bool allow_cancel)
{   int r;
	wchar_t *sw;

	sw = UnicodeOf (s);
	r = Application->MessageBox (sw, L"Plop Error",
             allow_cancel ? MB_OKCANCEL + MB_ICONERROR : MB_OK + MB_ICONERROR);
    if (r == ID_OK)
        return true;
    else
        return false;
}
//---------------------------------------------------------------------------
void warn_msg (const char *s)
{   wchar_t *sw;

	sw = UnicodeOf (s);

	(void) Application->MessageBox (sw, L"Plop Warning",
             MB_OK + MB_ICONEXCLAMATION);
}


//---------------------------------------------------------------------------

void prompt_exit (void)
{   throw PlopException (0);
}

//---------------------------------------------------------------------------
/* validate that larger than plop_max_xxxx in global.h */

#define STR_CONV_BUF_SIZE 30000 // the largest string you may have to convert. depends on your project


wchar_t* __fastcall UnicodeOf(const char* c)
{
		static wchar_t w[STR_CONV_BUF_SIZE];
		memset(w,0,sizeof(w));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, c, strlen(c), w, STR_CONV_BUF_SIZE);
		return(w);
}
//---------------------------------------------------------------------------
char* __fastcall AnsiOf(wchar_t* w)
{
		static char c[STR_CONV_BUF_SIZE];
		memset(c, 0, sizeof(c));
		WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, w, wcslen(w), c, STR_CONV_BUF_SIZE, NULL, NULL);
		return(c);
}
//---------------------------------------------------------------------------

__fastcall TCellEditForm::TCellEditForm(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------

char * __fastcall TCellEditForm::GetCompileDate (void) {
	return compile_date;
}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::AutoCellButtonClick(TObject *Sender)
{    AutoCellForm->Show ();
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::FileOpenItemClick(TObject *Sender)
{   int MbResult;
    int ifilenum;
    int separator_num;
    int i;

    if (FileIsChanged)
	{   MbResult = Application->MessageBox (L"Save file before loading new file?", L"Plop Save",
            MB_YESNOCANCEL + MB_ICONEXCLAMATION);
        if (MbResult == ID_CANCEL)
            return;
        else if (MbResult == ID_YES)
            FileSaveItemClick (Sender);
    }
    separator_num = FileItems->IndexOf (FileSeparatorItem);
    if (Sender == FileOpenItem)
    {   if (OpenDialog1->Execute())
        {   // in case set to editastext page, which will not automatically load
            CellPageControl->ActivePage = MirrorTabSheet;
            GrOpenFile = OpenDialog1->FileName;
            ifilenum = -1;
        }
        else
            return;
    }
    else
    {   ifilenum = FileItems->IndexOf ((TMenuItem *) Sender) - separator_num - 1;
    }
    try
    {   if (ifilenum < 0)
        {   if (NumFileNameStrings == MaxFileStrings)
            {   ifilenum = MaxFileStrings - 1;
                FileNameStrings->Strings [ifilenum] = GrOpenFile;
            }
            else
            {   if (NumFileNameStrings == 0)
                {   SeparatorItem = new TMenuItem (FileItems);
                    SeparatorItem->Caption = '-';
                    FileItems->Insert (separator_num + 1, SeparatorItem);
                }
                FileItems->Insert (separator_num + 1 + NumFileNameStrings,
                    FileNameItems [NumFileNameStrings]);
                NumFileNameStrings++;
            }
        }
        if (ifilenum >= 0)
        {   GrOpenFile = FileNameStrings->Strings [ifilenum];
            FileNameStrings->Delete (ifilenum);
        }
		FileNameStrings->Insert (0, GrOpenFile);
        for (i = 0; i < NumFileNameStrings; i++)
        {   FileNameItems [i]->Caption = "&" + IntToStr (i + 1) + " " +
                    FileNameStrings->Strings [i];
        }

        read_info (GrOpenFile.c_str ());
        LoadFromPlop ();
        CellEditScrollBarChange (CellEditScrollBar);
        CellPartScrollBarResize (PartNumParts, Sender);
        PartDimensionForm->PartNumScrollBarChange (Sender);
        FileIsChanged = false;
    }
    catch (PlopException p)
    {   err_msg ("Unable to load the file.");
    }
}
//---------------------------------------------------------------------------


void __fastcall TCellEditForm::RunPlopItemClick(TObject *Sender)
{
    RunForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::FileSaveAsItemClick(TObject *Sender)
{
    if(SaveDialog1->Execute())
    {   GrOpenFile = SaveDialog1->FileName;
		CopyToPlop (true);
        write_info (GrOpenFile.c_str (), 0, 1);
        FileIsChanged = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::FileSaveItemClick(TObject *Sender)
{
    if (GrOpenFile == "")
        FileSaveAsItemClick (Sender);
    else
    {   CopyToPlop (true);
        write_info (GrOpenFile.c_str (), 0, 1);
        FileIsChanged = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::GrHasChanged(TObject *Sender)
{   FileIsChanged = true;
}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::HelpAboutItemClick(TObject *Sender)
{
    AboutBox->Show();
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::ProcessMessage (TMsg &Message, bool &handled)
{   if (Message.message == WM_SYSCOMMAND && Message.wParam == SC_SCREENSAVE)
        handled = true;
    else
        handled = false;
}

//---------------------------------------------------------------------------


void __fastcall TCellEditForm::VarScrollBarChange (TObject *Sender)
{   int i;
    int n;
    NumEditState s;

    n = VarScrollBar->Position;
    for (i = 0; i < MeshEditNumVarScroll && i + n < NumVarEdit; i++)
    {   VarScrollNumEdit [i]->MyState = NULL;
        VarScrollNumEdit [i]->NumEditLoad (&VarEdit [n + i]);
        VarScrollNumEdit [i]->MyState = &VarEdit [n + i];

        VarScrollNameEdit [i]->MyString = NULL;
        VarScrollNameEdit [i]->Text = VarNames [n + i];
        VarScrollNameEdit [i]->MyString = &(VarNames [n + i]);
    }

}
//---------------------------------------------------------------------------
void __fastcall TCellEditForm::VarScrollBarResize (int NewNumVar)
{   int i;

    NumVarEdit = NewNumVar;
	VarScrollBar->Max = my_max (NumVarEdit - MeshEditNumVarScroll, 0);
    for (i = 0; i < MeshEditNumVarScroll; i++)
    {   VarScrollNumEdit [i]->MyState = NULL;
        VarScrollNameEdit [i]->MyString = NULL;
        if (i < NumVarEdit)
        {   VarScrollNumEdit [i]->Visible = true;
            VarScrollNameEdit [i]->Visible = true;
            VarScrollNameLabels [i]->Visible = true;
        }
        else
        {   VarScrollNumEdit [i]->Visible = false;
            VarScrollNameEdit [i]->Visible = false;
            VarScrollNameLabels [i]->Visible = false;
        }
    }
	VarScrollBarChange (VarScrollBar);
}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::CellEditScrollBarChange(TObject *Sender)
{   int i;
    int n;
    NumEditState s;
    char str [100];

    n = CellEditScrollBar->Position;
    for (i = 0; i < MeshEditNumMeshScroll; i++)
    {   sprintf (str, "Support Ring %d", i + n + 1);
        CellScrollGroupBoxes [i]->Caption = str;

        CellNumSupportEdits [i]->MyString = NULL;
        CellNumSupportEdits [i]->Text = CellNumSupportStrings [i + n];
        CellNumSupportEdits [i]->MyString = &(CellNumSupportStrings [i + n]);

        SupportRadiiNumEdit [i]->NumEditLoad (&SupportRadiiState [n + i]);
        SupportRadiiNumEdit [i]->MyState = &SupportRadiiState [n + i];
        if (VarAngleCheckBox->Checked)
        {   SupportAngleNumEdit [i]->NumEditLoad (&SupportAngleState [n + i]);
            SupportAngleNumEdit [i]->MyState = &SupportAngleState [n + i];
        }
        if (EqualForceCheckBox->Checked)
        {   SupportRelForceNumEdit [i]->NumEditLoad (&SupportRelForceState [n + i]);
            SupportRelForceNumEdit [i]->MyState = &SupportRelForceState [n + i];
        }

    }
    NumSupportRingChanged = false;

}

//---------------------------------------------------------------------------

// clear new cells and adjust scroll; to avoid, set NumSupportRing before calling

void __fastcall TCellEditForm::CellEditScrollBarResize (int NewNumRing)
{   int i;
    char str [100];

    for (i = NumSupportRing; i < NewNumRing; i++)
    {   SupportRadiiState [i].NEValue = "";
        SupportRadiiState [i].NEFrom = "";
        SupportRadiiState [i].NETo = "";
        SupportRadiiState [i].NEBy = "";
        SupportRadiiState [i].NEMode = NumEditFixed;

        SupportAngleState [i].NEValue = "";
        SupportAngleState [i].NEFrom = "";
        SupportAngleState [i].NETo = "";
        SupportAngleState [i].NEBy = "";
        SupportAngleState [i].NEMode = NumEditFixed;

        SupportRelForceState [i].NEValue = "";
        SupportRelForceState [i].NEFrom = "";
        SupportRelForceState [i].NETo = "";
        SupportRelForceState [i].NEBy = "";
        SupportRelForceState [i].NEMode = NumEditFixed;
    }
    NumSupportRing = NewNumRing;
    NumSupportRingChanged = false;
    sprintf (str, "%d", NewNumRing);
    NumSupportRingEdit->Text = str;

	CellEditScrollBar->Max = my_max (NumSupportRing - MeshEditNumMeshScroll, 0);
    for (i = 0; i < MeshEditNumMeshScroll; i++)
    {   if (i < NumSupportRing)
            CellScrollGroupBoxes [i]->Visible = true;
        else
            CellScrollGroupBoxes [i]->Visible = false;
    }
    CellEditScrollBarChange (CellEditScrollBar);
    FileIsChanged = true;
}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::AddToPlopMap (const char *pname, NumEdit *ANumEdit,
    int NumToMap, NumEditState *ANumEditState,
    TEdit *AEdit, int ARadioIndex, TRadioGroup *ARadioGroup)
{   int i;

    i = parm_name_index (pname);
    PlopMap [i].MyNumEdit = ANumEdit;
    PlopMap [i].MyNumEditState = ANumEditState;
    PlopMap [i].MyEdit = AEdit;
    PlopMap [i].RadioIndex = ARadioIndex;
    PlopMap [i].MyRadioGroup = ARadioGroup;
}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::LoadNumEditStates (
    int NumValues,
    int NumEditMode,
    int *NumEditWhich,
    int *NumEditIndex,
    int *NumEditIsVar,
    double *NumEditFrom,
    double *NumEditTo,
    int *NumEditBy,
    int *NumEditSetNum,
    ScanSetVals *NumEditSetVals)
{   NumEditState *ThisNumState;
    NumEdit *ThisNumEdit;
    char str [max_line_len];
    char word [wordlen];
    int i;
    int j;

    for (i = 0; i < NumValues; i++)
    {   if (NumEditIsVar [i])
        {   ThisNumState = &VarEdit [NumEditWhich [i]];
            ThisNumEdit = NULL;
        }
        else
        {   ThisNumState = &PlopMap [NumEditWhich [i]].MyNumEditState
                 [NumEditIndex [i]];
            if (PlopMap [NumEditWhich [i]].MyNumEdit != NULL)
                ThisNumEdit = &PlopMap [NumEditWhich [i]].MyNumEdit
                    [NumEditIndex [i]];
            else
                ThisNumEdit = NULL;
        }
        ThisNumState->NEMode = NumEditMode;
        if (NumEditFrom != NULL)
        {   sprintf (str, "%lg", NumEditFrom [i]);
            ThisNumState->NEFrom = str;
        }
        if (NumEditTo != NULL)
        {   sprintf (str, "%lg", NumEditTo [i]);
            ThisNumState->NETo = str;
        }
        if (NumEditBy != NULL)
        {   sprintf (str, "%d", NumEditBy [i]);
            ThisNumState->NEBy = str;
        }
        if (NumEditSetNum != NULL)
        {   str [0] = '\0';
            for (j = 0; j < NumEditSetNum [i]; j++)
            {   sprintf (word, " %lg", NumEditSetVals [i] [j]);
                strcat (str, word);
            }
            ThisNumState->NEFrom = str;
        }
        if (ThisNumEdit != NULL)
        {   ThisNumEdit->NumEditLoad (ThisNumState);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::ClearState (void)
{   int i;
    int j;

    for (i = 0; parm_list [i].name [0] != '\0'; i++)
    {   for (j = 0; j < parm_list [i].max_num; j++)
        {   if (PlopMap [i].MyNumEditState != NULL)
            {   PlopMap [i].MyNumEditState [j].Clear ();
            }
        }
        if (PlopMap [i].MyNumEdit != NULL)
            PlopMap [i].MyNumEdit->NumEditLoad (PlopMap [i].MyNumEditState);
    }

    for (i = 0; i < max_variables; i++)
	{   VarEdit [i].Clear ();
        VarNames [i] = "";
    }

    for (i = 0; i < max_mesh_radii; i++)
    {   SupportRadiiState [i].Clear ();
        SupportAngleState [i].Clear ();
        SupportRelForceState [i].Clear ();
        CellNumSupportStrings [i] = "";
    }

    for (i = 0; i < max_basis_size; i++)
    {   BasisNumEdits [i]->Text = "";
        BasisRingEdits [i]->Text = "";
    }

    NumSupportRingEdit->Text = "";
	NumMeshRingEdit->Text = "";
	NumMeshDepthEdit->Text = "";
	NumBasisEdit->Text = "";

    VarAngleCheckBox->Checked = true;
    EqualForceCheckBox->Checked = false;

    VarPaste->Enabled = false;
    MeshPaste->Enabled = false;

    FocalRadioGroup->ItemIndex = -1;
    ObsRadioGroup->ItemIndex = -1;
    HoleRadioGroup->ItemIndex = -1;
}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::LoadFromPlop (void)
{   int i;
    int j;
    char str [100];

    ClearState ();
    for (i = 0; parm_list [i].name [0] != '\0'; i++)
    {   for (j = 0; j < *parm_list [i].num_found; j++)
        {   if (PlopMap [i].MyNumEditState != NULL)
            {   if (parm_list [i].bound_to_var [j] >= 0)
                {   PlopMap [i].MyNumEditState [j].NEValue =
                        var_table [parm_list [i].bound_to_var [j]].name;
                }
                else if (parm_list [i].type_flag == parm_type_double)
                {   sprintf (str, "%-15.7g", parm_list [i].dptr [j]);
                    PlopMap [i].MyNumEditState [j].NEValue = str;
                }
                else
                {   sprintf (str, "%d", parm_list [i].iptr [j]);
                    PlopMap [i].MyNumEditState [j].NEValue = str;
                }
            }
        }

        /* if there is a NumEdit then it must be the first NumEditState */
        
        if (PlopMap [i].MyNumEdit != NULL && *parm_list [i].num_found > 0)
            PlopMap [i].MyNumEdit->NumEditLoad (PlopMap [i].MyNumEditState);
        if (PlopMap [i].MyRadioGroup != NULL && *parm_list [i].num_found > 0)
            PlopMap [i].MyRadioGroup->ItemIndex = PlopMap [i].RadioIndex;
    }
	NumSupportRing = my_max (n_abs_support_radii, n_rel_support_radii);
	NumSupportRing = my_min (NumSupportRing, n_num_support_rings);

    for (i = 0; i < NumSupportRing; i++)
    {   sprintf (str, "%d", num_support [i]);
        CellNumSupportStrings [i] = str;
    }

    sprintf (str, "%d", NumSupportRing);
    NumSupportRingEdit->Text = str;

	NumMeshRing = n_mesh_rings;
	sprintf (str, "%d", NumMeshRing);
	NumMeshRingEdit->Text = str;

	NumMeshDepth = n_mesh_depth;
	sprintf (str, "%d", NumMeshDepth);
	NumMeshDepthEdit->Text = str;

	for (i = 0; i < n_variables; i++)
    {   VarNames [i] = var_table [i].name;
        var_def_str (var_table + i, str);
        VarEdit [i].NEValue = str;
    }
    LoadNumEditStates (n_optimize_vars, NumEditOpt,
        opt_var_which, opt_var_index, opt_var_is_var,
        opt_var_step, NULL, NULL, NULL, NULL);

    LoadNumEditStates (n_scan_vars, NumEditScanVar,
        scan_var_which, scan_var_index, scan_var_is_var,
        scan_var_start, scan_var_end, scan_var_nsteps, NULL, NULL);

    LoadNumEditStates (n_scan_set_vars, NumEditScanSet,
        scan_set_which, scan_set_index, scan_set_is_var,
        NULL, NULL, NULL, scan_set_n_values, scan_set_values);

    LoadNumEditStates (n_monte_vars, NumEditMonte,
        monte_var_which, monte_var_index, monte_var_is_var,
        monte_var_delta, NULL, NULL, NULL, NULL);

    VarScrollBarResize (n_variables);
    CellEditScrollBarResize (NumSupportRing);

	NumBasis = my_min (n_basis_ring_found, n_basis_min_found);
    for (i = 0; i < NumBasis; i++)
    {   sprintf (str, "%d", basis_ring [i]);
        BasisNumEdits [i]->Text = str;
        sprintf (str, "%d", basis_min [i]);
        BasisRingEdits [i]->Text = str;
    }
    sprintf (str, "%d", NumBasis);
    NumBasisEdit->Text = str;
    NumBasisUpdateButtonClick (NumBasisUpdateButton);

	CommentsMemo->SetTextBuf (UnicodeOf (plop_comment_file_buff));

    VarAngleCheckBox->Checked = (n_support_angle > 0);
    VarAngleCheckBoxClick (this);
    EqualForceCheckBox->Checked = (n_rel_force > 0);
    EqualForceCheckBoxClick (this);

    ActiveSupportId = -1;
    ActiveVarId = -1;

    PartScrollLastPosition = -1;
    PartNumParts = n_parts;
    sprintf (str, "%d", PartNumParts);
    PartNumEdit->Text = str;
    for (i = 0; i < PartNumParts; i++)
    {   PartType [i] = part_type [i];
        sprintf (str, "%d", part_quantity [i]);
        PartQuantityText [i] = str;
        for (j = 0; j < part_type_num_corners [PartType [i]]; j++)
        {   PartPointType [i] [j] = part_point_type [i] [j];
            sprintf (str, "%d", part_ring_num [i] [j] + 1);
            PartPointRingNumText [i] [j] = str;
            sprintf (str, "%d", part_point_num [i] [j] + 1);
            PartPointPointNumText [i] [j] = str;
        }
    }
}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::UpdateFromOpt (void)
{   int i;
    char str [100];

    for (i = 0; i < n_optimize_vars; i++)
    {   if (opt_var_is_var [i])
        {   sprintf (str, "%lg", var_table [opt_var_which [i]].value);
            VarEdit [opt_var_which [i]].NEValue = str;
        }
        else
        {   sprintf (str, "%lg", parm_list [opt_var_which [i]].dptr [opt_var_index [i]]);
           PlopMap [opt_var_which [i]].MyNumEditState [opt_var_index [i]].NEValue = str;
        }
    }

    VarScrollBarResize (NumVarEdit);
    CellEditScrollBarResize (NumSupportRing);
    UpdateWindow (Handle);

    RunForm->UpdateError ();

}

//---------------------------------------------------------------------------

/* Parse the ANumEditState and copy it to Plop, handling
 * optimizations and scanning, etc. If IsVar is true, the NumEditState refers
 * to a variable, otherwise a parm. Which specifies which var or parm,
 * and index indexes into the vector if it is a vector.
 * If it is variable, parse it for a variable definition.
 * allow_err_ptr is a pointer to a bool indicating if should allow errors or abort.
 * If true, it will be set fo false when the user chooses cancel.
 */

int __fastcall TCellEditForm::StoreNumEditState (
    NumEditState *ANumEditState,
    int IsVar,
    int Which,
    int Index,
    char *err_id,
    bool *allow_err_ptr)
{   char str [max_line_len];
    char err_str [max_line_len];
    int i;
    int k;
    double d;
    double dfrom;
    double dto;
    char words [maxwords] [wordlen];
    int n_words;
    int nsteps;

    int err_found;

    err_found = 0;
    if (sscanf (ANumEditState->NEValue.c_str (), " %s", str) != 1 &&
        ANumEditState->NEMode != NumEditScanVar &&
        ANumEditState->NEMode != NumEditScanSet)
    {   sprintf (err_str, "Can\'t find a value in %s", err_id);
        *allow_err_ptr &= err_can_msg (err_str, *allow_err_ptr);
        err_found = 1;
    }
    else
    {   if (IsVar)
        {   parse_var_def_line (Which, ANumEditState->NEValue.c_str ());
        }
        else
        {   if (isalpha (str [0]))
			{   k = get_var (str, 0, 0, "");
                if (k < 0)
                {   sprintf (err_str, "No definition for variable %s in %s",
                        str, err_id);
                    *allow_err_ptr &= err_can_msg (err_str, *allow_err_ptr);
                    err_found = 1;
                }
                else
                {   parm_list [Which].bound_to_var [Index] = k;
                }
            }
            else
            {   parm_list [Which].bound_to_var [Index] = -1;
                if (sscanf (str, "%lg", &d) != 1)
                {   sprintf (err_str, "No value entered in %s", err_id);
                    *allow_err_ptr &= err_can_msg (err_str, *allow_err_ptr);
                    err_found = 1;
                    d = 0;
				}
#ifdef DebugLocale
				sprintf (err_str, "parse value which %d index %d str %s value %g\n", Which, Index, str, d);
				DebugMsg (err_str);
#endif
				parm_list [Which].dptr [Index] = d;
            }
        }
    }
    if (!err_found)
    {   switch (ANumEditState->NEMode)
        {   case NumEditOpt:
                if (sscanf (ANumEditState->NEFrom.c_str (), " %lg", &dfrom) != 1)
                {   sprintf (err_str, "No step size entered in %s", err_id);
                    *allow_err_ptr &= err_can_msg (err_str, *allow_err_ptr);
                    err_found = 1;
                    dfrom = 1;
                }
                opt_var_which [n_optimize_vars] = Which;
                opt_var_index [n_optimize_vars] = Index;
                opt_var_is_var [n_optimize_vars] = IsVar;
                opt_var_step [n_optimize_vars] = dfrom;
                n_optimize_vars++;
                break;

            case NumEditMonte:
                if (sscanf (ANumEditState->NEFrom.c_str (), " %lg", &dfrom) != 1)
                {   sprintf (err_str, "No variation entered in %s", err_id);
                    *allow_err_ptr &= err_can_msg (err_str, *allow_err_ptr);
                    err_found = 1;
                    dfrom = 1;
                }
                monte_var_which [n_monte_vars] = Which;
                monte_var_index [n_monte_vars] = Index;
                monte_var_is_var [n_monte_vars] = IsVar;
                monte_var_delta [n_monte_vars] = dfrom;
                n_monte_vars++;
                break;

            case NumEditScanVar:
                if (sscanf (ANumEditState->NEFrom.c_str (), " %lg", &dfrom) != 1)
                {   sprintf (err_str, "No from entered in %s", err_id);
                    *allow_err_ptr &= err_can_msg (err_str, *allow_err_ptr);
                    err_found = 1;
                    dfrom = 1;
                }
                if (sscanf (ANumEditState->NETo.c_str (), " %lg", &dto) != 1)
                {   sprintf (err_str, "No to entered in %s", err_id);
                    *allow_err_ptr &= err_can_msg (err_str, *allow_err_ptr);
                    err_found = 1;
                    dto = 1;
                }
                if (sscanf (ANumEditState->NEBy.c_str (), " %d", &nsteps) != 1)
                {   sprintf (err_str, "No number of steps entered in %s", err_id);
                    *allow_err_ptr &= err_can_msg (err_str, *allow_err_ptr);
                    err_found = 1;
                    nsteps = 1;
                }

                scan_var_which [n_scan_vars] = Which;
                scan_var_index [n_scan_vars] = Index;
                scan_var_is_var [n_scan_vars] = IsVar;
                scan_var_start [n_scan_vars] = dfrom;
                scan_var_end [n_scan_vars] = dto;
                scan_var_nsteps [n_scan_vars] = nsteps;
                n_scan_vars++;
                break;

            case NumEditScanSet:
                getwords (ANumEditState->NEFrom.c_str (), words, &n_words, maxwords);
                scan_set_which [n_scan_set_vars] = Which;
                scan_set_index [n_scan_set_vars] = Index;
                scan_set_is_var [n_scan_set_vars] = IsVar;
                for (i = 0; i < n_words && (*allow_err_ptr || !err_found); i++)
                {   if (sscanf (words [i], " %lg", &dfrom) != 1)
                    {   sprintf (err_str, "Bad set of values entered in %s", err_id);
                        *allow_err_ptr &= err_can_msg (err_str, *allow_err_ptr);
                        err_found = 1;
                        dfrom = 0;
                    }
                    scan_set_values [n_scan_set_vars] [i] = dfrom;
                }
                scan_set_n_values [n_scan_set_vars] = n_words;
                n_scan_set_vars++;
                break;
        }
    }
    return err_found;
}

//---------------------------------------------------------------------------


// copy the gui data to plop's parms and opt/scans
// if we aren't going to run plop, i.e. just doing a edit as text
// don't particularily care about errors

// allow_err prevents abort on error

int __fastcall TCellEditForm::CopyToPlop (bool allow_err)
{   int i;
	int j;
    int jmax;
	int t;
    char str [100];
    char err_id_str [100];
	int err_found;
	double d_debug_locale;
	int i_debug_locale;

    err_found = 0;

#ifdef DebugLocale
	sprintf (str, "start_locale %s\n", start_locale);
	DebugMsg (str);
	sprintf (str, "run_locale %s\n", run_locale);
	DebugMsg (str);
	sprintf (str, "decimal separator %s\n", localeconv()->decimal_point);
	DebugMsg (str);
	sprintf (str, "test string 1 %g\n", 1.2345e-6);
	DebugMsg (str);
	sprintf (str, "%g", 1.2345e-6);
	sscanf (str, "%lg", &d_debug_locale);
	i_debug_locale = d_debug_locale * 1e12;
	sprintf (str, "test string 2 %d\n", i_debug_locale);
	DebugMsg (str);
	sprintf (str, "contents of density box %s\n", DensityNumEdit->NumEditValue->Text);
	DebugMsg (str);
#endif

    init_gr_info ();

    if (SupportRadioGroup->ItemIndex == 0)
    {   n_abs_support_radii = NumSupportRing;
        n_rel_support_radii = 0;
	}
    else if (SupportRadioGroup->ItemIndex == 1)
    {   n_rel_support_radii = NumSupportRing;
        n_abs_support_radii = 0;
    }
    else
    {   allow_err &= err_can_msg ("Check either relative or absolute radii for supports!", allow_err);
        SupportRadioGroup->Show ();
        err_found = 1;
    }
    if (err_found && !allow_err)
        return 1;

    warp_sphere_flag = WarpSphereCheckBox->Checked;    

    if (EqualForceCheckBox->Checked)
        n_rel_force = NumSupportRing;
    else
        n_rel_force = 0;

    if (VarAngleCheckBox->Checked)
        n_support_angle = NumSupportRing;
    else
        n_support_angle = 0;

    n_num_support_rings = NumSupportRing;
    
    n_basis_ring_found = NumBasis;
    n_basis_min_found = NumBasis;
	n_mesh_rings = NumMeshRing;
	n_mesh_depth = NumMeshDepth;

    /* copy variable definitions to Plop */

    n_variables = 0;
    for (i = 0; (allow_err ||!err_found) && i < NumVarEdit; i++)
    {   var_table [i].affects_basis = 0;
        if (sscanf (VarNames [i].c_str (), " %s", str) != 1)
        {   allow_err &= err_can_msg ("Variable name is empty!", allow_err);
            err_found = 1;
        }
        else if (get_var (str, 0, 0, "") >= 0)
        {   allow_err &= err_can_msg ("Duplicate variable name!", allow_err);
            err_found = 1;
        }
        else
        {   (void) get_var (str, 1, 0, "");
            sprintf (err_id_str, "variable %s", str);
            err_found |= StoreNumEditState (&VarEdit [i], 1, i, -1, err_id_str, &allow_err);
            if (err_found)
            {   VarScrollBar->Show ();
				VarScrollBar->Position = my_min (i, NumVarEdit - MeshEditNumVarScroll);
            }
        }
    }
    if (err_found && !allow_err)
        return 1;
	if (swscanf (NumMeshRingEdit->Text.c_str (), L"%d", &NumMeshRing) != 1 ||
		NumMeshRing <= 0 || NumMeshRing > max_mesh_radii)
	{   NumMeshRingEdit->Show ();
		NumMeshRingEdit->SetFocus ();
		NumMeshRingEdit->SelectAll ();
		allow_err &= err_can_msg ("Number of mesh rings does not contain a valid number!", allow_err);
		err_found = 1;
	}
	else
	{   n_mesh_rings = NumMeshRing;
		n_mesh_rings_found = 1;

	}
	if (err_found && !allow_err)
		return 1;
	if (swscanf (NumMeshDepthEdit->Text.c_str (), L"%d", &NumMeshDepth) == 1 &&
		(NumMeshDepth < 0 || NumMeshDepth > max_mesh_radii))
	{   NumMeshDepthEdit->Show ();
		NumMeshDepthEdit->SetFocus ();
		NumMeshDepthEdit->SelectAll ();
		allow_err &= err_can_msg ("Number of mesh depth does not contain a valid number!", allow_err);
		err_found = 1;
	}
	else
	{   n_mesh_depth = NumMeshDepth;
		n_mesh_depth_found = 1;

	}
	if (err_found && !allow_err)
		return 1;

	tilt_support_mode = OffAxisRadioGroup->ItemIndex;


	/* Copy number of supports in each ring to Plop */

    for (i = 0; i < n_num_support_rings && (allow_err ||!err_found); i++)
    {   if (sscanf (CellNumSupportStrings[i].c_str (), "%d", &t) != 1 ||
            t <= 0 || t > max_mesh_perim)
        {   CellEditScrollBar->Show ();
			CellEditScrollBar->Position = my_min (i, n_num_support_rings - MeshEditNumMeshScroll);
            allow_err &= err_can_msg ("Number of support rings does not contain a valid number!", allow_err);
            err_found = 1;
            CellNumSupportEdits [i - CellEditScrollBar->Position]->SetFocus ();
        }
        else
        {   num_support [i] = t;
        }
    }
    if (err_found && !allow_err)
        return 1;

    /* copy part data to Plop */

    CellPartsSaveCurrentItem ();
    n_parts = PartNumParts;
    for (i = 0; i < PartNumParts && (allow_err || !err_found); i++)
    {   part_type [i] = PartType [i];
        if (sscanf (PartQuantityText [i].c_str (), "%d", &(part_quantity [i])) != 1)
        {   allow_err &= err_can_msg ("Part quantity does not contain a valid number!\n", allow_err);
            CellPartScrollBar->Position = i;
            err_found = 1;
            if (!allow_err)
                return 1;
        }
        jmax = part_type_num_corners  [part_type [i]];
        for (j = 0; j < jmax; j++)
		{   part_point_type [i] [j] = PartPointType [i] [j];

			/* add in check that a part only refers to previously defined parts */

            if (sscanf (PartPointRingNumText [i] [j].c_str (), "%d", &(part_ring_num [i] [j])) != 1)
            {   allow_err &= err_can_msg ("Part ring number does not contain a valid number!\n", allow_err);
                err_found = 1;
                if (!allow_err)
                    return 1;
            }
            else
            {   part_ring_num [i] [j]--;        /* 0 based in grid_gen 1 based in gui */
            }

            if (sscanf (PartPointPointNumText [i] [j].c_str (), "%d", &(part_point_num [i] [j])) != 1)
            {   allow_err &= err_can_msg ("Part point number does not contain a valid number!\n", allow_err);
                err_found = 1;
                if (!allow_err)
                    return 1;
            }
            else
            {   part_point_num [i] [j]--;
            }
        }
    }
    err_found |= check_part_descrs ();
    if (!allow_err && err_found)
        return 1;

    /* Use Plop data map to copy all other data to Plop.
     * For vectors, the number of entries should already be copied.
     * For scalars, detect if any data is in the NumEdit.
     * Also verify that if data present, the RadioGroup has a valid value.
     */



    for (i = 0; parm_list [i].name [0] != '\0' && (allow_err ||!err_found); i++)
    {   if (parm_list [i].type_flag == parm_type_double)
        {   if (parm_list [i].max_num == 1)
                *parm_list [i].num_found = 0;
            /* If it is a scalar, and there is something in the NumEditState, then
             * set the num_found to 1.
             */
            if (parm_list [i].max_num == 1 &&
                sscanf (PlopMap [i].MyNumEditState [0].NEValue.c_str ()," %s", str) == 1 &&
                (PlopMap [i].MyRadioGroup == NULL ||
                 PlopMap [i].RadioIndex == PlopMap [i].MyRadioGroup->ItemIndex))
                *parm_list [i].num_found = 1;
            for (j = 0; j < *parm_list [i].num_found && (allow_err || !err_found); j++)
            {   if (parm_list [i].max_num > 1)
                    sprintf (err_id_str, "%s[%d]", parm_list [i].name, j);
                else
                    strcpy (err_id_str, parm_list [i].name);
                err_found |= StoreNumEditState (&PlopMap [i].MyNumEditState [j],
                    0, i, j, err_id_str, &allow_err);
                if (err_found && PlopMap [i].MyNumEdit != NULL)
                    PlopMap [i].MyNumEdit->NumEditValue->Show ();
            }
        }
    }

    for (i = 0; i < NumBasis && (allow_err || !err_found); i++)
	{   if (swscanf (BasisNumEdits [i]->Text.c_str (), L"%d", &t) != 1)
        {   allow_err &= err_can_msg ("Number of points on basis ring does not contain a valid number!", allow_err);
            BasisNumEdits [i]->Show ();
            BasisNumEdits [i]->SelectAll ();
            err_found = 1;
        }
        else
        {   basis_ring [i] = t;
        }
		if (swscanf (BasisRingEdits [i]->Text.c_str (), L"%d", &t) != 1 || t < 0)
        {   allow_err &= err_can_msg ("Basis min does not contain a valid number!", allow_err);
			BasisNumEdits [i]->Show ();
            BasisNumEdits [i]->SelectAll ();
            err_found = 1;
        }
        else
        {   basis_min [i] = t;
        }
    }


	if (generate_z88_input_flag && tilt_support_mode == tilt_support_mode_sling &&
			(!sling_included_angle_found || sling_included_angle == 0 || sling_included_angle > 180)) {
		allow_err  &= err_can_msg ("Missing or bad angle in the sling", allow_err);
	}


/* TODO */
//	(void) CommentsMemo->GetTextBuf (plop_comment_file_buff, max_comments_len);
	(void) CommentsMemo->GetTextBuf (plop_comment_file_buff_w, max_comments_len);
	strcpy (plop_comment_file_buff, AnsiOf (plop_comment_file_buff_w));
	plop_comment_len = strlen (plop_comment_file_buff);

    return err_found;
}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::NumBasisUpdate(int NewNumBasis)
{   int i;
    bool b;

    for (i = NumBasis; i < NewNumBasis; i++)
    {   BasisNumEdits [i]->Text = "";
        BasisRingEdits [i]->Text = "1";
    }
    NumBasis = NewNumBasis;
    for (i = 0; i < max_basis_size; i++)
    {   b = (i < NumBasis);
        BasisNumLabels [i]->Visible = b;
        BasisNumEdits [i]->Visible = b;
        BasisRingLabels [i]->Visible = b;
        BasisRingEdits [i]->Visible = b;
    }
    FileIsChanged = true;
    NumBasisChanged = false;

}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::NumBasisUpdateButtonClick(TObject *Sender)
{
    int t;
    int NewNumBasis;

	if (swscanf (NumBasisEdit->Text.c_str (), L"%d", &t) != 1 ||
        t < 0 || t > max_basis_size)
    {   err_msg ("Number of basis rings does not contain a valid number!");
    }
    else
    {   NewNumBasis = t;
        NumBasisUpdate (NewNumBasis);
        FileIsChanged = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::ExitPlopClick(TObject *Sender)
{
    Close ();
}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::EqualForceCheckBoxClick(TObject *Sender)
{   int i;

    for (i = 0; i < MeshEditNumMeshScroll; i++)
    {   SupportRelForceNumEdit [i]->Visible = EqualForceCheckBox->Checked;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::VarAngleCheckBoxClick(TObject *Sender)
{   int i;

    for (i = 0; i < MeshEditNumMeshScroll; i++)
    {   SupportAngleNumEdit [i]->Visible = VarAngleCheckBox->Checked;
    }
}
//---------------------------------------------------------------------------


void __fastcall TCellEditForm::VarInsertClick(TObject *Sender)
{   int i;

    if (ActiveVarId == -1)
    {   err_msg ("Select a variable to duplicate");
        return;
    }
    else if (NumVarEdit == max_variables)
    {   err_msg ("Can't add any more variables; already at maximum");
    }
    else
    {   for (i = NumVarEdit; i >= ActiveVarId + VarScrollBar->Position; i--)
        {   VarNames [i + 1] = VarNames [i];
            VarEdit [i + 1] = VarEdit [i];
        }
    }
    i = ActiveVarId + VarScrollBar->Position;
    VarNames [i] = "";
    VarEdit [i].NEValue = "";
    VarEdit [i].NEMode = NumEditFixed;
    VarEdit [i].NEFrom = "";
    VarEdit [i].NETo = "";
    VarEdit [i].NEBy = "";

    VarScrollBarResize (NumVarEdit + 1);
    FileIsChanged = true;


}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::VarDeleteClick(TObject *Sender)
{   int i;

    if (ActiveVarId == -1)
	{  warn_msg ("Select a variable to delete");
    }
    else if (NumVarEdit == 0)
    {  warn_msg ("Nothing to delete!");
    }
    else
    {   i = ActiveVarId + VarScrollBar->Position;
        CopyVarEdit = VarEdit [i];
        CopyVarName = VarNames [i];
        VarPaste->Enabled = true;
        for (i = ActiveVarId + VarScrollBar->Position; i < NumVarEdit - 1; i++)
        {   VarNames [i] = VarNames [i + 1];
            VarEdit [i] = VarEdit [i + 1];
        }
        VarScrollBarResize (NumVarEdit - 1);
        FileIsChanged = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::VarDuplicateClick(TObject *Sender)
{    int i;

    if (ActiveVarId == -1)
    {  warn_msg ("Select a variable to duplicate");
    }
    else if (NumVarEdit == max_variables)
    {  err_msg ("Can't add any more variables; already at maximum");
    }
    else
    {   for (i = NumVarEdit; i >= ActiveVarId + VarScrollBar->Position; i--)
        {   VarNames [i + 1] = VarNames [i];
            VarEdit [i + 1] = VarEdit [i];
        }
        VarScrollBarResize (NumVarEdit + 1);
        FileIsChanged = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::VarAddClick(TObject *Sender)
{   int i;

    if (NumVarEdit == max_variables)
    {  err_msg ("Can't add any more variables; already at maximum");
    }
    i = NumVarEdit;
    VarNames [i] = "";
	VarEdit [i].NEValue = "";
    VarEdit [i].NEMode = NumEditFixed;
    VarEdit [i].NEFrom = "";
    VarEdit [i].NETo = "";
    VarEdit [i].NEBy = "";

    VarScrollBarResize (NumVarEdit + 1);
    FileIsChanged = true;
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::VarCopyClick(TObject *Sender)
{   int i;

    if (ActiveVarId == -1)
    {  err_msg ("Select a variable to copy");
    }
    else
    {   i = ActiveVarId + VarScrollBar->Position;
        CopyVarEdit = VarEdit [i];
        CopyVarName = VarNames [i];
        VarPaste->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::VarPasteClick(TObject *Sender)
{  int i;

    if (ActiveVarId == -1)
    {  warn_msg ("Select a position to paste");
    }
    else if (NumVarEdit == max_variables)
    {  err_msg ("Can't add any more variables; already at maximum");
    }
    else
    {   for (i = NumVarEdit; i >= ActiveVarId + VarScrollBar->Position; i--)
        {   VarNames [i + 1] = VarNames [i];
            VarEdit [i + 1] = VarEdit [i];
        }
    }
    i = ActiveVarId + VarScrollBar->Position;
    VarNames [i] = CopyVarName;
    VarEdit [i] = CopyVarEdit;

    VarScrollBarResize (NumVarEdit + 1);
    FileIsChanged = true;
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::NumSupportButtonClick(TObject *Sender)
{   int NewNumRing;

	if (swscanf (NumSupportRingEdit->Text.c_str (), L"%d", &NewNumRing) != 1 ||
        NewNumRing < 0 || NewNumRing > max_support_radii)
    {   err_msg ("Number of support rings does not contain a valid number!");
        return;
    }
    CellEditScrollBarResize (NewNumRing);

}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::AutoBasisButtonClick(TObject *Sender)
{   int i;
    int n;
    int d;
    char str [10];


    for (i = 0; i < NumSupportRing; i++)
    {   if (sscanf (CellNumSupportStrings [i].c_str (), " %d", &d) != 1)
        {   err_msg ("Number of support points does not contain a valid number!");
            return;
        }
        else
        {   if (i == 0)
                n = d;
            else
                n = gcd (n, d);
        }
    }
    if (n >= n_deg_free)
    {   NumBasisEdit->Text = 1;
        NumBasisUpdate (1);
        sprintf (str, "%d", n);
        BasisNumEdits [0]->Text = n;
        BasisRingEdits [0]->Text = "0";
        FileIsChanged = true;
        NumBasisChanged = false;
    }
    else
    {   err_msg ("Automatic basis generation failed");
    }
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{   int MbResult;
    int i;
    AnsiString Key;

    if (FileIsChanged)
	{   MbResult = Application->MessageBox (L"Save file before exiting?", L"Plop Save",
            MB_YESNOCANCEL + MB_ICONEXCLAMATION);
        if (MbResult == ID_CANCEL)
            Action = caNone;
        else if (MbResult == ID_YES)
            FileSaveItemClick (Sender);
    }

	Reg = new TRegistry;
	Reg->RootKey = HKEY_CURRENT_USER;
    Reg->Access = KEY_READ | KEY_WRITE;
    Reg->CloseKey ();
	Reg->OpenKey ("SOFTWARE\\Lewis\\GuiPlop", true);

    for (i = 0; i < NumFileNameStrings; i++)
	{   Key = "File" + IntToStr (i);
        Reg->WriteString (Key, FileNameStrings->Strings [i]);
	}
    delete Reg;

}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::MeshDeleteClick(TObject *Sender)
{   int i;

    if (ActiveSupportId == -1)
	{  warn_msg ("Select a support ring to delete");
    }
    else
    {   i = ActiveSupportId + CellEditScrollBar->Position;
		CopyCellNumSupportString = CellNumSupportStrings [i];
        CopySupportRadiiState = SupportRadiiState [i];
        CopySupportAngleState = SupportAngleState [i];
        CopySupportRelForceState = SupportRelForceState [i];
        MeshPaste->Enabled = true;
        for (i = ActiveSupportId + CellEditScrollBar->Position; i < NumSupportRing - 1; i++)
        {   CellNumSupportStrings [i] = CellNumSupportStrings [i + 1];
            SupportRadiiState [i] = SupportRadiiState [i + 1];
            SupportAngleState [i] = SupportAngleState [i + 1];
            SupportRelForceState [i] = SupportRelForceState [i + 1];
        }
        NumSupportRing--;
        CellEditScrollBarResize (NumSupportRing);
        FileIsChanged = true;
    }
}
//---------------------------------------------------------------------------


void __fastcall TCellEditForm::MeshAddClick(TObject *Sender)
{   int i;

    if (NumSupportRing == max_mesh_radii)
    {  err_msg ("Can't add any more supports; already at maximum");
    }
    else
    {   i = NumSupportRing;
        CellNumSupportStrings [i] = "";
        SupportRadiiState [i].NEValue = "";
        SupportRadiiState [i].NEMode = NumEditFixed;
        SupportRadiiState [i].NEFrom = "";
        SupportRadiiState [i].NETo = "";
        SupportRadiiState [i].NEBy = "";

        SupportAngleState [i].NEValue = "";
        SupportAngleState [i].NEMode = NumEditFixed;
        SupportAngleState [i].NEFrom = "";
        SupportAngleState [i].NETo = "";
        SupportAngleState [i].NEBy = "";

        SupportRelForceState [i].NEValue = "";
        SupportRelForceState [i].NEMode = NumEditFixed;
        SupportRelForceState [i].NEFrom = "";
        SupportRelForceState [i].NETo = "";
        SupportRelForceState [i].NEBy = "";

        NumSupportRing++;
        CellEditScrollBarResize (NumSupportRing);
        FileIsChanged = true;
    }
}

//---------------------------------------------------------------------------



void __fastcall TCellEditForm::MeshCopyClick(TObject *Sender)
{   int i;

    if (ActiveSupportId == -1)
    {  warn_msg ("Select a support ring to copy");
    }
    else
    {   i = ActiveSupportId + CellEditScrollBar->Position;
        CopyCellNumSupportString = CellNumSupportStrings [i];
        CopySupportRadiiState = SupportRadiiState [i];
        CopySupportAngleState = SupportAngleState [i];
        CopySupportRelForceState = SupportRelForceState [i];
        MeshPaste->Enabled = true;
    }
}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::MeshPasteClick(TObject *Sender)
{   int i;

    if (ActiveSupportId == -1)
    {   warn_msg ("Select a position to paste");
    }
    else if (NumSupportRing == max_mesh_radii)
    {   warn_msg ("Can't add any more supports; already at maximum");
    }
    else
    {   for (i = NumSupportRing; i >= ActiveSupportId + CellEditScrollBar->Position; i--)
        {   CellNumSupportStrings [i + 1] = CellNumSupportStrings [i];
            SupportRadiiState [i + 1] = SupportRadiiState [i];
            SupportAngleState [i + 1] = SupportAngleState [i];
            SupportRelForceState [i + 1] = SupportRelForceState [i];
        }
        i = ActiveSupportId + CellEditScrollBar->Position;
        CellNumSupportStrings [i] = CopyCellNumSupportString;
        SupportRadiiState [i] = CopySupportRadiiState;
        SupportAngleState [i] = CopySupportAngleState;
        SupportRelForceState [i] = CopySupportRelForceState;

        NumSupportRing++;
        CellEditScrollBarResize (NumSupportRing);
        FileIsChanged = true;
    }

}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::MeshDuplicateClick(TObject *Sender)
{   int i;

    if (ActiveSupportId == -1)
    {   warn_msg ("Select a position to duplicate");
    }
    else if (NumSupportRing == max_mesh_radii)
    {   err_msg ("Can't add any more supports; already at maximum");
    }
    else
    {   for (i = NumSupportRing; i >= ActiveSupportId + CellEditScrollBar->Position; i--)
        {   CellNumSupportStrings [i + 1] = CellNumSupportStrings [i];
            SupportRadiiState [i + 1] = SupportRadiiState [i];
            SupportAngleState [i + 1] = SupportAngleState [i];
            SupportRelForceState [i + 1] = SupportRelForceState [i];
        }
        NumSupportRing++;
        CellEditScrollBarResize (NumSupportRing);
        FileIsChanged = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::MeshInsertClick(TObject *Sender)
{   int i;

    if (ActiveSupportId == -1)
    {   warn_msg ("Select a position to insert");
    }
    else if (NumSupportRing == max_mesh_radii)
    {   err_msg ("Can't add any more supports; already at maximum");
    }
    else
    {   for (i = NumSupportRing; i >= ActiveSupportId + CellEditScrollBar->Position; i--)
        {   CellNumSupportStrings [i + 1] = CellNumSupportStrings [i];
            SupportRadiiState [i + 1] = SupportRadiiState [i];
            SupportAngleState [i + 1] = SupportAngleState [i];
            SupportRelForceState [i + 1] = SupportRelForceState [i];
        }
        i = ActiveSupportId + CellEditScrollBar->Position;
        CellNumSupportStrings [i] = "";
        SupportRadiiState [i].NEValue = "";
        SupportRadiiState [i].NEMode = NumEditFixed;
        SupportRadiiState [i].NEFrom = "";
        SupportRadiiState [i].NETo = "";
        SupportRadiiState [i].NEBy = "";

        SupportAngleState [i].NEValue = "";
        SupportAngleState [i].NEMode = NumEditFixed;
        SupportAngleState [i].NEFrom = "";
        SupportAngleState [i].NETo = "";
        SupportAngleState [i].NEBy = "";

        SupportRelForceState [i].NEValue = "";
        SupportRelForceState [i].NEMode = NumEditFixed;
        SupportRelForceState [i].NEFrom = "";
        SupportRelForceState [i].NETo = "";
        SupportRelForceState [i].NEBy = "";

        NumSupportRing++;
        CellEditScrollBarResize (NumSupportRing);
        FileIsChanged = true;
    }
}                                   
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::TextTabSheetShow(TObject *Sender)
{
    if (PlopRunningFlag)
    {   warn_msg ("Can't switch to edit as text while plop is running\n");
        EditAsTextMemo->Clear ();
        EditAsTextMemo->Enabled = false;
        TextIsValid = false;        /* remember in case plop finishes while showing */
        return;
    }
    CopyToPlop (true);

    write_info_chars (0, 1);

	EditAsTextMemo->SetTextBuf (UnicodeOf (plop_text_file_buff));
    EditAsTextMemo->Modified = false;
    TextIsValid = true;
    EditAsTextMemo->Enabled = true;

}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::SaveTextTabSheet (void)
{   bool PrevMod;

    if(PlopRunningFlag || !TextIsValid)
        return;
/* TODO */
//	(void) EditAsTextMemo->GetTextBuf (plop_text_file_buff, max_plop_file_len);
	(void) EditAsTextMemo->GetTextBuf (plop_text_file_buff_w, max_plop_file_len);
	strcpy (plop_text_file_buff, AnsiOf (plop_text_file_buff_w));

	read_info_chars ();

    // loadfromplop trashes fileischanged

    PrevMod = FileIsChanged;
	LoadFromPlop ();
    CellPartScrollBarResize (PartNumParts, NULL);
    PartDimensionForm->PartNumScrollBarChange (NULL);
    FileIsChanged = PrevMod;
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::TextTabSheetHide(TObject *Sender)
{
/* TODO */
//	(void) EditAsTextMemo->GetTextBuf (plop_text_file_buff, max_plop_file_len);
	(void) EditAsTextMemo->GetTextBuf (plop_text_file_buff_w, max_plop_file_len);
	strcpy (plop_text_file_buff, AnsiOf (plop_text_file_buff_w));

    if (EditAsTextMemo->Modified)
    {   try
        {   SaveTextTabSheet ();
        }
        catch (PlopException p)
        {   err_msg ("Unable to load the description as text.");
        }
        FileIsChanged = true;
    }

}

//---------------------------------------------------------------------------

void LockPlopData (int who)
{   CellEditForm->PlopDataCrit->Enter ();
}
//---------------------------------------------------------------------------

void UnlockPlopData (void)
{   CellEditForm->PlopDataCrit->Leave ();
}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::HelpHelpItemClick(TObject *Sender)
{
#ifdef debug_registry
	TRegistry *Reg;
	AnsiString hf;
    bool RegRet;

	Reg = new TRegistry;
	Reg->Access = KEY_READ;
	Reg->RootKey = HKEY_LOCAL_MACHINE;
	Reg->CloseKey ();
	RegRet = Reg->OpenKey ("SOFTWARE\\Lewis\\GuiPlop", true);
//	RegRet = Reg->OpenKey ("SOFTWARE\\WOW6432Node\\Lewis\\Plop", true);

	hf = Reg->ReadString ("HelpFileLoc");
	delete Reg;
#endif

//	void * r = ShellExecute (NULL, "open", "c:\\Users\\David\\Cloudstation\\devel\\plop\\gui_plop\\doc\\GuiPlop Users Manual.pdf",
//	NULL, NULL, SW_SHOW);
	ShellExecute (NULL, "open", HelpFileLoc.c_str (),	NULL, NULL, SW_SHOW);

// Application->HelpCommand (HELP_CONTENTS, 0);

}
//---------------------------------------------------------------------------



void __fastcall TCellEditForm::CommentsMemoChange(TObject *Sender)
{
    FileIsChanged = true;    
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::NumSupportRingEditChange(TObject *Sender)
{
    FileIsChanged = true;
    NumSupportRingChanged = true;    
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::NumBasisEditChange(TObject *Sender)
{
    FileIsChanged = true;
    NumBasisChanged = true;    
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::CellTypeTabSheetShow(TObject *Sender)
{   char str [100];

    sprintf (str, "%d", NumSupportRing);
    NumSupportRingEdit->Text = str;

}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::CellTypeTabSheetHide(TObject *Sender)
{   int r;

    if (NumSupportRingChanged)
	{   r = Application->MessageBox (L"You changed the number of supports,"
		 " but did not tell Plop to update\n"
		 "Do you want to update the number of supports?", L"Plop Warning",
             MB_YESNO + MB_ICONWARNING);
        if (r == ID_YES)
            NumSupportButtonClick (Sender);

    }
    NumSupportRingChanged = false;
}
//---------------------------------------------------------------------------


void __fastcall TCellEditForm::BasisTabSheetHide(TObject *Sender)
{   int r;

    if (NumBasisChanged)
	{   r = Application->MessageBox (L"You changed the size of the basis,"
         " but did not tell Plop to update\n"
		 "Do you want to update the basis?", L"Plop Warning",
             MB_YESNO + MB_ICONWARNING);
        if (r == ID_YES)
			NumBasisUpdateButtonClick (Sender);
    }
    NumBasisChanged = false;

}
//---------------------------------------------------------------------------


void __fastcall TCellEditForm::BasisTabSheetShow(TObject *Sender)
{   char str [100];

    sprintf (str, "%d", NumBasis);
    NumBasisEdit->Text = str;
    NumBasisChanged = false;
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::MaterialComboBoxChange(TObject *Sender)
{   int i;
	char str [100];

	i = MaterialComboBox->ItemIndex;
	sprintf (str, "%g", material_modulus [i]);
	ModulusNumEdit->NumEditValue->Text = str;
	sprintf (str, "%g", material_density [i]);
	DensityNumEdit->NumEditValue->Text = str;
	sprintf (str, "set density edit to %g\n", material_density [i]);
	DebugMsg (str);
	sprintf (str, "%g", material_poisson [i]);
	PoissonNumEdit->NumEditValue->Text = str;

}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::FormCreate(TObject *Sender)
{
    int i;
    int CellEditHeight;
    char stuff [200];
    NumEditState s;
    MEMORYSTATUS memstat;
    int separator_num;
    AnsiString RegKey;
	AnsiString RegValue;
	bool RegRet;
//	TStrings *RegStrings;
	TStringList *RegStrings = new TStringList;
	AnsiString debugstr;
	int foo;
	TRegDataInfo rinf;

/* suggested by Richard in the UK */
#ifdef richardgetfiledir
	AnsiString  dir, zExePath1, zExePath2;

	dir = ExtractFileDir(ParamStr(0));
	dir += "\\Z88\\";
	zExePath1 = dir + "z88i1plop.exe";
	zExePath2 = dir + "z88i2plop.exe";
	printf("%s\n%s\n", zExePath1, zExePath2);
#endif

	strcpy (start_locale, setlocale (LC_ALL, NULL));
	strcpy (run_locale, setlocale (LC_ALL, "C"));

	sprintf (compile_date, "Compiled %s %s", __DATE__, __TIME__);

    memstat.dwLength = sizeof (memstat);
    GlobalMemoryStatus (&memstat);

    FileNameStrings = new TStringList;
    NumFileNameStrings = 0;

    AutoCellLoc = "";
    HelpFileLoc = "";

	Reg = new TRegistry;
	Reg->Access = KEY_READ;
	Reg->RootKey = HKEY_LOCAL_MACHINE;
    Reg->CloseKey ();
	RegRet = Reg->OpenKey ("SOFTWARE\\Lewis\\GuiPlop", true);

//	Reg->GetKeyNames (RegStrings);
//	Reg->GetDataInfo ("AutoCellLoc", rinf);
	AutoCellLoc = Reg->ReadString ("AutoCellLoc");
	HelpFileLoc = Reg->ReadString ("HelpFileLoc");
	PlopLoc = Reg->ReadString ("PlopLoc");

	Reg->RootKey = HKEY_CURRENT_USER;
    Reg->Access = KEY_READ | KEY_WRITE;
    Reg->CloseKey ();
	Reg->OpenKey ("SOFTWARE\\Lewis\\GuiPlop", true);
//	Reg->GetKeyNames (RegStrings);
	LastVersionRun = Reg->ReadString ("LastVersionRun");
//	Reg->GetDataInfo ("LastVersionRun", rinf);
	Reg->WriteString ("LastVersionRun", CurrentVersion);

    Application->HelpFile = HelpFileLoc;

    DebugMsgs = NULL;

    PlopRunningFlag = false;
    TextIsValid = false;

	PlopDataCrit = new TCriticalSection;

    for (i = 0; i < MaxFileStrings; i++)
    {   FileNameItems [i] = new TMenuItem (FileItems);
        FileNameItems [i]->OnClick = FileOpenItemClick;
    }

    separator_num = FileItems->IndexOf (FileSeparatorItem);
    for (i = 0; i < MaxFileStrings; i++)
    {   RegKey = "File" + IntToStr (i);
        if (Reg->GetDataType (RegKey) == rdString)
		{   RegValue = Reg->ReadString (RegKey);
            if (RegValue != "" && FileExists (RegValue))
            {   FileNameStrings->Add (RegValue);
                if (NumFileNameStrings == 0)
                {   SeparatorItem = new TMenuItem (FileItems);
                    SeparatorItem->Caption = '-';
                    FileItems->Insert (separator_num + 1, SeparatorItem);
                }
                FileItems->Insert (separator_num + 1 + NumFileNameStrings,
                    FileNameItems [NumFileNameStrings]);
                NumFileNameStrings++;
            }
        }
    }
    for (i = 0; i < NumFileNameStrings; i++)
    {   FileNameItems [i]->Caption = "&" + IntToStr (i + 1) + " " +
                FileNameStrings->Strings [i];
    }
	delete Reg;



    /* create edits in right order so tabs work correctly
    */

    for (i = 0; i < MeshEditNumVarScroll; i++)
    {
        VarScrollNameEdit [i] = new VarNameEdit (this, VarScrollPanel,
            &(VarNames [i]));
        VarScrollNameEdit [i]->Parent = VarScrollPanel;
		VarScrollNameEdit [i]->Left = 60;
		VarScrollNameEdit [i]->Width = 80;
        VarScrollNameEdit [i]->Top = NumEditVSpace + NumEditVPitch * i;
        VarScrollNameEdit [i]->OnChange =
            VarScrollNameEdit [i]->VarNameChanged;
        VarScrollNameEdit [i]->Tag = i;
        VarScrollNameEdit [i]->IdPtr = &ActiveVarId;

        VarScrollNameLabels [i] = new TLabel (this);
        VarScrollNameLabels [i]->Parent = VarScrollPanel;
        VarScrollNameLabels [i]->Caption = "Name";
        VarScrollNameLabels [i]->Left = 10;
        VarScrollNameLabels [i]->Top = NumEditVSpace + NumEditVPitch * i + 4;

		VarScrollNumEdit [i] = new NumEdit (this, VarScrollPanel, "Value",
			NumEditVSpace + NumEditVPitch * i, 160, 60);
        VarScrollNumEdit [i]->SetIdTag (i, &ActiveVarId);

    }

    VarScrollBar->Min = 0;
    VarScrollBar->Max = max_variables - MeshEditNumVarScroll;
    VarScrollBar->SmallChange = 1;
    VarScrollBar->LargeChange = MeshEditNumVarScroll;
    VarScrollBar->Position = 0;

    for (i = 0; i < max_variables; i++)
    {
        s.NELabel = "Value";
        s.NEMode = NumEditFixed;
		VarEdit [i] = s;
    }

    NumVarEdit = 0;

    for (i = 0;  i < MeshEditNumVarScroll; i++)
    {   VarScrollNumEdit [i]->NumEditLoad (&(VarEdit [i]));
        VarScrollNumEdit [i]->MyState = &(VarEdit [i]);
    }

    for (i = 0; i < max_mesh_radii; i++)
    {
        s.NELabel = "Radius";
        s.NEMode = NumEditFixed;
        SupportRadiiState [i] = s;
        s.NELabel = "Angle";
        SupportAngleState [i] = s;
        s.NELabel = "Rel Force";
        SupportRelForceState [i] = s;
    }

    NumSupportRing = 0;
    NumSupportRingChanged = false;

    CellEditHeight = 4 * NumEditVPitch + NumEditVSpace;
    for (i = 0; i < MeshEditNumMeshScroll; i++)
    {   CellScrollGroupBoxes [i] = new TGroupBox (CellScrollPanel);
        CellScrollGroupBoxes [i]->Top = i * (CellEditHeight +
            MeshEditGroupBoxSpace) + 2 * MeshEditGroupBoxSpace;
        CellScrollGroupBoxes [i]->Left = 10;
        CellScrollGroupBoxes [i]->Height = CellEditHeight;
        CellScrollGroupBoxes [i]->Width = CellScrollPanel->Width -
            CellEditScrollBar->Width - 20;
        sprintf (stuff, "Support Ring %d", i);
        CellScrollGroupBoxes [i]->Caption = stuff;
        CellScrollGroupBoxes [i]->Parent = CellScrollPanel;
        CellSupportLabels [i] = new TLabel (this);
        CellSupportLabels [i]->Parent = CellScrollGroupBoxes [i];
        CellSupportLabels [i]->Caption = "Number of points";
        CellSupportLabels [i]->Left = 10;
        CellSupportLabels [i]->Top = NumEditVSpace + 4;
        CellNumSupportEdits [i] = new VarNameEdit (this,
            CellScrollGroupBoxes [i], &(CellNumSupportStrings [i]));
        CellNumSupportEdits [i]->Parent = CellScrollGroupBoxes [i];
        CellNumSupportEdits [i]->Left = 120;
        CellNumSupportEdits [i]->Top = NumEditVSpace;
        CellNumSupportEdits [i]->Tag = i;
        CellNumSupportEdits [i]->IdPtr = &ActiveSupportId;

		SupportRadiiNumEdit [i] = new NumEdit (this, CellScrollGroupBoxes [i],
		 "Radius", NumEditVPitch + NumEditVSpace, 10, 60);
		SupportRadiiNumEdit [i]->MyState = &(SupportRadiiState [i]);
		SupportRadiiNumEdit [i]->SetIdTag (i, &ActiveSupportId);

		SupportAngleNumEdit [i] = new NumEdit (this, CellScrollGroupBoxes [i],
		 "Angle", 2 * NumEditVPitch + NumEditVSpace, 10, 60);
		SupportAngleNumEdit [i]->MyState = &(SupportAngleState [i]);
		SupportAngleNumEdit [i]->SetIdTag (i, &ActiveSupportId);

		SupportRelForceNumEdit [i] = new NumEdit (this, CellScrollGroupBoxes [i],
		 "Rel Force", 3 * NumEditVPitch + NumEditVSpace, 10, 60);
		SupportRelForceNumEdit [i]->MyState = &(SupportRelForceState [i]);
        SupportRelForceNumEdit [i]->SetIdTag (i, &ActiveSupportId);

        CellScrollGroupBoxes [i]->Visible = true;
    }

    CellEditScrollBar->Min = 0;
    CellEditScrollBar->Max = 10;
    CellEditScrollBar->SmallChange = 1;
    CellEditScrollBar->LargeChange = MeshEditNumMeshScroll;

	DiamNumEdit = new NumEdit (this, DiamGroupBox, "Diameter", 30, 24, 70);
	DiamNumEdit->MyState = &DiamNumState;
	DiamNumEdit->NumEditSave (&DiamNumState);
	AddToPlopMap ("diameter", DiamNumEdit, 1, &DiamNumState, NULL, -1, NULL);

	ThickNumEdit = new NumEdit (this, DiamGroupBox, "Thickness", 70, 24, 70);
	ThickNumEdit->MyState = &ThickNumState;
	ThickNumEdit->NumEditSave (&ThickNumState);
	AddToPlopMap ("thickness", ThickNumEdit, 1, &ThickNumState, NULL, -1, NULL);

	FocalNumEdit = new NumEdit (this, FocalGroupBox, "Focal", 160, 24, 70);
	FocalNumEdit->MyState = &FocalNumState;
    FocalNumEdit->NumEditSave (&FocalNumState);
    AddToPlopMap ("focal-length", FocalNumEdit, 1, &FocalNumState, NULL,
     0, FocalRadioGroup);
    AddToPlopMap ("f-ratio", FocalNumEdit, 1, &FocalNumState, NULL,
     1, FocalRadioGroup);
    AddToPlopMap ("sagitta", FocalNumEdit, 1, &FocalNumState, NULL,
     2, FocalRadioGroup);
    AddToPlopMap ("rel-sagitta", FocalNumEdit, 1, &FocalNumState, NULL,
     3, FocalRadioGroup);

	ObsNumEdit = new NumEdit (this, ObsGroupBox, "Obstruction", 120, 32, 70);
    ObsNumEdit->MyState = &ObsNumState;
    ObsNumEdit->NumEditSave (&ObsNumState);
    AddToPlopMap ("obstruction-radius", ObsNumEdit, 1, &ObsNumState, NULL,
     0, ObsRadioGroup);
    AddToPlopMap ("obstruction-diam", ObsNumEdit, 1, &ObsNumState, NULL,
     1, ObsRadioGroup);
    AddToPlopMap ("rel-obs-radius", ObsNumEdit, 1, &ObsNumState, NULL,
     2, ObsRadioGroup);

	HoleNumEdit = new NumEdit (this, HoleGroupBox, "Hole", 120, 24, 60);
    HoleNumEdit->MyState = &HoleNumState;
    HoleNumEdit->NumEditSave (&HoleNumState);
    AddToPlopMap ("hole-diameter", HoleNumEdit, 1, &HoleNumState, NULL,
     0, HoleRadioGroup);
    AddToPlopMap ("rel-hole-diameter", HoleNumEdit, 1, &HoleNumState, NULL,
     1, HoleRadioGroup);

	ModulusNumEdit = new NumEdit (this, MaterialsGroupBox, "Modulus", 30, 24, 70);
    ModulusNumEdit->MyState = &ModulusNumState;
    ModulusNumEdit->NumEditSave (&ModulusNumState);
    AddToPlopMap ("modulus", ModulusNumEdit, 1, &ModulusNumState, NULL,
     -1, NULL);

	PoissonNumEdit = new NumEdit (this, MaterialsGroupBox, "Poisson", 70, 24, 70);
    PoissonNumEdit->MyState = &PoissonNumState;
    PoissonNumEdit->NumEditSave (&PoissonNumState);
    AddToPlopMap ("poisson", PoissonNumEdit, 1, &PoissonNumState, NULL,
     -1, NULL);

	DensityNumEdit = new NumEdit (this, MaterialsGroupBox, "Density", 110, 24, 70);
    DensityNumEdit->MyState = &DensityNumState;
    DensityNumEdit->NumEditSave (&DensityNumState);
    AddToPlopMap ("density", DensityNumEdit, 1, &DensityNumState, NULL,
     -1, NULL);

	MirrorTiltEdit = new NumEdit (this, Z88ParamTabSheet, "Mirror Tilt Angle", 20, 24, 130);
	MirrorTiltEdit->MyState = &MirrorTiltState;
	MirrorTiltEdit->NumEditSave (&MirrorTiltState);
	
//	AddToPlopMap ("tilt-angle", MirrorTiltEdit, 1, &MirrorTiltState, NULL, -1, NULL);
	AddToPlopMap ("edge-support-sling-angle", MirrorTiltEdit, 1, &MirrorTiltState, NULL, 0, OffAxisRadioGroup);
	AddToPlopMap ("edge-support-glued-angle", MirrorTiltEdit, 1, &MirrorTiltState, NULL, 1, OffAxisRadioGroup);

	SlingIncludedAngleEdit = new NumEdit (this, Z88ParamTabSheet, "Sling Included Angle", 130, 24, 130);
	SlingIncludedAngleEdit->MyState = &SlingIncludedAngleState;
	SlingIncludedAngleEdit->NumEditSave (&SlingIncludedAngleState);
	AddToPlopMap ("sling-included-angle", SlingIncludedAngleEdit, 1, &SlingIncludedAngleState, NULL,
	 -1, NULL);


	for (i = 0; material_names [i] [0] != '\0'; i++)
    {  MaterialComboBox->Items->Add(material_names [i]);
    }
    MaterialComboBox->ItemIndex = 0;
    MaterialComboBoxChange (Sender);

    AddToPlopMap ("support-radii", NULL, max_mesh_radii, SupportRadiiState,
     NULL, 0, SupportRadioGroup);
    AddToPlopMap ("rel-support-radii", NULL, max_mesh_radii, SupportRadiiState,
     NULL, 1, SupportRadioGroup);

    AddToPlopMap ("support-angle", NULL, max_mesh_radii, SupportAngleState,
     NULL, -1, NULL);

    AddToPlopMap ("rel-force", NULL, max_mesh_radii, SupportRelForceState,
     NULL, -1, NULL);

    // create basis info

    for (i = 0; i < max_basis_size; i++)
    {   BasisNumLabels [i] = new TLabel (this);
        BasisNumLabels [i]->Parent = BasisScrollBox;
        BasisNumLabels [i]->Caption = "Number of Points";
        BasisNumLabels [i]->Left = 20;
        BasisNumLabels [i]->Top = 40 * i + 20;

        BasisNumEdits [i] = new TEdit (this);
        BasisNumEdits [i]->Parent = BasisScrollBox;
        BasisNumEdits [i]->Left = 130;
        BasisNumEdits [i]->Width = 50;
        BasisNumEdits [i]->Top = 40 * i + 16;

        BasisRingLabels [i] = new TLabel (this);
        BasisRingLabels [i]->Parent = BasisScrollBox;
        BasisRingLabels [i]->Caption = "First Mesh Ring";
        BasisRingLabels [i]->Left = 200;
        BasisRingLabels [i]->Top = 40 * i + 20;

        BasisRingEdits [i] = new TEdit (this);
        BasisRingEdits [i]->Parent = BasisScrollBox;
        BasisRingEdits [i]->Left = 300;
        BasisRingEdits [i]->Width = 50;
        BasisRingEdits [i]->Top = 40 * i + 16;

    }
    NumBasis = 0;
    NumBasisChanged = false;

    ActiveSupportId = -1;
    ActiveVarId = -1;
    CellPageControl->ActivePage = MirrorTabSheet;

    EqualForceCheckBoxClick (Sender);
    VarAngleCheckBoxClick (Sender);

    VarScrollBarResize (NumVarEdit);
    CellEditScrollBarResize (NumSupportRing);
    NumBasisUpdate (NumBasis);

    // set up parts

    PartNumParts = 0;
    PartScrollLastPosition = -1;
    CellPartScrollBarResize (PartNumParts, Sender);
    CellPartScrollBarChange (Sender);



    // initialize Plop

    init_plop ();
    
    // 100 points per meg + 500 gives should not usually overflow
    set_max_points (500 + memstat.dwTotalPhys / 10000);

    init_graphics (); /* used to store some error calculation info */

    alloc_globals ();
    alloc_plate_globals ();


    Application->OnMessage = ProcessMessage;

	if (GuiPlopArgsT [0] != '\0')
    {   try
        {   // ignore leading and trailing "
			strcpy (stuff, GuiPlopArgsT);
            stuff [strlen (stuff) - 1] = '\0';
            read_info (stuff + 1);
            GrOpenFile = stuff + 1;
            LoadFromPlop ();
            CellEditScrollBarChange (CellEditScrollBar);
            CellPartScrollBarResize (PartNumParts, Sender);
        }
        catch (PlopException p)
        {   err_msg ("Unable to load the file.");
        }
    }
	FileIsChanged = false;
	MaterialComboBoxChange (Sender);
    
}
//---------------------------------------------------------------------------


void __fastcall TCellEditForm::MeshMenuItemClick(TObject *Sender)
{
    MeshPictureForm->Show ();    
}
//---------------------------------------------------------------------------
void __fastcall TCellEditForm::SupportsMenuItemClick(TObject *Sender)
{
   SupportPictureForm->Show ();    
}
//---------------------------------------------------------------------------
void __fastcall TCellEditForm::ContourMenuItemClick(TObject *Sender)
{
    ContourPictureForm->Show ();
}
//---------------------------------------------------------------------------
void __fastcall TCellEditForm::ColourPlotMenuItemClick(TObject *Sender)
{
	ColorPictureForm->Show ();
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::CellPartScrollBarResize (int NewNumParts,
        TObject *Sender)
{   int i;
    int j;

    for (i = PartNumParts; i < NewNumParts; i++)
    {   PartType [i] = part_type_triangle;
        PartQuantityText [i] = "";

        for (j = 0; j < tri_pts; j++)
        {   PartPointType [i] [j] = part_point_ring;
            PartPointRingNumText [i] [j] = "";
            PartPointPointNumText [i] [j] = "";
        }
    }
    PartNumParts = NewNumParts;
	CellPartScrollBar->Max = my_max (PartNumParts - 1, 0);
    PartNumGroupBox->Visible = (PartNumParts > 0);
    CellPartScrollBarChange (Sender);
}

//---------------------------------------------------------------------------


void __fastcall TCellEditForm::PartNumUpdateButtonClick(TObject *Sender)
{   int NewNumParts;

    if (swscanf (PartNumEdit->Text.c_str (), L"%d", &NewNumParts) != 1 ||
        NewNumParts < 0 || NewNumParts > max_parts)
    {   err_msg ("Number of cell parts does not contain a valid number!");
        return;
    }
    CellPartScrollBarResize (NewNumParts, Sender);

}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::CellPartsSaveCurrentItem (void)
{
    if (PartScrollLastPosition >= 0 && PartScrollLastPosition < PartNumParts)
    {   PartType [PartScrollLastPosition] = PartTypeComboBox->ItemIndex;
        PartQuantityText [PartScrollLastPosition] = PartQuantityEdit->Text;

        PartPointType [PartScrollLastPosition] [0] = PartPointTypeComboBox1->ItemIndex;
        PartPointRingNumText [PartScrollLastPosition] [0] = PartRingNumEdit1->Text;
        PartPointPointNumText [PartScrollLastPosition] [0] = PartPointEdit1->Text;

        PartPointType [PartScrollLastPosition] [1] = PartPointTypeComboBox2->ItemIndex;
        PartPointRingNumText [PartScrollLastPosition] [1] = PartRingNumEdit2->Text;
        PartPointPointNumText [PartScrollLastPosition] [1] = PartPointEdit2->Text;

        PartPointType [PartScrollLastPosition] [2] = PartPointTypeComboBox3->ItemIndex;
        PartPointRingNumText [PartScrollLastPosition] [2] = PartRingNumEdit3->Text;
        PartPointPointNumText [PartScrollLastPosition] [2] = PartPointEdit3->Text;
    }
}

//---------------------------------------------------------------------------

void __fastcall TCellEditForm::CellPartScrollBarChange(TObject *Sender)
{   int ipos;
    char str [100];

    CellPartsSaveCurrentItem ();
    ipos = CellPartScrollBar->Position;
    if (ipos >= 0 && ipos < PartNumParts)
    {   PartScrollLastPosition = ipos;
        sprintf (str, "Part Number %d", ipos + 1);
        PartNumGroupBox->Caption = str;
        PartTypeComboBox->ItemIndex = PartType [ipos];
        PartQuantityEdit->Text = PartQuantityText [ipos];

        PartPointTypeComboBox1->ItemIndex = PartPointType [ipos] [0];
        PartRingNumEdit1->Text = PartPointRingNumText [ipos] [0];
        PartPointEdit1->Text = PartPointPointNumText [ipos] [0];
        if (PartPointType [ipos] [0] == part_point_ring)
            PartPointNumLabel1->Caption = "Support Point in Ring";
        else
            PartPointNumLabel1->Caption = "Part Position in Ring";

        PartPointTypeComboBox2->ItemIndex = PartPointType [ipos] [1];
        PartRingNumEdit2->Text = PartPointRingNumText [ipos] [1];
        PartPointEdit2->Text = PartPointPointNumText [ipos] [1];
        if (PartPointType [ipos] [1] == part_point_ring)
            PartPointNumLabel2->Caption = "Support Point in Ring";
        else
            PartPointNumLabel2->Caption = "Part Position in Ring";

        PartPointTypeComboBox3->ItemIndex = PartPointType [ipos] [2];
        if (PartType [ipos] == part_type_triangle)
        {   PartRingNumEdit3->Text = PartPointRingNumText [ipos] [2];
            PartPointEdit3->Text = PartPointPointNumText [ipos] [2];
            PartPointTypeComboBox3->Visible = true;
            PartRingNumEdit3->Visible = true;
            PartPointEdit3->Visible = true;
            PartPointNumLabel3->Visible = true;
            if (PartPointType [ipos] [2] == part_point_ring)
                PartPointNumLabel3->Caption = "Support Point in Ring";
            else
                PartPointNumLabel3->Caption = "Part Position in Ring";
        }
        else
        {   PartPointTypeComboBox3->Visible = false;
            PartRingNumEdit3->Visible = false;
            PartPointEdit3->Visible = false;
            PartPointNumLabel3->Visible = false;
        }

    }
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::CellPartsMenuItemClick(TObject *Sender)
{
    CellPartPictureForm->Show ();
}
//---------------------------------------------------------------------------


void __fastcall TCellEditForm::DimensionsMenuItemClick(TObject *Sender)
{
    PartDimensionForm->Show ();
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::QuadsMenuItemClick(TObject *Sender)
{
	QuadPictureForm->Show ();
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::Z88ColorMenuItemClick(TObject *Sender)
{
	Z88ColorPictureForm->Show ();	
}
//---------------------------------------------------------------------------

void __fastcall TCellEditForm::WhatsNewMenuItemClick(TObject *Sender)
{
	WhatsNewForm->Show ();	
}
//---------------------------------------------------------------------------




bool __fastcall TCellEditForm::IsFirstRun (void) {
	return (LastVersionRun != CurrentVersion);
}

