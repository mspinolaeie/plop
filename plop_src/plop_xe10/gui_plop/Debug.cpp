//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop


#include <stdio.h>

#include "Debug.h"
#include "MeshEdit.h"

#include "plate_global.h"
#include "RegView.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDebugForm *DebugForm;

bool DebugEnabled = false;

extern const char *debug_strings [];

#include "Debug.h"
wchar_t* __fastcall UnicodeOf(const char* c);
char* __fastcall AnsiOf(wchar_t* w);

//---------------------------------------------------------------------------
__fastcall TDebugForm::TDebugForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDebugForm::SetMsg (char *m)
{   DebugPanel->Caption = m;
    UpdateWindow (Handle);    
}
//---------------------------------------------------------------------------

void DebugMsg (const char *m)
{   if (DebugEnabled)
	{   if (DebugForm->HaveDebugFile) {
			fputs (m, debug_file);
		}
		DebugForm->DebugPanel->Caption = m;
        while (*m != '\0' && CellEditForm->DebugMsgsNext -
            CellEditForm->DebugMsgs < (1000000 - 2))
        {   if (*m == '\n' && *CellEditForm->DebugMsgsNext != '\r')
                *(CellEditForm->DebugMsgsNext++) = '\r';
            *(CellEditForm->DebugMsgsNext++) = *m++;
        }
        *CellEditForm->DebugMsgsNext = '\0';
    }
}
//---------------------------------------------------------------------------
void __fastcall TDebugForm::UpdateTraceButtonClick(TObject *Sender)
{   /* this needs to be fixed, will overflow the buffer bigly */
	DebugMemo->SetTextBuf (UnicodeOf (CellEditForm->DebugMsgs));

}
//---------------------------------------------------------------------------
void __fastcall TDebugForm::DebugCheckBoxClick(TObject *Sender)
{
    DebugEnabled = DebugCheckBox->Checked;    
}
//---------------------------------------------------------------------------


void __fastcall TDebugForm::FormCreate(TObject *Sender)
{   int i;

    for (i = 0; debug_strings [i] [0] != '\0'; i++)
    {   DebugBoxes [i] = new TCheckBox (this);
        DebugBoxes [i]->Top = i * 24 + 248;
        DebugBoxes [i]->Left = 24;
        DebugBoxes [i]->Parent = this;
        DebugBoxes [i]->Caption = debug_strings [i];
        DebugBoxes [i]->Checked = false;
        DebugBoxes [i]->OnClick = UpdateDebugBoxes;
    }
    NDebugBox = i;

	HaveDebugFile = false;

}
//---------------------------------------------------------------------------
void __fastcall TDebugForm::UpdateDebugBoxes(TObject *Sender)
{   int i;

    for (i = 0; i < NDebugBox; i++)
    {   if (DebugBoxes [i]->Checked)
            debugs [i] = 1;
        else
            debugs [i] = 0;
    }
}

//---------------------------------------------------------------------------
void __fastcall TDebugForm::SetButtonClick(TObject *Sender)
{   int i;

    for (i = 0; i < NDebugBox; i++)
        DebugBoxes [i]->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TDebugForm::ClearButtonClick(TObject *Sender)
{   int i;

    for (i = 0; i < NDebugBox; i++)
        DebugBoxes [i]->Checked = false;
}
//---------------------------------------------------------------------------


void __fastcall TDebugForm::DebugFileButtonClick(TObject *Sender)
{
	if (HaveDebugFile)
    {   fflush (debug_file);
        fclose (debug_file);
    }
	debug_file = fopen (AnsiOf (FileEdit->Text.c_str ()), "w");
    HaveDebugFile = true;
}
//---------------------------------------------------------------------------

void __fastcall TDebugForm::FormShow(TObject *Sender)
{
    Timer1->Enabled = true;    
}
//---------------------------------------------------------------------------

void __fastcall TDebugForm::Timer1Timer(TObject *Sender)
{   char str [100];

    sprintf (str, "Mem usage: %dK", total_mem_alloced / 1024);
    MemUsageLabel->Caption = str;

}
//---------------------------------------------------------------------------

void __fastcall TDebugForm::FormHide(TObject *Sender)
{
    Timer1->Enabled = false;
}
//---------------------------------------------------------------------------



void __fastcall TDebugForm::RegViewButtonClick(TObject *Sender)
{
    RegViewer->Show ();
}
//---------------------------------------------------------------------------

