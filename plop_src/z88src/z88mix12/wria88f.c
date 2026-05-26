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
* wria88f.c (Jennings- Speicherung) beschreibt Z88O0.TXT und Z88O1.BNY
* und oeffnet und schliesst diese Files
* 29.9.2005 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88f.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fprintf,fwrite */
                     /* rewind */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88f.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fprintf,fwrite */
                     /* rewind */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88f(FR_INT4,int);
int wlog88f(FR_INT4,int);

/***********************************************************************
* hier beginnt Function wria88f
***********************************************************************/
int wria88f(void)
{
extern FILE *fo0,*f1y,*fwlo;
extern char c1y[],co0[];

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

extern FR_INT4AY koi;
extern FR_INT4AY ip;
extern FR_INT4AY ifrei; 
extern FR_INT4AY ioffs; 
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;
extern FR_INT4AY ivon;
extern FR_INT4AY ibis;
extern FR_INT4AY intord;

extern FR_INT4 ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag,LANG;

FR_INT4 i,nkoi,nfgp1;

/*----------------------------------------------------------------------
* Start Function: Oeffnen der Files
*---------------------------------------------------------------------*/
wlog88f(0,LOG_BWRIA88F);

f1y= fopen(c1y,"w+b");
if(f1y == NULL)
  {
  wlog88f(0,LOG_NO1Y);
  fclose(fwlo);
  return(AL_NO1Y);
  }

rewind(f1y);

fo0= fopen(co0,"w+");
if(fo0 == NULL)
  {
  wlog88f(0,LOG_NOO0);
  fclose(fwlo);
  return(AL_NOO0);
  }

rewind(fo0);

/***********************************************************************
* nkoi ist Anzahl der echt benutzten Elemente in koi; 19 geht immer
***********************************************************************/
nkoi= koffs[ne] + 19;

/**********************************************************************
* Beschreiben des Binaerfiles Z88O1.BNY
**********************************************************************/
wrim88f(0,TX_WRI1Y);
wlog88f(0,LOG_WRI1Y);

fwrite(&ndim,  sizeof(FR_INT4),1,f1y);
fwrite(&nkp,   sizeof(FR_INT4),1,f1y);
fwrite(&ne,    sizeof(FR_INT4),1,f1y);
fwrite(&nfg,   sizeof(FR_INT4),1,f1y);
fwrite(&neg,   sizeof(FR_INT4),1,f1y);
fwrite(&ibflag,sizeof(FR_INT4),1,f1y);
fwrite(&ipflag,sizeof(FR_INT4),1,f1y);
fwrite(&iqflag,sizeof(FR_INT4),1,f1y);

for(i = 1;i <= nkp;i++)
  { 
  fwrite(&x[i],     sizeof(FR_DOUBLE), 1,f1y);
  fwrite(&y[i],     sizeof(FR_DOUBLE), 1,f1y);
  fwrite(&z[i],     sizeof(FR_DOUBLE), 1,f1y);
  fwrite(&ifrei[i], sizeof(FR_INT4),   1,f1y);
  fwrite(&ioffs[i], sizeof(FR_INT4),   1,f1y);
  }

for(i = 1;i <= ne;i++)
  { 
  fwrite(&ityp[i],  sizeof(FR_INT4),  1,f1y);
  fwrite(&koffs[i], sizeof(FR_INT4),  1,f1y);
  }
       
fwrite(&nkoi, sizeof(FR_INT4),1,f1y);
for(i = 1;i <= nkoi;i++)
  fwrite(&koi[i], sizeof(FR_INT4),1,f1y);

for(i = 1;i <= neg;i++)
  { 
  fwrite(&ivon[i],   sizeof(FR_INT4),  1,f1y);
  fwrite(&ibis[i],   sizeof(FR_INT4),  1,f1y);
  fwrite(&emod[i],   sizeof(FR_DOUBLE),1,f1y);
  fwrite(&rnue[i],   sizeof(FR_DOUBLE),1,f1y);
  fwrite(&intord[i], sizeof(FR_INT4),  1,f1y);
  fwrite(&qpara[i],  sizeof(FR_DOUBLE),1,f1y);
  fwrite(&riyy[i],   sizeof(FR_DOUBLE),1,f1y);
  fwrite(&eyy[i],    sizeof(FR_DOUBLE),1,f1y);
  fwrite(&rizz[i],   sizeof(FR_DOUBLE),1,f1y);
  fwrite(&ezz[i],    sizeof(FR_DOUBLE),1,f1y);
  fwrite(&rit[i],    sizeof(FR_DOUBLE),1,f1y);
  fwrite(&wt[i],     sizeof(FR_DOUBLE),1,f1y);
  }

fwrite(&nfg, sizeof(FR_INT4),1,f1y);
nfgp1= nfg+1;
for(i = 1;i <= nfgp1;i++)
  fwrite(&ip[i], sizeof(FR_INT4),1,f1y);

/***********************************************************************
* Beschreiben des Files Z88O0.TXT
***********************************************************************/
wrim88f(0,TX_WRIO0);
wlog88f(0,LOG_WRIO0);

/*----------------------------------------------------------------------
* Allgemeine Strukturdaten
*---------------------------------------------------------------------*/
if(LANG == 1)
{
fprintf(fo0,"Ausgabedatei Z88O0.TXT: Strukturdaten, erzeugt mit Z88F V12\n");
fprintf(fo0,"                        *************\n");
fprintf(fo0,"\nAllgemeine Strukturdaten :");
fprintf(fo0,
"\n\nDimension  Knoten  Elemente  Freiheitsgrade  E-Gesetze  KFLAG  IBFLAG  IPFLAG  IQFLAG");
fprintf(fo0,
  "\n %5ld      %5ld    %5ld        %5ld         %5ld      %ld      %ld      %ld      %ld",
ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag);
}

if(LANG == 2)
{
fprintf(fo0,"output file Z88O0.TXT: structure info, produced by Z88F V12\n");
fprintf(fo0,"                       **************\n");
fprintf(fo0,"\ngeneral structure informations:");
fprintf(fo0,
"\n\ndimension   nodes  elements       DOF    mat-infos  KFLAG  IBFLAG  IPFLAG  IQFLAG");
fprintf(fo0,
  "\n %5ld      %5ld    %5ld        %5ld         %5ld      %ld      %ld      %ld      %ld",
ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag);
}

/*----------------------------------------------------------------------
* Koordinaten
*---------------------------------------------------------------------*/
if(LANG == 1)
{
fprintf(fo0,"\n\nKoordinaten :");
fprintf(fo0,
"\n\nKnoten    FG          X               Y               Z");
}

if(LANG == 2)
{
fprintf(fo0,"\n\ncoordinates :");
fprintf(fo0,
"\n\nnode      DOF         X               Y               Z");
}

for(i = 1;i <= nkp;i++)
  {

#ifdef FR_XQUAD
  fprintf(fo0,
  "\n %5ld %5ld     %+#13.5LE   %+#13.5LE   %+#13.5LE",
  i,ifrei[i],x[i],y[i],z[i]);
#endif

#ifdef FR_XDOUB
  fprintf(fo0,
  "\n %5ld %5ld     %+#13.5lE   %+#13.5lE   %+#13.5lE",
  i,ifrei[i],x[i],y[i],z[i]);
#endif
  }

if(LANG == 1)
{
fprintf(fo0,"\n\nKoinzidenz (2 Zeilen pro Element) :");
fprintf(fo0,
"\n\nE- Nr.   Typ");
}

if(LANG == 2)
{
fprintf(fo0,"\n\nelement information (2 lines per element) :");
fprintf(fo0,
"\n\ne- no.   type");
}

fprintf(fo0,
"\n    K1    K2    K3    K4    K5    K6    K7    K8    K9   K10\
   K11   K12   K13   K14   K15   K16   K17   K18   K19   K20");

/*----------------------------------------------------------------------
* Koinzidenz
*---------------------------------------------------------------------*/
for(i = 1;i <= ne;i++)
  {
        
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Elemente 1, 7, 8  20
*---------------------------------------------------------------------*/
  if(ityp[i] == 1 || ityp[i] == 7 || ityp[i] == 8 || ityp[i] == 20)
    {
    fprintf(fo0,
    "\n %5ld %5ld\n %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5],
    koi[koffs[i]+6],koi[koffs[i]+7]); 
    }
    
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Elemente 2, 4, 5 , 9 & 13
*---------------------------------------------------------------------*/
  if(ityp[i] == 2 || ityp[i] == 4 || ityp[i] == 5 ||
     ityp[i] == 9 || ityp[i] == 13 )
    { 
    fprintf(fo0,
    "\n %5ld %5ld\n %5ld %5ld\n",
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1]);
    }
    
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Elemente 3, 14 & 15 & 18
*---------------------------------------------------------------------*/
  if(ityp[i] == 3 || ityp[i] == 14 || ityp[i]== 15 || ityp[i] == 18)
    {
    fprintf(fo0,
    "\n %5ld %5ld\n %5ld %5ld %5ld %5ld %5ld %5ld\n",
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5]);
    }
    
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Elemente 6
*---------------------------------------------------------------------*/
  if(ityp[i] == 6)
    {
    fprintf(fo0,
    "\n %5ld %5ld\n %5ld %5ld %5ld\n",
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2]);
    }
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Element 10
*---------------------------------------------------------------------*/
  if(ityp[i] == 10)
    {
    fprintf(fo0,
    "\n %5ld %5ld\n %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld",
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5],
    koi[koffs[i]+6],koi[koffs[i]+7], 
    koi[koffs[i]+8],koi[koffs[i]+9]); 

    fprintf(fo0,
    " %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
    koi[koffs[i]+10],koi[koffs[i]+11], 
    koi[koffs[i]+12],koi[koffs[i]+13], 
    koi[koffs[i]+14],koi[koffs[i]+15], 
    koi[koffs[i]+16],koi[koffs[i]+17], 
    koi[koffs[i]+18],koi[koffs[i]+19]); 
    }
    
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Elemente 11 & 12
*---------------------------------------------------------------------*/
  if(ityp[i] == 11 || ityp[i] == 12)
    {
    fprintf(fo0,
    "\n %5ld %5ld\n %5ld %5ld %5ld %5ld %5ld %5ld",
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5]);

    fprintf(fo0,
    " %5ld %5ld %5ld %5ld %5ld %5ld\n",
    koi[koffs[i]+6],koi[koffs[i]+7], 
    koi[koffs[i]+8],koi[koffs[i]+9], 
    koi[koffs[i]+10],koi[koffs[i]+11]); 
    }

