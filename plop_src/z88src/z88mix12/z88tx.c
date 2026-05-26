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
* z88tx.c : von Z88 nach DXF
* 4.10.2005 Rieg 
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>
#include <stdio.h>      /* fopen, fprintf, fclose */
#endif

/***********************************************************************
* Fuer Windows95
***********************************************************************/
#ifdef FR_WIN95
#include <z88x.h>
#include <stdio.h>      /* fopen, fprintf, fclose */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88x(FR_INT4,int);
int wlog88x(FR_INT4,int);

/***********************************************************************
* hier beginnt Function z88tx
***********************************************************************/
int z88tx(void)
{
extern FILE *fdxf,*fwlo;

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
extern FR_DOUBLE texts;

extern FR_INT4 ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag,niflag;
extern FR_INT4 nrb,npr,ninto,ksflag,isflag;
extern FR_INT4 ICFLAG,ITSFLAG;

extern char cxx[];

FR_DOUBLE px[21], py[21], pz[21];

FR_DOUBLE xmin,xmax,ymin,ymax,zmin,zmax;
FR_DOUBLE xlimin,xlimax,ylimin,ylimax;
FR_DOUBLE pxele,pyele,pzele;
FR_DOUBLE fackno;

FR_INT4 i1point[] = {0,1,2,3,4,5,6,7,8,1,2,3,4};
FR_INT4 j1point[] = {0,2,3,4,1,6,7,8,5,5,6,7,8};

FR_INT4 i3point[] = {0,1,4,2,5,3,6};
FR_INT4 j3point[] = {0,4,2,5,3,6,1};

FR_INT4 i6point[] = {0,1,2,3};
FR_INT4 j6point[] = {0,2,3,1};

FR_INT4 i7point[] = {0,1,5,2,6,3,7,4,8};
FR_INT4 j7point[] = {0,5,2,6,3,7,4,8,1};

FR_INT4 i10point[]= { 0, 1, 9, 2,10, 3,11, 4,12, 5,13, 6,14, 7,15, 8,16,
                      1,17, 2,18, 3,19, 4,20};
FR_INT4 j10point[]= { 0, 9, 2,10, 3,11, 4,12, 1,13, 6,14, 7,15, 8,16, 5,
                     17, 5,18, 6,19, 7,20, 8};

FR_INT4 i11point[]= {0,1,5,6,2,7,8,3,9 ,10, 4,11,12};
FR_INT4 j11point[]= {0,5,6,2,7,8,3,9,10, 4,11,12, 1};

FR_INT4 i19point[] = {0,1,2,3,4,5,6,7,8,9, 10,11,12,13,14,15,16};
FR_INT4 j19point[] = {0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16, 1};

FR_INT4 i,j,k;
 
/***********************************************************************
* start function
***********************************************************************/
wrim88x(0,TX_Z88TX);
wlog88x(0,LOG_Z88TX);

/***********************************************************************
* file fdxf = Z88X.DXF oeffnen
***********************************************************************/
wlog88x(0,LOG_FX);
wrim88x(0,TX_FX);
fdxf= fopen(cxx,"w");
if(fdxf == NULL)
  {
  wlog88x(0,LOG_NOX);
  fclose(fwlo);
  return(AL_NOX);
  }
rewind(fdxf);

/***********************************************************************
* faktoren fuer textsize definieren
***********************************************************************/
wlog88x(0,LOG_FAC);
wrim88x(0,TX_FAC);

fackno= 0.01;

/***********************************************************************
* wenn 2d, z[i] null setzen
***********************************************************************/
if(ndim == 2)
  for(i= 1; i <= nkp; i++) z[i]= 0.0;

zmin= 0.0;
zmax= 0.0;

/***********************************************************************
* groesstwerte,limits,textsize ermitteln
***********************************************************************/
if (ndim == 2)
  {
/*---------------------------------------------------------------------
* 2d: kleinste & groesste werte x,y ermitteln
*--------------------------------------------------------------------*/
  xmin= x[1];
  xmax= x[1];
  ymin= y[1];
  ymax= y[1];

  for(i= 1; i <= nkp; i++)
    {
    if( x[i] < xmin) xmin= x[i];
    if( x[i] > xmax) xmax= x[i];
    if( y[i] < ymin) ymin= y[i];
    if( y[i] > ymax) ymax= y[i];
    }

/*---------------------------------------------------------------------
* 2d: textgroessen isele und iskno festlegen
*--------------------------------------------------------------------*/
  if(ITSFLAG == 0)
    texts= fackno*0.5*((xmax-xmin)+(ymax-ymin));

/*---------------------------------------------------------------------
* 2d: limits ermitteln
*--------------------------------------------------------------------*/
  xlimin= xmin - 0.25*(xmax-xmin);
  ylimin= ymin - 0.25*(ymax-ymin);
  xlimax= xmax + 0.25*(xmax-xmin);
  ylimax= ymax + 0.25*(ymax-ymin);
  }
else
  {
/*---------------------------------------------------------------------
* 3d: kleinste & groesste werte x,y,z ermitteln
*--------------------------------------------------------------------*/
  xmin= x[1];
  xmax= x[1];
  ymin= y[1];
  ymax= y[1];
  zmin= z[1];
  zmax= z[1];

  for(i= 1; i <= nkp; i++)
    {
    if( x[i] < xmin) xmin= x[i];
    if( x[i] > xmax) xmax= x[i];
    if( y[i] < ymin) ymin= y[i];
    if( y[i] > ymax) ymax= y[i];
    if( z[i] < zmin) zmin= z[i];
    if( z[i] > zmax) zmax= z[i];
    }

/*---------------------------------------------------------------------
* 3d: textgroesse texts festlegen
*--------------------------------------------------------------------*/
  if(ITSFLAG == 0)
    texts= fackno*0.333*((xmax-xmin)+(ymax-ymin)+(zmax-zmin));

/*---------------------------------------------------------------------
* 3d: limits ermitteln
*--------------------------------------------------------------------*/
  xlimin= xmin - 0.5*(xmax-xmin);
  ylimin= ymin - 0.5*(ymax-ymin);
  xlimax= xmax + 0.5*(xmax-xmin);
  ylimax= ymax + 0.5*(ymax-ymin);
  }

/***********************************************************************
* Z88X.DXF : bis section entities auffuellen
***********************************************************************/
wlog88x(0,LOG_SDXF);
wrim88x(0,TX_SDXF);

fprintf(fdxf,"  0\nSECTION"); /* start section header */
fprintf(fdxf,"\n  2\nHEADER");

fprintf(fdxf,"\n  9\n$ACADVER\n  1\nAC1009");
fprintf(fdxf,"\n  9\n$INSBASE\n 10\n0.0\n 20\n0.0\n 30\n0.0");

fprintf(fdxf,"\n  9\n$EXTMIN");
fprintf(fdxf,"\n 10\n%lg",xmin);
fprintf(fdxf,"\n 20\n%lg",ymin);
fprintf(fdxf,"\n 30\n%lg",zmin);

fprintf(fdxf,"\n  9\n$EXTMAX");
fprintf(fdxf,"\n 10\n%lg",xmax);
fprintf(fdxf,"\n 20\n%lg",ymax);
fprintf(fdxf,"\n 30\n%lg",zmax);

fprintf(fdxf,"\n  9\n$LIMMIN");
fprintf(fdxf,"\n 10\n%lg",xlimin);
fprintf(fdxf,"\n 20\n%lg",ylimin);

fprintf(fdxf,"\n  9\n$LIMMAX");
fprintf(fdxf,"\n 10\n%lg",xlimax);
fprintf(fdxf,"\n 20\n%lg",ylimax);

fprintf(fdxf,"\n  9\n$CLAYER\n  8\nZ88NET");

fprintf(fdxf,"\n  9\n$PDMODE\n 70\n     3"); /* schraege kreuze */
fprintf(fdxf,"\n  9\n$PDSIZE\n 40\n-3.0");   /* 3 % groesse */

fprintf(fdxf,"\n  0\nENDSEC"); /* ende section header */

fprintf(fdxf,"\n  0\nSECTION"); /* start section tables */
fprintf(fdxf,"\n  2\nTABLES");

fprintf(fdxf,"\n  0\nTABLE"); /* start table ltype */

fprintf(fdxf,"\n  2\nLTYPE\n 70\n     1"); /* 1 linientyp */

fprintf(fdxf,"\n  0\nLTYPE\n  2\nCONTINUOUS\n 70\n    64\n  3");
fprintf(fdxf,"\nSolid line\n 72\n    65\n 73\n     0\n 40\n0.0");

fprintf(fdxf,"\n  0\nENDTAB"); /* ende table ltype */

fprintf(fdxf,"\n  0\nTABLE");  /* start table layer */

fprintf(fdxf,"\n  2\nLAYER\n 70\n     6"); /* 6 layer ausser 0 */

fprintf(fdxf,"\n  0\nLAYER\n  2\n0\n 70\n    64\n 62\n    -7");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* weiss, ausgeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88NET\n 70\n    64\n 62\n     5");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* blau, eingeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88EIO\n 70\n    64\n 62\n     5");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* blau, eingeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88KNR\n 70\n    64\n 62\n     1");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* rot, eingeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88RBD\n 70\n    64\n 62\n     6");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* magenta, eingeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88FLA\n 70\n    64\n 62\n     6");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* magenta, eingeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88GEN\n 70\n    64\n 62\n     6");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* magenta, eingeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88PKT\n 70\n    64\n 62\n     1");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* rot, eingeschaltet */

