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
* Compilerunit rw2y88f.c enthaelt:
* - w2y88f : beschreibt Z88O2.BNY
* - r2y88f : liest Z88O2.BNY
* und oeffnet und schliesst diese Files
* 23.3.2002 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88f.h>
#include <stdio.h>    /* FILE,fopen,fclose,fprintf,fwrite */
                      /* fread,rewind,NULL */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88f.h>
#include <stdio.h>    /* FILE,fopen,fclose,fprintf,fwrite */
                      /* fread,rewind,NULL */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88f(FR_INT4,int);
int wlog88f(FR_INT4,int);

/***********************************************************************
* hier beginnt Function w2y88f
***********************************************************************/
int w2y88f(void)
{
extern FILE *f2y,*fwlo;
extern char c2y[];

extern FR_DOUBLEAY gs;

extern FR_INT4AY ip;
extern FR_INT4AY ifrei; 
extern FR_INT4AY ioffs; 

extern FR_INT4 nkp,nfg;

FR_INT4 i,nfgp1,ngsp1,j1000,jfull,jrest;

/***********************************************************************
* Start Function: Oeffnen der Files Z88O2.TXT
***********************************************************************/
f2y= fopen(c2y,"w+b");
if(f2y == NULL)
  {
  wlog88f(0,LOG_NO2Y);
  fclose(fwlo);
  return(AL_NO2Y);
  }

rewind(f2y);

/**********************************************************************
* Beschreiben des Binaerfiles Z88O2.BNY
**********************************************************************/
wrim88f(0,TX_WRI2Y);
wlog88f(0,LOG_WRI2Y);

nfgp1= nfg+1;
ngsp1= ip[nfgp1];

/*----------------------------------------------------------------------
* ngsp1 (=ip[nfgp1]) schreiben
*---------------------------------------------------------------------*/
fwrite(&ngsp1, sizeof(FR_INT4),1,f2y);

/*----------------------------------------------------------------------
* Vektor gs (Upper- Skyline der Gesamtsteifigkeitsmatrix) schreiben
*---------------------------------------------------------------------*/
j1000= ngsp1/1000;  /* immer 1000 Werte mit einem fwrite wegschreiben */
jfull= j1000*1000;  /* Anzahl der 1000er Durchlaeufe                  */
jrest= ngsp1-jfull; /* Rest, der unter 1000                           */

for(i = 1;i <= j1000;i++)
  fwrite(&gs[(i-1)*1000+1], sizeof(FR_DOUBLE),1000,f2y);
if(jrest > 0)
  fwrite(&gs[jfull+1], sizeof(FR_DOUBLE),(FR_SIZERW)jrest,f2y);

/*----------------------------------------------------------------------
* nfg schreiben
*---------------------------------------------------------------------*/
fwrite(&nfg, sizeof(FR_INT4),1,f2y);

/*----------------------------------------------------------------------
* Pointervektor ip schreiben
*---------------------------------------------------------------------*/
for(i = 1;i <= nfgp1;i++)
  fwrite(&ip[i], sizeof(FR_INT4),1,f2y);

/*----------------------------------------------------------------------
* nkp schreiben
*---------------------------------------------------------------------*/
fwrite(&nkp, sizeof(FR_INT4),1,f2y);

/*----------------------------------------------------------------------
* Offsetvektor ioffs und Freiheitsgradvektor ifrei schreiben
*---------------------------------------------------------------------*/
for(i = 1;i <= nkp;i++)
  {
  fwrite(&ioffs[i], sizeof(FR_INT4),1,f2y);
  fwrite(&ifrei[i], sizeof(FR_INT4),1,f2y);
  }

/**********************************************************************
* File Z88O2.BNY schliessen, Ende
**********************************************************************/
fclose(f2y);

wlog88f(0,LOG_WRI2YOK);

return(0);
}

/***********************************************************************
* hier beginnt Function r2y88f
***********************************************************************/
int r2y88f(void)
{
extern FILE *f2y,*fwlo;
extern char c2y[];

extern FR_DOUBLEAY gs;

extern FR_INT4AY ip;
extern FR_INT4AY ifrei; 
extern FR_INT4AY ioffs; 

extern FR_INT4 nkp,nfg;

FR_INT4 i,nfgp1,ngsp1,j1000,jfull,jrest;

/***********************************************************************
* Start Function: Oeffnen der Files Z88O2.TXT
***********************************************************************/
f2y= fopen(c2y,"rb");
if(f2y == NULL)
  {
  wlog88f(0,LOG_NO2Y);
  fclose(fwlo);
  return(AL_NO2Y);
  }

rewind(f2y);

/**********************************************************************
* Belesen des Binaerfiles Z88O2.BNY
**********************************************************************/
wrim88f(0,TX_REA2Y);
wlog88f(0,LOG_REA2Y);

/*----------------------------------------------------------------------
* ngsp1 (=ip[nfgp1]) lesen
*---------------------------------------------------------------------*/
fread(&ngsp1, sizeof(FR_INT4),1,f2y);

/*----------------------------------------------------------------------
* Vektor gs (Upper- Skyline der Gesamtsteifigkeitsmatrix) lesen
*---------------------------------------------------------------------*/
j1000= ngsp1/1000;  /* immer 1000 Werte mit einem fread weglesen */
jfull= j1000*1000;  /* Anzahl der 1000er Durchlaeufe                  */
jrest= ngsp1-jfull; /* Rest, der unter 1000                           */

for(i = 1;i <= j1000;i++)
  fread(&gs[(i-1)*1000+1], sizeof(FR_DOUBLE),1000,f2y);
if(jrest > 0)
  fread(&gs[jfull+1], sizeof(FR_DOUBLE),(FR_SIZERW)jrest,f2y);

/*----------------------------------------------------------------------
* nfg lesen
*---------------------------------------------------------------------*/
fread(&nfg, sizeof(FR_INT4),1,f2y);
nfgp1= nfg+1;

/*----------------------------------------------------------------------
* Pointervektor ip lesen
*---------------------------------------------------------------------*/
for(i = 1;i <= nfgp1;i++)
  fread(&ip[i], sizeof(FR_INT4),1,f2y);

/*----------------------------------------------------------------------
* nkp lesen
*---------------------------------------------------------------------*/
fread(&nkp, sizeof(FR_INT4),1,f2y);

/*----------------------------------------------------------------------
* Offsetvektor ioffs und Freiheitsgradvektor ifrei lesen
*---------------------------------------------------------------------*/
for(i = 1;i <= nkp;i++)
  {
  fread(&ioffs[i], sizeof(FR_INT4),1,f2y);
  fread(&ifrei[i], sizeof(FR_INT4),1,f2y);
  }

/**********************************************************************
* File Z88O2.BNY schliessen, Ende
**********************************************************************/
fclose(f2y);

wlog88f(0,LOG_REA2YOK);

return(0);
}
