/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the UNIX OS.
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
* Z88 should compile and run under any UNIX OS and Motif 2.0.
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
* wlog88v gibt Log-Datei-Meldungen aus (1 FR_INT4, 1 int)
* 22.3.2002 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88v.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88v.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
*  hier beginnt Function wlog88v
***********************************************************************/
int wlog88v(FR_INT4 i,int iatx)
{
extern FILE *fwlo;

extern FR_INT4 LANG;

switch(iatx)
  {
  case LOG_BZ88V:
    if(LANG == 1) fprintf(fwlo,"Start Z88V Version 10");
    if(LANG == 2) fprintf(fwlo,"start Z88V version 10");
    fflush(fwlo);
    break;
  case LOG_OPENZ88DYN:
    if(LANG == 1) fprintf(fwlo,"\nOeffnen der Datei Z88.DYN");
    if(LANG == 2) fprintf(fwlo,"\nopening file Z88.DYN");
    fflush(fwlo);
    break;
  case LOG_NODYN:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88.DYN nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88.DYN ..stop ###");
    fflush(fwlo);
    break;
  case LOG_WRONGDYN:
    if(LANG == 1)
      fprintf(fwlo,"\n### File Z88.DYN ist nicht korrekt ..Stop ###");
    if(LANG == 2)
      fprintf(fwlo,"\n### file Z88.DYN is not correct ..stop ###");
    fflush(fwlo);
    break;
  case LOG_MAXK:
    fprintf(fwlo,"\nMAXK   = %ld",i);
    fflush(fwlo);
    break;
  case LOG_MAXE:
    fprintf(fwlo,"\nMAXE   = %ld",i);
    fflush(fwlo);
    break;
  case LOG_MAXNFG:
    fprintf(fwlo,"\nMAXNFG = %ld",i);
    fflush(fwlo);
    break;
  case LOG_MAXNEG:
    fprintf(fwlo,"\nMAXNEG = %ld",i);
    fflush(fwlo);
    break;
  case LOG_OKDYN:
    if(LANG == 1)
      fprintf(fwlo,"\nDatei Z88.DYN gelesen..scheint formal o.k. zu sein");
    if(LANG == 2)
      fprintf(fwlo,"\nfile Z88.DYN read..seems to be o.k.");
    fflush(fwlo);
    break;
  case LOG_ALLOCMEMY:
    if(LANG == 1) fprintf(fwlo,"\nDynamisches Memory anlegen:");
    if(LANG == 2) fprintf(fwlo,"\nallocating dynamic memory:");
    fflush(fwlo);
    break;
  case LOG_ARRAYNOTOK:
    if(LANG == 1)
    fprintf(fwlo,"\n### Memory Kennung %ld nicht o.k. ..Stop ###",i);
    if(LANG == 2)
    fprintf(fwlo,"\n### memory id %ld is not o.k. ..stop ###",i);
    fflush(fwlo);
    break;
  case LOG_ARRAYOK:
    if(LANG == 1) fprintf(fwlo,"\nMemory Kennung %ld angelegt",i);
    if(LANG == 2) fprintf(fwlo,"\nmemory id %ld allocated",i);
    fflush(fwlo);
    break;
  case LOG_SUMMEMY:
    if(LANG == 1)
    fprintf(fwlo,"\nDynamisches Memory vollstaendig angefordert: %ld Bytes",i);
    if(LANG == 2)
    fprintf(fwlo,"\ndynamic memory totally allocated: %ld Bytes",i);
    fflush(fwlo);
    break;
  case LOG_EXITDYN88V:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Speichereinheit DYN88V");
    if(LANG == 2) fprintf(fwlo,"\nleaving storage function DYN88V");
    fflush(fwlo);
    break;
  }
return(0);
}