fprintf(fdxf,"\n  0\nENDTAB"); /* ende table layer */

fprintf(fdxf,"\n  0\nENDSEC"); /* ende section tables */

fprintf(fdxf,"\n  0\nSECTION"); /* start section entities */
fprintf(fdxf,"\n  2\nENTITIES");

/***********************************************************************
* allgemeine datei-informationen schreiben
***********************************************************************/
/*---------------------------------------------------------------------
* linke obere ecke
*--------------------------------------------------------------------*/
pxele= xlimin;
pyele= ylimax-1.5*texts;

/*---------------------------------------------------------------------
* grundsatz-infos schreiben
*--------------------------------------------------------------------*/
fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88GEN");
fprintf(fdxf,"\n 10\n%lg",pxele);
fprintf(fdxf,"\n 20\n%lg",pyele);
fprintf(fdxf,"\n 30\n0.0");
fprintf(fdxf,"\n 40\n%lg",texts);

if (ICFLAG == 1 || ICFLAG == 2)
  {
  if(kflag == 1) kflag = 0;
  fprintf(fdxf,"\n  1\nZ88I1.TXT %ld %ld %ld %ld %ld %ld %ld %ld %ld",
  ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag);
  }
else
  {
  if(kflag == 1) kflag = 0;
  if(ibflag == 1) ibflag = 0;
  fprintf(fdxf,"\n  1\nZ88NI.TXT %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",
  ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag,niflag);
  }