/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Elemente 16
*---------------------------------------------------------------------*/
  if(ityp[i] == 16)
    {
    fprintf(fo0,
    "\n %5ld %5ld\n %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld",
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5],
    koi[koffs[i]+6],koi[koffs[i]+7], 
    koi[koffs[i]+8],koi[koffs[i]+9]); 
    }

/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Element 17
*---------------------------------------------------------------------*/
  if(ityp[i] == 17)
    {
    fprintf(fo0,
    "\n %5ld %5ld\n %5ld %5ld %5ld %5ld",
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3]);
    }
    
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Element 19
*---------------------------------------------------------------------*/
  if(ityp[i] == 19)
    {
    fprintf(fo0,
    "\n %5ld %5ld\n %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld",
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5],
    koi[koffs[i]+6],koi[koffs[i]+7], 
    koi[koffs[i]+8],koi[koffs[i]+9]); 

    fprintf(fo0,
    " %5ld %5ld %5ld %5ld %5ld %5ld\n",
    koi[koffs[i]+10],koi[koffs[i]+11], 
    koi[koffs[i]+12],koi[koffs[i]+13], 
    koi[koffs[i]+14],koi[koffs[i]+15]); 
    }

  }

/*----------------------------------------------------------------------
* Elastizitaetsgesetze
*---------------------------------------------------------------------*/
if(LANG == 1)
  fprintf(fo0,"\nElastizitaetsgesetze (1 Zeile pro E-Gesetz) :");

