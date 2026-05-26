//---------------------------------------------------------------------------

#ifndef RegViewH
#define RegViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//#include <vcl\Registry.hpp>
#include <System.Win.Registry.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TRegViewer : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit1;
	TRadioGroup *RadioGroup1;
	TButton *Button1;
	TButton *Button2;
	TEdit *Edit3;
	TListBox *ListBox1;
	TStringGrid *StringGrid1;
	TButton *Button3;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall ListBox1DblClick(TObject *Sender);
private:	// User declarations
	TRegistry *Reg;
	TStringList *Keys;
	TStringList *ValueNames;
    TStringList *Values;
public:		// User declarations
	__fastcall TRegViewer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRegViewer *RegViewer;
//---------------------------------------------------------------------------
#endif
