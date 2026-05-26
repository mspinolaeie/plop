//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <Clipbrd.hpp>

#include "PartDimension.h"
#include "plot.h"
#include <math.h>

#define my_max(x,y) ((x)>(y)?(x):(y))
#define my_min(x,y) ((x)<(y)?(x):(y))

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPartDimensionForm *PartDimensionForm;


extern void LockPlopData (int);
extern void UnlockPlopData (void);

extern void evaluate_parts (void);

//---------------------------------------------------------------------------
__fastcall TPartDimensionForm::TPartDimensionForm(TComponent* Owner)
    : TForm(Owner)
{
    PicImage->Picture = new TPicture;
    MyBits = new Graphics::TBitmap;
    MyBits->PixelFormat = pf8bit;
    MyBits->Height = PicImage->Height;
    MyBits->Width = PicImage->Width;

    NewPicAvail = false;
    SomePicAvail = false;
}

//---------------------------------------------------------------------------

void __fastcall TPartDimensionForm::SetPalette (plop_cmap *pcm)
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

void __fastcall TPartDimensionForm::ClearPic (void)
{   TCanvas * tc;
    TRect FRect;

    tc = MyBits->Canvas;

    tc->Brush->Color = clWhite;
    tc->Brush->Style = bsSolid;
    FRect = Rect(0, 0, PicImage->Width, PicImage->Height);
    tc->FillRect (FRect);
    PartNumLabel->Caption = "No Parts";
    SupportRadiusLabel->Caption = "No Parts";
    SupportAngleLabel->Caption = "No Parts";
    PartCGXLabel->Caption = "No Parts";
    PartCGYLabel->Caption = "No Parts";

    PicImage->Picture->Bitmap = MyBits;
}
//---------------------------------------------------------------------------

void __fastcall TPartDimensionForm::SetNewPicAvail (void)
{   NewPicAvail = true;
    SomePicAvail = true;
    if (Visible)
        DrawPic ();
}

//---------------------------------------------------------------------------

