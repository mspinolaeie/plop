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
* NAST88
* 4.10.2005 Rieg
* wandelt NASTRAN- Files aus Pro/MECHANICA (PTC, Pro/ENGINEER) 
***********************************************************************/

/***********************************************************************
* Include- Files
***********************************************************************/
#ifdef FR_UNIX
#include <z88g.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

#ifdef FR_WIN95
#include <z88g.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

/****************************************************************************
*  Function-Declarationen
****************************************************************************/
int wrim88g(FR_INT4,int);
int wlog88g(FR_INT4,int);

/****************************************************************************
*  NAST88
****************************************************************************/
int nast88(void)
{
extern FILE        *fwlo,*fpro,*fin,*fi1,*fi2,*fi3;

extern FR_INT4     ICFLAG,LANG;

extern char        cnas[];
extern char        cin[];
extern char        ci1[];
extern char        ci2[];
extern char        ci3[];

FR_DOUBLEAY        druck;

FR_DOUBLE          x= 0.,y= 0.,z= 0.;
FR_DOUBLE          emod= 0.,rnue= 0.,qpara= 0.,wert= 0.;
FR_DOUBLE          fl= 0.,flalt= 0.; 
FR_DOUBLE          rdummy,fx,fy,fz;

FR_INT4AY          id; 

FR_INT4            koi[11];

FR_INT4            neg= 0,ivon= 1,intord= 0,isflag= 1;
FR_INT4            ndim= 0,nkp= 0,ne= 0,nfg= 0,kflag= 0,ibflag= 0;
FR_INT4            ipflag=0,iqflag=0;
FR_INT4            nkn= 0,ityp= 0,ifrei= 0,ibis= 0;
FR_INT4            nrb= 0,nfl= 0,iflag1= 0,ifg= 0;
FR_INT4            ktyp16= 0,ktyp17= 0,ktyp7= 0,ktyp14= 0;
FR_INT4            ktyp18= 0,ktyp20= 0,ktyp8= 0,ktyp15= 0;
FR_INT4            nalt= 0, inow= 0;

FR_INT4            idummy,jdummy,ipuf,ispc,iload;
FR_INT4            i,j,k;

char               cstring[255],c2zeile[255],cdummy[80],cdummy2[80];

/*----------------------------------------------------------------------
* ggf. Plattenflag setzen
*---------------------------------------------------------------------*/	
if(ICFLAG == 3) ipflag = 1;

/*----------------------------------------------------------------------
* NASTRAN- File oeffnen
*---------------------------------------------------------------------*/	
if((fpro= fopen(cnas,"r"))== NULL)
  {
  wlog88g(0,LOG_NONAS);
  fclose(fwlo);
  return(AL_NONAS);
  }
else
  {
  wrim88g(0,TX_NASOPEN);
  }
	
rewind(fpro);

/*----------------------------------------------------------------------
* Zwischendatei Z88G.IN oeffnen
*---------------------------------------------------------------------*/	
if((fin= fopen(cin,"w+"))== NULL)
  {
  wlog88g(0,LOG_NOIN);
  fclose(fwlo);
  return(AL_NOIN);
  }
else
  {
  wrim88g(0,TX_INOPEN);
  }
	
rewind(fin);

/*----------------------------------------------------------------------
* jetzt die NASTRAN- Datei konvertieren
*---------------------------------------------------------------------*/
while((i= fgetc(fpro)) != EOF)
  {
  if(i == ',') i= ' ';
  fputc(i,fin);
  }

if(fpro)fclose(fpro);

/*----------------------------------------------------------------------
* Z88I1.TXT, Z88I2.TXT und Z88I3.TXT oeffnen
*---------------------------------------------------------------------*/	
if((fi1= fopen("z88i1.txt","w"))== NULL)
  {
  wlog88g(0,LOG_NOI1);
  fclose(fwlo);
  return(AL_NOI1);
  }
else
  {
  wrim88g(0,TX_I1OPEN);
  }
	        
rewind(fi1);

if((fi2= fopen("z88i2.txt","w"))== NULL)
  {
  wlog88g(0,LOG_NOI2);
  fclose(fwlo);
  return(AL_NOI2);
  }
else
  {
  wrim88g(0,TX_I2OPEN);
  }
	        
rewind(fi2);
	        
if((fi3= fopen("z88i3.txt","w"))== NULL)
  {
  wlog88g(0,LOG_NOI3);
  fclose(fwlo);
  return(AL_NOI3);
  }
else
  {
  wrim88g(0,TX_I3OPEN);
  }
	        
rewind(fi3);

/*----------------------------------------------------------------------
* 1.Durchlauf: Lastfall und Kraftfall ausfiltern
*---------------------------------------------------------------------*/	
rewind(fin);	

/* Mustererkennung SUBCASE - SPC - ggf. LOAD */
while((fgets(cstring,254,fin))!= NULL) 
  {		
  if(strncmp(cstring,"SUBCASE",7)== 0)
    {
    fgets(c2zeile,254,fin);
    if(strncmp(c2zeile,"   SPC",6)== 0)    
      {
      sscanf(c2zeile,"%s %s %ld",cdummy,cdummy2,&ispc);
      wrim88g(ispc,TX_ISPC);
      wlog88g(ispc,LOG_ISPC);

      fgets(c2zeile,254,fin);
      if(strncmp(c2zeile,"   LOAD",7)== 0)
        {    
        sscanf(c2zeile,"%s %s %ld",cdummy,cdummy2,&iload);
        wrim88g(iload,TX_ILOAD);
        wlog88g(iload,LOG_ILOAD);
        }
      goto Lskip;
      }
    }
  }
Lskip:;


/* Mustererkennung SPC - LOAD */
/*
while((fgets(cstring,254,fin))!= NULL) 
  {		
  if(strncmp(cstring,"   SPC",6)== 0)
    {
    fgets(c2zeile,254,fin);
    if(strncmp(c2zeile,"   LOAD",7)== 0)    
      {
      sscanf(cstring,"%s %s %ld",cdummy,cdummy2,&ispc);
      wrim88g(ispc,TX_ISPC);
      wlog88g(ispc,LOG_ISPC);

      sscanf(c2zeile,"%s %s %ld",cdummy,cdummy2,&iload);
      wrim88g(iload,TX_ILOAD);
      wlog88g(iload,LOG_ILOAD);

      goto Lskip;
      }
    }
  }
Lskip:;
*/

/*----------------------------------------------------------------------
* 2.Durchlauf: nkp,ne,nrb,neg,emod,rnue,qpara aus NASTRAN Datei holen
*---------------------------------------------------------------------*/	
rewind(fin);

inow= 0; /* um den ganzen Schrott vorher auszufiltern */

while((fgets(cstring,254,fin))!= NULL) 
  {		
  if(strncmp(cstring,"MAT1",4)== 0)
    {
    sscanf(cstring,"%s %ld %lf %lf",cdummy,&idummy,&emod,&rnue);
    inow= 1;
    }

/*======================================================================
* Elemente und Knoten
*=====================================================================*/
  if(strncmp(cstring,"GRID",  4) == 0) nkp++;
  if(strncmp(cstring,"CTETRA",6) == 0) ne++;
  if(strncmp(cstring,"CTRIA6",6) == 0) ne++;
  if(strncmp(cstring,"CQUAD8",6) == 0) ne++;

/*======================================================================
* QPARA
*=====================================================================*/
  if(strncmp(cstring,"PSHELL",6) == 0)
    sscanf(cstring,"%s %ld %ld %lf",cdummy,&idummy,&jdummy,&qpara);    

/*======================================================================
* Lager und Kraefte
*=====================================================================*/
  if(strncmp(cstring,"SPC",   3) == 0 && inow == 1) 
    {
    sscanf(cstring,"%s %ld",cdummy,&idummy);
    if(idummy == ispc) nrb++;
    }

  if(strncmp(cstring,"FORCE", 5) == 0  && inow == 1)
    {
    iflag1= 1;
    sscanf(cstring,"%s %ld %ld %ld %lf %lf %lf %lf",
           cdummy,&idummy,&nkn,&jdummy,&rdummy,&fx,&fy,&fz);

    if(idummy == iload)
      {
      if(FR_FABS(fx) > 1e-10) nrb++; /* FX */
      if(FR_FABS(fy) > 1e-10) nrb++; /* FY */
      if(FR_FABS(fz) > 1e-10) nrb++; /* FZ */
      }
    }

/*======================================================================
* Platten: Anzahl E-Gesetze feststellen; 
*=====================================================================*/
  if(ICFLAG == 3)
    {
    if(strncmp(cstring,"PLOAD",5) == 0)
      {
      sscanf(cstring,"%s %ld %ld %lf",cdummy,&idummy,&jdummy,&rdummy);
      if(idummy == iload) 
        {
        nfl++;
        nkn= jdummy;
        fl=  rdummy;

        if(nkn == nalt+1) 
          if(fl != flalt) neg++;   /* ungleiche Flaechenlast */

        if(nkn != nalt+1) neg+=2;  /* Luecke, Elemente ohne Flaechenlast */
  
        nalt= nkn;
        flalt= fl;
        }
      }
    }

/*======================================================================
* Dimension feststellen; 
*=====================================================================*/
  if(strncmp(cstring,"CTETRA",6)== 0) ndim= 3;
  if(strncmp(cstring,"CTRIA6",6)== 0) ndim= 2;
  if(strncmp(cstring,"CQUAD8",6)== 0) ndim= 2;
  } 

/*----------------------------------------------------------------------
* Werte andrucken
*---------------------------------------------------------------------*/
if(ICFLAG == 1 || ICFLAG == 2 || 
    (ICFLAG == 3 && nfl == 0) || ICFLAG == 4) neg= 1;

wrim88g(ndim,TX_DIMDET);
wrim88g(nkp, TX_NODDET);
wrim88g(ne , TX_ELEDET);
wrim88g(nrb, TX_CONDET);
wrim88g(neg, TX_NEGDET);
if(ICFLAG == 3) wrim88g(nfl, TX_PELDET);

wlog88g(ndim,LOG_DIMDET);
wlog88g(nkp, LOG_NODDET);
wlog88g(ne , LOG_ELEDET);
wlog88g(nrb, LOG_CONDET);
wlog88g(neg, LOG_NEGDET);
if(ICFLAG == 3) wlog88g(nfl, LOG_PELDET);

/*----------------------------------------------------------------------
* 1.Zeile Z88I1.TXT schreiben
*---------------------------------------------------------------------*/
if(ICFLAG == 1 || ICFLAG == 3) /* Volumen und Platten */
  {
  nfg= nkp*3;
  ifrei= 3;
  }

if(ICFLAG == 2 || ICFLAG == 4) /* Scheiben und Tori */
  {
  nfg= nkp*2;
  ifrei= 2;
  }

if(LANG == 1)
  fprintf(fi1,
  "%5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld   Z88I1.TXT,via Z88G V12 NASTRAN\n",
  ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag);

if(LANG == 2)
  fprintf(fi1,
  "%5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld   Z88I1.TXT, by Z88G V12 NASTRAN\n",
  ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag);

/*----------------------------------------------------------------------
* 1.Zeile Z88I2.TXT schreiben
*---------------------------------------------------------------------*/
if(LANG == 1) fprintf(fi2,"%5ld   Z88I2.TXT,via Z88G V12 NASTRAN\n",nrb);
if(LANG == 2) fprintf(fi2,"%5ld   Z88I2.TXT, by Z88G V12 NASTRAN\n",nrb);

/*----------------------------------------------------------------------
* 3.Durchlauf:
* NASTRAN Datei lesen und Z88I1.TXT, Z88I2.TXT und Z88I3.TXT schreiben
*---------------------------------------------------------------------*/
wrim88g(0,TX_REAWRI);
wlog88g(0,LOG_REAWRI);

rewind(fin);  

inow= 0;  /* um den ganzen Schrott vorher auszufiltern */

while((fgets(cstring,254,fin)) != NULL)
  {
  if(strncmp(cstring,"GRID",4)== 0) inow= 1;

/*======================================================================
* Z88I1.TXT: Knoten
*=====================================================================*/
  if(strncmp(cstring,"GRID",4)== 0)
    {
    sscanf(cstring,"%s %ld %ld %lf %lf %lf",
           cdummy,&nkn,&idummy,&x,&y,&z);

    if(LANG == 1)
      fprintf(fi1,"%5ld %5ld %+#13.5lE %+#13.5lE %+#13.5lE   Knoten #%ld\n", 
      nkn,ifrei,x,y,z,nkn);
    if(LANG == 2)
      fprintf(fi1,"%5ld %5ld %+#13.5lE %+#13.5lE %+#13.5lE   node #%ld\n", 
      nkn,ifrei,x,y,z,nkn);
    }

/*======================================================================
* Z88I1.TXT: Elemente Typ 16
*=====================================================================*/
  if(strncmp(cstring,"CTETRA",6)== 0)
    {
    koi[4]= 0;
    sscanf(cstring,"%s %ld %ld %ld %ld %ld %ld %ld %ld",
           cdummy,&k,&idummy,
           &koi[0],&koi[1],&koi[2],&koi[3],&koi[4],&koi[5]);

    if(koi[4] != 0)
      {
      ityp= 16;
      ktyp16++;

      fgets(c2zeile,254,fin);   /* 2.Zeile */
      sscanf(c2zeile,"%ld %ld %ld %ld",&koi[6],&koi[7],&koi[8],&koi[9]);      

      fprintf(fi1,"%5ld %5ld  Element %5ld\n",k,ityp,k); 
      fprintf(fi1,"%5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
              koi[0],koi[1],koi[2],koi[3],koi[4],
              koi[5],koi[6],koi[8],koi[9],koi[7]);
      ibis= k;
      }

    else

/*======================================================================
* Z88I1.TXT: Elemente Typ 17
*=====================================================================*/
      {
      ityp= 17;
      ktyp17++;

      fprintf(fi1,"%5ld %5ld  Element %5ld\n",k,ityp,k); 
      fprintf(fi1,"%5ld %5ld %5ld %5ld\n",koi[0],koi[1],koi[2],koi[3]);
      ibis= k;
      }
    }

/*======================================================================
* Z88I1.TXT: Elemente Typ 7 und Typ 20 und Typ 8
*=====================================================================*/
  if(strncmp(cstring,"CQUAD8",6)== 0)
    {
    if(ICFLAG == 2) 
      {
      ityp= 7;
      ktyp7++;
      }

    if(ICFLAG == 3) 
      {
      ityp= 20;
      ktyp20++;
      }

    if(ICFLAG == 4) 
      {
      ityp= 8;
      ktyp8++;
      }

    sscanf(cstring,"%s %ld %ld %ld %ld %ld %ld %ld %ld",
           cdummy,&k,&idummy,
           &koi[0],&koi[1],&koi[2],&koi[3],&koi[4],&koi[5]);

    fgets(c2zeile,254,fin);   /* 2.Zeile */
    sscanf(c2zeile,"%ld %ld",&koi[6],&koi[7]);   
			
    fprintf(fi1,"%5ld %5ld  Element %5ld\n",k,ityp,k); 
    fprintf(fi1,"%5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
    koi[0],koi[1],koi[2],koi[3],koi[4],koi[5],koi[6],koi[7]);
    ibis= k;
    }

/*======================================================================
* Z88I1.TXT: Elemente Typ 14 und Typ 18 und Typ 15
*=====================================================================*/
  if(strncmp(cstring,"CTRIA6",6)== 0)
    {
    if(ICFLAG == 2) 
      {
      ityp= 14;
      ktyp14++;
      }

    if(ICFLAG == 3) 
      {
      ityp= 18;
      ktyp18++;
      }

    if(ICFLAG == 4) 
      {
      ityp= 15;
      ktyp15++;
      }

    sscanf(cstring,"%s %ld %ld %ld %ld %ld %ld %ld %ld",
           cdummy,&k,&idummy,
           &koi[0],&koi[1],&koi[2],&koi[3],&koi[4],&koi[5]);
			
    fprintf(fi1,"%5ld %5ld  Element %5ld\n",k,ityp,k); 
    fprintf(fi1,"%5ld %5ld %5ld %5ld %5ld %5ld\n",
    koi[0],koi[1],koi[2],koi[3],koi[4],koi[5]);
    ibis= k;
    }

/*======================================================================
* Z88I2.TXT: Randbedingungen: Lager
*=====================================================================*/
  if(strncmp(cstring,"SPC",   3) == 0 && inow == 1)  
    {
    iflag1= 2;
    sscanf(cstring,"%s %ld %ld %ld %lf",cdummy,&idummy,&nkn,&ipuf,&wert);

    if(idummy == ispc)
      {
      if(ipuf == 1)    ifg= 1;
      if(ipuf == 2)    ifg= 2;
      if(ipuf == 3) 
        {
        if(ICFLAG== 3) ifg= 1;
        else           ifg= 3;
        }         		
      if(ipuf == 4) 
        if(ICFLAG== 3) ifg= 2;
      if(ipuf == 5) 
        if(ICFLAG== 3) ifg= 3;

      fprintf(fi2,"%5ld %5ld %5ld %10.4lf\n",nkn,ifg,iflag1,wert); 
      }
    }

/*======================================================================
* Z88I2.TXT: Randbedingungen: Kraefte
*=====================================================================*/
  if(strncmp(cstring,"FORCE", 5) == 0  && inow == 1)
    {
    iflag1= 1;
    sscanf(cstring,"%s %ld %ld %ld %lf %lf %lf %lf",
           cdummy,&idummy,&nkn,&jdummy,&rdummy,&fx,&fy,&fz);

    if(idummy == iload)
      {
  
      if(FR_FABS(fx) > 1e-10)  /* FX */
        {
        ifg= 1;
        fprintf(fi2,"%5ld %5ld %5ld %10.4lf\n",nkn,ifg,iflag1,fx);
        }

  
      if(FR_FABS(fy) > 1e-10)  /* FY */
        {
        ifg= 2;
        fprintf(fi2,"%5ld %5ld %5ld %10.4lf\n",nkn,ifg,iflag1,fy);
        }

  
      if(FR_FABS(fz) > 1e-10)  /* FZ */
        {
        ifg= 3;
        fprintf(fi2,"%5ld %5ld %5ld %10.4lf\n",nkn,ifg,iflag1,fz);
        }
      }
    }
  
  }  /* Ende while 3.Durchlauf */  

wrim88g(nkp,   TX_NODDON);
wrim88g(ne ,   TX_ELEDON);
wrim88g(nrb,   TX_CONDON);
if(ICFLAG == 1)
  {
  wrim88g(ktyp16,TX_16DET);
  wrim88g(ktyp17,TX_17DET);
  }
if(ICFLAG == 2)
  {
  wrim88g(ktyp7, TX_7DET);
  wrim88g(ktyp14,TX_14DET);
  }
if(ICFLAG == 3)
  {
  wrim88g(ktyp20,TX_20DET);
  wrim88g(ktyp18,TX_18DET);
  }
if(ICFLAG == 4)
  {
  wrim88g(ktyp8, TX_8DET);
  wrim88g(ktyp15,TX_15DET);
  }

wlog88g(nkp,   LOG_NODDON);
wlog88g(ne ,   LOG_ELEDON);
wlog88g(nrb,   LOG_CONDON);
if(ICFLAG == 1)
  {
  wlog88g(ktyp16,LOG_16DET);
  wlog88g(ktyp17,LOG_17DET);
  }
if(ICFLAG == 2)
  {
  wlog88g(ktyp7, LOG_7DET);
  wlog88g(ktyp14,LOG_14DET);
  }
if(ICFLAG == 3)
  {
  wlog88g(ktyp20,LOG_20DET);
  wlog88g(ktyp18,LOG_18DET);
  }
if(ICFLAG == 4)
  {
  wlog88g(ktyp8, LOG_8DET);
  wlog88g(ktyp15,LOG_15DET);
  }

/*======================================================================
* Z88I1.TXT: E-Gesetz, wenn 3D, Scheiben oder Platten ganz ohne p
*=====================================================================*/
if(ktyp16 > 0) intord= 5;
if(ktyp17 > 0) intord= 4;
if(ktyp7  > 0) intord= 3;
if(ktyp14 > 0) intord= 3;
if(ktyp18 > 0) intord= 3;
if(ktyp20 > 0) intord= 2;
if(ktyp8  > 0) intord= 3;
if(ktyp15 > 0) intord= 3;

if(ICFLAG == 1 || ICFLAG ==2 ||
   (ICFLAG == 3 && nfl == 0) || ICFLAG == 4)
  fprintf(fi1,"%5ld %5ld %+#13.5lE %+#13.5lE %5ld %+#13.5lE\n",
	  ivon,ibis,emod,rnue,intord,qpara);

/*======================================================================
* Z88I3.TXT: erste und damit letzte Zeile
*=====================================================================*/
if(LANG == 1)
  fprintf(fi3,"%5ld %5ld %5ld   Z88I3.TXT,via Z88G V12 NASTRAN\n",
  intord,kflag,isflag);
if(LANG == 2)
  fprintf(fi3,"%5ld %5ld %5ld   Z88I3.TXT, by Z88G V12 NASTRAN\n",
  intord,kflag,isflag);

/*----------------------------------------------------------------------
* ggf. 4.Durchlauf fuer Platten, wenn Flaechenlasten vorhanden
* Z88I1.TXT: E-Gesetz
*---------------------------------------------------------------------*/
if(ICFLAG == 3 && nfl > 0)
  {
  rewind(fin);  

/*======================================================================
* Speicher kommen lassen
*=====================================================================*/
  druck= (FR_DOUBLEAY) FR_CALLOC(nfl+1,sizeof(FR_DOUBLE));
  if(druck == NULL)
    {
    wlog88g(1,LOG_ARRAYNOTOK);
    fclose(fwlo);
    return(AL_NOMEMY);
    }
  else
    wlog88g(1,LOG_ARRAYOK);

  id= (FR_INT4AY) FR_CALLOC(nfl+1,sizeof(FR_INT4));
  if(id == NULL)
    {
    wlog88g(2,LOG_ARRAYNOTOK);
    fclose(fwlo);
    return(AL_NOMEMY);
    }
  else
    wlog88g(2,LOG_ARRAYOK);

/*======================================================================
* Vektoren fuer Druck und Element-Nummer belegen
*=====================================================================*/
  i= 0;
  while((fgets(cstring,254,fin)) != NULL)
    {
    if(strncmp(cstring,"PLOAD",5)== 0)
      {
      sscanf(cstring,"%s %ld %ld %lf",cdummy,&idummy,&jdummy,&rdummy);
      if(idummy == iload) 
        {
        i++;
        nkn= jdummy;
        fl= -rdummy;

        druck[i]= fl;
        id[i]   = nkn;
        }
      }
    }

/*======================================================================
* E-Gesetze aufbauen
*=====================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 1.E-Gesetz aufbauen, gilt auch, wenn alle Ele. gleichen Druck haben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
  ivon= 1;
  ibis= 1;
  j=    1;

  if(id[1] == 1)
    {
    while((druck[j+1] == druck[j]) && (id[j+1] == id[j]+1)) 
      {
      ibis++; 
      j++;
      }
    fprintf(fi1,
    "%5ld %5ld %+#13.5lE %+#13.5lE %5ld %+#13.5lE %+#13.5lE\n",
    ivon,ibis,emod,rnue,intord,qpara,druck[j]);
    j++;
    }
  else
    {
    ibis= id[1]-1;
    fprintf(fi1,
    "%5ld %5ld %+#13.5lE %+#13.5lE %5ld %+#13.5lE  0.\n",
    ivon,ibis,emod,rnue,intord,qpara);
    }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* weitere E-Gesetz aufbauen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
  if(neg > 1)
    {
    for(i= 2; i <= neg; i++)
      {
      ibis++;
      ivon= ibis;

      if(id[j] == ivon)
        {
        while((druck[j+1] == druck[j]) && (id[j+1] == id[j]+1)) 
          {
          ibis++; 
          j++;
          }
        fprintf(fi1,
        "%5ld %5ld %+#13.5lE %+#13.5lE %5ld %+#13.5lE %+#13.5lE\n",
	ivon,ibis,emod,rnue,intord,qpara,druck[j]);
        j++;
        }
      else
        {
        ibis= id[j]-1;
        fprintf(fi1,
        "%5ld %5ld %+#13.5lE %+#13.5lE %5ld %+#13.5lE  0.\n",
	ivon,ibis,emod,rnue,intord,qpara);
        }
      }
    }

/*======================================================================
* Vektoren freigeben
*=====================================================================*/
  if(druck) free (druck);
  if(id)    free (id);

  } /* Ende ICFLAG == 3 */

/*----------------------------------------------------------------------
* Files schliessen und zurueck
*---------------------------------------------------------------------*/
fclose(fin);
fclose(fi1);
fclose(fi2);
fclose(fi3);

wrim88g(0,TX_Z88CS);
wlog88g(0,LOG_Z88CS);

return(0);
}
