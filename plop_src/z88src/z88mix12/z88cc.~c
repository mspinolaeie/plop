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
* z88cc.c mit Jennings- Speicherung
* Einbau der Randbedingungen nach H.R.Schwarz
* 29.9.2005 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88f.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,rewind */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88f.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,rewind */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88f(FR_INT4,int);
int wlog88f(FR_INT4,int);
int scal88(void);
int choy88(void);
int prfl88(void);

/***********************************************************************
* hier beginnt Function z88cc
***********************************************************************/
int z88cc(void)
{
extern FILE *fi2,*f3y,*fo1,*fo2,*fwlo;
extern char ci2[],c3y[],co1[],co2[];

extern FR_DOUBLEAY gs;
extern FR_DOUBLEAY rs;
extern FR_DOUBLEAY fak;

extern FR_INT4AY ip;
extern FR_INT4AY ioffs; 
extern FR_INT4AY ifrei; 

extern FR_INT4 nkp,nfg,iqflag;
extern FR_INT4 MAXNFG,LANG;

FR_DOUBLE wert;

FR_INT4 i,nrb,k,nkn,ifg,iflag1,jndex,j,istart,istop;

int iret;

char cline[256];

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/
wrim88f(0,TX_Z88CC);
wlog88f(0,LOG_Z88CC);

/***********************************************************************
* Oeffnen der Files Z88I2.TXT, Z88O3.BNY,Z88O1.TXT und Z88O2.TXT
***********************************************************************/
fi2= fopen(ci2,"r");
if(fi2 == NULL)
  {
  wlog88f(0,LOG_NOI2);
  fclose(fwlo);
  return(AL_NOI2);
  }

rewind(fi2);

f3y= fopen(c3y,"w+b");
if(f3y == NULL)
  {
  wlog88f(0,LOG_NO3Y);
  fclose(fwlo);
  return(AL_NO3Y);
  }

rewind(f3y);

fo1= fopen(co1,"w+");
if(fo1 == NULL)
  {
  wlog88f(0,LOG_NOO1);
  fclose(fwlo);
  return(AL_NOO1);
  }

rewind(fo1);

fo2= fopen(co2,"w+");
if(fo2 == NULL)
  {
  wlog88f(0,LOG_NOO2);
  fclose(fwlo);
  return(AL_NOO2);
  }

rewind(fo2);

/***********************************************************************
* Lesen des Randbedingungsfiles und Einarbeiten der RB, Pass 1
***********************************************************************/
wrim88f(0,TX_REAI2);
wrim88f(1,TX_ERBPA);
wlog88f(0,LOG_REAI2);
wlog88f(1,LOG_ERBPA);

fgets(cline,256,fi2);
sscanf(cline,"%ld",&nrb);

for(k = 1;k <= nrb;k++)
  {                                                        /* 120 */

  fgets(cline,256,fi2);

#ifdef FR_XQUAD
  sscanf(cline,"%ld %ld %ld %Lg",&nkn,&ifg,&iflag1,&wert);
#endif

#ifdef FR_XDOUB
  sscanf(cline,"%ld %ld %ld %lg",&nkn,&ifg,&iflag1,&wert);
#endif

  jndex= ioffs[nkn]-1+ifg;

/*----------------------------------------------------------------------
* Verzweigen, ob Kraft oder Verschiebung
*---------------------------------------------------------------------*/
/*======================================================================
* Kraft vorgegeben
*=====================================================================*/
  if (iflag1 == 1) rs[jndex] = rs[jndex] + wert;     

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
      rs[jndex]= wert;    /* Rechte Seite mit wert belegen */
      gs[ip[jndex]]= 1.;  /* Diagonalelemente auf 1 */

      if(jndex == 1) goto L30;  /* weil's ip[0] nicht gibt */
      
      istart=ip[jndex-1] + 1; /* Start der Skyline in der Zeile jndex */
      istop= ip[jndex]   - 1; /* Ende der Zeile vor Diagonalele.jndex */
      for(i= istart; i <= istop; i++)
        {
        j= jndex + i - istop -1;
        rs[j]-= wert * gs[i];
        gs[i]= 0.;         /* Zeile jndex 0 setzen */
        }  

      L30: if(jndex == nfg) continue;

      for(j= jndex+1; j <= nfg; j++)
        {
        if((ip[j-1] - ip[j] + j + 1) > jndex) continue;
        i= ip[j] - j + jndex;
        rs[j]-= wert * gs[i];
        gs[i]= 0.;         /* Spalte 0 setzen */ 
        } 
      } /* Ende inhomogene RB */
    else
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung == 0 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
      {
      gs[ip[jndex]]= 1.;  /* Diagonalelemente auf 1 */

      if(jndex == 1) goto L40;  /* weil's ip[0] nicht gibt */
      
      istart=ip[jndex-1] + 1; /* Start der Skyline in der Zeile jndex */
      istop= ip[jndex]   - 1; /* Ende der Zeile vor Diagonalele.jndex */
      for(i= istart; i <= istop; i++)
        gs[i]= 0.;         /* Zeile jndex 0 setzen */

      L40: if(jndex == nfg) continue;

      for(j= jndex+1; j <= nfg; j++)
        {
        if((ip[j-1] - ip[j] + j + 1) > jndex) continue;
        i= ip[j] - j + jndex;
        gs[i]= 0.;         /* Spalte 0 setzen */ 
        } 
      } /* Ende homogene RB */

    } /* Ende Weg vorgeben */

  } /* Ende Einbau RB */

