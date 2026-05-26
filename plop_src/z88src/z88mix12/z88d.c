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
*  Z88D fuer Windows
*  4.10.2005 Rieg
***********************************************************************/
/***********************************************************************
* Windows 95 und NT
***********************************************************************/
#ifdef FR_WIN95
#include <z88d.h>
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
int dyn88d(void);
int wrim88d(FR_INT4,int);
int wlog88d(FR_INT4,int);
int wtyp88d(FR_INT4,FR_INT4);
int ale88d(int);
int riy88d(void);
int slqu88(void);
int sbal88(void);
int sshe88(void);
int ssta88(FR_INT4);
int swel88(void);
int srin88(void);
int sqsh88(void);
int sest88(FR_INT4);
int shex88(void);
int scsh88(void);
int seba88(void);
int siso88(void);
int stet88(void);
int sspu88(void);
int sspl88(void);
int sapl88(void);
int shpl88(void);
int span88(void);  
int lan88d(void);

/****************************************************************************
*  globale Variable
****************************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fwlo,*f1y,*f3y,*fo3,*fi3,*fo5,*fo8,*fcfg;

/* FILE *fo9; /*

/*  
**   fdyn= z88.dyn      close in dyn88d
**   fwlo= z88d.log     close hier
**   f1y=  z88o1.bny    close in riy88d
**   f3y=  z88o3.bny    close in riy88d
**   fo3=  z88o3.txt    close hier
**   fi3=  z88i3.txt    close hier
**   fo5=  z88o5.txt    close hier
**   fo8=  z88o8.txt    close hier
**   fcfg= z88com.cfg
*/ 

char cdyn[8] = "z88.dyn";
char clog[9] = "z88d.log";
char c1y[10] = "z88o1.bny";
char c3y[10] = "z88o3.bny";
char co3[10] = "z88o3.txt";
char ci3[10] = "z88i3.txt";
char co5[10] = "z88o5.txt";
char co8[10] = "z88o8.txt";
char cfg[11] = "z88com.cfg";
  
/*--------------------------------------------------------------------------
* Pointer
*-------------------------------------------------------------------------*/
FR_DOUBLEAY u;
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
FR_DOUBLEAY smw;
FR_DOUBLEAY gmw;

FR_INT4AY koi;
FR_INT4AY ifrei; 
FR_INT4AY ioffs;
FR_INT4AY koffs;
FR_INT4AY ityp;
FR_INT4AY ivon;
FR_INT4AY ibis;
FR_INT4AY intord;
FR_INT4AY jsm;

/*--------------------------------------------------------------------------
* Char-Arrays
*-------------------------------------------------------------------------*/
char cstore[256];
char cbcall[128];
char cbpref[128];
char cbhelp[512];
char cmess[256];

/*--------------------------------------------------------------------------
* Arrays
*-------------------------------------------------------------------------*/
double ul[61];                         /* 61 ist 20 x 3 +1 */

FR_INT4 mspan[21];                     /* 21 ist MAXPA */

/* Diese Arrays werden in SHEX88,SLQU88,SQSH88 und SCSH88 verwendet */

double xk[21], yk[21], zk[21];         /* 21 ist MAXPA , SHEX88 */
double h[21];                          /* 21 ist MAXPA , SHEX88 */
double b[361];                         /* ist 6 x 60 +1, SHEX88 */
double xx[61];                         /* ist 3 x 20 +1, SHEX88 */
double d[37];                          /* ist 6 x 6  +1, SHEX88 */
double p[61];                          /* ist 3 x 20 +1, SHEX88 */

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
double emode,rnuee,qparae,riyye,eyye,rizze,ezze,rite,wte;
FR_INT4 nel,ktyp;
FR_INT4 IDYNMEM,LANG;
FR_INT4 ndim,nkp,ne,nfg,neg,nfgp1,nkoi,ibflag,ipflag,iqflag;
FR_INT4 mxknot,mxfrei;
FR_INT4 ninto,kflag,isflag,kc;
char cline[256];

/*--------------------------------------------------------------------------
* vorbelegte Variable
*-------------------------------------------------------------------------*/
FR_INT4 MAXNFG=0,MAXK=0,MAXE=0,MAXKOI=0,MAXNEG=0;

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
strcpy(capname, "Z88D");

wndclass.cbSize        = sizeof(wndclass);
wndclass.style         = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc   = WndProc;
wndclass.cbClsExtra    = 0;
wndclass.cbWndExtra    = 0;
wndclass.hInstance     = hInstance;
wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88D));
wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
wndclass.hbrBackground = CreateSolidBrush(RGB(255,0,255));
wndclass.lpszMenuName  = capname;
wndclass.lpszClassName = capname;
wndclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88D));

