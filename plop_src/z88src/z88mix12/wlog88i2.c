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
* V12.0 February 14, 2005
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
* wlog88i2 gibt Log-Datei-Meldungen aus (1 FR_INT4, 1 int)
* 1.2.06 Rieg
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
*  hier beginnt Function wlog88i2
***********************************************************************/
int wlog88i2(FR_INT4 i,int iatx)
{
extern FILE *fl2;
extern FR_INT4 LANG;

switch(iatx)
  {
  case LOG_BZ88I2:
    if(LANG == 1) fprintf(fl2,"Start Z88I2 Version 12");
    if(LANG == 2) fprintf(fl2,"start Z88I2 version 12");
    fflush(fl2);
  break;

  case LOG_CFLAGC:
    if(LANG == 1)
    fprintf(fl2,"\nSteuerflag CFLAG fuer Z88I2 ist -C, ICFLAG = %ld",i);
    if(LANG == 2)
    fprintf(fl2,"\nflag CFLAG for Z88I2 is -C, ICFLAG = %ld",i);
    fflush(fl2);
  break;

  case LOG_CFLAGN:
    if(LANG == 1)
    fprintf(fl2,"\nSteuerflag CFLAG fuer Z88I2 ist -S, ICFLAG = %ld",i);
    if(LANG == 2)
    fprintf(fl2,"\nflag CFLAG for Z88I2 is -S, ICFLAG = %ld",i);
    fflush(fl2);
  break;

  case LOG_OPENZ88DYN:
    if(LANG == 1) fprintf(fl2,"\nOeffnen der Datei Z88.DYN");
    if(LANG == 2) fprintf(fl2,"\nopening file Z88.DYN");
    fflush(fl2);
  break;

  case LOG_NODYN:
    if(LANG == 1)
    fprintf(fl2,"\n### kann Z88.DYN nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl2,"\n### cannot open Z88.DYN ..stop ###");
    fflush(fl2);
  break;

  case LOG_WRONGDYN:
    if(LANG == 1)
    fprintf(fl2,"\n### File Z88.DYN ist nicht korrekt ..Stop ###");
    if(LANG == 2)
    fprintf(fl2,"\n### file Z88.DYN is not correct ..stop ###");
    fflush(fl2);
  break;

  case LOG_MAXGS:
    fprintf(fl2,"\nMAXGS  = %ld",i);
    fflush(fl2);
  break;

  case LOG_MAXKOI:
    fprintf(fl2,"\nMAXKOI = %ld",i);
    fflush(fl2);
  break;

  case LOG_MAXK:
    fprintf(fl2,"\nMAXK   = %ld",i);
    fflush(fl2);
  break;

  case LOG_MAXE:
    fprintf(fl2,"\nMAXE   = %ld",i);
    fflush(fl2);
  break;

  case LOG_MAXNFG:
    fprintf(fl2,"\nMAXNFG = %ld",i);
    fflush(fl2);
  break;

  case LOG_MAXNEG:
    fprintf(fl2,"\nMAXNEG = %ld",i);
    fflush(fl2);
  break;

  case LOG_MAXESM:
    fprintf(fl2,"\nMAXESM = %ld",i);
    fflush(fl2);
  break;

  case LOG_MAXPR:
    fprintf(fl2,"\nMAXPR = %ld",i);
    fflush(fl2);
  break;
 
 case LOG_OKDYN:
    if(LANG == 1)
    fprintf(fl2,"\nDatei Z88.DYN gelesen..scheint formal o.k. zu sein");
    if(LANG == 2)
    fprintf(fl2,"\nfile Z88.DYN read ..seems to be o.k.");
    fflush(fl2);
  break;

  case LOG_ALLOCMEMY:
    if(LANG == 1) fprintf(fl2,"\nDynamisches Memory anlegen:");
    if(LANG == 2) fprintf(fl2,"\nallocating dynamic memory:");
    fflush(fl2);
  break;

  case LOG_ARRAYNOTOK:
    if(LANG == 1)
    fprintf(fl2,"\n### Memory Kennung %ld nicht o.k. ..Stop ###",i);
    if(LANG == 2)
    fprintf(fl2,"\n### memory id %ld is not o.k. ..stop ###",i);
    fflush(fl2);
  break;

  case LOG_ARRAYOK:
    if(LANG == 1) fprintf(fl2,"\nMemory Kennung %ld angelegt",i);
    if(LANG == 2) fprintf(fl2,"\nmemory id %ld allocated",i);
    fflush(fl2);
  break;

  case LOG_SUMMEMY:
    if(LANG == 1)
    fprintf(fl2,"\nDynamisches Memory vollstaendig angefordert: %ld MB",i);
    if(LANG == 2)
    fprintf(fl2,"\ndynamic memory totally allocated: %ld MB",i);
    fflush(fl2);
  break;

  case LOG_EXITDYN88I2:
    if(LANG == 1) fprintf(fl2,"\nVerlassen Speichereinheit DYN88I2");
    if(LANG == 2) fprintf(fl2,"\nleaving storage function DYN88I2");
    fflush(fl2);
  break;

  case LOG_NO1Y:
    if(LANG == 1)
    fprintf(fl2,"\n### kann Z88O1.BNY nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl2,"\n### cannot open Z88O1.BNY ..stop ###");
    fflush(fl2);
  break;

  case LOG_REAO1Y:
    if(LANG == 1) fprintf(fl2,"\nEinlesen von Z88O1.BNY");
    if(LANG == 2) fprintf(fl2,"\nreading Z88O2.BNY");
    fflush(fl2);
  break;

  case LOG_R1Y88OK:
    if(LANG == 1) fprintf(fl2,"\nZ88O2.BNY eingelesen");
    if(LANG == 2) fprintf(fl2,"\nZ88O2.BNY read");
    fflush(fl2);
  break;

  case LOG_REA4Y:
    if(LANG == 1) fprintf(fl2,"\nEinlesen von Z88O4.BNY");
    if(LANG == 2) fprintf(fl2,"\nreading Z88O4.BNY");
    fflush(fl2);
  break;

  case LOG_REA4YOK:
    if(LANG == 1) fprintf(fl2,"\nZ88O4.BNY eingelesen");
    if(LANG == 2) fprintf(fl2,"\nZ88O4.BNY read");
    fflush(fl2);
  break;

  case LOG_Z88B:
    if(LANG == 1) fprintf(fl2,"\nStart Z88BI : Pass 1 von Z88I2");
    if(LANG == 2) fprintf(fl2,"\nstart Z88BI : pass 1 of Z88I2");
    fflush(fl2);
  break;

  case LOG_EXGS:
    if(LANG == 1) fprintf(fl2,
"\n### IP = %ld,.. ueberschreitet MAXGS ###\
\n### Struktur zu gross fuer Z88 ..Stop       ###\
\n### Abhilfe: MAXGS hoeher setzen in Z88.DYN ###",i);
    if(LANG == 2) fprintf(fl2,
"\n### IP = %ld,.. exceeds MAXGS ###\
\n### system of equations too large ..stop ###\
\n### recover: increase MAXGS in Z88.DYN   ###",i);
    fflush(fl2);
  break;

  case LOG_EXKOI:
    if(LANG == 1) fprintf(fl2,
"\n### NKOI = %ld,.. ueberschreitet MAXKOI ###\
\n### Struktur zu gross fuer Z88 ..Stop       ###\
\n### Abhilfe: MAXKOI hoeher setzen in Z88.DYN ###",i);
    if(LANG == 2) fprintf(fl2,
"\n### NKOI = %ld,.. exceeds MAXKOI ###\
\n### system of equations too large ..stop ###\
\n### recover: increase MAXKOI in Z88.DYN  ###",i);
    fflush(fl2);
  break;

  case LOG_EXMAXPR:
    if(LANG == 1) fprintf(fl2,
"\n### NKOI = %ld,.. ueberschreitet MAXPR ###\
\n### Lastvektor zu gross fuer Z88 ..Stop       ###\
\n### Abhilfe: MAXPR hoeher setzen in Z88.DYN ###",i);
    if(LANG == 2) fprintf(fl2,
"\n### NKOI = %ld,.. exceeds MAXPR ###\
\n### load vektor too large ..stop ###\
\n### recover: increase MAXPR in Z88.DYN  ###",i);
    fflush(fl2);
  break;

  case LOG_COMPI:
    if(LANG == 1) fprintf(fl2,"\n*** Compilation ***");
    if(LANG == 2) fprintf(fl2,"\n*** compilation ***");
    fflush(fl2);
  break;

  case LOG_EXITZ88B:
    if(LANG == 1) fprintf(fl2,"\nVerlassen Z88BI, Pass 1 erledigt");
    if(LANG == 2) fprintf(fl2,"\nleaving Z88BI, pass 1 done");
    fflush(fl2);
  break;

  case LOG_NO2Y:
    if(LANG == 1)
    fprintf(fl2,"\n### kann Z88O2.BNY nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl2,"\n### cannot open Z88O2.BNY ..stop ###");
    fflush(fl2);
  break;

  case LOG_WRI2Y:
    if(LANG == 1) fprintf(fl2,"\nBeschreiben von Z88O2.BNY");
    if(LANG == 2) fprintf(fl2,"\nwriting Z88O2.BNY");
    fflush(fl2);
  break;

  case LOG_WRI2YOK:
    if(LANG == 1) fprintf(fl2,"\nZ88O2.BNY fertig geschrieben");
    if(LANG == 2) fprintf(fl2,"\nZ88O2.BNY totally written");
    fflush(fl2);
  break;

  case LOG_Z88CC:
    if(LANG == 1) fprintf(fl2,"\nStart Z88CI : Pass 2 von Z88I2");
    if(LANG == 2) fprintf(fl2,"\nstart Z88CI : pass 2 of Z88I2");
    fflush(fl2);
  break;

  case LOG_REA2Y:
    if(LANG == 1) fprintf(fl2,"\nEinlesen von Z88O2.BNY");
    if(LANG == 2) fprintf(fl2,"\nreading Z88O2.BNY");
    fflush(fl2);
  break;

  case LOG_REA2YOK:
    if(LANG == 1) fprintf(fl2,"\nZ88O2.BNY fertig eingelesen");
    if(LANG == 2) fprintf(fl2,"\nZ88O2.BNY totally read");
    fflush(fl2);
  break;

  case LOG_NOI4:
    if(LANG == 1)
    fprintf(fl2,"\n### kann Z88I4.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl2,"\n### cannot open Z88I4.TXT ..stop ###");
    fflush(fl2);
  break;

  case LOG_NOI2:
    if(LANG == 1)
    fprintf(fl2,"\n### kann Z88I2.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl2,"\n### cannot open Z88I2.TXT ..stop ###");
    fflush(fl2);
  break;

  case LOG_NOI5:
    if(LANG == 1)
    fprintf(fl2,"\n### kann Z88I5.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl2,"\n### cannot open Z88I5.TXT ..stop ###");
    fflush(fl2);
  break;

  case LOG_NO3Y:
    if(LANG == 1)
    fprintf(fl2,"\n### kann Z88O3.BNY nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl2,"\n### cannot open Z88O3.BNY ..stop ###");
    fflush(fl2);
  break;

  case LOG_NOO2:
    if(LANG == 1)
    fprintf(fl2,"\n### kann Z88O2.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fl2,"\n### cannot open Z88O2.TXT ..stop ###");
    fflush(fl2);
  break;

  case LOG_REAI4:
    if(LANG == 1) fprintf(fl2,"\nEinlesen Z88I4.TXT");
    if(LANG == 2) fprintf(fl2,"\nreading Z88I4.TXT");
    fflush(fl2);
  break;

  case LOG_REAI2:
    if(LANG == 1) fprintf(fl2,"\nEinlesen Z88I2.TXT");
    if(LANG == 2) fprintf(fl2,"\nreading Z88I2.TXT");
    fflush(fl2);
  break;

  case LOG_BRI588:
    if(LANG == 1) fprintf(fl2,"\nEinlesen von Z88I5.TXT");
    if(LANG == 2) fprintf(fl2,"\nreading Z88I5.TXT");
    fflush(fl2);
  break;

  case LOG_EXITRI188:
    if(LANG == 1) fprintf(fl2,"\nZ88I1.TXT fertig eingelesen");
    if(LANG == 2) fprintf(fl2,"\nZ88I1.TXT totally read");
    fflush(fl2);
  break;

  case LOG_EXITRI588:
    if(LANG == 1) fprintf(fl2,"\nZ88I5.TXT fertig eingelesen");
    if(LANG == 2) fprintf(fl2,"\nZ88I5.TXT totally read");
    fflush(fl2);
  break;

  case LOG_MAXIT:
    fprintf(fl2,"\nMAXIT  = %ld",i);
    fflush(fl2);
  break;

  case LOG_ERBPA:
    if(LANG == 1)
    fprintf(fl2,"\nEinarbeiten der Randbedingungen Pass %ld",i);
    if(LANG == 2)
    fprintf(fl2,"\nincorporating constraints pass %ld",i);
    fflush(fl2);
  break;

  case LOG_SCAL88:
    if(LANG == 1) fprintf(fl2,"\nStart SCAL88");
    if(LANG == 2) fprintf(fl2,"\nstart SCAL88");
    fflush(fl2);
  break;

  case LOG_SICCG88:
    if(LANG == 1) fprintf(fl2,"\nStart SICCG88");
    if(LANG == 2) fprintf(fl2,"\nstart SICCG88");
    fflush(fl2);
  break;

  case LOG_SORCG88:
    if(LANG == 1) fprintf(fl2,"\nStart SORCG88");
    if(LANG == 2) fprintf(fl2,"\nstart SORCG88");
    fflush(fl2);
  break;

  case LOG_WRI3Y:
    if(LANG == 1) fprintf(fl2,"\nBeschreiben von Z88O3.BNY");
    if(LANG == 2) fprintf(fl2,"\nwriting Z88O3.BNY");
    fflush(fl2);
  break;

  case LOG_WRIO2:
    if(LANG == 1) fprintf(fl2,"\nBeschreiben von Z88O2.TXT");
    if(LANG == 2) fprintf(fl2,"\nwriting Z88O2.TXT");
    fflush(fl2);
  break;

  case LOG_ITERA:
    if(LANG == 1) fprintf(fl2,"\n %ld Iterationen ausgefuehrt",i);
    if(LANG == 2) fprintf(fl2,"\n %ld iterations done",i);
    fflush(fl2);
  break;

  case LOG_EXITZ88CC:
    if(LANG == 1)
    fprintf(fl2,"\nVerlassen Z88CI, Pass 2 erledigt: Ende Z88I2");
    if(LANG == 2)
    fprintf(fl2,"\nleaving Z88CI, pass 2 done: Z88I2 done");
    fflush(fl2);
  break;

  case LOG_DIAGNULL:
    if(LANG == 1) 
      {
      fprintf(fl2,"\n### Diagonalelement %ld Null oder negativ ..Stop ###",i);
      fprintf(fl2,
      "\n### liegt oft an fehlenden oder falschen Randbedingungen ###");
      fprintf(fl2,
      "\n### Abhilfe: Randbedingungen pruefen (statisch unterbestimmt ?) ###");
      }    
    if(LANG == 2) 
      {
      fprintf(fl2,"\n### diagonal element %ld zero or negative ..stop ###",i);
      fprintf(fl2,"\n### often caused by missing or wrong constraints ###");
      fprintf(fl2,"\n### recover: check constraints (underdefined ?)  ###");
      }
    fflush(fl2);
  break;

  case LOG_JACNEG:
    if(LANG == 1) 
      {
      fprintf(fl2,
      "\n### Element %ld ###",i);
      fprintf(fl2,
      "\n### Jacobi- Determinante Null oder negativ ..Stop            ###");
      fprintf(fl2,
      "\n### Elementnumerierung falsch, nicht mathematisch positiv    ###");
      fprintf(fl2,
      "\n### Abhilfe: Siehe Online Hilfe oder Handbuch zum Elementtyp ###");
      }    
    if(LANG == 2) 
      {
      fprintf(fl2,"\n### Element %ld ###",i);
      fprintf(fl2,"\n### Jacobi determinant zero or negative ..stop     ###");
      fprintf(fl2,"\n### element numbering wrong, not counter-clockwise ###");
      fprintf(fl2,"\n### Recover:renumber wrong elements(consult manual)###");
      }
    fflush(fl2);
  break;

  case LOG_JACLOA:
    if(LANG == 1) 
      {
      fprintf(fl2,
      "\n### Lastvektor %ld ###",i);
      fprintf(fl2,
      "\n### Jacobi- Determinante Null oder negativ ..Stop            ###");
      fprintf(fl2,
      "\n### Elementnumerierung falsch, nicht mathematisch positiv    ###");
      fprintf(fl2,
      "\n### Abhilfe: Siehe Online Hilfe oder Handbuch zum Elementtyp ###");
      }    
    if(LANG == 2) 
      {
      fprintf(fl2,"\n### Load vector %ld ###",i);
      fprintf(fl2,"\n### Jacobi determinant zero or negative ..stop     ###");
      fprintf(fl2,"\n### element numbering wrong, not counter-clockwise ###");
      fprintf(fl2,"\n### Recover:renumber wrong elements(consult manual)###");
      }
    fflush(fl2);
  break;

  }
return(0);
}
