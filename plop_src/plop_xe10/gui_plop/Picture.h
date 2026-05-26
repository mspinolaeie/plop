//---------------------------------------------------------------------------
#ifndef PictureH
#define PictureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>

#include <stdio.h>
#include "global.h"
#include "plot.h"
#include "plop_parms.h"
#include <Dialogs.hpp>


#define PicStyleMesh        0
#define PicStyleSupports    1
#define PicStyleColor       2
#define PicStyleContour     3
#define PicStyleParts       4
#define PicStyleQuads		5
#define PicStyleZ88Color	6

extern void polar_to_euc (
	double r,
	double a,
    double *x,
	double *y);

#define num_color_shapes        11
#define z_scale_width			100
//---------------------------------------------------------------------------
class TPictureForm : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *PicSave;
    TMenuItem *PicOptions;
    TMenuItem *PictureOptions;
    TBevel *Bevel1;
    TImage *PicImage;
    TSaveDialog *SaveDialog1;
	TMenuItem *CopyMenuItem;
    void __fastcall PictureOptionsClick(TObject *Sender);
    void __fastcall PicSaveClick(TObject *Sender);
    void __fastcall ShowEvent (TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
	void __fastcall CopyMenuItemClick(TObject *Sender);
private:	// User declarations
    HPALETTE MyPalette;
    LOGPALETTE *MyLogPalette;
	Graphics::TBitmap *MyBits;

	double pic_z_min, pic_z_max;
	double err_pv, err_rms;


public:		// User declarations
    plop_cmap *MyCmap;
    int PictureStyle;
    bool NewPicAvail;
    bool SomePicAvail;
    __fastcall TPictureForm(TComponent* Owner);
    void __fastcall SetPalette(plop_cmap *pcm);
	void __fastcall DrawMesh (int mesh_flag, int part_flag);
	void __fastcall DrawQuads (int mesh_flag, int part_flag);
    void __fastcall ClearPic (void);
    void __fastcall DrawPic (void);
    void __fastcall SetNewPicAvail (void);
    void __fastcall LoadPlopPic (plop_cmap *pcm);
	void __fastcall SaveAsGif (AnsiString Fname);
	void __fastcall GetZRange (double *z_min, double *z_max, double *err_rms_ptr, double *err_pv_ptr);
	void __fastcall DrawParts (TCanvas * tc, double scale, int pic_y);
	void __fastcall DrawPoints (TCanvas *tc, double scale, int pic_y);
	void __fastcall DrawZLabels(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TPictureForm *PictureForm;
//---------------------------------------------------------------------------
#endif
