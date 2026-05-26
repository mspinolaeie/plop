//---------------------------------------------------------------------------

#ifndef WhatsNewH
#define WhatsNewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TWhatsNewForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *OKButton;
	TRichEdit *RichEdit1;
	TLabel *Label1;
	void __fastcall OKButtonClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TWhatsNewForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWhatsNewForm *WhatsNewForm;
//---------------------------------------------------------------------------
#endif
