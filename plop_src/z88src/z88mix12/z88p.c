/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows OS.
*
* Composed and edited and copyright by 
* Professor Dr.-Ing. Frank Rieg, University of Bayreuth, Germany
*
* eMail: 
* frank.rieg@uni-bayreuth.de
* dr.frank.rieg@t-online.de
* 
* V12.0  February 14, 2005
*
* Z88 should compile and run under any Windows release, starting
* with Windows95.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING.  If not, write to
* the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
***********************************************************************/ 
/***********************************************************************
*  Z88P fuer Windows
*  4.10.2005 Rieg
***********************************************************************/
/***********************************************************************
* Windows 95 und NT
***********************************************************************/
#ifdef FR_WIN95
#include <z88p.h>
#include <windows.h>
#include <commctrl.h>
#include <string.h>  /* strcpy */
#include <stdio.h>   /* fopen, fprintf, fclose */
#endif

/***********************************************************************
* Window- Functions
***********************************************************************/
LRESULT CALLBACK WndProc            (HWND, UINT, WPARAM, LPARAM);

BOOL    CALLBACK InterDiaProc       (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK StrucDiaProc       (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK FaktorGloDiaProc   (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK FaktorZenDiaProc   (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK FaktorVerDiaProc   (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK FaktorRotDiaProc   (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK FaktorFxcorDiaProc (HWND, UINT, WPARAM, LPARAM);

HWND             InitToolBar   (HWND hParent);

HFONT EzCreateFont (HDC hdc, char * szFaceName, int iDeciPtHeight,
                    int iDeciPtWidth, int iAttributes, BOOL fLogRes);

/***********************************************************************
*  externe Variable
***********************************************************************/
HDC        hDC;
HDC        hDCDummy;
HINSTANCE  hInstance;
HFONT      hFont;

HWND       hToolBar;
HMENU      hMenuGer,hMenuEng;

HCURSOR    waitcur;

/***********************************************************************
*  Function-Declarationen
***********************************************************************/
int dyn88p(void);
int wsto88(void);
int rsto88(void);
int ro5x88(void);
int ro2x88(void);
int ri1x88(void);
int vu2b88(void);
int vu3b88(void);
int vv2b88(void);
int vv3b88(void);
int vp88(HDC hDC);
int vsca88(void);
int vcur88(void);
int vu2s88(void);
int vu3s88(void);
int vgpp88(HDC hDC);
int pu2b88(void);
int pu3b88(void);
int pv2b88(void);
int pv3b88(void);
int pp88(void);
int pu2s88(void);
int pu3s88(void);
int pgpp88(void);
int wlog88p(FR_INT4,int);
int ale88p(int);
int rcol88(void);
int lan88p(void);

/***********************************************************************
*  globale Variable
***********************************************************************/
FILE *fdyn,*fwlo,*f2,*f3,*f4,*f6,*f8,*fcfg;

/*
** fdyn= z88.dyn
** fwlo= z88p.log
** f2=   z88o6.txt
** f3=   z88o2.txt
** f4=   z88i1.txt
** f6=   z88o5.txt
** f8=   z88p.sto
** fcfg= z88com.cfg
*/ 
  
FR_DOUBLEAY x;
FR_DOUBLEAY y;
FR_DOUBLEAY z;
FR_DOUBLEAY ux;
FR_DOUBLEAY uy;
FR_DOUBLEAY uz;
FR_DOUBLEAY xgp;
FR_DOUBLEAY ygp;
FR_DOUBLEAY zgp;
FR_DOUBLEAY siggp;

FR_INT4AY ityp;
FR_INT4AY koffs;
FR_INT4AY koi;

FR_INT4AY kx;
FR_INT4AY ky;
FR_INT4AY kgpx;
FR_INT4AY kgpy;

double spamax,spamin,spainc;
double facx= 1.,facy= 1.,facz= 1.;
double cx= 0.,cy= 0.,cz= 0.;
double rotx= 0.,roty= 0.,rotz= 0.;
double fux= 100.,fuy= 100.,fuz= 100.;
double xmin= 0.,xmax= 0.,ymin= 0.,ymax= 0.,zmin= 0.,zmax= 0.;
double fzoom= 1.1;
double fxcor= 0.75; /* fuer vga und startbild (nicht maximal) */

FR_INT4 MAXKOI,MAXE,MAXK,MFACCOMMON,MAXGP;
FR_INT4 LANG= 0,IDYNMEM = 0;
FR_INT4 ndim,nkp,ne,nfg,neg,kflag,isflag,igpanz,ibflag,ipflag,iqflag;
FR_INT4 izoom= 1;

int iflade= ID_NOTLOADSTRUC;
int iflaver=ID_NOTLOADVERF;
int iflspa= ID_NOTLOADSPANN;

int ifverf= IDM_UNVERFORMT;
int ifdevi= IDM_CRT;
int ifansi= IDM_XY;
int iflabe= IDM_NOLABELS;
int iztogg= IDM_NOSHOWSPANN;

int ifstala= ID_ENABLELABELS;
int ifscale;
int ifvcur= 0;
int ifxsto= 0;

int ibUnver,ibVerfo;

int iyClient,ixClient;

BYTE ifarbe[50];
/*------------------------------------
* ifarbe: 0-2 : fuer hPenUnver
*         3-5 : fuer hPenVerfo
*         6-8 : fuer Farbe Element
*         9-11: fuer Farbe Knoten
*-----------------------------------*/

char  cdyn[8]   = "z88.dyn";
char  clog[12]  = "z88p.log";
char  csto[12]  = "z88p.sto";
char  cstrn[32] = "z88i1.txt";
char  cintfn[32]= "z88o6.txt";
char  co2[10]   = "z88o2.txt";
char  co5[10]   = "z88o5.txt";
char  cfg[11]   = "z88com.cfg";

/*--------------------------------------------------------------------------
* Char-Arrays
*-------------------------------------------------------------------------*/
char cstore[256];
char cbcall[128];
char cbpref[128];
char cbhelp[512];
char cmess [256];

/***********************************************************************
* WinMain
***********************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR szCmdLine, int iCmdShow)
{
HWND       hWnd;
HACCEL     hAccel;
MSG        msg;
WNDCLASSEX wndclass;

char capname[10];

/***********************************************************************
* Handles kommen lassen, window oeffnen
***********************************************************************/
strcpy(capname, "Z88P");

wndclass.cbSize        = sizeof(wndclass);
wndclass.style         = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc   = WndProc;
wndclass.cbClsExtra    = 0;
wndclass.cbWndExtra    = 0;
wndclass.hInstance     = hInstance;
wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88P));
wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,255));
wndclass.lpszMenuName  = capname;
wndclass.lpszClassName = capname;
wndclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88P));

