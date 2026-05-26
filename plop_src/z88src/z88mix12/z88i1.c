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
/****************************************************************************
*  Programm z88i1.c - der Iterations- Solver Part 1
*  16.2.2005 Rieg
****************************************************************************/

/***********************************************************************
* Windows95 und NT
***********************************************************************/
#ifdef FR_WIN95
#include <z88i.h>
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>    /* FILE */
#include <string.h>   /* strcpy */
#endif

/***********************************************************************
*  Window- Function-Declarationen
***********************************************************************/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND InitToolBar   (HWND hParent);

HFONT EzCreateFont (HDC hdc, char * szFaceName, int iDeciPtHeight,
                    int iDeciPtWidth, int iAttributes, BOOL fLogRes);

/***********************************************************************
*  externe Variable
***********************************************************************/
HDC        hDC;
HINSTANCE  hInstance;
HFONT      hFont;

HWND       hToolBar;
HMENU      hMenuGer,hMenuEng;

HCURSOR    waitcur;

/***********************************************************************
*  Function-Declarationen
***********************************************************************/
int dyn88i1(void);
int ale88i(int);
int ri188i(void);
int z88ai(void);
int wria88i(void);
int w4y88i(void);
int lan88i1(void);
int wrim88i(FR_INT4,int);

/***********************************************************************
*  globale Variable
***********************************************************************/
FILE *fdyn,*fl1,*fi1,*f1y,*f4y,*fo0,*fo1,*fcfg;

/*  
**   fdyn= z88.dyn
**   fl1 = z88i1.log
**   fi1=  z88i1.txt
**   f1y=  z88o1.bny
**   f4y=  z88o4.bny
**   fo0=  z88o0.txt
**   fo1=  z88o1.txt
**   fcfg= z88com.cfg
*/ 

char cdyn[1000] = "z88.dyn";
char cl1[1000] = "z88i1.log";
char ci1[1000] = "z88i1.txt";
char c1y[1000] = "z88o1.bny";
char c4y[1000] = "z88o4.bny";
char co0[1000] = "z88o0.txt";
char co1[1000] = "z88o1.txt";
char cfg[1000] = "z88com.cfg";

#define cdyn_file_name "z88.dyn"
#define cl1_file_name  "z88i1.log"
#define ci1_file_name "z88i1.txt"
#define c1y_file_name "z88o1.bny"
#define c4y_file_name "z88o4.bny"
#define co0_file_name "z88o0.txt"
#define co1_file_name "z88o1.txt"
#define cfg_file_name "z88com.cfg"

/*--------------------------------------------------------------------------
* Pointer
*-------------------------------------------------------------------------*/
struct FR_SIJ *IJ;
FR_DOUBLEAY x;
FR_DOUBLEAY y;
FR_DOUBLEAY z;
FR_DOUBLEAY emod;
FR_DOUBLEAY rnue;
FR_DOUBLEAY qpara;
FR_DOUBLEAY riyy;
FR_DOUBLEAY eyy;
FR_DOUBLEAY rizz;
FR_DOUBLEAY ezz;
FR_DOUBLEAY rit;
FR_DOUBLEAY wt;

FR_INT4AY ip;
FR_INT4AY iez;
FR_INT4AY kc;
FR_INT4AY koi;
FR_INT4AY ifrei; 
FR_INT4AY ioffs;
FR_INT4AY koffs;
FR_INT4AY ityp;
FR_INT4AY ivon;
FR_INT4AY ibis;
FR_INT4AY intord;

/*--------------------------------------------------------------------------
* Char-Arrays
*-------------------------------------------------------------------------*/
char cstore[256];
char cbcall[128];
char cbpref[128];
char cbhelp[512];
char cmess [256];

/*--------------------------------------------------------------------------
* Arrays
*-------------------------------------------------------------------------*/
FR_INT4 mcomp[21];                     /* 21 ist MAXPA */

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
FR_DOUBLE emode,rnuee,qparae,riyye,eyye,rizze,ezze,rite,wte,eps,rp;

FR_INT4 kfoun,intore,nel,ktyp,maxit;
FR_INT4 LANG,IDYNMEM;
FR_INT4 ndim,nkp,ne,nfg,neg,nfgp1,nkoi,kflag,ibflag,ipflag,iqflag;

