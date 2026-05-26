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
* wria88x.c beschreibt Z88I1.TXT,Z88NI.TXT,Z88I2.TXT und Z88I3.TXT
* und oeffnet und schliesst diese Files
* 4.10.2005 Rieg 
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fprintf,fwrite */
                     /* rewind */
#endif

/***********************************************************************
* Fuer Windows95
***********************************************************************/
#ifdef FR_WIN95
#include <z88x.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fprintf,fwrite */
                     /* rewind */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88x(FR_INT4,int);
int wlog88x(FR_INT4,int);

/***********************************************************************
* hier beginnt Function wria88x
***********************************************************************/
int wria88x(void)
{
extern FILE *fz88,*fi2,*fi3,*fi5,*fwlo;

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
extern FR_INT4AY koffs;
extern FR_INT4AY ifrei;
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
extern FR_INT4AY noi;
extern FR_INT4AY noffs;
extern FR_INT4AY nep;

extern FR_CHARAY cjmode;
extern FR_CHARAY cimode;
extern FR_CHARAY ckmode;

extern FR_DOUBLE epsx,epsy,epsz;

extern FR_INT4 ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag,niflag;
extern FR_INT4 nrb,npr,ninto,ksflag,isflag;
extern FR_INT4 LANG,ICFLAG;

extern char ci1[];
extern char ci2[];
extern char ci3[];
extern char ci5[];
extern char cni[];

FR_INT4 i,j;

/*---------------------------------------------------------------------*
* Beschreiben Z88I1.TXT
*---------------------------------------------------------------------*/
if(ICFLAG == 4 || ICFLAG == 5)
  {
  wlog88x(0,LOG_WRII1);
  wrim88x(0,TX_WRII1);

/*---------------------------------------------------------------------*
* Oeffnen Z88I1.TXT
*---------------------------------------------------------------------*/
  fz88= fopen(ci1,"w");
  if(fz88 == NULL)
    {
    wlog88x(0,LOG_NOI1);
    fclose(fwlo);
    return(AL_NOI1);
    }
  rewind(fz88);

/*---------------------------------------------------------------------*
* Beschreiben Z88I1.TXT, erste Zeile
*---------------------------------------------------------------------*/
  if(kflag == 1) kflag = 0;
  
  if(LANG == 1)
  fprintf(fz88,
  " %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld  \
Z88I1.TXT,erzeugt von Z88X V12.0\n",
  ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag);


  if(LANG == 2)
  fprintf(fz88,
  " %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld  \
Z88I1.TXT,produced by Z88X V12.0\n",
  ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag);
  }

/*---------------------------------------------------------------------*
* Beschreiben Z88NI.TXT
*---------------------------------------------------------------------*/
if(ICFLAG == 6)
  {
  wlog88x(0,LOG_WRINI);
  wrim88x(0,TX_WRINI);

/*---------------------------------------------------------------------*
* Oeffnen Z88NI.TXT
*---------------------------------------------------------------------*/
  fz88= fopen(cni,"w");
  if(fz88 == NULL)
    {
    wlog88x(0,LOG_NONI);
    fclose(fwlo);
    return(AL_NONI);
    }
  rewind(fz88);

/*---------------------------------------------------------------------*
* Beschreiben Z88NI.TXT, erste Zeile
*---------------------------------------------------------------------*/
  if(kflag ==  1) kflag  = 0;
  if(ibflag == 1) ibflag = 0;
  
  if(LANG == 1)
  fprintf(fz88,
  " %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld  \
Z88NI.TXT,erzeugt von Z88X V12.0\n",
  ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag,niflag);

  if(LANG == 2)
  fprintf(fz88,
  " %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld  \
Z88NI.TXT,produced by Z88X V12.0\n",
  ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag,niflag);
  }

/*---------------------------------------------------------------------*
* Beschreiben Z88I1.TXT bzw. Z88NI.TXT, Koordinaten
*---------------------------------------------------------------------*/
for(i= 1; i<= nkp;i++)
  {
  if(LANG == 1)
  fprintf(fz88," %5ld %2ld  %+#13.5lE  %+#13.5lE  %+#13.5lE   Knoten #%ld\n",
  i,ifrei[i],x[i],y[i],z[i],i);

  if(LANG == 2)
  fprintf(fz88," %5ld %2ld  %+#13.5lE  %+#13.5lE  %+#13.5lE   node #%ld\n",
  i,ifrei[i],x[i],y[i],z[i],i);
  }

/*---------------------------------------------------------------------*
* Beschreiben Z88I1.TXT bzw. Z88NI.TXT, Koinzidenz
*---------------------------------------------------------------------*/
for(i= 1; i <= ne; i++)
  {
  if(ityp[i] == 1)
    {
    fprintf(fz88,
    " %5ld %5ld   element #%ld\n %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
    i,ityp[i],i,
    koi[koffs[i]   ], koi[koffs[i] +1],
    koi[koffs[i] +2], koi[koffs[i] +3],
    koi[koffs[i] +4], koi[koffs[i] +5],
    koi[koffs[i] +6], koi[koffs[i] +7]);
    }

  if(ityp[i] == 10)
    {
    fprintf(fz88,
    " %5ld %5ld   element #%ld\n\
 %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\
 %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
    i,ityp[i],i,
    koi[koffs[i]    ], koi[koffs[i] + 2],
    koi[koffs[i] + 4], koi[koffs[i] + 6],
    koi[koffs[i] + 8], koi[koffs[i] +10],
    koi[koffs[i] +12], koi[koffs[i] +14],
    koi[koffs[i] + 1], koi[koffs[i] + 3],
    koi[koffs[i] + 5], koi[koffs[i] + 7],
    koi[koffs[i] + 9], koi[koffs[i] +11],
    koi[koffs[i] +13], koi[koffs[i] +15],
    koi[koffs[i] +16], koi[koffs[i] +17],
    koi[koffs[i] +18], koi[koffs[i] +19]);
    }

  if(ityp[i] == 7 || ityp[i] == 8 || ityp[i] == 20)
    {
    fprintf(fz88,
    " %5ld %5ld   element #%ld\n %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
    i,ityp[i],i,
    koi[koffs[i]   ], koi[koffs[i] +2],
    koi[koffs[i] +4], koi[koffs[i] +6],
    koi[koffs[i] +1], koi[koffs[i] +3],
    koi[koffs[i] +5], koi[koffs[i] +7]);
    }

  if(ityp[i] == 11 || ityp[i] == 12)
    {
    fprintf(fz88," %5ld %5ld   element #%ld\n\
 %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
    i,ityp[i],i,
    koi[koffs[i]    ], koi[koffs[i] + 3],
    koi[koffs[i] + 6], koi[koffs[i] + 9],
    koi[koffs[i] + 1], koi[koffs[i] + 2],
    koi[koffs[i] + 4], koi[koffs[i] + 5],
    koi[koffs[i] + 7], koi[koffs[i] + 8],
    koi[koffs[i] +10], koi[koffs[i] +11]);
    }

  if(ityp[i] == 2 || ityp[i] == 4 || ityp[i] == 5 ||
     ityp[i] == 9 || ityp[i] == 13)
    {
    fprintf(fz88," %5ld %5ld   element #%ld\n %5ld %5ld\n",
    i,ityp[i],i,koi[koffs[i]    ], koi[koffs[i] +1]);
    }

  if(ityp[i] == 3 || ityp[i] == 14 || ityp[i] == 15 || ityp[i] == 18)
      {
    fprintf(fz88,
    " %5ld %5ld   element #%ld\n %5ld %5ld %5ld %5ld %5ld %5ld\n",
    i,ityp[i],i,
    koi[koffs[i]   ], koi[koffs[i] +2], koi[koffs[i] +4],
    koi[koffs[i] +1], koi[koffs[i] +3], koi[koffs[i] +5]);
    }

  if(ityp[i] == 6)
    {
    fprintf(fz88,
    " %5ld %5ld   element #%ld\n %5ld %5ld %5ld\n",
    i,ityp[i],i,
    koi[koffs[i]   ], koi[koffs[i] +1], koi[koffs[i] +2]);
    }

  if(ityp[i] == 19)
    {
    fprintf(fz88,
    " %5ld %5ld   element #%ld\n\
 %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\
 %5ld %5ld %5ld %5ld %5ld %5ld\n",
    i,ityp[i],i,
    koi[koffs[i]    ], koi[koffs[i] + 1],
    koi[koffs[i] + 2], koi[koffs[i] + 3],
    koi[koffs[i] + 4], koi[koffs[i] + 5],
    koi[koffs[i] + 6], koi[koffs[i] + 7],
    koi[koffs[i] + 8], koi[koffs[i] + 9],
    koi[koffs[i] +10], koi[koffs[i] +11],
    koi[koffs[i] +12], koi[koffs[i] +13],
    koi[koffs[i] +14], koi[koffs[i] +15]);
    }
  }

/*---------------------------------------------------------------------*
* Beschreiben Z88I1.TXT bzw. Z88NI.TXT, Elastizitaetsgesetze
*---------------------------------------------------------------------*/
for(i= 1; i <= neg; i++)
  if(ibflag == 0 && ipflag == 0)
    {
    fprintf(fz88," %5ld %5ld %+#13.5lE %+#13.5lE %5ld %+#13.5lE\n",
    ivon[i],ibis[i],emod[i],rnue[i],intord[i],qpara[i]);
    }
  else
   {
    fprintf(fz88," %5ld %5ld %+#13.5lE %+#13.5lE %5ld %+#13.5lE\
 %+#13.5lE %+#13.5lE %+#13.5lE %+#13.5lE %+#13.5lE %+#13.5lE\n",
    ivon[i],ibis[i],emod[i],rnue[i],intord[i],qpara[i],
    riyy[i],eyy[i],rizz[i],ezz[i],rit[i],wt[i]);
   }

/*---------------------------------------------------------------------*
* Z88NI.TXT: Zerlegungs- Infos schreiben
*---------------------------------------------------------------------*/
if(ICFLAG == 6)
  {
  for(i= 1; i <= ne; i++)
    {
    if(LANG == 1)
    fprintf(fz88,
    "%5ld %5ld   Superele. Nr.%ld,Typ %ld, --> Finites Ele. Typ %ld\n",
    i,itypfe[i],i,ityp[i],itypfe[i]);

    if(LANG == 2)
    fprintf(fz88,
    "%5ld %5ld  superele. no.%ld,type %ld, --> finite ele. type %ld\n",
    i,itypfe[i],i,ityp[i],itypfe[i]);

    if(ityp[i] == 1 || ityp[i] == 10)
      {
      fprintf(fz88,"%5ld %c %5ld %c %5ld %c\n",
      jel[i],cjmode[i],iel[i],cimode[i],kel[i],ckmode[i]);
      }
    else
      {
      fprintf(fz88,"%5ld %c %5ld %c\n",
      jel[i],cjmode[i],iel[i],cimode[i]);
      }
    }

  if(niflag == 1)
    {
    if(ityp[i] == 1 || ityp[i] == 10)
      {
      fprintf(fz88,"%+#13.5lE %+#13.5lE %+#13.5lE\n",epsx,epsy,epsz);
      }
    else
      {
      fprintf(fz88,"%+#13.5lE %+#13.5lE\n",epsx,epsy);
      }
    }
  }

fclose(fz88);

/*---------------------------------------------------------------------*
* Beschreiben Z88I2.TXT
*---------------------------------------------------------------------*/
if(ICFLAG == 5)
  {
  wlog88x(0,LOG_WRII2);
  wrim88x(0,TX_WRII2);

/*---------------------------------------------------------------------*
* Oeffnen Z88I2.TXT
*---------------------------------------------------------------------*/
  fi2= fopen(ci2,"w");
  if(fi2 == NULL)
    {
    wlog88x(0,LOG_NOI2);
    fclose(fwlo);
    return(AL_NOI2);
    }
  rewind(fi2);

/*---------------------------------------------------------------------*
* Beschreiben Z88I2.TXT, komplett
*---------------------------------------------------------------------*/
  if(LANG == 1) fprintf(fi2," %5ld    Z88I2.TXT,erzeugt von Z88X V12.0\n",nrb);
  if(LANG == 2) fprintf(fi2," %5ld    Z88I2.TXT,produced by Z88X V12.0\n",nrb);

  for(j= 1; j <= nrb; j++)
    fprintf(fi2," %5ld %5ld %5ld %+#13.5lE\n",
    nkn[j],ifg[j],irflag[j],wert[j]);
  fclose(fi2);
  }

/*---------------------------------------------------------------------*
* Beschreiben Z88I3.TXT
*---------------------------------------------------------------------*/
if(ICFLAG == 5)
  {
  wlog88x(0,LOG_WRII3);
  wrim88x(0,TX_WRII3);

/*---------------------------------------------------------------------*
* Oeffnen Z88I3.TXT
*---------------------------------------------------------------------*/
  fi3= fopen(ci3,"w");
  if(fi3 == NULL)
    {
    wlog88x(0,LOG_NOI3);
    fclose(fwlo);
    return(AL_NOI3);
    }
  rewind(fi3);

/*---------------------------------------------------------------------*
* Beschreiben Z88I3.TXT, komplett
*---------------------------------------------------------------------*/
  if(LANG == 1) 
  fprintf(fi3," %5ld %5ld %5ld    Z88I3.TXT,erzeugt von Z88X V12.0\n",
  ninto,ksflag,isflag);

  if(LANG == 2) 
  fprintf(fi3," %5ld %5ld %5ld    Z88I3.TXT,produced by Z88X V12.0\n",
  ninto,ksflag,isflag);
 
  fclose(fi3);
  }

/*---------------------------------------------------------------------*
* Beschreiben Z88I5.TXT
*---------------------------------------------------------------------*/
if(ICFLAG == 5 && iqflag == 1)
  {
  wlog88x(0,LOG_WRII5);
  wrim88x(0,TX_WRII5);

/*---------------------------------------------------------------------*
* Oeffnen Z88I5.TXT
*---------------------------------------------------------------------*/
  fi5= fopen(ci5,"w");
  if(fi5 == NULL)
    {
    wlog88x(0,LOG_NOI5);
    fclose(fwlo);
    return(AL_NOI5);
    }
  rewind(fi5);

/*---------------------------------------------------------------------*
* Beschreiben Z88I5.TXT, komplett
*---------------------------------------------------------------------*/
  if(LANG == 1) fprintf(fi5," %5ld    Z88I5.TXT,erzeugt von Z88X V12.0\n",npr);
  if(LANG == 2) fprintf(fi5," %5ld    Z88I5.TXT,produced by Z88X V12.0\n",npr);

  for(j= 1; j <= npr; j++)
    {
/*======================================================================
* Elementtypen 7, 8, 14, 15
*=====================================================================*/
    if(ityp[nep[j]]== 7  || ityp[nep[j]]== 8 ||
    ityp[nep[j]]== 14 || ityp[nep[j]]== 15) 
      {
      fprintf(fi5,"%5ld %+#13.5lE %+#13.5lE %5ld %5ld %5ld\n",
      nep[j],pres[j],tr1[j],
      noi[noffs[j]   ],noi[noffs[j] +1],noi[noffs[j] +2]);  
      }

/*======================================================================
* Elementtyp 10
*=====================================================================*/
    if(ityp[nep[j]]== 10) 
      {
      fprintf(fi5,
"%5ld %+#13.5lE %+#13.5lE %+#13.5lE %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
        nep[j],pres[j],tr1[j],tr2[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3], 
        noi[noffs[j] +4], noi[noffs[j] +5],
        noi[noffs[j] +6], noi[noffs[j] +7]); 
        }

/*======================================================================
* Elementtyp 1
*=====================================================================*/
    if(ityp[nep[j]]== 1) 
      {
      fprintf(fi5,
      "%5ld %+#13.5lE %+#13.5lE %+#13.5lE %5ld %5ld %5ld %5ld\n",
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]   ], noi[noffs[j] +1], 
      noi[noffs[j] +2], noi[noffs[j] +3]); 
      }

/*======================================================================
* Elementtypen 11 und 12
*=====================================================================*/
    if(ityp[nep[j]]== 11 || ityp[nep[j]]== 12) 
      {
      fprintf(fi5,"%5ld %+#13.5lE %+#13.5lE %5ld %5ld %5ld %5ld\n",
      nep[j],pres[j],tr1[j],
      noi[noffs[j]   ], noi[noffs[j] +1], 
      noi[noffs[j] +2], noi[noffs[j] +3]); 
      }

/*======================================================================
* Elementtyp 18,19 und 20
*=====================================================================*/
    if(ityp[nep[j]]== 18 || ityp[nep[j]]== 19 || ityp[nep[j]]== 20) 
      {
      fprintf(fi5,"%5ld %+#13.5lE\n",nep[j],pres[j]); 
      }

    } /* Enfe Schleife */

  fclose(fi5);
  }

return(0);
}