RegisterClassEx(&wndclass);
  
hWnd = CreateWindow(capname, "Z88 Plot Z88P",
                    WS_OVERLAPPEDWINDOW,
                     50,100,
                    650,520,
                    NULL, NULL, hInstance, NULL);

InitCommonControls();

ShowWindow(hWnd,iCmdShow);
UpdateWindow(hWnd);

hAccel= LoadAccelerators(hInstance,capname);

while(GetMessage(&msg, NULL, 0, 0))
  {
  if(!TranslateAccelerator(hWnd,hAccel,&msg))
    {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }
  }

wsto88();
DeleteObject(hFont);
ReleaseDC(hWnd,hDC);

return msg.wParam;
}

/***********************************************************************
* Main Window Procedure: Das eigentliche Steuerprogramm
***********************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message,
                         WPARAM wParam, LPARAM lParam)
{
extern HDC        hDC;
extern HINSTANCE  hInstance;
extern HFONT      hFont;

extern HWND       hToolBar;
extern HMENU      hMenuGer,hMenuEng;

extern HCURSOR    waitcur;

extern FR_INT4    LANG;

extern int        iflade,ifverf,ifdevi,ifansi,iflabe,iztogg,ifxsto;
extern int        ixClient, iyClient;
extern BYTE       ifarbe[];
extern char       cintfn[], cstrn[];

extern char       cstore[];
extern char       cbcall[];
extern char       cbpref[];
extern char       cbhelp[];
extern char       cmess[];

HMENU             hMenu;

PAINTSTRUCT       ps;

int               ialert,imess,iret;

size_t            laenge;

/*----------------------------------------------------------------------
* Los gehts
*---------------------------------------------------------------------*/
switch(Message)
  {

/*----------------------------------------------------------------------
* case WM_CREATE
*---------------------------------------------------------------------*/
  case WM_CREATE:

/*======================================================================
* hInstance kommen lassen
*=====================================================================*/
    hInstance= (HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE);

/*======================================================================
* Wartecursor anlegen
*=====================================================================*/
    waitcur= LoadCursor(hInstance,MAKEINTRESOURCE(CUR_Z88P));

/*======================================================================
* Sprache feststellen
*=====================================================================*/
    iret= lan88p();

    if(iret != 0)
      {
      ale88p(iret);
      PostQuitMessage(0);
      return(1);
      }

    hMenuGer= LoadMenu(hInstance,"GERMAN");
    hMenuEng= LoadMenu(hInstance,"ENGLISH");

    if(LANG == 1) SetMenu(hWnd,hMenuGer);
    if(LANG == 2) SetMenu(hWnd,hMenuEng);

/*======================================================================
* dynamischen Speicher anfordern
*=====================================================================*/
    iret= dyn88p();
    if(iret != 0)
      {
      ale88p(iret);
      PostQuitMessage(0);
      return(1);
      }
     
/*======================================================================
* Gibt's schon ein Z88P.STO ?
*=====================================================================*/
    if( rsto88() ==1) 
      {
      ifscale= IDM_YESSCALE; /* kein Z88P.STO */
      ifxsto = 0;
      } 
    else
      {
      ifscale= IDM_NOSCALE;  /* Ja, Z88P.STO  */
      ifxsto = 1;
      }

/*======================================================================
* Farben einlesen
*=====================================================================*/
    ialert= rcol88();
    if(ialert != 0)
      {
      ale88p(ialert); 
      PostQuitMessage(0);
      return 0;
      }

/*======================================================================
* Toolbar
*=====================================================================*/
    hToolBar= InitToolBar(hWnd);

    if     (ifansi == IDM_XY) 
      {
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_XY,(LPARAM) MAKELONG(TRUE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_XZ,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_YZ,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_3DIM,(LPARAM) MAKELONG(FALSE,0) );
      }

    else if(ifansi == IDM_XZ)
      {
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_XY,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_XZ,(LPARAM) MAKELONG(TRUE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_YZ,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_3DIM,(LPARAM) MAKELONG(FALSE,0) );
      }

    else if(ifansi == IDM_YZ)
      {
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_XY,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_XZ,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_YZ,(LPARAM) MAKELONG(TRUE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_3DIM,(LPARAM) MAKELONG(FALSE,0) );
      }

    else if(ifansi == IDM_3DIM)
      {
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_XY,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_XZ,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_YZ,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_3DIM,(LPARAM) MAKELONG(TRUE,0) );
      }

    if     (iflabe == IDM_NOLABELS) 
      {
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_NOLABELS,(LPARAM) MAKELONG(TRUE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_KNOTEN,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_ELEMENTE,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_ALLES,(LPARAM) MAKELONG(FALSE,0) );
      }

    else if(iflabe == IDM_KNOTEN)
      {
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_NOLABELS,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_KNOTEN,(LPARAM) MAKELONG(TRUE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_ELEMENTE,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_ALLES,(LPARAM) MAKELONG(FALSE,0) );
      }

    else if(iflabe == IDM_ELEMENTE)
      {
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_NOLABELS,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_KNOTEN,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_ELEMENTE,(LPARAM) MAKELONG(TRUE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_ALLES,(LPARAM) MAKELONG(FALSE,0) );
      }

    else if(iflabe == IDM_ALLES)
      {
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_NOLABELS,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_KNOTEN,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_ELEMENTE,(LPARAM) MAKELONG(FALSE,0) );
      SendMessage(hToolBar,TB_CHECKBUTTON,
      (WPARAM)ITC_ALLES,(LPARAM) MAKELONG(TRUE,0) );
      }

