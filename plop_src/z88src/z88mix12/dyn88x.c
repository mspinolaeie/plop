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
*  function dyn88x liest z88.dyn aus und laesst memory kommen
*  hier wird Files Z88.DYN erneut geoeffnet (vorher schon in lan88x)
*  27.9.2005 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
                     /* rewind                              */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
* Fuer Windows95
***********************************************************************/
#ifdef FR_WIN95
#include <z88x.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
                     /* rewind                              */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wlog88x(FR_INT4,int);

/***********************************************************************
*  hier beginnt Function dyn88x
***********************************************************************/
int dyn88x(void)
{
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
extern FR_DOUBLEAY wert;
extern FR_DOUBLEAY pres;
extern FR_DOUBLEAY tr1;
extern FR_DOUBLEAY tr2;

extern FR_INT4AY koi;
extern FR_INT4AY ifrei; 
extern FR_INT4AY ioffs;
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;
extern FR_INT4AY itypfe;
extern FR_INT4AY ivon;
extern FR_INT4AY ibis;
extern FR_INT4AY intord;
extern FR_INT4AY jel;
extern FR_INT4AY iel;
extern FR_INT4AY kel;
extern FR_INT4AY nkn;
extern FR_INT4AY ifg;
extern FR_INT4AY irflag;
extern FR_INT4AY nep;
extern FR_INT4AY noi;
extern FR_INT4AY noffs;

extern FR_CHARAY cjmode;
extern FR_CHARAY cimode;
extern FR_CHARAY ckmode;

extern FILE *fdyn, *fwlo;
extern char cdyn[];

extern FR_INT4 IDYNMEM,ICFLAG;
extern FR_INT4 MAXNFG,MAXK,MAXE,MAXKOI,MAXNEG,MAXPR;

char cline[256], cdummy[80];
  
/*----------------------------------------------------------------------
*  Eintragungen in Z88X.LOG
*---------------------------------------------------------------------*/
#ifdef FR_UNIX
if     (ICFLAG == 1) wlog88x(1,LOG_CFLAGI1TX);
else if(ICFLAG == 2) wlog88x(2,LOG_CFLAGIATX);
else if(ICFLAG == 3) wlog88x(3,LOG_CFLAGNITX);
else if(ICFLAG == 4) wlog88x(4,LOG_CFLAGI1FX);
else if(ICFLAG == 5) wlog88x(5,LOG_CFLAGIAFX);
else if(ICFLAG == 6) wlog88x(6,LOG_CFLAGNIFX);
#endif

/*----------------------------------------------------------------------
*  dyn- datei z88.dyn oeffnen
*---------------------------------------------------------------------*/
wlog88x(0,LOG_OPENZ88DYN);

fdyn= fopen(cdyn,"r");
if(fdyn == NULL)
  {
  wlog88x(0,LOG_NODYN);
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
        if( (strstr(cline,"MAXPR"))!= NULL)         /* Lesen MAXPR */
          sscanf(cline,"%s %ld",cdummy,&MAXPR);
        }
      while( (strstr(cline,"COMMON END"))== NULL);
      }                                             /* end if COMMON START */

    }
  while( (strstr(cline,"DYNAMIC END"))== NULL);     
    
  }                                                 /* end if DYNAMIC START */
