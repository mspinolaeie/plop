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
* prfl88 schreibt Flaechenlasten als Kontrolle in Z88O1.TXT
* 29.9.2005 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88f.h>
#include <stdio.h>
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88f.h>
#include <stdio.h>
#endif

/***********************************************************************
* hier beginnt Function prfl88
***********************************************************************/
int prfl88(void)
{
extern FILE *fo1;

extern FR_DOUBLEAY pres;
extern FR_DOUBLEAY tr1;
extern FR_DOUBLEAY tr2;

extern FR_INT4AY ityp;
extern FR_INT4AY noi;
extern FR_INT4AY noffs; 
extern FR_INT4AY nep;

extern FR_INT4 npr,LANG;

FR_INT4 j;

/*---------------------------------------------------------------------*
* Beschreiben Z88O1.TXT, Ueberschrift
*---------------------------------------------------------------------*/
fprintf(fo1,"\n");

if(LANG == 1)
{
fprintf(fo1,"Ausgabedatei Z88O1.TXT  Flaechenlasten\n");
fprintf(fo1,"                        **************\n\n");
fprintf(fo1,"Anzahl gegebene Flaechenlasten: %ld\n\n",npr);
}

if(LANG == 2)
{
fprintf(fo1,"output file Z88O1.TXT : surface loads\n");
fprintf(fo1,"                        *************\n\n");
fprintf(fo1,"number of given surface loads: %ld\n\n",npr);
}

/*---------------------------------------------------------------------*
* Schleife
*---------------------------------------------------------------------*/
for(j= 1; j <= npr; j++)
  {
/*======================================================================
* Elementtypen 7, 8, 14, 15
*=====================================================================*/
  if(ityp[nep[j]]== 7  || ityp[nep[j]]== 8 ||
  ityp[nep[j]]== 14 || ityp[nep[j]]== 15) 
    {
#ifdef FR_XDOUB
    if(LANG == 1)
      fprintf(fo1,"Element# %5ld   Normallast %+#13.5lE   Schub r %+#13.5lE\
   Knoten %5ld %5ld %5ld\n",nep[j],pres[j],tr1[j],
      noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]); 
    if(LANG == 2)
      fprintf(fo1,"element# %5ld   normal load %+#13.5lE  shear r %+#13.5lE\
   nodes %5ld %5ld %5ld\n",nep[j],pres[j],tr1[j],
      noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]); 
#endif
#ifdef FR_XQUAD
    if(LANG == 1)
      fprintf(fo1,"Element# %5ld   Normallast %+#13.5LE   Schub r %+#13.5LE\
   Knoten %5ld %5ld %5ld\n",nep[j],pres[j],tr1[j],
      noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]); 
    if(LANG == 2)
      fprintf(fo1,"element# %5ld   normal load %+#13.5LE  shear r %+#13.5LE\
   nodes %5ld %5ld %5ld\n",nep[j],pres[j],tr1[j],
      noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]); 
#endif
    }

/*======================================================================
* Elementtyp 17
*=====================================================================*/
  if(ityp[nep[j]]== 17) 
    {
#ifdef FR_XDOUB
    if(LANG == 1)
      fprintf(fo1,"Element# %5ld   Druck %+#13.5lE   Knoten %5ld %5ld %5ld\n",
      nep[j],pres[j],noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]); 
    if(LANG == 2)
      fprintf(fo1,"element# %5ld   pressure %+#13.5lE   nodes %5ld %5ld %5ld\n",
      nep[j],pres[j],noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]); 
#endif
#ifdef FR_XQUAD
    if(LANG == 1)
      fprintf(fo1,"Element# %5ld   Druck %+#13.5LE   Knoten %5ld %5ld %5ld\n",
      nep[j],pres[j],noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]); 
    if(LANG == 2)
      fprintf(fo1,"element# %5ld   pressure %+#13.5LE   nodes %5ld %5ld %5ld\n",
      nep[j],pres[j],noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]); 
#endif
    }

/*======================================================================
* Elementtyp 16
*=====================================================================*/
  if(ityp[nep[j]]== 16) 
    {
#ifdef FR_XDOUB
    if(LANG == 1)
      fprintf(fo1,"Element# %5ld   Druck %+#13.5lE\
   Knoten %5ld %5ld %5ld %5ld %5ld %5ld\n",nep[j],pres[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],
      noi[noffs[j]+3],noi[noffs[j]+4],noi[noffs[j]+5]); 
    if(LANG == 2)
      fprintf(fo1,"element# %5ld   pressure %+#13.5lE\
   nodes %5ld %5ld %5ld %5ld %5ld %5ld\n",nep[j],pres[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],
      noi[noffs[j]+3],noi[noffs[j]+4],noi[noffs[j]+5]); 
#endif
#ifdef FR_XQUAD
    if(LANG == 1)
      fprintf(fo1,"Element# %5ld   Druck %+#13.5LE\
   Knoten %5ld %5ld %5ld %5ld %5ld %5ld\n",nep[j],pres[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],
      noi[noffs[j]+3],noi[noffs[j]+4],noi[noffs[j]+5]); 
    if(LANG == 2)
      fprintf(fo1,"element# %5ld   pressure %+#13.5LE\
   nodes %5ld %5ld %5ld %5ld %5ld %5ld\n",nep[j],pres[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],
      noi[noffs[j]+3],noi[noffs[j]+4],noi[noffs[j]+5]); 
#endif
    }

