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
* mc188n: dreidimensional: Typ 10 --> Typ 10
* 4.10.2005 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88n.h>
#include <stdio.h>    /* FILE,fclose */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88n.h>
#include <stdio.h>    /* FILE,fclose */
#endif

/***********************************************************************
* Functions
***********************************************************************/
FR_DOUBLE cphh88(char cmode,FR_INT4 jel);
FR_DOUBLE ihh88(char cmode,FR_DOUBLE xinc,FR_INT4 j,FR_INT4 jmax);
int fh88(FR_DOUBLE r,FR_DOUBLE s,FR_DOUBLE t);
int wrim88n(FR_INT4,int);
int wlog88n(FR_INT4,int);
 
/***********************************************************************
* hier beginnt Function mc188n
***********************************************************************/
int mc188n(void)
{
extern FILE *fi1,*fwlo;

/*--------------------------------------------------------------------------
* globale Pointer
*-------------------------------------------------------------------------*/
extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY xss;
extern FR_DOUBLEAY yss;
extern FR_DOUBLEAY zss;
extern FR_DOUBLEAY qparass;
extern FR_DOUBLEAY emodss;
extern FR_DOUBLEAY rnuess;

extern FR_INT4AY koima;
extern FR_INT4AY join; 
extern FR_INT4AY koiss;
extern FR_INT4AY ioffss;
extern FR_INT4AY koffss;
extern FR_INT4AY jel;
extern FR_INT4AY iel;
extern FR_INT4AY kel;
extern FR_INT4AY ivonss;
extern FR_INT4AY ibisss;
extern FR_INT4AY intoss;
extern FR_INT4AY ivon;
extern FR_INT4AY ibis;

extern FR_CHARAY cjmode;
extern FR_CHARAY cimode;
extern FR_CHARAY ckmode;

/*--------------------------------------------------------------------------
* globale Arrays
*-------------------------------------------------------------------------*/
extern FR_DOUBLE h[];

extern FR_INT4 jhxsta[];
extern FR_INT4 ihxsta[];
extern FR_INT4 khxsta[];

/*--------------------------------------------------------------------------
* globale Variable
*-------------------------------------------------------------------------*/
extern FR_DOUBLE epsx,epsy,epsz;
extern FR_INT4 MAXSE,MAXAN,MAXK,MAXE,MAXNFG,LANG;
extern FR_INT4 ness,negss,ndim,kflag,ibflag,ipflag,iqflag,ifrei,ityp;

/*--------------------------------------------------------------------------
* lokale Arrays
*-------------------------------------------------------------------------*/
FR_INT4 koilo[21];

/*--------------------------------------------------------------------------
* lokale Variable
*-------------------------------------------------------------------------*/
FR_DOUBLE xinc,yinc,zinc,r,s,t,xsp,ysp,zsp,x4,y4,z4;
FR_DOUBLE xmax,xmin,xist,ymax,ymin,yist,zmax,zmin,zist;
FR_INT4 index,nkp,ne,nfg,neg,koimax,k,le,je,ie,ke,jmax,imax,kmax,iss,isum;
FR_INT4 j,i,m,joffs,icount,macoun,jgerad,igerad,kgerad,jndex,kk,min,max,n;

/*--------------------------------------------------------------------------
* Start Function
*-------------------------------------------------------------------------*/
wlog88n(0,LOG_SMC188N);
wrim88n(0,TX_BERKOOR);

/*--------------------------------------------------------------------------
* Koordinaten berechnen
*-------------------------------------------------------------------------*/
for(iss = 1;iss <= ness;iss++)
  {        
  wrim88n(iss,TX_SUPERELE);
  
/*----------------------------------------------------------------------
* max. Anzahl Knoten/Elementseite, ioffs & incremente
*---------------------------------------------------------------------*/ 
  jmax= jel[iss]*2+1;
  imax= iel[iss]*2+1;
  kmax= kel[iss]*2+1;
           
  xinc= cphh88(cjmode[iss],jel[iss]);
  yinc= cphh88(cimode[iss],iel[iss]);
  zinc= cphh88(ckmode[iss],kel[iss]);

/*----------------------------------------------------------------------
* Offsetvektor berechnen
*---------------------------------------------------------------------*/
  if(iss == 1)
    ioffss[1]= 1;
  else
    ioffss[iss]= ioffss[iss-1] + 
                 (jel[iss-1]*2+1)*(iel[iss-1]*2+1)*(kel[iss-1]*2+1);
                    
/*----------------------------------------------------------------------
* Berechnen der Formfunktionen fuer die komplette "Matrix"
* dabei ist a1,1 <=> Knoten 1 des Superelements unten links 
* und a imax,jmax <=> Knoten 3 des Superelements oben rechts
* beginnend bei a1,1 folgt a2,1, a3,1, ..., dann a2,1, a2,2 ..
*---------------------------------------------------------------------*/
  n= 0;
  for(j = 1;j <= jmax;j++)
    {
    r= ihh88(cjmode[iss],xinc,j,jmax);

    for(i = 1;i <= imax;i++)
      {
      s= ihh88(cimode[iss],yinc,i,imax);

      for(k = 1;k <= kmax;k++)
        {
        n++;
        t= ihh88(ckmode[iss],zinc,k,kmax);

        /* formfunktionen berechnen */

        fh88(r,s,t);

        /* echte Koordinaten aus nat. Koordinaten & Formfunktionen */

        xsp= 0.;
        ysp= 0.;
        zsp= 0.;
        
        for(m = 1;m <= 20;m++)
          {
          index= koiss[koffss[iss]+m-1];
          xsp= xsp + h[m] * xss[index];
          ysp= ysp + h[m] * yss[index];
          zsp= zsp + h[m] * zss[index];
          }

        /* in "Matrix" x und y speichern */

        index= (ioffss[iss]-1) + k + (i-1)*kmax + (j-1)*kmax*imax;

        if(index > MAXSE) 
          {
          wlog88n(0,LOG_TOBIG1);
          fclose(fwlo);
          return(AL_TOBIG1);
          }

        x[index]= xsp;
        y[index]= ysp;
        z[index]= zsp;
        }
      }
    }
  } 

/***********************************************************************
* Koinzidenzvektor koima fuer die Superelemente aufstellen
***********************************************************************/
wrim88n(0,TX_BERKOIN);
wlog88n(0,LOG_BERKOIN);

icount= 0;
macoun= 0;
for(iss = 1;iss <= ness;iss++)                        /* 240 */
  {
  wrim88n(iss,TX_SUPERELE);
  jmax= jel[iss]*2 + 1;
  imax= iel[iss]*2 + 1;
  kmax= kel[iss]*2 + 1;
  joffs= MAXAN*(iss-1);
          
  if(iss == 1) 
    {
/*----------------------------------------------------------------------
*   1.Element braucht Sonderbehandlung
*---------------------------------------------------------------------*/
    for(j = 1;j <= jmax;j++)
      {
      jgerad= j+1-((j+1)/2)*2;
      for(i = 1;i <= imax;i++)
        {
        igerad= i+1-((i+1)/2)*2;
        for(k = 1;k <= kmax;k++)
          {
          kgerad= k+1-((k+1)/2)*2;
          icount++;
          if(!((jgerad == 1 && igerad == 1) ||
               (jgerad == 1 && kgerad == 1) ||
               (igerad == 1 && kgerad == 1))) 
            {
/*======================================================================
*           nur wenn i und j nicht gleichzeitig gerade sind, dann. 
*=====================================================================*/
            macoun++;
            koima[icount]= macoun;
            }
          else
            {
/*======================================================================
*           totes element
*=====================================================================*/
            koima[icount]= 0;
            }  
          }
        }
      }
    }              /* endif Sonderbehandlung 1. Element */
  else
    {
/*-----------------------------------------------------------------------
*   Superelement 2 bis Ende
*---------------------------------------------------------------------*/
    for(j = 1;j <= jmax;j++)                          /* 230 */
      {
      jgerad= j+1 -((j+1)/2)*2;
      for(i = 1;i <= imax;i++)                        /* 220 */
        {
        igerad= i+1-((i+1)/2)*2;
        for(k = 1;k <= kmax;k++)                      /* 210 */
          {
          kgerad= k+1-((k+1)/2)*2;
          icount++;
          if(!((jgerad == 1 && igerad == 1) ||
               (jgerad == 1 && kgerad == 1) ||
               (igerad == 1 && kgerad == 1))) 
            {                                         /* if */
/*======================================================================
*           nur wenn i und j nicht gleichzeitig gerade sind, dann. 
*=====================================================================*/
            for(kk = 1;kk <= MAXAN;kk++)              /* 200 */
              {
/*......................................................................
*             Schleife ueber die Nachbar-Superelemente
*.....................................................................*/ 
              jndex= join[joffs+kk];
              if(jndex > 0 && jndex < iss)            /* if */
                {
                /* nur wenn Nachbar > 0 und < als aktuelles Superele */     
                min= ioffss[jndex];
                max= ioffss[jndex+1] -1;

                for(index = min;index <= max;index++) /* 190 */  
                  {
                  xmax= x[index] + epsx;
                  xmin= x[index] - epsx;
                  ymax= y[index] + epsy;
                  ymin= y[index] - epsy;
                  zmax= z[index] + epsz;
                  zmin= z[index] - epsz;
                  xist= x[icount];
                  yist= y[icount];
                  zist= z[icount];
                  if(xist >= xmin && xist <= xmax &&
                     yist >= ymin && yist <= ymax &&
                     zist >= zmin && zist <= zmax)
                    {                                 /* if */
                    /* alten Knoten gefunden,dessen Index zuweisen */
                    koima[icount]= koima[index];
                    goto L210;
                    }                                 /* end if */
                  }                                   /* e 190 */
                }                                     /* end if */
              }                                       /* e 200 */
            /* neuer Knoten; macoun incrementieren */
            macoun++;
            koima[icount]= macoun;
            }                                         /* end if */
          else
            {                                         /* if */
/*======================================================================
*           toter Knoten
*=====================================================================*/
            koima[icount]= 0;
            }                                         /* end if */
          L210:;
          }                                           /* e 210 */
        }                                             /* e 220 */
      }                                               /* e 230 */ 
    }                                                 /* end if */
  }                                                   /* e 240 */
/*----------------------------------------------------------------------
* ende if <1.Element> oder <2.bis letztes Element>
*---------------------------------------------------------------------*/

/***********************************************************************
* Beschreiben von Z88I1.TXT
***********************************************************************/
/*----------------------------------------------------------------------
* 1.Zeile
*---------------------------------------------------------------------*/
wrim88n(0,TX_WRII1);
wlog88n(0,LOG_WRII1);

nkp= macoun;

ne= 0;
for(i = 1;i <= ness;i++)
  {
  ne= ne + jel[i]*iel[i]*kel[i];
  }

nfg= 3*nkp;
neg= negss;
        
if(LANG == 1) fprintf(fi1,
" %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld  \
Z88I1.TXT, erzeugt von Z88N V12.0\n",
ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag);

if(LANG == 2) fprintf(fi1,
" %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld  \
Z88I1.TXT, computed by Z88N V12.0\n",
ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag);

/*----------------------------------------------------------------------
* Koordinaten
*---------------------------------------------------------------------*/
koimax= 1;

for(i = 1;i <= icount;i++)
  {
  if(i == 1)
    {
    if(FR_FABS(x[1]) < 1e-21)
      x4= 0.;
    else
      x4= x[1];
    if(FR_FABS(y[1]) < 1e-21)
      y4= 0.;
    else
      y4= y[1];
    if(FR_FABS(z[1]) < 1e-21)
      z4= 0.;
    else
      z4= z[1];
    if(LANG == 1) fprintf(fi1,
    " %5ld %2ld  %+#13.5lE  %+#13.5lE  %+#13.5lE   Knoten Nr.%ld\n",
    koimax,ifrei,x4,y4,z4,koimax);
    if(LANG == 2) fprintf(fi1,
    " %5ld %2ld  %+#13.5lE  %+#13.5lE  %+#13.5lE   node no.%ld\n",
    koimax,ifrei,x4,y4,z4,koimax);
    }
  else
    {
    if(koima[i] > koimax)
      {
      koimax= koima[i];
      if(FR_FABS(x[i]) < 1e-21)
        x4= 0.;
      else
        x4= x[i];
      if(FR_FABS(y[i]) < 1e-21)
        y4= 0.;
      else
        y4= y[i];
      if(FR_FABS(z[i]) < 1e-21)
        z4= 0.;
      else
        z4= z[i];
      if(LANG == 1) fprintf(fi1,
      " %5ld %2ld  %+#13.5lE  %+#13.5lE  %+#13.5lE   Knoten Nr.%ld\n",
      koimax,ifrei,x4,y4,z4,koimax);
      if(LANG == 2) fprintf(fi1,
      " %5ld %2ld  %+#13.5lE  %+#13.5lE  %+#13.5lE   node no.%ld\n",
      koimax,ifrei,x4,y4,z4,koimax);
      }
    }
  }
              
/*-----------------------------------------------------------------------
* Elementdaten & Koinzidenzliste
*---------------------------------------------------------------------*/
kk= 0;
        
for(iss = 1;iss <= ness;iss++)
  {
  jmax= jel[iss]*2+1;
  imax= iel[iss]*2+1;
  kmax= kel[iss]*2+1;

  for(je = 1;je <= jel[iss];je++)
    {
    for(ie = 1;ie <= iel[iss];ie++)
      {
      for(ke = 1;ke <= kel[iss];ke++)
        {
        kk++;
        for(le = 1;le <= 20;le++)
          {
          j= jhxsta[le] + 2*(je-1);
          i= ihxsta[le] + 2*(ie-1);
          k= khxsta[le] + 2*(ke-1);
          index= (ioffss[iss]-1) + k + (i-1)*kmax + (j-1)*kmax*imax;
          koilo[le]= koima[index];
          }

        if(LANG == 1) fprintf(fi1," %5ld %5ld   Element Nr.%ld\n",kk,ityp,kk);
        if(LANG == 2) fprintf(fi1," %5ld %5ld   element no.%ld\n",kk,ityp,kk);
        fprintf(fi1," %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\
 %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
        koilo[ 1],koilo[ 2],koilo[ 3],koilo[ 4],koilo[ 5],
        koilo[ 6],koilo[ 7],koilo[ 8],koilo[ 9],koilo[10],
        koilo[11],koilo[12],koilo[13],koilo[14],koilo[15],
        koilo[16],koilo[17],koilo[18],koilo[19],koilo[20]);
        }
      }
    }
  }
    
/*-----------------------------------------------------------------------
* Elastizitaetsgesetze 
*---------------------------------------------------------------------*/
for(i = 1;i <= negss;i++)
  {
  if(i == 1)
    {
    ivon[1]= 1;
    isum= 0;
    for(k = ivonss[1]; k <= ibisss[1];k++)
      isum= isum+jel[k]*iel[k]*kel[k];
    ibis[1]= isum;
    }
  else
    {   
    ivon[i]= ibis[i-1]+1;
    isum= 0;
    for(k = ivonss[i]; k <= ibisss[i];k++)
      isum= isum+jel[k]*iel[k]*kel[k];
    ibis[i]= isum + ibis[i-1]; 
    }

  fprintf(fi1," %5ld %5ld %+#13.5lE %+#13.5lE %5ld %+#13.5lE\n",
  ivon[i],ibis[i],emodss[i],rnuess[i],intoss[i],qparass[i]);
  }

/*-----------------------------------------------------------------------
* Testen gegen Grenzen 
*---------------------------------------------------------------------*/
if(nkp > MAXK || ne > MAXE || nfg > MAXNFG)
  {
  wlog88n(0,LOG_FEEXID);
  fclose(fwlo);
  return(AL_FEEXID);
  }

/*-----------------------------------------------------------------------
* normales Ende
*---------------------------------------------------------------------*/
fclose(fwlo);
fclose(fi1);
return(0);
}
