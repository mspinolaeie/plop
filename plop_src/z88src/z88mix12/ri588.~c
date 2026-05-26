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
* ri588
* 29.9.2005 Rieg 
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88f.h>
#include <stdio.h>    /* fopen,fclose,fprintf,fgets,sscanf */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88f.h>
#include <stdio.h>    /* fopen,fclose,fprintf,fgets,sscanf */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88f(FR_INT4,int);
int wlog88f(FR_INT4,int);

/***********************************************************************
* hier beginnt Function ri588
* ri588.c liest z88i5.txt ein
* hier wird File z88i5.txt geoeffnet 
***********************************************************************/
int ri588(void)
{
extern FILE *fi5,*fwlo;
extern char ci5[];

extern FR_DOUBLEAY pres;
extern FR_DOUBLEAY tr1;
extern FR_DOUBLEAY tr2;

extern FR_INT4AY noi;
extern FR_INT4AY noffs;
extern FR_INT4AY ityp;
extern FR_INT4AY nep;

extern FR_INT4 npr;
extern FR_INT4 MAXPR;

FR_INT4 i,idummy,nofold= 0;

char cline[256];

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/
wrim88f(0,TX_REAI5);

/*----------------------------------------------------------------------
* Oeffnen Z88I5.TXT
*---------------------------------------------------------------------*/
wlog88f(0,LOG_BRI588);
fi5= fopen(ci5,"r");
if(fi5 == NULL)
  {
  wlog88f(0,LOG_NOI5);
  fclose(fwlo);
  return(AL_NOI5);
  }

rewind(fi5);

/*----------------------------------------------------------------------
* Einlesen der allgemeinen Strukturdaten
*---------------------------------------------------------------------*/
fgets(cline,256,fi5);
sscanf(cline,"%ld",&npr);

/***********************************************************************
* Einlesen des Lastvektors
***********************************************************************/
for(i= 1; i <= npr; i++)
  {
  fgets(cline,256,fi5);
  sscanf(cline,"%ld",&nep[i]); 

/*----------------------------------------------------------------------
* den koinzidenzvektor noi & den zugehoerigen pointervektor noffs
* auffuellen
*---------------------------------------------------------------------*/

/*======================================================================
* Elementtypen 7, 8, 14, 15
*=====================================================================*/
  if(ityp[nep[i]]== 7  || ityp[nep[i]]== 8 ||
     ityp[nep[i]]== 14 || ityp[nep[i]]== 15) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    if(noffs[i]+3 > MAXPR)
      {
      wlog88f(MAXPR,LOG_EXMAXPR);
      fclose(fwlo);
      return(AL_EXMAXPR);
      }

#ifdef FR_XQUAD
    sscanf(cline,"%ld %Lg %Lg %ld %ld %ld",
    &idummy,&pres[i],&tr1[i],
    &noi[noffs[i]   ],&noi[noffs[i] +1],&noi[noffs[i] +2]);  
#endif

#ifdef FR_XDOUB
    sscanf(cline,"%ld %lf %lf %ld %ld %ld",
    &idummy,&pres[i],&tr1[i],
    &noi[noffs[i]   ],&noi[noffs[i] +1],&noi[noffs[i] +2]); 
#endif
    nofold= 3;
    }

/*======================================================================
* Elementtyp 17
*=====================================================================*/
  if(ityp[nep[i]]== 17) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    if(noffs[i]+3 > MAXPR)
      {
      wlog88f(MAXPR,LOG_EXMAXPR);
      fclose(fwlo);
      return(AL_EXMAXPR);
      }

#ifdef FR_XQUAD 
    sscanf(cline,"%ld %Lg %ld %ld %ld",
    &idummy,&pres[i],
    &noi[noffs[i]   ],&noi[noffs[i] +1],&noi[noffs[i] +2]); 
#endif

#ifdef FR_XDOUB
    sscanf(cline,"%ld %lf %ld %ld %ld",
    &idummy,&pres[i],
    &noi[noffs[i]   ],&noi[noffs[i] +1],&noi[noffs[i] +2]);  
#endif

    nofold= 3;
    }
          
/*======================================================================
* Elementtyp 16
*=====================================================================*/
  if(ityp[nep[i]]== 16) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    if(noffs[i]+6 > MAXPR)
      {
      wlog88f(MAXPR,LOG_EXMAXPR);
      fclose(fwlo);
      return(AL_EXMAXPR);
      }

#ifdef FR_XQUAD 
    sscanf(cline,"%ld %Lg %ld %ld %ld %ld %ld %ld",
    &idummy,&pres[i],
    &noi[noffs[i]   ], &noi[noffs[i] +1], 
    &noi[noffs[i] +2], &noi[noffs[i] +3], 
    &noi[noffs[i] +4], &noi[noffs[i] +5]); 