/*--------------------------------------------------------------------------
* vorbelegte Variable
*-------------------------------------------------------------------------*/
FR_INT4 MAXSOR=0,MAXPUF=0,MAXGS=0,MAXNFG=0,MAXK=0,MAXE=0,MAXKOI=0,MAXNEG=0;

/***********************************************************************
* WinMain
***********************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR lpszCmdLine, int nCmdShow)
{
HWND       hWnd;
MSG        msg;
WNDCLASSEX wndclass;

char       capname[10];
char *tmpenv;
char tmpname [1000];
       
/***********************************************************************
* Handles kommen lassen, window oeffnen
***********************************************************************/
strcpy(capname, "Z88I1");

#ifdef gui_plop_version
if ((tmpenv = getenv ("TEMP")) == NULL && (tmpenv = getenv ("TMP")) == NULL) {
	tmpname [0] = '\0';
} else {
	sprintf (tmpname, "%s\\", tmpenv);
}
#else
	tmpname [0] = '\0';
#endif

sprintf (cdyn, "%s", cdyn_file_name);
sprintf (cl1, "%s%s", tmpname, cl1_file_name);
sprintf (ci1, "%s%s", tmpname, ci1_file_name);
sprintf (c1y, "%s%s", tmpname, c1y_file_name);
sprintf (c4y, "%s%s", tmpname, c4y_file_name);
sprintf (co0, "%s%s", tmpname, co0_file_name);
sprintf (co1, "%s%s", tmpname, co1_file_name);
sprintf (cfg, "%s", cfg_file_name);


wndclass.cbSize        = sizeof(wndclass);
wndclass.style         = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc   = WndProc;
wndclass.cbClsExtra    = 0;
wndclass.cbWndExtra    = 0;
wndclass.hInstance     = hInstance;
wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88I1));
wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
/* wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); */
wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,0));
wndclass.lpszMenuName  = capname;
wndclass.lpszClassName = capname;
wndclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88I1));

RegisterClassEx(&wndclass);

hWnd = CreateWindow(capname,"Z88 Iteration Solver Part 1 Z88I1",
                    WS_OVERLAPPEDWINDOW,
                    150,220,
                    520,320,
                    NULL, NULL, hInstance, NULL);

InitCommonControls();

ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);

while(GetMessage(&msg, NULL, 0, 0))
  {
  TranslateMessage(&msg);
  DispatchMessage(&msg);
  }

DeleteObject(hFont);

return msg.wParam;
}

/***********************************************************************
* Main Window Procedure
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

extern FR_INT4    ICFLAG,LANG;
extern int        ifmode;

extern char       cstore[];
extern char       cbcall[];
extern char       cbpref[];
extern char       cbhelp[];
extern char       cmess[];

PAINTSTRUCT       ps;

static int        ixClient,iyClient;

int               imess,iret;

size_t            laenge;

/*----------------------------------------------------------------------
* Los gehts
*---------------------------------------------------------------------*/
switch (Message)
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
    waitcur= LoadCursor(hInstance,MAKEINTRESOURCE(CUR_Z88I1));