RegisterClassEx(&wndclass);

hWnd = CreateWindow(capname,"Z88 Stress Computing Z88D",
                    WS_OVERLAPPEDWINDOW,
                    200, 220,
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

extern FR_INT4    LANG,kc;

extern char       cstore[];
extern char       cbcall[];
extern char       cbpref[];
extern char       cbhelp[];
extern char       cmess[];

PAINTSTRUCT       ps;

static int        ixClient,iyClient;

int               imess,iret;

FR_INT4           i,k,janz;

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
    waitcur= LoadCursor(hInstance,MAKEINTRESOURCE(CUR_Z88D));

/*======================================================================
* Sprache feststellen
*=====================================================================*/
    iret= lan88d();
    if(iret != 0)
      {
      ale88d(iret);
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
    iret= dyn88d();
    if(iret != 0) 
      { 
      ale88d(iret);
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
          if(LANG == 1) pReply= "Berechne nun die Spannungen";
          if(LANG == 2) pReply= "Calculate the Stresses";
        break;

        case ITC_HELP:
          if(LANG == 1) pReply= "OnLine-Hilfe fuer Spannungs-Berechnung";
          if(LANG == 2) pReply= "OnLine Help for Stress Calculation";
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
"Spannungsprozessor Z88D fuer Windows\n\
Version 12.0\n\
Copyright Univ.-Prof.Dr.-Ing. Frank Rieg,\n\
Universitaet Bayreuth, 2005\n\
Alle Rechte vorbehalten");
          if(LANG == 2) strcpy(cmess,
"Stress Processor Z88D for Windows\n\
Version 12.0\n\
Copyright Prof.Dr. Frank Rieg,\n\
University of Bayreuth, Germany 2005\n\
All rights reserved");
        MessageBox(NULL,cmess,"Z88D", MB_OK | MB_ICONINFORMATION);
      return 0; 

/*======================================================================
* COMMAND : Xit
*=====================================================================*/
      case IDM_XIT:
        if(LANG == 1) strcpy(cmess,"Z88D beenden ?");
        if(LANG == 2) strcpy(cmess,"Quit Z88D ?");
        imess= MessageBox(NULL,cmess,"Z88D",MB_OKCANCEL | MB_ICONQUESTION);
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
          MessageBox(NULL,cmess,"Z88D", MB_OK | MB_ICONHAND);
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
        if(LANG == 1) strcat(cbhelp,"g88d.htm");
        if(LANG == 2) strcat(cbhelp,"e88d.htm");
        imess= WinExec(cbhelp,SW_SHOW);
        if(imess < 33)
          {
          if(LANG == 1) strcpy(cmess,
          "Internet Browser konnte nicht gestartet werden !");
          if(LANG == 2) strcpy(cmess,
          "Could not launch Internet Browser !");
          MessageBox(NULL,cmess,"Z88D", MB_OK | MB_ICONHAND);
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
        SetBkColor(hDC,RGB(255,0,255));
  
/*---------------------------------------------------------------------------
* es werden die Files Z88I3.TXT,Z88O3.TXT,Z88O5.TXT,Z88O8.TXT geoeffnet
*--------------------------------------------------------------------------*/
fi3= fopen(ci3,"r");
if(fi3 == NULL)
  {
  wlog88d(0L,LOG_NOI3);
  fclose(fwlo);
  ale88d(AL_NOI3);
  PostQuitMessage(0);
  return(0);
  }
rewind(fi3);

fo3= fopen(co3,"w+");
if(fo3 == NULL)
  {
  wlog88d(0L,LOG_NOO3);
  fclose(fwlo);
  ale88d(AL_NOO3);
  PostQuitMessage(0);
  return(0);
  }
rewind(fo3);

fo5= fopen(co5,"w+");
if(fo5 == NULL)
  {
  wlog88d(0L,LOG_NOO5);
  fclose(fwlo);
  ale88d(AL_NOO5);
  PostQuitMessage(0);
  return(0);
  }
rewind(fo5);

fo8= fopen(co8,"w+");
if(fo8 == NULL)
  {
  wlog88d(0L,LOG_NOO8);
  fclose(fwlo);
  ale88d(AL_NOO8);
  PostQuitMessage(0);
  return(0);
  }
rewind(fo8);

/*
fo9= fopen("z88o9.txt","w+");
rewind(fo9);
*/

/*---------------------------------------------------------------------------
* Einlesen des Parameterfiles Z88I3.TXT
*--------------------------------------------------------------------------*/
wlog88d(0L,LOG_REAI3);

fgets(cline,256,fi3);
sscanf(cline,"%ld %ld %ld",&ninto,&kflag,&isflag);

fclose(fi3);

/*---------------------------------------------------------------------------
* riy88d liest Z88O1.BNY und Z88O3.BNY ein
*--------------------------------------------------------------------------*/
wlog88d(0L,LOG_RIY88);

iret= riy88d();
if(iret != 0)
  {
  ale88d(iret);
  PostQuitMessage(0);
  return(0);
  }           

/*---------------------------------------------------------------------------
* wenn Berechnung der Spannungen in den Gausspunkten, dann ndim,ninto
*  & isflag in File Z88O5.TXT schreiben
*--------------------------------------------------------------------------*/
fprintf(fo5," %5ld %5ld %5ld",ndim,ninto,isflag);

/***********************************************************************
* Spannungsberechnung: sig= d*b*ul
***********************************************************************/
wrim88d(0L,TX_SPANNU);
wlog88d(0L,LOG_SPANNU);

if(LANG == 1)
  {
  fprintf(fo3,"Ausgabedatei Z88O3.TXT : Spannungen, erzeugt mit Z88D V12\n");
  fprintf(fo3,"                         **********\n");
  }
if(LANG == 2)
  {
  fprintf(fo3,"output file Z88O3.TXT : stresses, computed by Z88D V12\n");
  fprintf(fo3,"                        ********\n");
  }

if(ninto == 0) 
  {
  if(LANG == 1) fprintf(fo3,"\nBei isoparametrischen Elementen Berechnung\
 der Spannungen in den Eckknoten");
  if(LANG == 2) fprintf(fo3,"\nisoparametric elements: computing\
 stresses in corner nodes");
  }
else
  {
  if(LANG == 1) fprintf(fo3,"\nbei isoparametrischen Elementen Berechnung\
 der Spannungen in den Gausspunkten\n%ld Punkte pro Achse/Element",ninto);
  if(LANG == 2) fprintf(fo3,"\nisoparametric elements: computing\
 stresses in Gauss points %ld points per axis/element",ninto);          
  }
         
if (ninto > 0 && isflag == 1)
  {
  if(LANG == 1) fprintf(fo3,"\nBerechnung der Vergleichsspannungen nach\
 Gestaltsaenderungsenergie-Hypothese fuer Elemente 3 + 6\
  \nsowie fuer Gausspunkte der Elemente 1,7,8,10,11,12,14 bis 20");
  if(LANG == 2) fprintf(fo3,"\ncomputing von Mises' stresses\
 for elements 3 + 6 and for Gauss points of\n\
 elements 1,7,8,10,11,12,14 to 20");
  }

for(k= 1;k <= ne;k++)
  {
  kc= k;  /* Weitergabe an die Elementroutinen */

/*----------------------------------------------------------------------
*  es ist ityp(k):    1  isoparametrischer hexaeder, linearer ansatz
*                     2  balken
*                     3  scheibe, dreieckig, quadratischer ansatz
*                     4  raeumlicher stab
*                     5  welle
*                     6  torus, dreieckig, linearer ansatz
*                     7  isoparametrische scheibe, quadratischer ansatz
*                     8  isoparametrischer torus , quadratischer ansatz
*                     9  ebenes stabelement 
*                    10  isop. serendipity hexaeder, quadratischer ans.
*                    11  isoparametrische scheibe, kubischer ansatz
*                    12  isoparametrischer torus,  kubischer ansatz 
*                    13  ebenes balkenelement
*                    14  krummlinige dreiecksscheibe, quadr. ansatz
*                    15  krummliniger dreieckstorus, quadr. ansatz
*                    16  krummliniger tetraeder, quadr. ansatz
*                    17  tetraeder, linearer ansatz
*                    18  6-knoten serendipity reissner mindlin platte
*                    19  16-knoten lagrange reissner mindlin platte
*                    20  8-knoten serendipity reissner mindlin platte
*---------------------------------------------------------------------*/
/*----------------------------------------------------------------------
* zunaechst E-modul und Nue feststellen
*---------------------------------------------------------------------*/
for(i = 1;i <= neg;i++)
  {
  if(k >= ivon[i] && k <= ibis[i])
    {
    emode= emod[i];
    rnuee= rnue[i];
    qparae= qpara[i];
    if(ibflag == 1)
      {
      riyye= riyy[i];
      eyye = eyy[i];
      rizze= rizz[i];
      ezze = ezz[i];
      rite = rit[i];
      wte  = wt[i];
      } 
    goto L60;
    }
  }

L60:;

/*----------------------------------------------------------------------
* Start 8-Knoten Quader, isoparametrischer linearer Ansatz
*---------------------------------------------------------------------*/
  if(ityp[k]== 1)
    {
    wtyp88d(k,1);

/*----------------------------------------------------------------------
* isopara 8-Knoten Hexaeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer iso-8-Knoten Hexaeder berechen
*---------------------------------------------------------------------*/
    if(LANG==1)fprintf(fo3,"\n\nElement # = %ld     Typ = 8-K Hexaeder", k);
    if(LANG==2)fprintf(fo3,"\n\nelement # = %ld     type = 8-n hexahedron", k);

    if(isflag == 0 || ninto == 0)
      {
      fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX");
      }
    else
      {
      fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX       SIGV");
      }
  
    for(i = 1;i <= 8;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 3;            
    
    span88();

    iret= slqu88();
    if(iret != 0)
      {
      wlog88d(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88d(iret);
      PostQuitMessage(0);
      return(0);
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-8-Knoten Hexaeder
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Balkenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 2)
    {
    wtyp88d(k,2);

/*----------------------------------------------------------------------
* Balkenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    zk[1] = z [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    zk[2] = z [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Spannungsberechnung fuer Balkenelement im Raum
*---------------------------------------------------------------------*/
if(LANG == 1) fprintf(fo3,"\n\nElement #= %5ld Typ =RBalken\
  Knoten %5ld            Knoten %5ld",k,koi[koffs[k]],koi[koffs[k]+1]);
if(LANG == 2) fprintf(fo3,"\n\nelement #= %5ld type =spbeam\
   node  %5ld             node  %5ld",k,koi[koffs[k]],koi[koffs[k]+1]);

fprintf(fo3,"\n    SIGXX       TAUXX       SIGZZ1\
      SIGYY1      SIGZZ2      SIGYY2");

    mspan[1]= ioffs[koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 6;

    span88();
    sbal88();
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende Balkenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Dreieck-Scheibenelement, quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 3)
    {
    wtyp88d(k,3);

/*----------------------------------------------------------------------
* Scheibenelement: zutreffende Koordinaten bestimmen 
* die Mittenknoten werden nicht gebraucht
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    xk[3] = x [koi[koffs[k]+2]];
    yk[3] = y [koi[koffs[k]+2]];

/*----------------------------------------------------------------------
* nun Spannungsberechnung fuer Scheibenelement
*---------------------------------------------------------------------*/
    if(LANG == 1)
      fprintf(fo3,"\n\nElement # = %ld     Typ = 6-K Scheibe", k);
    if(LANG == 2)
      fprintf(fo3,"\n\nelement # = %ld     type= 6-n plane stress", k);

    if(isflag == 0)                                        /* keine VglSp */
      {
      if(kflag == 1)                                       /* zus. sigr */
        {
  fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT");
        }
      else                                                 /* kein sigr */
        {
        fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY");
        }
      }                                                    /* e if no VglSp */
    else                                                   /* ja, VglSp */
      {
      if(kflag == 1)                                       /* zus. sigr */
        {
  fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT       SIGV");
        }
      else                                                 /* kein sigr */
        {
        fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY       SIGV");
        }
      }                                                    /* e if ja VglSp */

    for(i = 1;i <= 6;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 6;
    mxfrei= 2;
            
    span88();
    sshe88();
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende 6-k Scheibenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start raeumliches Stabelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 4)
    {
    wtyp88d(k,4);

/*----------------------------------------------------------------------
* raeumliches Stabelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    zk[1] = z [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    zk[2] = z [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Spannungsberechnung fuer raeumliches Stabelement
*---------------------------------------------------------------------*/
    mspan[1]= ioffs[ koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[ koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 3;

    span88();
    ssta88(k);
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende raeumliches Stabelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Wellenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 5)
    {
    wtyp88d(k,5);

/*----------------------------------------------------------------------
* Wellenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Spannungsberechnung fuer Wellenelement
*---------------------------------------------------------------------*/
if(LANG == 1) fprintf(fo3,"\n\nElement #= %5ld Typ = Welle\
   Knoten %5ld            Knoten %5ld",k,koi[koffs[k]],koi[koffs[k]+1]);
if(LANG == 2) fprintf(fo3,"\n\nelement #= %5ld type = shaft\
    node  %5ld             node  %5ld",k,koi[koffs[k]],koi[koffs[k]+1]);

fprintf(fo3,"\n    SIGXX       TAUXX       SIGXY1\
      SIGXZ1      SIGXY2      SIGXZ2");

    mspan[1]= ioffs[ koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[ koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 6;

    span88();
    swel88();
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende Wellenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Toruselement, linearer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 6)
    {
    wtyp88d(k,6);

/*----------------------------------------------------------------------
* Toruselement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    xk[3] = x [koi[koffs[k]+2]];
    yk[3] = y [koi[koffs[k]+2]];
          
/*----------------------------------------------------------------------
* nun Spannungsberechnung fuer Toruselement
*---------------------------------------------------------------------*/
    if(LANG==1) fprintf(fo3,"\n\nElement # = %ld     Typ = 3-K Torus", k);
    if(LANG==2) fprintf(fo3,"\n\nelement # = %ld     type =3-n torus", k);

    if(isflag == 0)                                        /* keine VglSp */
      {
      fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE");
      }                                                    /* e if no VglSp */
    else                                                   /* ja, VglSp */
      {
      fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE       SIGV");
      }                                                    /* e if ja VglSp */

    mspan[1]= ioffs[koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[koi[koffs[k]+1]] -1;
    mspan[3]= ioffs[koi[koffs[k]+2]] -1;
         
    mxknot= 3;
    mxfrei= 2;

    span88();
    srin88();
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende Toruselement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 8-knoten Scheibe/Torus, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 7 || ityp[k]== 8)
    {
    if (ityp[k]== 7)
      {
      wtyp88d(k,7);
      ktyp= 2;
      }
    else
      {
      wtyp88d(k,8L);
      ktyp= 0;
      }

/*----------------------------------------------------------------------
* isopara 8-Knoten Scheibe/Torus: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* Spannungen fuer iso-8-Knoten Scheibe/Torus berechen
*---------------------------------------------------------------------*/
/*======================================================================
* ktyp=2: isopara Scheibenelement mit 8 Knoten
*=====================================================================*/  
    if(ktyp == 2)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = %ld     Typ = 8-K Scheibe", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = %ld     type= 8-n plane stress", k);

      if(isflag == 0 || ninto == 0)                         /* keine VglSp */
        {
        if(kflag == 1)                                     /* zus. sigr */
          {
  fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT");
          }
        else                                               /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY");
          }
        }                                                  /* e if no VglSp */
      else                                                 /* ja, VglSp */
        {
        if(kflag == 1)                                     /* zus. sigr */
          {
  fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT       SIGV");
          }
        else                                               /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY       SIGV");
          }
        }                                                  /* e if ja VglSp */
      }                                                    /* e if scheibe */
      
/*======================================================================
* ktyp=0: isopara Toruselement mit 8 Knoten
*=====================================================================*/  
    if(ktyp == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = %ld     Typ = 8-K Torus", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = %ld     type =8-n torus", k);

      if(isflag == 0 || ninto == 0)                         /* keine VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE");
        }                                                  /* e if no VglSp */
      else                                                 /* ja, VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE       SIGV");
        }                                                  /* e if ja VglSp */
      }                                                    /* e if torus */
      
/*======================================================================
* Rechnen
*=====================================================================*/  
    for(i = 1;i <= 8;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 2;            
    
    span88();

    iret= sqsh88();
    if(iret != 0)
      {
      wlog88d(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88d(iret);
      PostQuitMessage(0);
      return(0);
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-8-Knoten Scheibe/Torus
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start ebenes Stabelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 9)
    {
    wtyp88d(k,9);

/*----------------------------------------------------------------------
* ebenes Stabelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Spannungsberechnung fuer ebenes Stabelement
*---------------------------------------------------------------------*/
    mspan[1]= ioffs[ koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[ koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 2;

    span88();
    sest88(k);
    
    goto L7000;
    
/*----------------------------------------------------------------------
* Ende ebenes Stabelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 20-Knoten Hexaeder, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 10)
    {
    wtyp88d(k,10);
 
/*----------------------------------------------------------------------
* isopara 20-Knoten Hexaeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 20;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer iso-20-Knoten Hexaeder berechen
*---------------------------------------------------------------------*/
    if(LANG == 1)
      fprintf(fo3,"\n\nElement # = %ld     Typ = 20-K Hexaeder", k);
    if(LANG == 2)
      fprintf(fo3,"\n\nelement # = %ld     type =20-n hexahedron", k);

    if(isflag == 0 || ninto == 0)
      {
      fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX");
      }
    else
      {
      fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX       SIGV");
      }
  
    for(i = 1;i <= 20;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 20;
    mxfrei= 3;            
    
    span88();

    iret= shex88();
    if(iret != 0)
      {
      wlog88d(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88d(iret);
      PostQuitMessage(0);
      return(0);
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-20-Knoten Hexaeder
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 12-Knoten Scheibe/Torus, isoparametrischer kubischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 11 || ityp[k]== 12)
    {
    if (ityp[k]== 11)
      {
      wtyp88d(k,11);
      ktyp= 2;
      }
    else
      {
      wtyp88d(k,12);
      ktyp= 0;
      }

/*----------------------------------------------------------------------
* isopara 12-Knoten Scheibe/Torus: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 12;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* Spannungen fuer iso-12-Knoten Scheibe/Torus berechen
*---------------------------------------------------------------------*/
/*======================================================================
* ktyp=2: isopara Scheibenelement mit 12 Knoten
*=====================================================================*/  
    if(ktyp == 2)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = %ld     Typ = 12-K Scheibe", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = %ld     type= 12-n plane stress", k);

      if(isflag == 0 || ninto == 0)                         /* keine VglSp */
        {
        if(kflag == 1)                                     /* zus. sigr */
          {
  fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT");
          }
        else                                               /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY");
          }
        }                                                  /* e if no VglSp */
      else                                                 /* ja, VglSp */
        {
        if(kflag == 1)                                     /* zus. sigr */
          {
  fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT       SIGV");
          }
        else                                               /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY       SIGV");
          }
        }                                                  /* e if ja VglSp */
      }                                                    /* e if scheibe */
      
/*======================================================================
* ktyp=0: isopara Toruselement mit 12 Knoten
*=====================================================================*/  
    if(ktyp == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = %ld     Typ = 12-K Torus", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = %ld     type =12-n torus", k);

      if(isflag == 0 || ninto == 0)                         /* keine VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE");
        }                                                  /* e if no VglSp */
      else                                                 /* ja, VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE       SIGV");
        }                                                  /* e if ja VglSp */
      }                                                    /* e if torus */
      
/*======================================================================
* Rechnen
*=====================================================================*/  
    for(i = 1;i <= 12;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 12;
    mxfrei= 2;            
    
    span88();

    iret= scsh88();
    if(iret != 0)
      {
      wlog88d(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88d(iret);
      PostQuitMessage(0);
      return(0);
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-12-Knoten Scheibe/Torus
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start ebenes Balkenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 13)
    {
    wtyp88d(k,13);

/*----------------------------------------------------------------------
* Balkenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Spannungsberechnung fuer ebenes Balkenelement
*---------------------------------------------------------------------*/
     if(LANG == 1) fprintf(fo3,"\n\nElement #= %5ld Typ= Balken in Ebene\
     Knoten %5ld      Knoten %5ld",k,koi[koffs[k]],koi[koffs[k]+1]);

     if(LANG == 2) fprintf(fo3,"\n\nelement #= %5ld type = beam in plane\
      node  %5ld       node  %5ld",k,koi[koffs[k]],koi[koffs[k]+1]);

     fprintf(fo3,"\n    SIGXX                                    SIGZZ1\
            SIGZZ2");

    mspan[1]= ioffs[koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 3;

    span88();
    seba88();
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende ebenes Balkenelement
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 6-knoten Dreieck Scheibe/Torus, isop quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 14 || ityp[k]== 15)
    {
    if (ityp[k]== 14)
      {
      wtyp88d(k,14);
      ktyp= 2;
      }
    else
      {
      wtyp88d(k,15L);
      ktyp= 0;
      }

/*----------------------------------------------------------------------
* isop 6-Knoten Dreieck Scheibe/Torus: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* Spannungen fuer iso-6-Knoten Dreieck Scheibe/Torus berechen
*---------------------------------------------------------------------*/
/*======================================================================
* ktyp=2: isopara Scheibenelement mit 6 Knoten
*=====================================================================*/  
    if(ktyp == 2)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = %ld     Typ = 6-K isop. Scheibe", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = %ld     type= 6-n iso. plane stress", k);

      if(isflag == 0 || ninto == 0)                         /* keine VglSp */
        {
        if(kflag == 1)                                     /* zus. sigr */
          {
  fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT");
          }
        else                                               /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY");
          }
        }                                                  /* e if no VglSp */
      else                                                 /* ja, VglSp */
        {
        if(kflag == 1)                                     /* zus. sigr */
          {
  fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT       SIGV");
          }
        else                                               /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY       SIGV");
          }
        }                                                  /* e if ja VglSp */
      }                                                    /* e if scheibe */
      
/*======================================================================
* ktyp=0: isopara Toruselement mit 6 Knoten
*=====================================================================*/  
    if(ktyp == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = %ld     Typ = 6-K isop. Torus", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = %ld     type =6-n isop. torus", k);

      if(isflag == 0 || ninto == 0)                         /* keine VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE");
        }                                                  /* e if no VglSp */
      else                                                 /* ja, VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE       SIGV");
        }                                                  /* e if ja VglSp */
      }                                                    /* e if torus */
      
/*======================================================================
* Rechnen
*=====================================================================*/  
    for(i = 1;i <= 6;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 6;
    mxfrei= 2;            
    
    span88();

    iret= siso88();
    if(iret != 0)
      {
      wlog88d(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88d(iret);
      PostQuitMessage(0);
      return(0);
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-6-Knoten Dreieck Scheibe/Torus
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 10-Knoten Tetraeder, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 16)
    {
    wtyp88d(k,16);
 
/*----------------------------------------------------------------------
* isopara 10-Knoten Tetraeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 10;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer iso-10-Knoten Tetraeder berechen
*---------------------------------------------------------------------*/
    if(LANG == 1)
      fprintf(fo3,"\n\nElement # = %ld     Typ = 10-K Tetraeder", k);
    if(LANG == 2)
      fprintf(fo3,"\n\nelement # = %ld     type =10-n tetrahedron", k);

    if(isflag == 0 || ninto == 0)
      {
      fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX");
      }
    else
      {
      fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX       SIGV");
      }
  
    for(i = 1;i <= 10;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 10;
    mxfrei= 3;            
    
    span88();

    iret= stet88();
    if(iret != 0)
      {
      wlog88d(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88d(iret);
      PostQuitMessage(0);
      return(0);
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-10-Knoten Tetraeder
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 4-Knoten Tetraeder, linearer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 17)
    {
    wtyp88d(k,17);
 
/*----------------------------------------------------------------------
* 4-Knoten Tetraeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 4;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer 4-Knoten Tetraeder berechen
*---------------------------------------------------------------------*/
    if(LANG == 1)
      fprintf(fo3,"\n\nElement # = %ld     Typ = 4-K Tetraeder", k);
    if(LANG == 2)
      fprintf(fo3,"\n\nelement # = %ld     type =4-n tetrahedron", k);

    if(isflag == 0 || ninto == 0)
      {
      fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX");
      }
    else
      {
      fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX       SIGV");
      }
  
    for(i = 1;i <= 4;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 4;
    mxfrei= 3;            
    
    span88();

    iret= sspu88();
    if(iret != 0)
      {
      wlog88d(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88d(iret);
      PostQuitMessage(0);
      return(0);
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-4-Knoten Tetraeder
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 6-Knoten Reissner- Mindlin Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 18)
    {
    wtyp88d(k,18);
 
/*----------------------------------------------------------------------
* isopara 6-Knoten Platte: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer iso-6-Knoten Platte berechen
*---------------------------------------------------------------------*/
    if(LANG == 1)
      fprintf(fo3,"\n\nElement # = %ld     Typ = 6-K Platte", k);
    if(LANG == 2)
      fprintf(fo3,"\n\nelement # = %ld     type =6-n plate", k);

    if(isflag == 0 || ninto == 0)
      {
      fprintf(fo3,"\n XX         YY         MXX         MYY\
         MXY         QYZ         QZX         SIGXX       SIGYY\
       TAUXY       TAUXZ(Z=0)  TAUYZ(Z=0)");
      }
    else
      {
      fprintf(fo3,"\n XX         YY         MXX         MYY\
         MXY         QYZ         QZX         SIGXX       SIGYY\
       TAUXY       TAUXZ(Z=0)  TAUYZ(Z=0)   SIGV");
      }
  
    for(i = 1;i <= 6;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 6;
    mxfrei= 3;            
    
    span88();

    iret= sspl88();
    if(iret != 0)
      {
      wlog88d(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88d(iret);
      PostQuitMessage(0);
      return(0);
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 6-Knoten Reissner- Mindlin Platte
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 16-Knoten Reissner- Mindlin Lagrange Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 19)
    {
    wtyp88d(k,19);
 
/*----------------------------------------------------------------------
* isopara 16-Knoten Platte: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 16;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer iso-16-Knoten Platte berechen
*---------------------------------------------------------------------*/
    if(LANG == 1)
      fprintf(fo3,"\n\nElement # = %ld     Typ = 16-K Platte", k);
    if(LANG == 2)
      fprintf(fo3,"\n\nelement # = %ld     type =16-n plate", k);

    if(isflag == 0 || ninto == 0)
      {
      fprintf(fo3,"\n XX         YY         MXX         MYY\
         MXY         QYZ         QZX         SIGXX       SIGYY\
       TAUXY       TAUXZ(Z=0)  TAUYZ(Z=0)");
      }
    else
      {
      fprintf(fo3,"\n XX         YY         MXX         MYY\
         MXY         QYZ         QZX         SIGXX       SIGYY\
       TAUXY       TAUXZ(Z=0)  TAUYZ(Z=0)   SIGV");
      }
  
    for(i = 1;i <= 16;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 16;
    mxfrei= 3;            
    
    span88();

    iret= shpl88();
    if(iret != 0)
      {
      wlog88d(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88d(iret);
      PostQuitMessage(0);
      return(0);
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 16-Knoten Reissner- Mindlin Lagrange Platte
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 8-Knoten Reissner- Mindlin Serendipity Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 20)
    {
    wtyp88d(k,20);
 
/*----------------------------------------------------------------------
* isopara 8-Knoten Platte: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer iso-8-Knoten Platte berechen
*---------------------------------------------------------------------*/
    if(LANG == 1)
      fprintf(fo3,"\n\nElement # = %ld     Typ = 8-K Platte", k);
    if(LANG == 2)
      fprintf(fo3,"\n\nelement # = %ld     type =8-n plate", k);

    if(isflag == 0 || ninto == 0)
      {
      fprintf(fo3,"\n XX         YY         MXX         MYY\
         MXY         QYZ         QZX         SIGXX       SIGYY\
       TAUXY       TAUXZ(Z=0)  TAUYZ(Z=0)");
      }
    else
      {
      fprintf(fo3,"\n XX         YY         MXX         MYY\
         MXY         QYZ         QZX         SIGXX       SIGYY\
       TAUXY       TAUXZ(Z=0)  TAUYZ(Z=0)   SIGV");
      }
  
    for(i = 1;i <= 8;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 3;            
    
    span88();

    iret= sapl88();
    if(iret != 0)
      {
      wlog88d(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88d(iret);
      PostQuitMessage(0);
      return(0);
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 8-Knoten Reissner- Mindlin Serendipity Platte
*---------------------------------------------------------------------*/
    }

    
L7000:;
  
/***********************************************************************
* Ende der Schleife ueber alle Elemente
***********************************************************************/
  }  /* e 8000 */

/*----------------------------------------------------------------------
* Ende Z88D
*---------------------------------------------------------------------*/
/*======================================================================
* ggf. Ausschreiben von Z88O8.TXT fuer alle Nicht-Balken
*=====================================================================*/
if(isflag == 1 && !(ityp[1] == 2 || ityp[1] == 5 || ityp[1] == 13))
  {

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Wieviel "Eckknoten" ?
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  janz= 0;
  for(k= 1; k <= nkp; k++)
    if(jsm[k] > 0) janz++;

  fprintf(fo8," %ld",janz);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Eckknoten mit Vergleichsspannungen ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(k= 1; k <= nkp; k++)
    {
    if(jsm[k] > 0)
      {
      smw[k]/= jsm[k];
      fprintf(fo8,"\n%7ld  %7ld  %+#11.3lE",k,jsm[k],smw[k]);
      }
    }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Wieviel Elemente ?
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  fprintf(fo8,"\n %ld",ne);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* mittlere Vergleichsspannungen pro Element ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(k= 1; k <= ne; k++)
    fprintf(fo8,"\n%7ld  %+#11.3lE",k,gmw[k]);

  }

/*======================================================================
* Dateien schliessen
*=====================================================================*/
wrim88d(0L,TX_EXITZ88D);
wlog88d(0L,LOG_EXITZ88D);

fprintf(fo3,"\n");
fprintf(fo5,"\n");
fprintf(fo8,"\n");

fclose(fo3);
fclose(fo5);
fclose(fo8);

fclose(fwlo);
     
/*---------------------------------------------------------------------
* Ende Case Go
*---------------------------------------------------------------------*/
        if(LANG == 1) strcpy(cmess,"Spannungsprozessor Z88D gelaufen");
        if(LANG == 2) strcpy(cmess,"Computing Stresses Z88D done");
        MessageBox(NULL,cmess,"Z88D", MB_OK | MB_ICONINFORMATION);
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