pyele+= -1.5 * texts;

/*---------------------------------------------------------------------
* e-gesetze
*--------------------------------------------------------------------*/
for(i= 1;i <= neg;i++)
  { 
  fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88GEN");
  fprintf(fdxf,"\n 10\n%lg",pxele);
  fprintf(fdxf,"\n 20\n%lg",pyele);
  fprintf(fdxf,"\n 30\n0.0");
  fprintf(fdxf,"\n 40\n%lg",texts);
  if(ibflag == 0 && ipflag == 0)
    {
    fprintf(fdxf,"\n  1\nMAT %ld %ld %ld %lg %lg %ld %lg",
    i,ivon[i],ibis[i],emod[i],rnue[i],intord[i],qpara[i]);
    }
  else
    {
    fprintf(fdxf,
    "\n  1\nMAT %ld %ld %ld %lg %lg %ld %lg %lg %lg %lg %lg %lg %lg",
    i,ivon[i],ibis[i],emod[i],rnue[i],intord[i],qpara[i],
    riyy[i],eyy[i],rizz[i],ezz[i],rit[i],wt[i]);
    }
  pyele+= -1.5 * texts;
  }

/*---------------------------------------------------------------------
* ggf. neue fangbereiche bei Z88NI.TXT
*--------------------------------------------------------------------*/
if (ICFLAG == 3 && niflag == 1)
  {
  fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88GEN");
  fprintf(fdxf,"\n 10\n%lg",pxele);
  fprintf(fdxf,"\n 20\n%lg",pyele);
  fprintf(fdxf,"\n 30\n0.0");
  fprintf(fdxf,"\n 40\n%lg",texts);
  if(ndim == 2)
    fprintf(fdxf,"\n  1\nD %lg %lg",epsx,epsy);
  else
    fprintf(fdxf,"\n  1\nD %lg %lg %lg",epsx,epsy,epsz);
  pyele+= -1.5 * texts;
  }

