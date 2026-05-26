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
* Diese Compilerunit enthaelt:
* scal88
* choy88 mit Jennings- Speicherung
* Skalierung und Gleichungsloeser nach H.R.Schwarz
* 29.9.2005 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88f.h>
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88f.h>
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88f(FR_INT4,int);
int wlog88f(FR_INT4,int);

/***********************************************************************
* hier beginnt Function scal88
***********************************************************************/
int scal88(void)
{
extern FR_DOUBLEAY gs;
extern FR_DOUBLEAY rs;
extern FR_DOUBLEAY fak;

extern FR_INT4AY ip;

extern FR_INT4 nfg;

FR_INT4 i,j,k,jstart,jstop;

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/

/***********************************************************************
* Scalierungsfaktoren berechnen, rechte Seite umrechnen, Matrix skal.
***********************************************************************/
for(i = 1;i <= nfg;i++)
  {
  if(gs[ip[i]] <= 0.) 
    {
    wlog88f(i,LOG_DIAGNULL);
    return(AL_DIAGNULL);
    }
  fak[i]= 1. / FR_SQRT( gs[ip[i]] );
  rs[i] *= fak[i];
  gs[ip[i]]= 1.;
  
  if(i == 1) continue;
  
  jstart=ip[i-1] + 1; /* Start der inversen Skyline in der Zeile i */
  jstop= ip[i]   - 1; /* Zeile bis Diagonalelement der Zeile i */

  k= jstart - jstop + i - 1;
  
  for(j= jstart; j <= jstop; j++)
    {
    gs[j] *= fak[i] * fak[k];
    k++; 
    }  
  }

/**********************************************************************/
return(0);
}
 
/***********************************************************************
* Function choy88 loest Gleichungssysteme nach der Methode von
* Cholesky mit in-situ Speicherung
***********************************************************************/ 
/***********************************************************************
* hier beginnt Function choy88
***********************************************************************/
int choy88(void)
{
extern FR_DOUBLEAY gs;
extern FR_DOUBLEAY rs;

extern FR_INT4AY ip;

extern FR_INT4 nfg;

FR_DOUBLE sum;
FR_INT4 j,i,m,k,i0,j0,li,lj;

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/

/***********************************************************************
* Cholesky-Zerlegung
***********************************************************************/
gs[1]= FR_SQRT(gs[1]);

for(i = 2;i <= nfg;i++)
  {
  wrim88f(i,TX_CHOJ);
  i0= ip[i] - i;
  li= ip[i-1] + 1 - i0;
  for(j = li;j <= i;j++)
    {
    j0= ip[j] - j;
    sum=  gs[i0+j];
    lj= 1;

    if(j > 1) 
      lj= ip[j-1] - j0 + 1;
      
    if(li >= lj) m= li;
    else         m= lj;
       
    for(k = m;k <= j-1;k++) 
      sum -= gs[i0+k] * gs[j0+k];
      
    if(j < i)
      gs[i0+j]= sum / gs[ip[j]];
    else
      gs[ip[i]]= FR_SQRT(sum);    
    }
  }

/***********************************************************************
* Vorwaertseinsetzen
***********************************************************************/
wrim88f(0,TX_VORW);
wlog88f(0,LOG_VORW);

rs[1]= rs[1] / gs[1];
for(i= 2;i <= nfg;i++)
  {
  sum= rs[i];
  i0= ip[i] - i;
  li= ip[i-1] + 1 - i0;
  for(j= li;j <= i-1;j++)
    sum -= gs[i0+j] * rs[j];
  rs[i]= sum / gs[ip[i]];    
  }
 
/***********************************************************************
* Ruechwaertseinsetzen
***********************************************************************/
wrim88f(0,TX_RUECKW);
wlog88f(0,LOG_RUECKW);

for(i= nfg;i >= 2;i--)
  {
  rs[i] = rs[i] / gs[ip[i]];
  i0= ip[i] - i;
  li= ip[i-1] + 1 - i0;
  for(j= li;j <= i-1;j++)
    rs[j] -= gs[i0+j] * rs[i];
  }
rs[1]= rs[1] / gs[1];

return(0);
}