/*======================================================================
* Design-Context und Font setzen
*=====================================================================*/
    hDC= GetDC(hWnd);
    hFont= EzCreateFont(hDC,"Times New Roman",100,0,0,TRUE);
    SelectObject(hDC,hFont);
    SetBkColor(hDC,RGB(255,255,255));
    SetBkMode(hDC, TRANSPARENT);

  return 0; /* Ende WM_CREATE */
  
/*----------------------------------------------------------------------
* case WM_INITMENU
*---------------------------------------------------------------------*/
  case WM_INITMENU:
    hMenu= GetMenu(hWnd);
    CheckMenuItem(hMenu,IDM_UNVERFORMT,   MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_VERFORMT,     MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_UNUNDVERFORMT,MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,ifverf,           MF_CHECKED   | MF_BYCOMMAND);   

    CheckMenuItem(hMenu,IDM_PLOTTER,      MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_CRT,          MF_CHECKED   | MF_BYCOMMAND);   

    CheckMenuItem(hMenu,IDM_XY,           MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_XZ,           MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_YZ,           MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_3DIM,         MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,ifansi,           MF_CHECKED   | MF_BYCOMMAND);   

    CheckMenuItem(hMenu,IDM_NOLABELS,     MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_KNOTEN,       MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_ELEMENTE,     MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_ALLES,        MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,iflabe,           MF_CHECKED   | MF_BYCOMMAND);   

    CheckMenuItem(hMenu,IDM_NOSHOWSPANN,  MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_SHOWSPANN,    MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,iztogg,           MF_CHECKED   | MF_BYCOMMAND);   

    CheckMenuItem(hMenu,IDM_YESSCALE,     MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_NOSCALE,      MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,ifscale,          MF_CHECKED   | MF_BYCOMMAND);   

  return 0;

/*----------------------------------------------------------------------
* case WM_MOVE
*---------------------------------------------------------------------*/
  case WM_MOVE:
  return 0;

/*----------------------------------------------------------------------
* case WM_SIZE
*---------------------------------------------------------------------*/
  case WM_SIZE:
    iyClient= HIWORD(lParam);
    ixClient= LOWORD(lParam);
  return 0;

