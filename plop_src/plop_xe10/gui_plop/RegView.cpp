//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RegView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRegViewer *RegViewer;
//---------------------------------------------------------------------------
__fastcall TRegViewer::TRegViewer(TComponent* Owner)
	: TForm(Owner)
{	Reg = new TRegistry;
	Reg->Access = KEY_READ;
	Keys = new TStringList;
	ValueNames = new TStringList;
	Values = new TStringList;
	StringGrid1->ColWidths [0] = 160;
	StringGrid1->ColWidths [1] = 60;
	StringGrid1->ColWidths [2] = 500;
}
//---------------------------------------------------------------------------
HKEY hkeys [] = {HKEY_CLASSES_ROOT, HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, HKEY_USERS, HKEY_CURRENT_CONFIG};

void __fastcall TRegViewer::Button1Click(TObject *Sender)
{
	if (RadioGroup1->ItemIndex >= 0)
	{	Reg->RootKey = hkeys [RadioGroup1->ItemIndex];
		Edit1->Text = "";
	}
}

//---------------------------------------------------------------------------

void __fastcall TRegViewer::Button2Click(TObject *Sender)
{	bool openok;
	int i;
	UnicodeString str;
    UnicodeString str2;

	Reg->RootKey = hkeys [RadioGroup1->ItemIndex];
	Reg->CloseKey ();
	openok = Reg->OpenKey (Edit1->Text, false);
	if (openok)
	{	Edit3->Text = "ok";
		Reg->GetKeyNames (Keys);
		ListBox1->Items = Keys;
		Reg->GetValueNames (ValueNames);
//		ListBox2->Items = ValueNames;
		Values->Clear ();
		StringGrid1->RowCount = 0;
		StringGrid1->Cells [0][0] = "";
		StringGrid1->Cells [1][0] = "";
		StringGrid1->Cells [2][0] = "";
		for (i = 0; i < ValueNames->Count; i++) {
			switch (Reg->GetDataType (ValueNames->Strings [i])) {
				case rdUnknown:
					Values->Add ("unknown");
					break;

				case rdString:
					if (i >= StringGrid1->RowCount) {
						StringGrid1->RowCount = i + 1;
					}
					StringGrid1->Cells [0] [i] = ValueNames->Strings [i];
					StringGrid1->Cells [1] [i] = "string";
					StringGrid1->Cells [2] [i] = Reg->ReadString (ValueNames->Strings [i]);
					Values->Add (str);
					break;

				case rdInteger:
				case rdExpandString:
				case rdBinary:
				default:
					break;
			}

		}
    }
	else
		Edit3->Text = "bad";

}
//---------------------------------------------------------------------------
void __fastcall TRegViewer::Button3Click(TObject *Sender)
{   UnicodeString str;
	int i;

	str = Edit1->Text.c_str ();
	i = str.Length ();
	while (i >= 0 && str [i] != '\\') {
		str [i] = '\0';
		i--;
	}
	if (i >= 0) {
		str [i] = '\0';
	}
	Edit1->Text = str;
    Button2Click (Sender);

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TRegViewer::ListBox1DblClick(TObject *Sender)
{   int i;
	int sel;
	UnicodeString str;
	sel = -1;
	for (i = 0; i < ListBox1->Count && sel == -1; i++) {
		if (ListBox1->Selected [i]) {
			sel = i;
		}
	}
	str.printf (L"%s\\%s", Edit1->Text.c_str (), ListBox1->Items->Strings [sel].c_str ());
	Edit1->Text = str;
	Button2Click (Sender);
}
//---------------------------------------------------------------------------

