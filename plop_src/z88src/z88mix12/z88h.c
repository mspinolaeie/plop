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
* Z88H fuer Windows
* 25.8.2005 Rieg
* Cuthill- McKee Algorithmus fuer Z88I1.TXT, Z88I2.TXT und Z88I5.TXT.
* besonders fuer Files, die mit Z88G aus Pro/ENGINEER/Pro/MESH
* erzeugt wurden 
***********************************************************************/
/***********************************************************************
* Windows 95 und NT
***********************************************************************/
#ifdef FR_WIN95
#include <z88h.h>
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>    /* FILE */
#include <stdlib.h>   /* exit */
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
*  Functions
***********************************************************************/
int z882cut(void);
int cut88(void);
int cut2z88(void);
int rdy88h(void);
int wrim88h(FR_INT4,int);
int wlog88h(FR_INT4,int);
int ale88h(int);
int lan88h(void);
FR_INT4 FR_MAX(FR_INT4,FR_INT4);
FR_INT4 FR_MIN(FR_INT4,FR_INT4);

/****************************************************************************
*  globale Variable
****************************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fwlo,*fcfg;

char cdyn[8] = "z88.dyn";
char clog[9] = "z88h.log";
char cfg[11] = "z88com.cfg";

/*--------------------------------------------------------------------------
* Char-Arrays
*-------------------------------------------------------------------------*/
char cstore[256];
char cbcall[128];
char cbpref[128];
char cbhelp[512];
char cmess[256];

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
FR_INT4 ICFLAG=1;  /* Reverse Cuthill-McKee ist voreingestellt */
FR_INT4 LANG;
FR_INT4 MAXGRA,MAXNDL;
FR_INT4 iqflag;

/***********************************************************************
* Typen
***********************************************************************/
typedef  int  BOOL;

#define TRUE 1
#define FALSE 0

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
       
/***********************************************************************
* Handles kommen lassen, window oeffnen
***********************************************************************/
strcpy(capname, "Z88H");

wndclass.cbSize        = sizeof(wndclass);
wndclass.style         = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc   = WndProc;
wndclass.cbClsExtra    = 0;
wndclass.cbWndExtra    = 0;
wndclass.hInstance     = hInstance;
wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88H));
wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
wndclass.hbrBackground = CreateSolidBrush(RGB(128,128,192));
wndclass.lpszMenuName  = capname;
wndclass.lpszClassName = capname;
wndclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88H));

RegisterClassEx(&wndclass);

hWnd = CreateWindow(capname,"Z88 Cuthill-McKee Program Z88H",
                    WS_OVERLAPPEDWINDOW,
                    50, 320,
                    440, 320,
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

extern FR_INT4    LANG;

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
    waitcur= LoadCursor(hInstance,MAKEINTRESOURCE(CUR_Z88H));

/*======================================================================
* Sprache feststellen
*=====================================================================*/
    iret= lan88h();
    if(iret != 0)
      {
      ale88h(iret);
      PostQuitMessage(0);
      return(1);
      }

    hMenuGer= LoadMenu(hInstance,"GERMAN");
    hMenuEng= LoadMenu(hInstance,"ENGLISH");

    if(LANG == 1) SetMenu(hWnd,hMenuGer);
    if(LANG == 2) SetMenu(hWnd,hMenuEng);

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
          if(LANG == 1) pReply= "Starte nun Cuthill-McKee Programm Z88H";
          if(LANG == 2) pReply= "Now launch Cuthill-McKee Program Z88H";
        break;

        case ITC_HELP:
          if(LANG == 1) pReply= "OnLine-Hilfe fuer Cuthill-McKee Programm";
          if(LANG == 2) pReply= "OnLine Help for Cuthill-McKee Program";
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
"Cuthill-McKee Programm Z88H fuer Windows\n\
Version 12.0\n\
Copyright Univ.-Prof.Dr.-Ing. Frank Rieg,\n\
Universitaet Bayreuth, 2005\n\
Alle Rechte vorbehalten");
          if(LANG == 2) strcpy(cmess,
"Cuthill-McKee Program Z88H for Windows\n\
Version 12.0\n\
Copyright Prof.Dr. Frank Rieg,\n\
University of Bayreuth, Germany 2005\n\
All rights reserved");
        MessageBox(NULL,cmess,"Z88H", MB_OK | MB_ICONINFORMATION);
      return 0; 

