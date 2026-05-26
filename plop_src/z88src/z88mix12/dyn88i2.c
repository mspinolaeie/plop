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
*  function dyn88i2 liest z88.dyn aus und laesst memory kommen
*  hier wird File Z88.DYN erneut geoeffnet (vorher schon in lan88i2)
*  29.9.05 Rieg - fuer Iterationssolver - Part 2 
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88i.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
                     /* rewind                              */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88i.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
                     /* rewind                              */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wlog88i2(FR_INT4,int);

/***********************************************************************
* hier beginnt Function dyn88i2
***********************************************************************/
int dyn88i2(void)
{
extern FR_DOUBLEAY GS;
extern FR_DOUBLEAY CI;
extern FR_DOUBLEAY se;
extern FR_DOUBLEAY rs;
extern FR_DOUBLEAY xi;
extern FR_DOUBLEAY xa;
extern FR_DOUBLEAY v;
extern FR_DOUBLEAY pk;
extern FR_DOUBLEAY zz;
extern FR_DOUBLEAY fak;
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
extern FR_DOUBLEAY pres;
extern FR_DOUBLEAY tr1;
extern FR_DOUBLEAY tr2;

extern FR_INT4AY ip;
extern FR_INT4AY iez;
extern FR_INT4AY koi;
extern FR_INT4AY ifrei; 
extern FR_INT4AY ioffs;
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;
extern FR_INT4AY ivon;
extern FR_INT4AY ibis;
extern FR_INT4AY intord;
extern FR_INT4AY nep;
extern FR_INT4AY noi;
extern FR_INT4AY noffs;

extern FILE *fdyn, *fl2;
extern char cdyn[];

extern FR_INT4 IDYNMEM,ICFLAG;
extern FR_INT4 MAXGS,MAXNFG,MAXK,MAXE,MAXKOI,MAXESM,MAXNEG,MAXPR;

char cline[256], cdummy[80];
  
/*----------------------------------------------------------------------
*  Eintragungen in Z88I2.LOG
*---------------------------------------------------------------------*/
#ifdef FR_UNIX
if     (ICFLAG == 1) wlog88i2(1,LOG_CFLAGC);
else if(ICFLAG == 2) wlog88i2(2,LOG_CFLAGN);
#endif
      
/*----------------------------------------------------------------------
*  dyn- datei z88.dyn oeffnen
*---------------------------------------------------------------------*/
wlog88i2(0,LOG_OPENZ88DYN);

fdyn= fopen(cdyn,"r");
if(fdyn == NULL)
  {
  wlog88i2(0,LOG_NODYN);
  fclose(fl2);
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
        if( (strstr(cline,"MAXPR"))!= NULL)         /* Lesen MAXPR */
          sscanf(cline,CFORMA,cdummy,&MAXPR);
        }
      while( (strstr(cline,"COMMON END"))== NULL);
      }                                             /* end if COMMON START */

    }
  while( (strstr(cline,"DYNAMIC END"))== NULL);     
    
  }                                                 /* end if DYNAMIC START */
else
  {
  wlog88i2(0,LOG_WRONGDYN);
  fclose(fl2);
  return(AL_WRONGDYN);
  }  

if(MAXGS <= 0 || MAXKOI <= 0 || MAXK <= 0   ||
   MAXE <= 0  || MAXNFG <= 0 || MAXNEG <= 0 || MAXPR <= 0)
  {
  wlog88i2(0,LOG_WRONGDYN);
  fclose(fl2);
  return(AL_WRONGDYN);
  }  

/*----------------------------------------------------------------------
*  korrekt gelesen, file fdyn schliessen
*---------------------------------------------------------------------*/
fclose(fdyn);

wlog88i2(MAXGS,LOG_MAXGS);
wlog88i2(MAXKOI,LOG_MAXKOI);
wlog88i2(MAXK,LOG_MAXK);
wlog88i2(MAXE,LOG_MAXE);
wlog88i2(MAXNFG,LOG_MAXNFG);
wlog88i2(MAXNEG,LOG_MAXNEG);
wlog88i2(MAXESM,LOG_MAXESM);
wlog88i2(MAXPR,LOG_MAXPR);

wlog88i2(0,LOG_OKDYN);

/*----------------------------------------------------------------------
*  memory kommen lassen ..
*---------------------------------------------------------------------*/
wlog88i2(0,LOG_ALLOCMEMY);

