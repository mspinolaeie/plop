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
* Compilerunit m5.c enthaelt:  ro2x88 und ro5x88
* 4.10.2005 Rieg
***********************************************************************/

/*----------------------------------------------------------------------
* WindowsNT und 95
*---------------------------------------------------------------------*/
#ifdef FR_WIN95
#include <z88p.h>
#include <stdio.h>    /* fprintf,fgets,sscanf */
#endif

/*----------------------------------------------------------------------
* UNIX
*---------------------------------------------------------------------*/
#ifdef FR_UNIX
#include <z88p.h>
#include <stdio.h>    /* fprintf,fgets,sscanf */
#endif

/***********************************************************************
* Functions
***********************************************************************/
int wlog88p(FR_INT4,int);

/***********************************************************************
* hier beginnt Function ro2x88
***********************************************************************/
int ro2x88(void)
{
extern FILE *f3;
 
extern FR_DOUBLEAY ux;
extern FR_DOUBLEAY uy;
extern FR_DOUBLEAY uz;

extern FR_INT4 nkp,ipflag;

FR_INT4 i,idummy;

char cline[256];

/***********************************************************************
* Eintrag in z88ppm.log
***********************************************************************/
wlog88p(0,LOG_REAO2);
        
/***********************************************************************
* 5 zeilen leerlesen
***********************************************************************/
for(i= 0; i < 5; i++) fgets(cline,256,f3);
          
/***********************************************************************
* Verschiebungen einlesen, nur translatorisch erforderlich
***********************************************************************/
/*----------------------------------------------------------------------
* alles ausser Platten
*---------------------------------------------------------------------*/
if(ipflag == 0)
  {
  for(i= 1; i <= nkp; i++)
    {
    fgets(cline,256,f3);
    sscanf(cline,"%ld %lf %lf %lf",&idummy,&ux[i],&uy[i],&uz[i]);
    }
  }

/*----------------------------------------------------------------------
* Platten brauchen Sonderbehandlung
*---------------------------------------------------------------------*/
else
  {
  for(i= 1; i <= nkp; i++)
    {
    ux[i]= 0.;
    uy[i]= 0.;
    fgets(cline,256,f3);
    sscanf(cline,"%ld %lf",&idummy,&uz[i]);
    }
  }

wlog88p(0,LOG_REAO2OK);
return 0;
}

/***********************************************************************
* hier beginnt subroutine ro5x88
***********************************************************************/
int ro5x88(void)
{
extern FILE *f6;        

extern FR_DOUBLEAY xgp;
extern FR_DOUBLEAY ygp;
extern FR_DOUBLEAY zgp;
extern FR_DOUBLEAY siggp;
extern FR_DOUBLE spamin, spamax, spainc;

extern FR_INT4 MAXGP;
extern FR_INT4 ndim;
extern FR_INT4 isflag, igpanz;

FR_INT4 ninto,i;

char cline[256];

/***********************************************************************
* Einlesen des Fileheaders
***********************************************************************/
wlog88p(0,LOG_REAO5);

fgets(cline,256,f6);
sscanf(cline,"%ld %ld %ld",&ndim,&ninto,&isflag);

/***********************************************************************
* Pruefen, ob auch korrekterweise in Gausspunkten geplottet werden kann
***********************************************************************/
if(ninto== 0)
  {
  wlog88p(0,LOG_NINT0);
  return(AL_NINT0);
  }           

/***********************************************************************
* Einlesen 2 oder 3-dimensional
***********************************************************************/
if(ndim== 2) 
  {
  i= 1;

  while( (fgets(cline,256,f6)) != NULL)
    {
    sscanf(cline,"%lf %lf %lf",&xgp[i],&ygp[i],&siggp[i]);
    if(i == 1) 
      {
      spamin= siggp[1];
      spamax= siggp[1];
      }
    if( siggp[i] < spamin) spamin= siggp[i];
    if( siggp[i] > spamax) spamax= siggp[i];
    i++;
    if(i == MAXGP-1)
      {
      wlog88p(MAXGP,LOG_EXMAXGP);
      return(AL_EXMAXGP);
      }
    }              
  }
else
  {
  i= 1;
  while( (fgets(cline,256,f6)) != NULL)
    {
    sscanf(cline,"%lf %lf %lf %lf",&xgp[i],&ygp[i],&zgp[i],&siggp[i]);
    if(i == 1) 
      {
      spamin= siggp[1];
      spamax= siggp[1];
      }
    if( siggp[i] < spamin) spamin= siggp[i];
    if( siggp[i] > spamax) spamax= siggp[i];
    i++;
    if(i == MAXGP-1)
      {
      wlog88p(MAXGP,LOG_EXMAXGP);
      return(AL_EXMAXGP);
      }
    }              
  }

igpanz= i-1;  /* wie fortran */
spainc= 0.1*(spamax - spamin);
       
wlog88p(0,LOG_REAO5OK);
return 0;
}