/***********************************************************************
* Lesen des Randbedingungsfiles und Einarbeiten der RB, Pass 2
* Gleichzeitig Kontrollfile Z88O1.TXT beschreiben
***********************************************************************/
wrim88f(0,TX_REAI2);
wrim88f(2,TX_ERBPA);
wrim88f(0,TX_WRIO1);
wlog88f(0,LOG_REAI2);
wlog88f(2,LOG_ERBPA);
wlog88f(0,LOG_WRIO1);

rewind(fi2);

fgets(cline,256,fi2);
sscanf(cline,"%ld",&nrb);

if(LANG == 1)
{
fprintf(fo1,"Ausgabedatei Z88O1.TXT  Randbedingungen, erzeugt mit Z88F V12\n");
fprintf(fo1,"                        ***************\n\n");
fprintf(fo1,"Anzahl gegebene Randbedingungen: %ld\n\n",nrb);
}

if(LANG == 2)
{
fprintf(fo1,"output file Z88O1.TXT : constraints, produced by Z88F V12\n");
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
  }                                                        /* e 130 */

/*----------------------------------------------------------------------
* ggf. Flaechenlasten nach Z88O1.TXT ausschreiben
*---------------------------------------------------------------------*/
if(iqflag == 1) prfl88();

/*----------------------------------------------------------------------
* Z88I1.TXT und Z88O1.TXT schliessen
*---------------------------------------------------------------------*/
fclose(fi2);
fclose(fo1);

/***********************************************************************
* Gleichungssystem skalieren
***********************************************************************/
wrim88f(0,TX_SCAL88);
wlog88f(0,LOG_SCAL88);

iret= scal88();
if(iret != 0) return(iret);

/***********************************************************************
* Loesen des Gleichungssystems mit Function choy88
***********************************************************************/
wrim88f(0,TX_CHOY88);
wlog88f(0,LOG_CHOY88);

wrim88f(nfg,TX_NFG);

choy88();

/***********************************************************************
* Scalierung rueckgaengig machen
***********************************************************************/
for(i = 1;i <= nfg;i++)
  rs[i]= rs[i]* fak[i];

/***********************************************************************
* Beschreiben und Schliessen von Z88O3.BNY 
***********************************************************************/
wrim88f(0,TX_WRI3Y);
wlog88f(0,LOG_WRI3Y);

fwrite(&nfg,sizeof(FR_INT4),1,f3y);
for(i = 1;i <= nfg;i++)
  fwrite(&rs[i],sizeof(FR_DOUBLE),1,f3y);

fclose(f3y);

/***********************************************************************
* Beschreiben von Z88O2.TXT mit Verschiebungen
***********************************************************************/
wrim88f(0,TX_WRIO2);
wlog88f(0,LOG_WRIO2);

if(LANG == 1)
{
fprintf(fo2,"Ausgabedatei Z88O2.TXT : Verschiebungen, erzeugt mit Z88F V12\n");
fprintf(fo2,"                         **************\n");
}

if(LANG == 2)
{
fprintf(fo2,"output file Z88O2.TXT : displacements, computed by Z88F V12\n");
fprintf(fo2,"                        *************\n");
}

fprintf(fo2,
"\nKnoten         U(1)              U(2)              U(3)\
              U(4)              U(5)              U(6)\n");

/*----------------------------------------------------------------------
* Schleife ueber alle Knoten
*---------------------------------------------------------------------*/
k= 1;
for(i = 1;i <= nkp;i++)
  {                                                        /* 160 */
          
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
* Schliessen des noch offenen Files, Ende Z88CC
***********************************************************************/
fprintf(fo2,"\n");
fclose(fo2);

wlog88f(0,LOG_EXITZ88CC);
return(0);
}
