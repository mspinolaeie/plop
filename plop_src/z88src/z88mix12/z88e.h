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
*  z88e.h fuer UNIX und Windows
*  4.10.2005 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen Windows und UNIX 
***********************************************************************/
#define FR_INT4AY long *               /* Pointer auf long        */
#define FR_INT4 long                   /* long                    */
#define FR_CALLOC calloc               /* calloc */
#define FR_SIZERW size_t               /* Size fuer fread, fwrite */

#ifdef FR_XDOUB
#define FR_SQRT sqrt                   /* sqrt                    */
#define FR_POW pow                     /* pow                     */
#define FR_FABS fabs                   /* fabs                    */
#define FR_SIN sin                     /* sin                     */
#define FR_COS cos                     /* cos                     */
#define FR_DOUBLEAY double *           /* Pointer auf double      */
#define FR_DOUBLE double               /* double                  */
#endif

#ifdef FR_XQUAD
#define FR_SQRT sqrtl                  /* sqrtl                   */
#define FR_POW powl                    /* powl                    */
#define FR_FABS fabsl                  /* fabsl                   */
#define FR_SIN sinl                    /* sinl                    */
#define FR_COS cosl                    /* cosl                    */
#define FR_DOUBLEAY long double *      /* Pointer auf long double */
#define FR_DOUBLE long double          /* long double             */
#endif

#include <z88math.h>

/***********************************************************************
* Icon
***********************************************************************/
#define ICO_Z88E                       10

/***********************************************************************
* Cursor
***********************************************************************/
#define CUR_Z88E                       20

/***********************************************************************
* Toolbar
***********************************************************************/
#define BMP_Z88E                       30

/***********************************************************************
* Menue-IDs
***********************************************************************/
#define IDM_WER                        100
#define IDM_XIT                        110
#define IDM_GO                         120

/***********************************************************************
* Toolbar-IDs
***********************************************************************/
#define ITC_GO                         130
#define ITC_HELP                       140

/***********************************************************************
* Alerts
***********************************************************************/
#define AL_NOLOG 3000                  /* kein Z88F.LOG */ 
#define AL_NODYN 3010                  /* kein Z88.DYN */
#define AL_WRONGDYN 3020               /* Fehler in Z88.DYN */
#define AL_NOMEMY 3030                 /* nicht genug Memory */
#define AL_NOO4 3040                   /* Fehler Oeffnen z88o4.txt */
#define AL_NO1Y 3050                   /* Fehler Oeffnen z88o1.bny */
#define AL_NO3Y 3060                   /* Fehler Oeffnen z88o3.bny */
#define AL_JACNEG 3070                 /* Jacobi-Determinate <= 0 */

/***********************************************************************
* Texte
***********************************************************************/
#define TX_REAO1Y 3500                 /* Z88O1.BNY einlesen */
#define TX_REAO3Y 3510                 /* Z88O3.BNY einlesen */
#define TX_KNOTENK 3520                /* Knotenkraefte */
#define TX_EXITZ88E 3530               /* Ende Z88E */

/***********************************************************************
* Log- Eintraege
***********************************************************************/
#define LOG_BZ88E 4000                 /* Beginn Z88E */
#define LOG_OPENZ88DYN 4010            /* Oeffnen Z88.DYN */
#define LOG_NODYN 4020                 /* kann Z88.DYN nicht oeffnen */
#define LOG_WRONGDYN 4030              /* Z88.DYN nicht o.k. */
#define LOG_MAXKOI 4040                /* MAXKOI */
#define LOG_MAXK 4050                  /* MAXK */
#define LOG_MAXE 4060                  /* MAXE */
#define LOG_MAXNFG 4070                /* MAXNFG */
#define LOG_MAXNEG 4080                /* MAXNEG */
#define LOG_MAXESM 4090                /* MAXESM */
#define LOG_OKDYN 4100                 /* Z88.DYN scheint o.k. zu sein */
#define LOG_ALLOCMEMY 4110             /* Memory anlegen */
#define LOG_ARRAYNOTOK 4120            /* Memory Kennung I nicht o.k. */
#define LOG_ARRAYOK 4130               /* Memory Kennung I angelegt */
#define LOG_SUMMEMY 4140               /* Memory angefordert */
#define LOG_EXITDYN88E 4150            /* Verlassen DYN88E */
#define LOG_NOO4 4160                  /* kein Z88O4.TXT */
#define LOG_RIY88 4170                 /* Start RIY88 */
#define LOG_NO1Y 4180                  /* kein Z88O1.BNY */
#define LOG_NO3Y 4190                  /* kein Z88O3.BNY */
#define LOG_REAO1Y 4200                /* Einlesen Z88O1.BNY */
#define LOG_REAO3Y 4210                /* Einlesen Z88O3.BNY */
#define LOG_RIY88OK 4220               /* Verlassen RIY88 */
#define LOG_KNOTENK 4230               /* Knotenkraefte */
#define LOG_JACNEG 4240                /* Jacobi-Determinate <= 0 */
#define LOG_EXITZ88E 4250              /* Ende Z88E */