/*----------------------------------------------------------------------
* WM_NOTIFY
*---------------------------------------------------------------------*/
  case WM_NOTIFY:
    {
    LPNMHDR pnmh= (LPNMHDR) lParam;
    LPSTR   pReply;

    if(pnmh->code == TTN_NEEDTEXT)
      {
      LPTOOLTIPTEXT lpttt= (LPTOOLTIPTEXT) lParam;

      switch(lpttt->hdr.idFrom)
        {
        case ITC_HELP:
          if(LANG == 1) pReply= "OnLine-Hilfe fuer Plotprogramm";
          if(LANG == 2) pReply= "OnLine Help for Plot Program";
        break;

        case ITC_UNVERFORMT:
          if(LANG == 1) pReply= "Zeige unverformte Struktur";
          if(LANG == 2) pReply= "Show Undeflected Structure";
        break;

        case ITC_VERFORMT:
          if(LANG == 1) pReply= "Zeige verformte Struktur";
          if(LANG == 2) pReply= "Show Deflected Structure";
        break;

        case ITC_UNUNDVERFORMT:
          if(LANG == 1) pReply= "Zeige unverformte und verformte Struktur";
          if(LANG == 2) pReply= "Show Undeflected and Deflected Structure";
        break;

        case ITC_XY:
          if(LANG == 1) pReply= "Zeige XY- Ansicht";
          if(LANG == 2) pReply= "Show XY View";
        break;

        case ITC_XZ:
          if(LANG == 1) pReply= "Zeige XZ- Ansicht";
          if(LANG == 2) pReply= "Show XZ View";
        break;

        case ITC_YZ:
          if(LANG == 1) pReply= "Zeige YZ- Ansicht";
          if(LANG == 2) pReply= "Show YZ View";
        break;

        case ITC_3DIM:
          if(LANG == 1) pReply= "Zeige dreidimensionale Ansicht";
          if(LANG == 2) pReply= "Show 3 dimensional View";
        break;

        case ITC_NOLABELS:
          if(LANG == 1) pReply= "Zeige keine Knoten- und Element Labels";
          if(LANG == 2) pReply= "No Node- and Element Labels";
        break;

        case ITC_KNOTEN:
          if(LANG == 1) pReply= "Zeige Knoten- Labels";
          if(LANG == 2) pReply= "Show Node Labels";
        break;

        case ITC_ELEMENTE:
          if(LANG == 1) pReply= "Zeige Element Labels";
          if(LANG == 2) pReply= "Show Element Labels";
        break;

        case ITC_ALLES:
          if(LANG == 1) pReply= "Zeige Knoten- und Element Labels";
          if(LANG == 2) pReply= "Show Node- and Element Labels";
        break;

        case ITC_SHOWSPANN:
          if(LANG == 1) pReply= "Zeige/Unterdruecke Vergleichsspannungen ";
          if(LANG == 2) pReply= "Show/NoShow von Mises Stresses";
        break;

        case ITC_YESSCALE:
          if(LANG == 1) pReply= "Auto-Skalieren";
          if(LANG == 2) pReply= "AutoScale";
        break;

        }
      lstrcpy(lpttt->szText,pReply);
      }
    return 0;  /* sehr wichtig */
    }

