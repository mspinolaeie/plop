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
/**********************************************************************
* Compilerunit g1i188 fuer WindowsNT und 95 enthaelt:
*
* Function g1i188 prueft die erste zeile fuer Z88I1.TXT & Z88NI.TXT
* Function erif88: falscher Fileaufbau
*
* 22.9.2005 Rieg
**********************************************************************/
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
* Start G1I188
***********************************************************************/
int g1i188(HWND hWnd)
{
extern FILE *fdatei;

extern FR_INT4 LANG;

extern FR_INT4 MAXK,MAXE,MAXNFG,MAXNEG;
extern FR_INT4 ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag,niflag;
extern FR_INT4 iwarn,izeile,ifnii1;

int ier;

char *cresult;
char cline[256], cmess[1024], chead[12];

/**********************************************************************
* Header vorbelegen
**********************************************************************/
if(ifnii1 == 1)
  strcpy(chead,"Z88NI.TXT");
else
  strcpy(chead,"Z88I1.TXT");  
  
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

if(ifnii1 == 0)              /* fuer Z88I1.TXT */
  {
  ier= sscanf(cline,"%ld %ld %ld %ld %ld %ld %ld %ld %ld",
  &ndim,&nkp,&ne,&nfg,&neg,&kflag,&ibflag,&ipflag,&iqflag);
  if(ier != 9) 
    {
    if(LANG == 1) sprintf(cmess,
    "%s\nSchreibfehler oder fehlende Daten in Zeile 1 endeckt",cline);

    if(LANG == 2) sprintf(cmess,
    "%s\ntyping error or missing entries in line 1 detected",cline);

    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }
  }

if(ifnii1 == 1)              /* fuer Z88NI.TXT */
  {          
  ier= sscanf(cline,"%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",
  &ndim,&nkp,&ne,&nfg,&neg,&kflag,&ibflag,&ipflag,&iqflag,&niflag);
  if(ier != 10) 
    {
    if(LANG == 1) sprintf(cmess,
    "%s\nSchreibfehler oder fehlende Daten in Zeile 1 endeckt",cline);

    if(LANG == 2) sprintf(cmess,
    "%s\ntyping error or missing entries in line 1 detected",cline);

    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }
  }

/*---------------------------------------------------------------------
* ndim ?
*--------------------------------------------------------------------*/
if(!(ndim == 3 || ndim == 2))
  {
  if(LANG == 1) sprintf(cmess,
"%s\nDimension der Struktur nicht 2 oder 3 ! \
1.Wert in Zeile 1 ueberpruefen",cline);

  if(LANG == 2) sprintf(cmess,
"%s\ndimension of structure not 2 or 3 ! \
check 1st entry in line 1",cline);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

/*---------------------------------------------------------------------
* nkp ?
*--------------------------------------------------------------------*/
if(nkp <= 0)
  {
  if(LANG == 1) sprintf(cmess,
  "%s\nAnzahl Knoten nicht > 0 ! 2.Wert in Zeile 1 ueberpruefen",cline);

  if(LANG == 2) sprintf(cmess,
  "%s\nnumber of nodes not > 0 ! check 2nd entry in line 1",cline);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

if(nkp > MAXK)
  {
  if(LANG == 1) sprintf(cmess,
"%s\nAnzahl Knoten groesser als %ld in Z88.DYN\n\
2.Wert in Zeile 1 ueberpruefen oder MAXK in Z88.DYN erhoehen",cline,MAXK);

  if(LANG == 2) sprintf(cmess,
"%s\nnumber of nodes greater than %ld in Z88.DYN\n\
check 2nd entry in line 1 or increase MAXK in Z88.DYN",cline,MAXK);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

/*---------------------------------------------------------------------
* ne ?
*--------------------------------------------------------------------*/
if(ne <= 0)
  {
  if(LANG == 1) sprintf(cmess,
  "%s\nAnzahl Elemente nicht > 0 ! 3.Wert in Zeile 1 ueberpruefen",cline);

  if(LANG == 2) sprintf(cmess,
  "%s\nnumber of elements not > 0 ! check 3rd entry in line 1",cline);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

if(ne > MAXE)
  {
  if(LANG == 1) sprintf(cmess,
"%s\nAnzahl Elemente groesser als %ld in Z88.DYN\n\
3.Wert in Zeile 1 ueberpruefen oder MAXE in Z88.DYN erhoehen",cline,MAXE);

  if(LANG == 2) sprintf(cmess,
"%s\nnumber of elements greater than %ld in Z88.DYN\n\
check 3rd entry in line 1 or increase MAXE in Z88.DYN",cline,MAXE);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

/*---------------------------------------------------------------------
* nfg ?
*--------------------------------------------------------------------*/
if(ndim == 2)
  {
  if(nfg < 2*nkp  && ipflag == 0)
    {
    if(LANG == 1) sprintf(cmess,
"%s\nAnzahl Freiheitsgrade nicht groesser als min. 2*Knotenanzahl\n\
4.Wert in Zeile 1 ueberpruefen",cline);

    if(LANG == 2) sprintf(cmess,
"%s\nnumber of DOF not greater than at least 2*number of nodes\n\
check 4th entry in line 1",cline);

    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }

  if(nfg < 3*nkp && ipflag != 0)
    {
    if(LANG == 1) sprintf(cmess,
"%s\nAnzahl Freiheitsgrade nicht groesser als min. 3*Knotenanzahl\n\
4.Wert in Zeile 1 ueberpruefen",cline);

    if(LANG == 2) sprintf(cmess,
"%s\nnumber of DOF not greater than at least 3*number of nodes\n\
check 4th entry in line 1",cline);
    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    } 

 }

if(ndim == 3)
  {
  if(nfg < 3*nkp)
    {
    if(LANG == 1) sprintf(cmess,
"%s\nAnzahl Freiheitsgrade nicht groesser als min. 3*Knotenanzahl\n\
4.Wert in Zeile 1 ueberpruefen",cline);

    if(LANG == 2) sprintf(cmess,
"%s\nnumber of DOF not greater than at least 3*number of nodes\n\
check 4th entry in line 1",cline);
    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }
  }

if(nfg > MAXNFG)
  {
  if(LANG == 1) sprintf(cmess,
"%s\nAnzahl Freiheitsgrade groesser als %ld in Z88.DYN\n\
4.Wert in Zeile 1 ueberpruefen oder MAXNFG in Z88.DYN erhoehen",cline,MAXNFG);

  if(LANG == 2) sprintf(cmess,
"%s\nnumber of DOF greater than %ld in Z88.DYN\n\
check 4th entry in line 1 or increase MAXNFG in Z88.DYN",cline,MAXNFG);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

/*---------------------------------------------------------------------
* neg ?
*--------------------------------------------------------------------*/
if(neg < 1)
  {
  if(LANG == 1) sprintf(cmess,"%s\nAnzahl E-Gesetze < 1\n\
5.Wert in Zeile 1 ueberpruefen",cline);

  if(LANG == 2) sprintf(cmess,"%s\nnumber of mat info lines < 1\n\
check 5th entry in line 1",cline);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

if(neg > MAXNEG)
  {
  if(LANG == 1) sprintf(cmess,
"%s\nAnzahl E-Gesetze groesser als %ld in Z88.DYN\n\
5.Wert in Zeile 1 ueberpruefen oder MAXNEG in Z88.DYN erhoehen",cline,MAXNEG);

  if(LANG == 2) sprintf(cmess,
"%s\nnumber of mat info lines greater than %ld in Z88.DYN\n\
check 5th entry in line 1 or increase MAXNEG in Z88.DYN",cline,MAXNEG);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

/*---------------------------------------------------------------------
* kflag ?
*--------------------------------------------------------------------*/
if(!(kflag == 0 || kflag == 1))
  {
  if(LANG == 1) sprintf(cmess,"%s\nKoordinatenflag nicht 0 oder 1\n\
6.Wert in Zeile 1 ueberpruefen",cline);

  if(LANG == 2) sprintf(cmess,"%s\ncoordinate flag not 0 or 1\n\
check 6th entry in line 1",cline);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

/*---------------------------------------------------------------------
* ibflag ?
*--------------------------------------------------------------------*/
if(!(ibflag == 0 || ibflag == 1))
  {
  if(LANG == 1) sprintf(cmess,"%s\nBalkenflag nicht 0 oder 1\n\
7.Wert in Zeile 1 ueberpruefen",cline);

  if(LANG == 2) sprintf(cmess,"%s\nbeam flag not 0 or 1\n\
check 7th entry in line 1",cline);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

/*---------------------------------------------------------------------
* ipflag ?
*--------------------------------------------------------------------*/
if(!(ipflag == 0  || ipflag == 1 || ipflag == 2))
  {
  if(LANG == 1) sprintf(cmess,"%s\nPlattenflag nicht 0,1 oder 2\n\
8.Wert in Zeile 1 ueberpruefen",cline);

  if(LANG == 2) sprintf(cmess,"%s\nplate flag neither 0, 1 nor 2\n\
check 8th entry in line 1",cline);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

if(ipflag != 0 && ibflag == 1)
  {
  if(LANG == 1) sprintf(cmess,
"%s\nPlattenflag und Balkenflag gleichzeitig gesetzt\n\
in momentaner Z88- Version nicht zulaessig\n\
7.und 8.Wert in Zeile 1 ueberpruefen",cline);

  if(LANG == 2) sprintf(cmess,"%s\nboth plate flag and beam flag set\n\
not allowed in this Z88 release\n\
check 7th and 8th entry in line",cline);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

/*---------------------------------------------------------------------
* iqflag ?
*--------------------------------------------------------------------*/
if(!(iqflag == 0 || iqflag == 1))
  {
  if(LANG == 1) sprintf(cmess,"%s\nFlaechenlastflag nicht 0 oder 1\n\
9.Wert in Zeile 1 ueberpruefen",cline);

  if(LANG == 2) sprintf(cmess,"%s\nplate flag neither 0 nor 1\n\
check 9th entry in line 1",cline);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

if(ipflag == 1 && iqflag == 1)
  {
  if(LANG == 1) sprintf(cmess,
"%s\n>>> Hinweis: IPFLAG = 1 und IQFLAG = 1\n\
>>> Ist fuer Platten 18,19 und 20 zulaessig\n\
>>> Dann Plattendruck in Datei Z88I5.TXT geben",cline);

  if(LANG == 2) sprintf(cmess,
"%s\n>>> Attention: IPFLAG = 1 and IQFLAG = 1\n\
>>> However, is allowed for plate elements No.18,19 & 20\n\
>>> But then enter surface load into file Z88I5.TXT",cline);

  MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
  return(2);
  }

/*---------------------------------------------------------------------
* niflag ?
*--------------------------------------------------------------------*/
if(ifnii1 ==1)
  {
  if(!(niflag == 0 || niflag == 1))
    {
    if(LANG == 1) sprintf(cmess,"%s\nFangradiusflag nicht 0 oder 1\n\
9.Wert in Zeile 1 ueberpruefen",cline);

    if(LANG == 2) sprintf(cmess,"%s\ntrap radius flag not 0 or 1\n\
check 9th entry in line 1",cline);

    MessageBox(NULL, cmess, chead, MB_OK | MB_ICONHAND);
    return(2);
    }
  }

/***********************************************************************
* Ende grp1: keine Fehler
***********************************************************************/
return(0);
}

/***********************************************************************
* Function erif88
***********************************************************************/
void erif88(HWND hWnd,long izeile)
{
extern FR_INT4 LANG;

char cmess[1024];

if(LANG == 1) sprintf(cmess,
"Versuchte Zeile %ld zu lesen, aber Fileende wurde gefunden\n\
Fileaufbau falsch, File zu kurz oder leer\n\
evtl. fehlt ein CR/LF am Ende der letzten Zeile",izeile);

if(LANG == 2) sprintf(cmess,
"Tried to read line %ld, but end of file was found !\n\
file structure wrong, file too short or empty\n\
perhaps a CR/LF at end of very last line is missing ?",izeile);

MessageBox(NULL, cmess, "Z88V", MB_OK | MB_ICONHAND);

return;
}

