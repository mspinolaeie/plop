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
/**********************************************************
* Z88P.H fuer UNIX und Windows
* 4.10.2005 Rieg
**********************************************************/

/***********************************************************************
* Datentypen Windows und UNIX
***********************************************************************/
#define FR_INT4AY long *               /* Pointer auf long        */
#define FR_INT4 long                   /* long                    */
#define FR_SIZERW size_t               /* Size fuer fread, fwrite */
#define FR_CALLOC calloc               /* calloc */
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

#include <z88math.h>

/***********************************************************************
* Icon
***********************************************************************/
#define ICO_Z88P             10

/***********************************************************************
* Cursor
***********************************************************************/
#define CUR_Z88P             11

/***********************************************************************
* Toolbar
***********************************************************************/
#define BMP_Z88P             12

/***********************************************************************
* Steuerflags
***********************************************************************/
#define ID_NOTLOADSTRUC      20 /* Ladezustand Struktur      */
#define ID_LOADSTRUC         30 /* Strukturfile geladen      */
#define ID_NOTLOADVERF       40 /* Ladezustand Z88O2.TXT     */
#define ID_LOADVERF          50 /* Z88O2.TXT geladen         */  
#define ID_NOTLOADSPANN      60 /* Ladezustand Spannungsfile */
#define ID_LOADSPANN         70 /* Spannungsfile geladen     */
#define ID_ENABLELABELS      80
#define ID_DISABLELABELS     90

/**********************************************************
* Menue-IDs
**********************************************************/
#define IDM_INTERFACE        100
#define IDM_STRUKTURFILE     110
#define IDM_LADEN            120
#define IDM_XIT              130
#define IDM_WER              140

#define IDM_UNVERFORMT       150
#define IDM_VERFORMT         160
#define IDM_UNUNDVERFORMT    170

#define IDM_CRT              180
#define IDM_PLOTTER          190

#define IDM_XY               200 
#define IDM_XZ               210 
#define IDM_YZ               220 
#define IDM_3DIM             230 

#define IDM_NOLABELS         240
#define IDM_KNOTEN           250
#define IDM_ELEMENTE         260
#define IDM_ALLES            270

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

#define IDM_GLO              430 
#define IDM_ZEN              440
#define IDM_VER              450
#define IDM_ROT              460
#define IDM_FXCOR            470

#define IDM_SHOWSPANN        480
#define IDM_NOSHOWSPANN      490

#define IDM_YESSCALE         500
#define IDM_NOSCALE          510

/**********************************************************
* Toolbar-IDs
**********************************************************/
#define ITC_HELP             550

#define ITC_UNVERFORMT       551
#define ITC_VERFORMT         552
#define ITC_UNUNDVERFORMT    553

#define ITC_XY               554 
#define ITC_XZ               555 
#define ITC_YZ               556 
#define ITC_3DIM             557 

#define ITC_NOLABELS         558
#define ITC_KNOTEN           559
#define ITC_ELEMENTE         560
#define ITC_ALLES            561

#define ITC_SHOWSPANN        562

#define ITC_YESSCALE         563

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

/***********************************************************************
* Alerts
***********************************************************************/
#define AL_NOLOG 3000                  /* kein Z88P.LOG */ 
#define AL_NODYN 3010                  /* kein Z88.DYN */
#define AL_WRONGDYN 3020               /* Fehler in Z88.DYN */
#define AL_NOMEMY 3030                 /* nicht genug Memory */
#define AL_NINT0 3040                  /* NINT = 0 */
#define AL_EXMAXGP 3050                /* MAXGP ueberschritten */
#define AL_NOOPENSTO 3060              /* kann Z88P.STO nicht oeffnen */
#define AL_NOSTRFI 3070                /* kein Strukturfile */
#define AL_NOO2 3080                   /* kein Z88O2.TXT */
#define AL_NOO5 3090                   /* kein Z88O5.TXT */
#define AL_NOPLOF 3100                 /* kein Plotterfile */
#define AL_EXMAXK 3110                 /* MAXK ueberschritten */
#define AL_EXMAXE 3120                 /* MAXE ueberschritten */
#define AL_WRONGDIM 3130               /* NDIM falsch */
#define AL_NOCOL 3140                  /* kein Z88P.COL */
#define AL_WRONGCOL 3150               /* Z88P.COL falsch */
#define AL_NO_CF_ENTRIES 3160          /* kein Font CF_ENTRIES */
#define AL_NO_CF_BUTTONS 3170          /* kein Font CF_BUTTONS */
#define AL_NO_CO_BACKGR 3180           /* keine Farbe CO_BACKGR */
#define AL_NO_CO_FOREGR 3190           /* keine Farbe CO_FOREGR */
#define AL_NO_CO_ENTRIES 3200          /* keine Farbe CO_ENTRIES */
#define AL_NO_GC 3210                  /* kein Grafikkontext */
#define AL_NO_CF_GRAFICS 3220          /* kein Grafikfont */
#define AL_NO_CO_FARBE 3230            /* keine Grafikfarbe */