if(LANG == 2)
  fprintf(fo0,"\nmaterial informations (1 line per material) :");

if(ibflag == 0 && ipflag == 0)
  {
  if(LANG == 1) fprintf(fo0,
  "\n\n   Von   Bis     E-Modul       Quer-Zahl   INTORD      QPARA");

  if(LANG == 2) fprintf(fo0,
  "\n\n  from   to      Young's       Poisson's   INTORD      QPARA");
        
  for(i = 1;i <= neg;i++)
    {

#ifdef FR_XQUAD
    fprintf(fo0,
    "\n %5ld %5ld  %+#13.5LE  %+#13.5LE  %2ld     %+#13.5LE",
    ivon[i],ibis[i],emod[i],rnue[i],intord[i],qpara[i]);
#endif

#ifdef FR_XDOUB
    fprintf(fo0,
    "\n %5ld %5ld  %+#13.5lE  %+#13.5lE  %2ld     %+#13.5lE",
    ivon[i],ibis[i],emod[i],rnue[i],intord[i],qpara[i]);
#endif
    }
  }
else
  {
  if(LANG == 1) fprintf(fo0,
  "\n\n  Von   Bis    E-Modul     Quer-Zahl INT     QPARA\
          Iyy          eyy          Izz          ezz          It\
            Wt");

  if(LANG == 2) fprintf(fo0,
  "\n\n from   to     Young's     Poisson's INT     QPARA\
          Iyy          eyy          Izz          ezz          It\
            Wt");
        
  for(i = 1;i <= neg;i++)
    {

#ifdef FR_XQUAD
    fprintf(fo0,
    "\n%5ld %5ld %+#13.5LE %+#11.3LE %2ld %+#13.5LE\
 %+#13.5LE %+#11.3LE %+#13.5LE %+#11.3LE %+#13.5LE %+#13.5LE",
    ivon[i],ibis[i],emod[i],rnue[i],intord[i],qpara[i],
    riyy[i],eyy[i],rizz[i],ezz[i],rit[i],wt[i]);
#endif

#ifdef FR_XDOUB
    fprintf(fo0,
    "\n%5ld %5ld %+#13.5lE %+#11.3lE %2ld %+#13.5lE\
 %+#13.5lE %+#11.3lE %+#13.5lE %+#11.3lE %+#13.5lE %+#13.5lE",
    ivon[i],ibis[i],emod[i],rnue[i],intord[i],qpara[i],
    riyy[i],eyy[i],rizz[i],ezz[i],rit[i],wt[i]);
#endif
    }
  }


fprintf(fo0,"\n");
  
/**********************************************************************
* erforderliche Dimensionierung anzeigen
**********************************************************************/
wrim88f(ip[nfg],TX_GSERF);
wrim88f(nkoi,TX_KOIERF);

wlog88f(ip[nfg],LOG_GSERF);
wlog88f(nkoi,LOG_KOIERF);

/**********************************************************************
* Schliessen der Files; Ende Z88A
**********************************************************************/
fclose(f1y);
fclose(fo0);

wlog88f(0,LOG_EXITWRIA88F);
return(0);
}
