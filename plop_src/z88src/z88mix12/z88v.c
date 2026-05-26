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
* Z88V fuer Windows
* 4.10.2005 Rieg
***********************************************************************/

/***********************************************************************
* Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88v.h>
#include <windows.h>
#include <commctrl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#endif

/***********************************************************************
* Window- Function- Deklarationen
***********************************************************************/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND InitToolBar   (HWND hParent);

/***********************************************************************
*  externe Variable
***********************************************************************/
HDC        hDC;
HWND       hToolBar;
HMENU      hMenuGer,hMenuEng;
HINSTANCE  hInstance;

/***********************************************************************
* Functions
***********************************************************************/
int dyn88v(void);
int ale88v(int iret);
int g1i188(HWND hWnd);
int g2i188(HWND hWnd);
int g3i188(HWND hWnd);
int g4i188(HWND hWnd);
int g5i188(HWND hWnd);
int g1i288(HWND hWnd);
int g2i288(HWND hWnd);
int g1i388(HWND hWnd);
int g1i488(HWND hWnd);
int g1i588(HWND hWnd);
int g2i588(HWND hWnd);
int lan88v(void);

/***********************************************************************
* Globale Variable
***********************************************************************/
FILE *fdatei,*fdyn,*fwlo,*fcfg;

/*
**   fdatei= z88ni.txt,z88i1.txt,z88i2.txt,z88i3.txt,z88i4.txt,z88i5.txt
**   fdyn  = z88.dyn
**   fwlo  = z88e.log
**   fcfg  = z88com.cfg
*/

char cdyn[8] = "z88.dyn";
char clog[9] = "z88v.log";
char cfg[11] = "z88com.cfg";

FR_INT4AY jtyp;
FR_INT4AY jzeile;
FR_INT4AY ifrei;

FR_INT4 IDYNMEM,LANG;
FR_INT4 MAXSE,MAXESS,MAXKSS,MAXAN;
FR_INT4 MAXGS,MAXKOI,MAXK,MAXE,MAXNFG,MAXNEG,MAXPR,MAXSOR,MAXPUF;
FR_INT4 MFACCOMMON,MAXGP;
FR_INT4 MAXESM=3600;

FR_INT4 ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag,niflag,nrb,npr;
FR_INT4 iwarn,izeile,iruni1,ispann,ifnii1;

char cdatei[10];

/*--------------------------------------------------------------------------
* Char-Arrays
*-------------------------------------------------------------------------*/
char cstore[256];
char cbcall[128];
char cbpref[128];
char cbhelp[512];
char cmess[1024];

/***********************************************************************
* WinMain- Function
***********************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR lpszCmdLine, int nCmdShow)
{
extern FR_INT4 iruni1;
extern FR_INT4 ispann;
extern FR_INT4 ifnii1;

HWND           hWnd;
MSG            msg;
WNDCLASSEX     wndclass;

char           capname[10];

iruni1= 0;    /* Check Z88I1.TXT gelaufen ? ja = 1     */
ispann= 0;    /* Spannungsfile noetig ? ja = 1         */
ifnii1= 0;    /* Vorwahl fuer Z88I1.TXT, Z88NI.TXT = 1 */

/***********************************************************************
* Handles kommen lassen, window oeffnen
***********************************************************************/
strcpy(capname, "Z88V");

wndclass.cbSize        = sizeof(wndclass);
wndclass.style         = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc   = WndProc;
wndclass.cbClsExtra    = 0;
wndclass.cbWndExtra    = 0;
wndclass.hInstance     = hInstance;
wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88V));
wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
wndclass.hbrBackground = CreateSolidBrush(RGB(128,0,128));
wndclass.lpszMenuName  = capname;
wndclass.lpszClassName = capname;
wndclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88V));

RegisterClassEx(&wndclass);

hWnd = CreateWindow(capname,"Z88 File Checker Z88V",
                    WS_OVERLAPPEDWINDOW,
                     10, 220,
                    400, 200,
                    NULL, NULL, hInstance, NULL);

InitCommonControls();

ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);

while(GetMessage(&msg, NULL, 0, 0))
  {
  TranslateMessage(&msg);
  DispatchMessage(&msg);
  }

return msg.wParam;
}

