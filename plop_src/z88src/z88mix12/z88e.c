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
*  Z88E fuer Windows
*  21.7.2005 Rieg
***********************************************************************/
/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88e.h>
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
int dyn88e(void);
int wrim88e(FR_INT4,int);
int wlog88e(FR_INT4,int);
int wtyp88e(FR_INT4,FR_INT4);
int ale88e(int);
int riy88(void);
int ri4t288(void);
int ri4t1388(void);
int lqua88(void);
int balk88(void);
int shei88(void);
int stab88(void);
int well88(void);
int ring88(void);
int qshe88(void);
int esta88(void);
int hexa88(void);
int cshe88(void);
int ebal88(void);
int isod88(void);
int tetr88(void);
int spur88(void);
int spla88(void);
int hpla88(void);
int apla88(void);
int forc88(void);  
int lan88e(void);

/****************************************************************************
*  globale Variable
****************************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fwlo,*f1y,*f3y,*fo4,*fcfg;

/*  
**   fdyn= z88.dyn
**   fwlo= z88e.log
**   f1y=  z88o1.bny
**   f3y=  z88o3.bny
**   fo4=  z88o4.txt
**   fcfg= z88com.cfg
*/ 

char cdyn[8] = "z88.dyn";
char clog[9] = "z88e.log";
char c1y[10] = "z88o1.bny";
char c3y[10] = "z88o3.bny";
char co4[10] = "z88o4.txt";
char cfg[11] = "z88com.cfg";
  
/*--------------------------------------------------------------------------
* Pointer
*-------------------------------------------------------------------------*/
FR_DOUBLEAY se;
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
FR_DOUBLEAY fsum1;
FR_DOUBLEAY fsum2;
FR_DOUBLEAY fsum3;
FR_DOUBLEAY fsum4;
FR_DOUBLEAY fsum5;
FR_DOUBLEAY fsum6;

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
char cmess[256];

/*--------------------------------------------------------------------------
* Arrays
*-------------------------------------------------------------------------*/
double f[61];                          /* 61 ist MAXFE */
double ul[61];                         /* 61 ist MAXFE */

FR_INT4 mcomp[21];                     /* 21 ist MAXPA */

/* Diese Arrays werden in HEXA88,LQUA88,QSHE88 und CSHE88 verwendet */

double xk[21], yk[21], zk[21];         /* 21 ist MAXPA , HEXA88 */
double h[21];                          /* 21 ist MAXPA , HEXA88 */
double b[361];                         /* ist 6 x 60 +1, HEXA88 */
double xx[61];                         /* ist 3 x 20 +1, HEXA88 */
double d[37];                          /* ist 6 x 6  +1, HEXA88 */
double p[61];                          /* ist 3 x 20 +1, HEXA88 */

/* fuer Plattenberechnung */
FR_DOUBLE be[49];                         /* fuer 16-Knoten Platte  */
FR_DOUBLE hi[49];
FR_DOUBLE bbi[145];
FR_DOUBLE bsv[97];
FR_DOUBLE dbi[10];
FR_DOUBLE dsv[5];

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
double emode,rnuee,qparae,riyye,eyye,rizze,ezze,rite,wte;
FR_INT4 intore,nel,ktyp;
FR_INT4 IDYNMEM,LANG;
FR_INT4 ndim,nkp,ne,nfg,neg,nfgp1,nkoi,ibflag,ipflag,iqflag;
FR_INT4 mxknot,mxfrei,mxfe;

/*--------------------------------------------------------------------------
* vorbelegte Variable
*-------------------------------------------------------------------------*/
FR_INT4 MAXNFG=0,MAXK=0,MAXE=0,MAXKOI=0,MAXNEG=0;
FR_INT4 MAXESM=3600;

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
strcpy(capname, "Z88E");

wndclass.cbSize        = sizeof(wndclass);
wndclass.style         = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc   = WndProc;
wndclass.cbClsExtra    = 0;
wndclass.cbWndExtra    = 0;
wndclass.hInstance     = hInstance;
wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88E));
wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
wndclass.hbrBackground = CreateSolidBrush(RGB(0,255,255));
wndclass.lpszMenuName  = capname;
wndclass.lpszClassName = capname;
wndclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88E));

RegisterClassEx(&wndclass);