pyele+= -1.5 * texts;

/*---------------------------------------------------------------------
* randbedingungen z88i2.txt
*--------------------------------------------------------------------*/
if (ICFLAG == 2)
  {
  fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88RBD");
  fprintf(fdxf,"\n 10\n%lg",pxele);
  fprintf(fdxf,"\n 20\n%lg",pyele);
  fprintf(fdxf,"\n 30\n0.0");
  fprintf(fdxf,"\n 40\n%lg",texts);
  fprintf(fdxf,"\n  1\nZ88I2.TXT %ld",nrb);
  pyele+= -1.5 * texts;

  for(i= 1;i <= nrb;i++)
    { 
    fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88RBD");
    fprintf(fdxf,"\n 10\n%lg",pxele);
    fprintf(fdxf,"\n 20\n%lg",pyele);
    fprintf(fdxf,"\n 30\n0.0");
    fprintf(fdxf,"\n 40\n%lg",texts);
    fprintf(fdxf,"\n  1\nRBD %ld %ld %ld %ld %lg",
    i,nkn[i],ifg[i],irflag[i],wert[i]);
    pyele+= -1.5 * texts;
    }
  }

pyele+= -1.5 * texts;

/*---------------------------------------------------------------------
* z88i3.txt-infos schreiben
*--------------------------------------------------------------------*/
if (ICFLAG == 2)
  {
  fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88GEN");
  fprintf(fdxf,"\n 10\n%lg",pxele);
  fprintf(fdxf,"\n 20\n%lg",pyele);
  fprintf(fdxf,"\n 30\n0.0");
  fprintf(fdxf,"\n 40\n%lg",texts);
  fprintf(fdxf,"\n  1\nZ88I3.TXT %ld %ld %ld",ninto,ksflag,isflag);
  }

pyele+= -3.0 * texts;

