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
* V11.0  December 12, 2003
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
* - wrim88g gibt Texte aus (1 FR_INT4)
* 25.3.2004 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88g.h>
#include <windows.h>
#include <string.h>   /* strlen  */
#include <stdio.h>    /* sprintf */
#endif

/***********************************************************************
*  hier beginnt Function wrim88g
***********************************************************************/
int wrim88g(FR_INT4 i,int iatx)
{
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];

switch(iatx)
  {
  case TX_COSOPEN:
    if(LANG == 1) TextOut(hDC,10,50,"Z88G.COS geoeffnet",18);
    if(LANG == 2) TextOut(hDC,10,50,"Z88G.COS opened",15);
  break;

  case TX_NASOPEN:
    if(LANG == 1) TextOut(hDC,10,50,"Z88G.NAS geoeffnet",18);
    if(LANG == 2) TextOut(hDC,10,50,"Z88G.NAS opened",15);
  break;

  case TX_I1OPEN:
    if(LANG == 1) TextOut(hDC,280,50,"Z88I1.TXT geoeffnet",19);
    if(LANG == 2) TextOut(hDC,280,50,"Z88I1.TXT opened",16);
  break;

  case TX_I2OPEN:
    if(LANG == 1) TextOut(hDC,10,70,"Z88I2.TXT geoeffnet",19);
    if(LANG == 2) TextOut(hDC,10,70,"Z88I2.TXT opened",16);
  break;

  case TX_I3OPEN:
    if(LANG == 1) TextOut(hDC,280,70,"Z88I3.TXT geoeffnet",19);
    if(LANG == 2) TextOut(hDC,280,70,"Z88I3.TXT opened",16);
  break;

  case TX_DIMDET:
    if(LANG == 1) sprintf(cline,"%ld-D Struktur entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld-D structure detected",i);
    laenge= strlen(cline);
    TextOut(hDC,10,90,cline,laenge);
  break;

  case TX_NODDET:
    if(LANG == 1) sprintf(cline,"%ld Knoten entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld nodes detected",i);
    laenge= strlen(cline);
    TextOut(hDC,280,90,cline,laenge);
  break;

  case TX_ELEDET:
    if(LANG == 1) sprintf(cline,"%ld Elemente entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld elements detected",i);
    laenge= strlen(cline);
    TextOut(hDC,10,110,cline,laenge);
  break;

  case TX_CONDET:
    if(LANG == 1) sprintf(cline,"%ld Randbedingungen entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld boundary conditions detected",i);
    laenge= strlen(cline);
    TextOut(hDC,280,110,cline,laenge);
  break;

  case TX_NEGDET:
    if(LANG == 1) sprintf(cline,"%ld E-Gesetze entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld mat lines detected",i);
    laenge= strlen(cline);
    TextOut(hDC,10,130,cline,laenge);
  break;

  case TX_PELDET:
    if(LANG == 1) sprintf(cline,"%ld Elemente mit Druck entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld elements with pressure detected",i);
    laenge= strlen(cline);
    TextOut(hDC,280,130,cline,laenge);
  break;

  case TX_REAWRI:
    if(LANG == 1) TextOut(hDC,10,150,"Z88G.COS/IN lesen, Z88I*.TXT schreiben",38);
    if(LANG == 2) TextOut(hDC,10,150,"reading Z88G.COS/IN, writing Z88I*.TXT",38);
  break;

  case TX_NODDON:
    if(LANG == 1) sprintf(cline,"%ld Knoten erledigt",i);
    if(LANG == 2) sprintf(cline,"%ld nodes done",i);
    laenge= strlen(cline);
    TextOut(hDC,10,170,cline,laenge);
  break;

  case TX_ELEDON:
    if(LANG == 1) sprintf(cline,"%ld Elemente erledigt",i);
    if(LANG == 2) sprintf(cline,"%ld elements done",i);
    laenge= strlen(cline);
    TextOut(hDC,280,170,cline,laenge);
  break;

  case TX_CONDON:
    if(LANG == 1) sprintf(cline,"%ld Randbedingungen erledigt",i);
    if(LANG == 2) sprintf(cline,"%ld boundary conditions done",i);
    laenge= strlen(cline);
    TextOut(hDC,10,190,cline,laenge);
  break;

  case TX_16DET:
    if(LANG == 1) sprintf(cline,"%ld Tetraeder Nr.16 entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld tetrahedrons No.16 detected",i);
    laenge= strlen(cline);
    TextOut(hDC,10,210,cline,laenge);
  break;

  case TX_17DET:
    if(LANG == 1) sprintf(cline,"%ld Tetraeder Nr.17 entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld tetrahedrons No.17 detected",i);
    laenge= strlen(cline);
    TextOut(hDC,280,210,cline,laenge);
  break;

  case TX_7DET:
    if(LANG == 1) sprintf(cline,"%ld Scheiben Nr.7 entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld plane stress ele. No.7 detected",i);
    laenge= strlen(cline);
    TextOut(hDC,10,230,cline,laenge);
  break;

  case TX_14DET:
    if(LANG == 1) sprintf(cline,"%ld Scheiben Nr.14 entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld plane stress ele. No.14 detected",i);
    laenge= strlen(cline);
    TextOut(hDC,280,230,cline,laenge);
  break;

  case TX_18DET:
    if(LANG == 1) sprintf(cline,"%ld Platten Nr.18 entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld plates No.18 detected",i);
    laenge= strlen(cline);
    TextOut(hDC,10,250,cline,laenge);
  break;

  case TX_20DET:
    if(LANG == 1) sprintf(cline,"%ld Platten Nr.20 entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld plates No.20 detected",i);
    laenge= strlen(cline);
    TextOut(hDC,280,250,cline,laenge);
  break;

  case TX_8DET:
    if(LANG == 1) sprintf(cline,"%ld Torus Nr.8 entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld torus No.8 detected",i);
    laenge= strlen(cline);
    TextOut(hDC,10,250,cline,laenge);
  break;

  case TX_15DET:
    if(LANG == 1) sprintf(cline,"%ld Torus Nr.15 entdeckt",i);
    if(LANG == 2) sprintf(cline,"%ld torus No.15 detected",i);
    laenge= strlen(cline);
    TextOut(hDC,280,250,cline,laenge);
  break;

  case TX_Z88CS:
    if(LANG == 1) TextOut(hDC,10,270,"Z88-Daten berechnet und gespeichert",35);
    if(LANG == 2) TextOut(hDC,10,270,"Z88 data computed and stored",28);
  break;

  case TX_Z88DONE:
    if(LANG == 1) TextOut(hDC,280,270,"Alle Dateien geschlossen. Ende Z88G",35);
    if(LANG == 2) TextOut(hDC,280,270,"All files closed. Z88G done",27);
  break;
  }
return(0);
}

