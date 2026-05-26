//---------------------------------------------------------------------------
#ifndef RunH
#define RunH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>

#include "Picture.h"
#include "PlopExec.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TRunForm : public TForm
{
__published:	// IDE-managed Components
    TPageControl *OptionsPageControl;
    TTabSheet *RunOptionsTabSheet;
    TCheckBox *UpdateCellCheckBox;
    TMainMenu *MainMenu1;
    TMenuItem *Windows1;
    TMenuItem *MeshMenuItem;
    TMenuItem *SupportsMenuItem;
    TMenuItem *ContourMenuItem;
    TMenuItem *ColorPlotMenuItem;
    TBevel *Bevel1;
    TLabel *Label3;
    TEdit *ErrPVVisEdit;
    TLabel *Label4;
    TEdit *ErrRMSVisEdit;
    TCheckBox *RefocusCheckBox;
    TCheckBox *PVCheckBox;
    TTabSheet *TabSheet2;
    TLabel *Label5;
    TEdit *MonteNumEdit;
    TOpenDialog *TraceOpenDialog;
    TLabel *Label1;
    TLabel *Label2;
    TEdit *NumOptEdit;
    TEdit *OptStepEdit;
    TProgressBar *SolverProgressBar;
    TLabel *Label8;
    TGroupBox *GroupBox2;
    TLabel *Label10;
    TLabel *Label6;
    TLabel *Label7;
    TEdit *MonteNumDoneEdit;
    TEdit *MonteMaxEdit;
    TEdit *MonteAvgEdit;
    TCheckBox *RefocusXYRCheckBox;
    TTabSheet *TabSheet3;
    TCheckBox *ZernikeCheckBox;
    TEdit *ZernikeOrderEdit;
    TLabel *Label12;
    TListBox *ZernikeListBox;
    TButton *SaveButton;
    TOpenDialog *ZernikeOpenDialog;
    TLabel *Label13;
    TEdit *RefocusFocalEdit;
    TMenuItem *CellPartsMenuItem;
    TMenuItem *DimensionsMenuItem;
	TCheckBox *UseBasisCheckBox;
	TGroupBox *GroupBox3;
	TButton *StartButton;
	TButton *PauseButton;
	TButton *ResumeButton;
	TButton *AbortButton;
	TGroupBox *GroupBox4;
	TButton *RunZ88Button;
	TTabSheet *Trace;
	TGroupBox *GroupBox1;
	TCheckBox *SaveOutputCheckBox;
	TComboBox *SaveOutputComboBox;
	TButton *SaveOutputButton;
	TCheckBox *OptTraceCheckBox;
	TCheckBox *GenZ88InputCheckBox;
	TMenuItem *QuadsMenuItem;
	TMenuItem *Z88ColorMenuItem;
	TEdit *ErrZ88PVEdit;
	TEdit *ErrZ88RMSEdit;
	TLabel *Label9;
	TLabel *Label11;
    void __fastcall MeshMenuItemClick(TObject *Sender);
    void __fastcall SupportsMenuItemClick(TObject *Sender);
    void __fastcall ContourMenuItemClick(TObject *Sender);
    void __fastcall ColorPlotMenuItemClick(TObject *Sender);
    void __fastcall StartButtonClick(TObject *Sender);
    void __fastcall UpdateCellCheckBoxClick(TObject *Sender);
    void __fastcall SaveOutputButtonClick(TObject *Sender);
    void __fastcall UpdateError (void);
	void __fastcall UpdateZ88Error(void);
	void __fastcall UpdateOptStatus(void);
    void __fastcall ExecFinished (void);
    void __fastcall UpdateStatus (int n);
    void __fastcall UpdateMonte (int ntests, double avgerr, double maxerr);
    void __fastcall UpdateMonteSync (void);
    void __fastcall UpdatePics (void);

    void __fastcall PauseButtonClick(TObject *Sender);
    void __fastcall ResumeButtonClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall AbortButtonClick(TObject *Sender);
    void __fastcall RefocusCheckBoxClick(TObject *Sender);
    void __fastcall SaveButtonClick(TObject *Sender);
    void __fastcall CellPartsMenuItemClick(TObject *Sender);
    void __fastcall DimensionsMenuItemClick(TObject *Sender);
	void __fastcall QuadsMenuItemClick(TObject *Sender);
	void __fastcall RunZ88ButtonClick(TObject *Sender);
	void __fastcall Z88ColorMenuItemClick(TObject *Sender);

private:	// User declarations
    bool UpdateDisplay;

public:		// User declarations
    bool HaveOutput;
    int n_opt_evals;
    int n_montes;
    double monte_avg_err;
    double monte_max_err;
    double last_opt_step;
    PlopExec *ExecThread;
	__fastcall TRunForm(TComponent* Owner);

	};
//---------------------------------------------------------------------------
extern PACKAGE TRunForm *RunForm;
//---------------------------------------------------------------------------
#endif
