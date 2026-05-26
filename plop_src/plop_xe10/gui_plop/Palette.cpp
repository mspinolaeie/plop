//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdlib.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "Picture.h"

TPictureForm *PictureForm;
//---------------------------------------------------------------------------
__fastcall TPictureForm::TPictureForm(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TPictureForm::SaveButtonClick(TObject *Sender)
{
{   int i;
    int j;
    int c;
    Graphics::TBitmap * bm;

    MyLogPalette = (LOGPALETTE *) malloc (sizeof (LOGPALETTE) + 249 * sizeof (PALETTEENTRY));
    for (i = 0; i < 125; i++)
    { MyLogPalette->palPalEntry [i].peRed = 0;
      MyLogPalette->palPalEntry [i].peGreen = i * 2;
      MyLogPalette->palPalEntry [i].peBlue = 250 - i * 2;
      MyLogPalette->palPalEntry [i].peFlags = 0;
    }
    for (; i < 250; i++)
    { MyLogPalette->palPalEntry [i].peRed = (i - 125) * 2;
      MyLogPalette->palPalEntry [i].peGreen = (250 - i) * 2;
      MyLogPalette->palPalEntry [i].peBlue = 0;
      MyLogPalette->palPalEntry [i].peFlags = 0;
    }
    MyLogPalette->palVersion = 0x300;
    MyLogPalette->palNumEntries = 250;
    MyPalette = CreatePalette (MyLogPalette);
    Image1->Picture = new TPicture;
    bm = new Graphics::TBitmap;
    bm->Height = 300;
    bm->Width = 300;
    bm->Palette = MyPalette;
    for (i = 0; i < 300; i++)
    {   for (j = 0; j < 300; j++)
        {   c = (i + j) % 250;
            if( c < 125)
            {   bm->Canvas->Pixels [i] [j] =
                (((125 - c) << 16) + (c << 8)) * 2 + 0x0000000;
            }
            else
            {   bm->Canvas->Pixels [i] [j] =
                (((250 - c) << 8) + c - 125) * 2 + 0x0000000;
            }
        }
    }
    Image1->Picture->Bitmap = bm;
}

}
//---------------------------------------------------------------------------