/*************************************************************************
* Main Window Procedure
*************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message,
                         WPARAM wParam, LPARAM lParam)
{
extern FR_INT4    LANG;
extern FR_INT4    MAXSE,MAXESS,MAXKSS,MAXAN;
extern FR_INT4    MAXGS,MAXKOI,MAXK,MAXE,MAXNFG,MAXNEG;
extern FR_INT4    MAXPR,MAXSOR,MAXPUF,MFACCOMMON,MAXGP,MAXESM;

extern HMENU      hMenuGer,hMenuEng;
extern HINSTANCE  hInstance;
extern HDC        hDC;

PAINTSTRUCT       ps;

FR_INT4           isumf=0,isumi1=0,isumi2=0,is2sic=0;

int               ier,imess,iret;

size_t            laenge;

/*************************************************************************
* Messages abhandeln
*************************************************************************/
switch (Message)
  {

/*------------------------------------------------------------------------
* WM_CREATE
*-----------------------------------------------------------------------*/
  case WM_CREATE:
/*======================================================================
* hInstance kommen lassen
*=====================================================================*/
    hInstance= (HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE);

/*======================================================================
* Sprache feststellen
*=====================================================================*/
    iret= lan88v();
    if(iret != 0)
      {
      ale88v(iret);
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
    iret= dyn88v();
    if(iret != 0) 
      { 
      ale88v(iret);
      PostQuitMessage(0);
      return 0;
      }           

/*======================================================================
* Toolbar
*=====================================================================*/
    hToolBar= InitToolBar(hWnd);

  return 0;

/*------------------------------------------------------------------------
* WM_MOVE
*-----------------------------------------------------------------------*/
  case WM_MOVE:
  return 0;

/*------------------------------------------------------------------------
* WM_SIZE
*-----------------------------------------------------------------------*/
  case WM_SIZE:
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
          if(LANG == 1) pReply= "OnLine-Hilfe fuer Filechecker";
          if(LANG == 2) pReply= "OnLine Help for File Checker";
        break;

        case ITC_Z88DYN:
          if(LANG == 1) pReply= "Zeige durch Z88.DYN definierten Speicher";
          if(LANG == 2) pReply= "Show Memory defined by Z88.DYN";
        break;

        case ITC_Z88NITXT:
          if(LANG == 1) pReply= "Untersuche Netzgenerator-Datei Z88NI.TXT";
          if(LANG == 2) pReply= "Investigate Net Generator File Z88NI.TXT";
        break;

        case ITC_Z88I1TXT:
          if(LANG == 1) pReply= "Untersuche FE-Struktur-Datei Z88I1.TXT";
          if(LANG == 2) pReply= "Investigate FE Structure File Z88I1.TXT";
        break;

        case ITC_Z88I2TXT:
          if(LANG == 1) pReply= "Untersuche Randbedingungs-Datei Z88I2.TXT";
          if(LANG == 2) pReply= "Investigate Boundary Con. File Z88I2.TXT";
        break;

        case ITC_Z88I3TXT:
          if(LANG == 1) pReply= "Untersuche Spannungsparameter D. Z88I3.TXT";
          if(LANG == 2) pReply= "Investigate Stress Flag File Z88I3.TXT";
        break;

        case ITC_Z88I4TXT:
          if(LANG == 1) pReply= "Untersuche Parameter Iterationssolver Z88I4.TXT";
          if(LANG == 2) pReply= "Investigate Para File Iteration Solver Z88I4.TXT";
        break;

        case ITC_Z88I5TXT:
          if(LANG == 1) pReply= "Untersuche Flaechenlast-Datei Z88I5.TXT";
          if(LANG == 2) pReply= "Investigate Surface Loads File Z88I5.TXT";
        break;
        }
      lstrcpy(lpttt->szText,pReply);
      }
    return 0;  /* sehr wichtig */
    }

/*------------------------------------------------------------------------
* WM_COMMAND
*-----------------------------------------------------------------------*/
  case WM_COMMAND:
    switch (LOWORD(wParam))
      {

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
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONHAND);
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
        if(LANG == 1) strcat(cbhelp,"g88v.htm");
        if(LANG == 2) strcat(cbhelp,"e88v.htm");
        imess= WinExec(cbhelp,SW_SHOW);
        if(imess < 33)
          {
          if(LANG == 1) strcpy(cmess,
          "Internet Browser konnte nicht gestartet werden !");
          if(LANG == 2) strcpy(cmess,
          "Could not launch Internet Browser !");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONHAND);
          }

      return 0;

