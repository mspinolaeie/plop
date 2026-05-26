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
* Z88COM.H fuer UNIX und Windows
* 2.3.2006 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen UNIX und Windows 
***********************************************************************/
#define FR_INT4 long                   /* long                    */

/***********************************************************************
* Icon (Windows)
***********************************************************************/
#define ICO_Z88COM                       10

/***********************************************************************
* Toolbar (Windows)
***********************************************************************/
#define BMP_Z88COM                       20

/***********************************************************************
* Hintergrund (Windows)
***********************************************************************/
#define BMP_Z88BGR                       30

/***********************************************************************
* Toolbar-IDs (Windows)
***********************************************************************/
#define ITC_Z88V                        100
#define ITC_Z88X                        110
#define ITC_Z88G                        120
#define ITC_Z88H                        130
#define ITC_Z88N                        140
#define ITC_Z88F                        150
#define ITC_Z88I1                       160
#define ITC_Z88I2                       170
#define ITC_Z88D                        180
#define ITC_Z88E                        190
#define ITC_Z88P                        200
#define ITC_Z88O                        210
#define ITC_DYN                         220
#define ITC_HELP                        230

/***********************************************************************
* Menue-IDs (Windows)
***********************************************************************/
#define IDM_DATEI                      1000
#define IDM_EDITFEST                   1010
#define IDM_WER                        1020
#define IDM_XIT                        1030
#define IDM_1Q                         1040
#define IDM_BROWSER                    1050

#define IDM_COMPUTE                    1100
#define IDM_Z88V                       1120
#define IDM_Z88G                       1122
#define IDM_Z88H                       1124 
#define IDM_Z88X                       1130
#define IDM_Z88N                       1140
#define IDM_Z88F                       1150
#define IDM_Z88I1                      1152
#define IDM_Z88I2                      1155
#define IDM_Z88D                       1160
#define IDM_Z88E                       1170
#define IDM_2Q                         1180

#define IDM_EDIT                       1200
#define IDM_Z88DYNEDIT                 1210
#define IDM_EDITCOL                    1220
#define IDM_EDITOGL                    1230
#define IDM_Z88NITXT                   1240
#define IDM_Z88I1TXT                   1250
#define IDM_Z88I2TXT                   1260
#define IDM_Z88I3TXT                   1270
#define IDM_Z88I4TXT                   1280
#define IDM_Z88I5TXT                   1285
#define IDM_Z88O0TXT                   1290
#define IDM_Z88O1TXT                   1300
#define IDM_Z88O2TXT                   1310
#define IDM_Z88O3TXT                   1320
#define IDM_Z88O4TXT                   1330
#define IDM_Z88O6TXT                   1340
#define IDM_3Q                         1350

#define IDM_PLOTTEN                    1400
#define IDM_Z88P                       1410
#define IDM_LOESCHEN                   1420
#define IDM_ANHAENGEN                  1430
#define IDM_XONSEQ                     1435
#define IDM_LASERJET                   1440
#define IDM_Z88O                       1450 
#define IDM_4Q                         1460
 
#define IDM_INDEX                      1510
#define IDM_Z88ALLG                    1520
#define IDM_Z88DYN                     1530
#define IDM_AELE1                      1540
#define IDM_BELE2                      1550
#define IDM_CELE3                      1560
#define IDM_DELE4                      1570
#define IDM_EELE5                      1580
#define IDM_FELE6                      1590
#define IDM_GELE7                      1600
#define IDM_HELE8                      1610
#define IDM_IELE9                      1620
#define IDM_JELE10                     1630
#define IDM_KELE11                     1640
#define IDM_LELE12                     1650
#define IDM_MELE13                     1660
#define IDM_NELE14                     1670
#define IDM_OELE15                     1680
#define IDM_PELE16                     1690
#define IDM_QELE17                     1700
#define IDM_RELE18                     1710
#define IDM_SELE19                     1720
#define IDM_TELE20                     1730
#define IDM_RANDBED                    1740
#define IDM_S1                         1750
#define IDM_S2                         1760
#define IDM_S3                         1770
#define IDM_S4                         1780
#define IDM_S5                         1790
#define IDM_S6                         1800
#define IDM_S7                         1810
#define IDM_S8                         1820
#define IDM_S9                         1830
#define IDM_S10                        1840

/**********************************************************
* Box-IDs (Windows)
**********************************************************/
/*---------------------------------------------------------
* Editor definieren
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT1                  1900
#define IDDLG_V_TEXT2                  1910

/*---------------------------------------------------------
* Browser definieren
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT3                  1920
#define IDDLG_V_TEXT4                  1930

/***********************************************************************
* IDs fuer Widgets (UNIX, soweit noch nicht weiter oben definiert)
***********************************************************************/
#define IDM_Z88NI                      2000

