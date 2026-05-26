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
* r4y88i : liest Z88O4.BNY
* 23.3.02 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88i.h>
#include <stdio.h>    /* FILE,fopen,fclose,fprintf,fwrite */
                      /* fread,rewind,NULL */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88i.h>
#include <stdio.h>    /* FILE,fopen,fclose,fprintf,fwrite */
                      /* fread,rewind,NULL */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88i(FR_INT4,int);
int wlog88i2(FR_INT4,int);

/***********************************************************************
* hier beginnt Function r4y88i
***********************************************************************/
int r4y88i(void)
{
extern FILE *f4y,*fl2;
extern char c4y[];

extern FR_INT4AY ip;
extern FR_INT4AY iez;

extern FR_INT4 kfoun,nfg;

/***********************************************************************
* Start Function: Oeffnen der Files Z88O4.BNY
***********************************************************************/
f4y= fopen(c4y,"rb");
if(f4y == NULL)
  {
  wlog88i2(0,LOG_NO4Y);
  fclose(fl2);
  return(AL_NO4Y);
  }

rewind(f4y);

/**********************************************************************
* Einlesen des Binaerfiles Z88O4.BNY
**********************************************************************/
wrim88i(0,TX_REA4Y);
wlog88i2(0,LOG_REA4Y);

/*----------------------------------------------------------------------
* nfg lesen
*---------------------------------------------------------------------*/
fread(&nfg,sizeof(FR_INT4),1,f4y);

/*----------------------------------------------------------------------
* kfoun lesen
*---------------------------------------------------------------------*/
fread(&kfoun,sizeof(FR_INT4),1,f4y);

/*----------------------------------------------------------------------
* Diagonal- Pointervektor ip lesen
*---------------------------------------------------------------------*/
fread(&ip[0],sizeof(FR_INT4),nfg+1,f4y);

/*----------------------------------------------------------------------
* Spaltenindex- Pointervektor iez lesen
*---------------------------------------------------------------------*/
fread(&iez[1],sizeof(FR_INT4),ip[nfg],f4y);

/**********************************************************************
* File Z88O4.BNY schliessen, Ende
**********************************************************************/
fclose(f4y);

wlog88i2(0,LOG_REA4YOK);

return(0);
}
