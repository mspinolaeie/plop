//---------------------------------------------------------------------------
#ifndef DebugH
#define DebugH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include <stdio.h>
#include "plop_debug.h"
//---------------------------------------------------------------------------
class TDebugForm : public TForm
{
__published:	// IDE-managed Components
    TMemo *DebugMemo;
    TButton *UpdateTraceButton;
    TCheckBox *DebugCheckBox;
    TPanel *DebugPanel;
    TButton *SetButton;
    TButton *ClearButton;
    TEdit *FileEdit;
    TButton *DebugFileButton;
    TTimer *Timer1;
    TLabel *MemUsageLabel;
	TButton *RegViewButton;
    void __fastcall UpdateTraceButtonClick(TObject *Sender);
    void __fastcall DebugCheckBoxClick(TObject *Sender);
    void __fastcall SetMsg (char *msg);

    void __fastcall FormCreate(TObject *Sender);
    void __fastcall SetButtonClick(TObject *Sender);
    void __fastcall ClearButtonClick(TObject *Sender);
    void __fastcall UpdateDebugBoxes(TObject *Sender);

    void __fastcall DebugFileButtonClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormHide(TObject *Sender);
	void __fastcall RegViewButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TDebugForm(TComponent* Owner);
    TCheckBox *DebugBoxes [ndebugs];
    int NDebugBox;
    bool HaveDebugFile;
};
//---------------------------------------------------------------------------
extern PACKAGE TDebugForm *DebugForm;
//---------------------------------------------------------------------------

extern void DebugMsg (const char *m);

extern bool DebugEnabled;
#endif
  