/*========================================================================
* Z88.DYN
*=======================================================================*/
      case IDM_Z88DYN:
      case ITC_Z88DYN:
        if(MAXSE <= 0 || MAXESS <= 0 || MAXKSS <= 0 || MAXAN <= 0)
          {
          if(LANG == 1) strcpy(cmess,
            "Irgendein Wert in Gruppe NET kleiner oder gleich 0    STOP");
          if(LANG == 2) strcpy(cmess,
            "One or more entries in group NET less or equal 0   STOP ");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONHAND);
          fclose(fdyn);
          PostQuitMessage(0);
          return 0;
          }  

        if(MAXGS  <= 0 || MAXKOI <= 0 || MAXK   <= 0 ||
           MAXE   <= 0 || MAXNFG <= 0 || MAXNEG <= 0 ||
           MAXSOR <= 0 || MAXPUF <= 0 || MAXPR <= 0)
          {
          if(LANG == 1) strcpy(cmess,
            "Irgendein Wert in Gruppe COMMON kleiner oder gleich 0    STOP");
          if(LANG == 2) strcpy(cmess,
            "One or more entries in group COMMON less or equal 0   STOP ");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONHAND);
          fclose(fdyn);
          PostQuitMessage(0);
          return 0;
          }  

        if(MFACCOMMON <= 0 || MAXGP <= 0)
          {
          if(LANG == 1) strcpy(cmess,
            "Irgendein Wert in Gruppe PLOT kleiner oder gleich 0    STOP");
          if(LANG == 2) strcpy(cmess,
            "One or more entries in group PLOT less or equal 0   STOP ");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONHAND);
          fclose(fdyn);
          PostQuitMessage(0);
          return 0;
          }  

/*=====================================================================*
*  Z88F
*=====================================================================*/
  isumf =   (MAXGS+1)*sizeof(FR_DOUBLE);  /* gs */
  isumf+=   (MAXESM+1)*sizeof(FR_DOUBLE); /* se */
  isumf+= 2*(MAXNFG+1)*sizeof(FR_DOUBLE); /* rs, fak */
  isumf+= 3*(MAXK+1)*sizeof(FR_DOUBLE);   /* x,y,z */
  isumf+= 3*(MAXNEG+1)*sizeof(FR_DOUBLE); /* emod, rnue, qpara */
  isumf+=   (MAXNFG+1)*sizeof(FR_INT4);   /* ip */
  isumf+=   (MAXKOI+1)*sizeof(FR_INT4);   /* koi */
  isumf+= 2*(MAXK+1)*sizeof(FR_INT4);     /* ifrei, ioffs */
  isumf+= 2*(MAXE+1)*sizeof(FR_INT4);     /* koffs, ityp */
  isumf+= 3*(MAXNEG+1)*sizeof(FR_INT4);   /* ivon,ibis,intord */
  isumf+= 6*(MAXNEG+1)*sizeof(FR_DOUBLE); /* riyy,eyy,rizz,ezz,rit,wt */
  isumf+=10*(MAXPR+1) *sizeof(FR_INT4);   /* nep,noi,noffs */
  isumf+= 3*(MAXPR+1) *sizeof(FR_DOUBLE); /* pres,tr1,tr2 */

  isumf/= 1048576;   /* in MegaByte */

/*=====================================================================*
*  Z88I1
*=====================================================================*/
  isumi1 =   (MAXSOR+1)*sizeof(struct FR_SIJ);   /* IJ */
  isumi1+= 3*(MAXK+1)  *sizeof(FR_DOUBLE);       /* x,y,z */
  isumi1+= 3*(MAXNEG+1)*sizeof(FR_DOUBLE);       /* emod, rnue, qpara */
  isumi1+=   (MAXNFG+1)*sizeof(FR_INT4);         /* ip */
  isumi1+=   (MAXSOR+1)*sizeof(FR_INT4);         /* iez */
  isumi1+=   (MAXKOI+1)*sizeof(FR_INT4);         /* koi */
  isumi1+= 2*(MAXK+1)  *sizeof(FR_INT4);         /* ifrei, ioffs */
  isumi1+= 2*(MAXE+1)  *sizeof(FR_INT4);         /* koffs, ityp */
  isumi1+= 3*(MAXNEG+1)*sizeof(FR_INT4);         /* ivon,ibis,intord */
  isumi1+= 6*(MAXNEG+1)*sizeof(FR_DOUBLE); /* riyy,eyy,rizz,ezz,rit,wt */
  isumi1+=   (MAXPUF+1)*sizeof(FR_INT4);         /* kc */

  isumi1/= 1048576;