#define IDM_Z88I3                      2010
#define IDM_Z88I4                      2020
#define IDM_Z88I5                      2025
#define IDM_Z88O0                      2030
#define IDM_Z88O1                      2040
#define IDM_Z88O2                      2050
#define IDM_Z88O3                      2060
#define IDM_Z88O4                      2070
#define IDM_Z88O6                      2080

#define IDM_Z88FCD                     2090

#define IDM_I1TX                       2100
#define IDM_IATX                       2110
#define IDM_NITX                       2120
#define IDM_I1FX                       2130
#define IDM_IAFX                       2140
#define IDM_NIFX                       2150

#define IDM_RMSTO                      2160
#define IDM_CATO6O7                    2170
#define IDM_PXON88                     2180
#define IDM_LASERJ88                   2190

#define IDM_Z88FCOM                    2200
#define IDM_Z88FTES                    2210  
#define IDM_Z88II1                     2240 
#define IDM_Z88II2C                    2250 
#define IDM_Z88II2S                    2260 

/***********************************************************************
* Alerts
***********************************************************************/
#define AL_NOLOG 3000                  /* kein Z88F.LOG */ 
#define AL_NODYN 3010                  /* kein Z88.DYN */
#define AL_WRONGDYN 3020               /* Fehler in Z88.DYN */
#define AL_NOCFG 3030                  /* kein Z88COM.CFG */
#define AL_WRONGCFG 3040               /* Fehler in Z88COM.CFG */
#define AL_NOWRICFG 3050               /* Schreibfehler Z88COM.CFG */
#define AL_NOCOL 3060                  /* kein Z88.FCD */
#define AL_WRONGCOL 3065               /* Z88.FCD falsch */
#define AL_NOZ88V 3070                 /* kann Z88V nicht starten */
#define AL_NOZ88X 3080                 /* kann Z88X nicht starten */
#define AL_NOZ88N 3090                 /* kann Z88N nicht starten */
#define AL_NOZ88F 3100                 /* kann Z88F nicht starten */
#define AL_NOZ88I1 3103                /* kann Z88I1 nicht starten */
#define AL_NOZ88I2 3105                /* kann Z88I2 nicht starten */
#define AL_NOZ88D 3110                 /* kann Z88D nicht starten */
#define AL_NOZ88E 3120                 /* kann Z88E nicht starten */
#define AL_NOZ88G 3122                 /* kann Z88G nicht starten */
#define AL_NOZ88H 3124                 /* kann Z88H nicht starten */
#define AL_NOEDDYN 3130                /* Fehler Editor Z88.DYN */
#define AL_NOEDCOL 3140                /* Fehler Editor Z88P.COL */
#define AL_NOEDOGL 3150                /* Fehler Editor Z88O.OGL */
#define AL_NOEDNI 3160                 /* Fehler Editor Z88NI.TXT */
#define AL_NOEDI1 3170                 /* Fehler Editor Z88I1.TXT */
#define AL_NOEDI2 3180                 /* Fehler Editor Z88I2.TXT */
#define AL_NOEDI3 3190                 /* Fehler Editor Z88I3.TXT */
#define AL_NOEDI4 3200                 /* Fehler Editor Z88I4.TXT */
#define AL_NOEDI5 3205                 /* Fehler Editor Z88I5.TXT */
#define AL_NOEDO0 3210                 /* Fehler Editor Z88O0.TXT */
#define AL_NOEDO1 3220                 /* Fehler Editor Z88O1.TXT */
#define AL_NOEDO2 3230                 /* Fehler Editor Z88O2.TXT */
#define AL_NOEDO3 3240                 /* Fehler Editor Z88O3.TXT */
#define AL_NOEDO4 3250                 /* Fehler Editor Z88O4.TXT */
#define AL_NOEDO6 3260                 /* Fehler Editor Z88O6.TXT */
#define AL_NOZ88P 3270                 /* kann Z88P nicht starten */
#define AL_NOZ88O 3280                 /* kann Z88O nicht starten */
#define AL_NOO6 3290                   /* kann Z88O6.TXT nicht oeffnen */
#define AL_NOO7 3300                   /* kann Z88O7.TXT nicht oeffnen */
#define AL_NBYTES 3310                 /* Bytes an Z88O6.TXT gehaengt */
#define AL_NOO6TMP 3320                /* kann Z88O6.TMP nicht oeffnen */
#define AL_XONXOFF 3330                /* xon/xoff Sequenz vor Z88O6.TXT */
#define AL_LASERJET 3340               /* HP-GL und Querf. vor Z88O6.TXT */
#define AL_NO_CF_ENTRIES 3350          /* kein Font fuer entry-fields */
#define AL_NO_CF_FLARGE 3360           /* kein grosser Font */
#define AL_NO_CF_FSMALL 3370           /* kein kleiner Font */
#define AL_NO_CO_BACKGR 3380           /* keine Farbe Background */
#define AL_NO_CO_FOREGR 3390           /* keine Farbe Vordergrund */
#define AL_NO_CO_ENTRIES 3400          /* keine Farbe Textfield */
#define AL_NOBROWSER 3410              /* kein HTML- Browser */