#endif

#ifdef FR_XDOUB
    sscanf(cline,"%ld %lf %ld %ld %ld %ld %ld %ld",
    &idummy,&pres[i],
    &noi[noffs[i]   ], &noi[noffs[i] +1], 
    &noi[noffs[i] +2], &noi[noffs[i] +3], 
    &noi[noffs[i] +4], &noi[noffs[i] +5]); 
#endif

    nofold= 6;
    }

/*======================================================================
* Elementtyp 10
*=====================================================================*/
  if(ityp[nep[i]]== 10) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    if(noffs[i]+8 > MAXPR)
      {
      wlog88f(MAXPR,LOG_EXMAXPR);
      fclose(fwlo);
      return(AL_EXMAXPR);
      }
 
#ifdef FR_XQUAD 
    sscanf(cline,"%ld %Lg %Lg %Lg %ld %ld %ld %ld %ld %ld %ld %ld",
    &idummy,&pres[i],&tr1[i],&tr2[i],
    &noi[noffs[i]   ], &noi[noffs[i] +1], 
    &noi[noffs[i] +2], &noi[noffs[i] +3], 
    &noi[noffs[i] +4], &noi[noffs[i] +5],
    &noi[noffs[i] +6], &noi[noffs[i] +7]); 
#endif

#ifdef FR_XDOUB
    sscanf(cline,"%ld %lf %lf %lf %ld %ld %ld %ld %ld %ld %ld %ld",
    &idummy,&pres[i],&tr1[i],&tr2[i],
    &noi[noffs[i]   ], &noi[noffs[i] +1], 
    &noi[noffs[i] +2], &noi[noffs[i] +3], 
    &noi[noffs[i] +4], &noi[noffs[i] +5],
    &noi[noffs[i] +6], &noi[noffs[i] +7]); 
#endif

    nofold= 8;
    }

/*======================================================================
* Elementtyp 1
*=====================================================================*/
  if(ityp[nep[i]]== 1) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    if(noffs[i]+4 > MAXPR)
      {
      wlog88f(MAXPR,LOG_EXMAXPR);
      fclose(fwlo);
      return(AL_EXMAXPR);
      }

#ifdef FR_XQUAD 
    sscanf(cline,"%ld %Lg %Lg %Lg %ld %ld %ld %ld",
    &idummy,&pres[i],&tr1[i],&tr2[i],
    &noi[noffs[i]   ], &noi[noffs[i] +1], 
    &noi[noffs[i] +2], &noi[noffs[i] +3]); 
#endif

#ifdef FR_XDOUB
    sscanf(cline,"%ld %lf %lf %lf %ld %ld %ld %ld",
    &idummy,&pres[i],&tr1[i],&tr2[i],
    &noi[noffs[i]   ], &noi[noffs[i] +1], 
    &noi[noffs[i] +2], &noi[noffs[i] +3]); 
#endif

    nofold= 4;
    }

/*======================================================================
* Elementtypen 11 und 12
*=====================================================================*/
  if(ityp[nep[i]]== 11 || ityp[nep[i]]== 12) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    if(noffs[i]+4 > MAXPR)
      {
      wlog88f(MAXPR,LOG_EXMAXPR);
      fclose(fwlo);
      return(AL_EXMAXPR);
      }
 
#ifdef FR_XQUAD 
    sscanf(cline,"%ld %Lg %Lg %ld %ld %ld %ld",
    &idummy,&pres[i],&tr1[i],
    &noi[noffs[i]   ], &noi[noffs[i] +1], 
    &noi[noffs[i] +2], &noi[noffs[i] +3]); 
#endif

#ifdef FR_XDOUB
    sscanf(cline,"%ld %lf %lf %ld %ld %ld %ld",
    &idummy,&pres[i],&tr1[i],
    &noi[noffs[i]   ], &noi[noffs[i] +1], 
    &noi[noffs[i] +2], &noi[noffs[i] +3]); 
#endif

    nofold= 4;
    }

/*======================================================================
* Elementtyp 18,19 und 20
*=====================================================================*/
  if(ityp[nep[i]]== 18 || ityp[nep[i]]== 19 || ityp[nep[i]]== 20) 
    {
#ifdef FR_XQUAD
    sscanf(cline,"%ld %Lg",&idummy,&pres[i]); 
#endif

#ifdef FR_XDOUB
    sscanf(cline,"%ld %lf",&idummy,&pres[i]); 
#endif
    }

  } /* Ende Schleife ueber alle Flaechenlasten */

/*----------------------------------------------------------------------
* Z88I5.TXT schliessen 
*---------------------------------------------------------------------*/
fclose(fi5);

wlog88f(0,LOG_EXITRI188);
return (0);
}
