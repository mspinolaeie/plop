//---------------------------------------------------------------------------
#ifndef GraphOptionsH
#define GraphOptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <stdio.h>
#include <ExtCtrls.hpp>


//---------------------------------------------------------------------------
class TGraphOptionsForm : public TForm
{
__published:	// IDE-managed Components
    TButton *OKButton;
    TButton *CancelButton;
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TEdit *NumColorEdit;
    TEdit *NumContourEdit;
    TEdit *ZAxisEdit;
    TEdit *ContourSpaceEdit;
    void __fastcall OKButtonClick(TObject *Sender);
    void __fastcall CancelButtonClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    
    
    
private:	// User declarations
public:		// User declarations
    __fastcall TGraphOptionsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGraphOptionsForm *GraphOptionsForm;
//---------------------------------------------------------------------------
#endif
