//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "NumEdit.h"
#include "MeshEdit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall NumEditCombo::NumEditCombo (TComponent *AOwner,
    TWinControl *AParent, NumEdit *ANumEdit) : TComboBox (AOwner)
{   Parent = AParent;
    MyEdit = ANumEdit;
    OnChange = NumEditChanged;
    OnEnter = Entered;
    OnExit = Exited;
}
__fastcall VarNameEdit::VarNameEdit (TComponent *AOwner,
    TWinControl *AParent, AnsiString *AString) : TCEdit (AOwner)
{   Parent = AParent;
    MyString = AString;
    OnChange = VarNameChanged;
    OnEnter = Entered;
    OnExit = Exited;
}

//---------------------------------------------------------------------------

void __fastcall VarNameEdit::Entered (TObject *Sender)
{   if (IdPtr != NULL && Tag != -1)
        *IdPtr = Tag;
}

//---------------------------------------------------------------------------

void __fastcall VarNameEdit::Exited (TObject *Sender)
{   if (IdPtr != NULL && Tag != -1)
        *IdPtr = -1;
}
//---------------------------------------------------------------------------

void __fastcall NumEditCombo::Entered (TObject *Sender)
{   if (IdPtr != NULL && Tag != -1)
        *IdPtr = Tag;
}

//---------------------------------------------------------------------------

void __fastcall NumEditCombo::Exited (TObject *Sender)
{   if (IdPtr != NULL && Tag != -1)
        *IdPtr = -1;
}

//---------------------------------------------------------------------------


__fastcall NumEdit::NumEdit (TComponent *AOwner, TWinControl *AParent,
	 const char *Name, int Top, int Left, int TextSpace)
{
    NumEditMode = NumEditFixed;
	MyLeft = Left;
	MyLeftExtra = Left + TextSpace + 100;

    NumEditLabel = new TLabel (AOwner);
    NumEditLabel->Parent = AParent;
    NumEditLabel->Caption = Name;
    NumEditLabel->Left = Left;
    NumEditLabel->Top = Top + 4;

    NumEditValue = new TCEdit (AOwner);
    NumEditValue->Parent = AParent;
    NumEditValue->Width = 70;
	NumEditValue->Left = Left + TextSpace;
	NumEditValue->Top = Top;

    NumEditModeBox = new NumEditCombo (AOwner, AParent, this);
    NumEditModeBox->Parent = AParent;
	NumEditModeBox->Width = 100;
	MyLeftExtra = Left + TextSpace + NumEditModeBox->Width;
	NumEditModeBox->Left = Left + TextSpace + 90;
    NumEditModeBox->Top = Top;
    NumEditModeBox->Style = csDropDownList;
    NumEditModeBox->Items->Insert (0, "Fixed");
    NumEditModeBox->Items->Insert (1, "Optimize");
    NumEditModeBox->Items->Insert (2, "Scan range");
    NumEditModeBox->Items->Insert (3, "Scan set");
    NumEditModeBox->Items->Insert (4, "Monte Carlo");
    NumEditModeBox->ItemIndex = 0;

    NumEditScanLabel = new TLabel (AOwner);
	NumEditScanLabel->Parent = AParent;
    NumEditScanLabel->Caption = "From";
	NumEditScanLabel->Left = MyLeftExtra + 110;
	NumEditScanLabel->Top = Top + 4;

	NumEditToLabel = new TLabel (AOwner);
	NumEditToLabel->Parent = AParent;
	NumEditToLabel->Caption = "To";
	NumEditToLabel->Left = MyLeftExtra + 280;
	NumEditToLabel->Top = Top + 4;

    NumEditByLabel = new TLabel (AOwner);
    NumEditByLabel->Parent = AParent;
	NumEditByLabel->Caption = "Num Steps";
	NumEditByLabel->Left = MyLeftExtra + 400;
    NumEditByLabel->Top = Top + 4;


    NumEditRangeFrom = new TCEdit (AOwner);
    NumEditRangeFrom->Parent = AParent;
    NumEditRangeFrom->Width = 70;
	NumEditRangeFrom->Left = MyLeftExtra + 190;
	NumEditRangeFrom->Top = Top;

	NumEditRangeTo = new TCEdit (AOwner);
	NumEditRangeTo->Parent = AParent;
	NumEditRangeTo->Width = 70;
	NumEditRangeTo->Left = MyLeftExtra + 310;
	NumEditRangeTo->Top = Top;

	NumEditRangeBy = new TCEdit (AOwner);
	NumEditRangeBy->Parent = AParent;
	NumEditRangeBy->Width = 70;
	NumEditRangeBy->Left = MyLeftExtra + 480;
    NumEditRangeBy->Top = Top;

    NumMode = NumEditFixed;

    NumEditValue->OnChange = NumEditSaveState;
    NumEditRangeFrom->OnChange = NumEditSaveState;
    NumEditRangeTo->OnChange = NumEditSaveState;
    NumEditRangeBy->OnChange = NumEditSaveState;

}

void __fastcall NumEdit::SetIdTag (int Id, int *AIdPtr)
{   NumEditValue->Tag = Id;
    NumEditValue->IdPtr = AIdPtr;

    NumEditRangeFrom->Tag = Id;
    NumEditRangeFrom->IdPtr = AIdPtr;

    NumEditRangeTo->Tag = Id;
    NumEditRangeTo->IdPtr = AIdPtr;

    NumEditRangeBy->Tag = Id;
    NumEditRangeBy->IdPtr = AIdPtr;

    NumEditModeBox->Tag = Id;
    NumEditModeBox->IdPtr = AIdPtr;
}

