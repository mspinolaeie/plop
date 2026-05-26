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
*  function ale88f gibt Fehlermeldungen aus
*  14.9.2005 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer WindowsNT und 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88f.h>
#include <windows.h>    /* printf */
#endif

/***********************************************************************
*  hier beginnt Function ale88f
***********************************************************************/
int ale88f(int ialert)
{
extern FR_INT4 MAXKSS,MAXESS,LANG;

char cmess[256];

switch(ialert)
  {
  case AL_NOLOG:
    if(LANG == 1) strcpy(cmess,"Kann Z88F.LOG nicht oeffnen !   STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88F.LOG !    STOP");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_NODYN:
    if(LANG == 1) strcpy(cmess,"Kann Z88.DYN nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88.DYN !    STOP");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGDYN:
    if(LANG == 1) strcpy(cmess,"Z88.DYN ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88.DYN is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_NOMEMY:
    if(LANG == 1) strcpy(cmess,"Nicht genug dynamischer Speicher !    STOP\
    Abhilfe: Eintraege in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,"Dynamic memory exhausted !    STOP\
    Recover: increase entries in Z88.DYN");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI1:
    if(LANG == 1) strcpy(cmess,"Kann Z88I1.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I1.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI2:
    if(LANG == 1) strcpy(cmess,"Kann Z88I2.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I2.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI5:
    if(LANG == 1) strcpy(cmess,"Kann Z88I5.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I5.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_NO1Y:
    if(LANG == 1) strcpy(cmess,"Kann Z88O1.BNY nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O1.BNY !    STOP");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_NO3Y:
    if(LANG == 1) strcpy(cmess,"Kann Z88O3.BNY nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O3.BNY !    STOP");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_NOO0:
    if(LANG == 1) strcpy(cmess,"Kann Z88O0.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O0.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_NOO1:
    if(LANG == 1) strcpy(cmess,"Kann Z88O1.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O1.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_NOO2:
    if(LANG == 1) strcpy(cmess,"Kann Z88O2.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O2.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONDIM:
    if(LANG == 1) strcpy(cmess,"Falsche Dimension im Structurfile !    STOP\
    Abhilfe: Im Strukturfile 2 oder 3 fuer Dimension waehlen.");
    if(LANG == 2) strcpy(cmess,"Wrong dimension in structure file !    STOP\
    Recover: enter 2 or 3 for dimension in structure file.");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXK:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Knoten ueberschritten !    STOP\
    Abhilfe: MAXK in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for nodes exhausted !    STOP\
    Recover: increase MAXK in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXE:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Elemente ueberschritten !\
    STOP    Abhilfe: MAXE in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for elements exhausted !    STOP\
    Recover: increase MAXE in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXNFG:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Freiheitsgrade ueberschritten !\
    STOP    Abhilfe: MAXNFG in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for degrees of freedom exhausted !\
    STOP    Recover: increase MAXNFG in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXNEG:
    if(LANG == 1) strcpy(cmess,"Speicher fuer E- Gesetze ueberschritten !\
    STOP    Abhilfe: MAXNEG in Z88.DYN erhoehen .");
    if(LANG == 2) strcpy(cmess,"Memory for material infos exhausted !\
    STOP    Recover: increase MAXNEG in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXPR:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Lstvektoren ueberschritten !\
    STOP    Abhilfe: MAXPR in Z88.DYN erhoehen .");
    if(LANG == 2) strcpy(cmess,"Memory for load vectors exhausted !\
    STOP    Recover: increase MAXPR in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_WROKFLAG:
    if(LANG == 1) strcpy(cmess,"Koordinatenflag KFLAG falsch !\
    STOP    Abhilfe: KFLAG in 1. Zeile Z88I1.TXT zu 0 oder 1 setzen.");
    if(LANG == 2) strcpy(cmess,"Coordinate flag KFLAG wrong !\
    STOP    Recover: enter 0 or 1 for KFLAG in first line Z88I1.TXT .");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_WROETYP:
    if(LANG == 1) strcpy(cmess,"Unbekannter Elementtyp in Z88I1.TXT !\
    STOP    Abhilfe: Elementtypen von 1 bis 13 zulassen.");
    if(LANG == 2) strcpy(cmess,"Unknown element type in Z88I1.TXT !\
    STOP    Recover: enter element types from 1 to 13.");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_EXGS:
    if(LANG == 1) strcpy(cmess,"Zuwenig Memory fuer Z88F !\
    STOP    Abhilfe: MAXGS in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory exhausted for Z88F !\
    STOP    Recover: increase MAXGS in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_EXKOI:
    if(LANG == 1) strcpy(cmess,"Zuwenig Memory fuer Z88F !\
    STOP    Abhilfe: MAXKOI in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory exhausted for Z88F !\
    STOP    Recover: increase MAXKOI in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_JACNEG:
    if(LANG == 1) strcpy(cmess,"Jacobi- Determinante Null oder negativ !\
    STOP    Elementnumerierung falsch, nicht mathematisch positiv\
    Abhilfe: Siehe Online Hilfe oder Handbuch zum Elementtyp");
    if(LANG == 2) strcpy(cmess,"Jacobi-determinant zero or negative !\
    STOP    element numbering wrong, not counter-clockwise\
    Recover: renumber wrong elements (consult manual)");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_JACLOA:
    if(LANG == 1) strcpy(cmess,"Jacobi- Determinante Null oder negativ !\
    STOP    Lastvektoren in Z88I5.TXT falsch, Nummerierung?\
    Abhilfe: Siehe Online Hilfe oder Handbuch zum Elementtyp");
    if(LANG == 2) strcpy(cmess,"Jacobi-determinant zero or negative !\
    STOP    load vektors in Z88I5.TXT wrong, correct numbered?\
    Recover: renumber wrong surfaces (consult manual)");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;

  case AL_DIAGNULL:
    if(LANG == 1) strcpy(cmess,"Diagonalelement im Gleichungssystem Null\
 oder negativ !    STOP    Liegt oft an fehlenden oder falschen Rand\
bedingungen.    Abhilfe: Randbedingungen checken (statisch unterbestimmt ?).");
    if(LANG == 2) strcpy(cmess,"diagonal element in array zero or negative !\
    STOP    Often caused by missing or wrong constraints\
    Recover: check constraints (underdefined ?).");
    MessageBox(NULL,cmess, "Z88F",MB_OK | MB_ICONHAND);
  break;
  }
return(0);
}

