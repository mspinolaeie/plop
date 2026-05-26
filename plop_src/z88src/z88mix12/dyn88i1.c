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
*  function dyn88i1 liest z88.dyn aus und laesst memory kommen
*  hier wird File Z88.DYN erneut geoeffnet (vorher schon in lan88i1)
*  29.9.2005 Rieg - fuer Iterationssolver Part 1
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88i.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88i.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wlog88i1(FR_INT4,int);

/***********************************************************************
*  hier beginnt Function dyn88i1
***********************************************************************/
int dyn88i1(void)
{
extern struct FR_SIJ *IJ;
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

extern FR_INT4AY ip;
extern FR_INT4AY iez;
extern FR_INT4AY kc;
extern FR_INT4AY koi;
extern FR_INT4AY ifrei; 
extern FR_INT4AY ioffs;
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;
extern FR_INT4AY ivon;
extern FR_INT4AY ibis;
extern FR_INT4AY intord;

extern FILE *fdyn, *fl1;
extern char cdyn[];

extern FR_INT4 IDYNMEM;
extern FR_INT4 MAXSOR,MAXPUF,MAXGS,MAXNFG,MAXK,MAXE,MAXKOI,MAXNEG;

char cline[256], cdummy[80];
  
/*----------------------------------------------------------------------
*  dyn- datei z88.dyn oeffnen
*---------------------------------------------------------------------*/
wlog88i1(0,LOG_OPENZ88DYN);

fdyn= fopen(cdyn,"r");
if(fdyn == NULL)
  {
  wlog88i1(0,LOG_NODYN);
  fclose(fl1);
  return(AL_NODYN);
  }

rewind(fdyn);

/*----------------------------------------------------------------------
*  dyn- datei z88.dyn lesen
*---------------------------------------------------------------------*/
#define CFORMA "%s %ld"

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
        if( (strstr(cline,"MAXGS"))!= NULL)         /* Lesen MAXGS */
          sscanf(cline,CFORMA,cdummy,&MAXGS);
        if( (strstr(cline,"MAXKOI"))!= NULL)        /* Lesen MAXKOI */
          sscanf(cline,CFORMA,cdummy,&MAXKOI);
        if( (strstr(cline,"MAXK"))!= NULL)          /* Lesen MAXK */
          sscanf(cline,CFORMA,cdummy,&MAXK);
        if( (strstr(cline,"MAXE"))!= NULL)          /* Lesen MAXE */
          sscanf(cline,CFORMA,cdummy,&MAXE);
        if( (strstr(cline,"MAXNFG"))!= NULL)        /* Lesen MAXNFG */
          sscanf(cline,CFORMA,cdummy,&MAXNFG);
        if( (strstr(cline,"MAXNEG"))!= NULL)        /* Lesen MAXNEG */
          sscanf(cline,CFORMA,cdummy,&MAXNEG);
        if( (strstr(cline,"MAXSOR"))!= NULL)        /* Lesen MAXSOR */
          sscanf(cline,CFORMA,cdummy,&MAXSOR);
        if( (strstr(cline,"MAXPUF"))!= NULL)        /* Lesen MAXPUF */
          sscanf(cline,CFORMA,cdummy,&MAXPUF);
        }
      while( (strstr(cline,"COMMON END"))== NULL);
      }                                             /* end if COMMON START */

    }
  while( (strstr(cline,"DYNAMIC END"))== NULL);     
    
  }                                                 /* end if DYNAMIC START */
else
  {
  wlog88i1(0,LOG_WRONGDYN);
  fclose(fl1);
  return(AL_WRONGDYN);
  }  

if(MAXSOR <= 0 || MAXGS <= 0  || MAXKOI <= 0 || MAXK <= 0 ||
   MAXE <= 0   || MAXNFG <= 0 || MAXNEG <= 0 || MAXPUF <= 0)
  {
  wlog88i1(0,LOG_WRONGDYN);
  fclose(fl1);
  return(AL_WRONGDYN);
  }  

/*----------------------------------------------------------------------
*  korrekt gelesen, file fdyn schliessen
*---------------------------------------------------------------------*/
fclose(fdyn);

wlog88i1(MAXSOR,LOG_MAXSOR);
wlog88i1(MAXPUF,LOG_MAXPUF);
wlog88i1(MAXGS,LOG_MAXGS);
wlog88i1(MAXKOI,LOG_MAXKOI);
wlog88i1(MAXK,LOG_MAXK);
wlog88i1(MAXE,LOG_MAXE);
wlog88i1(MAXNFG,LOG_MAXNFG);
wlog88i1(MAXNEG,LOG_MAXNEG);

wlog88i1(0,LOG_OKDYN);

/*----------------------------------------------------------------------
*  memory kommen lassen ..
*---------------------------------------------------------------------*/
wlog88i1(0,LOG_ALLOCMEMY);

