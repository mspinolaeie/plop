//---------------------------------------------------------------------------
#ifndef NumEditH
#define NumEditH

#include "TCEdit.h"
//---------------------------------------------------------------------------

#define NumEditFixed    0
#define NumEditOpt      1
#define NumEditScanVar  2
#define NumEditScanSet  3
#define NumEditMonte    4

#define NumEditVPitch   40
#define NumEditVSpace   20

class NumEdit;

class NumEditCombo : public TComboBox
{
private:
    NumEdit *MyEdit;
public:
    int *IdPtr;
    __fastcall NumEditCombo (TComponent *AOwner,
        TWinControl *AParent, NumEdit *ANumEdit);
    void __fastcall NumEditChanged (TObject *Sender);
    void __fastcall Entered (TObject *Sender);
    void __fastcall Exited (TObject *Sender);
};

class VarNameEdit: public TCEdit
{
private:
public:
    AnsiString *MyString;
    __fastcall VarNameEdit (TComponent *AOwner,
        TWinControl *AParent, AnsiString *AString);
    void __fastcall VarNameChanged (TObject *Sender);
    void __fastcall Entered (TObject *Sender);
    void __fastcall Exited (TObject *Sender);
};

class NumEditState {
public:
    AnsiString NELabel;
    AnsiString NEValue;
    int NEMode;
    AnsiString NEFrom;
    AnsiString NETo;
    AnsiString NEBy;

    void __fastcall Clear (void);

};

class NumEdit
{
public:
	int MyLeft;
	int MyLeftExtra;
    TLabel *NumEditLabel;
	TCEdit *NumEditValue;
    NumEditCombo *NumEditModeBox;
    TLabel *NumEditScanLabel;
    TLabel *NumEditToLabel;
    TLabel *NumEditByLabel;
    TCEdit *NumEditRangeFrom;
    TCEdit *NumEditRangeTo;
    TCEdit *NumEditRangeBy;
private:
    int NumEditMode;
    void __fastcall SetMode (int NewMode);
    int __fastcall GetMode ();
    void __fastcall SetVisible (bool NewVisible);
public:
    NumEditState *MyState;
    __fastcall NumEdit(TComponent *AOwner, TWinControl *AParent,
    const char *Name, int Top, int Left, int TextSpace);
    int __property NumMode = {read=GetMode,write=SetMode};
    bool __property Visible = {write=SetVisible};
    void __fastcall NumEditLoad (NumEditState *NEState);
    void __fastcall NumEditSave (NumEditState *NEState);
    void __fastcall NumEditSaveState (TObject *Sender);
    void __fastcall SetIdTag (int Id, int *IdPtr);
};

#endif