/*=====================================================================*
*  Z88I2
*=====================================================================*/
  isumi2 =   (MAXGS+1) *sizeof(FR_DOUBLE);     /* GS */

  isumi2+=   (MAXESM+1)*sizeof(FR_DOUBLE);     /* se */
  isumi2+= 7*(MAXNFG+1)*sizeof(FR_DOUBLE);     /* rs,fak,xi,xa,v,pk,zz*/
  isumi2+= 3*(MAXK+1)  *sizeof(FR_DOUBLE);     /* x,y,z */
  isumi2+= 3*(MAXNEG+1)*sizeof(FR_DOUBLE);     /* emod, rnue, qpara */
  isumi2+=   (MAXNFG+1)*sizeof(FR_INT4);       /* ip */
  isumi2+=   (MAXGS+1) *sizeof(FR_INT4);       /* iez */
  isumi2+=   (MAXKOI+1)*sizeof(FR_INT4);       /* koi */
  isumi2+= 2*(MAXK+1)  *sizeof(FR_INT4);       /* ifrei, ioffs */
  isumi2+= 2*(MAXE+1)  *sizeof(FR_INT4);       /* koffs, ityp */
  isumi2+= 3*(MAXNEG+1)*sizeof(FR_INT4);       /* ivon,ibis,intord */
  isumi2+= 6*(MAXNEG+1)*sizeof(FR_DOUBLE);     /* riyy,eyy,rizz,ezz,rit,wt */
  isumi2+=10*(MAXPR+1) *sizeof(FR_INT4);       /* nep,noi,noffs */
  isumi2+= 3*(MAXPR+1) *sizeof(FR_DOUBLE);     /* pres,tr1,tr2 */

  isumi2/= 1048576;   /* in MegaByte */

  is2sic= (MAXGS+1) *sizeof(FR_DOUBLE) /1048576;     /* CI */

/*=====================================================================*
*  und ausschreiben
*=====================================================================*/
  if(LANG == 1) sprintf(cmess,
    "Z88.DYN definiert momentan folgende Circa-Speicherbedarfe:\n\n\
    %ld MB fuer Z88F\n\
    %ld MB fuer Z88I1\n\
    %ld MB fuer Z88I2 mit SOR\n\
    %ld MB fuer Z88I2 mit SIC",
    isumf,isumi1,isumi2,(isumi2+is2sic));

  if(LANG == 2) sprintf(cmess,
    "Z88.DYN currently defines the following about- Memory Needs:\n\n\
    %ld MB for Z88F\n\
    %ld MB for Z88I1\n\
    %ld MB for Z88I2 with SOR\n\
    %ld MB for Z88I2 with SIC",
    isumf,isumi1,isumi2,(isumi2+is2sic));
  MessageBox(NULL,cmess,"Z88V",MB_OK | MB_ICONINFORMATION);

  return 0;

