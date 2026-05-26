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
* z88g.h, fuer UNIX und Windows
* 4.10.2005 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen Windows und UNIX 
***********************************************************************/
#define FR_INT4AY long *               /* Pointer auf long        */
#define FR_INT4 long                   /* long                    */
#define FR_CALLOC calloc               /* calloc */
#define FR_SIZERW size_t               /* Size fuer fread, fwrite */

#ifdef FR_XDOUB
#define FR_DOUBLEAY double *           /* Pointer auf double      */
#define FR_DOUBLE double               /* double                  */
#define FR_FABS fabs                   /* fabs                    */
#endif

#include <z88math.h>

/***********************************************************************
* Icon
***********************************************************************/
#define ICO_Z88G                       10

/***********************************************************************
* Cursor
***********************************************************************/
#define CUR_Z88G                       20

/***********************************************************************
* Toolbar
***********************************************************************/
#define BMP_Z88G                       30

/***********************************************************************
* Menue-IDs
***********************************************************************/
#define IDM_WER                        100
#define IDM_XIT                        110
#define IDM_VOLU                       120
#define IDM_SHEI                       130
#define IDM_PLAT                       140
#define IDM_TORU                       150
#define IDM_GO                         160
#define IDM_NAST                       170
#define IDM_COSM                       180

/***********************************************************************
* Toolbar-IDs
***********************************************************************/
#define ITC_GO                         200
#define ITC_VOLU                       210
#define ITC_SHEI                       220
#define ITC_PLAT                       230
#define ITC_TORU                       240
#define ITC_HELP                       250
#define ITC_NAST                       260
#define ITC_COSM                       270

/***********************************************************************
* Alerts
***********************************************************************/
#define AL_NOLOG 3000                  /* kein Z88F.LOG */ 
#define AL_NODYN 3010                  /* kein Z88.DYN */
#define AL_WRONGDYN 3020               /* Fehler in Z88.DYN */
#define AL_NOCOS 3030                  /* kein z88g.cos */
#define AL_NONAS 3033                  /* kein z88g.nas */
#define AL_NOIN 3035                   /* kein z88g.in */
#define AL_NOI1 3040                   /* Fehler Oeffnen z88i1.txt */
#define AL_NOI2 3050                   /* Fehler Oeffnen z88i2.txt */
#define AL_NOI3 3060                   /* Fehler Oeffnen z88i3.txt */
#define AL_NOI5 3070                   /* Fehler Oeffnen z88i3.txt */
#define AL_NOMEMY 3080                 /* nicht genug Speicher */

/***********************************************************************
* Texte
***********************************************************************/
#define TX_COSOPEN 3500                /* Z88G.COS geoeffnet */
#define TX_NASOPEN 3503                /* Z88G.NAS geoeffnet */
#define TX_INOPEN  3505                /* Z88G.IN geoeffnet */
#define TX_I1OPEN  3510                /* Z88I1.TXT geoeffnet */
#define TX_I2OPEN  3520                /* Z88I2.TXT geoeffnet */
#define TX_I3OPEN  3530                /* Z88I3.TXT geoeffnet */
#define TX_I5OPEN  3532                /* Z88I5.TXT geoeffnet */
#define TX_DIMDET  3535                /* Dimension entdeckt */
#define TX_NODDET  3540                /* i Knoten entdeckt */
#define TX_ELEDET  3550                /* i Elemente entdeckt */
#define TX_CONDET  3560                /* i Randbed. entdeckt */
#define TX_NEGDET  3570                /* i Mat-Gesetze entdeckt */
#define TX_PELDET  3580                /* i Elemente mit Druck entd. */
#define TX_REAWRI  3590                /* abw. Lesen und Schreiben */
#define TX_NODDON  3600                /* i Knoten fertig */
#define TX_ELEDON  3610                /* i Elemente fertig */
#define TX_CONDON  3620                /* i Randbed. fertig */
#define TX_16DET   3630                /* i Elemente Nr.16 entdeckt */  
#define TX_17DET   3640                /* i Elemente Nr.17 entdeckt */  
#define TX_7DET    3650                /* i Elemente Nr.7 entdeckt */  
#define TX_14DET   3660                /* i Elemente Nr.14 entdeckt */  
#define TX_18DET   3670                /* i Elemente Nr.18 entdeckt */  
#define TX_20DET   3680                /* i Elemente Nr.20 entdeckt */  
#define TX_8DET    3683                /* i Elemente Nr.8 entdeckt */  
#define TX_15DET   3686                /* i Elemente Nr.15 entdeckt */  
#define TX_Z88CS   3690                /* Z88 Daten fertig */
#define TX_Z88DONE 3700                /* Z88 fertig */
#define TX_SHEIPLA 3710                /* gewaehlter Elementtyp */
#define TX_CHOICOS 3720                /* Auswahl Elementtyp COSMOS */
#define TX_CHOINAS 3725                /* Auswahl Elementtyp COSMOS */
#define TX_COSNAS  3730                /* Auswahl COSMOS oder NASTRAN */
#define TX_FILEF   3740                /* File COSMOS oder NASTRAN */
#define TX_ISPC    3750                /* Lagerfall bei NASTRAN */
#define TX_ILOAD   3760                /* Lastfall bei NASTRAN */