void __fastcall NumEditCombo::NumEditChanged (TObject *Sender)
{   MyEdit->NumMode = ItemIndex;
    MyEdit->NumEditSaveState (Sender);
}

int __fastcall NumEdit::GetMode (void)
{   return (NumEditMode);
}

void __fastcall NumEditState::Clear (void)
{   NEValue = "";
    NEFrom = "";
    NETo = "";
    NEBy = "";
    NEMode = NumEditFixed;
}

void __fastcall NumEdit::SetMode (int NewMode)
{   NumEditMode = NewMode;
    NumEditModeBox->ItemIndex = NewMode;
    NumEditLabel->Visible = true;
    NumEditValue->Visible = true;
    NumEditModeBox->Visible = true;
    switch (NumEditMode)
    {   case NumEditFixed:
			NumEditScanLabel->Visible = false;
            NumEditToLabel->Visible = false;
            NumEditByLabel->Visible = false;
            NumEditRangeFrom->Visible = false;
            NumEditRangeTo->Visible = false;
            NumEditRangeBy->Visible = false;
            break;

        case NumEditOpt:
        case NumEditMonte:
            if (NumEditMode == NumEditOpt)
                NumEditScanLabel->Caption = "Step size";
            else
                NumEditScanLabel->Caption = "Variation";
			NumEditScanLabel->Visible = true;
			NumEditScanLabel->Left = MyLeftExtra + 110;
			NumEditRangeFrom->Left = MyLeftExtra + 190;
            NumEditRangeFrom->Width = 70;
            NumEditRangeFrom->Visible = true;
            NumEditToLabel->Visible = false;
            NumEditByLabel->Visible = false;
            NumEditRangeTo->Visible = false;
            NumEditRangeBy->Visible = false;
            break;

        case NumEditScanVar:
            NumEditScanLabel->Caption = "From";
			NumEditScanLabel->Left = MyLeftExtra + 110;
			NumEditScanLabel->Visible = true;
            NumEditToLabel->Caption = "To";
			NumEditToLabel->Left = MyLeftExtra + 280;
            NumEditToLabel->Visible = true;
			NumEditByLabel->Caption = "Num steps";
			NumEditByLabel->Left = MyLeftExtra + 400;
            NumEditByLabel->Visible = true;
			NumEditRangeFrom->Left = MyLeftExtra + 190;
			NumEditRangeFrom->Width = 70;
            NumEditRangeFrom->Visible = true;
			NumEditRangeTo->Left = MyLeftExtra + 310;
            NumEditRangeTo->Visible = true;
			NumEditRangeBy->Left = MyLeftExtra + 480;
            NumEditRangeBy->Visible = true;
            break;

        case NumEditScanSet:
            NumEditScanLabel->Caption = "Values";
            NumEditScanLabel->Visible = true;
			NumEditRangeFrom->Left = MyLeftExtra + 190;
            NumEditRangeFrom->Width = 290;
            NumEditRangeFrom->Visible = true;
            NumEditToLabel->Visible = false;
            NumEditByLabel->Visible = false;
            NumEditRangeTo->Visible = false;
            NumEditRangeBy->Visible = false;
            break;

    }
}

void __fastcall NumEdit::SetVisible (bool NewVisible)
{   if (NewVisible)
        NumMode = NumEditMode;
    else
    {   NumEditLabel->Visible = false;
        NumEditValue->Visible = false;
        NumEditModeBox->Visible = false;
        NumEditScanLabel->Visible = false;
        NumEditToLabel->Visible = false;
        NumEditByLabel->Visible = false;
        NumEditRangeFrom->Visible = false;
        NumEditRangeTo->Visible = false;
        NumEditRangeBy->Visible = false;
    }
}

void __fastcall NumEdit::NumEditLoad (NumEditState *NEState)
{   NumEditState *NES;

    // preserve MyState so changes don't overwrite it if it is same as NEState
    
    NES = MyState;
    MyState = NULL;
    NumEditLabel->Caption = NEState->NELabel;
    NumEditValue->Text = NEState->NEValue;
    NumEditRangeFrom->Text = NEState->NEFrom;
    NumEditRangeTo->Text = NEState->NETo;
    NumEditRangeBy->Text = NEState->NEBy;
    NumMode = NEState->NEMode;
    MyState = NES;
}

void __fastcall NumEdit::NumEditSave (NumEditState *NEState)
{    NEState->NELabel = NumEditLabel->Caption;
     NEState->NEValue = NumEditValue->Text;
     NEState->NEFrom = NumEditRangeFrom->Text;
     NEState->NETo = NumEditRangeTo->Text;
     NEState->NEBy = NumEditRangeBy->Text;
     NEState->NEMode = NumMode;
}

void __fastcall NumEdit::NumEditSaveState (TObject *Sender)
{   if (MyState != NULL)
        NumEditSave (MyState);
    CellEditForm->GrHasChanged (Sender);

}

void __fastcall VarNameEdit::VarNameChanged (TObject *Sender)
{   if (MyString != NULL)
        *MyString = Text;
}