/*========================================================================
* Z88NI.TXT
*=======================================================================*/
      case IDM_Z88NITXT:
      case ITC_Z88NITXT:
        ifnii1= 1;
        iwarn= 0;
        strcpy(cdatei,"z88ni.txt");
        fdatei= fopen(cdatei,"r");
        if(fdatei == NULL)
          {
          if(LANG == 1) strcpy(cmess,"Kann Z88NI.TXT nicht oeffnen");
          if(LANG == 2) strcpy(cmess,"Cannot open Z88NI.TXT");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONQUESTION);
          goto L10;
          }
        rewind(fdatei);

        if(LANG == 1) strcpy(cmess,"Nun checken von Z88NI.TXT");
        if(LANG == 2) strcpy(cmess,"Now checking Z88NI.TXT");
        MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);

        ier= g1i188(hWnd);
        if (ier != 0) fclose(fdatei);

        if(ier == 0) ier= g2i188(hWnd);
        if (ier != 0) fclose(fdatei);

        if(ier == 0) ier= g3i188(hWnd);
        if (ier != 0) fclose(fdatei);

        if(ier == 0) ier= g4i188(hWnd);
        if (ier != 0) fclose(fdatei);

        if(ier == 0) ier= g5i188(hWnd);
        if (ier != 0) fclose(fdatei);

        if(iwarn == 0 && ier == 0)
          {
          if(LANG == 1) strcpy(cmess,
          "Z88NI.TXT gecheckt: Keine Fehler und Warnungen entdeckt");
          if(LANG == 2) strcpy(cmess,
          "Z88NI.TXT was checked: No Errors and Warnings detected");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
          }

        if(iwarn != 0 && ier == 0)
          { 
          if(LANG == 1) sprintf(cmess,
          "Z88NI.TXT gecheckt: Keine Fehler, aber %ld Warnungen entdeckt",
          iwarn);
          if(LANG == 2) sprintf(cmess,
          "Z88NI.TXT was checked: No Errors, but %ld Warnings detected",iwarn);
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
          }

        if(ier != 0)
          {
          if(LANG == 1) strcpy(cmess,
          "Z88NI.TXT gecheckt: Fehler entdeckt\nZ88NI.TXT ist geschlossen. \
Sie koennen in Z88V bleiben und parallel dazu Z88NI.TXT korrigieren. Dann \
erneut checken");
          if(LANG == 2) strcpy(cmess,
          "Z88NI.TXT was checked: Errors detected\nZ88NI.TXT is closed. \
You can stay in Z88V and edit Z88NI.TXT. Then check again");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONEXCLAMATION);
          }

      L10:; /* hier raus, wenn File nicht geoeffnet werden konnte */
      return 0;

/*==========================================================================
* Z88I1.TXT
*=========================================================================*/
      case IDM_Z88I1TXT:
      case ITC_Z88I1TXT:
        ifnii1= 0;
        iwarn= 0;
        strcpy(cdatei,"z88i1.txt");
        fdatei= fopen(cdatei,"r");
        if(fdatei == NULL)
          {
          if(LANG == 1) strcpy(cmess,"Kann Z88I1.TXT nicht oeffnen");
          if(LANG == 2) strcpy(cmess,"Cannot open Z88I1.TXT");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONQUESTION);
          goto L20;
          }
        rewind(fdatei);

        if(LANG == 1) strcpy(cmess,"Nun checken von Z88I1.TXT");
        if(LANG == 2) strcpy(cmess,"Now checking Z88I1.TXT");
        MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);

        ier= g1i188(hWnd);
        if (ier != 0) fclose(fdatei);

        if(ier == 0) ier= g2i188(hWnd);
        if (ier != 0) fclose(fdatei);

        if(ier == 0) ier= g3i188(hWnd);
        if (ier != 0) fclose(fdatei);

        if(ier == 0) ier= g4i188(hWnd);
        if (ier != 0) fclose(fdatei);

        if(iwarn == 0 && ier == 0)
          {
          iruni1= 1;
          if(LANG == 1) strcpy(cmess,
          "Z88I1.TXT gecheckt: Keine Fehler und Warnungen entdeckt");
          if(LANG == 2) strcpy(cmess,
          "Z88I1.TXT was checked: No Errors and Warnings detected");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
          }
          
        if(iwarn != 0 && ier == 0)
          { 
          iruni1= 1;
          if(LANG == 1) sprintf(cmess,
          "Z88I1.TXT gecheckt: Keine Fehler, aber %ld Warnungen entdeckt",
          iwarn);
          if(LANG == 2) sprintf(cmess,
          "Z88I1.TXT was checked: No Errors, but %ld Warnings detected",iwarn);
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
          }

        if(ier != 0)
          {
          if(LANG == 1) strcpy(cmess,
          "Z88I1.TXT gecheckt: Fehler entdeckt\nZ88I1.TXT ist geschlossen. \
Sie koennen in Z88V bleiben und parallel dazu Z88I1.TXT korrigieren. Dann \
erneut checken");
          if(LANG == 2) strcpy(cmess,
          "Z88I1.TXT was checked: Errors detected\nZ88I1.TXT is closed. \
You can stay in Z88V and edit Z88I1.TXT. Then check again");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONEXCLAMATION);
          }

      L20:; /* hier raus, wenn File nicht geoeffnet werden konnte */
      return 0;