/*----------------------------------------------------------------------
* case WM_COMMAND
*---------------------------------------------------------------------*/
  case WM_COMMAND:
    switch (LOWORD(wParam))
      {
/*======================================================================
* Datei
*=====================================================================*/ 
      case IDM_WER:
        if(LANG == 1) strcpy(cmess,
"Plotprogramm Z88P fuer Windows\n\
Version 12.0\n\
Copyright Univ.-Prof.Dr.-Ing. Frank Rieg,\n\
Universitaet Bayreuth, 2005\n\
Alle Rechte vorbehalten");
          if(LANG == 2) strcpy(cmess,
"Plot Program Z88P for Windows\n\
Version 12.0\n\
Copyright Prof.Dr. Frank Rieg,\n\
University of Bayreuth, Germany 2005\n\
All rights reserved");
        MessageBox(NULL,cmess,"Z88P", MB_OK | MB_ICONINFORMATION);
      return 0;
                          
      case IDM_INTERFACE:
        if(LANG == 1) DialogBox(hInstance,"Dlg_Inter88G",hWnd,InterDiaProc);
        if(LANG == 2) DialogBox(hInstance,"Dlg_Inter88E",hWnd,InterDiaProc);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_STRUKTURFILE:
        if(LANG == 1) DialogBox(hInstance,"Dlg_Struc88G",hWnd,StrucDiaProc);
        if(LANG == 2) DialogBox(hInstance,"Dlg_Struc88E",hWnd,StrucDiaProc);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_XIT:
        if(LANG == 1) strcpy(cmess,"Z88P beenden ?");
        if(LANG == 2) strcpy(cmess,"Quit Z88P ?");
        imess= MessageBox(NULL,cmess,"Z88P",MB_OKCANCEL | MB_ICONQUESTION);
        if(imess == IDOK)     PostQuitMessage(0);
        if(imess == IDCANCEL) return 0;  
      return 0; 

/*======================================================================
* COMMAND : Hilfe
*=====================================================================*/
      case ITC_HELP:
        fcfg= fopen(cfg,"r");          /* Z88COM.CFG oeffnen */
        if(fcfg == NULL)
          {
          if(LANG == 1) strcpy(cmess,
          "Datei Z88COM.CFG nicht vorhanden oder zerschossen !");
          if(LANG == 2) strcpy(cmess,
          "File Z88COM.CFG not available or destroyed !");
          MessageBox(NULL,cmess,"Z88P", MB_OK | MB_ICONHAND);
          }

        rewind(fcfg);

        fgets(cstore,128,fcfg);
        fgets(cstore,128,fcfg);

        fgets(cstore,128,fcfg);
        laenge= strlen(cstore);
        strncpy(cbpref,cstore,laenge-1);
        strcat (cbpref,"\0");

        fgets(cstore,128,fcfg);
        laenge= strlen(cstore);
        strncpy(cbcall,cstore,laenge-1);
        strcat (cbcall,"\0");

        fclose(fcfg); 

        strcpy(cbhelp,cbcall);
        strcat(cbhelp," ");
        strcat(cbhelp,cbpref);
        if(LANG == 1) strcat(cbhelp,"g88p.htm");
        if(LANG == 2) strcat(cbhelp,"e88p.htm");
        imess= WinExec(cbhelp,SW_SHOW);
        if(imess < 33)
          {
          if(LANG == 1) strcpy(cmess,
          "Internet Browser konnte nicht gestartet werden !");
          if(LANG == 2) strcpy(cmess,
          "Could not launch Internet Browser !");
          MessageBox(NULL,cmess,"Z88P", MB_OK | MB_ICONHAND);
          }

      return 0;

/*======================================================================
* Struktur via Menue
*=====================================================================*/ 
      case IDM_UNVERFORMT:
      case IDM_VERFORMT:
      case IDM_UNUNDVERFORMT:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,ifverf,MF_UNCHECKED | MF_BYCOMMAND);
        ifverf= LOWORD(wParam);
        CheckMenuItem(hMenu,ifverf,MF_CHECKED | MF_BYCOMMAND);   

        if     (ifverf == IDM_UNVERFORMT) 
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_UNVERFORMT,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_VERFORMT,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_UNUNDVERFORMT,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifverf == IDM_VERFORMT)
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_UNVERFORMT,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_VERFORMT,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_UNUNDVERFORMT,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifverf == IDM_UNUNDVERFORMT)
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_UNVERFORMT,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_VERFORMT,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_UNUNDVERFORMT,(LPARAM) MAKELONG(TRUE,0) );
          }

        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* Struktur via Toolbar
*=====================================================================*/ 
      case ITC_UNVERFORMT:
        ifverf = IDM_UNVERFORMT; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_VERFORMT:
        ifverf = IDM_VERFORMT; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_UNUNDVERFORMT:
        ifverf = IDM_UNUNDVERFORMT; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* Ausgabe
*=====================================================================*/ 
      case IDM_CRT:
      case IDM_PLOTTER:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,ifdevi,MF_UNCHECKED | MF_BYCOMMAND);
        ifdevi= LOWORD(wParam);
        CheckMenuItem(hMenu,ifdevi,MF_CHECKED | MF_BYCOMMAND);   
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* Ansicht via Menue
*=====================================================================*/ 
      case IDM_XY:
      case IDM_XZ:
      case IDM_YZ:
      case IDM_3DIM:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,ifansi,MF_UNCHECKED | MF_BYCOMMAND);
        ifansi= LOWORD(wParam);
        CheckMenuItem(hMenu,ifansi,MF_CHECKED | MF_BYCOMMAND);   

        if     (ifansi == IDM_XY) 
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_XY,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_XZ,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_YZ,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_3DIM,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifansi == IDM_XZ)
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_XY,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_XZ,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_YZ,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_3DIM,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifansi == IDM_YZ)
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_XY,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_XZ,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_YZ,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_3DIM,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifansi == IDM_3DIM)
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_XY,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_XZ,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_YZ,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_3DIM,(LPARAM) MAKELONG(TRUE,0) );
          }

        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* Ansicht via Toolbar
*=====================================================================*/ 
      case ITC_XY:
        ifansi = IDM_XY; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_XZ:
        ifansi = IDM_XZ; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_YZ:
        ifansi = IDM_YZ; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_3DIM:
        ifansi = IDM_3DIM; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* Labels via Menue
*=====================================================================*/ 
      case IDM_NOLABELS:
      case IDM_KNOTEN:
      case IDM_ELEMENTE:
      case IDM_ALLES:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,iflabe,MF_UNCHECKED | MF_BYCOMMAND);
        iflabe= LOWORD(wParam);
        CheckMenuItem(hMenu,iflabe,MF_CHECKED | MF_BYCOMMAND);   

        if     (iflabe == IDM_NOLABELS) 
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NOLABELS,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_KNOTEN,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_ELEMENTE,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_ALLES,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(iflabe == IDM_KNOTEN)
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NOLABELS,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_KNOTEN,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_ELEMENTE,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_ALLES,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(iflabe == IDM_ELEMENTE)
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NOLABELS,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_KNOTEN,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_ELEMENTE,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_ALLES,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(iflabe == IDM_ALLES)
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NOLABELS,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_KNOTEN,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_ELEMENTE,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_ALLES,(LPARAM) MAKELONG(TRUE,0) );
          }

        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* Labels via Toolbar
