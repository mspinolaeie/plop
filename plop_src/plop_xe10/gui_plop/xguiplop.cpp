//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("RunOptions.cpp", RunOptionsForm);
USEFORM("SupportPicture.cpp", SupportPictureForm);
USEFORM("WhatsNew.cpp", WhatsNewForm);
USEFORM("PlopExecDone.cpp", RunFinishedForm);
USEFORM("QuadPicture.cpp", QuadPictureForm);
USEFORM("RegView.cpp", RegViewer);
USEFORM("Run.cpp", RunForm);
USEFORM("Z88ColorPicture.cpp", Z88ColorPictureForm);
USEFORM("CellPartPicture.cpp", CellPartPictureForm);
USEFORM("ColorPicture.cpp", ColorPictureForm);
USEFORM("ContourPicture.cpp", ContourPictureForm);
USEFORM("Debug.cpp", DebugForm);
USEFORM("About.cpp", AboutBox);
USEFORM("AutoCell.cpp", AutoCellForm);
USEFORM("MeshPicture.cpp", MeshPictureForm);
USEFORM("PartDimension.cpp", PartDimensionForm);
USEFORM("Picture.cpp", PictureForm);
USEFORM("GraphOptions.cpp", GraphOptionsForm);
USEFORM("MeshEdit.cpp", CellEditForm);
//---------------------------------------------------------------------------
LPTSTR GuiPlopArgsT;

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR MyArgs, int)
{
	try
	{   GuiPlopArgsT = MyArgs;

		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TCellEditForm), &CellEditForm);
		Application->CreateForm(__classid(TAutoCellForm), &AutoCellForm);
		Application->CreateForm(__classid(TDebugForm), &DebugForm);
		Application->CreateForm(__classid(TGraphOptionsForm), &GraphOptionsForm);
		Application->CreateForm(__classid(TPartDimensionForm), &PartDimensionForm);
		Application->CreateForm(__classid(TPictureForm), &PictureForm);
		Application->CreateForm(__classid(TQuadPictureForm), &QuadPictureForm);
		Application->CreateForm(__classid(TSupportPictureForm), &SupportPictureForm);
		Application->CreateForm(__classid(TMeshPictureForm), &MeshPictureForm);
		Application->CreateForm(__classid(TCellPartPictureForm), &CellPartPictureForm);
		Application->CreateForm(__classid(TContourPictureForm), &ContourPictureForm);
		Application->CreateForm(__classid(TColorPictureForm), &ColorPictureForm);
		Application->CreateForm(__classid(TRunFinishedForm), &RunFinishedForm);
		Application->CreateForm(__classid(TZ88ColorPictureForm), &Z88ColorPictureForm);
		Application->CreateForm(__classid(TRunForm), &RunForm);
		Application->CreateForm(__classid(TRunOptionsForm), &RunOptionsForm);
		Application->CreateForm(__classid(TWhatsNewForm), &WhatsNewForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TRegViewer), &RegViewer);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
