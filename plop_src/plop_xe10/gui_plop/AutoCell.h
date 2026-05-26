//---------------------------------------------------------------------------
#ifndef AutoCellH
#define AutoCellH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <checklst.hpp>
//---------------------------------------------------------------------------
extern void read_info (char *);


class TAutoCellForm : public TForm
{
__published:	// IDE-managed Components
    TButton *RightButton;
    TButton *MiddleButton;
    TButton *LeftButton;
    TPanel *CellTypePanel;
    TRadioGroup *CellPointsRadioGroup;
    TCheckBox *ForceCheckBox;
    TCheckBox *AngleCheckBox;
    TPanel *Panel1;
    TLabel *Label1;
    TLabel *Label2;
    TPanel *MirrorSizePanel;
    TLabel *Label4;
    TLabel *Label5;
    TEdit *DiamEdit;
    TEdit *ThickEdit;
    TLabel *Label6;
    TEdit *FocalEdit;
    TLabel *Label8;
    TEdit *SecEdit;
    TLabel *Label9;
	TEdit *HoleEdit;
	TLabel *Label3;
    void __fastcall RightButtonClick(TObject *Sender);
    
    
    void __fastcall LeftButtonClick(TObject *Sender);
    void __fastcall MiddleButtonClick(TObject *Sender);
private:	// User declarations
    int ActivePanel;
public:		// User declarations
    __fastcall TAutoCellForm(TComponent* Owner);
};

#define ActivePanelDiam 0
#define ActivePanelCell 1

//---------------------------------------------------------------------------
extern PACKAGE TAutoCellForm *AutoCellForm;
//---------------------------------------------------------------------------
#endif
