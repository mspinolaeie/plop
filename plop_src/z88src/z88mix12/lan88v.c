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
*  function lan88v liest z88.dyn aus und stellt Sprache fest
*  hier werden die Files Z88V.LOG und Z88.DYN geoeffnet
*  23.3.2002 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88v.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
                     /* rewind                              */
#include <string.h>  /* strstr */
#endif

/***********************************************************************
* Fuer Windows95
***********************************************************************/
#ifdef FR_WIN95
#include <z88v.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
                     /* rewind                              */
#include <string.h>  /* strstr */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wlog88v(FR_INT4,int);

/***********************************************************************
*  hier beginnt Function lan88v
***********************************************************************/
int lan88v(void)
{
extern FILE *fdyn, *fwlo;
extern char cdyn[];
extern char clog[];

extern FR_INT4 LANG;

char cline[256];
  
/*----------------------------------------------------------------------
*  Log- Datei z88v.log oeffnen, erste Eintragungen
*---------------------------------------------------------------------*/
fwlo= fopen(clog, "w+");
if(fwlo == NULL)
  return(AL_NOLOG);

rewind(fwlo);

wlog88v(0,LOG_BZ88V);

/*----------------------------------------------------------------------
*  dyn- datei z88.dyn oeffnen
*---------------------------------------------------------------------*/
wlog88v(0,LOG_OPENZ88DYN);

fdyn= fopen(cdyn,"r");
if(fdyn == NULL)
  {
  wlog88v(0,LOG_NODYN);
  fclose(fwlo);
  return(AL_NODYN);
  }

rewind(fdyn);

/*----------------------------------------------------------------------
*  dyn- datei z88.dyn lesen
*---------------------------------------------------------------------*/
fgets(cline,256,fdyn);

if( (strstr(cline,"DYNAMIC START"))!= NULL)         /* Lesen File */
  {
  do
    {
    fgets(cline,256,fdyn);
    if( (strstr(cline,"GERMAN"))!= NULL) LANG = 1;
    if( (strstr(cline,"ENGLISH"))!= NULL) LANG = 2;
    }
  while( (strstr(cline,"DYNAMIC END"))== NULL);     
  }                                                 /* end if DYNAMIC START */
else
  {
  LANG = 2;                                         /* Englisch */
  wlog88v(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

/*----------------------------------------------------------------------
*  korrekt gelesen, file fdyn schliessen
*---------------------------------------------------------------------*/
fclose(fdyn);

/*----------------------------------------------------------------------
*  sicherheitshalber englisch einstellen
*---------------------------------------------------------------------*/
if(LANG == 0) LANG = 2;

return(0);
}
