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
* Z88O.H fuer UNIX und Windows
* 4.10.2005 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen Windows und UNIX
***********************************************************************/
#define FR_INT4AY long *               /* Pointer auf long        */
#define FR_INT4 long                   /* 4 Bytes Integer         */
#define FR_SIZERW size_t               /* Size fuer fread, fwrite */
#define FR_CHARAY char *               /* Pointer auf char        */

#ifdef FR_XDOUB
#define FR_SQRT sqrt                   /* sqrt                    */
#define FR_POW pow                     /* pow                     */
#define FR_FABS fabs                   /* fabs                    */
#define FR_SIN sin                     /* sin                     */
#define FR_COS cos                     /* cos                     */
#define FR_ATAN atan                   /* atan                    */
#define FR_DOUBLEAY double *           /* Pointer auf double      */
#define FR_DOUBLE double               /* double                  */
#endif

#ifdef FR_UNIX
#define FR_CALLOC XtCalloc             /* calloc                  */
#endif

#ifdef FR_WIN95
#define FR_CALLOC calloc               /* calloc                  */
#endif


#include <z88math.h>

/***********************************************************************
* Icon
***********************************************************************/
#define ICO_Z88O             10

/***********************************************************************
* Cursor
***********************************************************************/
#define CUR_Z88O             11

/***********************************************************************
* Toolbar
***********************************************************************/
#define BMP_Z88O             12

/***********************************************************************
* Steuerflags
***********************************************************************/
#define ID_NOTLOADSTRUC      20 /* Ladezustand Struktur      */
#define ID_LOADSTRUC         21 /* Strukturfile geladen      */
#define ID_NOTLOADVERF       30 /* Ladezustand Z88O2.TXT     */
#define ID_LOADVERF          31 /* Z88O2.TXT geladen         */  
#define ID_NOTLOADSPANN      40 /* Ladezustand Z88O8.TXT     */
#define ID_LOADSPANN         41 /* Z88O8.TXT geladen         */
#define ID_ZOOM              50 /* Maus: Zoomen              */
#define ID_PAN               51 /* Maus: Verschieben         */
#define ID_ROTATE            52 /* Maus: Rotieren            */
#define ID_FUNKEY            60 /* Rotieren via F-Tasten     */
#define ID_MOUSE             61 /* Rotieren via Maus         */
#define ID_DISABLELABELS     70 /* Labels aus                */
#define ID_ENABLELABELS      71 /* Labels an                 */

/***********************************************************************
* Menue-IDs
***********************************************************************/
#define IDM_RUN              100
#define IDM_FILE             110
#define IDM_XIT              120
#define IDM_WER              130

#define IDM_ZOOM             140 
#define IDM_PAN              150 
#define IDM_ROTATE           160 

#define IDM_UNVERFORMT       170
#define IDM_VERFORMT         180

#define IDM_LIGHT            190 
#define IDM_HIDDEN           200
#define IDM_SHOWSPANN        210
#define IDM_SHOWGAUSS        212
#define IDM_SHOWVX           214
#define IDM_SHOWVY           216
#define IDM_SHOWVZ           218

#define IDM_YESSCALE         220
#define IDM_NOSCALE          230

#define IDM_NOLABELS         240
#define IDM_KNOTEN           250
#define IDM_ELEMENTE         260

#define IDM_PRIOR            280
#define IDM_NEXT             290
#define IDM_UP               300
#define IDM_DOWN             310
#define IDM_LEFT             320
#define IDM_RIGHT            330
#define IDM_HOME             340
#define IDM_END              350
#define IDM_F2               360
#define IDM_F3               370
#define IDM_F4               380
#define IDM_F5               390
#define IDM_F6               400
#define IDM_F7               410
#define IDM_F8               420

#define IDM_VER              450
#define IDM_ROT              460
#define IDM_ZM               470

#define IDM_HELP             480

/**********************************************************
* Toolbar-IDs
**********************************************************/
#define ITC_RUN              500
#define ITC_FILE             501
#define ITC_YESSCALE         502

#define ITC_MAUS             510

#define ITC_UNVERFORMT       520
#define ITC_VERFORMT         521

#define ITC_LIGHT            530 
#define ITC_HIDDEN           531 
#define ITC_SHOWSPANN        532
#define ITC_SHOWGAUSS        533
#define ITC_SHOWVX           534
#define ITC_SHOWVY           536
#define ITC_SHOWVZ           538

#define ITC_NOLABELS         540
#define ITC_KNOTEN           541
#define ITC_ELEMENTE         542

#define ITC_HELP             550