/*---------------------------------------------------------------------
* flaechenlasten z88i5.txt
*--------------------------------------------------------------------*/
if (ICFLAG == 2 && iqflag == 1)
  {
  fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88FLA");
  fprintf(fdxf,"\n 10\n%lg",pxele);
  fprintf(fdxf,"\n 20\n%lg",pyele);
  fprintf(fdxf,"\n 30\n0.0");
  fprintf(fdxf,"\n 40\n%lg",texts);
  fprintf(fdxf,"\n  1\nZ88I5.TXT %ld",npr);
  pyele+= -1.5 * texts;

  for(j= 1;j <= npr;j++)
    { 
    fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88FLA");
    fprintf(fdxf,"\n 10\n%lg",pxele);
    fprintf(fdxf,"\n 20\n%lg",pyele);
    fprintf(fdxf,"\n 30\n0.0");
    fprintf(fdxf,"\n 40\n%lg",texts);

/*======================================================================
* Elementtypen 7, 8, 14, 15
*=====================================================================*/
    if(ityp[nep[j]]== 7  || ityp[nep[j]]== 8 ||
    ityp[nep[j]]== 14 || ityp[nep[j]]== 15) 
      {
      fprintf(fdxf,"\n  1\nFLA %ld %ld %lg %lg %ld %ld %ld",
      j,nep[j],pres[j],tr1[j],
      noi[noffs[j]   ],noi[noffs[j] +1],noi[noffs[j] +2]);  
      }

/*======================================================================
* Elementtyp 10
*=====================================================================*/
    if(ityp[nep[j]]== 10) 
      {
      fprintf(fdxf,
      "\n  1\nFLA %ld %ld %lg %lg %lg %ld %ld %ld %ld %ld %ld %ld %ld",
      j,nep[j],pres[j],tr1[j],tr2[j],
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
      fprintf(fdxf,"\n  1\nFLA %ld %ld %lg %lg %lg %ld %ld %ld %ld",
      j,nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]   ], noi[noffs[j] +1], 
      noi[noffs[j] +2], noi[noffs[j] +3]); 
      }

/*======================================================================
* Elementtypen 11 und 12
*=====================================================================*/
    if(ityp[nep[j]]== 11 || ityp[nep[j]]== 12) 
      {
      fprintf(fdxf,"\n  1\nFLA %ld %ld %lg %lg %ld %ld %ld %ld",
      j,nep[j],pres[j],tr1[j],
      noi[noffs[j]   ], noi[noffs[j] +1], 
      noi[noffs[j] +2], noi[noffs[j] +3]); 
      }

/*======================================================================
* Elementtyp 18,19 und 20
*=====================================================================*/
    if(ityp[nep[j]]== 18 || ityp[nep[j]]== 19 || ityp[nep[j]]== 20) 
      {
      fprintf(fdxf,"\n  1\nFLA %ld %ld %lg",j,nep[j],pres[j]); 
      }

    pyele+= -1.5 * texts;
    }
  }

/***********************************************************************
* punkte setzen
***********************************************************************/
for(i= 1; i <= nkp; i++)
  {
  fprintf(fdxf,"\n  0\nPOINT\n  8\nZ88PKT");
  fprintf(fdxf,"\n 10\n%lg",x[i]);
  fprintf(fdxf,"\n 20\n%lg",y[i]);
  fprintf(fdxf,"\n 30\n%lg",z[i]);

  fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88KNR");
  fprintf(fdxf,"\n 10\n%lg",x[i]);
  fprintf(fdxf,"\n 20\n%lg",y[i]);
  fprintf(fdxf,"\n 30\n%lg",z[i]);
  fprintf(fdxf,"\n 40\n%lg",texts);
  fprintf(fdxf,"\n  1\nP %ld",i);
  }

/***********************************************************************
* grosse elementschleife fuer element-infos
***********************************************************************/
wlog88x(0,LOG_SELE);
wrim88x(0,TX_SELE);

for(k= 1; k <= ne; k++)
  {
 
/*---------------------------------------------------------------------
* 8 punkte fuer 8-k hexaeder
*--------------------------------------------------------------------*/
  if(ityp[k] == 1)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 8; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[7]);
      pyele= 0.5*(py[1]+py[7]);
      pzele= 0.5*(pz[1]+pz[7]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n%lg",pxele);
      fprintf(fdxf,"\n 20\n%lg",pyele);
      fprintf(fdxf,"\n 30\n%lg",pzele);
      fprintf(fdxf,"\n 40\n%lg",texts);
      fprintf(fdxf,"\n  1\nFE %ld %ld",k,ityp[k]);
      }

    }

