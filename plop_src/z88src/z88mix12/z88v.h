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
*  z88v.h fuer UNIX und Windows
*  4.10.2005 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen Windows und UNIX
***********************************************************************/
#define FR_INT4AY long *               /* Pointer auf long        */
#define FR_INT4 long                   /* 4 Bytes Integer         */
#define FR_CALLOC calloc               /* calloc */
struct FR_SIJ
  {
  FR_INT4 izei;
  FR_INT4 jspa;
  };

#ifdef FR_XDOUB
#define FR_FABS fabs                   /* fabs                    */
#define FR_DOUBLE double               /* double                  */
#endif

#include <z88math.h>

/***********************************************************************
* Icon
***********************************************************************/
#define ICO_Z88V                        10

/***********************************************************************
* Toolbar
***********************************************************************/
#define BMP_Z88V                        20

/***********************************************************************
* Menue
***********************************************************************/
#define IDM_DATEI                      100
#define IDM_Z88DYN                     110
#define IDM_Z88NITXT                   120
#define IDM_Z88I1TXT                   130
#define IDM_Z88I2TXT                   140
#define IDM_Z88I3TXT                   150
#define IDM_Z88I4TXT                   160
#define IDM_Z88I5TXT                   170
#define IDM_WER                        180
#define IDM_XIT                        190

/***********************************************************************
* Toolbar
***********************************************************************/
#define ITC_HELP                       200
#define ITC_Z88DYN                     210
#define ITC_Z88NITXT                   220
#define ITC_Z88I1TXT                   230
#define ITC_Z88I2TXT                   240
#define ITC_Z88I3TXT                   250
#define ITC_Z88I4TXT                   260
#define ITC_Z88I5TXT                   270

/***********************************************************************
* Alerts
***********************************************************************/
#define AL_NOLOG 3000                  /* kein Z88F.LOG */ 
#define AL_NODYN 3010                  /* kein Z88.DYN */
#define AL_WRONGDYN 3020               /* Fehler in Z88.DYN */
#define AL_NOMEMY 3030                 /* nicht genug Memory */

/***********************************************************************
* Log- Eintraege
***********************************************************************/
#define LOG_BZ88V 4000                 /* Beginn Z88V */
#define LOG_OPENZ88DYN 4010            /* Oeffnen Z88.DYN */
#define LOG_NODYN 4020                 /* kann Z88.DYN nicht oeffnen */
#define LOG_WRONGDYN 4030              /* Z88.DYN nicht o.k. */
#define LOG_MAXE 4040                  /* MAXE */
#define LOG_MAXK 4050                  /* MAXK */
#define LOG_MAXNFG 4060                /* MAXNFG */
#define LOG_MAXNEG 4070                /* MAXNEG */
#define LOG_OKDYN 4080                 /* Z88.DYN scheint o.k. zu sein */
#define LOG_ALLOCMEMY 4090             /* Memory anlegen */
#define LOG_ARRAYNOTOK 4100            /* Memory Kennung I nicht o.k. */
#define LOG_ARRAYOK 4110               /* Memory Kennung I angelegt */
#define LOG_SUMMEMY 4120               /* Memory angefordert */
#define LOG_EXITDYN88V 4130            /* Verlassen DYN88V */