*=====================================================================*/ 
      case ITC_NOLABELS:
        iflabe = IDM_NOLABELS; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_KNOTEN:
        iflabe = IDM_KNOTEN; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_ELEMENTE:
        iflabe = IDM_ELEMENTE; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_ALLES:
        iflabe = IDM_ALLES; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* Bild
*=====================================================================*/ 
      case IDM_PRIOR:
        facx *= fzoom;
        facy *= fzoom;
        facz *= fzoom;
        izoom++;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;
      
      case IDM_NEXT:
        facx /= fzoom;
        facy /= fzoom;
        facz /= fzoom;
        izoom--;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0; 

      case IDM_UP:
        if(ifvcur == 0) vcur88();
        cy= cy - 0.05*(fabs(ymax) + fabs(ymin))/pow(fzoom,(double)izoom);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_DOWN:
        if(ifvcur == 0) vcur88();
        cy= cy + 0.05*(fabs(ymax) + fabs(ymin))/pow(fzoom,(double)izoom);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_RIGHT:
        if(ifvcur == 0) vcur88();
        cx= cx - 0.05*(fabs(xmax) + fabs(xmin))/pow(fzoom,(double)izoom);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_LEFT:
        if(ifvcur == 0) vcur88();
        cx= cx + 0.05*(fabs(xmax) + fabs(xmin))/pow(fzoom,(double)izoom);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_HOME:
        if(ifvcur == 0) vcur88();
        cz= cz - 0.05*(fabs(zmax) + fabs(zmin))/pow(fzoom,(double)izoom);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_END:
        if(ifvcur == 0) vcur88();
        cz= cz + 0.05*(fabs(zmax) + fabs(zmin))/pow(fzoom,(double)izoom);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;
 
      case IDM_F2:
        rotx -= 10.;
        if ((int)rotx == -10) rotx= 350.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_F3:
        rotx += 10.;
        if ((int)rotx == 360) rotx= 0.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_F4:
        roty -= 10.;
        if ((int)roty == -10) roty= 350.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_F5:
        roty += 10.;
        if ((int)roty == 360) roty= 0.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_F6:
        rotz -= 10.;
        if ((int)rotz == -10) rotz= 350.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_F7:
        rotz += 10.;
        if ((int)rotz == 360) rotz= 0.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_F8:
        rotx= 0.;
        roty= 0.;
        rotz= 0.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* Faktor- Boxen
*=====================================================================*/ 
      case IDM_GLO:
        if(LANG == 1) DialogBox(hInstance,"Dlg_Glo88G",hWnd,FaktorGloDiaProc);
        if(LANG == 2) DialogBox(hInstance,"Dlg_Glo88E",hWnd,FaktorGloDiaProc);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_ZEN:
        if(LANG == 1) DialogBox(hInstance,"Dlg_Zen88G",hWnd,FaktorZenDiaProc);
        if(LANG == 2) DialogBox(hInstance,"Dlg_Zen88E",hWnd,FaktorZenDiaProc);
        InvalidateRect(hWnd,NULL,TRUE);
       return 0;

      case IDM_VER:
        if(LANG == 1) DialogBox(hInstance,"Dlg_Ver88G",hWnd,FaktorVerDiaProc);
        if(LANG == 2) DialogBox(hInstance,"Dlg_Ver88E",hWnd,FaktorVerDiaProc);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_ROT:
        if(LANG == 1) DialogBox(hInstance,"Dlg_Rot88G",hWnd,FaktorRotDiaProc);
        if(LANG == 2) DialogBox(hInstance,"Dlg_Rot88E",hWnd,FaktorRotDiaProc);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;
         
      case IDM_FXCOR:
        if(LANG == 1)DialogBox(hInstance,"Dlg_FXC88G",hWnd,FaktorFxcorDiaProc);
        if(LANG == 2)DialogBox(hInstance,"Dlg_FXC88E",hWnd,FaktorFxcorDiaProc);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
*     Vergleichspannungen setzen via Menue
*=====================================================================*/ 
      case IDM_NOSHOWSPANN:
      case IDM_SHOWSPANN:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,iztogg,MF_UNCHECKED | MF_BYCOMMAND);
        iztogg= LOWORD(wParam);
        CheckMenuItem(hMenu,iztogg,MF_CHECKED | MF_BYCOMMAND);   

        if(iztogg == IDM_NOSHOWSPANN)
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SHOWSPANN,(LPARAM) MAKELONG(FALSE,0) );
          }
        if(iztogg == IDM_SHOWSPANN)
          {
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SHOWSPANN,(LPARAM) MAKELONG(TRUE,0) );
          }

        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