/*==========================================================================
* Z88I2.TXT
*=========================================================================*/
      case IDM_Z88I2TXT:
      case ITC_Z88I2TXT:
        if(iruni1 == 0)
          {
          if(LANG == 1) strcpy(cmess,"Bitte erst Z88I1.TXT checken");
          if(LANG == 2) strcpy(cmess,"Please check Z88I1.TXT first");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONQUESTION);
          goto L30;
          }
        iwarn= 0;
        strcpy(cdatei,"z88i2.txt");
        fdatei= fopen(cdatei,"r");
        if(fdatei == NULL)
          {
          if(LANG == 1) strcpy(cmess,"Kann Z88I2.TXT nicht oeffnen");
          if(LANG == 2) strcpy(cmess,"Cannot open Z88I2.TXT");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONQUESTION);
          goto L30;
          }
        rewind(fdatei);

        if(LANG == 1) strcpy(cmess,"Nun checken von Z88I2.TXT");
        if(LANG == 2) strcpy(cmess,"Now checking Z88I2.TXT");
        MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);

        ier= g1i288(hWnd);
        if (ier != 0) fclose(fdatei);

        if(ier == 0) ier= g2i288(hWnd);
        if (ier != 0) fclose(fdatei);

        if(iwarn == 0 && ier == 0)
          {
          if(LANG == 1) strcpy(cmess,
          "Z88I2.TXT gecheckt: Keine Fehler und Warnungen entdeckt");
          if(LANG == 2) strcpy(cmess,
          "Z88I2.TXT was checked: No Errors and Warnings detected");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
          }

        if(iwarn != 0 && ier == 0)
          { 
          if(LANG == 1) sprintf(cmess,
          "Z88I2.TXT gecheckt: Keine Fehler, aber %ld Warnungen entdeckt",
          iwarn);
          if(LANG == 2) sprintf(cmess,
          "Z88I2.TXT was checked: No Errors, but %ld Warnings detected",iwarn);
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
          }

        if(ier != 0)
          {
          if(LANG == 1) strcpy(cmess,
          "Z88I2.TXT gecheckt: Fehler entdeckt\nZ88I2.TXT ist geschlossen. \
Sie koennen in Z88V bleiben und parallel dazu Z88I2.TXT korrigieren. Dann \
erneut checken");
          if(LANG == 2) strcpy(cmess,
          "Z88I2.TXT was checked: Errors detected\nZ88I2.TXT is closed. \
You can stay in Z88V and edit Z88I2.TXT. Then check again");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONEXCLAMATION);
          }

      L30:; /* hier raus, wenn File nicht geoeffnet werden konnte */
      return 0;

/*==========================================================================
* Z88I3.TXT
*=========================================================================*/
      case IDM_Z88I3TXT:
      case ITC_Z88I3TXT:
        if(iruni1 == 0)
          {
          if(LANG == 1) strcpy(cmess,"Bitte erst Z88I1.TXT checken");
          if(LANG == 2) strcpy(cmess,"Please check Z88I1.TXT first");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONQUESTION);
          goto L40;
          }
        iwarn= 0;
        strcpy(cdatei,"z88i3.txt");
        fdatei= fopen(cdatei,"r");
        if(fdatei == NULL)
          {
          if(LANG == 1) strcpy(cmess,"Kann Z88I3.TXT nicht oeffnen");
          if(LANG == 2) strcpy(cmess,"Cannot open Z88I3.TXT");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONQUESTION);
          goto L40;
          }
        rewind(fdatei);

        if(LANG == 1) strcpy(cmess,"Nun checken von Z88I3.TXT");
        if(LANG == 2) strcpy(cmess,"Now checking Z88I3.TXT");
        MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);

        ier= g1i388(hWnd);
        if (ier != 0) fclose(fdatei);

        if(iwarn == 0 && ier == 0)
          {
          if(LANG == 1) strcpy(cmess,
          "Z88I3.TXT gecheckt: Keine Fehler und Warnungen entdeckt");
          if(LANG == 2) strcpy(cmess,
          "Z88I3.TXT was checked: No Errors and Warnings detected");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
          }

        if(iwarn != 0 && ier == 0)
          { 
          if(LANG == 1) sprintf(cmess,
          "Z88I3.TXT gecheckt: Keine Fehler, aber %ld Warnungen entdeckt",
          iwarn);
          if(LANG == 2) sprintf(cmess,
          "Z88I3.TXT was checked: No Errors, but %ld Warnings detected",iwarn);
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
          }

        if(ier != 0)
          {
          if(LANG == 1) strcpy(cmess,
          "Z88I3.TXT gecheckt: Fehler entdeckt\nZ88I3.TXT ist geschlossen. \
Sie koennen in Z88V bleiben und parallel dazu Z88I3.TXT korrigieren. Dann \
erneut checken");
          if(LANG == 2) strcpy(cmess,
          "Z88I3.TXT was checked: Errors detected\nZ88I3.TXT is closed. \
You can stay in Z88V and edit Z88I3.TXT. Then check again");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONEXCLAMATION);
          }

      L40:; /* hier raus, wenn File nicht geoeffnet werden konnte */
      return 0;

