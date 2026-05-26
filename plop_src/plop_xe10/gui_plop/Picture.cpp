//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <Clipbrd.hpp>

#include "Picture.h"
#include "GraphOptions.h"

#define my_max(x,y) ((x)>(y)?(x):(y))
#define my_min(x,y) ((x)<(y)?(x):(y))

#include "plot.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPictureForm *PictureForm;

extern void LockPlopData (int);
extern void UnlockPlopData (void);

bool PicStyleHasZ [] = {false, false, true, false, false, false, true};

//---------------------------------------------------------------------------
__fastcall TPictureForm::TPictureForm(TComponent* Owner)
    : TForm(Owner)
{
    PicImage->Picture = new TPicture;
    MyBits = new Graphics::TBitmap;
    MyBits->PixelFormat = pf8bit;
    MyBits->Height = PicImage->Height;
    MyBits->Width = PicImage->Width;

    NewPicAvail = false;
    SomePicAvail = false;

    OnShow = ShowEvent;
}
//---------------------------------------------------------------------------

void __fastcall TPictureForm::SetPalette (plop_cmap *pcm)
{   int i;

    MyLogPalette = (LOGPALETTE *) malloc (sizeof (LOGPALETTE) + pcm->n_colors * sizeof (PALETTEENTRY));
    for (i = 0; i < pcm->n_colors; i++)
    {   MyLogPalette->palPalEntry [i].peRed = pcm->color_r [i];
        MyLogPalette->palPalEntry [i].peGreen = pcm->color_g [i];
        MyLogPalette->palPalEntry [i].peBlue = pcm->color_b [i];
        MyLogPalette->palPalEntry [i].peFlags = 0;
    }
    MyLogPalette->palVersion = 0x300;
    MyLogPalette->palNumEntries = pcm->n_colors;
    MyPalette = CreatePalette (MyLogPalette);
    PicImage->Picture = new TPicture;
    MyBits->Palette = MyPalette;
    PicImage->Picture->Bitmap = MyBits;
    MyCmap = pcm;
}
//---------------------------------------------------------------------------


void __fastcall TPictureForm::ClearPic (void)
{   TCanvas * tc;
    TRect FRect;

    tc = MyBits->Canvas;

    tc->Brush->Color = clWhite;
    tc->Brush->Style = bsSolid;
    FRect = Rect(0, 0, PicImage->Width, PicImage->Height);
    tc->FillRect (FRect);
//    PicImage->Canvas->Draw (0, 0, MyBits);
	PicImage->Picture->Bitmap = MyBits;
}
//---------------------------------------------------------------------------