/***********************************************************************
* LOGs
***********************************************************************/
#define LOG_BZ88COM 4000               /* Beginn Z88 */
#define LOG_OPENDYN 4010               /* Oeffnen Z88.DYN */
#define LOG_NODYN 4020                 /* kann Z88.DYN nicht oeffnen */
#define LOG_WRONGDYN 4030              /* Z88.DYN nicht o.k. */
#define LOG_NOCFG 4040                 /* kann Z88.DYN nicht oeffnen */
#define LOG_WRONGCFG 4050              /* Z88.DYN nicht o.k. */
#define LOG_NOWRICFG 4060              /* Schreibfehler Z88COM.CFG */
#define LOG_NOCOL 4070                 /* kein Z88.FCD */
#define LOG_WRONGCOL 4075              /* Z88.FCD falsch */
#define LOG_NOZ88V 4080                /* kann Z88V nicht starten */
#define LOG_NOZ88X 4090                /* kann Z88X nicht starten */
#define LOG_NOZ88N 4100                /* kann Z88N nicht starten */
#define LOG_NOZ88F 4110                /* kann Z88F nicht starten */
#define LOG_NOZ88I1 4112               /* kann Z88I1 nicht starten */
#define LOG_NOZ88I2 4115               /* kann Z88I2 nicht starten */
#define LOG_NOZ88D 4120                /* kann Z88D nicht starten */
#define LOG_NOZ88E 4130                /* kann Z88E nicht starten */
#define LOG_NOZ88G 4132                /* kann Z88G nicht starten */
#define LOG_NOZ88H 4134                /* kann Z88H nicht starten */
#define LOG_NOEDDYN 4140               /* Fehler Editor Z88.DYN */
#define LOG_NOEDCOL 4150               /* Fehler Editor Z88P.COL */
#define LOG_NOEDOGL 4155               /* Fehler Editor Z88O.OGL */
#define LOG_NOEDNI 4160                /* Fehler Editor Z88NI.TXT */
#define LOG_NOEDI1 4170                /* Fehler Editor Z88I1.TXT */
#define LOG_NOEDI2 4180                /* Fehler Editor Z88I2.TXT */
#define LOG_NOEDI3 4190                /* Fehler Editor Z88I3.TXT */
#define LOG_NOEDI4 4195                /* Fehler Editor Z88I4.TXT */
#define LOG_NOEDI5 4198                /* Fehler Editor Z88I5.TXT */
#define LOG_NOEDO0 4200                /* Fehler Editor Z88O0.TXT */
#define LOG_NOEDO1 4210                /* Fehler Editor Z88O1.TXT */
#define LOG_NOEDO2 4220                /* Fehler Editor Z88O2.TXT */
#define LOG_NOEDO3 4230                /* Fehler Editor Z88O3.TXT */
#define LOG_NOEDO4 4240                /* Fehler Editor Z88O4.TXT */
#define LOG_NOEDO6 4250                /* Fehler Editor Z88O6.TXT */
#define LOG_NOZ88P 4260                /* kann Z88P nicht starten */
#define LOG_NOZ88O 4265                /* kann Z88O nicht starten */
#define LOG_NOO6 4270                  /* kann Z88O6.TXT nicht oeffnen */
#define LOG_NOO7 4280                  /* kann Z88O7.TXT nicht oeffnen */
#define LOG_NBYTES 4290                /* Bytes an Z88O6.TXT gehaengt */
#define LOG_NOO6TMP 4300               /* kann Z88O6.TMP nicht oeffnen */
#define LOG_XONXOFF 4310               /* xon/xoff Sequenz vor Z88O6.TXT */
#define LOG_LASERJET 4320              /* HP-GL und Querf. vor Z88O6.TXT */
#define LOG_NO_CF_ENTRIES 4330         /* kein Font fuer entry-fields */
#define LOG_NO_CF_FLARGE 4340          /* kein grosser Font */
#define LOG_NO_CF_FSMALL 4350          /* kein kleiner Font */
#define LOG_NO_CO_BACKGR 4360          /* keine Farbe Background */
#define LOG_NO_CO_FOREGR 4370          /* keine Farbe Vordergrund */
#define LOG_NO_CO_ENTRIES 4380         /* keine Farbe Textfield */
#define LOG_NOBROWSER 4390             /* kein Browser */
#define LOG_LADETECT 4400              /* Sprache entdeckt */
  