/*==========================================================================
* Z88I4.TXT
*=========================================================================*/
      case IDM_Z88I4TXT:
      case ITC_Z88I4TXT:
        iwarn= 0;
        strcpy(cdatei,ci4);
        fdatei= fopen(cdatei,"r");
        if(fdatei == NULL)
          {
          if(LANG == 1) strcpy(cmess,"Kann Z88I4.TXT nicht oeffnen");
          if(LANG == 2) strcpy(cmess,"Cannot open Z88I4.TXT");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONQUESTION);
          goto L50;
          }
        rewind(fdatei);

        if(LANG == 1) strcpy(cmess,"Nun checken von Z88I4.TXT");
        if(LANG == 2) strcpy(cmess,"Now checking Z88I4.TXT");
        MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);

        ier= g1i488(hWnd);
        if (ier != 0) fclose(fdatei);

        if(iwarn == 0 && ier == 0)
          {
          if(LANG == 1) strcpy(cmess,
          "Z88I4.TXT gecheckt: Keine Fehler und Warnungen entdeckt");
          if(LANG == 2) strcpy(cmess,
          "Z88I4.TXT was checked: No Errors and Warnings detected");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
          }

        if(iwarn != 0 && ier == 0)
          { 
          if(LANG == 1) sprintf(cmess,
          "Z88I4.TXT gecheckt: Keine Fehler, aber %ld Warnungen entdeckt",
          iwarn);
          if(LANG == 2) sprintf(cmess,
          "Z88I4.TXT was checked: No Errors, but %ld Warnings detected",iwarn);
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
          }

        if(ier != 0)
          {
          if(LANG == 1) strcpy(cmess,
          "Z88I4.TXT gecheckt: Fehler entdeckt\nZ88I4.TXT ist geschlossen. \
Sie koennen in Z88V bleiben und parallel dazu Z88I4.TXT korrigieren. Dann \
erneut checken");
          if(LANG == 2) strcpy(cmess,
          "Z88I4.TXT was checked: Errors detected\nZ88I4.TXT is closed. \
You can stay in Z88V and edit Z88I4.TXT. Then check again");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONEXCLAMATION);
          }

      L50:; /* hier raus, wenn File nicht geoeffnet werden konnte */
      return 0;