/***********************************************************************
* Infos
***********************************************************************/
#define INF_GENPLOT 3500               /* Z88O6.TXT erzeugt */

/***********************************************************************
* LOGs
***********************************************************************/
#define LOG_BZ88PWIN 4000              /* Start Z88P */
#define LOG_OPENDYN 4010               /* Oeffnen Z88.DYN */
#define LOG_NODYN 4020                 /* kein Z88.DYN */
#define LOG_WRONGDYN 4030              /* Z88.DYN falsch */
#define LOG_MAXKOI 4040                /* MAXKOI */
#define LOG_MAXK 4050                  /* MAXK */
#define LOG_MAXE 4060                  /* MAXE */
#define LOG_MFACCOMMON 4070            /* MFACCOMMON */
#define LOG_MAXGP 4080                 /* MAXGP */
#define LOG_OKDYN 4090                 /* Z88.DYN gelesen..o.k. */
#define LOG_ALLOCMEMY 4100             /* Memory anlegen */
#define LOG_ARRAYNOTOK 4110            /* Array nicht o.k. */
#define LOG_ARRAYOK 4120               /* Array o.k. */
#define LOG_SUMMEMY 4130               /* Memory in Bytes */
#define LOG_EXITDYN88P 4140            /* Verlassen Speicherunit DYN88P */
#define LOG_REAO2 4150                 /* Einlesen Z88O2.TXT */
#define LOG_REAO2OK 4160               /* Z88O2.TXT eingelesen */
#define LOG_REAO5 4170                 /* Einlesen Z88O5.TXT */
#define LOG_NINT0 4180                 /* NINT = 0 */
#define LOG_EXMAXGP 4190               /* MAXGP ueberschritten */
#define LOG_REAO5OK 4200               /* Z88O5.TXT eingelesen */
#define LOG_NOSTO 4210                 /* kein Z88P.STO ..Default */
#define LOG_REASTO 4220                /* Z88P.STO einlesen */
#define LOG_REASTOOK 4230              /* Z88P.STO eingelesen */
#define LOG_NOOPENSTO 4240             /* kann Z88P.STO nicht oeffnen */
#define LOG_WRISTO 4250                /* Z88PWIN. beschreiben */
#define LOG_WRISTOOK 4260              /* Z88PWIN. fertig beschrieben */
#define LOG_REAI1 4270                 /* Einlesen Z88I1.TXT */
#define LOG_REAI1OK 4280               /* Z88I1.TXT eingelesen */
#define LOG_NOSTRFI 4290               /* kein Strukturfile */
#define LOG_NOO2 4300                  /* kein Z88O2.TXT */
#define LOG_NOO5 4310                  /* kein Z88O5.TXT */
#define LOG_NOPLOF 4320                /* kein Plotterfile */
#define LOG_EXMAXK 4330                /* MAXK ueberschritten */
#define LOG_EXMAXE 4340                /* MAXE ueberschritten */
#define LOG_WRONGDIM 4350              /* NDIM falsch */
#define LOG_NOCOL 4360                 /* kein Z88P.COL */
#define LOG_WRONGCOL 4370              /* Z88P.COL falsch */
#define LOG_NO_CF_ENTRIES 4380         /* kein Font CF_ENTRIES */
#define LOG_NO_CF_BUTTONS 4390         /* kein Font CF_BUTTONS */
#define LOG_NO_CO_BACKGR 4400          /* keine Farbe CO_BACKGR */
#define LOG_NO_CO_FOREGR 4410          /* keine Farbe CO_FOREGR */
#define LOG_NO_CO_ENTRIES 4420         /* keine Farbe CO_ENTRIES */
#define LOG_NO_GC 4430                 /* kein Grafikkontext */
#define LOG_NO_CF_GRAFICS 4440         /* kein Grafikfont */
#define LOG_NO_CO_FARBE 4450           /* keine Grafikfarbe */
