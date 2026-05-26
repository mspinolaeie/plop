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
* V10.0  December 12, 2001
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
* RCOL88: Farben einlesen
* 16.9.2002 Rieg
***********************************************************************/
/***********************************************************************
* WindowsNT und 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88p.h>
#include <windows.h>
#include <stdio.h>   /* fopen,fclose,fgets */
#include <string.h>  /* strstr */
#endif

/***********************************************************************
* Functions
***********************************************************************/
int wlog88p(FR_INT4,int);

/***********************************************************************
* Start rcol88
***********************************************************************/
int rcol88(void)
{
extern BYTE ifarbe[];
extern int ibUnver,ibVerfo;

FILE *fcol;

short icol1,icol2,icol3;

char cline[256], cdummy[80];

/*----------------------------------------------------------------------
* Color- datei z88p.col oeffnen
*---------------------------------------------------------------------*/
fcol= fopen("z88p.col","rb");

if(fcol == NULL)
  {
  wlog88p(0L,LOG_NOCOL);
  return(AL_NOCOL);
  }
rewind(fcol);

/*----------------------------------------------------------------------
* Color- datei z88p.col lesen
*---------------------------------------------------------------------*/
do
  if(fgets(cline,256,fcol)== NULL) break;
while( (strstr(cline,"COLOR START"))== NULL);

if( (strstr(cline,"COLOR START"))!= NULL)              /* File */
  {
  do
    {
    fgets(cline,80,fcol);

    if( (strstr(cline,"GRAFIC START"))!= NULL)        /* Grafic */
      {
      do
        {
        fgets(cline,80,fcol);
        if( (strstr(cline,"NORMAL"))!= NULL)          /*  Unverformt */ 
          {
          sscanf(cline,"%s %d %hd %hd %hd",
          cdummy,&ibUnver,&icol1,&icol2,&icol3);
          ifarbe[0] = (BYTE)icol1;
          ifarbe[1] = (BYTE)icol2;
          ifarbe[2] = (BYTE)icol3;
          }
        if( (strstr(cline,"DEFLECTED"))!= NULL)        /* Verformt */ 
          {
          sscanf(cline,"%s %d %hd %hd %hd",
          cdummy,&ibVerfo,&icol1,&icol2,&icol3);
          ifarbe[3] = (BYTE)icol1;
          ifarbe[4] = (BYTE)icol2;
          ifarbe[5] = (BYTE)icol3;
          }
        if( (strstr(cline,"ELEMENTS"))!= NULL)        /* Elemente */ 
          {
          sscanf(cline,"%s %hd %hd %hd",cdummy,&icol1,&icol2,&icol3);
          ifarbe[6] = (BYTE)icol1;
          ifarbe[7] = (BYTE)icol2;
          ifarbe[8] = (BYTE)icol3;
          }
        if( (strstr(cline,"NODES"))!= NULL)          /* Knoten */ 
          {
          sscanf(cline,"%s %hd %hd %hd",cdummy,&icol1,&icol2,&icol3);
          ifarbe[9] = (BYTE)icol1;
          ifarbe[10]= (BYTE)icol2;
          ifarbe[11]= (BYTE)icol3;
          }
        if( (strstr(cline,"STRESS01"))!= NULL)        /* 1.Sp-Wert */ 
          {
          sscanf(cline,"%s %hd %hd %hd",cdummy,&icol1,&icol2,&icol3);
          ifarbe[12]= (BYTE)icol1;
          ifarbe[13]= (BYTE)icol2;
          ifarbe[14]= (BYTE)icol3;
          }
        if( (strstr(cline,"STRESS02"))!= NULL)        /* 2.Sp-Wert */ 
          {
          sscanf(cline,"%s %hd %hd %hd",cdummy,&icol1,&icol2,&icol3);
          ifarbe[15]= (BYTE)icol1;
          ifarbe[16]= (BYTE)icol2;
          ifarbe[17]= (BYTE)icol3;
          }
        if( (strstr(cline,"STRESS03"))!= NULL)        /* 3.Sp-Wert */ 
          {
          sscanf(cline,"%s %hd %hd %hd",cdummy,&icol1,&icol2,&icol3);
          ifarbe[18]= (BYTE)icol1;
          ifarbe[19]= (BYTE)icol2;
          ifarbe[20]= (BYTE)icol3;
          }
        if( (strstr(cline,"STRESS04"))!= NULL)        /* 4.Sp-Wert */ 
          {
          sscanf(cline,"%s %hd %hd %hd",cdummy,&icol1,&icol2,&icol3);
          ifarbe[21]= (BYTE)icol1;
          ifarbe[22]= (BYTE)icol2;
          ifarbe[23]= (BYTE)icol3;
          }
        if( (strstr(cline,"STRESS05"))!= NULL)        /* 5.Sp-Wert */ 
          {
          sscanf(cline,"%s %hd %hd %hd",cdummy,&icol1,&icol2,&icol3);
          ifarbe[24]= (BYTE)icol1;
          ifarbe[25]= (BYTE)icol2;
          ifarbe[26]= (BYTE)icol3;
          }
        if( (strstr(cline,"STRESS06"))!= NULL)        /* 6.Sp-Wert */ 
          {
          sscanf(cline,"%s %hd %hd %hd",cdummy,&icol1,&icol2,&icol3);
          ifarbe[27]= (BYTE)icol1;
          ifarbe[28]= (BYTE)icol2;
          ifarbe[29]= (BYTE)icol3;
          }
        if( (strstr(cline,"STRESS07"))!= NULL)        /* 7.Sp-Wert */ 
          {
          sscanf(cline,"%s %hd %hd %hd",cdummy,&icol1,&icol2,&icol3);
          ifarbe[30]= (BYTE)icol1;
          ifarbe[31]= (BYTE)icol2;
          ifarbe[32]= (BYTE)icol3;
          }
        if( (strstr(cline,"STRESS08"))!= NULL)        /* 8.Sp-Wert */ 
          {
          sscanf(cline,"%s %hd %hd %hd",cdummy,&icol1,&icol2,&icol3);
          ifarbe[33]= (BYTE)icol1;
          ifarbe[34]= (BYTE)icol2;
          ifarbe[35]= (BYTE)icol3;
          }
        if( (strstr(cline,"STRESS09"))!= NULL)        /* 9.Sp-Wert */ 
          {
          sscanf(cline,"%s %hd %hd %hd",cdummy,&icol1,&icol2,&icol3);
          ifarbe[36]= (BYTE)icol1;
          ifarbe[37]= (BYTE)icol2;
          ifarbe[38]= (BYTE)icol3;
          }
        if( (strstr(cline,"STRESS10"))!= NULL)        /*10.Sp-Wert */ 
          {
          sscanf(cline,"%s %hd %hd %hd",cdummy,&icol1,&icol2,&icol3);
          ifarbe[39]= (BYTE)icol1;
          ifarbe[40]= (BYTE)icol2;
          ifarbe[41]= (BYTE)icol3;
          }
        }
      while( (strstr(cline,"GRAFIC END"))== NULL);
      }                                                /* endif GRAFIC START */

    }
  while( (strstr(cline,"COLOR END"))== NULL);     
    
  }                                                    /* endif COLOR START */
else
  {
  wlog88p(0L,LOG_WRONGCOL);
  return(AL_WRONGCOL);
  }  

/*----------------------------------------------------------------------
* korrekt gelesen, file fcol schliessen
*---------------------------------------------------------------------*/
fclose(fcol);
return (0);
}

