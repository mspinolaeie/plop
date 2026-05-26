//---------------------------------------------------------------------------
#ifndef MeshEditH
#define MeshEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <syncobjs.hpp>
#include "NumEdit.h"
#include "Picture.h"

//#include <vcl\Registry.hpp>
#include <system.win.registry.hpp>



#define MeshEditNumVarScroll    7
#define MeshEditNumMeshScroll   2

#define MeshEditGroupBoxSpace   10

#define MaxFileStrings          9



typedef int PlopException;

extern void set_max_points (int);

extern void read_info (char *);
extern void read_info_chars (void);

extern void write_info (char *, int, int);
extern void write_info_chars (int, int);

extern int gcd (int x, int y);

extern void var_def_str (var_def *, char *);
extern int parm_name_index (const char *pname);
extern void init_gr_info (void);
extern int parse_var_def_line (int v_index, char *line);
extern int get_var (const char *n, int addit, int must_exist, const char *line);
extern void getwords (
	char *line,
	char wordtable [maxwords] [wordlen],
	int *wordsfound,
	int wtabsize);
    
extern void init_plop (void);

extern void init_graphics (void); /* used to store some error calculation info */

extern void alloc_globals (void);
extern void alloc_plate_globals (void);

extern char CurrentVersion [];






//---------------------------------------------------------------------------



#include "PlopInterface.h"

typedef double ScanSetVals [max_scan_set];