hWnd = CreateWindow(capname,"Z88 Nodal Forces Computing Z88E",
                    WS_OVERLAPPEDWINDOW,
                    250, 220,
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

extern FR_INT4    LANG;

extern char       cstore[];
extern char       cbcall[];
extern char       cbpref[];
extern char       cbhelp[];
extern char       cmess[];

PAINTSTRUCT       ps;

static int        ixClient,iyClient;

int               imess,iret;

FR_INT4           i,j,k;

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
    waitcur= LoadCursor(hInstance,MAKEINTRESOURCE(CUR_Z88E));

/*======================================================================
* Sprache feststellen
*=====================================================================*/
    iret= lan88e();
    if(iret != 0)
      {
      ale88e(iret);
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
    iret= dyn88e();
    if(iret != 0) 
      { 
      ale88e(iret);
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
          if(LANG == 1) pReply= "Berechne nun die Knotenkraefte";
          if(LANG == 2) pReply= "Calculate the Nodal Forces";
        break;

        case ITC_HELP:
          if(LANG == 1) pReply= "OnLine-Hilfe fuer Knotenkraft-Berechnung";
          if(LANG == 2) pReply= "OnLine Help for Nodal Force Calculation";
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
"Knotenkraft Prozessor Z88E fuer Windows\n\
Version 12.0\n\
Copyright Univ.-Prof.Dr.-Ing. Frank Rieg,\n\
Universitaet Bayreuth, 2005\n\
Alle Rechte vorbehalten");
          if(LANG == 2) strcpy(cmess,
"Nodal Force Processor Z88E for Windows\n\
Version 12.0\n\
Copyright Prof.Dr. Frank Rieg,\n\
University of Bayreuth, Germany 2005\n\
All rights reserved");
        MessageBox(NULL,cmess,"Z88E", MB_OK | MB_ICONINFORMATION);
      return 0; 

/*======================================================================
* COMMAND : Xit
*=====================================================================*/
      case IDM_XIT:
        if(LANG == 1) strcpy(cmess,"Z88E beenden ?");
        if(LANG == 2) strcpy(cmess,"Quit Z88E ?");
        imess= MessageBox(NULL,cmess,"Z88E",MB_OKCANCEL | MB_ICONQUESTION);
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
          MessageBox(NULL,cmess,"Z88E", MB_OK | MB_ICONHAND);
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
        if(LANG == 1) strcat(cbhelp,"g88e.htm");
        if(LANG == 2) strcat(cbhelp,"e88e.htm");
        imess= WinExec(cbhelp,SW_SHOW);
        if(imess < 33)
          {
          if(LANG == 1) strcpy(cmess,
          "Internet Browser konnte nicht gestartet werden !");
          if(LANG == 2) strcpy(cmess,
          "Could not launch Internet Browser !");
          MessageBox(NULL,cmess,"Z88E", MB_OK | MB_ICONHAND);
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
        SetBkColor(hDC,RGB(0,255,255));
  
/*---------------------------------------------------------------------------
* es werden die Files Z88O4.TXT und Z88I4.TXT geoeffnet
*--------------------------------------------------------------------------*/
fo4= fopen(co4,"w+");
if(fo4 == NULL)
  {
  wlog88e(0L,LOG_NOO4);
  fclose(fwlo);
  ale88e(AL_NOO4);
  PostQuitMessage(0);
  return(0);
  }
rewind(fo4);

/*---------------------------------------------------------------------------
* riy88 liest Z88O1.BNY und Z88O3.BNY ein
*--------------------------------------------------------------------------*/
wlog88e(0L,LOG_RIY88);

iret= riy88();
if(iret != 0)
  {
  ale88e(iret);
  PostQuitMessage(0);
  return(0);
  }           

/***********************************************************************
* Berechnen der Elementsteifigkeitsmatrizen, Compilation  
***********************************************************************/
wrim88e(0L,TX_KNOTENK);
wlog88e(0L,LOG_KNOTENK);

for(i= 1;i <= nkp;i++)  /* schadet nicht */
  {
  fsum1[i]= 0.;
  fsum2[i]= 0.;
  fsum3[i]= 0.;
  fsum4[i]= 0.;
  fsum5[i]= 0.;
  fsum6[i]= 0.;
  }

if(LANG == 1)
  {
  fprintf(fo4,"Ausgabedatei Z88O4.TXT : Knotenkraefte, erzeugt mit Z88E V12\n");
  fprintf(fo4,"                         *************\n\n");
  fprintf(fo4,"Zunaechst die Knotenkraefte elementweise\n");
  fprintf(fo4,"----------------------------------------\n");
  }
if(LANG == 2)
  {
  fprintf(fo4,"output file Z88O4.TXT : nodal forces, computed by Z88E V12\n");
  fprintf(fo4,"                        ************\n\n");
  fprintf(fo4,"starting with nodal forces computed for each element\n");
  fprintf(fo4,"----------------------------------------------------\n");
  }

for(k= 1;k <= ne;k++)
  {

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
    intore=intord[i];
    qparae= qpara[i];

    if(ibflag == 1L)
      {
      riyye= riyy[i];
      eyye = eyy[i];
      rizze= rizz[i];
      ezze = ezz[i];
      rite = rit[i];
      wte  = wt[i];
      } 

    if(ipflag != 0)
      {
      riyye= riyy[i];
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
    wtyp88e(k,1);

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
* nun Elementsteifigkeitsmatrix fuer iso-8-Knoten Hexaeder berechen
*---------------------------------------------------------------------*/
    iret= lqua88();
    if(iret != 0)
      {
      wlog88e(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88e(iret);
      PostQuitMessage(0);
      return(0);
      }

/*----------------------------------------------------------------------
* Compilation fuer lqua88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 3;            
    mxfe  = 24;
    
    forc88();
    
    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = 8-K Hexaeder",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = 8-n hexahedron",k);
      fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
      }

    j= 1;
            
    for(i = 1;i <= 8;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
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
    wtyp88e(k,2);

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
* Elementsteifigkeitsmatrix fuer Balkenelement berechen
*---------------------------------------------------------------------*/
    balk88();

/*----------------------------------------------------------------------
* Compilation fuer balk88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 6;
    mxfe  = 12;

    forc88();
    
    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = Balken im Raum",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)\
           F(4)           F(5)           F(6)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = beam in space",k);
      fprintf(fo4,"\nnode         F(1)           F(2)           F(3)\
           F(4)           F(5)           F(6)");
      }

    j= 1;
            
    for(i = 1;i <= 2;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE  %+#13.5lE\
  %+#13.5lE  %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1],f[j+2],f[j+3],f[j+4],f[j+5]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      fsum4[koi[koffs[k]+i-1]] += f[j+3];
      fsum5[koi[koffs[k]+i-1]] += f[j+4];
      fsum6[koi[koffs[k]+i-1]] += f[j+5];
      j+= 6;   
      }

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
    wtyp88e(k,3);

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
* nun Elementsteifigkeitsmatrix fuer Scheibenelement berechen
*---------------------------------------------------------------------*/
    iret= shei88();
    if(iret != 0)
      {
      wlog88e(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88e(iret);
      PostQuitMessage(0);
      return(0);
      }

/*-----------------------------------------------------------------------
* Compilation fuer shei88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 6;
    mxfrei= 2;
    mxfe  = 12;
            
    forc88();
    
    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = 6-K Scheibe",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = 6-n plane stress",k);
      fprintf(fo4,"\nnode         F(1)           F(2)");
      }

    j= 1;
            
    for(i = 1;i <= 6;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      j+= 2;   
      }
            
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
    wtyp88e(k,4);

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
* nun Elementsteifigkeitsmatrix fuer raeumliches Stabelement berechen
*---------------------------------------------------------------------*/
    stab88();

/*----------------------------------------------------------------------
* Compilation fuer stab88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 3;
    mxfe  = 6;
            
    forc88();
    
    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = Stab im Raum",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = truss in space",k);
      fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
      }

    j= 1;
            
    for(i = 1;i <= 2;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }
            
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
    wtyp88e(k,5);

/*----------------------------------------------------------------------
* Wellenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer Wellenelement berechen
*---------------------------------------------------------------------*/
    well88();

/*----------------------------------------------------------------------
* Compilation fuer well88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[ koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[ koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 6;
    mxfe  = 12;

    forc88();
    
    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = Welle",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)\
           F(4)           F(5)           F(6)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = shaft",k);
      fprintf(fo4,"\nnode         F(1)           F(2)           F(3)\
           F(4)           F(5)           F(6)");
      }

    j= 1;
            
    for(i = 1;i <= 2;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE  %+#13.5lE\
  %+#13.5lE  %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1],f[j+2],f[j+3],f[j+4],f[j+5]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      fsum4[koi[koffs[k]+i-1]] += f[j+3];
      fsum5[koi[koffs[k]+i-1]] += f[j+4];
      fsum6[koi[koffs[k]+i-1]] += f[j+5];
      j+= 6;   
      }

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
    wtyp88e(k,6);

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
* nun Elementsteifigkeitsmatrix fuer Toruselement berechen
*---------------------------------------------------------------------*/
    ring88();

/*----------------------------------------------------------------------
* Compilation fuer ring88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[koi[koffs[k]+1]] -1;
    mcomp[3]= ioffs[koi[koffs[k]+2]] -1;
         
    mxknot= 3;
    mxfrei= 2;
    mxfe  = 6;

    forc88();
    
    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = 3-K Torus",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = 3-n torus",k);
      fprintf(fo4,"\nnode         F(1)           F(2)");
      }

    j= 1;
            
    for(i = 1;i <= 3;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      j+= 2;   
      }

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
      wtyp88e(k,7);
      ktyp= 2;
      }
    else
      {
      wtyp88e(k,8);
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
* nun Elementsteifigkeitsmatrix fuer iso-8-knoten Scheibe/Tor  berechen
*---------------------------------------------------------------------*/
    iret= qshe88();
    if(iret != 0)
      {
      wlog88e(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88e(iret);
      PostQuitMessage(0);
      return(0);
      }
    
/*----------------------------------------------------------------------
* Compilation fuer qshe88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 8;
    mxfrei= 2;
    mxfe  = 16;
            
    forc88();

    if(ktyp == 2)
      {    
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = %5ld     Typ = 8-K Scheibe",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = %5ld     type = 8-n plane stress",k);
        fprintf(fo4,"\nnode         F(1)           F(2)");
        }
      }
    if(ktyp == 0)
      {    
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = %5ld     Typ = 8-K Torus",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = %5ld     type = 8-n torus",k);
        fprintf(fo4,"\nnode         F(1)           F(2)");
        }
      }
       
    j= 1;
            
    for(i = 1;i <= 8;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      j+= 2;   
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
    wtyp88e(k,9);

/*----------------------------------------------------------------------
* ebenes Stabelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer e. Stabelement berechen
*---------------------------------------------------------------------*/
    esta88();

/*----------------------------------------------------------------------
* Compilation fuer esta88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[ koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[ koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 2;
    mxfe  = 4;

    forc88();
    
    if(LANG == 1)
      {  
      fprintf(fo4,"\nElement # = %5ld     Typ = Stab in der Ebene",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)");
      }
    if(LANG == 2)
      {  
      fprintf(fo4,"\nelement # = %5ld     type = truss in plane",k);
      fprintf(fo4,"\nnode         F(1)           F(2)");
      }

    j= 1;
            
    for(i = 1;i <= 2;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      j+= 2;   
      }

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
    wtyp88e(k,10);
 
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
* nun Elementsteifigkeitsmatrix fuer iso-20-Knoten Hexaeder berechen
*---------------------------------------------------------------------*/
    iret= hexa88();
    if(iret != 0)
      {
      wlog88e(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88e(iret);
      PostQuitMessage(0);
      return(0);
      }

/*----------------------------------------------------------------------
* Compilation fuer hexa88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 20;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 20;
    mxfrei= 3;
    mxfe  = 60; 

    forc88();
    
    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = 20-K Hexaeder",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = 20-n hexahedron",k);
      fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
      }

    j= 1;
            
    for(i = 1;i <= 20;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-20-Knoten Hexaeder
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 12-knoten Scheibe/Torus, isoparametrischer kubischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 11 || ityp[k]== 12)
    {
    if (ityp[k]== 11)
      {
      wtyp88e(k,11);
      ktyp= 2;
      }
    else
      {
      wtyp88e(k,12);
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
* nun Elementsteifigkeitsmatrix fuer iso-12-Knoten Scheibe/Tor  ber.
*---------------------------------------------------------------------*/
    iret= cshe88();
    if(iret != 0)
      {
      wlog88e(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88e(iret);
      PostQuitMessage(0);
      return(0);
      }

/*----------------------------------------------------------------------
* Compilation fuer cshe88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 12;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 12;
    mxfrei= 2;
    mxfe  = 24;
            
    forc88();

    if(ktyp == 2)
      {    
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = %5ld     Typ = 12-K Scheibe",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = %5ld     type = 12-n plane stress",k);
        fprintf(fo4,"\nnode         F(1)           F(2)");
        }
      }
    if(ktyp == 0)
      {    
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = %5ld     Typ = 12-K Torus",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = %5ld     type = 12-n torus",k);
        fprintf(fo4,"\nnode         F(1)           F(2)");
        }
      }
       
    j= 1;
            
    for(i = 1;i <= 12;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      j+= 2;   
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
    wtyp88e(k,13);

/*----------------------------------------------------------------------
* Balkenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Elementsteifigkeitsmatrix fuer ebenes Balkenelement berechen
*---------------------------------------------------------------------*/
    ebal88();

/*----------------------------------------------------------------------
* Compilation fuer ebal88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 3;
    mxfe  = 6;

    forc88();
    
    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = Balken in der Ebene",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = beam in plane",k);
      fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
      }

    j= 1;
            
    for(i = 1;i <= 2;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende ebenes Balkenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 6-knoten Dreieck-Scheibe/Torus, isop. quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 14 || ityp[k]== 15)
    {
    if (ityp[k]== 14)
      {
      wtyp88e(k,14);
      ktyp= 2;
      }
    else
      {
      wtyp88e(k,15);
      ktyp= 0;
      }

/*----------------------------------------------------------------------
* iso 6-Knoten Dreieck-Scheibe/Torus: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-6-knoten Scheibe/Tor  berechnen
*---------------------------------------------------------------------*/
    iret= isod88();
    if(iret != 0)
      {
      wlog88e(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88e(iret);
      PostQuitMessage(0);
      return(0);
      }
    
/*----------------------------------------------------------------------
* Compilation fuer isod88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 6;
    mxfrei= 2;
    mxfe  = 12;
            
    forc88();

    if(ktyp == 2)
      {    
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = %5ld     Typ = 6-K isop. Scheibe",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = %5ld     type = 6-n isop. plane stress",k);
        fprintf(fo4,"\nnode         F(1)           F(2)");
        }
      }
    if(ktyp == 0)
      {    
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = %5ld     Typ = 6-K isop. Torus",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = %5ld     type = 6-n isop. torus",k);
        fprintf(fo4,"\nnode         F(1)           F(2)");
        }
      }
       
    j= 1;
            
    for(i = 1;i <= 6;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      j+= 2;   
      }
            
    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-6-Knoten Dreieck-Scheibe/Torus
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 10-Knoten Tetraeder, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 16)
    {
    wtyp88e(k,16);
 
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
* nun Elementsteifigkeitsmatrix fuer iso-10-Knoten Tetraeder berechen
*---------------------------------------------------------------------*/
    iret= tetr88();
    if(iret != 0)
      {
      wlog88e(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88e(iret);
      PostQuitMessage(0);
      return(0);
      }

/*----------------------------------------------------------------------
* Compilation fuer tetr88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 10;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 10;
    mxfrei= 3;
    mxfe  = 30; 

    forc88();

    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = 10-K Tetraeder",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = 10-n tetrahedron",k);
      fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
      }
      
    j= 1;
            
    for(i = 1;i <= 10;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-10-Knoten Tetraeder
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 4-Knoten Tetraeder, lineaer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 17)
    {
    wtyp88e(k,17);
 
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
* nun Elementsteifigkeitsmatrix fuer 4-Knoten Tetraeder berechen
*---------------------------------------------------------------------*/
    iret= spur88();
    if(iret != 0)
      {
      wlog88e(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88e(iret);
      PostQuitMessage(0);
      return(0);
      }

/*----------------------------------------------------------------------
* Compilation fuer spur88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 4;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 4;
    mxfrei= 3;
    mxfe  = 12; 

    forc88();

    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = 4-K Tetraeder",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = 4-n tetrahedron",k);
      fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
      }
      
    j= 1;
            
    for(i = 1;i <= 4;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 4-Knoten Tetraeder
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 6-Knoten Reissner- Mindlin Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 18)
    {
    wtyp88e(k,18);

/*----------------------------------------------------------------------
* 6-Knoten Plattenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }
          
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 6-Knoten Plattenelement berechen
*---------------------------------------------------------------------*/
    iret= spla88();
    if(iret != 0)
      {
      wlog88e(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88e(iret);
      PostQuitMessage(0);
      return(0);
      }

/*----------------------------------------------------------------------
* Compilation fuer spla88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 6;
    mxfrei= 3;
    mxfe  = 18;
         
    forc88();
    
    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = 6-K Mindlin- Platte",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = 6-n Mindlin plate",k);
      fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
      }
    
    j= 1;
            
    for(i = 1;i <= 6;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 6-Knoten Reissner- Mindlin Platte
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 16-Knoten Reissner Mindlin Platte, kubischer Lagrange Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 19)
    {
    wtyp88e(k,19);
 
/*----------------------------------------------------------------------
* 16-Knoten Platte: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 16;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 16-Knoten Platte berechen
*---------------------------------------------------------------------*/
    iret= hpla88();
    if(iret != 0)
      {
      wlog88e(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88e(iret);
      PostQuitMessage(0);
      return(0);
      }

/*----------------------------------------------------------------------
* Compilation fuer hpla88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 16;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 16;
    mxfrei= 3;
    mxfe  = 48; 

    forc88();

    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = 16-K Mindlin Platte",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = 16-n Mindlin plate",k);
      fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
      }
      
    j= 1;
            
    for(i = 1;i <= 16;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 16-Knoten Lagrange Reissner Mindlin Platte
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 8-Knoten Reissner- Mindlin Serendipity Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 20)
    {
    wtyp88e(k,20);

/*----------------------------------------------------------------------
* 8-Knoten Plattenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }
          
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 8-Knoten Plattenelement berechen
*---------------------------------------------------------------------*/
    iret= apla88();
    if(iret != 0)
      {
      wlog88e(0L,LOG_JACNEG);
      fclose(fwlo);
      ale88e(iret);
      PostQuitMessage(0);
      return(0);
      }

/*----------------------------------------------------------------------
* Compilation fuer apla88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 8;
    mxfrei= 3;
    mxfe  = 24;
         
    forc88();
    
    if(LANG == 1)
      {
      fprintf(fo4,"\nElement # = %5ld     Typ = 8-K Mindlin- Platte",k);
      fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
      }
    if(LANG == 2)
      {
      fprintf(fo4,"\nelement # = %5ld     type = 8-n Mindlin plate",k);
      fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
      }
    
    j= 1;
            
    for(i = 1;i <= 8;i++)
      {
      fprintf(fo4,"\n%5ld   %+#13.5lE  %+#13.5lE  %+#13.5lE",
      koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 8-Knoten Reissner- Mindlin Serendipity Platte
*---------------------------------------------------------------------*/
    }


L7000:;
  fprintf(fo4,"\n");
  
/***********************************************************************
* Ende der Schleife ueber alle Elemente
***********************************************************************/
  }  /* e 8000 */

/***********************************************************************
* Schleife ueber alle Knoten
***********************************************************************/
fprintf(fo4,"\n");

if(LANG == 1)
  {
  fprintf(fo4,"Nun die aufsummierten Knotenkraefte je Knoten\n");
  fprintf(fo4,"---------------------------------------------\n\n");
  fprintf(fo4,"Knoten       F(1)           F(2)           F(3)\
           F(4)           F(5)           F(6)\n\n");
  }
if(LANG == 2)
  {
  fprintf(fo4,"now the nodal sums for each node\n");
  fprintf(fo4,"--------------------------------\n");
  fprintf(fo4,"  node       F(1)           F(2)           F(3)\
           F(4)           F(5)           F(6)\n\n");
  }

for(i = 1;i <= nkp;i++)
  {
  fprintf(fo4,
  "%5ld   %+#13.5lE  %+#13.5lE  %+#13.5lE  %+#13.5lE  %+#13.5lE  %+#13.5lE\n",
  i,fsum1[i],fsum2[i],fsum3[i],fsum4[i],fsum5[i],fsum6[i]);
  }

/*----------------------------------------------------------------------
* Ende Z88E
*---------------------------------------------------------------------*/
fclose(fo4);

wrim88e(0L,TX_EXITZ88E);
wlog88e(0L,LOG_EXITZ88E);

/*---------------------------------------------------------------------------
* Ende Case Go
*--------------------------------------------------------------------------*/
        if(LANG == 1) strcpy(cmess,"Knotenkraefte Z88E gelaufen");
        if(LANG == 2) strcpy(cmess,"Computing Nodal Forces Z88E done");
        MessageBox(NULL,cmess,"Z88E", MB_OK | MB_ICONINFORMATION);
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