/*==========================================================================
* Z88I5.TXT
*=========================================================================*/
      case IDM_Z88I5TXT:
      case ITC_Z88I5TXT:
        if(iruni1 == 0)
          {
          if(LANG == 1) strcpy(cmess,"Bitte erst Z88I1.TXT checken");
          if(LANG == 2) strcpy(cmess,"Please check Z88I1.TXT first");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONQUESTION);
          goto L60;
          }

        if(iqflag == 0)
          {
          if(LANG == 1) strcpy(cmess,
            "IQFLAG in Z88I1.TXT nicht gesetzt\n\
Flaechenlastdatei Z88I5.TXT wird nicht angezogen");
          if(LANG == 2) strcpy(cmess,
            "IQFLAG not set in Z88I1.TXT\n\
Surface Load File Z88I5.TXT not used");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONQUESTION);
          goto L60;
          }

        iwarn= 0;
        strcpy(cdatei,"z88i5.txt");
        fdatei= fopen(cdatei,"r");
        if(fdatei == NULL)
          {
          if(LANG == 1) strcpy(cmess,"Kann Z88I5.TXT nicht oeffnen");
          if(LANG == 2) strcpy(cmess,"Cannot open Z88I5.TXT");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONQUESTION);
          goto L60;
          }
        rewind(fdatei);

        if(LANG == 1) strcpy(cmess,"Nun checken von Z88I5.TXT");
        if(LANG == 2) strcpy(cmess,"Now checking Z88I5.TXT");
        MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);

        ier= g1i588(hWnd);
        if (ier != 0) fclose(fdatei);

        if(ier == 0) ier= g2i588(hWnd);
        if (ier != 0) fclose(fdatei);

        if(iwarn == 0 && ier == 0)
          {
          if(LANG == 1) strcpy(cmess,
          "Z88I5.TXT gecheckt: Keine Fehler und Warnungen entdeckt");
          if(LANG == 2) strcpy(cmess,
          "Z88I5.TXT was checked: No Errors and Warnings detected");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
          }

        if(iwarn != 0 && ier == 0)
          { 
          if(LANG == 1) sprintf(cmess,
          "Z88I5.TXT gecheckt: Keine Fehler, aber %ld Warnungen entdeckt",
          iwarn);
          if(LANG == 2) sprintf(cmess,
          "Z88I5.TXT was checked: No Errors, but %ld Warnings detected",iwarn);
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
          }

        if(ier != 0)
          {
          if(LANG == 1) strcpy(cmess,
          "Z88I2.TXT gecheckt: Fehler entdeckt\nZ88I5.TXT ist geschlossen. \
Sie koennen in Z88V bleiben und parallel dazu Z88I5.TXT korrigieren. Dann \
erneut checken");
          if(LANG == 2) strcpy(cmess,
          "Z88I2.TXT was checked: Errors detected\nZ88I5.TXT is closed. \
You can stay in Z88V and edit Z88I5.TXT. Then check again");
          MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONEXCLAMATION);
          }

      L60:; /* hier raus, wenn File nicht geoeffnet werden konnte */
      return 0;

/*======================================================================
* COMMAND : Wer ist es
*=====================================================================*/
      case IDM_WER:
        if(LANG == 1) strcpy(cmess,
"Filechecker Z88V fuer Windows\n\
Version 12.0\n\
Copyright Univ.-Prof.Dr.-Ing. Frank Rieg,\n\
Universitaet Bayreuth, 2005\n\
Alle Rechte vorbehalten");
          if(LANG == 2) strcpy(cmess,
"File Checker Z88V for Windows\n\
Version 12.0\n\
Copyright Prof.Dr. Frank Rieg,\n\
University of Bayreuth, Germany 2005\n\
All rights reserved");
        MessageBox(NULL,cmess,"Z88V", MB_OK | MB_ICONINFORMATION);
      return 0;

/*==========================================================================
* Xit
*=========================================================================*/
      case IDM_XIT:
        if(LANG == 1) strcpy(cmess,"Z88V beenden ?");
        if(LANG == 2) strcpy(cmess,"Quit Z88V ?");
        imess= MessageBox(NULL,cmess,"Z88V",MB_OKCANCEL | MB_ICONQUESTION);
        if(imess == IDOK)     PostQuitMessage(0);
        if(imess == IDCANCEL) return 0;  
      return 0; 

/*==========================================================================
* Default
*=========================================================================*/
      default:
        return DefWindowProc(hWnd, Message, wParam, lParam);
      }


/*------------------------------------------------------------------------
* WM_PAINT
*-----------------------------------------------------------------------*/
  case WM_PAINT:
    memset(&ps, 0x00, sizeof(PAINTSTRUCT));
    hDC = BeginPaint(hWnd, &ps);

    /* Included in case the background is not a pure color */
    SetBkMode(hDC, TRANSPARENT);

    EndPaint(hWnd, &ps);
  return 0;

/*------------------------------------------------------------------------
* WM_CLOSE
*-----------------------------------------------------------------------*/
  case WM_CLOSE:
    PostQuitMessage(0);
  return 0;

/*------------------------------------------------------------------------
* WM_DESTROY
*-----------------------------------------------------------------------*/
  case WM_DESTROY:
    PostQuitMessage(0);
  return 0;

  default:
    return DefWindowProc(hWnd, Message, wParam, lParam);
  }
}

