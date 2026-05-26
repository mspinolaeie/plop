/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows OS.
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
* Z88 should compile and run under any Windows release, starting
* with Windows95.
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
*  function ale88c gibt Fehlermeldungen aus
*  20.7.2005 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer WindowsNT und 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88com.h>
#include <windows.h>    /* printf */
#endif

/***********************************************************************
*  hier beginnt Function ale88c
***********************************************************************/
int ale88c(int ialert)
{
extern FR_INT4 LANG;

char cmess[256];

switch(ialert)
  {
  case AL_NOLOG:
    if(LANG == 1) strcpy(cmess,"Kann Z88COM.LOG nicht oeffnen !   STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88COM.LOG !    STOP");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONHAND);
  break;

  case AL_NODYN:
    if(LANG == 1) strcpy(cmess,"Kann Z88.DYN nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88.DYN !    STOP");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGDYN:
    if(LANG == 1) strcpy(cmess,"Z88.DYN ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88.DYN is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONHAND);
  break;

  case AL_NOCFG:
    if(LANG == 1) strcpy(cmess,"Kann Z88COM.CFG nicht oeffnen !   STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88COM.CFG !    STOP");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGCFG:
    if(LANG == 1) strcpy(cmess,"Z88COM.CFG ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88COM.CFG is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONHAND);
  break;

  case AL_NOWRICFG:
    if(LANG == 1) strcpy(cmess,
      "Fehler beim Schreiben von Z88COM.CFG !    STOP");
    if(LANG == 2) strcpy(cmess,"Error when writing Z88COM.CFG !    STOP");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONHAND);
  break;

  case AL_NOZ88V:
    if(LANG == 1) strcpy(cmess,
      "Z88V konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88V !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88G:
    if(LANG == 1) strcpy(cmess,
      "Z88G konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88G !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88H:
    if(LANG == 1) strcpy(cmess,
      "Z88H konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88H !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88X:
    if(LANG == 1) strcpy(cmess,
      "Z88X konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88X !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88N:
    if(LANG == 1) strcpy(cmess,
      "Z88N konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88N !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88F:
    if(LANG == 1) strcpy(cmess,
      "Z88F konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88F !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88I1:
    if(LANG == 1) strcpy(cmess,
      "Z88I1 konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88I1 !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88I2:
    if(LANG == 1) strcpy(cmess,
      "Z88I2 konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88I2 !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88D:
    if(LANG == 1) strcpy(cmess,
      "Z88D konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88D !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88E:
    if(LANG == 1) strcpy(cmess,
      "Z88E konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88E !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDDYN:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88.DYN konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88.DYN !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDCOL:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88P.COL konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88P.COL !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDOGL:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O.OGL konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O.OGL !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDNI:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88NI.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88NI.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDI1:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88I1.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88I1.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDI2:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88I2.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88I2.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDI3:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88I3.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88I3.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDI4:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88I4.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88I4.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDI5:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88I5.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88I5.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDO0:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O0.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O0.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDO1:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O1.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O1.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDO2:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O2.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O2.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDO3:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O3.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O3.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDO4:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O4.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O4.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDO6:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O6.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O6.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88P:
    if(LANG == 1) strcpy(cmess,
      "Z88P konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88P !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88O:
    if(LANG == 1) strcpy(cmess,
      "Z88O konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88O !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOO6:
    if(LANG == 1) strcpy(cmess,"Kann Z88O6.TXT nicht oeffnen !   WEITER");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O6.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOO7:
    if(LANG == 1) strcpy(cmess,"Kann Z88O7.TXT nicht oeffnen !   WEITER");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O7.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NBYTES:
    if(LANG == 1) strcpy(cmess,"Z88O7.TXT an Z88O6.TXT angehaengt !");
    if(LANG == 2) strcpy(cmess,"Z88O7.TXT added to Z88O6.TXT !");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONINFORMATION);
  break;

  case AL_NOO6TMP:
    if(LANG == 1) strcpy(cmess,"Kann Z88O6.TMP nicht oeffnen !   WEITER");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O6.TMP !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_XONXOFF:
    if(LANG == 1) strcpy(cmess,"XON/XOFF-Sequenz in Z88O6.TXT eingebaut !");
    if(LANG == 2) strcpy(cmess,"XON/XOFF command added to Z88O6.TXT !");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONINFORMATION);
  break;

  case AL_LASERJET:
    if(LANG == 1) strcpy(cmess,"LaserJet-Befehl in Z88O6.TXT eingebaut !");
    if(LANG == 2) strcpy(cmess,"LaserJet command added to Z88O6.TXT !");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONINFORMATION);
  break;

  case AL_NOBROWSER:
    if(LANG == 1) strcpy(cmess,
    "HTML- Browser konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch HTML- Browser !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  }
return(0);
}

