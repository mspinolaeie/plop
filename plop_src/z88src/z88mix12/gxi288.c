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
* V10.0  December 12, 2001
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
* Compilerunit gxi288 enthaelt:
* g1i288
* g2i288
* 9.09.2002 Rieg 
***********************************************************************/
#ifdef FR_WIN95
#include <z88v.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#endif

/***********************************************************************
* Functions
***********************************************************************/
void erif88(HWND hWnd,long izeile);

/***********************************************************************
* Start G1I288
***********************************************************************/
int g1i288(HWND hWnd)
{
extern FILE *fdatei;

extern FR_INT4 LANG;
extern FR_INT4 ndim,nfg,nrb,iwarn,izeile;

int ier;

char *cresult;
char cline[256], cmess[512], chead[12];

/**********************************************************************
* Header vorbelegen
**********************************************************************/
strcpy(chead,"Z88I2.TXT");

/**********************************************************************
* Checken der 1.Zeile
**********************************************************************/
izeile= 1; 

cresult= fgets(cline,256,fdatei);
if(!cresult)
  {
  erif88(hWnd,izeile);
  return(2);
  }

ier= sscanf(cline,"%ld",&nrb);
if(ier != 1) 
  {
  if(LANG == 1) sprintf(cmess,
  "%s\nSchreibfehler oder fehlende Daten in Zeile 1 entdeckt",cline);

  if(LANG == 2) sprintf(cmess,
  "%s\ntyping error  or missing entries in line 1 detected",cline);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }
        
/*----------------------------------------------------------------------
* logische Pruefung nrb 
*---------------------------------------------------------------------*/
if(nrb > nfg)
  {
  if(LANG == 1) sprintf(cmess,
  "%s\nZuviele Randbedingungen in Zeile 1 entdeckt .. mehr als \
%ld Freiheitsgrade in Z88I1.TXT (Zeile 1, 4.Wert)",cline,nfg);

  if(LANG == 2) sprintf(cmess,
  "%s\ntoo many constraints in line 1 detected .. more than \
%ld DOF in Z88I1.TXT (line 1, 4th entry)",cline,nfg);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

if(ndim == 2)
  {
  if(nrb < 3)
    {
    if(LANG == 1) sprintf(cmess,"%s\nZuwenig Randbedingungen (< 3) fuer 2-D \
    Struktur in Zeile 1 entdeckt", cline);

    if(LANG == 2) sprintf(cmess,"%s\ntoo few constraints (< 3) for 2-D \
    structure in line 1 detected", cline);

    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }
  }

if(ndim == 3)
  {
  if(nrb < 6)
    {
    if(LANG == 1) sprintf(cmess,"%s\nZuwenig Randbedingungen (< 6) fuer 3-D \
    Struktur in Zeile 1 entdeckt", cline);

    if(LANG == 2) sprintf(cmess,"%s\ntoo few constraints (< 6) for 3-D \
    structure in line 1 detected", cline);

    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }
  }
return(0);
}
          
/***********************************************************************
* Start G2I288
***********************************************************************/
int g2i288(HWND hWnd)
{
extern FILE *fdatei;

extern FR_INT4 LANG;

extern FR_INT4AY ifrei;

extern FR_INT4 nkp,nrb,iwarn,izeile;

double wert;

FR_INT4 nkn,ifg,iflag1,nknalt,ifgalt,i;

int ier;

char *cresult;
char cline[256], clina[256], cmess[1024], chead[12];

/**********************************************************************
* Header vorbelegen
**********************************************************************/
strcpy(chead,"Z88I2.TXT");

/**********************************************************************
* Checken der 2.Gruppe
**********************************************************************/
for(i = 1;i <= nrb;i++)
  {
  izeile++;

  if(i > 1)
    {
    nknalt= nkn;
    strcpy(clina,cline);
    ifgalt= ifg;
    }
            
  cresult= fgets(cline,256,fdatei);
  if(!cresult)
    {
    erif88(hWnd,izeile);
    return(2);
    }

  ier= sscanf(cline,"%ld %ld %ld %lg",&nkn,&ifg,&iflag1,&wert);
  if(ier != 4) 
    {
    if(LANG == 1) sprintf(cmess,
    "%s\nSchreibfehler oder fehlende Daten in Zeile %ld entdeckt\n\
Stimmt Anzahl Randbedingungen aus Zeile 1 mit der dann folgenden \
Anzahl Steuerzeilen ueberein ?", cline,izeile);

    if(LANG == 2) sprintf(cmess,
    "%s\ntyping error or missing entries in line %ld detected\n\
matches number of constraints defined in line 1 the then folowing \
number of constraint lines ?", cline,izeile);

    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }

/*----------------------------------------------------------------------
* logische Pruefung
*---------------------------------------------------------------------*/
  if(nkn < 1 || nkn > nkp)
    {
    if(LANG == 1) sprintf(cmess,"%s\nKnotennummer ungueltig\n\
1.Wert in Zeile %ld ueberpruefen",cline,izeile);

    if(LANG == 2) sprintf(cmess,"%s\nnode number invalid\n\
check 1st entry in line %ld",cline,izeile);

    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }

  if(i > 1)
    { 
    if(nkn < nknalt)
      {
      if(LANG == 1) sprintf(cmess,
"%s\n%s\nKnotennummern nicht aufsteigend geordnet\n\
1.Wert in Zeile %ld ueberpruefen\n1.Wert in Zeile %ld ueberpruefen",
      clina,cline,izeile-1,izeile);

      if(LANG == 2) sprintf(cmess,
"%s\n%s\nnode numbers not ascending arranged\n\
check 1st entry in line %ld\ncheck 1. entry in line %ld",
      clina,cline,izeile-1,izeile);

      MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
      return(2);
      }
    }
          
  if(ifg < 1)
    {
    if(LANG == 1) sprintf(cmess,"%s\nNummer Freiheitsgrad unzulaessig\n\
2.Wert in Zeile %ld ueberpruefen",cline,izeile);

    if(LANG == 2) sprintf(cmess,"%s\nnumber DOF invalid\n\
check 2nd entry in line %ld",cline,izeile);

    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }

  if(ifg > ifrei[nkn])
    {
    if(LANG == 1) sprintf(cmess,
"%s\nNummer Freiheitsgrad groesser als in Z88I1.TXT\n\
2.Wert in Zeile %ld ueberpruefen",cline,izeile);

    if(LANG == 2) sprintf(cmess,
"%s\nnumber DOF greater than defined in Z88I1.TXT\n\
check 2nd entry in line %ld",cline,izeile);

    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }

  if(nkn == nknalt)
    { 
    if(ifg <= ifgalt)
      {
      if(LANG == 1) sprintf(cmess,
"%s\n%s\nFreiheitsgrade nicht aufsteigend geordnet\n\
2.Wert in Zeile %ld ueberpruefen\n2.Wert in Zeile %ld ueberpruefen",
      clina,cline,izeile-1,izeile);

      if(LANG == 2) sprintf(cmess,
"%s\n%s\nDOF not ascending arranged\n\
check 2nd entry in line %ld\ncheck 2. entry in line %ld",
      clina,cline,izeile-1,izeile);

      MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
      return(2);
      }
    }

  if(!(iflag1 == 1 || iflag1 == 2))
    {
    if(LANG == 1) sprintf(cmess,
"%s\nLast/Verschiebungsflag unzulaessig (nicht 1 oder 2)\n\
3.Wert in Zeile %ld ueberpruefen",cline,izeile);

    if(LANG == 2) sprintf(cmess,
"%s\nload/displacement flag invalid (not 1 or 2)\n\
check 3rd entry in line %ld",cline,izeile);

    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }

  }
return(0);
}