/***********************************************************************
* Log
***********************************************************************/
#define LOG_BZ88 4000                  /* Beginn Z88G */
#define LOG_OPENZ88DYN 4010            /* Oeffnen Z88.DYN */
#define LOG_NODYN 4020                 /* kann Z88.DYN nicht oeffnen */
#define LOG_WRONGDYN 4030              /* Z88.DYN nicht o.k. */
#define LOG_NOCOS 4040                 /* kein Z88G.COS */  
#define LOG_NONAS 4043                 /* kein Z88G.NAS */  
#define LOG_NOIN 4045                  /* kein Z88G.IN */  
#define LOG_NOI1 4050                  /* kein Z88I1.TXT */
#define LOG_NOI2 4060                  /* kein Z88I2.TXT */
#define LOG_NOI3 4070                  /* kein Z88I3.TXT */
#define LOG_NOI5 4072                  /* kein Z88I5.TXT */
#define LOG_DIMDET 4075                /* Dimension entdeckt */
#define LOG_NODDET 4080                /* i Knoten entdeckt */
#define LOG_ELEDET 4090                /* i Elemente entdeckt */
#define LOG_CONDET 4100                /* i Randbed. entdeckt */
#define LOG_NEGDET 4110                /* i Mat-Gesetze entdeckt */
#define LOG_PELDET 4120                /* i Ele mit Druck entdeckt */
#define LOG_REAWRI 4130                /* abw. Lesen und Schreiben */
#define LOG_NODDON 4140                /* i Knoten fertig */
#define LOG_ELEDON 4150                /* i Elemente fertig */
#define LOG_CONDON 4160                /* i Randbed. fertig */
#define LOG_16DET 4170                 /* i Elemente Nr.16 entdeckt */  
#define LOG_17DET 4180                 /* i Elemente Nr.17 entdeckt */  
#define LOG_7DET 4190                  /* i Elemente Nr.7 entdeckt */  
#define LOG_14DET 4200                 /* i Elemente Nr.14 entdeckt */  
#define LOG_18DET 4210                 /* i Elemente Nr.18 entdeckt */  
#define LOG_20DET 4220                 /* i Elemente Nr.20 entdeckt */  
#define LOG_8DET 4223                  /* i Elemente Nr.8 entdeckt */  
#define LOG_15DET 4226                 /* i Elemente Nr.15 entdeckt */  
#define LOG_Z88CS 4230                 /* Z88 Daten fertig */
#define LOG_Z88DONE 4240               /* Z88 fertig */
#define LOG_SHEIPLA 4250               /* Platte oder Scheibe */
#define LOG_FILEF 4255                 /* COSMOS oder NASTRAN */
#define LOG_ARRAYOK 4260               /* Speicher ok */
#define LOG_ARRAYNOTOK 4270            /* Speicher nicht ok */
#define LOG_ISPC 4280                  /* Lagerfall bei NASTRAN */
#define LOG_ILOAD 4290                 /* Lastfall bei NASTRAN */