void __fastcall TPartDimensionForm::DrawPic (void)
{   int ipart;
    int jcorner;
    int ncorners;
    double part_size_max_x;
    double part_size_max_y;
    double part_size_min_x;
    double part_size_min_y;
    double scale;
    double pic_size_fill = 0.9;
    double pic_cg_size = 0.015;
    double text_x_size = 100;   /* guess how much space label takes in X */
    double text_y_size = 20;    int origin_x;
    int origin_y;
    int pic_size_x;
    int pic_size_y;
    int xs;
    int ys;
    int xe;
    int ye;
    int pic_v;
    double unit_scale;
    char str [100];
    TCanvas * tc;
    TRect FRect;

    LockPlopData (1);

    tc = MyBits->Canvas;

    tc->Brush->Color = clWhite;
    tc->Brush->Style = bsSolid;
    FRect = Rect(0, 0, PicImage->Width, PicImage->Height);
    tc->FillRect (FRect);

    tc->Pen->Style = psSolid;
    tc->Pen->Color = clBlack;
    tc->Brush->Style = bsClear;


	switch (DimensionUnitsRadioGroup->ItemIndex)
    {   case 0:
            unit_scale = 1;
            break;

        case 1:
            unit_scale = 1 / 25.4;
            break;
    }
	pic_size = my_min (PicImage->Width, PicImage->Height);
    pic_size_x = PicImage->Width;
    pic_size_y = PicImage->Height;
    pic_v = PicImage->Height - 1;
    ipart = PartNumScrollBar->Position;
    part_size_max_x = 0;
    part_size_max_y = 0;
    part_size_min_x = 0;
    part_size_min_y = 0;

    if (n_parts > 0 && SomePicAvail)
    {   sprintf (str, "Part Number %d", ipart + 1);
        PartNumLabel->Caption = str;
        sprintf (str, "Radius of CG = %.3f", part_cg_radius [ipart] * unit_scale);
        SupportRadiusLabel->Caption = str;
        sprintf (str, "Angle of CG = %.3f", fmod (part_cg_angle [ipart], (double) degrees));
        SupportAngleLabel->Caption = str;
        sprintf (str, "X of CG = %.3f", part_cg_x [ipart] * unit_scale);
        PartCGXLabel->Caption = str;
        sprintf (str, "Y of CG = %.3f", part_cg_y [ipart] * unit_scale);
        PartCGYLabel->Caption = str;
    }
    else
    {   PartNumLabel->Caption = "No Parts";
        SupportRadiusLabel->Caption = "No Parts";
        SupportAngleLabel->Caption = "No Parts";
        PartCGXLabel->Caption = "No Parts";
        PartCGYLabel->Caption = "No Parts";
    }
    if (ipart >= 0 && ipart < n_parts)
    {   ncorners = part_type_num_corners [part_type [ipart]];
        for (jcorner = 0; jcorner < ncorners; jcorner++)
		{   part_size_max_x = my_max (part_draw_x [ipart] [jcorner], part_size_max_x);
			part_size_max_y = my_max (part_draw_y [ipart] [jcorner], part_size_max_y);
			part_size_min_x = my_min (part_draw_x [ipart] [jcorner], part_size_min_x);
			part_size_min_y = my_min (part_draw_y [ipart] [jcorner], part_size_min_y);
        }
        scale = my_min (
				(pic_size_x - text_x_size) * pic_size_fill / my_max((part_size_max_x - part_size_min_x), 1.0e-10) ,
				(pic_size_y - text_y_size) * pic_size_fill / my_max((part_size_max_y - part_size_min_y), 1.0e-10));
        origin_x = ((pic_size_x - text_x_size) - (part_size_max_x + part_size_min_x) * scale) / 2;
        origin_y = ((pic_size_y - text_y_size) - (part_size_max_y + part_size_min_y)* scale) / 2;
        for (jcorner = 0; jcorner < ncorners; jcorner++)
        {   xs = part_draw_x [ipart] [jcorner] * scale + origin_x + 0.5;
            ys = part_draw_y [ipart] [jcorner] * scale + origin_y + 0.5;
            xe = part_draw_x [ipart] [(jcorner + 1) % ncorners] * scale + origin_x + 0.5;
            ye = part_draw_y [ipart] [(jcorner + 1) % ncorners] * scale + origin_y + 0.5;
            ys = pic_v - ys;
            ye = pic_v - ye;
            tc->MoveTo (xs, ys);
            tc->LineTo (xe, ye);
            tc->Ellipse (xs - pic_size / 140 - 1, ys - pic_size / 140 - 1,
                    xs + pic_size / 140 + 1, ys + pic_size / 140 + 1);
			sprintf (str, "(%d) X=%.3f,Y=%.3f", (jcorner + part_rotation [ipart]) % part_type_num_corners [part_type [ipart]] + 1,
						 part_draw_x [ipart] [jcorner] * unit_scale,
                    part_draw_y [ipart] [jcorner] * unit_scale);
            tc->Font->Color = clBlack;
            tc->TextOut (xs + 10, ys - 10, str);
        }
        tc->Pen->Color = clRed;
        xs = part_draw_cg_x [ipart] * scale + origin_x + 0.5 - pic_size * pic_cg_size;
        ys = part_draw_cg_y [ipart] * scale + origin_y + 0.5;
        xe = part_draw_cg_x [ipart] * scale + origin_x + 0.5 + pic_size * pic_cg_size;
        ye = part_draw_cg_y [ipart] * scale + origin_y + 0.5;
        ys = pic_v - ys;
        ye = pic_v - ye;
        tc->MoveTo (xs, ys);
        tc->LineTo (xe, ye);
        xs = part_draw_cg_x [ipart] * scale + origin_x + 0.5;
        ys = part_draw_cg_y [ipart] * scale + origin_y + 0.5 - pic_size * pic_cg_size;
        xe = part_draw_cg_x [ipart] * scale + origin_x + 0.5;
        ye = part_draw_cg_y [ipart] * scale + origin_y + 0.5 + pic_size * pic_cg_size;
        ys = pic_v - ys;
        ye = pic_v - ye;
        tc->MoveTo (xs, ys);
        tc->LineTo (xe, ye);

        xs = part_draw_cg_x [ipart] * scale + origin_x + 0.5;
        ys = part_draw_cg_y [ipart] * scale + origin_y + 0.5;
        ys = pic_v - ys;
        sprintf (str, "X=%.3f,Y=%.3f", part_draw_cg_x [ipart] * unit_scale,
                part_draw_cg_y [ipart] * unit_scale);
        tc->Font->Color = clRed;
        tc->TextOut (xs + 15, ys - 15, str);
    }


    UnlockPlopData ();
    PicImage->Picture->Bitmap = MyBits;

    UpdateWindow (Handle);
    NewPicAvail = false;
}

//---------------------------------------------------------------------------

void __fastcall TPartDimensionForm::PartNumScrollBarChange(TObject *Sender)
{   char str [100];
    int ipos;

	PartNumScrollBar->Max = my_max (n_parts - 1, 0);
    if (SomePicAvail)
        DrawPic ();

}
//---------------------------------------------------------------------------


void __fastcall TPartDimensionForm::FormResize(TObject *Sender)
{
    MyBits->Height = PicImage->Height;
    MyBits->Width = PicImage->Width;
    ClearPic ();
    if (SomePicAvail)
        DrawPic ();
    
}
//---------------------------------------------------------------------------

void __fastcall TPartDimensionForm::RotateButtonClick(TObject *Sender)
{   int ipart;

    ipart = PartNumScrollBar->Position;
    part_rotation [ipart] = (part_rotation [ipart] + 1) %
            part_type_num_corners [part_type [ipart]];
    if (SomePicAvail)
    {   evaluate_parts ();
        DrawPic ();
    }
}

//---------------------------------------------------------------------------

void __fastcall TPartDimensionForm::SaveAsGif (AnsiString Fname)
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

void __fastcall TPartDimensionForm::PicSaveClick(TObject *Sender)
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

void __fastcall TPartDimensionForm::CopyMenuItemClick(TObject *Sender)
{
	Clipboard ()->Assign (PicImage->Picture->Bitmap);
}
//---------------------------------------------------------------------------

