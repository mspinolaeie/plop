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
* wlog88d gibt Log-Datei-Meldungen aus (1 FR_INT4, 1 int)
* 7.7.2003 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX  
#include <z88d.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88d.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
*  hier beginnt Function wlog88d
***********************************************************************/
int wlog88d(FR_INT4 i,int iatx)
{
extern FILE *fwlo;
extern FR_INT4 LANG;

switch(iatx)
  {
  case LOG_BZ88D:
    if(LANG == 1) fprintf(fwlo,"Start Z88D Version 10.0A");
    if(LANG == 2) fprintf(fwlo,"start Z88D version 10.0A");
    fflush(fwlo);
  break;

  case LOG_OPENZ88DYN:
    if(LANG == 1) fprintf(fwlo,"\nOeffnen der Datei Z88.DYN");
    if(LANG == 2) fprintf(fwlo,"\nopening file Z88.DYN");
    fflush(fwlo);
  break;

  case LOG_NODYN:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88.DYN nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88.DYN ..stop ###");
    fflush(fwlo);
  break;

  case LOG_WRONGDYN:
    if(LANG == 1)
    fprintf(fwlo,"\n### File Z88.DYN ist nicht korrekt ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### file Z88.DYN is not correct ..stop ###");
    fflush(fwlo);
  break;

  case LOG_MAXKOI:
    fprintf(fwlo,"\nMAXKOI = %ld",i);
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
    fprintf(fwlo,"\nfile Z88.DYN read .. seems to be o.k.");
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

  case LOG_EXITDYN88D:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Speichereinheit DYN88D");
    if(LANG == 2) fprintf(fwlo,"\nleaving storage function DYN88D");
    fflush(fwlo);
  break;

  case LOG_NOO3:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88O3.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88O3.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOO5:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88O5.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88O5.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOO8:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88O8.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88O8.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOI3:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88I3.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88I3.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_REAI3:
    if(LANG == 1) fprintf(fwlo,"\nLesen Parameterfile Z88I3.TXT");
    if(LANG == 2) fprintf(fwlo,"\nreading stress flag file Z88I3.TXT");
    fflush(fwlo);
  break;

  case LOG_RIY88:
    if(LANG == 1) fprintf(fwlo,"\nStart Leseeinheit RIY88");
    if(LANG == 2) fprintf(fwlo,"\nstart reading function RIY88");
    fflush(fwlo);
  break;

  case LOG_REAO1Y:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen von Z88O1.BNY");
    if(LANG == 2) fprintf(fwlo,"\nreading Z88O1.BNY");
    fflush(fwlo);
  break;

  case LOG_REAO3Y:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen von Z88O3.BNY");
    if(LANG == 2) fprintf(fwlo,"\nreading Z88O3.BNY");
    fflush(fwlo);
  break;

  case LOG_RIY88OK:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Leseeinheit RIY88");
    if(LANG == 2) fprintf(fwlo,"\nleaving reading function RIY88");
    fflush(fwlo);
  break;

  case LOG_SPANNU:
    if(LANG == 1) fprintf(fwlo,"\nSpannungen berechnen");
    if(LANG == 2) fprintf(fwlo,"\ncomputing stresses");
    fflush(fwlo);
  break;

  case LOG_EXITZ88D:
    if(LANG == 1) fprintf(fwlo,"\nEnde Z88D");
    if(LANG == 2) fprintf(fwlo,"\nZ88D done");
    fflush(fwlo);
  break;

  }
return(0);
}