/*---------------------------------------------------------------------
* 20 punkte fuer 20-k hexaeder
*--------------------------------------------------------------------*/
  else if(ityp[k] == 10)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 20; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   entweder element-infos  schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[7]);
      pyele= 0.5*(py[1]+py[7]);
      pzele= 0.5*(pz[1]+pz[7]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n%lg",pxele);
      fprintf(fdxf,"\n 20\n%lg",pyele);
      fprintf(fdxf,"\n 30\n%lg",pzele);
      fprintf(fdxf,"\n 40\n%lg",texts);
      fprintf(fdxf,"\n  1\nFE %ld %ld",k,ityp[k]);
      }

/*=====================================================================
*   .. oder superelement-infos knoten schreiben (Z88NI.TXT)
*====================================================================*/
    else
      {
      pxele= 0.5*(px[1]+px[7]);
      pyele= 0.5*(py[1]+py[7]);
      pzele= 0.5*(pz[1]+pz[7]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n%lg",pxele);
      fprintf(fdxf,"\n 20\n%lg",pyele);
      fprintf(fdxf,"\n 30\n%lg",pzele);
      fprintf(fdxf,"\n 40\n%lg",texts);
      fprintf(fdxf,"\n  1\nSE %ld %ld %ld %ld %c %ld %c %ld %c",
      k,ityp[k],itypfe[k],
      jel[k],cjmode[k],iel[k],cimode[k],kel[k],ckmode[k]);
      }

    }

/*----------------------------------------------------------------------
* 2 punkte fuer ebenen stab, ebener balken
*---------------------------------------------------------------------*/
  else if(ityp[k]== 9 || ityp[k]== 13)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 2; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[2]);
      pyele= 0.5*(py[1]+py[2]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n%lg",pxele);
      fprintf(fdxf,"\n 20\n%lg",pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n%lg",texts);
      fprintf(fdxf,"\n  1\nFE %ld %ld",k,ityp[k]);
      }

    }

/*----------------------------------------------------------------------
* 2 punkte fuer raeuml stab, welle, raeuml balken
*---------------------------------------------------------------------*/
  else if(ityp[k]== 2 || ityp[k]== 4 || ityp[k]== 5)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 2; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[2]);
      pyele= 0.5*(py[1]+py[2]);
      pzele= 0.5*(pz[1]+pz[2]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n%lg",pxele);
      fprintf(fdxf,"\n 20\n%lg",pyele);
      fprintf(fdxf,"\n 30\n%lg",pzele);
      fprintf(fdxf,"\n 40\n%lg",texts);
      fprintf(fdxf,"\n  1\nFE %ld %ld",k,ityp[k]);
      }

    }