void __fastcall TPictureForm::DrawParts (TCanvas * tc, double scale, int pic_y)
{	int i;
    int isubpart;
	int j;
    int ncorners;
	double angle;
	double xs, ys;
	double xe, ye;
    double PicCrossSize = 0.015;
    int xsi, ysi;
    int xei, yei;
	TRect FRect;
	char str [100];


	for (i = 0; i < n_parts; i++)
	{	ncorners = part_type_num_corners [part_type [i]];
		for (isubpart = 0; isubpart < part_quantity [i]; isubpart++)
		{   for (j = 0; j < ncorners; j++)
			{	polar_to_euc (part_corner_radius [i] [j],
					part_corner_angle [i] [j] + isubpart * (double) degrees / part_quantity [i],
					&xs, &ys);
				polar_to_euc (part_corner_radius [i] [(j + 1) % ncorners],
					part_corner_angle [i] [(j + 1) % ncorners] + isubpart * (double) degrees / part_quantity [i],
					&xe, &ye);
				xs *= scale;
				ys *= scale;
				xe *= scale;
				ye *= scale;
				xsi = xs + pic_size / 2;
				ysi = ys + pic_size / 2;
				ysi = pic_y - ysi;
				xei = xe + pic_size / 2;
				yei = ye + pic_size / 2;
				yei = pic_y - yei;
				tc->MoveTo (xsi, ysi);
				tc->LineTo (xei, yei);
				sprintf (str, "(%d)", j + 1);
				tc->Font->Color = clBlack;
				tc->TextOut (xsi + 6, ysi - 6, str);
			}
			tc->Pen->Color = clRed;
			polar_to_euc (part_cg_radius [i],
					part_cg_angle [i] + isubpart * (double) degrees / part_quantity [i],
					&xs, &ys);
			xs *= scale;
			ys *= scale;
			xsi = xs + pic_size * (0.5 - PicCrossSize);
			ysi = ys + pic_size * 0.5;
			ysi = pic_y - ysi;
			xei = xs + pic_size * (0.5 + PicCrossSize);
			yei = ys + pic_size * 0.5;
			yei = pic_y - yei;
			tc->MoveTo (xsi, ysi);
			tc->LineTo (xei, yei);
			xsi = xs + pic_size * 0.5;
			ysi = ys + pic_size * (0.5 - PicCrossSize);
			ysi = pic_y - ysi;
			xei = xs + pic_size * 0.5;
			yei = ys + pic_size * (0.5 + PicCrossSize);
			yei = pic_y - yei;
			tc->MoveTo (xsi, ysi);
			tc->LineTo (xei, yei);
			tc->Pen->Color = clBlack;
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TPictureForm::DrawPoints (TCanvas *tc, double scale, int pic_y)
{	int i;
	int isubpart;
	int j;
	int ncorners;
	double angle;
	double xs, ys;
	double xe, ye;
	int xsi, ysi;
	int xei, yei;
	TRect FRect;

	tc->Brush->Style = bsClear;
	for (i = 0; i < n_support_radii; i++)
	{	for (j = 0; j < num_support [i]; j++)
		{	angle = support_angle [i] + j * (double) degrees / num_support [i];
			polar_to_euc (support_radii [i], angle, &xs, &ys);
            xs *= scale;
            ys *= scale;
            xsi = xs + pic_size / 2;
            ysi = ys + pic_size / 2;
            ysi = pic_y - ysi;
            tc->Ellipse (xsi - pic_size / 140 - 1, ysi - pic_size / 140 - 1,
                xsi + pic_size / 140 + 1, ysi + pic_size / 140 + 1); 
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TPictureForm::DrawMesh (
	int mesh_flag,
    int part_flag)
{	int i;
    int isubpart;
	int j;
    int ncorners;
	double scale;
    double angle;
	double xs, ys;
	double xe, ye;
	int xsi, ysi;
    int xei, yei;
    int pic_y;
    TCanvas * tc;
    TRect FRect;

    tc = MyBits->Canvas;

    tc->Brush->Color = clWhite;
    tc->Brush->Style = bsSolid;
    FRect = Rect(0, 0, PicImage->Width, PicImage->Height);
    tc->FillRect (FRect);

    tc->Pen->Style = psSolid;
    tc->Pen->Color = clBlack;

    scale = pic_size * 0.95 / diameter;
    pic_y = PicImage->Height - 1;

    if (mesh_flag)
    {	for (i = 0; i < n_triangles; i++)
        {	for (j = 0; j < tri_pts; j++)
            {	polar_to_euc (point_radius [triangle_points [i] [j]],
                        point_angle [triangle_points [i] [j]], &xs, &ys);
                polar_to_euc (point_radius [triangle_points [i] [(j + 1) %tri_pts]],
                        point_angle [triangle_points [i] [(j + 1) %tri_pts]], &xe, &ye);
                xs *= scale;
                ys *= scale;
                xe *= scale;
                ye *= scale;
                xsi = xs + pic_size / 2;
                ysi = ys + pic_size / 2;
                ysi = pic_y - ysi;
                xei = xe + pic_size / 2;
                yei = ye + pic_size / 2;
                yei = pic_y - yei;
                tc->MoveTo (xsi, ysi);
                tc->LineTo (xei, yei);
            }
        }
    }
    else
    	tc->Ellipse (pic_size * 0.025, pic_y - pic_size * 0.025,
            pic_size * 0.975, pic_y - pic_size * 0.975);
    if (part_flag)
	{	DrawParts (tc, scale, pic_y);
	}
	DrawPoints (tc, scale, pic_y);
	//    PicImage->Canvas->Draw (0, 0, MyBits);
    PicImage->Picture->Bitmap = MyBits;
}

//---------------------------------------------------------------------------

void __fastcall TPictureForm::DrawQuads (
	int mesh_flag,
    int part_flag)
{	int i;
	int isubpart;
	int j;
    int ncorners;
	double scale;
    double angle;
	double xs, ys;
	double xe, ye;
	int xsi, ysi;
    int xei, yei;
    int pic_y;
    TCanvas * tc;
    TRect FRect;

    tc = MyBits->Canvas;

    tc->Brush->Color = clWhite;
    tc->Brush->Style = bsSolid;
    FRect = Rect(0, 0, pic_size, pic_size);
    tc->FillRect (FRect);

    tc->Pen->Style = psSolid;
    tc->Pen->Color = clBlack;

    scale = pic_size * 0.95 / diameter;
    pic_y = PicImage->Height - 1;

    if (mesh_flag)
	{	for (i = 0; i < n_quads; i++)
		{	for (j = 0; j < quad_pts; j++)
			{	polar_to_euc (point_radius [quad_points [i] [j]],
						point_angle [quad_points [i] [j]], &xs, &ys);
				polar_to_euc (point_radius [quad_points [i] [(j + 1) % quad_pts]],
						point_angle [quad_points [i] [(j + 1) % quad_pts]], &xe, &ye);
				xs *= scale;
                ys *= scale;
                xe *= scale;
                ye *= scale;
                xsi = xs + pic_size / 2;
                ysi = ys + pic_size / 2;
                ysi = pic_y - ysi;
                xei = xe + pic_size / 2;
                yei = ye + pic_size / 2;
                yei = pic_y - yei;
                tc->MoveTo (xsi, ysi);
                tc->LineTo (xei, yei);
            }
        }
    }
	else {
		tc->Ellipse (pic_size * 0.025, pic_y - pic_size * 0.025,
			pic_size * 0.975, pic_y - pic_size * 0.975);
	}
	
	if (part_flag)
	{	DrawParts (tc, scale, pic_y);
	}
	DrawPoints (tc, scale, pic_y);
//    PicImage->Canvas->Draw (0, 0, MyBits);
    PicImage->Picture->Bitmap = MyBits;
}

//---------------------------------------------------------------------------

void __fastcall TPictureForm::LoadPlopPic (plop_cmap *pcm)
{   int i;
    int j;
    char *p;

    for (i = 0; i < pic_size; i++)
    {   p = (char *) MyBits->ScanLine [i];
        for (j = 0; j < pic_size; j++)
        {   p [j] = picture [i] [j];
        }
    }
//    PicImage->Canvas->Draw (0, 0, MyBits);
    PicImage->Picture->Bitmap = MyBits;
}

//---------------------------------------------------------------------------

void __fastcall TPictureForm::DrawPic (void)
{   LockPlopData (1);
    
	if (PicStyleHasZ [PictureStyle]) {
		pic_size = my_min (PicImage->Width - z_scale_width, PicImage->Height);
	} else {
		pic_size = my_min (PicImage->Width, PicImage->Height);
	}

    switch (PictureStyle)
    {   case PicStyleMesh:
            DrawMesh (1, 0);
            break;

        case PicStyleSupports:
            DrawMesh (0, 0);
            break;

        case PicStyleColor:
			calculate_plop_plot (0, &pic_z_min, &pic_z_max, &err_rms, &err_pv);
			LoadPlopPic (MyCmap);
			DrawZLabels ();
			break;

		case PicStyleContour:
			calculate_plop_plot (1, &pic_z_min, &pic_z_max, &err_rms, &err_pv);
            LoadPlopPic (MyCmap);
            break;

        case PicStyleParts:
            DrawMesh (0, 1);
			break;

		case PicStyleQuads:
			DrawQuads (1, 0);
			break;


		case PicStyleZ88Color:
			calculate_z88_plot (0, &pic_z_min, &pic_z_max, &err_rms, &err_pv);
            LoadPlopPic (MyCmap);
			DrawZLabels ();
            break;
	}

    UnlockPlopData ();

    UpdateWindow (Handle);
    NewPicAvail = false;
}

//---------------------------------------------------------------------------

void __fastcall TPictureForm::SetNewPicAvail (void)
{   NewPicAvail = true;
    SomePicAvail = true;
    if (Visible)
        DrawPic ();
}
//---------------------------------------------------------------------------


void __fastcall TPictureForm::ShowEvent (TObject *Sender)
{   if (SomePicAvail)
        DrawPic ();
}
//---------------------------------------------------------------------------

void __fastcall TPictureForm::SaveAsGif (AnsiString Fname)
{   int h;
	int w;
    int i;
	int j;
    char *p;

	/* hack because need to update global variable pic_size*/
	DrawPic ();

	h = MyBits->Height;
	w = MyBits->Width;
	for (i = 0; i < h; i++)
	{   p = (char *) MyBits->ScanLine [h - i - 1];
		for (j = 0; j < w; j++)
		{   picture [i] [j] = p [j];
		}
	}
	write_picture (Fname.c_str (), MyCmap);
}

//---------------------------------------------------------------------------

void __fastcall TPictureForm::PictureOptionsClick(TObject *Sender)
{
    GraphOptionsForm->Show ();    
}
//---------------------------------------------------------------------------

void __fastcall TPictureForm::PicSaveClick(TObject *Sender)
{   AnsiString Fname;
	AnsiString Fext;


    if (SaveDialog1->Execute ())
    {   Fname = SaveDialog1->FileName;
        Fext = ExtractFileExt (Fname);
        if (Fext == ".bmp")
            MyBits->SaveToFile (Fname);
        else if (Fext == ".gif")
            SaveAsGif (Fname);
    }
}
//---------------------------------------------------------------------------


void __fastcall TPictureForm::FormShow(TObject *Sender)
{   if (NewPicAvail)
        DrawPic ();
}
//---------------------------------------------------------------------------

void __fastcall TPictureForm::FormResize(TObject *Sender)
{
//	MyBits->Height = min (PicImage->Height, PicImage->Width);
//	MyBits->Width = min (PicImage->Height, PicImage->Width);
	MyBits->Height = PicImage->Height;
	MyBits->Width = PicImage->Width;
	ClearPic ();
    if (SomePicAvail)
        DrawPic ();
}
//---------------------------------------------------------------------------

void __fastcall TPictureForm::GetZRange (double *z_min, double *z_max,
	double *err_rms_ptr, double *err_pv_ptr) {
	*z_min = pic_z_min;
	*z_max = pic_z_max;
	*err_rms_ptr = err_rms;
	*err_pv_ptr = err_pv;
}
//---------------------------------------------------------------------------

void __fastcall TPictureForm::DrawZLabels(void)
{   int i;
    double z;
	char str [100];
	double pic_z_min, pic_z_max;
	double err_rms, err_pv;
	TCanvas *tc;
	int icol;
	int left;

	GetZRange (&pic_z_min, &pic_z_max, &err_rms, &err_pv);

	tc = PicImage->Picture->Bitmap->Canvas;
	tc->Font->Color = clBlack;
    tc->Font->Size = 10;
	left = PicImage->Picture->Width - 100;
	tc->TextOut (left, 16, "RMS");
	sprintf (str, "%10.4g", err_rms);
	tc->TextOut (left + tc->TextWidth ("RMS "), 16, str);
	tc->TextOut (left, 40, "P-V");
	sprintf (str, "%10.4g", err_pv);
	tc->TextOut (left + tc->TextWidth ("RMS "), 40, str);

	for (i = 0; i < num_color_shapes; i++)
	{   icol = ((num_color_shapes - i - 1) * (n_colors - 1)) / (num_color_shapes - 1);
		tc->Brush->Color = (TColor)
			(MyCmap->color_r [icol] << 16 |
			 MyCmap->color_g [icol] << 8 |
			 MyCmap->color_b [icol]);
		tc->Rectangle (left, i * 24 + 64, left + 16, i * 24 + 80);
		z = pic_z_min + (pic_z_max - pic_z_min) *
			(num_color_shapes - i - 1) / (num_color_shapes - 1);
		sprintf (str, "%9.3g", z);
		tc->Brush->Color = clWhite;
		tc->TextOut (left + 30, i * 24 + 64, str);
	}
}


void __fastcall TPictureForm::CopyMenuItemClick(TObject *Sender)
{
	Clipboard ()->Assign (PicImage->Picture->Bitmap);
}
//---------------------------------------------------------------------------

