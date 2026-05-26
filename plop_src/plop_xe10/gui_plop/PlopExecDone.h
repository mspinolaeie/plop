//---------------------------------------------------------------------------
#ifndef PlopExecDoneH
#define PlopExecDoneH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TRunFinishedForm : public TForm
{
__published:	// IDE-managed Components
    TButton *OKButton;
    TBevel *Bevel1;
    TBevel *Bevel2;
    TLabel *Label1;
    void __fastcall OKButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TRunFinishedForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRunFinishedForm *RunFinishedForm;
//---------------------------------------------------------------------------
#endif