/*======================================================================
*  memory fuer GS und CI (nur fuer SICCG88) 1 und 18
*=====================================================================*/
GS= (FR_DOUBLEAY) FR_CALLOC((MAXGS+1),sizeof(FR_DOUBLE));
if(GS == NULL)
  {
  wlog88i2(1,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(1,LOG_ARRAYOK);

if(ICFLAG == 1)
  {
  CI= (FR_DOUBLEAY) FR_CALLOC((MAXGS+1),sizeof(FR_DOUBLE));
  if(CI == NULL)
    {
    wlog88i2(18,LOG_ARRAYNOTOK);
    fclose(fl2);
    return(AL_NOMEMY);
    }
  else
    wlog88i2(18,LOG_ARRAYOK);
  }

/*======================================================================
*  memory fuer se,rs,fak,xi,xa 2,3,4,5,6
*=====================================================================*/
se= (FR_DOUBLEAY) FR_CALLOC((MAXESM+1),sizeof(FR_DOUBLE));
if(se == NULL)
  {
  wlog88i2(2,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(2,LOG_ARRAYOK);

rs= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
if(rs == NULL)
  {
  wlog88i2(3,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(3,LOG_ARRAYOK);

fak= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
if(fak == NULL)
  {
  wlog88i2(4,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(4,LOG_ARRAYOK);

xi= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
if(xi == NULL)
  {
  wlog88i2(5,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(5,LOG_ARRAYOK);

xa= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
if(xa == NULL)
  {
  wlog88i2(6,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(6,LOG_ARRAYOK);

/*======================================================================
*  memory fuer v,pk,zz 7,8,9
*=====================================================================*/
v= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
if(v == NULL)
  {
  wlog88i2(7,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(7,LOG_ARRAYOK);

pk= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
if(pk == NULL)
  {
  wlog88i2(8,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(8,LOG_ARRAYOK);

zz= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
if(zz == NULL)
  {
  wlog88i2(9,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(9,LOG_ARRAYOK);

/*======================================================================
*  memory fuer x, y, z 10,11,12
*=====================================================================*/
x= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(x == NULL)
  {
  wlog88i2(10,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(10,LOG_ARRAYOK);

y= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(y == NULL)
  {
  wlog88i2(11,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(11,LOG_ARRAYOK);

z= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(z == NULL)
  {
  wlog88i2(12,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(12,LOG_ARRAYOK);

/*======================================================================
*  memory fuer emod, rnue, qpara: 13,14,15
*=====================================================================*/
emod= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(emod == NULL)
  {
  wlog88i2(13,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(13,LOG_ARRAYOK);

rnue= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rnue == NULL)
  {
  wlog88i2(14,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(14,LOG_ARRAYOK);

qpara= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(qpara == NULL)
  {
  wlog88i2(15,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(15,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ip, iez, koi 16,17,20
*=====================================================================*/
ip= (FR_INT4AY) FR_CALLOC((MAXNFG+1),sizeof(FR_INT4));
if(ip == NULL)
  {
  wlog88i2(16,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(16,LOG_ARRAYOK);

iez= (FR_INT4AY) FR_CALLOC((MAXGS+1),sizeof(FR_INT4));
if(iez == NULL)
  {
  wlog88i2(17,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(17,LOG_ARRAYOK);

koi= (FR_INT4AY) FR_CALLOC((MAXKOI+1),sizeof(FR_INT4));
if(koi == NULL)
  {
  wlog88i2(20,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(20,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ifrei, ioffs, koffs, ityp 21,22,23,24
*=====================================================================*/
ifrei= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(ifrei == NULL)
  {
  wlog88i2(21,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(21,LOG_ARRAYOK);

ioffs= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(ioffs == NULL)
  {
  wlog88i2(22,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(22,LOG_ARRAYOK);

koffs= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(koffs == NULL)
  {
  wlog88i2(23,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(23,LOG_ARRAYOK);

ityp= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(ityp == NULL)
  {
  wlog88i2(24,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(24,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ivon, ibis, intord 25,26,27
*=====================================================================*/
ivon= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(ivon == NULL)
  {
  wlog88i2(25,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(25,LOG_ARRAYOK);

ibis= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(ibis == NULL)
  {
  wlog88i2(26,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(26,LOG_ARRAYOK);

intord= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(intord == NULL)
  {
  wlog88i2(27,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(27,LOG_ARRAYOK);

/*======================================================================
*  memory fuer riyy,eyy,rizz,ezz,rit,wt:28,29,30,31,32,33
*=====================================================================*/
riyy= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(riyy == NULL)
  {
  wlog88i2(28,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(28,LOG_ARRAYOK);

eyy= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(eyy == NULL)
  {
  wlog88i2(29,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(29,LOG_ARRAYOK);

rizz= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rizz == NULL)
  {
  wlog88i2(30,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(30,LOG_ARRAYOK);

ezz= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(ezz == NULL)
  {
  wlog88i2(31,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(31,LOG_ARRAYOK);

rit= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rit == NULL)
  {
  wlog88i2(32,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(32,LOG_ARRAYOK);

wt= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(wt == NULL)
  {
  wlog88i2(33,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(33,LOG_ARRAYOK);

/*======================================================================
*  memory fuer pres,tr1,tr2,nep,noi,noffs:34,35,36,37,38,39
*  Annahme: max. 8 Knoten pro Oberflaeche
*=====================================================================*/
pres= (FR_DOUBLEAY) FR_CALLOC((MAXPR+1),sizeof(FR_DOUBLE));
if(pres == NULL)
  {
  wlog88i2(34,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(34,LOG_ARRAYOK);

tr1= (FR_DOUBLEAY) FR_CALLOC((MAXPR+1),sizeof(FR_DOUBLE));
if(tr1 == NULL)
  {
  wlog88i2(35,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(35,LOG_ARRAYOK);

tr2= (FR_DOUBLEAY) FR_CALLOC((MAXPR+1),sizeof(FR_DOUBLE));
if(tr2 == NULL)
  {
  wlog88i2(36,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(36,LOG_ARRAYOK);

nep= (FR_INT4AY) FR_CALLOC((MAXPR+1),sizeof(FR_INT4));
if(nep == NULL)
  {
  wlog88i2(37,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(37,LOG_ARRAYOK);

noi= (FR_INT4AY) FR_CALLOC((MAXPR*8+1),sizeof(FR_INT4));
if(noi == NULL)
  {
  wlog88i2(38,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(38,LOG_ARRAYOK);

noffs= (FR_INT4AY) FR_CALLOC((MAXPR+1),sizeof(FR_INT4));
if(noffs == NULL)
  {
  wlog88i2(39,LOG_ARRAYNOTOK);
  fclose(fl2);
  return(AL_NOMEMY);
  }
else
  wlog88i2(39,LOG_ARRAYOK);

/***********************************************************************
* alles o.k. 
***********************************************************************/
IDYNMEM =   (MAXGS+1) *sizeof(FR_DOUBLE);     /* GS */
if(ICFLAG ==1)
  IDYNMEM+= (MAXGS+1) *sizeof(FR_DOUBLE);     /* CI */

IDYNMEM+=   (MAXESM+1)*sizeof(FR_DOUBLE);     /* se */
IDYNMEM+= 7*(MAXNFG+1)*sizeof(FR_DOUBLE);     /* rs,fak,xi,xa,v,pk,zz*/
IDYNMEM+= 3*(MAXK+1)  *sizeof(FR_DOUBLE);     /* x,y,z */
IDYNMEM+= 3*(MAXNEG+1)*sizeof(FR_DOUBLE);     /* emod, rnue, qpara */
IDYNMEM+=   (MAXNFG+1)*sizeof(FR_INT4);       /* ip */
IDYNMEM+=   (MAXGS+1) *sizeof(FR_INT4);       /* iez */
IDYNMEM+=   (MAXKOI+1)*sizeof(FR_INT4);       /* koi */
IDYNMEM+= 2*(MAXK+1)  *sizeof(FR_INT4);       /* ifrei, ioffs */
IDYNMEM+= 2*(MAXE+1)  *sizeof(FR_INT4);       /* koffs, ityp */
IDYNMEM+= 3*(MAXNEG+1)*sizeof(FR_INT4);       /* ivon,ibis,intord */
IDYNMEM+= 6*(MAXNEG+1)*sizeof(FR_DOUBLE);     /* riyy,eyy,rizz,ezz,rit,wt */
IDYNMEM+=10*(MAXPR+1) *sizeof(FR_INT4);       /* nep,noi,noffs */
IDYNMEM+= 3*(MAXPR+1) *sizeof(FR_DOUBLE);     /* pres,tr1,tr2 */

IDYNMEM/= 1048576;   /* in MegaByte */

wlog88i2(IDYNMEM,LOG_SUMMEMY);
wlog88i2(0,LOG_EXITDYN88I2);

return(0);
}