/*======================================================================
* Sprache feststellen
*=====================================================================*/
    iret= lan88i1();
    if(iret != 0)
      {
      ale88i(iret);
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
    iret= dyn88i1();
    if(iret != 0) 
      { 
      ale88i(iret);
      PostQuitMessage(0);
      return 0;
      }           

/*======================================================================
* Toolbar
*=====================================================================*/
    hToolBar= InitToolBar(hWnd);

  return 0; /* Ende WM_CREATE */

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
        case ITC_GO:
          if(LANG == 1) pReply= "Baue nun die Sparse- Matrix auf";
          if(LANG == 2) pReply= "Assemble the Sparse Matrix";
        break;

        case ITC_HELP:
          if(LANG == 1) pReply= "OnLine-Hilfe fuer Iterationssolver";
          if(LANG == 2) pReply= "OnLine Help for Iteration Solver";
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
* COMMAND : Wer ist es
*=====================================================================*/
      case IDM_WER:
        if(LANG == 1) strcpy(cmess,
"Der FE- Prozessor Z88I1 fuer Windows\n\
Version 12.0\n\
Der Iterationssolver Part 1\n\
Copyright Univ.-Prof.Dr.-Ing. Frank Rieg,\n\
Universitaet Bayreuth, 2005\n\
Alle Rechte vorbehalten");
          if(LANG == 2) strcpy(cmess,
"FEA Solver Z88I1 for Windows\n\
Version 12.0\n\
The Iteration Solver Part 1\n\
Copyright Prof.Dr. Frank Rieg,\n\
University of Bayreuth, Germany 2005\n\
All rights reserved");
        MessageBox(NULL,cmess,"Z88I1", MB_OK | MB_ICONINFORMATION);
      return 0;

/*======================================================================
* COMMAND : Xit
*=====================================================================*/
      case IDM_XIT:
        if(LANG == 1) strcpy(cmess,"Z88I1 beenden ?");
        if(LANG == 2) strcpy(cmess,"Quit Z88I1 ?");
        imess= MessageBox(NULL,cmess,"Z88I1",MB_OKCANCEL | MB_ICONQUESTION);
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
          MessageBox(NULL,cmess,"Z88I1", MB_OK | MB_ICONHAND);
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
        if(LANG == 1) strcat(cbhelp,"g88ite.htm");
        if(LANG == 2) strcat(cbhelp,"e88ite.htm");
        imess= WinExec(cbhelp,SW_SHOW);
        if(imess < 33)
          {
          if(LANG == 1) strcpy(cmess,
          "Internet Browser konnte nicht gestartet werden !");
          if(LANG == 2) strcpy(cmess,
          "Could not launch Internet Browser !");
          MessageBox(NULL,cmess,"Z88I1", MB_OK | MB_ICONHAND);
          }

      return 0;

/*======================================================================
* COMMAND : Go
*=====================================================================*/
      case IDM_GO:
      case ITC_GO:
        SetCursor(waitcur);
        ShowCursor(TRUE);
        
        hDC= GetDC(hWnd);
        hFont= EzCreateFont(hDC,"Times New Roman",120,0,2,TRUE);
        SelectObject(hDC,hFont);
        SetBkColor(hDC,RGB(255,255,0));

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Einlesen Z88I1.TXT
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        iret= ri188i();
        if(iret != 0) 
          { 
          ale88i(iret);
          PostQuitMessage(0);
          return 0;
          }             
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Rechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        iret= z88ai();
        if(iret != 0) 
          { 
          ale88i(iret);
          PostQuitMessage(0);
          return 0;
          }             

        iret= wria88i();         /* Schreiben Z88O1.TXT und Z88O1.BNY */ 
        if(iret != 0) 
          { 
          ale88i(iret);
          PostQuitMessage(0);
          return 0;
          }                 

        iret= w4y88i();          /* Schreiben Z88O4.BNY */ 
        if(iret != 0) 
          { 
          ale88i(iret);
          PostQuitMessage(0);
          return 0;
          }          

        wrim88i(0,TX_ENDI1);

/*---------------------------------------------------------------------------
* Ende Case Go
*--------------------------------------------------------------------------*/
        if(LANG == 1) strcpy(cmess,"FE-Prozessor Z88I1 gelaufen");
        if(LANG == 2) strcpy(cmess,"FEA-Solver Z88I1 done");
        MessageBox(NULL,cmess,"Z88I1", MB_OK | MB_ICONINFORMATION);
        ReleaseDC(hWnd,hDC);  
        SetCursor(LoadCursor(NULL,IDC_ARROW));
      return 0;                           /* end case GO */

      default:
        return DefWindowProc(hWnd, Message, wParam, lParam);
      }                                /* end switch command */ 

/*----------------------------------------------------------------------
* case WM_PAINT
*---------------------------------------------------------------------*/
  case WM_PAINT:
    memset(&ps, 0x00, sizeof(PAINTSTRUCT));
    hDC = BeginPaint(hWnd, &ps);

    SetBkMode(hDC, TRANSPARENT);

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

  default:
    return DefWindowProc(hWnd, Message, wParam, lParam);
  } 
}
