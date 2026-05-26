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
* V10.0  December, 2001
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
*  function dyn88d liest z88.dyn aus und laesst memory kommen
*  hier wird File Z88.DYN geoffnet
*  11.12.2003 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88d.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
                     /* rewind                              */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88d.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
                     /* rewind                              */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wlog88d(FR_INT4,int);

/***********************************************************************
*  hier beginnt Function dyn88d
***********************************************************************/
int dyn88d(void)
{
extern FR_DOUBLEAY u;
extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY emod;
extern FR_DOUBLEAY rnue;
extern FR_DOUBLEAY qpara;
extern FR_DOUBLEAY riyy;
extern FR_DOUBLEAY eyy;
extern FR_DOUBLEAY rizz;
extern FR_DOUBLEAY ezz;
extern FR_DOUBLEAY rit;
extern FR_DOUBLEAY wt;
extern FR_DOUBLEAY smw;
extern FR_DOUBLEAY gmw;

extern FR_INT4AY koi;
extern FR_INT4AY ifrei; 
extern FR_INT4AY ioffs;
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;
extern FR_INT4AY ivon;
extern FR_INT4AY ibis;
extern FR_INT4AY intord;
extern FR_INT4AY jsm;

extern FILE *fdyn, *fwlo;
extern char cdyn[];

extern FR_INT4 IDYNMEM;
extern FR_INT4 MAXNFG,MAXK,MAXE,MAXKOI,MAXNEG;

char cline[256], cdummy[80];
  
/*----------------------------------------------------------------------
*  dyn- datei z88.dyn oeffnen
*---------------------------------------------------------------------*/
wlog88d(0,LOG_OPENZ88DYN);

fdyn= fopen(cdyn,"r");
if(fdyn == NULL)
  {
  wlog88d(0,LOG_NODYN);
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

    if( (strstr(cline,"COMMON START"))!= NULL)      /* Lesen COMMON */
      {
      do
        {
        fgets(cline,256,fdyn);
        if( (strstr(cline,"MAXKOI"))!= NULL)        /* Lesen MAXKOI */
          sscanf(cline,"%s %ld",cdummy,&MAXKOI);
        if( (strstr(cline,"MAXK"))!= NULL)          /* Lesen MAXK */
          sscanf(cline,"%s %ld",cdummy,&MAXK);
        if( (strstr(cline,"MAXE"))!= NULL)          /* Lesen MAXE */
          sscanf(cline,"%s %ld",cdummy,&MAXE);
        if( (strstr(cline,"MAXNFG"))!= NULL)        /* Lesen MAXNFG */
          sscanf(cline,"%s %ld",cdummy,&MAXNFG);
        if( (strstr(cline,"MAXNEG"))!= NULL)        /* Lesen MAXNEG */
          sscanf(cline,"%s %ld",cdummy,&MAXNEG);
        }
      while( (strstr(cline,"COMMON END"))== NULL);
      }                                             /* end if COMMON START */

    }
  while( (strstr(cline,"DYNAMIC END"))== NULL);     
    
  }                                                 /* end if DYNAMIC START */