/*----------------------------------------------------------------------
* 6 punkte fuer 6-k scheibe bzw. platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 3 || ityp[k]== 14 || ityp[k]== 15 || ityp[k]== 18)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 6; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.333*(px[1]+px[2]+px[3]);
      pyele= 0.333*(py[1]+py[2]+py[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n%lg",pxele);
      fprintf(fdxf,"\n 20\n%lg",pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n%lg",texts);
      fprintf(fdxf,"\n  1\nFE %ld %ld",k,ityp[k]);
      }

    }

/*----------------------------------------------------------------------
* 3 punkte fuer 3-k torus 
*---------------------------------------------------------------------*/
  else if(ityp[k]== 6)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 3; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.333*(px[1]+px[2]+px[3]);
      pyele= 0.333*(py[1]+py[2]+py[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n%lg",pxele);
      fprintf(fdxf,"\n 20\n%lg",pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n%lg",texts);
      fprintf(fdxf,"\n  1\nFE %ld %ld",k,ityp[k]);
      }

    }

/*---------------------------------------------------------------------
* 8 punkte fuer 8-k serendipity-scheibe & -torus bzw. platte
*--------------------------------------------------------------------*/
  else if(ityp[k] == 7 || ityp[k] == 8 || ityp[k] == 20)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 8; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   entweder element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[3]);
      pyele= 0.5*(py[1]+py[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n%lg",pxele);
      fprintf(fdxf,"\n 20\n%lg",pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n%lg",texts);
      fprintf(fdxf,"\n  1\nFE %ld %ld",k,ityp[k]);
      }

/*=====================================================================
*   .. oder superelement-infos schreiben (Z88NI.TXT)
*====================================================================*/
    else
      {
      pxele= 0.5*(px[1]+px[3]);
      pyele= 0.5*(py[1]+py[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n%lg",pxele);
      fprintf(fdxf,"\n 20\n%lg",pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n%lg",texts);
      fprintf(fdxf,"\n  1\nSE %ld %ld %ld %ld %c %ld %c",
      k,ityp[k],itypfe[k],
      jel[k],cjmode[k],iel[k],cimode[k]);
      }

    }

/*----------------------------------------------------------------------
* 12 punkte fuer 12-k serendipity-scheibe & -torus
*---------------------------------------------------------------------*/
  else if(ityp[k]== 11 || ityp[k]== 12)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 12; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   entweder element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[3]);
      pyele= 0.5*(py[1]+py[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n%lg",pxele);
      fprintf(fdxf,"\n 20\n%lg",pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n%lg",texts);
      fprintf(fdxf,"\n  1\nFE %ld %ld",k,ityp[k]);
      }

/*=====================================================================
*   .. oder superelement-infos schreiben (Z88NI.TXT)
*====================================================================*/
    else
      {
      pxele= 0.5*(px[1]+px[3]);
      pyele= 0.5*(py[1]+py[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n%lg",pxele);
      fprintf(fdxf,"\n 20\n%lg",pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n%lg",texts);
      fprintf(fdxf,"\n  1\nSE %ld %ld %ld %ld %c %ld %c",
      k,ityp[k],itypfe[k],
      jel[k],cjmode[k],iel[k],cimode[k]);
      }

    }

/*----------------------------------------------------------------------
* 16 punkte fuer 16-k platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 19)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 16; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[16]);
      pyele= 0.5*(py[1]+py[16]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n%lg",pxele);
      fprintf(fdxf,"\n 20\n%lg",pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n%lg",texts);
      fprintf(fdxf,"\n  1\nFE %ld %ld",k,ityp[k]);
      }

    }

  }

/***********************************************************************
* grosse elementschleife fuer linien
***********************************************************************/
for(k= 1; k <= ne; k++)
  {
 
/*---------------------------------------------------------------------
* 8 punkte fuer 8-k hexaeder
*--------------------------------------------------------------------*/
  if(ityp[k] == 1)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 8; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 12; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n%lg",px[i1point[j]]);
      fprintf(fdxf,"\n 20\n%lg",py[i1point[j]]);
      fprintf(fdxf,"\n 30\n%lg",pz[i1point[j]]);
      fprintf(fdxf,"\n 11\n%lg",px[j1point[j]]);
      fprintf(fdxf,"\n 21\n%lg",py[j1point[j]]);
      fprintf(fdxf,"\n 31\n%lg",pz[j1point[j]]);
      }

    }

/*---------------------------------------------------------------------
* 20 punkte fuer 20-k hexaeder
*--------------------------------------------------------------------*/
  else if(ityp[k] == 10)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 20; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 24; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n%lg",px[i10point[j]]);
      fprintf(fdxf,"\n 20\n%lg",py[i10point[j]]);
      fprintf(fdxf,"\n 30\n%lg",pz[i10point[j]]);
      fprintf(fdxf,"\n 11\n%lg",px[j10point[j]]);
      fprintf(fdxf,"\n 21\n%lg",py[j10point[j]]);
      fprintf(fdxf,"\n 31\n%lg",pz[j10point[j]]);
      }

    }

/*----------------------------------------------------------------------
* 2 punkte fuer ebenen stab, ebener balken
*---------------------------------------------------------------------*/
  else if(ityp[k]== 9 || ityp[k]== 13)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 2; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
    fprintf(fdxf,"\n 10\n%lg",px[1]);
    fprintf(fdxf,"\n 20\n%lg",py[1]);
    fprintf(fdxf,"\n 30\n0.0");
    fprintf(fdxf,"\n 11\n%lg",px[2]);
    fprintf(fdxf,"\n 21\n%lg",py[2]);
    fprintf(fdxf,"\n 31\n0.0");

    }

/*----------------------------------------------------------------------
* 2 punkte fuer raeuml stab, welle, raeuml balken
*---------------------------------------------------------------------*/
  else if(ityp[k]== 2 || ityp[k]== 4 || ityp[k]== 5)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 2; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
    fprintf(fdxf,"\n 10\n%lg",px[1]);
    fprintf(fdxf,"\n 20\n%lg",py[1]);
    fprintf(fdxf,"\n 30\n%lg",pz[1]);
    fprintf(fdxf,"\n 11\n%lg",px[2]);
    fprintf(fdxf,"\n 21\n%lg",py[2]);
    fprintf(fdxf,"\n 31\n%lg",pz[2]);

    }

/*----------------------------------------------------------------------
* 6 punkte fuer 6-k scheibe bzw. platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 3 || ityp[k]== 14 || ityp[k]== 15 || ityp[k]== 18)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 6; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 6; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n%lg",px[i3point[j]]);
      fprintf(fdxf,"\n 20\n%lg",py[i3point[j]]);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 11\n%lg",px[j3point[j]]);
      fprintf(fdxf,"\n 21\n%lg",py[j3point[j]]);
      fprintf(fdxf,"\n 31\n0.0");
      }

    }

/*----------------------------------------------------------------------
* 3 punkte fuer 3-k torus 
*---------------------------------------------------------------------*/
  else if(ityp[k]== 6)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 3; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 3; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n%lg",px[i6point[j]]);
      fprintf(fdxf,"\n 20\n%lg",py[i6point[j]]);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 11\n%lg",px[j6point[j]]);
      fprintf(fdxf,"\n 21\n%lg",py[j6point[j]]);
      fprintf(fdxf,"\n 31\n0.0");
      }

    }