/*======================================================================
* Elementtyp 10
*=====================================================================*/
  if(ityp[nep[j]]== 10) 
    {
#ifdef FR_XDOUB
    if(LANG == 1)
      fprintf(fo1,
      "Element# %5ld   Druck %+#13.5lE   Schub r %+#13.5lE   Schub s %+#13.5lE\
   Knoten %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3],
      noi[noffs[j]+4],noi[noffs[j]+5],noi[noffs[j]+6],noi[noffs[j]+7]); 
    if(LANG == 2)
      fprintf(fo1,
      "Element# %5ld   pressure %+#13.5lE   shear r %+#13.5lE   shear s %+#13.5lE\
   nodes %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3],
      noi[noffs[j]+4],noi[noffs[j]+5],noi[noffs[j]+6],noi[noffs[j]+7]); 
#endif
#ifdef FR_XQUAD
    if(LANG == 1)
      fprintf(fo1,
      "Element# %5ld   Druck %+#13.5LE   Schub r %+#13.5LE   Schub s %+#13.5LE\
   Knoten %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3],
      noi[noffs[j]+4],noi[noffs[j]+5],noi[noffs[j]+6],noi[noffs[j]+7]); 
    if(LANG == 2)
      fprintf(fo1,
      "Element# %5ld   pressure %+#13.5LE   shear r %+#13.5LE   shear s %+#13.5LE\
   nodes %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3],
      noi[noffs[j]+4],noi[noffs[j]+5],noi[noffs[j]+6],noi[noffs[j]+7]); 
#endif
    }

/*======================================================================
* Elementtyp 1
*=====================================================================*/
  if(ityp[nep[j]]== 1) 
    {
#ifdef FR_XDOUB
    if(LANG == 1)
      fprintf(fo1,
      "Element# %5ld   Druck %+#13.5lE   Schub r %+#13.5lE   Schub s %+#13.5lE\
   Knoten %5ld %5ld %5ld %5ld\n",
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3]);
    if(LANG == 2)
      fprintf(fo1,
      "Element# %5ld   pressure %+#13.5lE   shear r %+#13.5lE   shear s %+#13.5lE\
   nodes %5ld %5ld %5ld %5ld\n",
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3]); 
#endif
#ifdef FR_XQUAD
    if(LANG == 1)
      fprintf(fo1,
      "Element# %5ld   Druck %+#13.5LE   Schub r %+#13.5LE   Schub s %+#13.5LE\
   Knoten %5ld %5ld %5ld %5ld\n",
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3]); 
    if(LANG == 2)
      fprintf(fo1,
      "Element# %5ld   pressure %+#13.5LE   shear r %+#13.5LE   shear s %+#13.5LE\
   nodes %5ld %5ld %5ld %5ld\n",
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3]); 
#endif
    }

/*======================================================================
* Elementtypen 11 und 12
*=====================================================================*/
  if(ityp[nep[j]]== 11  || ityp[nep[j]]== 12) 
    {
#ifdef FR_XDOUB
    if(LANG == 1)
      fprintf(fo1,"Element# %5ld   Normallast %+#13.5lE   Schub r %+#13.5lE\
   Knoten %5ld %5ld %5ld %5ld\n",nep[j],pres[j],tr1[j],
      noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3]); 
    if(LANG == 2)
      fprintf(fo1,"element# %5ld   normal load %+#13.5lE  shear r %+#13.5lE\
   nodes %5ld %5ld %5ld %5ld\n",nep[j],pres[j],tr1[j],
      noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3]); 
#endif
#ifdef FR_XQUAD
    if(LANG == 1)
      fprintf(fo1,"Element# %5ld   Normallast %+#13.5LE   Schub r %+#13.5LE\
   Knoten %5ld %5ld %5ld %5ld\n",nep[j],pres[j],tr1[j],
      noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3]); 
    if(LANG == 2)
      fprintf(fo1,"element# %5ld   normal load %+#13.5LE  shear r %+#13.5LE\
   nodes %5ld %5ld %5ld %5ld\n",nep[j],pres[j],tr1[j],
      noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3]); 
#endif
    }

/*======================================================================
* Elementtyp 18,19 und 20
*=====================================================================*/
  if(ityp[nep[j]]== 18 || ityp[nep[j]]== 19 || ityp[nep[j]]== 20) 
    {
#ifdef FR_XDOUB
    if(LANG == 1)
      fprintf(fo1,"Element# %5ld   Druck %+#13.5lE\n",nep[j],pres[j]);
    if(LANG == 2)
      fprintf(fo1,"Element# %5ld   pressure %+#13.5lE\n",nep[j],pres[j]); 
#endif
#ifdef FR_XQUAD
    if(LANG == 1)
      fprintf(fo1,"Element# %5ld   Druck %+#13.5LE\n",nep[j],pres[j]);
    if(LANG == 2)
      fprintf(fo1,"Element# %5ld   pressure %+#13.5LE\n",nep[j],pres[j]); 
#endif
    }

  }  /* Ende Schleife */

return(0);
}