else
  {
  wlog88d(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

if(MAXKOI <= 0 || MAXK <= 0 ||
   MAXE <= 0 || MAXNFG <= 0 || MAXNEG <= 0)
  {
  wlog88d(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

/*----------------------------------------------------------------------
*  korrekt gelesen, file fdyn schliessen
*---------------------------------------------------------------------*/
fclose(fdyn);

wlog88d(MAXKOI,LOG_MAXKOI);
wlog88d(MAXK,LOG_MAXK);
wlog88d(MAXE,LOG_MAXE);
wlog88d(MAXNFG,LOG_MAXNFG);
wlog88d(MAXNEG,LOG_MAXNEG);

wlog88d(0,LOG_OKDYN);

/*----------------------------------------------------------------------
*  memory kommen lassen ..
*---------------------------------------------------------------------*/
wlog88d(0,LOG_ALLOCMEMY);

/*======================================================================
*  memory fuer u :1
*=====================================================================*/
u= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
if(u == NULL)
  {
  wlog88d(1,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(1,LOG_ARRAYOK);

/*======================================================================
*  memory fuer x, y, z :2,3,4
*=====================================================================*/
x= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(x == NULL)
  {
  wlog88d(2,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(2,LOG_ARRAYOK);

y= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(y == NULL)
  {
  wlog88d(3,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(3,LOG_ARRAYOK);

z= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(z == NULL)
  {
  wlog88d(4,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(4,LOG_ARRAYOK);

/*======================================================================
*  memory fuer emod, rnue, qpara: 5,6,7
*=====================================================================*/
emod= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(emod == NULL)
  {
  wlog88d(5,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(5,LOG_ARRAYOK);

rnue= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rnue == NULL)
  {
  wlog88d(6,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(6,LOG_ARRAYOK);

qpara= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(qpara == NULL)
  {
  wlog88d(7,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(7,LOG_ARRAYOK);

/*======================================================================
*  memory fuer koi: 8
*=====================================================================*/
koi= (FR_INT4AY) FR_CALLOC((MAXKOI+1),sizeof(FR_INT4));
if(koi == NULL)
  {
  wlog88d(8,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(8,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ifrei, ioffs, koffs, ityp 9,10,11,12
*=====================================================================*/
ifrei= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(ifrei == NULL)
  {
  wlog88d(9,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(9,LOG_ARRAYOK);

ioffs= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(ioffs == NULL)
  {
  wlog88d(10,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(10,LOG_ARRAYOK);

koffs= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(koffs == NULL)
  {
  wlog88d(11,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(11,LOG_ARRAYOK);

ityp= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(ityp == NULL)
  {
  wlog88d(12,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(12,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ivon, ibis, intord:13,14,15
*=====================================================================*/
ivon= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(ivon == NULL)
  {
  wlog88d(13,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(13,LOG_ARRAYOK);

ibis= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(ibis == NULL)
  {
  wlog88d(14,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(14,LOG_ARRAYOK);

intord= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(intord == NULL)
  {
  wlog88d(15,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(15,LOG_ARRAYOK);

/*======================================================================
*  memory fuer riyy,eyy,rizz,ezz,rit,wt:16,17,18,19,20,21
*=====================================================================*/
riyy= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(riyy == NULL)
  {
  wlog88d(16,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(16,LOG_ARRAYOK);

eyy= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(eyy == NULL)
  {
  wlog88d(17,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(17,LOG_ARRAYOK);

rizz= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rizz == NULL)
  {
  wlog88d(18,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(18,LOG_ARRAYOK);

ezz= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(ezz == NULL)
  {
  wlog88d(19,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(19,LOG_ARRAYOK);

rit= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rit == NULL)
  {
  wlog88d(20,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(20,LOG_ARRAYOK);

wt= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(wt == NULL)
  {
  wlog88d(21,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(21,LOG_ARRAYOK);

/*======================================================================
*  memory fuer smw und jsm: 22,23
*=====================================================================*/
smw= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(smw == NULL)
  {
  wlog88d(22,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(22,LOG_ARRAYOK);

jsm= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(jsm == NULL)
  {
  wlog88d(23,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(23,LOG_ARRAYOK);

/*======================================================================
*  memory fuer gmw: 24
*=====================================================================*/
gmw= (FR_DOUBLEAY) FR_CALLOC((MAXE+1),sizeof(FR_DOUBLE));
if(gmw == NULL)
  {
  wlog88d(24,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88d(24,LOG_ARRAYOK);

/***********************************************************************
* alles o.k. 
***********************************************************************/
IDYNMEM =   (MAXNFG+1)*sizeof(FR_DOUBLE); /* u */
IDYNMEM+= 4*(MAXK+1)*sizeof(FR_DOUBLE);   /* x,y,z,smw */
IDYNMEM+= 3*(MAXNEG+1)*sizeof(FR_DOUBLE); /* emod, rnue, qpara */
IDYNMEM+=   (MAXKOI+1)*sizeof(FR_INT4);   /* koi */
IDYNMEM+= 3*(MAXK+1)*sizeof(FR_INT4);     /* ifrei, ioffs,jsm */
IDYNMEM+= 2*(MAXE+1)*sizeof(FR_INT4);     /* koffs, ityp */
IDYNMEM+= 3*(MAXNEG+1)*sizeof(FR_INT4);   /* ivon,ibis,intord */ 
IDYNMEM+= 6*(MAXNEG+1)*sizeof(FR_DOUBLE); /* riyy,eyy,rizz,ezz,rit,wt*/
IDYNMEM+=   (MAXE+1)*sizeof(FR_DOUBLE);   /* gmw */

wlog88d(IDYNMEM,LOG_SUMMEMY);
wlog88d(0,LOG_EXITDYN88D);

return(0);
}