//---------------------------------------------------------------------------
class TCellEditForm : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *FileItems;
    TMenuItem *FileOpenItem;
    TMenuItem *FileSaveItem;
    TMenuItem *FileSaveAsItem;
    TMenuItem *RunItems;
    TMenuItem *HelpItems;
    TMenuItem *HelpHelpItem;
    TMenuItem *HelpAboutItem;
    TMenuItem *RunPlopItem;
    TPageControl *CellPageControl;
    TTabSheet *MirrorTabSheet;
    TTabSheet *TabSheet2;
    TGroupBox *MaterialsGroupBox;
    TTabSheet *TabSheet3;
    TTabSheet *BasisTabSheet;
    TLabel *Label8;
    TScrollBox *BasisScrollBox;
    TTabSheet *VarTabSheet;
    TOpenDialog *OpenDialog1;
    TGroupBox *GroupBox4;
    TGroupBox *AutoCellGroupBox;
    TLabel *Label5;
    TLabel *Label6;
    TButton *AutoCellButton;
    TBevel *Bevel1;
    TGroupBox *GroupBox3;
    TButton *AutoBasisButton;
    TLabel *Label9;
    TGroupBox *FocalGroupBox;
    TRadioGroup *FocalRadioGroup;
    TGroupBox *DiamGroupBox;
    TTabSheet *HoleTabSheet;
    TPanel *Panel1;
    TSaveDialog *SaveDialog1;
    TGroupBox *ObsGroupBox;
    TRadioGroup *ObsRadioGroup;
    TPanel *Panel2;
    TGroupBox *HoleGroupBox;
    TRadioGroup *HoleRadioGroup;
    TMenuItem *ExitPlop;
    TTabSheet *CommentsTabSheet;
    TMemo *CommentsMemo;
    TPopupMenu *VarPopupMenu;
    TMenuItem *VarDuplicate;
    TMenuItem *VarAdd;
    TMenuItem *VarDelete;
    TPanel *VarScrollPanel;
    TScrollBar *VarScrollBar;
    TTabSheet *CellTypeTabSheet;
    TLabel *Label1;
    TGroupBox *GroupBox1;
    TPanel *Panel3;
    TCheckBox *EqualForceCheckBox;
    TLabel *Label3;
    TEdit *NumSupportRingEdit;
    TRadioGroup *SupportRadioGroup;
    TPanel *CellScrollPanel;
    TScrollBar *CellEditScrollBar;
    TPanel *Panel4;
    TPanel *Panel5;
    TMenuItem *VarInsert;
    TPopupMenu *CellPopupMenu;
    TMenuItem *MeshAdd;
    TMenuItem *MeshInsert;
    TMenuItem *MeshDuplicate;
    TMenuItem *MeshDelete;
    TEdit *NumBasisEdit;
    TButton *NumBasisUpdateButton;
    TLabel *Label2;
    TEdit *NumMeshRingEdit;
    TCheckBox *VarAngleCheckBox;
    TMenuItem *VarCopy;
    TMenuItem *VarPaste;
    TButton *NumSupportButton;
    TMenuItem *MeshCopy;
    TMenuItem *MeshPaste;
    TTabSheet *TextTabSheet;
    TMemo *EditAsTextMemo;
    TComboBox *MaterialComboBox;
    TLabel *Label4;
    TLabel *Label10;
    TMenuItem *GraphicPlots1;
    TMenuItem *MeshMenuItem;
    TMenuItem *SupportsMenuItem;
    TMenuItem *ContourMenuItem;
    TMenuItem *ColourPlotMenuItem;
    TTabSheet *CellPartsTabSheet;
    TPanel *CellPartPanel;
    TScrollBar *CellPartScrollBar;
    TEdit *PartNumEdit;
    TLabel *Label13;
    TButton *PartNumUpdateButton;
    TGroupBox *PartNumGroupBox;
    TComboBox *PartTypeComboBox;
    TLabel *Label11;
    TEdit *PartRingNumEdit1;
    TLabel *PartPointNumLabel1;
    TEdit *PartPointEdit1;
    TEdit *PartRingNumEdit2;
    TLabel *PartPointNumLabel2;
    TEdit *PartPointEdit2;
    TEdit *PartRingNumEdit3;
    TLabel *PartPointNumLabel3;
    TEdit *PartPointEdit3;
    TComboBox *PartPointTypeComboBox1;
    TComboBox *PartPointTypeComboBox2;
    TComboBox *PartPointTypeComboBox3;
    TLabel *Label12;
    TEdit *PartQuantityEdit;
    TMenuItem *CellPartsMenuItem;
    TMenuItem *DimensionsMenuItem;
    TMenuItem *FileSeparatorItem;
    TCheckBox *WarpSphereCheckBox;
	TLabel *Label14;
	TEdit *NumMeshDepthEdit;
	TMenuItem *QuadsMenuItem;
	TMenuItem *Z88ColorMenuItem;
	TTabSheet *Z88ParamTabSheet;
	TRadioGroup *OffAxisRadioGroup;
	TMenuItem *WhatsNewMenuItem;
    void __fastcall AutoCellButtonClick(TObject *Sender);
    void __fastcall HelpAboutItemClick(TObject *Sender);
    void __fastcall FileOpenItemClick(TObject *Sender);
    void __fastcall RunPlopItemClick(TObject *Sender);
    void __fastcall FileSaveAsItemClick(TObject *Sender);
    void __fastcall VarScrollBarChange(TObject *Sender);
    void __fastcall CellEditScrollBarChange(TObject *Sender);
    void __fastcall GrHasChanged(TObject *Sender);
    void __fastcall LoadFromPlop (void);
    void __fastcall ClearState (void);
    int __fastcall CopyToPlop (bool allow_err);
    void __fastcall AddToPlopMap (const char *pname, NumEdit *ANumEdit,
        int NumToMap, NumEditState *ANumEditState,
        TEdit *AEdit, int ARadioIndex, TRadioGroup *ARadioGroup);
    void __fastcall LoadNumEditStates (
        int NumValues,
        int NumEditMode,
        int *NumEditWhich,
        int *NumEditIndex,
        int *NumEditIsVar,
        double *NumEditFrom,
        double *NumEditTo,
        int *NumEditBy,
        int *NumEditSetNum,
        ScanSetVals *NumEditSetVals);
    int __fastcall StoreNumEditState (
        NumEditState *ANumEditState,
        int IsVar,
        int Which,
        int Index,
        char *err_id,
        bool *allow_err_ptr);
    void __fastcall UpdateFromOpt (void);
    void __fastcall VarScrollBarResize (int NewNumVar);
    void __fastcall NumBasisUpdate(int NewNumBasis);
    void __fastcall NumBasisUpdateButtonClick(TObject *Sender);
    void __fastcall CellEditScrollBarResize (int NewNumCell);
    void __fastcall CellPartScrollBarResize (int NewNumParts, TObject *Sender);
    void __fastcall FileSaveItemClick(TObject *Sender);
    void __fastcall ExitPlopClick(TObject *Sender);
    void __fastcall EqualForceCheckBoxClick(TObject *Sender);
    void __fastcall VarAngleCheckBoxClick(TObject *Sender);
    void __fastcall VarInsertClick(TObject *Sender);
    void __fastcall VarDeleteClick(TObject *Sender);
    void __fastcall VarDuplicateClick(TObject *Sender);
    void __fastcall VarAddClick(TObject *Sender);
    void __fastcall VarCopyClick(TObject *Sender);
    void __fastcall VarPasteClick(TObject *Sender);
    void __fastcall NumSupportButtonClick(TObject *Sender);
    
    void __fastcall MeshAddClick(TObject *Sender);
    void __fastcall AutoBasisButtonClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall MeshDeleteClick(TObject *Sender);
    
    void __fastcall MeshCopyClick(TObject *Sender);
    void __fastcall MeshPasteClick(TObject *Sender);
    void __fastcall MeshDuplicateClick(TObject *Sender);
    void __fastcall MeshInsertClick(TObject *Sender);
    void __fastcall TextTabSheetShow(TObject *Sender);
    void __fastcall TextTabSheetHide(TObject *Sender);
    void __fastcall SaveTextTabSheet (void);
    void __fastcall HelpHelpItemClick(TObject *Sender);
    void __fastcall CommentsMemoChange(TObject *Sender);
    void __fastcall NumSupportRingEditChange(TObject *Sender);
    void __fastcall NumBasisEditChange(TObject *Sender);

    void __fastcall BasisTabSheetShow(TObject *Sender);
    void __fastcall BasisTabSheetHide(TObject *Sender);
    void __fastcall CellTypeTabSheetShow(TObject *Sender);
    void __fastcall CellTypeTabSheetHide(TObject *Sender);
    void __fastcall ProcessMessage (TMsg &Message, bool &handled);
    void __fastcall MaterialComboBoxChange(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
	void __fastcall MeshMenuItemClick(TObject *Sender);
    void __fastcall SupportsMenuItemClick(TObject *Sender);
    void __fastcall ContourMenuItemClick(TObject *Sender);
    void __fastcall ColourPlotMenuItemClick(TObject *Sender);
    void __fastcall PartNumUpdateButtonClick(TObject *Sender);
    void __fastcall CellPartScrollBarChange(TObject *Sender);
    void __fastcall CellPartsMenuItemClick(TObject *Sender);
    void __fastcall CellPartsSaveCurrentItem (void);
	void __fastcall DimensionsMenuItemClick(TObject *Sender);
	char * __fastcall GetCompileDate (void);
	void __fastcall QuadsMenuItemClick(TObject *Sender);
	void __fastcall Z88ColorMenuItemClick(TObject *Sender);
	void __fastcall WhatsNewMenuItemClick(TObject *Sender);
	bool __fastcall IsFirstRun (void);

public:	// User declarations

    char *DebugMsgs;
    char *DebugMsgsNext;
    TCriticalSection *PlopDataCrit;
    AnsiString GrOpenFile;
    bool FileIsChanged;

    bool PlopRunningFlag;       /* prevent mucking up data if running */
    bool TextIsValid;

	char start_locale [100];
	char run_locale [100];

	char compile_date [100];

    AnsiString AutoCellLoc;
    AnsiString HelpFileLoc;
    AnsiString PlopLoc;
	AnsiString LastVersionRun;
	
    TRegistry *Reg;

    TStringList *FileNameStrings;
    int NumFileNameStrings;
    TMenuItem *SeparatorItem;
    TMenuItem *FileNameItems [MaxFileStrings];

    // data for support rings
    TGroupBox *CellScrollGroupBoxes [MeshEditNumMeshScroll];
    TLabel *CellSupportLabels [MeshEditNumMeshScroll];
    VarNameEdit *CellNumSupportEdits [MeshEditNumMeshScroll];
    NumEdit *SupportRadiiNumEdit [MeshEditNumMeshScroll];
    NumEdit *SupportAngleNumEdit [MeshEditNumMeshScroll];
    NumEdit *SupportRelForceNumEdit [MeshEditNumMeshScroll];

    AnsiString CellNumSupportStrings [max_mesh_radii];
    NumEditState SupportRadiiState [max_mesh_radii];
    NumEditState SupportAngleState [max_mesh_radii];
    NumEditState SupportRelForceState [max_mesh_radii];

    AnsiString CopyCellNumSupportString;
    NumEditState CopySupportRadiiState;
    NumEditState CopySupportAngleState;
    NumEditState CopySupportRelForceState;
    int NumSupportRing;
    bool NumSupportRingChanged;
    int ActiveSupportId;

    // data for variables

    NumEditState VarEdit [max_variables];
    AnsiString VarNames [max_variables];
    NumEdit *VarScrollNumEdit [MeshEditNumVarScroll];
    VarNameEdit *VarScrollNameEdit [MeshEditNumVarScroll];
    TLabel *VarScrollNameLabels [MeshEditNumVarScroll];
    int NumVarEdit;
    int ActiveVarId;
    NumEditState CopyVarEdit;
    AnsiString CopyVarName;


    // data for basis rings
    int NumBasis;
    bool NumBasisChanged;
    TLabel *BasisNumLabels [max_basis_size];
    TEdit *BasisNumEdits [max_basis_size];
    TLabel *BasisRingLabels [max_basis_size];
    TEdit *BasisRingEdits [max_basis_size];

    // other general parameters

	int NumMeshRing;
	int NumMeshDepth;

	double MirrorTiltAngle;
	double SlingIncludedAngle;

    
    NumEdit *DiamNumEdit;
    NumEditState DiamNumState;
    
    NumEdit *ThickNumEdit;
    NumEditState ThickNumState;
    
    NumEdit *FocalNumEdit;
    NumEditState FocalNumState;
    
    NumEdit *ObsNumEdit;
    NumEditState ObsNumState;
    
    NumEdit *HoleNumEdit;
    NumEditState HoleNumState;
    
    NumEdit *ModulusNumEdit;
    NumEditState ModulusNumState;
    
    NumEdit *PoissonNumEdit;
    NumEditState PoissonNumState;

    NumEdit *DensityNumEdit;
    NumEditState DensityNumState;

	NumEdit *MirrorTiltEdit;
	NumEditState MirrorTiltState;

	NumEdit *SlingIncludedAngleEdit;
	NumEditState SlingIncludedAngleState;


    PlopDataMap PlopMap [max_parm_names];

    // Data for parts

    int PartScrollLastPosition;
    int PartNumParts;
    int PartType [max_parts];
    AnsiString PartQuantityText [max_parts];
    int PartPointType [max_parts] [tri_pts];
    AnsiString PartPointRingNumText [max_parts] [tri_pts];
    AnsiString PartPointPointNumText [max_parts] [tri_pts];



public:		// User declarations
    __fastcall TCellEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCellEditForm *CellEditForm;
//---------------------------------------------------------------------------
extern parm_descr parm_list [];

#endif
