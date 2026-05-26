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
* Compilerunit gxi588 enthaelt:
* g1i588
* g2i588
* 16.9.2005 Rieg 
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
* Start G1I588
***********************************************************************/
int g1i588(HWND hWnd)
{
extern FILE *fdatei;

extern FR_INT4 LANG;
extern FR_INT4 ne,npr,iwarn,izeile;

int ier;

char *cresult;
char cline[256], cmess[512], chead[12];

/**********************************************************************
* Header vorbelegen
**********************************************************************/
strcpy(chead,"Z88I5.TXT");

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

ier= sscanf(cline,"%ld",&npr);
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
* logische Pruefung npr 
*---------------------------------------------------------------------*/
if(npr > ne)
  {
  if(LANG == 1) sprintf(cmess,
  "%s\nZuviele Flaechenlasten in Zeile 1 entdeckt .. mehr als \
%ld Elemente in Z88I1.TXT (Zeile 1, 4.Wert)",cline,ne);

  if(LANG == 2) sprintf(cmess,
  "%s\ntoo many surface loads in line 1 detected .. more than \
%ld elements in Z88I1.TXT (line 1, 4th entry)",cline,ne);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

if(npr <= 0)
  {
  if(LANG == 1) 
    sprintf(cmess,"%s\nZuwenig Flaechenlasten in Zeile 1 entdeckt",cline);

  if(LANG == 2)
    sprintf(cmess,"%s\ntoo few surface loads in line 1 detected", cline);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

return(0);
}
          
/***********************************************************************
* Start G2I588
***********************************************************************/
int g2i588(HWND hWnd)
{
extern FILE *fdatei;

extern FR_INT4 LANG;

extern FR_INT4AY jtyp;

extern FR_INT4 nkp,ne,npr,izeile;

double pree,tr1e,tr2e;

FR_INT4 noi[9];

FR_INT4 i,j,k,jele,ityp,jmax;

int ier;

char *cresult;
char cline[256], cmess[1024], chead[12];

/**********************************************************************
* Header vorbelegen
**********************************************************************/
strcpy(chead,"Z88I5.TXT");

/**********************************************************************
* Checken der 2.Gruppe
**********************************************************************/
for(i = 1;i <= npr;i++)
  {
  izeile++;

/*----------------------------------------------------------------------
* welcher Typ?
*---------------------------------------------------------------------*/            
  cresult= fgets(cline,256,fdatei);
  if(!cresult)
    {
    erif88(hWnd,izeile);
    return(2);
    }

  ier= sscanf(cline,"%ld",&jele);

  if(jele < 1 || jele > ne)
    {
    if(LANG == 1) sprintf(cmess,
      "%s\nElementnummer in Zeile %ld gibts garnicht\n",cline,izeile);
    if(LANG == 2) sprintf(cmess,
      "%s\nelement number in line %ld does not exist\n",cline,izeile);
    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }

  ityp= jtyp[jele];
  
  if(ityp == 2 || ityp == 3 || ityp == 4 || ityp == 5 || ityp == 6 ||
     ityp == 9 || ityp == 13)
    {
    if(LANG == 1) sprintf(cmess,
      "%s\nElementtyp in Zeile %ld nicht geeignet fuer Flaechenlasten",
      cline,izeile);
    if(LANG == 2) sprintf(cmess,
      "%s\nelement type in line %ld not allowed for surface loads",
      cline,izeile);
    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }

/*=====================================================================
* Elementtyp 1
*====================================================================*/ 
  if(ityp == 1)
    {
    ier= sscanf(cline,"%ld %lf %lf %lf %ld %ld %ld %ld",
         &jele,&pree,&tr1e,&tr2e,&noi[1],&noi[2],&noi[3],&noi[4]);

    if(ier != 8) 
      {
      if(LANG == 1) sprintf(cmess,
        "%s\nSchreibfehler oder fehlende Daten in Zeile %ld entdeckt",
        cline,izeile);
      if(LANG == 2) sprintf(cmess,
        "%s\ntyping error or missing entries in line %ld detected",
        cline,izeile);
      MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
      return(2);
      }
    jmax= 4;
    }

/*=====================================================================
* Elementtyp 10
*====================================================================*/ 
  if(ityp == 10)
    {
    ier= sscanf(cline,"%ld %lf %lf %lf %ld %ld %ld %ld  %ld %ld %ld %ld",
         &jele,&pree,&tr1e,&tr2e,&noi[1],&noi[2],&noi[3],&noi[4],
         &noi[5],&noi[6],&noi[7],&noi[8]);

    if(ier != 12) 
      {
      if(LANG == 1) sprintf(cmess,
        "%s\nSchreibfehler oder fehlende Daten in Zeile %ld entdeckt",
        cline,izeile);
      if(LANG == 2) sprintf(cmess,
        "%s\ntyping error or missing entries in line %ld detected",
        cline,izeile);
      MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
      return(2);
      }
    jmax= 8;
    }

/*=====================================================================
* Elementtyp 17
*====================================================================*/ 
  if(ityp == 17)
    {
    ier= sscanf(cline,"%ld %lf %ld %ld %ld",
         &jele,&pree,&noi[1],&noi[2],&noi[3]);

    if(ier != 5) 
      {
      if(LANG == 1) sprintf(cmess,
        "%s\nSchreibfehler oder fehlende Daten in Zeile %ld entdeckt",
        cline,izeile);
      if(LANG == 2) sprintf(cmess,
        "%s\ntyping error or missing entries in line %ld detected",
        cline,izeile);
      MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
      return(2);
      }
    jmax= 3;
    }

/*=====================================================================
* Elementtyp 16
*====================================================================*/ 
  if(ityp == 16)
    {
    ier= sscanf(cline,"%ld %lf %ld %ld %ld %ld %ld %ld",
         &jele,&pree,&noi[1],&noi[2],&noi[3],&noi[4],&noi[5],&noi[6]);

    if(ier != 8) 
      {
      if(LANG == 1) sprintf(cmess,
        "%s\nSchreibfehler oder fehlende Daten in Zeile %ld entdeckt",
        cline,izeile);
      if(LANG == 2) sprintf(cmess,
        "%s\ntyping error or missing entries in line %ld detected",
        cline,izeile);
      MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
      return(2);
      }
    jmax= 6;
    }

/*=====================================================================
* Elementtyp 7,8,14,15
*====================================================================*/ 
  if(ityp == 7 || ityp == 8 || ityp == 14 || ityp == 15)
    {
    ier= sscanf(cline,"%ld %lf %lf %ld %ld %ld",
         &jele,&pree,&tr1e,&noi[1],&noi[2],&noi[3]);

    if(ier != 6) 
      {
      if(LANG == 1) sprintf(cmess,
        "%s\nSchreibfehler oder fehlende Daten in Zeile %ld entdeckt",
        cline,izeile);
      if(LANG == 2) sprintf(cmess,
        "%s\ntyping error or missing entries in line %ld detected",
        cline,izeile);
      MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
      return(2);
      }
    jmax= 3;
    }

/*=====================================================================
* Elementtyp 11,12
*====================================================================*/ 
  if(ityp == 11 || ityp == 12)
    {
    ier= sscanf(cline,"%ld %lf %lf %ld %ld %ld %ld",
         &jele,&pree,&tr1e,&noi[1],&noi[2],&noi[3],&noi[4]);

    if(ier != 7) 
      {
      if(LANG == 1) sprintf(cmess,
        "%s\nSchreibfehler oder fehlende Daten in Zeile %ld entdeckt",
        cline,izeile);
      if(LANG == 2) sprintf(cmess,
        "%s\ntyping error or missing entries in line %ld detected",
        cline,izeile);
      MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
      return(2);
      }
    jmax= 4;
    }

/*=====================================================================
* Elementtyp 18,19 & 20
*====================================================================*/ 
  if(ityp == 18 || ityp == 19 || ityp == 20)
    {
    ier= sscanf(cline,"%ld %lf",&jele,&pree);

    if(ier != 2) 
      {
      if(LANG == 1) sprintf(cmess,
        "%s\nSchreibfehler oder fehlende Daten in Zeile %ld entdeckt",
        cline,izeile);
      if(LANG == 2) sprintf(cmess,
        "%s\ntyping error or missing entries in line %ld detected",
        cline,izeile);
      MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
      return(2);
      }
    jmax= 0;
    }

/*======================================================================
* koi(j) innerhalb logischer Grenzen ?
*=====================================================================*/
  for(j = 1;j <= jmax;j++)
    {
    if(!(noi[j] > 0 && noi[j] <= nkp))
      {
      if(LANG == 1) sprintf(cmess,
        "%s\nKnoten nicht zwischen 1 und %ld fuer Element %ld entdeckt",
        cline,nkp,i);
      if(LANG == 2) sprintf(cmess,
        "%s\nnode number not in range (1 to %ld) for element %ld detected",
        cline,nkp,i);
      MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
      return(2);
      }
    }

  for(j = 1;j <= jmax-1;j++)
    {
    for(k= j+1;k <= jmax;k++)
      {
      if(noi[j] == noi[k])
        {
        if(LANG == 1) sprintf(cmess,
          "%s\nIdentische Knoten fuer Element %ld in Zeile %ld entdeckt",
          cline,jele,izeile);
        if(LANG == 2) sprintf(cmess,
          "%s\nidentical nodes for element %ld in line %ld detected",
          cline,jele,izeile);
        MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
        return(2);
        }
      }
    }

/*---------------------------------------------------------------------
* Schleifenende
*--------------------------------------------------------------------*/ 
  }
return(0);
}

