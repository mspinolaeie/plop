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
* V10.0 December 12, 2001
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
* z88ai.c
* 4.09.2002 Rieg
* Matrix- Sortieren und -Verdichten von Dipl.-Ing. Frank Koch
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88i.h>
#include <stdio.h>
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88i.h>
#endif

#include <stdlib.h>

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88i(FR_INT4,int);
int wlog88i1(FR_INT4,int);
int wtyp88i(FR_INT4,FR_INT4);
int wfor88i(FR_INT4,FR_INT4);

int vergleich(struct FR_SIJ *,struct FR_SIJ *); 

/***********************************************************************
* hier beginnt Function z88ai
***********************************************************************/
int z88ai(void)
{
extern struct FR_SIJ *IJ;
extern FR_INT4AY ip;
extern FR_INT4AY iez;
extern FR_INT4AY kc;
extern FR_INT4AY koi;
extern FR_INT4AY ioffs; 
extern FR_INT4AY ifrei; 
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;

extern FR_INT4 mcomp[];

extern FR_INT4 nkp,ne,nfg,kfoun,MAXPUF,MAXSOR,IDYNMEM;

FR_INT4 i,i2,j,j2,k,mxknot,mxfrei,mcompi,mcompj;
FR_INT4 jcoun= 0;

FR_INT4 idcoun=0,istart,iende,inc,k1,k2,m;

kfoun= 0;

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/
wrim88i(0,TX_Z88A);
wlog88i1(0,LOG_Z88A);

wrim88i(IDYNMEM,TX_SUMMEMY);

/***********************************************************************
* Berechnung des Offsetvektors ioffs
***********************************************************************/
ioffs[1]= 1;

for(i= 2;i <= nkp;i++)
  ioffs[i]= ioffs[i-1]+ifrei[i-1];

/***********************************************************************
* Aufbau der Sparse- Matrix fuer gs,obere Haelfte
***********************************************************************/
 
/*----------------------------------------------------------------------
* grosse Formatierungsschleife
*---------------------------------------------------------------------*/
wrim88i(0,TX_FORMA);
wlog88i1(0,LOG_FORMA);

for(k= 1;k <= ne;k++)
  {
/*----------------------------------------------------------------------
*  es ist ityp(k):    1  isoparametrischer hexaeder, linearer ansatz
*                     2  balken
*                     3  scheibe, dreieckig, quadratischer ansatz
*                     4  stab
*                     5  welle
*                     6  torus, dreieckig, linearer ansatz
*                     7  isoparametrische scheibe, quadratischer ansatz
*                     8  isoparametrischer torus , quadratischer ansatz
*                     9  ebenes stabelement 
*                    10  isopara. hexaeder, quadratischer ansatz
*                    11  isoparametrische scheibe, kubischer ansatz
*                    12  isoparametrischer torus,  kubischer ansatz 
*                    13  ebener balken
*                    14  krummlinige dreiecksscheibe, quadr. ansatz
*                    15  krummliniger dreieckstorus, quadr. ansatz
*                    16  krummliniger tetraeder, quadr. ansatz
*                    17  tetraeder, linearer ansatz
*                    18  6-knoten serendipity- platte
*                    19  16-knoten lagrange- platte
*                    20  8-knoten serendipity- platte
*---------------------------------------------------------------------*/

/*----------------------------------------------------------------------
* Start 8-Knoten Quader, isoparametrischer linearer Ansatz
*---------------------------------------------------------------------*/
  if(ityp[k]== 1)
    {
    wtyp88i(k,1);
 
/*----------------------------------------------------------------------
*   Formatieren fuer lqua88
*---------------------------------------------------------------------*/
    for(i= 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 3;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende isopara-8-Knoten Quader
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
*  Start  Balkenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 2)
    {
    wtyp88i(k,2);

/*----------------------------------------------------------------------
*   Formatieren fuer balk88
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[ koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[ koi[koffs[k]+1]] -1;

    mxknot= 2;
    mxfrei= 6;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende Balkenelement
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start Dreieck-Scheibenelement, quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 3)
    {
    wtyp88i(k,3);

/*----------------------------------------------------------------------
*   Formatieren fuer shei88
*---------------------------------------------------------------------*/
    for(i= 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 6;
    mxfrei= 2;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende Scheibenelement
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start Stabelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 4)
    {
    wtyp88i(k,4);

/*----------------------------------------------------------------------
*   Formatieren fuer stab88
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[ koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[ koi[koffs[k]+1]] -1;

    mxknot= 2;
    mxfrei= 3;

    goto L7000;
              
/*----------------------------------------------------------------------
*   Ende Stabelement
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
*  Start Wellenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 5)
    {
    wtyp88i(k,5);

/*-----------------------------------------------------------------------
*   Formatieren fuer well88
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[ koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[ koi[koffs[k]+1]] -1;

    mxknot= 2;
    mxfrei= 6;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende Wellenelement
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start Toruselement, linearer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 6)
    {
    wtyp88i(k,6);

/*----------------------------------------------------------------------
*   Formatieren fuer ring88
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[ koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[ koi[koffs[k]+1]] -1;
    mcomp[3]= ioffs[ koi[koffs[k]+2]] -1;

    mxknot= 3;
    mxfrei= 2;

    goto L7000;

/*-----------------------------------------------------------------------
*   Ende Toruselement
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 8-knoten Scheibe/Torus, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 7 || ityp[k]== 8)
    {
    if (ityp[k]== 7)  wtyp88i(k,7);
    else              wtyp88i(k,8);
 
/*----------------------------------------------------------------------
*   Formatieren fuer qshe88
*---------------------------------------------------------------------*/
    for(i= 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 2;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende isopara-8-Knoten Scheibe/Torus
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start ebenes Stabelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 9)
    {
    wtyp88i(k,9);

/*----------------------------------------------------------------------
*   Formatieren fuer esta88
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[ koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[ koi[koffs[k]+1]] -1;

    mxknot= 2;
    mxfrei= 2;

    goto L7000;
         
/*----------------------------------------------------------------------
*   Ende ebenes Stabelement
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 20-Knoten Quader, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 10)
    {
    wtyp88i(k,10);
 
/*-----------------------------------------------------------------------
*   Formatieren fuer hexa88
*---------------------------------------------------------------------*/
    for(i= 1;i <= 20;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 20;
    mxfrei= 3;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende isopara-20-Knoten Quader
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 12-knoten Scheibe/Torus, isoparametrischer kubischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 11 || ityp[k]== 12)
    {
    if (ityp[k]== 11)  wtyp88i(k,11);
    else               wtyp88i(k,12);
 
/*----------------------------------------------------------------------
*   Formatieren fuer cshe88
*---------------------------------------------------------------------*/
    for(i= 1;i <= 12;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 12;
    mxfrei= 2;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende isopara-12-Knoten Scheibe/Torus
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start  ebenes Balkenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 13)
    {
    wtyp88i(k,13);

/*----------------------------------------------------------------------
*   Formatieren fuer ebal88
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[ koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[ koi[koffs[k]+1]] -1;

    mxknot= 2;
    mxfrei= 3;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende ebenes Balkenelement
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 6-knoten Dreieck- Scheibe/Torus, isop. quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 14 || ityp[k]== 15)
    {
    if (ityp[k]== 14) wtyp88i(k,14);
    else              wtyp88i(k,15);

/*----------------------------------------------------------------------
*   Formatieren fuer isod88
*---------------------------------------------------------------------*/
    for(i= 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 6;
    mxfrei= 2;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende isopara-6-Knoten Dreieck-Scheibe/Torus
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 10-Knoten Tetraeder, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 16)
    {
    wtyp88i(k,16);
 
/*-----------------------------------------------------------------------
*   Formatieren fuer tetr88
*---------------------------------------------------------------------*/
    for(i= 1;i <= 10;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 10;
    mxfrei= 3;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende isopara-10-Knoten Tetraeder
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 4-Knoten Tetraeder, linearer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 17)
    {
    wtyp88i(k,17);
 
/*-----------------------------------------------------------------------
*   Formatieren fuer spur88
*---------------------------------------------------------------------*/
    for(i= 1;i <= 4;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 4;
    mxfrei= 3;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende isopara-10-Knoten Tetraeder
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 6-Knoten Reissner- Mindlin Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 18)
    {
    wtyp88i(k,18);
 
/*-----------------------------------------------------------------------
*   Formatieren fuer spla88
*---------------------------------------------------------------------*/
    for(i= 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 6;
    mxfrei= 3;

    goto L7000;

/*----------------------------------------------------------------------
* Ende 6-Knoten Reissner- Mindlin Platte
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 16-Knoten Lagrange-Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 19)
    {
    wtyp88i(k,19);
 
/*-----------------------------------------------------------------------
*   Formatieren fuer hpla88
*---------------------------------------------------------------------*/
    for(i= 1;i <= 16;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 16;
    mxfrei= 3;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende 16-Knoten Lagrange- Platte
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 8-Knoten Reissner- Mindlin Serendipity-Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 20)
    {
    wtyp88i(k,20);
 
/*-----------------------------------------------------------------------
*   Formatieren fuer apla88
*---------------------------------------------------------------------*/
    for(i= 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 3;

    goto L7000;

/*----------------------------------------------------------------------
*   Ende 8-Knoten Reissner- Mindlin Serendipity- Platte
*---------------------------------------------------------------------*/
    }

  else
/*----------------------------------------------------------------------
* falscher/unbekannter Elementtyp
*---------------------------------------------------------------------*/
    {
    wlog88i1(ityp[k],LOG_WROETYP);
    return(AL_WROETYP);
    }
    
/*----------------------------------------------------------------------
* nun Aufbau der Sparse- Matrix, aber noch unsortiert
*---------------------------------------------------------------------*/
  L7000:;

  for(j= 1;j <= mxknot;j++)
    {
    for(j2= 1;j2 <= mxfrei;j2++)
      {
      for(i= 1;i <= mxknot;i++)
        {
        for(i2= 1;i2 <= mxfrei;i2++)
          {
          mcompi= mcomp[i]+i2;
          mcompj= mcomp[j]+j2;
          
          jcoun++;

          kfoun++;
          if(kfoun >= MAXSOR)
            {
            wlog88i1(k,LOG_EXMAXSOR);
            return(AL_EXMAXSOR);
            }
            
          IJ[kfoun].izei= mcompi;
          IJ[kfoun].jspa= mcompj;

	  if(jcoun >= MAXPUF)
	    {
            wfor88i(k,kfoun);
#ifdef FR_UNIX
            fflush(stdout);
#endif
	    qsort(IJ,(kfoun+1),sizeof(struct FR_SIJ),(int (*) (const void *, const void *))vergleich);
	    jcoun = 0;
	    idcoun= 0; 

	    /*** Doppelte Stellen identifizieren ***/
	    for(k1= 2; k1 <= kfoun; k1++)
              {
              if((IJ[k1].izei == IJ[k1-1].izei) && 
                 (IJ[k1].jspa == IJ[k1-1].jspa))
                {
		idcoun++;
		kc[idcoun]= k1;
		}
              }

	    idcoun++;
	    kc[idcoun] = kfoun + 1;

	    /*** Umspeichern ***/
	    inc = 0;
	    for(k2= 2;k2 <= idcoun;k2++)
              {
              istart= kc[k2-1] + 1;
              iende = kc[k2] - 1;
              inc++;
              for(m= istart;m <= iende;m++)
                {
                IJ[m-inc].izei = IJ[m].izei;
                IJ[m-inc].jspa = IJ[m].jspa;
                }
              }

            kfoun = kfoun - inc;
            }

          }
        }
      }
    }

/***********************************************************************
* Ende der Schleife ueber alle Elemente
***********************************************************************/
  }                                              /* ende Form-Slei */

wrim88i(kfoun,TX_NONZ);

/***********************************************************************
* Sparse- Matrix gs fertig sortieren
***********************************************************************/

/*----------------------------------------------------------------------
* nun richtiger Aufbau der Sparse- Matrix
*---------------------------------------------------------------------*/
qsort(IJ,(kfoun+1),sizeof(struct FR_SIJ),(int (*) (const void *, const void *))vergleich);

/*----------------------------------------------------------------------
* Doppelte Stellen identifizieren
*---------------------------------------------------------------------*/
idcoun = 0; 

for(k= 2; k <= kfoun; k++)
  {
  if((IJ[k].izei == IJ[k-1].izei) && (IJ[k].jspa == IJ[k-1].jspa))
    {
    idcoun++;
    kc[idcoun]= k;
    }
  }

idcoun++;
kc[idcoun] = kfoun + 1;

/*----------------------------------------------------------------------
* Umspeichern
*---------------------------------------------------------------------*/
inc = 0;

for(i= 2;i <= idcoun;i++)
  {
  istart= kc[i-1] + 1;
  iende = kc[i] - 1;
  inc++;
  for(j= istart;j <= iende;j++)
    {
    IJ[j-inc].izei = IJ[j].izei;
    IJ[j-inc].jspa = IJ[j].jspa;
    }
  }

  kfoun = kfoun - inc;

/*----------------------------------------------------------------------
* iez und ip neu bestimmen
* Pointervektor ip zeigt auf die Diagonalelemente a(i,i)
* Pointervektor iez zeigt auf die Spaltenindices a(x,j)
*---------------------------------------------------------------------*/
ip[0]= 0;  /* sehr wichtig fuer Z88BI */
i = 1;
j = 1;

for(k= 1; k <= kfoun; k++)
  {
  if(IJ[k].jspa < IJ[k].izei)
    {
    iez[j]= IJ[k].jspa;
    j++;
    }
  if((IJ[k].izei == i) && (IJ[k].jspa == i))
    {
    iez[j]= IJ[k].jspa;
    ip[i] = j;
    i++;
    j++;
    }
  }


/***********************************************************************
* Ende Z88AI
***********************************************************************/
kfoun= ip[nfg];

wrim88i(0,TX_GSSO);
wlog88i1(0,LOG_EXITZ88A);
return(0);
}

/**********************************************************************
 * Funktion vergleiche
 *********************************************************************/
int vergleich(struct FR_SIJ *a,struct FR_SIJ *b)
{
if(a->izei > b->izei) return 1;
else if(a->izei < b->izei) return -1;
else
  {
    if(a->jspa > b->jspa) return 1;
    else if(a->jspa < b->jspa) return -1;
    else return 0;
  }
}