/*---------------------------------------------------------------------
* 8 punkte fuer 8-k serendipity-scheibe & -torus bzw. platte
*--------------------------------------------------------------------*/
  else if(ityp[k] == 7 || ityp[k] == 8 || ityp[k]== 20)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 8; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 8; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n%lg",px[i7point[j]]);
      fprintf(fdxf,"\n 20\n%lg",py[i7point[j]]);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 11\n%lg",px[j7point[j]]);
      fprintf(fdxf,"\n 21\n%lg",py[j7point[j]]);
      fprintf(fdxf,"\n 31\n0.0");
      }

    }

/*----------------------------------------------------------------------
* 12 punkte fuer 12-k serendipity-scheibe & -torus
*---------------------------------------------------------------------*/
  else if(ityp[k]== 11 || ityp[k]== 12)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 12; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 12; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n%lg",px[i11point[j]]);
      fprintf(fdxf,"\n 20\n%lg",py[i11point[j]]);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 11\n%lg",px[j11point[j]]);
      fprintf(fdxf,"\n 21\n%lg",py[j11point[j]]);
      fprintf(fdxf,"\n 31\n0.0");
      }

    }

/*---------------------------------------------------------------------
* 16 punkte fuer 16-k lagrange platte
*--------------------------------------------------------------------*/
  else if(ityp[k] == 19)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 16; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 16; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n%lg",px[i19point[j]]);
      fprintf(fdxf,"\n 20\n%lg",py[i19point[j]]);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 11\n%lg",px[j19point[j]]);
      fprintf(fdxf,"\n 21\n%lg",py[j19point[j]]);
      fprintf(fdxf,"\n 31\n0.0");
      }

    }

  }

/***********************************************************************
* file schliessen
***********************************************************************/
fprintf(fdxf,"\n  0\nENDSEC\n  0\nEOF\n");
fclose(fdxf);
 
/***********************************************************************
* Ende Z88TX
***********************************************************************/
wlog88x(0,LOG_EXITZ88TX);
wrim88x(0,TX_EXITZ88TX);
return(0);
}