*     Vergleichspannungen setzen via Toolbar
*=====================================================================*/ 
      case ITC_SHOWSPANN:
        if(iztogg == IDM_NOSHOWSPANN) iztogg = IDM_SHOWSPANN;
        else                          iztogg = IDM_NOSHOWSPANN;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;
      
/*======================================================================
*     Autoscale setzen via Menue
*=====================================================================*/ 
      case IDM_YESSCALE:
        izoom= 1;
      case IDM_NOSCALE:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,ifscale,MF_UNCHECKED | MF_BYCOMMAND);
        ifscale= LOWORD(wParam);
        CheckMenuItem(hMenu,ifscale,MF_CHECKED | MF_BYCOMMAND);   
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
*     Autoscale setzen via Toolbar
*=====================================================================*/ 
      case ITC_YESSCALE:
        ifscale = IDM_YESSCALE;
        izoom= 1;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      default:
        return DefWindowProc(hWnd, Message, wParam, lParam); /* end switch */
      }
              
/*----------------------------------------------------------------------
* case WM_PAINT
*---------------------------------------------------------------------*/
  case WM_PAINT:
    hDCDummy = BeginPaint(hWnd, &ps);

    /* hFont= EzCreateFont(hDC,"Times New Roman",80,0,0,TRUE); */
    /* SelectObject(hDC,hFont);                                */
    /* SetBkColor(hDC,RGB(255,255,255));                       */

/*======================================================================
* Laden der Files Z88I1.TXT, Z88O2.TXT & Z88O5.TXT
*=====================================================================*/ 
    if(iflade== ID_NOTLOADSTRUC) /* Z88I1 */
      {
      SetCursor(waitcur);
      ShowCursor(TRUE);
      f4= fopen(cstrn,"r");
      if(f4== NULL)
        {
        ale88p(AL_NOSTRFI);
        wlog88p(0L,LOG_NOSTRFI);
        return 0;
        }

      ialert= ri1x88();
      if(ialert != 0)
        {
        ale88p(ialert); 
        PostQuitMessage(0);
        return 0;
        }

      iflade= ID_LOADSTRUC;

      if(ifxsto == 0) /* Es gibt noch kein Z88P.STO */
        {
        if(ndim == 3L)
          {  
          ifansi= IDM_3DIM; 
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_XY,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_XZ,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_YZ,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_3DIM,(LPARAM) MAKELONG(TRUE,0) );
          }
        else
          {
          ifansi= IDM_XY;   
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_XY,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_XZ,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_YZ,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_3DIM,(LPARAM) MAKELONG(FALSE,0) );
          }
        }

      fclose(f4);  
      }

    if(iflaver== ID_NOTLOADVERF &&
      (ifverf== IDM_VERFORMT || ifverf== IDM_UNUNDVERFORMT)) /* Z88I2 */
      {
      SetCursor(waitcur);
      ShowCursor(TRUE);
      f3= fopen(co2,"r");
      if(f3== NULL)
        {
        ale88p(AL_NOO2);
        wlog88p(0L,LOG_NOO2);
        return 0;
        }
      ro2x88();
      iflaver= ID_LOADVERF;
      fclose(f3);  
      }
                  
    if(iflspa== ID_NOTLOADSPANN && iztogg== IDM_SHOWSPANN) /* Z88O5 */
      {
      SetCursor(waitcur);
      ShowCursor(TRUE);
      f6= fopen(co5,"r");
      if(f6== NULL)
        {
        ale88p(AL_NOO5);
        wlog88p(0L,LOG_NOO5);
        return 0;
        }

      ialert= ro5x88();
      if(ialert != 0)
        {
        ale88p(ialert); 
        PostQuitMessage(0);
        return 0;
        }

      iflspa= ID_LOADSPANN;
      fclose(f6);  
      }

/*======================================================================
* ggf. oeffnen des plotterfiles
*=====================================================================*/ 
    if(ifdevi== IDM_PLOTTER)
      {
      f2= fopen(cintfn,"w+");
      if(f2== NULL)
        {
        ale88p(AL_NOPLOF);
        wlog88p(0L,LOG_NOPLOF);
        return 0;
        }
      }
               
/*======================================================================
* autoscale: wenn kein Z88P.STO oder StrucDiaProc gelaufen
*=====================================================================*/ 
    if( ifscale == IDM_YESSCALE) vsca88();
            
/*======================================================================
* zeichnen
*=====================================================================*/ 
/*--------- unverformt, crt  -----------------------------------------*/
    if(ifverf== IDM_UNVERFORMT && ifdevi== IDM_CRT)
      {
      SetCursor(LoadCursor(NULL,IDC_WAIT));
      if(ifansi != IDM_3DIM) vu2b88();
      else                   vu3b88();
      vp88(hDC);

      if(iztogg== IDM_SHOWSPANN)
        {
        if(ifansi != IDM_3DIM) vu2s88();
        else                   vu3s88();
        vgpp88(hDC);
        } 

      SetCursor(LoadCursor(NULL,IDC_ARROW));
      }

