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
* Composed and edited and coypright by 
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
* Function VEND88
* 22.3.2002 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88v.h>
#include <stdio.h>   /* FILE,fclose,printf */
#endif

/***********************************************************************
* Functions
***********************************************************************/
int FR_GETC(void);
void stop88v(void);

/***********************************************************************
* VEND88
***********************************************************************/
int vend88(int ier)
{
extern FR_INT4 LANG;
extern FR_INT4 iwarn;
extern char cdatei[];
           
int jyn;
                
/***********************************************************************
* File fehlerfrei
***********************************************************************/
if(ier == 0 && iwarn == 0)
  {
  if(LANG == 1)
    {
    printf("Keine Fehler in %s endeckt !\n",cdatei);
    printf("Anderes File checken ? 1 <ja> 2 <nein> ");
    }
  if(LANG == 2)
    {
    printf("no errors in %s detected !\n",cdatei);
    printf("check another file ? 1 <yes> 2 <no> ");
    }

  do
    {
    jyn= FR_GETC();

    if      (jyn == 1) return(0);
    else if (jyn == 2) stop88v();
    else
      {
      if(LANG == 1) printf("Falsche Auswahl --> 1 <ja> oder 2 <nein> ");
      if(LANG == 2) printf("wrong choice --> 1 <yes> or 2 <no> ");
      }
    }
  while(!(jyn == 1 || jyn == 2)); 
  }
        
/***********************************************************************
* File hat Warnings, aber keine Fehler
***********************************************************************/
if(iwarn > 0 && ier == 0)
  {
  if(LANG == 1)
    {
    printf("%ld Warnungen in %s endeckt !\n",iwarn,cdatei);
    printf("Anderes File checken ? 1 <ja> 2 <nein> ");
    }
  if(LANG == 2)
    {
    printf("%ld warnings in %s detected !\n",iwarn,cdatei);
    printf("check another file ? 1 <yes> 2 <no> ");
    }
    
  do
    {
    jyn= FR_GETC();

    if      (jyn == 1) return(0);
    else if (jyn == 2) stop88v();
    else
      {
      if(LANG == 1) printf("Falsche Auswahl --> 1 <ja> oder 2 <nein> ");
      if(LANG == 2) printf("wrong choice --> 1 <yes> or 2 <no> ");
      }
    }
  while(!(jyn == 1 || jyn == 2)); 
  }

/***********************************************************************
* File hat Fehler, aber keine Warnings
***********************************************************************/
if(ier == 2 && iwarn == 0)
  {
  if(LANG == 1) printf("Ende Z88V .. Fehler in %s endeckt !\n",cdatei);
  if(LANG == 2) printf("Z88V done .. error in %s detected !\n",cdatei);
  }

/***********************************************************************
* File hat Fehler & Warnings
***********************************************************************/
if(ier == 2 && iwarn > 0)
  {
  if(LANG == 1)
    printf("Ende Z88V .. Fehler und %ld Warnung(en) in %s endeckt !\n",
    iwarn,cdatei);
  if(LANG == 2)
    printf("Z88V done .. error and %ld warning(s) in %s detected !\n",
    iwarn,cdatei);
  }
        
/***********************************************************************
* File nicht vorhanden
***********************************************************************/
if(ier == 3)
  {
  if(LANG == 1) printf("Ende Z88V .. Datei %s nicht vorhanden !\n",cdatei);
  if(LANG == 2) printf("Z88V done .. file %s missing !\n",cdatei);
  }

/***********************************************************************
* Stop
***********************************************************************/
stop88v();

return(0); /* wird ansich nie angesprungen */
}
