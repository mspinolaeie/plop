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
* Diese Compilerunit umfasst:
* - wrim88f gibt Texte aus (1 FR_INT4)
* - wproz88 gibt Prozentanteil aus (1 FR_INT4, 1 double)
* - wtyp88f gibt Elementtypen aus (1 FR_INT4, 1 FR_INT4)
* 14.9.2005 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer WindowsNT und 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88f.h>
#include <windows.h>
#include <string.h>   /* strlen  */
#include <stdio.h>    /* sprintf */
#include <stdlib.h>   /* ltoa    */
#endif

/***********************************************************************
*  hier beginnt Function wrim88f
***********************************************************************/
int wrim88f(FR_INT4 i,int iatx)
{
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];

switch(iatx)
  {
  case TX_REAI1:
    if(LANG == 1) TextOut(hDC,10,50,"Z88I1.TXT einlesen :",20);
    if(LANG == 2) TextOut(hDC,10,50,"Reading Z88I1.TXT : ",20);
  break;

  case TX_KOOR:
    if(LANG == 1) TextOut(hDC,290,50,"Koordinaten einlesen",20);
    if(LANG == 2) TextOut(hDC,290,50,"Reading coordinates ",20);
  break;

  case TX_POLAR:
    if(LANG == 1) TextOut(hDC,290,50,"Polar/Zylinder-Koordinaten",26);
    if(LANG == 2) TextOut(hDC,290,50,"Polar/cylinder-coordinates",26);
  break;

  case TX_KOIN:
    if(LANG == 1) 
      TextOut(hDC,290,50,"Koinzidenz einlesen                 ",36);
    if(LANG == 2) 
      TextOut(hDC,290,50,"Reading element informations        ",36);
  break;

  case TX_EGES:
    if(LANG == 1) TextOut(hDC,290,50,"Elastizitaetsgesetze einlesen",29);
    if(LANG == 2) TextOut(hDC,290,50,"Reading material informations",29);
  break;

  case TX_Z88A:
    if(LANG == 1) TextOut(hDC,10,70,">>> Start Z88A: Pass 1 von Z88F <<<",35);
    if(LANG == 2) TextOut(hDC,10,70,">>> Start Z88A: pass  1 of Z88F <<<",35);
  break;

  case TX_FORMA:
    if(LANG == 1) TextOut(hDC,290,110,"Formatieren",11);
    if(LANG == 2) TextOut(hDC,290,110,"Formatting ",11);
  break;

  case TX_WRI1Y:
    if(LANG == 1) TextOut(hDC,290,70,"Z88O1.BNY beschreiben",21);
    if(LANG == 2) TextOut(hDC,290,70,"Writing Z88O1.BNY    ",21);
  break;

  case TX_WRIO0:
    if(LANG == 1) TextOut(hDC,290,70,"Z88O0.TXT beschreiben  ",23);
    if(LANG == 2) TextOut(hDC,290,70,"Writing Z88O0.TXT      ",23);
  break;

  case TX_GSERF:
    if(LANG == 1) sprintf(cline,"GS erfordert %ld Elemente",i);
    if(LANG == 2) sprintf(cline,"GS needs %ld elements",i);
    laenge= strlen(cline);
    TextOut(hDC,10,90,cline,laenge);
  break;

  case TX_KOIERF:
    if(LANG == 1) sprintf(cline,"KOI erfordert %ld Elemente",i);
    if(LANG == 2) sprintf(cline,"KOI needs %ld elements",i);
    laenge= strlen(cline);
    TextOut(hDC,290,90,cline,laenge);
  break;

  case TX_Z88B:
    if(LANG == 1) TextOut(hDC,10,110,">>> Start Z88B: Pass 2 von Z88F <<<",35);
    if(LANG == 2) TextOut(hDC,10,110,">>> Start Z88B: pass  2 of Z88F <<<",35);
  break;

  case TX_COMPI:
    if(LANG == 1) TextOut(hDC,290,110,"Compilation",11);
    if(LANG == 2) TextOut(hDC,290,110,"Compilation",11);
  break;

  case TX_REAI5:
    if(LANG == 1) TextOut(hDC,290,150,"Lastvektoren berechnen",22);
    if(LANG == 2) TextOut(hDC,290,150,"computing load vectors",22);
  break;

  case TX_Z88CC:
    if(LANG == 1)TextOut(hDC,10,170,">>> Start Z88CC: Pass 3 von Z88F <<<",36);
    if(LANG == 2)TextOut(hDC,10,170,">>> Start Z88CC: pass  3 of Z88F <<<",36);
  break;

  case TX_REAI2:
    if(LANG == 1) TextOut(hDC,290,170,"Lesen RB-File Z88I2.TXT",23);
    if(LANG == 2) TextOut(hDC,290,170,"Reading const Z88I2.TXT",23);
  break;

  case TX_ERBPA:
    if(LANG == 1) sprintf(cline,"Einarbeiten der Randbed. Pass %ld",i);
    if(LANG == 2) sprintf(cline,"Incorporating constraints pass %ld",i);
    laenge= strlen(cline);
    TextOut(hDC,290,170,cline,laenge);
  break;

  case TX_WRIO1:
    if(LANG == 1) TextOut(hDC,10,190,"Z88O1.TXT beschreiben",21);
    if(LANG == 2) TextOut(hDC,10,190,"Writing Z88O1.TXT    ",21);
  break;

  case TX_SCAL88:
    if(LANG == 1) TextOut(hDC,290,190,"Start SCAL88",12);
    if(LANG == 2) TextOut(hDC,290,190,"Start SCAL88",12);
  break;

  case TX_CHOY88:
    if(LANG == 1)
      TextOut(hDC,10,210,"Start des Cholesky- Verfahrens CHOY88",37);
    if(LANG == 2)
      TextOut(hDC,10,210,"Start of Cholesky- solver CHOY88     ",37);
  break;

  case TX_NFG:
    if(LANG == 1) sprintf(cline,"%ld * %ld=Groesse Gleichungsystem",i,i);
    if(LANG == 2) sprintf(cline,"%ld * %ld=size system of equations",i,i);
    laenge= strlen(cline);
    TextOut(hDC,10,230,cline,laenge);
  break;

  case TX_CHOJ:
    ltoa(i,cline,10);
    laenge= strlen(cline);
    TextOut(hDC,360,230,cline,laenge);
  break;

  case TX_VORW:
    if(LANG == 1) TextOut(hDC,10,250,"Vorwaertseinsetzen",18);
    if(LANG == 2) TextOut(hDC,10,250,"Forward-substitutution",22);
  break;

  case TX_RUECKW:
    if(LANG == 1) TextOut(hDC,290,250,"Rueckwaertseinsetzen",20);
    if(LANG == 2) TextOut(hDC,290,250,"Back-substitution   ",20);
  break;

  case TX_WRI3Y:
    if(LANG == 1) TextOut(hDC,10,270,"Z88O3.BNY beschreiben",21);
    if(LANG == 2) TextOut(hDC,10,270,"Writing Z88O3.BNY    ",21);
  break;

  }

return(0);
}

/***********************************************************************
* function wproz88 gibt Prozentanteil aus
***********************************************************************/ 
int wproz88(FR_INT4 iltx,double proz)
{
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];

if(LANG == 1) sprintf(cline,"GS enthaelt %ld Elemente",iltx);
if(LANG == 2) sprintf(cline,"GS needs %ld elements",iltx);
laenge= strlen(cline);
TextOut(hDC,10,130,cline,laenge);

if(LANG == 1) sprintf(cline,"Anteil Null in GS ist %4.0lf %%",proz);
if(LANG == 2) sprintf(cline,"portion zero in GS is %4.0lf %%",proz);
laenge= strlen(cline);
TextOut(hDC,290,130,cline,laenge);

return(0);
}

/***********************************************************************
*  function wtyp88f gibt Elementtypen in Z88F aus
***********************************************************************/ 
int wtyp88f(FR_INT4 k,FR_INT4 i)
{
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];

if(LANG == 1) sprintf(cline,"Nr. %5ld Typ %5ld",k,i);
if(LANG == 2) sprintf(cline,"no. %5ld type %5ld",k,i);
laenge= strlen(cline);
TextOut(hDC,380,110,cline,laenge);

return(0);
}

