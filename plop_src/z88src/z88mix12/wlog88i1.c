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
* V10.0 December 12, 2001
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
* wlog88i1 gibt Log-Datei-Meldungen aus (1 FR_INT4, 1 int)
* 29.9.02 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88i.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88i.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
*  hier beginnt Function wlog88i1
***********************************************************************/
int wlog88i1(FR_INT4 i,int iatx)
{
extern FILE *fl1;
extern FR_INT4 LANG;

switch(iatx)
  {
  case LOG_BZ88I1:
    if(LANG == 1) fprintf(fl1,"Start Z88I1 Version 10");
    if(LANG == 2) fprintf(fl1,"start Z88I1 version 10");
    fflush(fl1);
  break;

  case LOG_OPENZ88DYN:
    if(LANG == 1) fprintf(fl1,"\nOeffnen der Datei Z88.DYN");
    if(LANG == 2) fprintf(fl1,"\nopening file Z88.DYN");
    fflush(fl1);
  break;

  case LOG_NODYN:
    if(LANG == 1)
    fprintf(fl1,"\n### kann Z88.DYN nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl1,"\n### cannot open Z88.DYN ..stop ###");
    fflush(fl1);
  break;

  case LOG_WRONGDYN:
    if(LANG == 1)
    fprintf(fl1,"\n### File Z88.DYN ist nicht korrekt ..Stop ###");
    if(LANG == 2)
    fprintf(fl1,"\n### file Z88.DYN is not correct ..stop ###");
    fflush(fl1);
  break;

  case LOG_MAXSOR:
    fprintf(fl1,"\nMAXSOR  = %ld",i);
    fflush(fl1);
  break;

  case LOG_MAXPUF:
    fprintf(fl1,"\nMAXPUF  = %ld",i);
    fflush(fl1);
  break;

  case LOG_MAXKOI:
    fprintf(fl1,"\nMAXKOI  = %ld",i);
    fflush(fl1);
  break;

  case LOG_MAXGS:
    fprintf(fl1,"\nMAXGS   = %ld",i);
    fflush(fl1);
  break;

  case LOG_MAXK:
    fprintf(fl1,"\nMAXK    = %ld",i);
    fflush(fl1);
  break;

  case LOG_MAXE:
    fprintf(fl1,"\nMAXE    = %ld",i);
    fflush(fl1);
  break;

  case LOG_MAXNFG:
    fprintf(fl1,"\nMAXNFG  = %ld",i);
    fflush(fl1);
  break;

  case LOG_MAXNEG:
    fprintf(fl1,"\nMAXNEG  = %ld",i);
    fflush(fl1);
  break;

 case LOG_OKDYN:
    if(LANG == 1)
    fprintf(fl1,"\nDatei Z88.DYN gelesen..scheint formal o.k. zu sein");
    if(LANG == 2)
    fprintf(fl1,"\nfile Z88.DYN read ..seems to be o.k.");
    fflush(fl1);
  break;

  case LOG_ALLOCMEMY:
    if(LANG == 1) fprintf(fl1,"\nDynamisches Memory anlegen:");
    if(LANG == 2) fprintf(fl1,"\nallocating dynamic memory:");
    fflush(fl1);
  break;

  case LOG_ARRAYNOTOK:
    if(LANG == 1)
    fprintf(fl1,"\n### Memory Kennung %ld nicht o.k. ..Stop ###",i);
    if(LANG == 2)
    fprintf(fl1,"\n### memory id %ld is not o.k. ..stop ###",i);
    fflush(fl1);
  break;

  case LOG_ARRAYOK:
    if(LANG == 1) fprintf(fl1,"\nMemory Kennung %ld angelegt",i);
    if(LANG == 2) fprintf(fl1,"\nmemory id %ld allocated",i);
    fflush(fl1);
  break;

  case LOG_SUMMEMY:
    if(LANG == 1)
    fprintf(fl1,"\nDynamisches Memory vollstaendig angefordert: %ld Bytes",i);
    if(LANG == 2)
    fprintf(fl1,"\ndynamic memory totally allocated: %ld Bytes",i);
    fflush(fl1);
  break;

  case LOG_EXITDYN88I1:
    if(LANG == 1) fprintf(fl1,"\nVerlassen Speichereinheit DYN88I1");
    if(LANG == 2) fprintf(fl1,"\nleaving storage function DYN88I1");
    fflush(fl1);
  break;

  case LOG_BRI188:
    if(LANG == 1)
    fprintf(fl1,"\nStart Leseeinheit RI188I\nEinlesen von Z88I1.TXT");
    if(LANG == 2)
    fprintf(fl1,"\nstart reading function RI188I\nreading Z88I1.TXT");
    fflush(fl1);
  break;

  case LOG_NOI1:
    if(LANG == 1)
    fprintf(fl1,"\n### kann Z88I1.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl1,"\n### cannot open Z88I1.TXT ..stop ###");
    fflush(fl1);
  break;

  case LOG_WRONGDIM:
    if(LANG == 1)
    fprintf(fl1,"\n### Dimension %ld falsch ..Stop ###",i);
    if(LANG == 2)
    fprintf(fl1,"\n### dimension %ld wrong ..stop ###",i);
    fflush(fl1);
  break;

  case LOG_EXMAXK:
    if(LANG == 1)
      {
      fprintf(fl1,"\n### Nur %ld Knoten in Z88.DYN definiert ..Stop ###",i);
      fprintf(fl1,"\n### Abhilfe: MAXK in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fl1,"\n### only %ld nodes in Z88.DYN defined ..stop ###",i);
      fprintf(fl1,"\n### recover: increase MAXK in Z88.DYN ###");
      }
    fflush(fl1);
  break;

  case LOG_EXMAXE:
    if(LANG == 1)
      {
      fprintf(fl1,"\n### Nur %ld Elemente in Z88.DYN definiert ..Stop ###",i);
      fprintf(fl1,"\n### Abhilfe: MAXE in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fl1,"\n### only %ld elements in Z88.DYN defined ..stop ###",i);
      fprintf(fl1,"\n### recover: increase MAXE in Z88.DYN ###");
      }
    fflush(fl1);
  break;

  case LOG_EXMAXKOI:
    if(LANG == 1)
      {
      fprintf(fl1,"\n### Nur MAXKOI=%ld in Z88.DYN definiert ..Stop ###",i);
      fprintf(fl1,"\n### Abhilfe: MAXKOI in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fl1,"\n### only MAXKOI=%ld in Z88.DYN defined ..stop ###",i);
      fprintf(fl1,"\n### recover: increase MAXKOI in Z88.DYN ###");
      }
    fflush(fl1);
  break;

  case LOG_EXMAXNFG:
    if(LANG == 1)
      {
      fprintf(fl1,"\n### Nur %ld FG in Z88.DYN definiert ..Stop ###",i);
      fprintf(fl1,"\n### Abhilfe: MAXNFG in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fl1,"\n### only %ld DOF in Z88.DYN defined ..stop ###",i);
      fprintf(fl1,"\n### recover: increase MAXNFG in Z88.DYN ###");
      }
    fflush(fl1);
  break;

  case LOG_EXMAXNEG:
    if(LANG == 1)
      {
      fprintf(fl1,"\n### Nur %ld E-Gesetze in Z88.DYN definiert ..Stop ###",i);
      fprintf(fl1,"\n### Abhilfe: MAXNEG in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fl1,"\n### only %ld mat lines in Z88.DYN defined ..stop ###",i);
      fprintf(fl1,"\n### recover: increase MAXNEG in Z88.DYN ###");
      }
    fflush(fl1);
  break;

  case LOG_EXMAXSOR:
    if(LANG == 1)
      {
      fprintf(fl1,"\n### Abbruch bei Element %ld ..Stop ###",i);
      fprintf(fl1,"\n### Sortierstructure IJ zu klein ..Stop ###");
      fprintf(fl1,"\n### Abhilfe: MAXSOR in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fl1,"\n### exiting at element %ld ..Stop ###",i);
      fprintf(fl1,"\n### sorting structure IJ exhausted ..stop ###");
      fprintf(fl1,"\n### recover: increase MAXSOR in Z88.DYN   ###");
      }
    fflush(fl1);
  break;

  case LOG_WROKFLAG:
    if(LANG == 1) fprintf(fl1,"\n### KFLAG %ld falsch ..Stop ###",i);
    if(LANG == 2) fprintf(fl1,"\n### KFLAG %ld wrong ..stop ###",i);
    fflush(fl1);
  break;

  case LOG_KOOR:
    if(LANG == 1) fprintf(fl1,"\nEinlesen der Koordinaten");
    if(LANG == 2) fprintf(fl1,"\nreading coordinates");
    fflush(fl1);
  break;

  case LOG_KOIN:
    if(LANG == 1) fprintf(fl1,"\nEinlesen der Koinzidenz");
    if(LANG == 2) fprintf(fl1,"\nreading element information");
    fflush(fl1);
  break;

  case LOG_EGES:
    if(LANG == 1)
    fprintf(fl1,"\nEinlesen der Elastizitaetsgesetze");
    if(LANG == 2)
    fprintf(fl1,"\nreading material informations");
    fflush(fl1);
  break;

  case LOG_EXITRI188:
    if(LANG == 1)
    fprintf(fl1,"\nZ88I1.TXT eingelesen, Verlassen Leseeinheit RI188I");
    if(LANG == 2)
    fprintf(fl1,"\nZ88I1.TXT read, leaving reading function RI188I");
    fflush(fl1);
  break;

  case LOG_BWRIA88F:
    if(LANG == 1) fprintf(fl1,"\nStart Schreibeinheit WRIA88I");
    if(LANG == 2) fprintf(fl1,"\nstart writing function WRIA88I");
    fflush(fl1);
  break;

  case LOG_NO1Y:
    if(LANG == 1)
    fprintf(fl1,"\n### kann Z88O1.BNY nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl1,"\n### cannot open Z88O1.BNY ..stop ###");
    fflush(fl1);
  break;

  case LOG_NO4Y:
    if(LANG == 1)
    fprintf(fl1,"\n### kann Z88O4.BNY nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl1,"\n### cannot open Z88O4.BNY ..stop ###");
    fflush(fl1);
  break;

  case LOG_NOO0:
    if(LANG == 1)
    fprintf(fl1,"\n### kann Z88O0.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl1,"\n### cannot open Z88O0.TXT ..stop ###");
    fflush(fl1);
  break;

  case LOG_NOO1:
    if(LANG == 1)
    fprintf(fl1,"\n### kann Z88O1.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl1,"\n### cannot open Z88O1.TXT ..stop ###");
    fflush(fl1);
  break;

  case LOG_WRI1Y:
    if(LANG == 1) fprintf(fl1,"\nBeschreiben von Z88O1.BNY");
    if(LANG == 2) fprintf(fl1,"\nwriting Z88O1.BNY");
    fflush(fl1);
  break;

  case LOG_WRI4Y:
    if(LANG == 1) fprintf(fl1,"\nBeschreiben von Z88O4.BNY");
    if(LANG == 2) fprintf(fl1,"\nwriting Z88O4.BNY");
    fflush(fl1);
  break;

  case LOG_WRI4YOK:
    if(LANG == 1) fprintf(fl1,"\nZ88O4.BNY fertig geschrieben");
    if(LANG == 2) fprintf(fl1,"\nZ88O4.BNY written");
    fflush(fl1);
  break;

  case LOG_WRIO0:
    if(LANG == 1) fprintf(fl1,"\nBeschreiben von Z88O0.TXT");
    if(LANG == 2) fprintf(fl1,"\nwriting Z88O0.TXT");
    fflush(fl1);
  break;

  case LOG_WRIO1:
    if(LANG == 1) fprintf(fl1,"\nBeschreiben von Z88O1.TXT");
    if(LANG == 2) fprintf(fl1,"\nwriting Z88O1.TXT");
    fflush(fl1);
  break;

  case LOG_GSERF:
    if(LANG == 1) fprintf(fl1,"\nVektor GS braucht %ld Elemente",i);
    if(LANG == 2) fprintf(fl1,"\nvector GS needs %ld Elemente",i);
    fflush(fl1);
  break;

  case LOG_KOIERF:
    if(LANG == 1) fprintf(fl1,"\nVektor KOI braucht %ld Elemente",i);
    if(LANG == 2) fprintf(fl1,"\nvector KOI needs %ld Elemente",i);
    fflush(fl1);
  break;

  case LOG_EXITWRIA88F:
    if(LANG == 1) fprintf(fl1,"\nVerlassen Schreibeinheit WRIA88I");
    if(LANG == 2) fprintf(fl1,"\nleaving writing function WRIA88I");
    fflush(fl1);
  break;

  case LOG_Z88A:
    if(LANG == 1) fprintf(fl1,"\nStart Z88AI : Pass 1 von Z88I1");
    if(LANG == 2) fprintf(fl1,"\nstart Z88AI : pass 1 of Z88I1");
    fflush(fl1);
  break;

  case LOG_FORMA:
    if(LANG == 1) fprintf(fl1,"\n*** Formatieren ***");
    if(LANG == 2) fprintf(fl1,"\n*** formatting ***");
    fflush(fl1);
  break;

  case LOG_WROETYP:
   if(LANG == 1)
    fprintf(fl1,"\n### Falschen Elementtyp %ld entdeckt ..Stop ###",i);
    if(LANG == 2)
    fprintf(fl1,"\n### wrong element type %ld detected ..stop ###",i);
    fflush(fl1);
  break;

  case LOG_EXITZ88A:
    if(LANG == 1) fprintf(fl1,"\nVerlassen Z88AI, Pass 1 erledigt");
    if(LANG == 2) fprintf(fl1,"\nleaving Z88AI, pass 1 done");
    fflush(fl1);
  break;


  }
return(0);
}
