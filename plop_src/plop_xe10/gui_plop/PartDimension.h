//---------------------------------------------------------------------------
#ifndef PartDimensionH
#define PartDimensionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include <stdio.h>
#include "global.h"
#include "plot.h"

#include "plop_parms.h"
#include <Dialogs.hpp>
#include <Menus.hpp>

//---------------------------------------------------------------------------
class TPartDimensionForm : public TForm
{
__published:	// IDE-managed Components
    TImage *PicImage;
    TScrollBar *PartNumScrollBar;
    TPanel *Panel1;
    TLabel *PartNumLabel;
    TRadioGroup *DimensionUnitsRadioGroup;
    TButton *RotateButton;
    TPanel *Panel2;
    TLabel *PartCGXLabel;
    TLabel *SupportRadiusLabel;
    TLabel *SupportAngleLabel;
    TLabel *PartCGYLabel;
    TLabel *Label1;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *PicSave;
	TMenuItem *PicOptions;
	TMenuItem *PictureOptions;
	TSaveDialog *SaveDialog1;
	TMenuItem *CopyMenuItem;
    void __fastcall PartNumScrollBarChange(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall RotateButtonClick(TObject *Sender);
	void __fastcall PicSaveClick(TObject *Sender);
	void __fastcall CopyMenuItemClick(TObject *Sender);
private:	// User declarations
    HPALETTE MyPalette;
    LOGPALETTE *MyLogPalette;
    Graphics::TBitmap *MyBits;
    plop_cmap *MyCmap;

public:		// User declarations
    int PictureStyle;
    bool NewPicAvail;
    bool SomePicAvail;
    __fastcall TPartDimensionForm(TComponent* Owner);
    void __fastcall SetPalette(plop_cmap *pcm);
    void __fastcall ClearPic (void);
    void __fastcall DrawPic (void);
    void __fastcall SetNewPicAvail (void);
	void __fastcall SaveAsGif (AnsiString Fname);
};
//---------------------------------------------------------------------------
extern PACKAGE TPartDimensionForm *PartDimensionForm;
//---------------------------------------------------------------------------
#endif
