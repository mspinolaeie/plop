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
* z88b.c mit Jennings- Speicherung
* 25.8.2005 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88f.h>
#include <stdio.h>    /* FILE,fclose */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88f.h>
#include <stdio.h>    /* FILE,fclose */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88f(FR_INT4,int);
int wlog88f(FR_INT4,int);
int wproz88(FR_INT4,FR_DOUBLE);
int wtyp88f(FR_INT4,FR_INT4);
int ri588(void);
int lqua88(void);
int balk88(void);
int shei88(void);
int stab88(void);
int well88(void);
int ring88(void);
int qshe88(void);
int esta88(void);
int hexa88(void);
int cshe88(void);
int ebal88(void);
int isod88(void);
int tetr88(void);
int spur88(void);
int spla88(void);
int hpla88(void);
int apla88(void);
int btetr88(void);
int bspla88(void);
int bqshe88(void);
int bhexa88(void);
int bspur88(void);
int blqua88(void);
int bcshe88(void);
int bapla88(void);
int bhpla88(void);

/***********************************************************************
* hier beginnt Function z88b
***********************************************************************/
int z88b(void)
{
extern FILE *fwlo;

extern FR_DOUBLEAY gs;
extern FR_DOUBLEAY se;
extern FR_DOUBLEAY rs;
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
extern FR_DOUBLEAY pres;
extern FR_DOUBLEAY tr1;
extern FR_DOUBLEAY tr2;

extern FR_INT4AY ip;
extern FR_INT4AY koi;
extern FR_INT4AY ioffs; 
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;
extern FR_INT4AY ivon;
extern FR_INT4AY ibis;
extern FR_INT4AY intord;
extern FR_INT4AY noi;
extern FR_INT4AY noffs; 
extern FR_INT4AY nep;

extern FR_DOUBLE xk[],yk[],zk[],be[];
extern FR_INT4 mcomp[];

extern FR_DOUBLE emode,rnuee,qparae,riyye,eyye,rizze,ezze,rite,wte;
extern FR_DOUBLE pree,tr1e,tr2e;
extern FR_INT4 intore,ktyp;
extern FR_INT4 MAXGS,MAXKOI;
extern FR_INT4 ne,nfg,neg,ibflag,ipflag,iqflag,nkoi,npr;

FR_DOUBLE proz;

FR_INT4 i,k,mxknot,mxfrei,index;
FR_INT4 ise,j,j2,i2,mcompi,mcompj,inull;

int iret;

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/
wrim88f(0,TX_Z88B);
wlog88f(0,LOG_Z88B);

mxknot = 0;
mxfrei = 0; /* nur wg. compiler warnings */

/*----------------------------------------------------------------------
* Ueberpruefen der Grenzen
*---------------------------------------------------------------------*/
if(ip[nfg+1] > MAXGS)
  {
  wlog88f((ip[nfg+1]),LOG_EXGS);
  fclose(fwlo);
  return(AL_EXGS);
  }

if(nkoi > MAXKOI)
  {
  wlog88f(nkoi,LOG_EXKOI);
  fclose(fwlo);
  return(AL_EXKOI);
  }

/*----------------------------------------------------------------------
* gs nullsetzen
*---------------------------------------------------------------------*/
for(i = 1;i <= ip[nfg+1];i++)
  gs[i]= 0.;

/*----------------------------------------------------------------------
* rs nullsetzen; hier werden die Elementvektoren aufaddiert
*---------------------------------------------------------------------*/
for(i = 1;i <= nfg;i++)
  rs[i]= 0.;

/***********************************************************************
* Berechnen der Elementsteifigkeitsmatrizen, Compilation  
***********************************************************************/
wrim88f(0,TX_COMPI);
wlog88f(0,LOG_COMPI);

for(k= 1;k <= ne;k++)
  {

/*----------------------------------------------------------------------
*  es ist ityp(k):    1  isoparametrischer hexaeder, linearer ansatz
*                     2  balken
*                     3  scheibe, dreieckig, quadratischer ansatz
*                     4  raeumlicher stab
*                     5  welle
*                     6  torus, dreieckig, linearer ansatz
*                     7  isoparametrische scheibe, quadratischer ansatz
*                     8  isoparametrischer torus , quadratischer ansatz
*                     9  ebenes stabelement 
*                    10  isop. serendipity hexaeder, quadratischer ans.
*                    11  isoparametrische scheibe, kubischer ansatz
*                    12  isoparametrischer torus,  kubischer ansatz 
*                    13  ebenes balkenelement
*                    14  isop. dreieck scheibe, quadratischer ansatz
*                    15  isop. dreieck torus, quadratischer ansatz
*                    16  isop. tetraeder, quadratischer ansatz
*                    17  tetraeder, linearer ansatz
*                    18  6-Knoten Serendipity- Platte
*                    19  16-Knoten Lagrange- Platte
*                    20  8-Knoten Serendipity- Platte
*---------------------------------------------------------------------*/
/*----------------------------------------------------------------------
* zunaechst E-modul und Nue feststellen
*---------------------------------------------------------------------*/
for(i = 1;i <= neg;i++)
  {
  if(k >= ivon[i] && k <= ibis[i])
    {
    emode = emod[i];
    rnuee = rnue[i];
    intore= intord[i];
    qparae= qpara[i];

    if(ibflag == 1)
      {
      riyye= riyy[i];
      eyye = eyy[i];
      rizze= rizz[i];
      ezze = ezz[i];
      rite = rit[i];
      wte  = wt[i];
      } 

    if(ipflag != 0)
      {
      riyye= riyy[i];
      } 

    goto L60;
    }
  }

L60:;

/*----------------------------------------------------------------------
* Start 8-Knoten Quader, isoparametrischer linearer Ansatz
*---------------------------------------------------------------------*/
  if(ityp[k]== 1)
    {
    wtyp88f(k,1);

/*----------------------------------------------------------------------
* isopara 8-Knoten Hexaeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-8-Knoten Hexaeder berechen
*---------------------------------------------------------------------*/
    iret= lqua88();
    if(iret != 0)
      {
      wlog88f(0,LOG_JACNEG);
      fclose(fwlo);
      return(iret);
      }
      
/*----------------------------------------------------------------------
* Compilation fuer lqua88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 3;            
  
    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-8-Knoten Hexaeder
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Balkenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 2)
    {
    wtyp88f(k,2);

/*----------------------------------------------------------------------
* Balkenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    zk[1] = z [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    zk[2] = z [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Elementsteifigkeitsmatrix fuer Balkenelement berechen
*---------------------------------------------------------------------*/
    iret= balk88();

/*----------------------------------------------------------------------
* Compilation fuer balk88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 6;

    goto L7000;

/*----------------------------------------------------------------------
* Ende Balkenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Dreieck-Scheibenelement, quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 3)
    {
    wtyp88f(k,3);

/*----------------------------------------------------------------------
* Scheibenelement: zutreffende Koordinaten bestimmen 
* die Mittenknoten werden nicht gebraucht
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    xk[3] = x [koi[koffs[k]+2]];
    yk[3] = y [koi[koffs[k]+2]];

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer Scheibenelement berechen
*---------------------------------------------------------------------*/
    iret= shei88();
    if(iret != 0)
      {
      wlog88f(0,LOG_JACNEG);
      fclose(fwlo);
      return(iret);
      }

/*-----------------------------------------------------------------------
* Compilation fuer shei88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 6;
    mxfrei= 2;

    goto L7000;

/*----------------------------------------------------------------------
* Ende 6-k Scheibenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start raeumliches Stabelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 4)
    {
    wtyp88f(k,4);

/*----------------------------------------------------------------------
* raeumliches Stabelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    zk[1] = z [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    zk[2] = z [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer raeumliches Stabelement berechen
*---------------------------------------------------------------------*/
    iret= stab88();

/*----------------------------------------------------------------------
* Compilation fuer stab88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 3;

    goto L7000;

/*----------------------------------------------------------------------
* Ende raeumliches Stabelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Wellenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 5)
    {
    wtyp88f(k,5);

/*----------------------------------------------------------------------
* Wellenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer Wellenelement berechen
*---------------------------------------------------------------------*/
    iret= well88();

/*----------------------------------------------------------------------
* Compilation fuer well88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[ koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[ koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 6;

    goto L7000;

/*----------------------------------------------------------------------
* Ende Wellenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Toruselement, linearer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 6)
    {
    wtyp88f(k,6);

/*----------------------------------------------------------------------
* Toruselement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    xk[3] = x [koi[koffs[k]+2]];
    yk[3] = y [koi[koffs[k]+2]];
          
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer Toruselement berechen
*---------------------------------------------------------------------*/
    iret= ring88();

/*----------------------------------------------------------------------
* Compilation fuer ring88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[koi[koffs[k]+1]] -1;
    mcomp[3]= ioffs[koi[koffs[k]+2]] -1;
         
    mxknot= 3;
    mxfrei= 2;

    goto L7000;

/*----------------------------------------------------------------------
* Ende Toruselement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 8-knoten Scheibe/Torus, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 7 || ityp[k]== 8)
    {
    if (ityp[k]== 7)
      {
      wtyp88f(k,7);
      ktyp= 2;
      }
    else
      {
      wtyp88f(k,8);
      ktyp= 0;
      }

/*----------------------------------------------------------------------
* isopara 8-Knoten Scheibe/Torus: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-8-knoten Scheibe/Tor  berechen
*---------------------------------------------------------------------*/
    iret= qshe88();
    if(iret != 0)
      {
      wlog88f(0,LOG_JACNEG);
      fclose(fwlo);
      return(iret);
      }
    
/*----------------------------------------------------------------------
* Compilation fuer qshe88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 8;
    mxfrei= 2;

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-8-Knoten Scheibe/Torus
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start ebenes Stabelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 9)
    {
    wtyp88f(k,9);

/*----------------------------------------------------------------------
* ebenes Stabelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer e. Stabelement berechen
*---------------------------------------------------------------------*/
    iret= esta88();

/*----------------------------------------------------------------------
* Compilation fuer esta88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[ koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[ koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 2;
             
    goto L7000;
    
/*----------------------------------------------------------------------
* Ende ebenes Stabelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 20-Knoten Hexaeder, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 10)
    {
    wtyp88f(k,10);
 
/*----------------------------------------------------------------------
* isopara 20-Knoten Hexaeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 20;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-20-Knoten Hexaeder berechen
*---------------------------------------------------------------------*/
    iret= hexa88();
    if(iret != 0)
      {
      wlog88f(0,LOG_JACNEG);
      fclose(fwlo);
      return(iret);
      }

/*----------------------------------------------------------------------
* Compilation fuer hexa88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 20;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 20;
    mxfrei= 3;
  
    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-20-Knoten Hexaeder
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 12-knoten Scheibe/Torus, isoparametrischer kubischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 11 || ityp[k]== 12)
    {
    if (ityp[k]== 11)
      {
      wtyp88f(k,11);
      ktyp= 2;
      }
    else
      {
      wtyp88f(k,12);
      ktyp= 0;
      }
      
/*----------------------------------------------------------------------
* isopara 12-Knoten Scheibe/Torus: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 12;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-12-Knoten Scheibe/Tor  ber.
*---------------------------------------------------------------------*/
    iret= cshe88();
    if(iret != 0)
      {
      wlog88f(0,LOG_JACNEG);
      fclose(fwlo);
      return(iret);
      }

/*----------------------------------------------------------------------
* Compilation fuer cshe88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 12;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 12;
    mxfrei= 2;

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-12-Knoten Scheibe/Torus
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start ebenes Balkenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 13)
    {
    wtyp88f(k,13);

/*----------------------------------------------------------------------
* Balkenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Elementsteifigkeitsmatrix fuer ebenes Balkenelement berechen
*---------------------------------------------------------------------*/
    iret= ebal88();

/*----------------------------------------------------------------------
* Compilation fuer ebal88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 3;

    goto L7000;

/*----------------------------------------------------------------------
* Ende ebenes Balkenelement
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 6-knoten Dreieck- Scheibe/Torus, isop. quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 14 || ityp[k]== 15)
    {
    if (ityp[k]== 14)
      {
      wtyp88f(k,14);
      ktyp= 2;
      }
    else
      {
      wtyp88f(k,15);
      ktyp= 0;
      }

/*----------------------------------------------------------------------
* isopara 6-Knoten Dreieck: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-6-knoten Dreieck berechen
*---------------------------------------------------------------------*/
    iret= isod88();
    if(iret != 0)
      {
      wlog88f(0,LOG_JACNEG);
      fclose(fwlo);
      return(iret);
      }
    
/*----------------------------------------------------------------------
* Compilation fuer isod88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 6;
    mxfrei= 2;

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-6-Knoten Dreieck-Scheibe/Torus
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 10-Knoten Tetraeder, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 16)
    {
    wtyp88f(k,16);
 
/*----------------------------------------------------------------------
* isopara 10-Knoten Tetraeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 10;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-10-Knoten Tetraeder berechen
*---------------------------------------------------------------------*/
    iret= tetr88();
    if(iret != 0)
      {
      wlog88f(0,LOG_JACNEG);
      fclose(fwlo);
      return(iret);
      }

/*----------------------------------------------------------------------
* Compilation fuer tetr88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 10;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 10;
    mxfrei= 3;
  
    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-10-Knoten Tetraeder
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 4-Knoten Tetraeder, linearer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 17)
    {
    wtyp88f(k,17);
 
/*----------------------------------------------------------------------
* 4-Knoten Tetraeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 4;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 4-Knoten Tetraeder berechen
*---------------------------------------------------------------------*/
    iret= spur88();
    if(iret != 0)
      {
      wlog88f(0,LOG_JACNEG);
      fclose(fwlo);
      return(iret);
      }

/*----------------------------------------------------------------------
* Compilation fuer spur88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 4;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 4;
    mxfrei= 3;
  
    goto L7000;

/*----------------------------------------------------------------------
* Ende 4-Knoten Tetraeder
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 6-Knoten Reissner- Mindlin Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 18)
    {
    wtyp88f(k,18);
 
/*----------------------------------------------------------------------
* 6-Knoten Platte: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 6-Knoten Platte berechen
*---------------------------------------------------------------------*/
    iret= spla88();
    if(iret != 0)
      {
      wlog88f(0,LOG_JACNEG);
      fclose(fwlo);
      return(iret);
      }

/*----------------------------------------------------------------------
* Compilation fuer spla88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 6;
    mxfrei= 3;
  
    goto L7000;

/*----------------------------------------------------------------------
* Ende 6-Knoten Reissner- Mindlin Platte
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 16-Knoten Lagrange- Reissner- Mindlin Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 19)
    {
    wtyp88f(k,19);
 
/*----------------------------------------------------------------------
* 16-Knoten Platte: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 16;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 16-Knoten Platte berechen
*---------------------------------------------------------------------*/
    iret= hpla88();
    if(iret != 0)
      {
      wlog88f(0,LOG_JACNEG);
      fclose(fwlo);
      return(iret);
      }

/*----------------------------------------------------------------------
* Compilation fuer hpla88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 16;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 16;
    mxfrei= 3;
  
    goto L7000;

/*----------------------------------------------------------------------
* Ende 16-Knoten Lagrange- Reissner- Mindlin Platte
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 8-Knoten Reissner- Mindlin Serendipity-Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 20)
    {
    wtyp88f(k,20);
 
/*----------------------------------------------------------------------
* 8-Knoten Platte: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 8-Knoten Platte berechen
*---------------------------------------------------------------------*/
    iret= apla88();
    if(iret != 0)
      {
      wlog88f(0,LOG_JACNEG);
      fclose(fwlo);
      return(iret);
      }

/*----------------------------------------------------------------------
* Compilation fuer apla88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 3;
  
    goto L7000;

/*----------------------------------------------------------------------
* Ende 8-Knoten Reissner- Mindlin Serendipity-Platte
*---------------------------------------------------------------------*/
    } 
       
/*----------------------------------------------------------------------
* nun Compilation ausfuehren (Jennings- Speicherung)
*---------------------------------------------------------------------*/
L7000:;

  ise= 0;
        
  for(j = 1;j <= mxknot;j++)
    {
    for(j2 = 1;j2 <= mxfrei;j2++)
      {
      for(i = 1;i <= mxknot;i++)
        {
        for(i2 = 1;i2 <= mxfrei;i2++)
          {
          mcompi= mcomp[i]+i2;
          mcompj= mcomp[j]+j2;
          ise++;
          if(mcompj <= mcompi)
            {
            index= ip[mcompi] - (mcompi - mcompj);
            gs[index] += se[ise];
            }
          }
        }
      }
    }

/*----------------------------------------------------------------------
* fuer Platten den Elementvektor hinzuaddieren
*---------------------------------------------------------------------*/
  if(ipflag != 0 && iqflag == 0)
    { 
    ise= 0;
       
    for(i = 1;i <= mxknot;i++)
      {
      for(i2 = 1;i2 <= mxfrei;i2++)
        {
        ise++;
        mcompi= mcomp[i]+i2;
        rs[mcompi] += be[ise];
        }
      }
    }
          
/***********************************************************************
* Ende der Schleife ueber alle Elemente
***********************************************************************/
  }

/***********************************************************************
* Berechnen des Lastvektors  
***********************************************************************/
if(iqflag == 1)
  {
  iret= ri588();
  if(iret != 0) return iret;

  for(k= 1;k <= npr;k++)
    {
    pree= pres[k];

/*----------------------------------------------------------------------
* Typ 18: Sechsknoten-Platte SPLA88.C, hier BSPLA88.C
*---------------------------------------------------------------------*/
    if(ityp[nep[k]]== 18)
      {
/*======================================================================
* zutreffende Koordinaten bestimmen 
*=====================================================================*/
      for(i = 1;i <= 6;i++)
        {
        xk[i] = x [koi[koffs[nep[k]]+i-1]];
        yk[i] = y [koi[koffs[nep[k]]+i-1]];
        }

/*======================================================================
* nun Lastvektor berechen
*=====================================================================*/
      iret= bspla88();
      if(iret != 0)
        {
        wlog88f(k,LOG_JACLOA);
        fclose(fwlo);
        return(iret);
        }      

      for(i = 1;i <= 6;i++)
        mcomp[i]= ioffs[koi[koffs[nep[k]]+i-1]] -1;
         
      mxknot= 6;
      mxfrei= 3;

      goto L8000;
      }

/*----------------------------------------------------------------------
* Typ 19: 16-Knoten-Platte HPLA88.C, hier BHPLA88.C
*---------------------------------------------------------------------*/
    if(ityp[nep[k]]== 19)
      {
/*======================================================================
* zutreffende Koordinaten bestimmen 
*=====================================================================*/
      for(i = 1;i <= 16;i++)
        {
        xk[i] = x [koi[koffs[nep[k]]+i-1]];
        yk[i] = y [koi[koffs[nep[k]]+i-1]];
        }

/*======================================================================
* nun Lastvektor berechen
*=====================================================================*/
      iret= bhpla88();
      if(iret != 0)
        {
        wlog88f(k,LOG_JACLOA);
        fclose(fwlo);
        return(iret);
        }      

      for(i = 1;i <= 16;i++)
        mcomp[i]= ioffs[koi[koffs[nep[k]]+i-1]] -1;
         
      mxknot= 16;
      mxfrei= 3;

      goto L8000;
      }

/*----------------------------------------------------------------------
* Typ 20: 8-Knoten-Platte APLA88.C, hier BAPLA88.C
*---------------------------------------------------------------------*/
    if(ityp[nep[k]]== 20)
      {
/*======================================================================
* zutreffende Koordinaten bestimmen 
*=====================================================================*/
      for(i = 1;i <= 8;i++)
        {
        xk[i] = x [koi[koffs[nep[k]]+i-1]];
        yk[i] = y [koi[koffs[nep[k]]+i-1]];
        }

/*======================================================================
* nun Lastvektor berechen
*=====================================================================*/
      iret= bapla88();
      if(iret != 0)
        {
        wlog88f(k,LOG_JACLOA);
        fclose(fwlo);
        return(iret);
        }      

      for(i = 1;i <= 8;i++)
        mcomp[i]= ioffs[koi[koffs[nep[k]]+i-1]] -1;
         
      mxknot= 8;
      mxfrei= 3;

      goto L8000;
      }

/*----------------------------------------------------------------------
* Typ 7: Achtknoten-Scheibe QSHE88.C, hier BQSHE88.C
* auch fuer Elemente 8,14,15
*---------------------------------------------------------------------*/
    if(ityp[nep[k]]== 7  || ityp[nep[k]]== 8 ||
       ityp[nep[k]]== 14 || ityp[nep[k]]== 15)
      {
      tr1e= tr1[k];

/*======================================================================
* zutreffende Koordinaten bestimmen 
*=====================================================================*/
      for(i = 1;i <= 3;i++)
        {
        xk[i] = x [noi[noffs[k]+i-1]];
        yk[i] = y [noi[noffs[k]+i-1]];
        }

/*======================================================================
* nun Lastvektor berechen
*=====================================================================*/
      bqshe88();

      for(i = 1;i <= 3;i++)
        mcomp[i]= ioffs[noi[noffs[k]+i-1]] -1;
         
      mxknot= 3;
      mxfrei= 2;

      goto L8000;
      }

/*----------------------------------------------------------------------
* Typ 16: 10-Knoten Tetraeder TETR88.C, hier BTETR88.C
*---------------------------------------------------------------------*/
    if(ityp[nep[k]]== 16)
      {

/*----------------------------------------------------------------------
* zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
      for(i = 1;i <= 6;i++)
        {
        xk[i] = x [noi[noffs[k]+i-1]];
        yk[i] = y [noi[noffs[k]+i-1]];
        zk[i] = z [noi[noffs[k]+i-1]];
        }

/*----------------------------------------------------------------------
* nun Lastvektor berechen
*---------------------------------------------------------------------*/
      btetr88();

      for(i = 1;i <= 6;i++)
        mcomp[i]= ioffs[noi[noffs[k]+i-1]] -1;
         
      mxknot= 6;
      mxfrei= 3;

      goto L8000;
      }

/*----------------------------------------------------------------------
* Typ 17: 4-Knoten Tetraeder SPUR88.C, hier BSPUR88.C
*---------------------------------------------------------------------*/
    if(ityp[nep[k]]== 17)
      {

/*----------------------------------------------------------------------
* zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
      for(i = 1;i <= 3;i++)
        {
        xk[i] = x [noi[noffs[k]+i-1]];
        yk[i] = y [noi[noffs[k]+i-1]];
        zk[i] = z [noi[noffs[k]+i-1]];
        }

/*----------------------------------------------------------------------
* nun Lastvektor berechen
*---------------------------------------------------------------------*/
      bspur88();

      for(i = 1;i <= 3;i++)
        mcomp[i]= ioffs[noi[noffs[k]+i-1]] -1;
         
      mxknot= 3;
      mxfrei= 3;

      goto L8000;
      }

/*----------------------------------------------------------------------
* Typ 10: 20-Knoten Hexaeder HEXA88.C, hier BHEXA88:C
*---------------------------------------------------------------------*/
    if(ityp[nep[k]]== 10)
      {
      tr1e= tr1[k];
      tr2e= tr2[k];

/*----------------------------------------------------------------------
* zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
      for(i = 1;i <= 8;i++)
        {
        xk[i] = x [noi[noffs[k]+i-1]];
        yk[i] = y [noi[noffs[k]+i-1]];
        zk[i] = z [noi[noffs[k]+i-1]];
        }

/*----------------------------------------------------------------------
* nun Lastvektor berechen
*---------------------------------------------------------------------*/
      bhexa88();

      for(i = 1;i <= 8;i++)
        mcomp[i]= ioffs[noi[noffs[k]+i-1]] -1;
         
      mxknot= 8;
      mxfrei= 3;

      goto L8000;
      }

/*----------------------------------------------------------------------
* Typ 1: 8-Knoten Hexaeder LQUA88.C, hier BLQUA88:C
*---------------------------------------------------------------------*/
    if(ityp[nep[k]]== 1)
      {
      tr1e= tr1[k];
      tr2e= tr2[k];

/*----------------------------------------------------------------------
* zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
      for(i = 1;i <= 4;i++)
        {
        xk[i] = x [noi[noffs[k]+i-1]];
        yk[i] = y [noi[noffs[k]+i-1]];
        zk[i] = z [noi[noffs[k]+i-1]];
        }

/*----------------------------------------------------------------------
* nun Lastvektor berechen
*---------------------------------------------------------------------*/
      blqua88();

      for(i = 1;i <= 4;i++)
        mcomp[i]= ioffs[noi[noffs[k]+i-1]] -1;
         
      mxknot= 4;
      mxfrei= 3;

      goto L8000;
      }

/*----------------------------------------------------------------------
* Typ 11, 12: 12-Knoten Scheibe oder Torus, CSHE88.C, hier BCSHE88:C
*---------------------------------------------------------------------*/
    if(ityp[nep[k]]== 11 || ityp[nep[k]]== 12)
      {
      tr1e= tr1[k];

/*----------------------------------------------------------------------
* zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
      for(i = 1;i <= 4;i++)
        {
        xk[i] = x [noi[noffs[k]+i-1]];
        yk[i] = y [noi[noffs[k]+i-1]];
        }

/*----------------------------------------------------------------------
* nun Lastvektor berechen
*---------------------------------------------------------------------*/
      bcshe88();

      for(i = 1;i <= 4;i++)
        mcomp[i]= ioffs[noi[noffs[k]+i-1]] -1;
         
      mxknot= 4;
      mxfrei= 2;

      goto L8000;
      }

/*----------------------------------------------------------------------
* Lastvektor einbauen
*---------------------------------------------------------------------*/
L8000:
     ise= 0;
   
     for(i = 1;i <= mxknot;i++)
       {
       for(i2 = 1;i2 <= mxfrei;i2++)
         {
         ise++;
         mcompi= mcomp[i]+i2;
         rs[mcompi] += be[ise];
         }
       }

/***********************************************************************
* Ende der Schleife ueber alle Elemente mit Druck; Ende if iqflag
***********************************************************************/
    } 
  } 

/*----------------------------------------------------------------------
* Nullanteil feststellen
*---------------------------------------------------------------------*/
inull= 0;

for(i = 1;i <= ip[nfg];i++)
  if(gs[i] == 0.) inull++;

proz= (FR_DOUBLE)inull / (FR_DOUBLE)ip[nfg] * 100.;

wproz88(ip[nfg],proz);

/*----------------------------------------------------------------------
* Ende Z88B
*---------------------------------------------------------------------*/
wlog88f(0,LOG_EXITZ88B);
return(0);
}