/*======================================================================
*  memory fuer IJ 1
*=====================================================================*/
IJ= (struct FR_SIJ *) FR_CALLOC((MAXSOR+1),sizeof(struct FR_SIJ));
if(IJ == NULL)
  {
  wlog88i1(1,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(1,LOG_ARRAYOK);
	
/*======================================================================
*  memory fuer x, y, z 2,3,4
*=====================================================================*/
x= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(x == NULL)
  {
  wlog88i1(2,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(2,LOG_ARRAYOK);

y= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(y == NULL)
  {
  wlog88i1(3,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(3,LOG_ARRAYOK);

z= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(z == NULL)
  {
  wlog88i1(4,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(4,LOG_ARRAYOK);

/*======================================================================
*  memory fuer emod, rnue, qpara: 5,6,7
*=====================================================================*/
emod= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(emod == NULL)
  {
  wlog88i1(5,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(5,LOG_ARRAYOK);

rnue= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rnue == NULL)
  {
  wlog88i1(6,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(6,LOG_ARRAYOK);

qpara= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(qpara == NULL)
  {
  wlog88i1(7,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(7,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ip, iez, koi 8,9,10
*=====================================================================*/
ip= (FR_INT4AY) FR_CALLOC((MAXNFG+1),sizeof(FR_INT4));
if(ip == NULL)
  {
  wlog88i1(8,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(8,LOG_ARRAYOK);

iez= (FR_INT4AY) FR_CALLOC((MAXSOR+1),sizeof(FR_INT4));
if(iez == NULL)
  {
  wlog88i1(9,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(9,LOG_ARRAYOK);

koi= (FR_INT4AY) FR_CALLOC((MAXKOI+1),sizeof(FR_INT4));
if(koi == NULL)
  {
  wlog88i1(10,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(10,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ifrei, ioffs, koffs, ityp 11,12,13,14
*=====================================================================*/
ifrei= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(ifrei == NULL)
  {
  wlog88i1(11,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(11,LOG_ARRAYOK);

ioffs= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(ioffs == NULL)
  {
  wlog88i1(12,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(12,LOG_ARRAYOK);

koffs= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(koffs == NULL)
  {
  wlog88i1(13,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(13,LOG_ARRAYOK);

ityp= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(ityp == NULL)
  {
  wlog88i1(14,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(14,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ivon, ibis, intord 15,16,17
*=====================================================================*/
ivon= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(ivon == NULL)
  {
  wlog88i1(15,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(15,LOG_ARRAYOK);

ibis= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(ibis == NULL)
  {
  wlog88i1(16,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(16,LOG_ARRAYOK);

intord= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(intord == NULL)
  {
  wlog88i1(17,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(17,LOG_ARRAYOK);

/*======================================================================
*  memory fuer riyy,eyy,rizz,ezz,rit,wt:18,19,20,21,22,23
*=====================================================================*/
riyy= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(riyy == NULL)
  {
  wlog88i1(18,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(18,LOG_ARRAYOK);

eyy= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(eyy == NULL)
  {
  wlog88i1(19,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(19,LOG_ARRAYOK);

rizz= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rizz == NULL)
  {
  wlog88i1(20,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(20,LOG_ARRAYOK);

ezz= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(ezz == NULL)
  {
  wlog88i1(21,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(21,LOG_ARRAYOK);

rit= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rit == NULL)
  {
  wlog88i1(22,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(22,LOG_ARRAYOK);

wt= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(wt == NULL)
  {
  wlog88i1(23,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(23,LOG_ARRAYOK);

/*======================================================================
*  memory fuer kc 24
*=====================================================================*/
kc= (FR_INT4AY) FR_CALLOC((MAXPUF+1),sizeof(FR_INT4));
if(kc == NULL)
  {
  wlog88i1(24,LOG_ARRAYNOTOK);
  fclose(fl1);
  return(AL_NOMEMY);
  }
else
  wlog88i1(24,LOG_ARRAYOK);

/***********************************************************************
* alles o.k. 
***********************************************************************/
IDYNMEM =   (MAXSOR+1)*sizeof(struct FR_SIJ);   /* IJ */
IDYNMEM+= 3*(MAXK+1)  *sizeof(FR_DOUBLE);       /* x,y,z */
IDYNMEM+= 3*(MAXNEG+1)*sizeof(FR_DOUBLE);       /* emod, rnue, qpara */
IDYNMEM+=   (MAXNFG+1)*sizeof(FR_INT4);         /* ip */
IDYNMEM+=   (MAXSOR+1)*sizeof(FR_INT4);         /* iez */
IDYNMEM+=   (MAXKOI+1)*sizeof(FR_INT4);         /* koi */
IDYNMEM+= 2*(MAXK+1)  *sizeof(FR_INT4);         /* ifrei, ioffs */
IDYNMEM+= 2*(MAXE+1)  *sizeof(FR_INT4);         /* koffs, ityp */
IDYNMEM+= 3*(MAXNEG+1)*sizeof(FR_INT4);         /* ivon,ibis,intord */
IDYNMEM+= 6*(MAXNEG+1)*sizeof(FR_DOUBLE); /* riyy,eyy,rizz,ezz,rit,wt */
IDYNMEM+=   (MAXPUF+1)*sizeof(FR_INT4);         /* kc */

IDYNMEM/= 1048576;

wlog88i1(IDYNMEM,LOG_SUMMEMY);
wlog88i1(0,LOG_EXITDYN88I1);

return(0);
}
