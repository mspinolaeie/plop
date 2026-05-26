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
*  function dyn88e liest z88.dyn aus und laesst memory kommen
*  hier wird File Z88.DYN geoffnet
*  8.4.2002 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88e.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
                     /* rewind                              */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88e.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
                     /* rewind                              */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wlog88e(FR_INT4,int);

/***********************************************************************
*  hier beginnt Function dyn88e
***********************************************************************/
int dyn88e(void)
{
extern FR_DOUBLEAY se;
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
extern FR_DOUBLEAY fsum1;
extern FR_DOUBLEAY fsum2;
extern FR_DOUBLEAY fsum3;
extern FR_DOUBLEAY fsum4;
extern FR_DOUBLEAY fsum5;
extern FR_DOUBLEAY fsum6;

extern FR_INT4AY koi;
extern FR_INT4AY ifrei; 
extern FR_INT4AY ioffs;
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;
extern FR_INT4AY ivon;
extern FR_INT4AY ibis;
extern FR_INT4AY intord;

extern FILE *fdyn, *fwlo;
extern char cdyn[];

extern FR_INT4 IDYNMEM;
extern FR_INT4 MAXNFG,MAXK,MAXE,MAXKOI,MAXESM,MAXNEG;

char cline[256], cdummy[80];
  
/*----------------------------------------------------------------------
*  dyn- datei z88.dyn oeffnen
*---------------------------------------------------------------------*/
wlog88e(0,LOG_OPENZ88DYN);

fdyn= fopen(cdyn,"r");
if(fdyn == NULL)
  {
  wlog88e(0,LOG_NODYN);
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
  wlog88e(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

if(MAXKOI <= 0 || MAXK <= 0 ||
   MAXE <= 0 || MAXNFG <= 0 || MAXNEG <= 0)
  {
  wlog88e(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

/*----------------------------------------------------------------------
*  korrekt gelesen, file fdyn schliessen
*---------------------------------------------------------------------*/
fclose(fdyn);

wlog88e(MAXKOI,LOG_MAXKOI);
wlog88e(MAXK,LOG_MAXK);
wlog88e(MAXE,LOG_MAXE);
wlog88e(MAXNFG,LOG_MAXNFG);
wlog88e(MAXNEG,LOG_MAXNEG);
wlog88e(MAXESM,LOG_MAXESM);

wlog88e(0,LOG_OKDYN);

/*----------------------------------------------------------------------
*  memory kommen lassen ..
*---------------------------------------------------------------------*/
wlog88e(0,LOG_ALLOCMEMY);

/*======================================================================
*  memory fuer se,u :1,2
*=====================================================================*/
se= (FR_DOUBLEAY) FR_CALLOC((MAXESM+1),sizeof(FR_DOUBLE));
if(se == NULL)
  {
  wlog88e(1,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(1,LOG_ARRAYOK);

u= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
if(u == NULL)
  {
  wlog88e(2,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(2,LOG_ARRAYOK);

/*======================================================================
*  memory fuer x, y, z :3,4,5
*=====================================================================*/
x= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(x == NULL)
  {
  wlog88e(3,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(3,LOG_ARRAYOK);

y= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(y == NULL)
  {
  wlog88e(4,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(4,LOG_ARRAYOK);

z= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(z == NULL)
  {
  wlog88e(5,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(5,LOG_ARRAYOK);

/*======================================================================
*  memory fuer emod, rnue, qpara: 6,7,8
*=====================================================================*/
emod= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(emod == NULL)
  {
  wlog88e(6,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(6,LOG_ARRAYOK);

rnue= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rnue == NULL)
  {
  wlog88e(7,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(7,LOG_ARRAYOK);

qpara= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(qpara == NULL)
  {
  wlog88e(8,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(8,LOG_ARRAYOK);

/*======================================================================
*  memory fuer koi: 9
*=====================================================================*/
koi= (FR_INT4AY) FR_CALLOC((MAXKOI+1),sizeof(FR_INT4));
if(koi == NULL)
  {
  wlog88e(9,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(9,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ifrei, ioffs, koffs, ityp 10,11,12,13
*=====================================================================*/
ifrei= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(ifrei == NULL)
  {
  wlog88e(10,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(10,LOG_ARRAYOK);

ioffs= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(ioffs == NULL)
  {
  wlog88e(11,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(11,LOG_ARRAYOK);

koffs= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(koffs == NULL)
  {
  wlog88e(12,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(12,LOG_ARRAYOK);

ityp= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(ityp == NULL)
  {
  wlog88e(13,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(13,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ivon, ibis, intord:14,15,16
*=====================================================================*/
ivon= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(ivon == NULL)
  {
  wlog88e(14,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(14,LOG_ARRAYOK);

ibis= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(ibis == NULL)
  {
  wlog88e(15,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(15,LOG_ARRAYOK);

intord= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(intord == NULL)
  {
  wlog88e(16,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(16,LOG_ARRAYOK);

/*======================================================================
*  memory fuer riyy,eyy,rizz,ezz,rit,wt:17,18,19,20,21,22
*=====================================================================*/
riyy= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(riyy == NULL)
  {
  wlog88e(17,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(17,LOG_ARRAYOK);

eyy= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(eyy == NULL)
  {
  wlog88e(18,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(18,LOG_ARRAYOK);

rizz= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rizz == NULL)
  {
  wlog88e(19,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(19,LOG_ARRAYOK);

ezz= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(ezz == NULL)
  {
  wlog88e(20,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(20,LOG_ARRAYOK);

rit= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rit == NULL)
  {
  wlog88e(21,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(21,LOG_ARRAYOK);

wt= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(wt == NULL)
  {
  wlog88e(22,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(22,LOG_ARRAYOK);

/*======================================================================
*  memory fuer fsum1 - fsum6: 23,24,25,26,27,28
*=====================================================================*/
fsum1= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(fsum1 == NULL)
  {
  wlog88e(23,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(23,LOG_ARRAYOK);

fsum2= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(fsum2 == NULL)
  {
  wlog88e(24,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(24,LOG_ARRAYOK);
  
fsum3= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(fsum3 == NULL)
  {
  wlog88e(25,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(25,LOG_ARRAYOK);

fsum4= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(fsum4 == NULL)
  {
  wlog88e(26,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(26,LOG_ARRAYOK);
  
fsum5= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(fsum5 == NULL)
  {
  wlog88e(27,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(27,LOG_ARRAYOK);
  
fsum6= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(fsum6 == NULL)
  {
  wlog88e(28,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88e(28,LOG_ARRAYOK);
  
/***********************************************************************
* alles o.k. 
***********************************************************************/
IDYNMEM =   (MAXESM+1)*sizeof(FR_DOUBLE); /* se */
IDYNMEM+=   (MAXNFG+1)*sizeof(FR_DOUBLE); /* u */
IDYNMEM+= 3*(MAXK+1)*sizeof(FR_DOUBLE);   /* x,y,z */
IDYNMEM+= 3*(MAXNEG+1)*sizeof(FR_DOUBLE); /* emod, rnue, qpara */
IDYNMEM+=   (MAXKOI+1)*sizeof(FR_INT4);   /* koi */
IDYNMEM+= 2*(MAXK+1)*sizeof(FR_INT4);     /* ifrei, ioffs */
IDYNMEM+= 2*(MAXE+1)*sizeof(FR_INT4);     /* koffs, ityp */
IDYNMEM+= 3*(MAXNEG+1)*sizeof(FR_INT4);   /* ivon,ibis,intord */
IDYNMEM+= 6*(MAXNEG+1)*sizeof(FR_DOUBLE); /* riyy,eyy,rizz,ezz,rit,wt*/
IDYNMEM+= 6*(MAXK+1)*sizeof(FR_DOUBLE);   /* fsum1 - fsum6 */

wlog88e(IDYNMEM,LOG_SUMMEMY);
wlog88e(0,LOG_EXITDYN88E);

return(0);
}