else
  {
  wlog88x(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

if(MAXKOI <= 0 || MAXK <= 0 || MAXE <= 0 || MAXNFG <= 0 || 
   MAXNEG <= 0 || MAXPR <= 0)
  {
  wlog88x(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

/*----------------------------------------------------------------------
*  korrekt gelesen, file fdyn schliessen
*---------------------------------------------------------------------*/
fclose(fdyn);

wlog88x(MAXKOI,LOG_MAXKOI);
wlog88x(MAXK,LOG_MAXK);
wlog88x(MAXE,LOG_MAXE);
wlog88x(MAXNFG,LOG_MAXNFG);
wlog88x(MAXNEG,LOG_MAXNEG);
wlog88x(MAXPR,LOG_MAXPR);

wlog88x(0,LOG_OKDYN);

/*----------------------------------------------------------------------
*  memory kommen lassen ..
*---------------------------------------------------------------------*/
wlog88x(0,LOG_ALLOCMEMY);

/*======================================================================
*  memory fuer x, y, z 5,6,7
*=====================================================================*/
x= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(x == NULL)
  {
  wlog88x(5,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(5,LOG_ARRAYOK);

y= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(y == NULL)
  {
  wlog88x(6,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(6,LOG_ARRAYOK);

z= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(z == NULL)
  {
  wlog88x(7,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(7,LOG_ARRAYOK);

/*======================================================================
*  memory fuer emod, rnue, qpara 8,9,10
*=====================================================================*/
emod= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(emod == NULL)
  {
  wlog88x(8,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(8,LOG_ARRAYOK);

rnue= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(rnue == NULL)
  {
  wlog88x(9,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(9,LOG_ARRAYOK);

qpara= (FR_DOUBLEAY) FR_CALLOC((MAXNEG+1),sizeof(FR_DOUBLE));
if(qpara == NULL)
  {
  wlog88x(10,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(10,LOG_ARRAYOK);

/*======================================================================
*  memory fuer koi 11
*=====================================================================*/
koi= (FR_INT4AY) FR_CALLOC((MAXKOI+1),sizeof(FR_INT4));
if(koi == NULL)
  {
  wlog88x(11,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(11,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ifrei, ioffs, koffs, ityp, itypfe 12,13,14,15,16
*=====================================================================*/
ifrei= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(ifrei == NULL)
  {
  wlog88x(12,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(12,LOG_ARRAYOK);

ioffs= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(ioffs == NULL)
  {
  wlog88x(13,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(13,LOG_ARRAYOK);

koffs= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(koffs == NULL)
  {
  wlog88x(14,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(14,LOG_ARRAYOK);

ityp= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(ityp == NULL)
  {
  wlog88x(15,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(15,LOG_ARRAYOK);

itypfe= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(ityp == NULL)
  {
  wlog88x(16,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(16,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ivon, ibis, intord 17,18,19
*=====================================================================*/
ivon= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(ivon == NULL)
  {
  wlog88x(17,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(17,LOG_ARRAYOK);

ibis= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(ibis == NULL)
  {
  wlog88x(18,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(18,LOG_ARRAYOK);

intord= (FR_INT4AY) FR_CALLOC((MAXNEG+1),sizeof(FR_INT4));
if(intord == NULL)
  {
  wlog88x(19,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(19,LOG_ARRAYOK);

/*======================================================================
* Memory fuer riyy, eyy, rizz, ezz, rit, wt: 20,21,22,23,24,25
*=====================================================================*/
riyy= (FR_DOUBLEAY) FR_CALLOC(MAXNEG+1,sizeof(FR_DOUBLE));
if(riyy == NULL)
  {
  wlog88x(20,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(20,LOG_ARRAYOK);

eyy= (FR_DOUBLEAY) FR_CALLOC(MAXNEG+1,sizeof(FR_DOUBLE));
if(eyy == NULL)
  {
  wlog88x(21,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(21,LOG_ARRAYOK);

rizz= (FR_DOUBLEAY) FR_CALLOC(MAXNEG+1,sizeof(FR_DOUBLE));
if(rizz == NULL)
  {
  wlog88x(22,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(22,LOG_ARRAYOK);

ezz= (FR_DOUBLEAY) FR_CALLOC(MAXNEG+1,sizeof(FR_DOUBLE));
if(ezz == NULL)
  {
  wlog88x(23,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(23,LOG_ARRAYOK);

rit= (FR_DOUBLEAY) FR_CALLOC(MAXNEG+1,sizeof(FR_DOUBLE));
if(rit == NULL)
  {
  wlog88x(24,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(24,LOG_ARRAYOK);

wt= (FR_DOUBLEAY) FR_CALLOC(MAXNEG+1,sizeof(FR_DOUBLE));
if(wt == NULL)
  {
  wlog88x(25,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(25,LOG_ARRAYOK);

/*======================================================================
* Memory fuer jel, iel, kel: 26,27,28
*=====================================================================*/
jel= (FR_INT4AY) FR_CALLOC(MAXE+1,sizeof(FR_INT4));
if(jel == NULL)
  {
  wlog88x(26,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(26,LOG_ARRAYOK);

iel= (FR_INT4AY) FR_CALLOC(MAXE+1,sizeof(FR_INT4));
if(iel == NULL)
  {
  wlog88x(27,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(27,LOG_ARRAYOK);

kel= (FR_INT4AY) FR_CALLOC(MAXE+1,sizeof(FR_INT4));
if(kel == NULL)
  {
  wlog88x(28,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(28,LOG_ARRAYOK);

/*======================================================================
* Memory fuer cjmode, cimode, ckmode: 29,30,31
*=====================================================================*/
cjmode= (FR_CHARAY) FR_CALLOC(MAXE+1,sizeof(char));
if(cjmode == NULL)
  {
  wlog88x(29,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(29,LOG_ARRAYOK);

cimode= (FR_CHARAY) FR_CALLOC(MAXE+1,sizeof(char));
if(cimode == NULL)
  {
  wlog88x(30,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(30,LOG_ARRAYOK);

ckmode= (FR_CHARAY) FR_CALLOC(MAXE+1,sizeof(char));
if(ckmode == NULL)
  {
  wlog88x(31,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(31,LOG_ARRAYOK);

/*======================================================================
* Memory fuer nkn,ifg,irflag:32,33,34
*=====================================================================*/
nkn= (FR_INT4AY) FR_CALLOC(MAXNFG+1,sizeof(FR_INT4));
if(nkn == NULL)
  {
  wlog88x(32,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(32,LOG_ARRAYOK);

ifg= (FR_INT4AY) FR_CALLOC(MAXNFG+1,sizeof(FR_INT4));
if(ifg == NULL)
  {
  wlog88x(33,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(33,LOG_ARRAYOK);

irflag= (FR_INT4AY) FR_CALLOC(MAXNFG+1,sizeof(FR_INT4));
if(irflag == NULL)
  {
  wlog88x(34,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(34,LOG_ARRAYOK);

/*======================================================================
* Memory fuer wert: 35
*=====================================================================*/
wert= (FR_DOUBLEAY) FR_CALLOC(MAXNFG+1,sizeof(FR_DOUBLE));
if(wert == NULL)
  {
  wlog88x(35,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(35,LOG_ARRAYOK);

/*======================================================================
*  memory fuer pres,tr1,tr2,nep,noi,noffs:36,37,38,39,40,41
*  Annahme: max. 8 Knoten pro Oberflaeche
*=====================================================================*/
pres= (FR_DOUBLEAY) FR_CALLOC((MAXPR+1),sizeof(FR_DOUBLE));
if(pres == NULL)
  {
  wlog88x(36,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(36,LOG_ARRAYOK);

tr1= (FR_DOUBLEAY) FR_CALLOC((MAXPR+1),sizeof(FR_DOUBLE));
if(tr1 == NULL)
  {
  wlog88x(37,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(37,LOG_ARRAYOK);

tr2= (FR_DOUBLEAY) FR_CALLOC((MAXPR+1),sizeof(FR_DOUBLE));
if(tr2 == NULL)
  {
  wlog88x(38,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(38,LOG_ARRAYOK);

nep= (FR_INT4AY) FR_CALLOC((MAXPR+1),sizeof(FR_INT4));
if(nep == NULL)
  {
  wlog88x(39,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(39,LOG_ARRAYOK);

noi= (FR_INT4AY) FR_CALLOC((MAXPR*8+1),sizeof(FR_INT4));
if(noi == NULL)
  {
  wlog88x(40,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(40,LOG_ARRAYOK);

noffs= (FR_INT4AY) FR_CALLOC((MAXPR+1),sizeof(FR_INT4));
if(noffs == NULL)
  {
  wlog88x(41,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88x(41,LOG_ARRAYOK);

/***********************************************************************
* alles o.k. 
***********************************************************************/
IDYNMEM+= 3*(MAXK+1)*sizeof(FR_DOUBLE);       /* x,y,z */
IDYNMEM+= 3*(MAXNEG+1)*sizeof(FR_DOUBLE);     /* emod,rnue,qpara */
IDYNMEM+=   (MAXKOI+1)*sizeof(FR_INT4);       /* koi */
IDYNMEM+= 2*(MAXK+1)*sizeof(FR_INT4);         /* ifrei,ioffs */
IDYNMEM+= 3*(MAXE+1)*sizeof(FR_INT4);         /* koffs,ityp,itypfe */
IDYNMEM+= 3*(MAXNEG+1)*sizeof(FR_INT4);       /* ivon,ibis,intord */
IDYNMEM+= 6*(MAXNEG+1)*sizeof(FR_DOUBLE);     /* riyy,eyy,rizz,ezz.. */
IDYNMEM+= 3*(MAXE+1)*sizeof(FR_INT4);         /* jel,iel,kel */
IDYNMEM+= 3*(MAXE+1)*sizeof(char);            /* cimode,cjmode,ckmode */
IDYNMEM+= 3*(MAXNFG+1)*sizeof(FR_INT4);       /* nkn,ifg,irflag */
IDYNMEM+=   (MAXNFG+1)*sizeof(FR_DOUBLE);     /* wert */
IDYNMEM+=10*(MAXPR+1) *sizeof(FR_INT4);       /* nep,noi,noffs */
IDYNMEM+= 3*(MAXPR+1) *sizeof(FR_DOUBLE);     /* pres,tr1,tr2 */

wlog88x(IDYNMEM,LOG_SUMMEMY);
wlog88x(0,LOG_EXITDYN88X);

return(0);
}
