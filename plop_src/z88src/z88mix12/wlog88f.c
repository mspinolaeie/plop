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
* V12.0  February 14, 2005
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
* wlog88f gibt Log-Datei-Meldungen aus (1 FR_INT4, 1 int)
* 29.9.2005 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88f.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88f.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
*  hier beginnt Function wlog88f
***********************************************************************/
int wlog88f(FR_INT4 i,int iatx)
{
extern FILE *fwlo;
extern FR_INT4 LANG;

switch(iatx)
  {
  case LOG_BZ88:
    if(LANG == 1) fprintf(fwlo,"Start Z88F Version 12");
    if(LANG == 2) fprintf(fwlo,"start Z88F version 12");
    fflush(fwlo);
  break;

  case LOG_CFLAGC:
    if(LANG == 1)
    fprintf(fwlo,"\nSteuerflag CFLAG fuer Z88F ist -C, ICFLAG = %ld",i);
    if(LANG == 2)
    fprintf(fwlo,"\nflag CFLAG for Z88F is -C, ICFLAG = %ld",i);
    fflush(fwlo);
  break;

  case LOG_CFLAGT:
    if(LANG == 1)
    fprintf(fwlo,"\nSteuerflag CFLAG fuer Z88F ist -T, ICFLAG = %ld",i);
    if(LANG == 2)
    fprintf(fwlo,"\nflag CFLAG for Z88F is -T, ICFLAG = %ld",i);
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

  case LOG_MAXGS:
    fprintf(fwlo,"\nMAXGS  = %ld",i);
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

  case LOG_MAXESM:
    fprintf(fwlo,"\nMAXESM = %ld",i);
    fflush(fwlo);
  break;
 
 case LOG_OKDYN:
    if(LANG == 1)
    fprintf(fwlo,"\nDatei Z88.DYN gelesen..scheint formal o.k. zu sein");
    if(LANG == 2)
    fprintf(fwlo,"\nfile Z88.DYN read ..seems to be o.k.");
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
    fprintf(fwlo,"\nDynamisches Memory vollstaendig angefordert: %ld MB",i);
    if(LANG == 2)
    fprintf(fwlo,"\ndynamic memory totally allocated: %ld MB",i);
    fflush(fwlo);
  break;

  case LOG_EXITDYN88F:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Speichereinheit DYN88F");
    if(LANG == 2) fprintf(fwlo,"\nleaving storage function DYN88F");
    fflush(fwlo);
  break;

  case LOG_BRI188:
    if(LANG == 1)
    fprintf(fwlo,"\nStart Leseeinheit RI188\nEinlesen von Z88I1.TXT");
    if(LANG == 2)
    fprintf(fwlo,"\nstart reading function RI188\nreading Z88I1.TXT");
    fflush(fwlo);
  break;

  case LOG_NOI1:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88I1.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88I1.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_WRONGDIM:
    if(LANG == 1)
    fprintf(fwlo,"\n### Dimension %ld falsch ..Stop ###",i);
    if(LANG == 2)
    fprintf(fwlo,"\n### dimension %ld wrong ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_EXMAXK:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Nur %ld Knoten in Z88.DYN definiert ..Stop ###",i);
      fprintf(fwlo,"\n### Abhilfe: MAXK in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### only %ld nodes in Z88.DYN defined ..stop ###",i);
      fprintf(fwlo,"\n### recover: increase MAXK in Z88.DYN ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXE:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Nur %ld Elemente in Z88.DYN definiert ..Stop ###",i);
      fprintf(fwlo,"\n### Abhilfe: MAXE in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### only %ld elements in Z88.DYN defined ..stop ###",i);
      fprintf(fwlo,"\n### recover: increase MAXE in Z88.DYN ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXNFG:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Nur %ld FG in Z88.DYN definiert ..Stop ###",i);
      fprintf(fwlo,"\n### Abhilfe: MAXNFG in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### only %ld DOF in Z88.DYN defined ..stop ###",i);
      fprintf(fwlo,"\n### recover: increase MAXNFG in Z88.DYN ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXNEG:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Nur %ld E-Gesetze in Z88.DYN definiert ..Stop ###",i);
      fprintf(fwlo,"\n### Abhilfe: MAXNEG in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### only %ld mat lines in Z88.DYN defined ..stop ###",i);
      fprintf(fwlo,"\n### recover: increase MAXNEG in Z88.DYN ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXPR:
    if(LANG == 1) fprintf(fwlo,
"\n### NKOI = %ld,.. ueberschreitet MAXPR ###\
\n### Lastvektor zu gross fuer Z88 ..Stop       ###\
\n### Abhilfe: MAXPR hoeher setzen in Z88.DYN ###",i);
    if(LANG == 2) fprintf(fwlo,
"\n### NKOI = %ld,.. exceeds MAXPR ###\
\n### load vektor too large ..stop ###\
\n### recover: increase MAXPR in Z88.DYN  ###",i);
    fflush(fwlo);
  break;

  case LOG_WROKFLAG:

    if(LANG == 1) fprintf(fwlo,"\n### KFLAG %ld falsch ..Stop ###",i);
    if(LANG == 2) fprintf(fwlo,"\n### KFLAG %ld wrong ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_KOOR:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen der Koordinaten");
    if(LANG == 2) fprintf(fwlo,"\nreading coordinates");
    fflush(fwlo);
  break;

  case LOG_KOIN:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen der Koinzidenz");
    if(LANG == 2) fprintf(fwlo,"\nreading element information");
    fflush(fwlo);
  break;

  case LOG_EGES:
    if(LANG == 1)
    fprintf(fwlo,"\nEinlesen der Elastizitaetsgesetze");
    if(LANG == 2)
    fprintf(fwlo,"\nreading material informations");
    fflush(fwlo);
  break;

  case LOG_EXITRI188:
    if(LANG == 1)
    fprintf(fwlo,"\nZ88I1.TXT eingelesen, Verlassen Leseeinheit RI188");
    if(LANG == 2)
    fprintf(fwlo,"\nZ88I1.TXT read, leaving reading function RI188");
    fflush(fwlo);
  break;

  case LOG_BWRIA88F:
    if(LANG == 1) fprintf(fwlo,"\nStart Schreibeinheit WRIA88F");
    if(LANG == 2) fprintf(fwlo,"\nstart writing function WRIA88F");
    fflush(fwlo);
  break;

  case LOG_NO1Y:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88O1.BNY nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88O1.BNY ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOO0:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88O0.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88O0.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOO1:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88O1.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88O1.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_WRI1Y:
    if(LANG == 1) fprintf(fwlo,"\nBeschreiben von Z88O1.BNY");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88O1.BNY");
    fflush(fwlo);
  break;

  case LOG_WRIO0:
    if(LANG == 1) fprintf(fwlo,"\nBeschreiben von Z88O0.TXT");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88O0.TXT");
    fflush(fwlo);
  break;

  case LOG_WRIO1:
    if(LANG == 1) fprintf(fwlo,"\nBeschreiben von Z88O1.TXT");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88O1.TXT");
    fflush(fwlo);
  break;

  case LOG_GSERF:
    if(LANG == 1) fprintf(fwlo,"\nVektor GS braucht %ld Elemente",i);
    if(LANG == 2) fprintf(fwlo,"\nvector GS needs %ld Elemente",i);
    fflush(fwlo);
  break;

  case LOG_KOIERF:
    if(LANG == 1) fprintf(fwlo,"\nVektor KOI braucht %ld Elemente",i);
    if(LANG == 2) fprintf(fwlo,"\nvector KOI needs %ld Elemente",i);
    fflush(fwlo);
  break;

  case LOG_EXITWRIA88F:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Schreibeinheit WRIA88F");
    if(LANG == 2) fprintf(fwlo,"\nleaving writing function WRIA88F");
    fflush(fwlo);
  break;

  case LOG_Z88A:
    if(LANG == 1) fprintf(fwlo,"\nStart Z88A : Pass 1 von Z88F");
    if(LANG == 2) fprintf(fwlo,"\nstart Z88A : pass 1 of Z88F");
    fflush(fwlo);
  break;

  case LOG_FORMA:
    if(LANG == 1) fprintf(fwlo,"\n*** Formatieren ***");
    if(LANG == 2) fprintf(fwlo,"\n*** formatting ***");
    fflush(fwlo);
  break;

  case LOG_WROETYP:
   if(LANG == 1)
    fprintf(fwlo,"\n### Falschen Elementtyp %ld entdeckt ..Stop ###",i);
    if(LANG == 2)
    fprintf(fwlo,"\n### wrong element type %ld detected ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_EXITZ88A:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Z88A, Pass 1 erledigt");
    if(LANG == 2) fprintf(fwlo,"\nleaving Z88A, pass 1 done");
    fflush(fwlo);
  break;

  case LOG_Z88B:
    if(LANG == 1) fprintf(fwlo,"\nStart Z88B : Pass 2 von Z88F");
    if(LANG == 2) fprintf(fwlo,"\nstart Z88B : pass 2 of Z88F");
    fflush(fwlo);
  break;

  case LOG_EXGS:
    if(LANG == 1) fprintf(fwlo,
"\n### IP = %ld,.. ueberschreitet MAXGS ###\
\n### Struktur zu gross fuer Z88 ..Stop       ###\
\n### Abhilfe: MAXGS hoeher setzen in Z88.DYN ###",i);
    if(LANG == 2) fprintf(fwlo,
"\n### IP = %ld,.. exceeds MAXGS ###\
\n### system of equations too large ..stop ###\
\n### recover: increase MAXGS in Z88.DYN   ###",i);
    fflush(fwlo);
  break;

  case LOG_EXKOI:
    if(LANG == 1) fprintf(fwlo,
"\n### NKOI = %ld,.. ueberschreitet MAXKOI ###\
\n### Struktur zu gross fuer Z88 ..Stop       ###\
\n### Abhilfe: MAXGS hoeher setzen in Z88.DYN ###",i);
    if(LANG == 2) fprintf(fwlo,
"\n### NKOI = %ld,.. exceeds MAXKOI ###\
\n### system of equations too large ..stop ###\
\n### recover: increase MAXKOI in Z88.DYN  ###",i);
    fflush(fwlo);
  break;

  case LOG_COMPI:
    if(LANG == 1) fprintf(fwlo,"\n*** Compilation ***");
    if(LANG == 2) fprintf(fwlo,"\n*** compilation ***");
    fflush(fwlo);
  break;

  case LOG_EXITZ88B:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Z88B, Pass 2 erledigt");
    if(LANG == 2) fprintf(fwlo,"\nleaving Z88B, pass 2 done");
    fflush(fwlo);
  break;

  case LOG_Z88CC:
    if(LANG == 1) fprintf(fwlo,"\nStart Z88CC : Pass 3 von Z88F");
    if(LANG == 2) fprintf(fwlo,"\nstart Z88CC : pass 3 of Z88F");
    fflush(fwlo);
  break;

  case LOG_NOI2:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88I2.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88I2.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NO3Y:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88O3.BNY nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88O3.BNY ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOO2:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88O2.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88O2.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_REAI2:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen Z88I2.TXT");
    if(LANG == 2) fprintf(fwlo,"\nreading Z88I2.TXT");
    fflush(fwlo);
  break;

  case LOG_ERBPA:
    if(LANG == 1)
    fprintf(fwlo,"\nEinarbeiten der Randbedingungen Pass %ld",i);
    if(LANG == 2)
    fprintf(fwlo,"\nincorporating constraints pass %ld",i);
    fflush(fwlo);
  break;

  case LOG_SCAL88:
    if(LANG == 1) fprintf(fwlo,"\nStart SCAL88");
    if(LANG == 2) fprintf(fwlo,"\nstart SCAL88");
    fflush(fwlo);
  break;

  case LOG_CHOY88:
    if(LANG == 1) fprintf(fwlo,"\nStart CHOY88");
    if(LANG == 2) fprintf(fwlo,"\nstart CHOY88");
    fflush(fwlo);
  break;

  case LOG_WRI3Y:
    if(LANG == 1) fprintf(fwlo,"\nBeschreiben von Z88O3.BNY");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88O3.BNY");
    fflush(fwlo);
  break;

  case LOG_WRIO2:
    if(LANG == 1) fprintf(fwlo,"\nBeschreiben von Z88O2.TXT");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88O2.TXT");
    fflush(fwlo);
  break;

  case LOG_EXITZ88CC:
    if(LANG == 1)
    fprintf(fwlo,"\nVerlassen Z88CC, Pass 3 erledigt: Ende Z88F");
    if(LANG == 2)
    fprintf(fwlo,"\nleaving Z88CC, pass 3 done: Z88F done");
    fflush(fwlo);
  break;

  case LOG_VORW:
    if(LANG == 1) fprintf(fwlo,"\nVorwaertseinsetzen");
    if(LANG == 1) fprintf(fwlo,"\nforward-substitution");
    fflush(fwlo);
  break;

  case LOG_RUECKW:
    if(LANG == 1) fprintf(fwlo,"\nRueckwaertseinsetzen");
    if(LANG == 1) fprintf(fwlo,"\nback-substitution");
    fflush(fwlo);
  break;

  case LOG_DIAGNULL:
    if(LANG == 1) 
      {
      fprintf(fwlo,"\n### Diagonalelement %ld Null oder negativ ..Stop ###",i);
      fprintf(fwlo,
      "\n### liegt oft an fehlenden oder falschen Randbedingungen ###");
      fprintf(fwlo,
      "\n### Abhilfe: Randbedingungen pruefen (statisch unterbestimmt ?) ###");
      }    
    if(LANG == 2) 
      {
      fprintf(fwlo,"\n### diagonal element %ld zero or negative ..stop ###",i);
      fprintf(fwlo,"\n### often caused by missing or wrong constraints ###");
      fprintf(fwlo,"\n### recover: check constraints (underdefined ?)  ###");
      }
    fflush(fwlo);
  break;

  case LOG_JACNEG:
    if(LANG == 1) 
      {
      fprintf(fwlo,
      "\n### Jacobi- Determinante Null oder negativ ..Stop            ###");
      fprintf(fwlo,
      "\n### liegt oft an fehlenden oder falschen Randbedingungen     ###");
      fprintf(fwlo,
      "\n### Abhilfe: Randbedingungen pruefen (stat. unterbestimmt ?) ###");
      }    
    if(LANG == 2) 
      {
      fprintf(fwlo,"\n### Jacobi determinant zero or negative ..stop   ###");
      fprintf(fwlo,"\n### often caused by missing or wrong constraints ###");
      fprintf(fwlo,"\n### recover: check constraints (underdefined ?)  ###");
      }
    fflush(fwlo);
  break;

  }
return(0);
}
