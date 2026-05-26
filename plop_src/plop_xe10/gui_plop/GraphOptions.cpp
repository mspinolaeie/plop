//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GraphOptions.h"
#include "Picture.h"
#include "ColorPicture.h"
#include "ContourPicture.h"
#include "MeshPicture.h"
#include "SupportPicture.h"
#include "Z88ColorPicture.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGraphOptionsForm *GraphOptionsForm;
//---------------------------------------------------------------------------
__fastcall TGraphOptionsForm::TGraphOptionsForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGraphOptionsForm::OKButtonClick(TObject *Sender)
{   int n;
    double d;

	if (swscanf (NumColorEdit->Text.c_str (), L" %d", &n) == 1)
    {   if (n < 2 || n > color_map_size)
            n = color_map_size;
        n_colors = n;
    }
    else
        n_colors = default_n_colors;
        
	if (swscanf (NumContourEdit->Text.c_str (), L" %d", &n) == 1)
    {   if (n < 2)
            n = 2;
        else if (n > max_contours)
            n = max_contours;
        n_contours = n;
    }
    else
        n_contours = default_n_contours;

	if  (swscanf (ZAxisEdit->Text.c_str (), L" %lg", &d) == 1)
    {   if (d < 0)
            d = 0;
        pic_z_range = d;
    }
    else
        pic_z_range = 0;

	if  (swscanf (ContourSpaceEdit->Text.c_str (), L" %lg", &d) == 1)
    {   if (d < 0)
            d = 0;
        contour_space = d;
    }
    else
        contour_space = 0;

    if (ColorPictureForm->SomePicAvail && ColorPictureForm->Visible)
    {   ColorPictureForm->DrawPic ();
    }

	if (Z88ColorPictureForm->SomePicAvail && Z88ColorPictureForm->Visible)
	{   Z88ColorPictureForm->DrawPic ();
	}

	if (ContourPictureForm->SomePicAvail && ContourPictureForm->Visible)
        ContourPictureForm->DrawPic ();
    Close ();
}
//---------------------------------------------------------------------------
void __fastcall TGraphOptionsForm::CancelButtonClick(TObject *Sender)
{
    Close ();    
}
//---------------------------------------------------------------------------
void __fastcall TGraphOptionsForm::FormShow(TObject *Sender)
{   char str [100];

    sprintf (str, "%d", n_colors);
    NumColorEdit->Text = str;

    sprintf (str, "%d", n_contours);
    NumContourEdit->Text = str;

    if (pic_z_range != 0)
    {   sprintf (str, "%lg", pic_z_range);
        ZAxisEdit->Text = str;
    }
    else
        ZAxisEdit->Text = "";

}
//---------------------------------------------------------------------------




