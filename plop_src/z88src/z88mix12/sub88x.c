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
* V10.0  December 12, 2001
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
* sub88x.c : hilfswerte ausfiltern
* 11.9.2002 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>
#endif

/***********************************************************************
* Fuer Windows95
***********************************************************************/
#ifdef FR_WIN95
#include <z88x.h>
#endif

/***********************************************************************
*  Functions
***********************************************************************/

/***********************************************************************
* hier beginnt Function sub88x
***********************************************************************/
void sub88x(FR_INT4 i)
{
extern FR_INT4AY ityp;

extern FR_INT4 ianz,ifrej;

/***********************************************************************
* start function
***********************************************************************/
/*----------------------------------------------------------------------
* Anzahl Knoten
*---------------------------------------------------------------------*/
if     (ityp[i] == 1  || ityp[i] == 7 ||
        ityp[i] == 8  || ityp[i] == 20)    ianz= 8;

else if(ityp[i] == 2  || ityp[i] == 4 ||
        ityp[i] == 5  || ityp[i] == 9 ||
        ityp[i] ==13)                      ianz= 2;

else if(ityp[i] == 3  || ityp[i] == 14 ||
        ityp[i] == 15 || ityp[i] == 18)    ianz= 6;

else if(ityp[i] == 6)                      ianz= 3;

else if(ityp[i] == 10)                     ianz= 20;

else if(ityp[i] == 11 || ityp[i] == 12)    ianz= 12;

else if(ityp[i] == 19)                     ianz= 16;

/*----------------------------------------------------------------------
* Anzahl Knoten
*---------------------------------------------------------------------*/
if     (ityp[i] == 1  || ityp[i] == 4  || 
        ityp[i] == 10 || ityp[i] == 13 ||
        ityp[i] == 18 || ityp[i] == 19 ||
        ityp[i] == 20)                      ifrej= 3;

else if(ityp[i] == 2  || ityp[i] == 5)      ifrej= 6; 

else                                        ifrej= 2;

return; 
}
