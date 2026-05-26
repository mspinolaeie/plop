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
* z88ci.c
* Einbau der Randbedingungen basiert gedanklich auf
* einem FORTRAN- Programm von H.R.Schwarz, Uni Zuerich. 
* 29.9.2005 Rieg 
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88i.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,rewind */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88i.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,rewind */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88i(FR_INT4,int);
int wlog88i2(FR_INT4,int);
int wran88i(FR_INT4,FR_INT4);
int scal88(void);
int siccg88(void);
int sorcg88(void);
int prfl88(void);

/***********************************************************************
* hier beginnt Function z88ci
***********************************************************************/
int z88ci(void)
{
extern FILE *fi2,*fi4,*f3y,*fo1,*fo2,*fl2;
extern char ci2[],ci4[],c3y[],co1[],co2[];

extern FR_DOUBLEAY GS;
extern FR_DOUBLEAY rs;
extern FR_DOUBLEAY fak;

extern FR_INT4AY ip;
extern FR_INT4AY iez;
extern FR_INT4AY ioffs; 
extern FR_INT4AY ifrei; 

extern FR_DOUBLE  eps,rp;
extern FR_INT4 kfoun,nkp,nfg,maxit,iqflag;
extern FR_INT4 MAXNFG,LANG,ICFLAG;

FR_DOUBLE wert;

FR_INT4 i,nrb,k,nkn,ifg,iflag1,jndex,j;

int iret;

char cline[256];

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/
wrim88i(0,TX_Z88CC);
wlog88i2(0,LOG_Z88CC);

/***********************************************************************
* Oeffnen der Files Z88I2.TXT,Z88I4.TXT,Z88O3.BNY,Z88O1.TXT & Z88O2.TXT
***********************************************************************/
fi2= fopen(ci2,"r");
if(fi2 == NULL)
  {
  wlog88i2(0,LOG_NOI2);
  fclose(fl2);
  return(AL_NOI2);
  }

rewind(fi2);

fi4= fopen(ci4,"r");
if(fi4 == NULL)
  {
  wlog88i2(0,LOG_NOI4);
  fclose(fl2);
  return(AL_NOI4);
  }

rewind(fi4);

f3y= fopen(c3y,"w+b");
if(f3y == NULL)
  {
  wlog88i2(0,LOG_NO3Y);
  fclose(fl2);
  return(AL_NO3Y);
  }

rewind(f3y);

fo1= fopen(co1,"w+");
if(fo1 == NULL)
  {
  wlog88i2(0,LOG_NOO1);
  fclose(fl2);
  return(AL_NOO1);
  }

rewind(fo1);

fo2= fopen(co2,"w+");
if(fo2 == NULL)
  {
  wlog88i2(0,LOG_NOO2);
  fclose(fl2);
  return(AL_NOO2);
  }

rewind(fo2);

/***********************************************************************
* Lesen des Steuerfiles Z88I4.TXT
***********************************************************************/
wrim88i(0,TX_REAI4);
wlog88i2(0,LOG_REAI4);

fgets(cline,256,fi4);

#ifdef FR_XQUAD
sscanf(cline,"%ld %Lf %Lf",&maxit,&eps,&rp);
#endif

#ifdef FR_XDOUB
sscanf(cline,"%ld %lf %lf",&maxit,&eps,&rp);
#endif

wlog88i2(maxit,LOG_MAXIT);
fclose(fi4);

/***********************************************************************
* Lesen des Randbedingungsfiles und Einarbeiten der RB, Pass 1
***********************************************************************/
wrim88i(0,TX_REAI2);
wrim88i(1,TX_ERBPA);
wlog88i2(0,LOG_REAI2);
wlog88i2(1,LOG_ERBPA);

fgets(cline,256,fi2);
sscanf(cline,"%ld",&nrb);

for(k = 1;k <= nrb;k++)
  {

  fgets(cline,256,fi2);

#ifdef FR_XQUAD
  sscanf(cline,"%ld %ld %ld %Lg",&nkn,&ifg,&iflag1,&wert);
#endif

#ifdef FR_XDOUB
  sscanf(cline,"%ld %ld %ld %lg",&nkn,&ifg,&iflag1,&wert);
#endif

  jndex= ioffs[nkn]-1+ifg;

  wran88i(k,iflag1);

/*----------------------------------------------------------------------
* Verzweigen, ob Kraft oder Verschiebung
*---------------------------------------------------------------------*/
/*======================================================================
* Kraft vorgegeben
*=====================================================================*/
  if (iflag1 == 1) rs[jndex]+= wert;     

/*======================================================================
* Verschiebung vorgegeben
*=====================================================================*/
  if(iflag1 == 2)
    {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung != 0
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
    if(FR_FABS(wert) >=  1e-8)
      {
      rs[jndex]= wert;
      GS[ip[jndex]]= 1.;

      if(jndex == 1) goto L30; 

      for(i= ip[jndex-1]+1; i <= ip[jndex]-1; i++)
        {
        rs[iez[i]]-= wert * GS[i];
        GS[i]= 0.;
        }  

      L30: if(jndex == nfg) break;

      for(j= jndex+1; j <= nfg; j++)
        {
        for(i= ip[j-1]+1; i <= ip[j]; i++)
          {
          if(iez[i] > jndex) break;
          if(iez[i] < jndex) continue;
          rs[j]-= wert * GS[i];
          GS[i]= 0.;
          break;
          }
        } 
      } /* Ende inhomogene RB */
    else
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung == 0 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
      {
      GS[ip[jndex]]= 1.;

      if(jndex == 1) goto L40; 

      for(i= ip[jndex-1]+1; i <= ip[jndex]-1; i++)
        GS[i]= 0.;

      L40: if(jndex == nfg) break;

      for(j= jndex+1; j <= nfg; j++)
        {
        for(i= ip[j-1]+1; i <= ip[j]; i++)
          {
          if(iez[i] > jndex) break;
          if(iez[i] < jndex) continue;
          GS[i]= 0.;
          break;
          }
        } 
      } /* Ende homogene RB */
    } /* Ende Weg vorgeben */

  } /* Ende Schleife Randbedingungen */

/***********************************************************************
* Lesen des Randbedingungsfiles und Einarbeiten der RB, Pass 2
* Gleichzeitig Kontrollfile Z88O1.TXT beschreiben
***********************************************************************/
wrim88i(0,TX_REAI2P2);
wrim88i(2,TX_ERBPA);
wrim88i(0,TX_WRIO1);
wlog88i2(0,LOG_REAI2);
wlog88i2(2,LOG_ERBPA);
wlog88i2(0,LOG_WRIO1);

rewind(fi2);

fgets(cline,256,fi2);
sscanf(cline,"%ld",&nrb);

if(LANG == 1)
{
fprintf(fo1,"Ausgabedatei Z88O1.TXT  Randbedingungen, erzeugt mit Z88I2 V12\n");
fprintf(fo1,"                        ***************\n\n");
fprintf(fo1,"Anzahl gegebene Randbedingungen: %ld\n\n",nrb);
}

if(LANG == 2)
{
fprintf(fo1,"output file Z88O1.TXT : constraints, produced by Z88I2 V12\n");
fprintf(fo1,"                        ***********\n\n");
fprintf(fo1,"number of given constraints: %ld\n\n",nrb);
}

for(k = 1;k <= nrb;k++)
  {
  fgets(cline,256,fi2);

#ifdef FR_XQUAD
  sscanf(cline,"%ld %ld %ld %Lg",&nkn,&ifg,&iflag1,&wert);
#endif

#ifdef FR_XDOUB
  sscanf(cline,"%ld %ld %ld %lg",&nkn,&ifg,&iflag1,&wert);
#endif

  jndex= ioffs[nkn]-1+ifg;
  if(iflag1 == 2) rs[jndex]= wert;

#ifdef FR_XQUAD
  if(iflag1 == 1)
    {
    if(LANG == 1)
    fprintf(fo1,
    "Knoten# %5ld   FG %1ld   Steuerflag %1ld   Last         %+#15.7LE\n",
    nkn,ifg,iflag1,wert);

    if(LANG == 2)
    fprintf(fo1,
    "  node# %5ld   DOF%1ld   lo/di flag %1ld   load         %+#15.7LE\n",
    nkn,ifg,iflag1,wert);
    }
    
  if(iflag1 == 2)
    {
    if(LANG == 1)
    fprintf(fo1,
    "Knoten# %5ld   FG %1ld   Steuerflag %1ld   Verschiebung %+#15.7LE\n",
    nkn,ifg,iflag1,wert);

    if(LANG == 2)
    fprintf(fo1,
    "  node# %5ld   DOF%1ld   lo/di flag %1ld   displacement %+#15.7LE\n",
    nkn,ifg,iflag1,wert);
    }
#endif    

#ifdef FR_XDOUB
  if(iflag1 == 1)
    {
    if(LANG == 1)
    fprintf(fo1,
    "Knoten# %5ld   FG %1ld   Steuerflag %1ld   Last         %+#15.7lE\n",
    nkn,ifg,iflag1,wert);

    if(LANG == 2)
    fprintf(fo1,
    "  node# %5ld   DOF%1ld   lo/di flag %1ld   load         %+#15.7lE\n",
    nkn,ifg,iflag1,wert);
    }
    
  if(iflag1 == 2)
    {
    if(LANG == 1)
    fprintf(fo1,
    "Knoten# %5ld   FG %1ld   Steuerflag %1ld   Verschiebung %+#15.7lE\n",
    nkn,ifg,iflag1,wert);

    if(LANG == 2)
    fprintf(fo1,
    "  node# %5ld   DOF%1ld   lo/di flag %1ld   displacement %+#15.7lE\n",
    nkn,ifg,iflag1,wert);
    }
#endif    
  }

/*----------------------------------------------------------------------
* ggf. Flaechenlasten nach Z88O1.TXT ausschreiben
*---------------------------------------------------------------------*/
if(iqflag == 1) prfl88();

/*----------------------------------------------------------------------
* Z88I2.TXT und Z88O1.TXT schliessen
*---------------------------------------------------------------------*/
fclose(fi2);
fclose(fo1);

/***********************************************************************
* Gleichungssystem skalieren mit SCAL88
***********************************************************************/
wrim88i(0,TX_SCAL88);
wlog88i2(0,LOG_SCAL88);

iret= scal88();
if(iret != 0) return(iret);

/***********************************************************************
* Ab die Post: Loesen des Gleichungssystems mit SICCG88 oder SORCG88
***********************************************************************/
if(ICFLAG == 1)
  {
  wrim88i(0,TX_SICCG88);
  wlog88i2(0,LOG_SICCG88);

  wrim88i(nfg,TX_NFG);

  siccg88();
  }

if(ICFLAG == 2)
  {
  wrim88i(0,TX_SORCG88);
  wlog88i2(0,LOG_SORCG88);

  wrim88i(nfg,TX_NFG);

  sorcg88();
  }

/***********************************************************************
* Scalierung rueckgaengig machen
***********************************************************************/
for(i = 1;i <= nfg;i++)
  rs[i]= rs[i]* fak[i];

/***********************************************************************
* Beschreiben und Schliessen von Z88O3.BNY 
***********************************************************************/
wrim88i(0,TX_WRI3Y);
wlog88i2(0,LOG_WRI3Y);

fwrite(&nfg,sizeof(FR_INT4),1,f3y);
for(i = 1;i <= nfg;i++)
  fwrite(&rs[i],sizeof(FR_DOUBLE),1,f3y);

fclose(f3y);

/***********************************************************************
* Beschreiben von Z88O2.TXT mit Verschiebungen
***********************************************************************/
wrim88i(0,TX_WRIO2);
wlog88i2(0,LOG_WRIO2);

if(LANG == 1)
{
fprintf(fo2,"Ausgabedatei Z88O2.TXT: Verschiebungen, erzeugt mit Z88I2 V12\n");
fprintf(fo2,"                        **************\n");
}

if(LANG == 2)
{
fprintf(fo2,"output file Z88O2.TXT: displacements, computed by Z88I2 V12\n");
fprintf(fo2,"                       *************\n");
}

fprintf(fo2,
"\nKnoten         U(1)              U(2)              U(3)\
              U(4)              U(5)              U(6)\n");

/*----------------------------------------------------------------------
* Schleife ueber alle Knoten
*---------------------------------------------------------------------*/
k= 1;
for(i = 1;i <= nkp;i++)
  {
          
/*======================================================================
* 2 Freiheitsgrade:
*=====================================================================*/
  if (ifrei[i] == 2)
    {

#ifdef FR_XQUAD
    fprintf(fo2,
    "\n %5ld   %+#15.7LE   %+#15.7LE",i,rs[k],rs[k+1]);
    k+= 2;
#endif

#ifdef FR_XDOUB
    fprintf(fo2,
    "\n %5ld   %+#15.7lE   %+#15.7lE",i,rs[k],rs[k+1]);
    k+= 2;
#endif
    }

/*======================================================================
* 3 Freiheitsgrade:
*=====================================================================*/
  if (ifrei[i] == 3)
    {

#ifdef FR_XQUAD
    fprintf(fo2,
    "\n %5ld   %+#15.7LE   %+#15.7LE   %+#15.7LE",
    i,rs[k],rs[k+1],rs[k+2]);
    k+= 3;
#endif

#ifdef FR_XDOUB
    fprintf(fo2,
    "\n %5ld   %+#15.7lE   %+#15.7lE   %+#15.7lE",
    i,rs[k],rs[k+1],rs[k+2]);
    k+= 3;
#endif
    }

/*======================================================================
* 6 Freiheitsgrade:
*=====================================================================*/
  if (ifrei[i] == 6)
    {

#ifdef FR_XQUAD
    fprintf(fo2,
    "\n %5ld   %+#15.7LE   %+#15.7LE   %+#15.7LE\
   %+#15.7LE   %+#15.7LE   %+#15.7LE",
    i,rs[k],rs[k+1],rs[k+2],rs[k+3],rs[k+4],rs[k+5]);
    k+= 6;
#endif

#ifdef FR_XDOUB
    fprintf(fo2,
    "\n %5ld   %+#15.7lE   %+#15.7lE   %+#15.7lE\
   %+#15.7lE   %+#15.7lE   %+#15.7lE",
    i,rs[k],rs[k+1],rs[k+2],rs[k+3],rs[k+4],rs[k+5]);
    k+= 6;
#endif
    }

/*---------------------------------------------------------------------
* Ende Schleife ueber alle Knoten
*--------------------------------------------------------------------*/
   }

/***********************************************************************
* Schliessen des noch offenen Files, Ende Z88CI
***********************************************************************/
fprintf(fo2,"\n");
fclose(fo2);

wlog88i2(0,LOG_EXITZ88CC);
return(0);
}
