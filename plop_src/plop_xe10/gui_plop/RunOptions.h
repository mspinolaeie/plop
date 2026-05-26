//---------------------------------------------------------------------------
#ifndef RunOptionsH
#define RunOptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TRunOptionsForm : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TRunOptionsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRunOptionsForm *RunOptionsForm;
//---------------------------------------------------------------------------
#endif