/**********************************************************
* Box-IDs
**********************************************************/
/*---------------------------------------------------------
* Interface
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT1        600

/*---------------------------------------------------------
* Struktur
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT2        610

/*---------------------------------------------------------
* Globale Vergroesserungen
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT3        620
#define IDDLG_V_TEXT4        630
#define IDDLG_V_TEXT5        640

/*---------------------------------------------------------
* Zentrierfaktoren
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT6        650
#define IDDLG_V_TEXT7        660
#define IDDLG_V_TEXT8        670

/*---------------------------------------------------------
* Vergroesserungen Verschiebungen
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT9        680
#define IDDLG_V_TEXT10       690
#define IDDLG_V_TEXT11       700

/*---------------------------------------------------------
* Rotationen
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT12       710
#define IDDLG_V_TEXT13       720
#define IDDLG_V_TEXT14       730

/*---------------------------------------------------------
* FXCOR
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT15       740

/*---------------------------------------------------------
* Knoten von - bis
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT16       750
#define IDDLG_V_TEXT17       760

/*---------------------------------------------------------
* Elemente von - bis
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT18       770
#define IDDLG_V_TEXT19       780

/***********************************************************************
* Alerts
***********************************************************************/
#define AL_NOLOG 3000                  /* kein Z88P.LOG */ 
#define AL_NODYN 3010                  /* kein Z88.DYN */
#define AL_WRONGDYN 3020               /* Fehler in Z88.DYN */
#define AL_NOMEMY 3030                 /* nicht genug Memory */
#define AL_NONINT0 3040                /* NINT != 0 */
#define AL_NOSTRFI 3050                /* kein Strukturfile */
#define AL_NOO2 3060                   /* kein Z88O2.TXT */
#define AL_NOO8 3070                   /* kein Z88O8.TXT */
#define AL_EXMAXK 3080                 /* MAXK ueberschritten */
#define AL_EXMAXE 3090                 /* MAXE ueberschritten */
#define AL_WRONGDIM 3100               /* NDIM falsch */
#define AL_NOOGL 3110                  /* kein Z88O.OGL */
#define AL_WRONGOGL 3120               /* Z88o.OGL falsch */
#define AL_NOFCD 3130                  /* kein Z88.FCD */
#define AL_WRONGFCD 3140               /* Z88.FCD falsch */
#define AL_NO_GLX 3150                 /* kein GLX- Context */
#define AL_NO_CF_ENTRIES 3160          /* kein Font CF_ENTRIES */
#define AL_NO_CF_BUTTONS 3170          /* kein Font CF_BUTTONS */
#define AL_NO_CF_GRAFICS 3180          /* kein Font CF_GRAFICS */
#define AL_NO_CO_BACKGR 3190           /* keine Farbe CO_BACKGR */
#define AL_NO_CO_FOREGR 3200           /* keine Farbe CO_FOREGR */
#define AL_NO_CO_ENTRIES 3210          /* keine Farbe CO_ENTRIES */
 
/***********************************************************************
* LOGs
***********************************************************************/
#define LOG_BZ88OWIN 4000              /* Start Z88O */
#define LOG_OPENDYN 4010               /* Oeffnen Z88.DYN */
#define LOG_NODYN 4020                 /* kein Z88.DYN */
#define LOG_WRONGDYN 4030              /* Z88.DYN falsch */
#define LOG_MAXKOI 4040                /* MAXKOI */
#define LOG_MAXK 4050                  /* MAXK */
#define LOG_MAXE 4060                  /* MAXE */
#define LOG_OKDYN 4090                 /* Z88.DYN gelesen..o.k. */
#define LOG_ALLOCMEMY 4100             /* Memory anlegen */
#define LOG_ARRAYNOTOK 4110            /* Array nicht o.k. */
#define LOG_ARRAYOK 4120               /* Array o.k. */
#define LOG_SUMMEMY 4130               /* Memory in Bytes */
#define LOG_EXITDYN88O 4140            /* Verlassen Speicherunit DYN88O */
#define LOG_REAO2 4150                 /* Einlesen Z88O2.TXT */
#define LOG_REAO2OK 4160               /* Z88O2.TXT eingelesen */
#define LOG_REAO8 4170                 /* Einlesen Z88O8.TXT */
#define LOG_NONINT0 4180               /* NINT != 0 */
#define LOG_REAO8OK 4190               /* Z88O8.TXT eingelesen */
#define LOG_REAI1 4200                 /* Einlesen Z88I1.TXT */
#define LOG_REAI1OK 4210               /* Z88I1.TXT eingelesen */
#define LOG_NOSTRFI 4220               /* kein Strukturfile */
#define LOG_NOO2 4230                  /* kein Z88O2.TXT */
#define LOG_NOO8 4240                  /* kein Z88O8.TXT */
#define LOG_EXMAXK 4250                /* MAXK ueberschritten */
#define LOG_EXMAXE 4260                /* MAXE ueberschritten */
#define LOG_WRONGDIM 4270              /* NDIM falsch */
#define LOG_NOOGL 4280                 /* kein Z88O.OGL */
#define LOG_WRONGOGL 4290              /* Z88O.OGL falsch */
#define LOG_NOFCD 4300                 /* kein Z88.FCD */
#define LOG_WRONGFCD 4310              /* Z88.FCD falsch */
#define LOG_NO_CF_ENTRIES 4320         /* kein Font CF_ENTRIES */
#define LOG_NO_CF_BUTTONS 4330         /* kein Font CF_BUTTONS */
#define LOG_NO_CF_GRAFICS 4340         /* kein Font CF_GRAFICS */
#define LOG_NO_CO_BACKGR 4350          /* keine Farbe CO_BACKGR */
#define LOG_NO_CO_FOREGR 4360          /* keine Farbe CO_FOREGR */
#define LOG_NO_CO_ENTRIES 4370         /* keine Farbe CO_ENTRIES */
#define LOG_NO_GLX 4380                /* kein  GLX- Context */