/*--------- unverformt, plotter  -------------------------------------*/
    if(ifverf== IDM_UNVERFORMT && ifdevi== IDM_PLOTTER)
      {
      SetCursor(LoadCursor(NULL,IDC_WAIT));

      if(ifansi != IDM_3DIM) pu2b88();
      else                   pu3b88();
      pp88();

      if(iztogg== IDM_SHOWSPANN)
        {
        if(ifansi != IDM_3DIM) pu2s88();
        else                   pu3s88();
        pgpp88();
        } 

      SetCursor(LoadCursor(NULL,IDC_ARROW));

      if(LANG == 1) strcpy(cmess,"Plotter-Datei wurde erzeugt !");
      if(LANG == 2) strcpy(cmess,"Plot File created !");
      MessageBox(NULL,cmess,"Z88P", MB_OK | MB_ICONINFORMATION);

      fclose(f2);
      ifdevi= IDM_CRT;
      InvalidateRect(hWnd,NULL,TRUE);
      }

/*--------- verformt, crt  -------------------------------------------*/
    if(ifverf== IDM_VERFORMT && ifdevi== IDM_CRT)
      {
      SetCursor(LoadCursor(NULL,IDC_WAIT));
      if(ifansi != IDM_3DIM) vv2b88();
      else                   vv3b88();
      vp88(hDC);
      SetCursor(LoadCursor(NULL,IDC_ARROW));
      }

/*--------- verformt, plotter  ---------------------------------------*/
    if(ifverf== IDM_VERFORMT && ifdevi== IDM_PLOTTER)
      {
      SetCursor(LoadCursor(NULL,IDC_WAIT));

      if(ifansi != IDM_3DIM) pv2b88();
      else                   pv3b88();
      pp88();

      SetCursor(LoadCursor(NULL,IDC_ARROW));

      if(LANG == 1) strcpy(cmess,"Plotter-Datei wurde erzeugt !");
      if(LANG == 2) strcpy(cmess,"Plot File created !");
      MessageBox(NULL,cmess,"Z88P", MB_OK | MB_ICONINFORMATION);

      fclose(f2);
      ifdevi= IDM_CRT;
      InvalidateRect(hWnd,NULL,TRUE);
      }
              
/*--------- un- und verformt, crt  -----------------------------------*/
    if(ifverf== IDM_UNUNDVERFORMT && ifdevi== IDM_CRT)
      {
      SetCursor(LoadCursor(NULL,IDC_WAIT));
      ifstala=ID_ENABLELABELS ;
      ifverf= IDM_UNVERFORMT;
      if(ifansi != IDM_3DIM) vu2b88();
      else                   vu3b88();
      vp88(hDC);
      ifstala=ID_DISABLELABELS ;
      ifverf= IDM_VERFORMT;
      if(ifansi != IDM_3DIM) vv2b88();
      else                   vv3b88();
      vp88(hDC);
      ifstala=ID_ENABLELABELS ;
      ifverf= IDM_UNUNDVERFORMT;
      SetCursor(LoadCursor(NULL,IDC_ARROW));
      }
                  
/*--------- un- und verformt, plotter --------------------------------*/
    if(ifverf== IDM_UNUNDVERFORMT && ifdevi== IDM_PLOTTER)
      {
      SetCursor(LoadCursor(NULL,IDC_WAIT));

      ifstala=ID_ENABLELABELS ;
      ifverf= IDM_UNVERFORMT;
      if(ifansi != IDM_3DIM) pu2b88();
      else                   pu3b88();
      pp88();
      ifstala=ID_DISABLELABELS ;
      ifverf= IDM_VERFORMT;
      if(ifansi != IDM_3DIM) pv2b88();
      else                   pv3b88();
      pp88();
      ifstala=ID_ENABLELABELS ;
      ifverf= IDM_UNUNDVERFORMT;

      SetCursor(LoadCursor(NULL,IDC_ARROW));

      if(LANG == 1) strcpy(cmess,"Plotter-Datei wurde erzeugt !");
      if(LANG == 2) strcpy(cmess,"Plot File created !");
      MessageBox(NULL,cmess,"Z88P", MB_OK | MB_ICONINFORMATION);

      fclose(f2);
      ifdevi= IDM_CRT;
      InvalidateRect(hWnd,NULL,TRUE);
      }

    EndPaint(hWnd, &ps);
  return 0;

/*----------------------------------------------------------------------
* case WM_CLOSE
*---------------------------------------------------------------------*/
  case WM_CLOSE:
    PostQuitMessage(0);
  return 0;

/*----------------------------------------------------------------------
* case WM_DESTROY
*---------------------------------------------------------------------*/
  case WM_DESTROY:
    PostQuitMessage(0);
  return 0;

/*----------------------------------------------------------------------
* default
*---------------------------------------------------------------------*/
  default:
    return DefWindowProc(hWnd,Message,wParam,lParam);
  }
}