/*======================================================================
* COMMAND : Xit
*=====================================================================*/
      case IDM_XIT:
        if(LANG == 1) strcpy(cmess,"Z88H beenden ?");
        if(LANG == 2) strcpy(cmess,"Quit Z88H ?");
        imess= MessageBox(NULL,cmess,"Z88H",MB_OKCANCEL | MB_ICONQUESTION);
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
          MessageBox(NULL,cmess,"Z88H", MB_OK | MB_ICONHAND);
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
        if(LANG == 1) strcat(cbhelp,"g88h.htm");
        if(LANG == 2) strcat(cbhelp,"e88h.htm");
        imess= WinExec(cbhelp,SW_SHOW);
        if(imess < 33)
          {
          if(LANG == 1) strcpy(cmess,
          "Internet Browser konnte nicht gestartet werden !");
          if(LANG == 2) strcpy(cmess,
          "Could not launch Internet Browser !");
          MessageBox(NULL,cmess,"Z88H", MB_OK | MB_ICONHAND);
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
        SetBkColor(hDC,RGB(128,128,192));

        iret= z882cut();               /* Z88I1.TXT in Z88H.IN */

        if(iret == 0) iret= cut88();   /* Cuthill-McKee --> Z88H.OUT */
        else
          {
          PostQuitMessage(0);
          return(1);
          }

        if(iret == 0) iret= cut2z88(); /* Z88I1.TXT + Z88I2.TXT umbauen */ 
        else
          {
          PostQuitMessage(0);
          return(1);
          }

/*---------------------------------------------------------------------------
* Ende Case Go
*--------------------------------------------------------------------------*/
        if(LANG == 1) strcpy(cmess,"Cuthill-McKee Programm Z88H gelaufen");
        if(LANG == 2) strcpy(cmess,"Cuthill-McKee Program Z88H done");
        MessageBox(NULL,cmess,"Z88H", MB_OK | MB_ICONINFORMATION);
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

/***********************************************************************
* Z882CUT
***********************************************************************/        
int z882cut(void)
{
FILE *fz88i1, *fcut;

FR_INT4 nkp,ndim,ne,newnum,ianz,nfg,neg,kflag,ibflag,ipflag;
FR_INT4 koi[21];
FR_INT4 idummy,ityp;
FR_INT4 i;

char cstring[255];
char cfcut[]="z88h.in";
char cfi1[]= "z88i1.txt";

/*----------------------------------------------------------------------
* Files oeffnen
*---------------------------------------------------------------------*/
if ((fcut=fopen(cfcut,"w"))==NULL)
  {
  ale88h(AL_NOIN);
  wlog88h(0,LOG_NOIN);
  return 1;
  }
else
  wrim88h(0,TX_INOPEN);
    
rewind(fcut);
        
if ((fz88i1=fopen(cfi1,"r"))==NULL)
  {
  ale88h(AL_NOI1);
  wlog88h(0,LOG_NOI1);
  return 1;
  }
else
  wrim88h(0,TX_I1OPEN);
  
rewind(fz88i1);
                
/*----------------------------------------------------------------------
* Vorbereiten
*---------------------------------------------------------------------*/
newnum= -1;                            /* nur eine Startnummer */
        
iqflag=0;
	
fgets(cstring,254,fz88i1);
sscanf(cstring,"%ld %ld %ld %ld %ld %ld %ld %ld %ld",
  &ndim,&nkp,&ne,&nfg,&neg,&kflag,&ibflag,&ipflag,&iqflag);

fprintf(fcut,"%9ld %9ld\n",nkp,newnum);
        
/*----------------------------------------------------------------------
* 1. Durchlauf: Rewind, Leerlesen Koordinaten, Elementtyp feststellen
*---------------------------------------------------------------------*/        
rewind(fz88i1);

fgets(cstring,254,fz88i1);             /* leerlesen 1. Zeile */ 

for(i = 1;i <= nkp; i++)               /* leerlesen Koordinaten */
  fgets(cstring,254,fz88i1); 
  
fgets(cstring,254,fz88i1);
sscanf(cstring,"%ld %ld",&idummy,&ityp); /* Typ des 1.Elements */

/*----------------------------------------------------------------------
* 2. Durchlauf: Rewind, Leerlesen Koordinaten
*---------------------------------------------------------------------*/        
rewind(fz88i1);

fgets(cstring,254,fz88i1);             /* leerlesen 1. Zeile */ 

for(i = 1;i <= nkp; i++)               /* leerlesen Koordinaten */
  fgets(cstring, 254, fz88i1); 

/*----------------------------------------------------------------------
* Schreiben der Hexaeder Nr.1, Scheiben Nr.7, Torus Nr.8, Platte Nr.20
*---------------------------------------------------------------------*/        
if (ityp == 1 || ityp == 7 || ityp == 8 || ityp == 20)
  {
  ianz= 8;
  fprintf(fcut,"%ld\n",ianz);
        
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,"%ld %ld",&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
                
    sscanf(cstring, "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", 
    &koi[1],&koi[2],&koi[3],&koi[4],&koi[5],
    &koi[6],&koi[7],&koi[8],&koi[9],&koi[10]);
        
    fprintf(fcut, "%9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\n",
    koi[1],koi[2],koi[3],koi[4],koi[5],
    koi[6],koi[7],koi[8],koi[9],koi[10]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0 0 0 0 0\n");
  goto L999;
  }

/*----------------------------------------------------------------------
* Schreiben der Balken Nr.2, 13, Welle Nr.5, Stab Nr.4, Nr.9
*---------------------------------------------------------------------*/        
if (ityp == 2 || ityp == 4 || ityp == 5 || ityp == 9 || ityp == 13)
  {
  ianz= 2;
  fprintf(fcut,"%ld\n",ianz);
        
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,"%ld %ld",&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
                
    sscanf(cstring,"%ld %ld",&koi[1],&koi[2]);

    fprintf(fcut,"%9ld %9ld\n",koi[1],koi[2]);
    } 
  fprintf(fcut, "-1 0\n");
  goto L999;
  }

/*----------------------------------------------------------------------
* Schreiben der Dreiecke Nr.3, 14, Torus Nr.15 und Platte Nr.18
*---------------------------------------------------------------------*/        
if (ityp == 3 || ityp == 14 || ityp == 15 || ityp == 18)
  {
  ianz= 6;
  fprintf(fcut,"%ld\n",ianz);
        
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,"%ld %ld",&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
                
    sscanf(cstring, "%ld %ld %ld %ld %ld %ld", 
    &koi[1],&koi[2],&koi[3],&koi[4],&koi[5],&koi[6]);
        
    fprintf(fcut, "%9ld %9ld %9ld %9ld %9ld %9ld\n",
    koi[1],koi[2],koi[3],koi[4],koi[5],koi[6]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0\n");
  goto L999;
  }
        
/*----------------------------------------------------------------------
* Schreiben der Torus Nr.6
*---------------------------------------------------------------------*/        
if (ityp == 6)
  {
  ianz= 3;
  fprintf(fcut,"%ld\n",ianz);
        
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,"%ld %ld",&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
                
    sscanf(cstring, "%ld %ld %ld",&koi[1],&koi[2],&koi[3]);
        
    fprintf(fcut, "%9ld %9ld %9ld\n",koi[1],koi[2],koi[3]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0\n");
  goto L999;
  }
        
/*----------------------------------------------------------------------
* Schreiben der Hexaeder Typ 10
*---------------------------------------------------------------------*/        
if (ityp == 10)
  {
  ianz= 20;
  fprintf(fcut,"%ld\n",ianz);
        
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,"%ld %ld",&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
                
    sscanf(cstring,
    "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", 
    &koi[ 1],&koi[ 2],&koi[ 3],&koi[ 4],&koi[ 5],
    &koi[ 6],&koi[ 7],&koi[ 8],&koi[ 9],&koi[10],
    &koi[11],&koi[12],&koi[13],&koi[14],&koi[15],
    &koi[16],&koi[17],&koi[18],&koi[19],&koi[20]);
        
    fprintf(fcut,
    "%9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\
 %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\n",
    koi[ 1],koi[ 2],koi[ 3],koi[ 4],koi[ 5],
    koi[ 6],koi[ 7],koi[ 8],koi[ 9],koi[10],
    koi[11],koi[12],koi[13],koi[14],koi[15],
    koi[16],koi[17],koi[18],koi[19],koi[20]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n");
  goto L999;
  }

/*----------------------------------------------------------------------
* Schreiben der Platte Typ 19
*---------------------------------------------------------------------*/        
if (ityp == 19)
  {
  ianz= 16;
  fprintf(fcut,"%ld\n",ianz);
        
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,"%ld %ld",&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
                
    sscanf(cstring,
    "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", 
    &koi[ 1],&koi[ 2],&koi[ 3],&koi[ 4],&koi[ 5],
    &koi[ 6],&koi[ 7],&koi[ 8],&koi[ 9],&koi[10],
    &koi[11],&koi[12],&koi[13],&koi[14],&koi[15],
    &koi[16]);
        
    fprintf(fcut,
    "%9ld %9ld %9ld %9ld %9ld %9ld\
 %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\n",
    koi[ 1],koi[ 2],koi[ 3],koi[ 4],koi[ 5],
    koi[ 6],koi[ 7],koi[ 8],koi[ 9],koi[10],
    koi[11],koi[12],koi[13],koi[14],koi[15],
    koi[16]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n");
  goto L999;
  }
        
/*----------------------------------------------------------------------
* Schreiben der Scheiben Nr.11 und Torus Nr.12
*---------------------------------------------------------------------*/        
if (ityp == 11 || ityp == 12)
  {
  ianz= 12;
  fprintf(fcut,"%ld\n",ianz);
        
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,"%ld %ld",&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
                
    sscanf(cstring,
    "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", 
    &koi[ 1],&koi[ 2],&koi[ 3],&koi[ 4],&koi[ 5], &koi[ 6],
    &koi[ 7],&koi[ 8],&koi[ 9],&koi[10],&koi[11],&koi[12]);
        
    fprintf(fcut,
    "%9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\n",
    koi[ 1],koi[ 2],koi[ 3],koi[ 4],koi[ 5],koi[ 6],
    koi[ 7],koi[ 8],koi[ 9],koi[10],koi[11],koi[12]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0 0 0 0 0 0 0\n");
  goto L999;
  }
                
/*----------------------------------------------------------------------
* Schreiben der Tetraeder Nr.16
*---------------------------------------------------------------------*/        
if (ityp == 16)
  {
  ianz= 10;
  fprintf(fcut,"%ld\n",ianz);
        
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring, 254,fz88i1);
    sscanf(cstring,"%ld %ld",&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
                
    sscanf(cstring,"%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", 
    &koi[1],&koi[2],&koi[3],&koi[4],&koi[5],
    &koi[6],&koi[7],&koi[8],&koi[9],&koi[10]);
        
    fprintf(fcut,"%9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\n",
    koi[1],koi[2],koi[3],koi[4],koi[5],
    koi[6],koi[7],koi[8],koi[9],koi[10]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0 0 0 0 0\n");
  goto L999;
  }
                
/*----------------------------------------------------------------------
* Schreiben der Tetraeder Nr.17
*---------------------------------------------------------------------*/        
if (ityp == 17)
  {
  ianz= 4;
  fprintf(fcut,"%ld\n",ianz);

  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,"%ld %ld",&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
                
    sscanf(cstring,"%ld %ld %ld %ld",&koi[1],&koi[2],&koi[3],&koi[4]);
    fprintf(fcut,"%9ld %9ld %9ld %9ld\n",koi[1],koi[2],koi[3],koi[4]);
    } 
  fprintf(fcut, "-1 0 0 0\n");
  goto L999;
  }
        
/*----------------------------------------------------------------------
* Files schliessen
*---------------------------------------------------------------------*/        
L999:;

fprintf(fcut, "-1\n");
fclose(fz88i1);
fclose(fcut);
 
return 0;
}

/***********************************************************************
* CUT88
***********************************************************************/
int cut88(void)
{
extern FR_INT4 MAXGRA,MAXNDL;

FILE *fcut,*fpermdat;   

FR_INT4 *igraph,*igrad,*istart;
FR_INT4 *neu,*irneu,*neuin,*irneuin;
FR_INT4 *level,*ipermb,*iperme;

FR_INT4 np[21];

FR_INT4 nkp,maxgr,ndl;
FR_INT4 igradzp,ifcm,ifrcm,krcm;
FR_INT4 isizegr,neunum,nknot,izeile= 0;
FR_INT4 i,j,k,is,nzp,nnp,maxgd,mingd,minbd;
FR_INT4 nstart,levs,leve,nlev,l;
FR_INT4 mingr,m,nprcm,nprrcm,nzprcm,iflag=0;

int iret;

BOOL *num;

char cpermdat[]="z88h.out";
char cutfile[]= "z88h.in";
char cstring[255];

/*----------------------------------------------------------------------
* File- Operationen
*---------------------------------------------------------------------*/
if((fpermdat=fopen(cpermdat,"w"))==NULL)
  {
  ale88h(AL_NOOUT);;
  wlog88h(0,LOG_NOOUT);
  return 1;
  }
else
  wrim88h(0,TX_OUTOPEN);
  
rewind(fpermdat);

if((fcut=fopen(cutfile,"r"))==NULL)
  {
  ale88h(AL_NOIN);
  wlog88h(0,LOG_NOIN);
  return 1;
  }
else
  wrim88h(0,TX_INOPEN);

rewind(fcut);

/*----------------------------------------------------------------------
* max. Groesse maxgr und ndl
*---------------------------------------------------------------------*/
iret= rdy88h();
if(iret != 0)
  {
  ale88h(iret);
  return(iret);              
  }           

maxgr= MAXGRA;
ndl=   MAXNDL;

/*----------------------------------------------------------------------
* File- Operationen
*---------------------------------------------------------------------*/
fgets(cstring,254,fcut);
sscanf(cstring, "%ld %ld",&nkp,&neunum); /* neunum = -1 */
        
isizegr= (maxgr+1)*(nkp+1);            /* +1 wg. FORTAN 77 */

/*----------------------------------------------------------------------
* Memory anlegen
*---------------------------------------------------------------------*/
if(((igraph =(FR_INT4 *)calloc((size_t)isizegr,sizeof(FR_INT4)))==NULL) ||
   ((igrad  =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((istart =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((neu    =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((irneu  =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((neuin  =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((irneuin=(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((level  =(FR_INT4 *)calloc((size_t)(ndl+1),sizeof(FR_INT4)))==NULL) ||
   ((ipermb =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((iperme =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((num    =(BOOL *)   calloc((size_t)(nkp+1),sizeof(BOOL   )))==NULL) )  
  {
  ale88h(AL_NOMEM);
  wlog88h(0,LOG_NOMEM);
  return 1; 
  }

wrim88h(0,TX_MEMOK);
        
/*----------------------------------------------------------------------
* Aufbau des Graphen auf Grund Knotennummern der Elemente
*---------------------------------------------------------------------*/        
L30:;

fgets(cstring,254,fcut);
sscanf(cstring,"%ld",&nknot);
        
if (nknot > 0)
  {
  L40:; 
  fgets(cstring,254,fcut);
  izeile++;
                
  if (nknot == 2)
    sscanf(cstring,"%ld %ld",&np[1],&np[2]);
   
  if (nknot == 3)
    sscanf(cstring,"%ld %ld %ld",&np[1],&np[2],&np[3]);

  if (nknot == 4)
    sscanf(cstring,"%ld %ld %ld %ld",&np[1],&np[2],&np[3],&np[4]);

  if (nknot == 6)
    sscanf(cstring,"%ld %ld %ld %ld %ld %ld",
    &np[1],&np[2],&np[3],&np[4],&np[5],&np[6]);
                               
  if (nknot == 8)
    sscanf(cstring,"%ld %ld %ld %ld %ld %ld %ld %ld",&np[1],&np[2],&np[3],
    &np[4],&np[5],&np[6],&np[7],&np[8]);

  if (nknot == 10)
    sscanf(cstring,"%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",
    &np[1],&np[2],&np[3],&np[4],&np[5],
    &np[6],&np[7],&np[8],&np[9],&np[10]);

  if (nknot == 16)
    sscanf(cstring,
    "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",
    &np[ 1],&np[ 2],&np[ 3],&np[ 4],&np[ 5],
    &np[ 6],&np[ 7],&np[ 8],&np[ 9],&np[10],
    &np[11],&np[12],&np[13],&np[14],&np[15],
    &np[16]);

  if (nknot == 20)
    sscanf(cstring,
    "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",
    &np[ 1],&np[ 2],&np[ 3],&np[ 4],&np[ 5],
    &np[ 6],&np[ 7],&np[ 8],&np[ 9],&np[10],
    &np[11],&np[12],&np[13],&np[14],&np[15],
    &np[16],&np[17],&np[18],&np[19],&np[20]);
    
                               
  if (np[1] <= 0) goto L30;

  for (i = 1; i <= nknot-1; i++) 
    {
    nzp = np[i];
    for (j= i+1; j <= nknot; j++) 
      {
      nnp = np[j];
      for (k = 1; k <= maxgr; k++) 
        {
        if (igraph[(k-1)*nkp + nzp] == nnp) goto L80;
        if (igraph[(k-1)*nkp + nzp] > 0 )   continue;
        igraph[(k-1)*nkp + nzp] = nnp;
        igrad[nzp]++;
        goto L60;
        } 

      wlog88h(igrad[nzp],LOG_1STOP);
      wrim88h(igrad[nzp],TX_1STOP);
      ale88h(AL_1STOP);
      return 1;

L60:;
      igrad[nnp]++;
      if (igrad[nnp] <= maxgr) goto L70;
      wlog88h(igrad[nzp],LOG_1STOP);
      wrim88h(igrad[nzp],TX_1STOP);
      ale88h(AL_1STOP);
      return 1;
L70:;
      igraph[(igrad[nnp]-1)*nkp + nnp]= nzp;
L80:;           
      } 
    }  

  goto L40;
  }
        
maxgd= igrad[1];
mingd= igrad[1];
        
for (i = 2; i <= nkp; i++)
  {
  maxgd= FR_MAX(maxgd,igrad[i]);
  mingd= FR_MIN(mingd,igrad[i]);
  }

minbd = (maxgd+1)/2;

wrim88h(maxgd,TX_MAXGR);

/*----------------------------------------------------------------------
* Vorgabe bzw. Bestimmung der Startpunkte
*---------------------------------------------------------------------*/        
if (neunum > 0)
  {
  for (i = 1; i <= neunum; i++)
    fscanf(fcut,"%ld",&istart[i]);
  }
else
  {
  neunum= -neunum;
  k=0;
  
L110:;

  for (i = 1; i <= nkp; i++) 
    {
    if (igrad[i]== mingd)
      {
      k++;
      istart[k]= i;
      if (k >= neunum) goto L130;
      }
    } 
  mingd++;
  goto L110;

L130:;

  for (i = 1; i <= neunum; i++) 
    wrim88h(istart[i],TX_STARTNUM);
  }

/*----------------------------------------------------------------------
* Neunummerierung der Knotenpunkte
*---------------------------------------------------------------------*/        
for(is = 1; is <= neunum; is++) 
  {
  nstart= istart[is];
  neu[1]= nstart;
  neuin[nstart] = 1;
  irneu[nkp]= nstart;
  irneuin[nstart]= nkp;

  for(i = 1; i <= nkp; i++) num[i] = FALSE;

  num[nstart]= TRUE;
  level[1]= 1;
  levs= 1;
  leve= 1;
  nlev= 1;
  l= 1;

L150:;  

  for (j = levs; j <= leve; j++) 
    {
    nzp= neu[j];
    igradzp= igrad[nzp];

L160:;

    mingr= maxgr;
    k= 0;

    for (i = 1; i <= igradzp; i++)
      {
      nnp= igraph[(i-1)*nkp + nzp];
      if (num[nnp] || igrad[nnp] > mingr) continue;
      mingr = igrad[nnp];
      k = nnp;
      }

    if (k == 0) goto L180;
    l++;
    neu[l]= k;
    neuin[k]= l;
    irneu[nkp-l+1]= k;
    irneuin[k]= nkp-l+1;
    num[k]= TRUE;
    goto L160;

L180:;
  } 
                
  levs+= level[nlev];
  nlev++;
  wrim88h(nlev,TX_LEVEL);
  level[nlev] = l - levs + 1;
  leve+= level[nlev];
  if (leve < nkp) goto L150;

/*----------------------------------------------------------------------
* Bandbreite m und Profil nprcm der Neunumerierung
*---------------------------------------------------------------------*/        
  m=      0;
  nprcm=  0;
  nprrcm= 0;

  for (i = 1; i <= nkp; i++)
    {
    nzp=      neuin[i];
    nzprcm=   irneuin[i];
    ifcm=     nzp;
    ifrcm=    nzprcm;
    igradzp=  igrad[i];
  
    for (j = 1; j <= igradzp; j++)
      {
      k=    neuin[igraph[(j-1)*nkp + i]];
      m=    FR_MAX(m, abs(k-nzp));
      ifcm= FR_MIN(ifcm, k);
      krcm= irneuin[igraph[(j-1)*nkp + i]];
      ifrcm=FR_MIN(ifrcm, krcm);
      }

    nprcm= nprcm + nzp - ifcm + 1;
    nprrcm= nprrcm + nzprcm - ifrcm + 1;
    }

  wrim88h(nprcm,TX_NPRCM);
  wrim88h(nprrcm,TX_NPRRCM);

  if (ICFLAG == 1)                 /* reverse Cuthill-McKee */
    {
    iflag=  1;
    for (i = 1; i <= nkp; i++) iperme[i]= irneuin[i];
    }  

  if (ICFLAG == 2)                  /* normaler Cuthill-McKee */
    {
    iflag=  2;
    for (i = 1; i <= nkp; i++) iperme[i]= neuin[i];
    }  

  }
        
/*----------------------------------------------------------------------
* Abspeichern des Permutationsvektors
*---------------------------------------------------------------------*/        
wrim88h(iflag,TX_STOPERM);

j= 1;
for (i = 1; i <= nkp; i++)
  {
  if (j < 10)
    {
    fprintf(fpermdat, "%9ld", iperme[i]);
    j++;
    }
  else
    {
    fprintf(fpermdat, "%9ld\n", iperme[i]);
    j= 1;
    }
  }

/*----------------------------------------------------------------------
* Files schliessen, Speicher freigeben fuer CUT2Z88
*---------------------------------------------------------------------*/        
fclose(fcut);
fclose(fpermdat);

free(igraph);
free(igrad);
free(istart);
free(neu);
free(irneu);
free(neuin);
free(irneuin);
free(level);
free(ipermb);
free(iperme);
free(num);  

return 0;
}

/***********************************************************************
* max
***********************************************************************/
FR_INT4 FR_MAX(FR_INT4 i, FR_INT4 j)
{
if (i > j) return i;
else       return j;
}

/***********************************************************************
* min
***********************************************************************/
FR_INT4 FR_MIN(FR_INT4 i, FR_INT4 j)
{
if (i < j) return i;
else       return j;
}

/***********************************************************************
* CUT2Z88
***********************************************************************/
int cut2z88(void)
{
extern FR_INT4 iqflag;

FILE *fpermdat,*fz88i1old,*fz88i2old,*fz88i5old,*fz88i1,*fz88i2,*fz88i5;

double    *x,*y,*z;
double    *wert;
FR_DOUBLE pree,tr1e,tr2e;

FR_INT4   *iperm;
FR_INT4   koi[21];

FR_INT4   i,j;
FR_INT4   nkp=0,ne=0,ndim=0,nfg=0,neg=0,ifrei=0,idummy=0,ityp=0;

FR_INT4   nrb,npr,jele;
FR_INT4   k1,k2,k3,k4,k5,k6,k7,k8;

FR_INT4   *node;
FR_INT4   *kfrei;
FR_INT4   *iflag;
FR_INT4   *ktyp;

char cpermdat[]= "z88h.out";
char cz88i1[]=   "z88i1.txt";
char cz88i2[]=   "z88i2.txt";
char cz88i5[]=   "z88i5.txt";
char cz88i1old[]="z88i1.old";
char cz88i2old[]="z88i2.old";
char cz88i5old[]="z88i5.old";

char cstring[255];

/*----------------------------------------------------------------------
* Vektor koi loeschen
*---------------------------------------------------------------------*/
wrim88h(0,TX_UMSPEI);

for(i = 0;i <= 20; i++) koi[i]= 0;

/*----------------------------------------------------------------------
* File- Operationen: Z88I1.TXT, Z88I2.TXT, Z88I5.TXT -> 
*                    Z88I1.OLD, Z88I2.OLD, Z88I5.OLD
*---------------------------------------------------------------------*/
if ((fz88i1old= fopen(cz88i1old,"r")) != NULL)
  {
  fclose(fz88i1old);
  remove(cz88i1old);
  }

if ((fz88i2old= fopen(cz88i2old,"r")) != NULL)
  {
  fclose(fz88i2old);
  remove(cz88i2old);
  }

if(iqflag == 1)
  {
  if ((fz88i5old= fopen(cz88i5old,"r")) != NULL)
    {
    fclose(fz88i5old);
    remove(cz88i5old);
    }
  }

rename(cz88i1,cz88i1old);
rename(cz88i2,cz88i2old);
if(iqflag == 1) rename(cz88i5,cz88i5old);

fpermdat= fopen(cpermdat,"r");
	
fz88i1old= fopen(cz88i1old,"r");
fz88i2old= fopen(cz88i2old,"r");
if(iqflag == 1) fz88i5old= fopen(cz88i5old,"r");

fz88i1=    fopen(cz88i1,"w");
fz88i2=    fopen(cz88i2,"w");
if(iqflag == 1) fz88i5=    fopen(cz88i5,"w");
        
wrim88h(0,TX_TXT2OLD);

/*----------------------------------------------------------------------
* Z88I1.TXT
*---------------------------------------------------------------------*/

/*======================================================================
* 1.Zeile
*=====================================================================*/
fgets(cstring,254,fz88i1old);
fputs(cstring,fz88i1);
        
sscanf(cstring,"%ld %ld %ld %ld %ld",&ndim,&nkp,&ne,&nfg,&neg);
        
/*======================================================================
* Memory anlegen
*=====================================================================*/
if(((iperm= (FR_INT4 *)   calloc((size_t)nkp+1,sizeof(FR_INT4  )))==NULL) || 
   ((  x  = (FR_DOUBLE *) calloc((size_t)nkp+1,sizeof(FR_DOUBLE)))==NULL) ||
   ((  y  = (FR_DOUBLE *) calloc((size_t)nkp+1,sizeof(FR_DOUBLE)))==NULL) ||
   ((  z  = (FR_DOUBLE *) calloc((size_t)nkp+1,sizeof(FR_DOUBLE)))==NULL) ||
   ((ktyp = (FR_INT4 *)   calloc((size_t)ne+1, sizeof(FR_INT4  )))==NULL))
  {
  ale88h(AL_NOMEM);
  wlog88h(0,LOG_NOMEM);
  return 1; 
  }

wrim88h(0,TX_MEMOK);
        
/*======================================================================
* Knoten
*=====================================================================*/
wrim88h(0,TX_WRII1);

for(i = 1; i <= nkp; i++)
  fscanf(fpermdat,"%ld",&iperm[i]);

for(i = 1; i <= nkp; i++)
  {
  fgets(cstring,254,fz88i1old);
  sscanf(cstring,"%ld %ld %lf %lf %lf",
  &idummy,&ifrei,&x[iperm[i]],&y[iperm[i]],&z[iperm[i]]);
  }
        
for(i = 1; i <= nkp; i++)
  fprintf(fz88i1,"%9ld %9ld %+#13.5lE %+#13.5lE %+#13.5lE Knoten #%ld\n",
  i,ifrei,x[i],y[i],z[i],i);

/*======================================================================
* Koinzidenz
*=====================================================================*/
for(i = 1; i <= ne; i++)
  {
  fgets (cstring,254,fz88i1old);
  sscanf(cstring,"%ld %ld",&idummy,&ityp);
  fputs (cstring,fz88i1);

  ktyp[i]= ityp;

  fgets (cstring,254,fz88i1old);
                
  if(ityp == 1 || ityp == 7 || ityp == 8 || ityp == 20)
    {
    sscanf(cstring,"%ld %ld %ld %ld %ld %ld %ld %ld",
    &koi[1],&koi[2],&koi[3],&koi[4],&koi[5],&koi[6],&koi[7],&koi[8]);

    fprintf(fz88i1,"%9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\n",
    iperm[koi[1]],iperm[koi[2]],iperm[koi[3]],iperm[koi[4]],
    iperm[koi[5]],iperm[koi[6]],iperm[koi[7]],iperm[koi[8]]);
    }

  if(ityp == 2 || ityp == 4 || ityp == 5 || ityp == 9 || ityp == 13)
    {
    sscanf(cstring,"%ld %ld",&koi[1],&koi[2]);

    fprintf(fz88i1,"%9ld %9ld\n",iperm[koi[1]],iperm[koi[2]]);
    }

  if(ityp == 3 || ityp == 14 || ityp == 15 || ityp == 18)
    {
    sscanf(cstring,"%ld %ld %ld %ld %ld %ld",
    &koi[1],&koi[2],&koi[3],&koi[4],&koi[5],&koi[6]);

    fprintf(fz88i1,"%9ld %9ld %9ld %9ld %9ld %9ld\n",
    iperm[koi[1]],iperm[koi[2]],iperm[koi[3]],
    iperm[koi[4]],iperm[koi[5]],iperm[koi[6]]);
    }

  if(ityp == 6)
    {
    sscanf(cstring,"%ld %ld %ld",
    &koi[1],&koi[2],&koi[3]);

    fprintf(fz88i1,"%9ld %9ld %9ld\n",
    iperm[koi[1]],iperm[koi[2]],iperm[koi[3]]);
    }

  if(ityp == 10)
    {
    sscanf(cstring,
    "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",
    &koi[ 1],&koi[ 2],&koi[ 3],&koi[ 4],&koi[ 5],
    &koi[ 6],&koi[ 7],&koi[ 8],&koi[ 9],&koi[10],
    &koi[11],&koi[12],&koi[13],&koi[14],&koi[15],
    &koi[16],&koi[17],&koi[18],&koi[19],&koi[20]);

    fprintf(fz88i1,"%9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\
 %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\n",
    iperm[koi[ 1]],iperm[koi[ 2]],iperm[koi[ 3]],iperm[koi[ 4]],iperm[koi[ 5]],
    iperm[koi[ 6]],iperm[koi[ 7]],iperm[koi[ 8]],iperm[koi[ 9]],iperm[koi[10]],
    iperm[koi[11]],iperm[koi[12]],iperm[koi[13]],iperm[koi[14]],iperm[koi[15]],
    iperm[koi[16]],iperm[koi[17]],iperm[koi[18]],iperm[koi[19]],iperm[koi[20]]);
    }

  if(ityp == 19)
    {
    sscanf(cstring,
    "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",
    &koi[ 1],&koi[ 2],&koi[ 3],&koi[ 4],&koi[ 5],
    &koi[ 6],&koi[ 7],&koi[ 8],&koi[ 9],&koi[10],
    &koi[11],&koi[12],&koi[13],&koi[14],&koi[15],
    &koi[16]);

    fprintf(fz88i1,"%9ld %9ld %9ld %9ld %9ld %9ld\
 %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\n",
    iperm[koi[ 1]],iperm[koi[ 2]],iperm[koi[ 3]],iperm[koi[ 4]],iperm[koi[ 5]],
    iperm[koi[ 6]],iperm[koi[ 7]],iperm[koi[ 8]],iperm[koi[ 9]],iperm[koi[10]],
    iperm[koi[11]],iperm[koi[12]],iperm[koi[13]],iperm[koi[14]],iperm[koi[15]],
    iperm[koi[16]]);
    }

  if(ityp == 11 || ityp == 12)
    {
    sscanf(cstring,
    "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",
    &koi[ 1],&koi[ 2],&koi[ 3],&koi[ 4],&koi[ 5],&koi[ 6],
    &koi[ 7],&koi[ 8],&koi[ 9],&koi[10],&koi[11],&koi[12]);

    fprintf(fz88i1,"%9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\n",
    iperm[koi[ 1]],iperm[koi[ 2]],iperm[koi[ 3]],iperm[koi[ 4]],
    iperm[koi[ 5]],iperm[koi[ 6]],iperm[koi[ 7]],iperm[koi[ 8]],
    iperm[koi[ 9]],iperm[koi[10]],iperm[koi[11]],iperm[koi[12]]);
    }

  if(ityp == 16)
    {
    sscanf(cstring,"%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",
    &koi[1],&koi[2],&koi[3],&koi[4],&koi[5],
    &koi[6],&koi[7],&koi[8],&koi[9],&koi[10]);

    fprintf(fz88i1,"%9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\n",
    iperm[koi[1]],iperm[koi[2]],iperm[koi[3]],iperm[koi[4]],iperm[koi[5]],
    iperm[koi[6]],iperm[koi[7]],iperm[koi[8]],iperm[koi[9]],iperm[koi[10]]);
    }

  if(ityp == 17)
    {
    sscanf(cstring,"%ld %ld %ld %ld",
    &koi[1],&koi[2],&koi[3],&koi[4]);

    fprintf(fz88i1,"%9ld %9ld %9ld %9ld\n",
    iperm[koi[1]],iperm[koi[2]],iperm[koi[3]],iperm[koi[4]]);
    }
  }
                
/*======================================================================
* Materialgesetze
*=====================================================================*/
for(i = 1; i <= neg; i++)
  {
  fgets(cstring,254,fz88i1old);
  fputs(cstring,fz88i1);
  }

/*======================================================================
* Files schliessen
*=====================================================================*/
fclose(fz88i1);
fclose(fz88i1old);
fclose(fpermdat);  
                
/*----------------------------------------------------------------------
* Z88I2.TXT
*---------------------------------------------------------------------*/
/*======================================================================
* Anzahl Randbedingungen
*=====================================================================*/
fgets(cstring,254,fz88i2old);
sscanf(cstring,"%ld",&nrb);
fputs(cstring,fz88i2);

/*======================================================================
* Memory anlegen
*=====================================================================*/
if(
((node = (FR_INT4 *)calloc((size_t)nrb+1,sizeof(FR_INT4)))==NULL) ||
((kfrei= (FR_INT4 *)calloc((size_t)nrb+1,sizeof(FR_INT4)))==NULL) ||
((iflag= (FR_INT4 *)calloc((size_t)nrb+1,sizeof(FR_INT4)))==NULL) ||
((wert = (double  *)calloc((size_t)nrb+1,sizeof(double )))==NULL))
  {
  ale88h(AL_NOMEM);
  wlog88h(0,LOG_NOMEM);
  return 1; 
  }

wrim88h(0,TX_MEMOK);
wrim88h(0,TX_WRII2);

for(i = 1; i <= nrb; i++)
  {
  fgets(cstring,254,fz88i2old);
  sscanf(cstring,"%ld %ld %ld %lf",&node[i],&kfrei[i],&iflag[i],&wert[i]);
  }
        
for (i = 1; i <= nkp; i++)
  {
  for (j = 1; j <= nrb; j++)
    {
    if(i == iperm[node[j]])
      fprintf(fz88i2,"%9ld %9ld %9ld %13.5lf\n",i,kfrei[j],iflag[j],wert[j]);                      
    }
  }
        
/*----------------------------------------------------------------------
* Files schliessen
*---------------------------------------------------------------------*/
fclose(fz88i2);  
fclose(fz88i2old);  

/*----------------------------------------------------------------------
* Z88I5.TXT
*---------------------------------------------------------------------*/
/*======================================================================
* Anzahl Elemente mit Lasten
*=====================================================================*/
if(iqflag == 1)
  {
  fgets(cstring,254,fz88i5old);
  sscanf(cstring,"%ld",&npr);
  fputs(cstring,fz88i5);

  wrim88h(0,TX_MEMOK);
  wrim88h(0,TX_WRII5);

  for(j = 1; j <= npr; j++)
    {
    fgets(cstring,254,fz88i5old);
    sscanf(cstring,"%ld",&jele);

/*======================================================================
* Elemente 7,8,14 und 15: 
*=====================================================================*/
    if(ktyp[jele]== 7  || ktyp[jele]== 8 || 
       ktyp[jele]== 14 || ktyp[jele]== 15)
      { 
      sscanf(cstring,"%ld %lf %lf %ld %ld %ld",
        &jele,&pree,&tr1e,&k1,&k2,&k3);
      fprintf(fz88i5,"%9ld %13.5lf %13.5lf %9ld %9ld %9ld\n",
        jele,pree,tr1e,iperm[k1],iperm[k2],iperm[k3]);
      }  

/*======================================================================
* Element 17: 
*=====================================================================*/
    if(ktyp[jele]== 17)
      { 
      sscanf(cstring,"%ld %lf %ld %ld %ld",&jele,&pree,&k1,&k2,&k3);
      fprintf(fz88i5,"%9ld %13.5lf %9ld %9ld %9ld\n",
        jele,pree,iperm[k1],iperm[k2],iperm[k3]);
      }  

/*======================================================================
* Elemente 11 und 12:
*=====================================================================*/
    if(ktyp[jele]== 11 || ktyp[jele]== 12)
      { 
      sscanf(cstring,"%ld %lf %lf %ld %ld %ld %ld",
        &jele,&pree,&tr1e,&k1,&k2,&k3,&k4);
      fprintf(fz88i5,"%9ld %13.5lf %13.5lf %9ld %9ld %9ld %9ld\n",
        jele,pree,tr1e,iperm[k1],iperm[k2],iperm[k3],iperm[k4]);
      }  

/*======================================================================
* Element 1:
*=====================================================================*/
    if(ktyp[jele]== 1)
      { 
      sscanf(cstring,"%ld %lf %lf %lf %ld %ld %ld %ld",
        &jele,&pree,&tr1e,&tr2e,&k1,&k2,&k3,&k4);
      fprintf(fz88i5,"%9ld %13.5lf %13.5lf %13.5lf %9ld %9ld %9ld %9ld\n",
        jele,pree,tr1e,tr2e,iperm[k1],iperm[k2],iperm[k3],iperm[k4]);
      }  

/*======================================================================
* Element 16
*=====================================================================*/
    if(ktyp[jele]== 16)
      { 
      sscanf(cstring,"%ld %lf %ld %ld %ld %ld %ld %ld",
        &jele,&pree,&k1,&k2,&k3,&k4,&k5,&k6);
      fprintf(fz88i5,"%9ld %13.5lf %9ld %9ld %9ld %9ld %9ld %9ld\n",
        jele,pree,
        iperm[k1],iperm[k2],iperm[k3],iperm[k4],iperm[k5],iperm[k6]);
      }

/*======================================================================
* Element 10:
*=====================================================================*/
    if(ktyp[jele]== 10)
      { 
      sscanf(cstring,"%ld %lf %lf %lf %ld %ld %ld %ld %ld %ld %ld %ld",
        &jele,&pree,&tr1e,&tr2e,&k1,&k2,&k3,&k4,&k5,&k6,&k7,&k8);
      fprintf(fz88i5,
        "%9ld %13.5lf %13.5lf %13.5lf %9ld %9ld %9ld %9ld %9ld %9ld %9ld %9ld\n",
        jele,pree,tr1e,tr2e,iperm[k1],iperm[k2],iperm[k3],iperm[k4],
        iperm[k5],iperm[k6],iperm[k7],iperm[k8]);
      }  

/*======================================================================
* die drei Plattenelemente 18,19 und 20
*=====================================================================*/
    if(ktyp[jele]== 18 || ktyp[jele]== 19 || ktyp[jele]== 20)
      { 
      sscanf(cstring,"%ld %lf",&jele,&pree);
      fprintf(fz88i5,"%9ld %13.5lf\n",jele,pree);
      }

    }

  fclose(fz88i5);   
  fclose(fz88i5old);   
  }
  	
/*----------------------------------------------------------------------
* Ende Z88H
*---------------------------------------------------------------------*/
wrim88h(0,TX_Z88DONE);

return 0;
}



