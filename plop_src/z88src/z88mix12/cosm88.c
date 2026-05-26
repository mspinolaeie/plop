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
* COSM88
* 14.3.2005 Rieg
* wandelt COSMOS- Files aus Pro/MESH (PTC, Pro/ENGINEER) 
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
*  COSM88
****************************************************************************/
int cosm88(void)
{
extern FILE        *fwlo,*fpro,*fi1,*fi2,*fi3;

extern FR_INT4     ICFLAG,LANG;

extern char        ccos[];
extern char        ci1[];
extern char        ci2[];
extern char        ci3[];

FR_DOUBLEAY        druck;

FR_DOUBLE          x= 0.,y= 0.,z= 0.;
FR_DOUBLE          emod= 0.,rnue= 0.,qpara= 0.,wert= 0.;
FR_DOUBLE          fl= 0.,flalt= 0.; 

FR_INT4AY          id; 

FR_INT4            koi[11];

FR_INT4            neg= 0,ivon= 1,intord= 0,isflag= 1;
FR_INT4            ndim= 0,nkp= 0,ne= 0,nfg= 0,kflag= 0,ibflag= 0;
FR_INT4            ipflag=0,iqflag=0;
FR_INT4            nkn= 0,ityp= 0,ifrei= 0,ibis= 0;
FR_INT4            nrb= 0,nfl= 0,iflag1= 0,ifg= 0;
FR_INT4            ktyp16= 0,ktyp17= 0,ktyp7= 0,ktyp14= 0;
FR_INT4            ktyp18= 0,ktyp20= 0,ktyp8= 0,ktyp15= 0;
FR_INT4            nalt= 0;

FR_INT4            i,j,k;

char               cstring[255];
char               csep[]= ",";
char               *cteils;

/*----------------------------------------------------------------------
* ggf. Plattenflag setzen
*---------------------------------------------------------------------*/	
if(ICFLAG == 3) ipflag = 1;

/*----------------------------------------------------------------------
* COSMOS- File oeffnen
*---------------------------------------------------------------------*/	
if((fpro= fopen(ccos,"r"))== NULL)
  {
  wlog88g(0,LOG_NOCOS);
  fclose(fwlo);
  return(AL_NOCOS);
  }
else
  {
  wrim88g(0,TX_COSOPEN);
  }
	
rewind(fpro);
	
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
* 1.Durchlauf:
* nkp,ne,nrb,neg,emod,rnue,qpara aus COSMOS Datei ermitteln
*---------------------------------------------------------------------*/	
while((fgets(cstring,254,fpro))!= NULL)        /* EMOD */
  {		
  if(strncmp(cstring,"MPROP,1,EX",10)== 0)
    {
    cteils= strtok(cstring,csep);
    for(i = 1;i <= 3;i++) cteils= strtok(NULL,csep);
    emod= atof(cteils);
    }

  if(strncmp(cstring,"MPROP,1,NUXY",12)== 0)  /* RNUE */
    {
    cteils= strtok(cstring,csep);
    for(i = 1;i <= 3;i++) cteils= strtok(NULL,csep);
    rnue= atof(cteils);
    }

  if(strncmp(cstring,"RCONST",6)== 0)         /* QPARA */
    {
    cteils= strtok(cstring, csep);
    for (i = 1;i <= 5;i++) cteils= strtok(NULL,csep);
    qpara= atof(cteils);
    }

  if(strncmp(cstring,"ND", 2) == 0) nkp++;
  if(strncmp(cstring,"EL", 2) == 0) ne++;
  if(strncmp(cstring,"DND",3) == 0) nrb++;
  if(strncmp(cstring,"FND",3) == 0) nrb++;

/*======================================================================
* Platten: Anzahl E-Gesetze feststellen; 
*=====================================================================*/
  if(ICFLAG == 3)
    {
    if(strncmp(cstring,"PEL",3) == 0)
      {
      nfl++;

      cteils= strtok(cstring,csep);
      cteils= strtok(NULL,csep);
      nkn= atoi(cteils);

      cteils= strtok(NULL,csep);
      fl= atof(cteils);

      if(nkn == nalt+1) 
        if(fl != flalt) neg++;   /* ungleiche Flaechenlast */

      if(nkn != nalt+1) neg+=2;  /* Luecke, Elemente ohne Flaechenlast */
  
      nalt= nkn;
      flalt= fl;
      }
    }

  if((strncmp(cstring,"EL",2)== 0)&&(strstr(cstring,"VL,0,10"))) ndim= 3;
  if((strncmp(cstring,"EL",2)== 0)&&(strstr(cstring,"VL,0,4")))  ndim= 3;
  if((strncmp(cstring,"EL",2)== 0)&&(strstr(cstring,"SF,0,8")))  ndim= 2;  
  if((strncmp(cstring,"EL",2)== 0)&&(strstr(cstring,"SF,0,6")))  ndim= 2;

  } /* 1.Durchlauf fertig */

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
if(ICFLAG == 1 || ICFLAG == 3)
  {
  nfg= nkp*3;
  ifrei= 3;
  }

if(ICFLAG == 2 || ICFLAG == 4)
  {
  nfg= nkp*2;
  ifrei= 2;
  }

if(LANG == 1)
  fprintf(fi1,
  "%5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld   Z88I1.TXT,via Z88G V12 COSMOS\n",
  ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag);

if(LANG == 2)
  fprintf(fi1,
  "%5ld %5ld %5ld %5ld %5ld %5ld %5ld  %5ld%5ld   Z88I1.TXT, by Z88G V12 COSMOS\n",
  ndim,nkp,ne,nfg,neg,kflag,ibflag,ipflag,iqflag);

/*----------------------------------------------------------------------
* 1.Zeile Z88I2.TXT schreiben
*---------------------------------------------------------------------*/
if(LANG == 1) fprintf(fi2,"%5ld   Z88I2.TXT,via Z88G V12 COSMOS\n",nrb);
if(LANG == 2) fprintf(fi2,"%5ld   Z88I2.TXT, by Z88G V12 COSMOS\n",nrb);

/*----------------------------------------------------------------------
* 2.Durchlauf:
* COSMOS Datei lesen und Z88I1.TXT, Z88I2.TXT und Z88I3.TXT schreiben
*---------------------------------------------------------------------*/
wrim88g(0,TX_REAWRI);
wlog88g(0,LOG_REAWRI);

rewind(fpro);  

fgets(cstring,254,fpro);

while((fgets(cstring,254,fpro)) != NULL)
  {
/*======================================================================
* Z88I1.TXT: Knoten
*=====================================================================*/
  if(strncmp(cstring,"ND",2)== 0)
    {
    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    nkn= atoi(cteils);

    cteils= strtok(NULL,csep);
    x= atof(cteils);

    cteils= strtok(NULL,csep);
    y= atof(cteils); 

    if(ndim == 3)
      {
      cteils= strtok(NULL,csep);
      z= atof(cteils); 
      }

    if(LANG == 1)
      fprintf(fi1,"%5ld %5ld %+#13.5lE %+#13.5lE %+#13.5lE   Knoten #%ld\n", 
      nkn,ifrei,x,y,z,nkn);
    if(LANG == 2)
      fprintf(fi1,"%5ld %5ld %+#13.5lE %+#13.5lE %+#13.5lE   node #%ld\n", 
      nkn,ifrei,x,y,z,nkn);
    }

/*======================================================================
* Z88I1.TXT: Elemente
* Typ 16
*=====================================================================*/
  if((strncmp(cstring,"EL",2)== 0) && (strstr(cstring,"VL,0,10")))
    {
    ityp= 16;
    ktyp16++;
    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    k= atoi(cteils);

    for(i = 1;i <= 3;i++) cteils= strtok(NULL, csep);

    for(i = 0;i < 10;i++)
      {
      cteils= strtok(NULL,csep);
      koi[i] = atoi(cteils);
      }
			
    fprintf(fi1,"%5ld %5ld  Element %5ld\n",k,ityp,k); 
    fprintf(fi1,"%5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
            koi[0],koi[1],koi[2],koi[3],koi[4],
            koi[5],koi[6],koi[8],koi[9],koi[7]);
    ibis= k;
    }

/*======================================================================
* Z88I1.TXT: Elemente
* Typ 17
*=====================================================================*/
  if((strncmp(cstring,"EL",2)== 0) && (strstr(cstring,"VL,0,4")))
    {
    ityp= 17;
    ktyp17++;
    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    k= atoi(cteils);

    for(i = 1;i <= 3;i++) cteils= strtok(NULL, csep);

    for(i = 0;i < 4;i++)
      {
      cteils= strtok(NULL,csep);
      koi[i] = atoi(cteils);
      }
			
    fprintf(fi1,"%5ld %5ld  Element %5ld\n",k,ityp,k); 
    fprintf(fi1,"%5ld %5ld %5ld %5ld\n",koi[0],koi[1],koi[2],koi[3]);
    ibis= k;
    }

/*======================================================================
* Z88I1.TXT: Elemente Typ 7 und Typ 20 und Typ 8
*=====================================================================*/
  if((strncmp(cstring,"EL",2)== 0) && (strstr(cstring,"SF,0,8")))
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

    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    k= atoi(cteils);

    for(i = 1;i <= 3;i++) cteils= strtok(NULL, csep);

    for(i = 0;i < 8;i++)
      {
      cteils= strtok(NULL,csep);
      koi[i] = atoi(cteils);
      }
			
    fprintf(fi1,"%5ld %5ld  Element %5ld\n",k,ityp,k); 
    fprintf(fi1,"%5ld %5ld %5ld %5ld %5ld %5ld %5ld %5ld\n",
    koi[0],koi[1],koi[2],koi[3],koi[4],koi[5],koi[6],koi[7]);
    ibis= k;
    }

/*======================================================================
* Z88I1.TXT: Elemente Typ 14 und Typ 18 und Typ 15
*=====================================================================*/
  if((strncmp(cstring,"EL",2)== 0) && (strstr(cstring,"SF,0,6")))
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

    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    k= atoi(cteils);

    for(i = 1;i <= 3;i++) cteils= strtok(NULL, csep);

    for(i = 0;i < 6;i++)
      {
      cteils= strtok(NULL,csep);
      koi[i] = atoi(cteils);
      }
			
    fprintf(fi1,"%5ld %5ld  Element %5ld\n",k,ityp,k); 
    fprintf(fi1,"%5ld %5ld %5ld %5ld %5ld %5ld\n",
    koi[0],koi[1],koi[2],koi[3],koi[4],koi[5]);
    ibis= k;
    }
		
/*======================================================================
* Z88I2.TXT: Randbedingungen: Lager
*=====================================================================*/
  if(strncmp(cstring,"DND",3)== 0)
    {
    iflag1= 2;
    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    nkn= atoi(cteils);	

    cteils= strtok(NULL,csep);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebungen gleich Null
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(cteils[0]== 'U')
      {
      if(cteils[1]== 'X') ifg= 1;
      if(cteils[1]== 'Y') ifg= 2;
      if(cteils[1]== 'Z') 
        {
        if(ICFLAG== 3)    ifg= 1;
        else              ifg= 3;
        }
      }                 		

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Rotationen gleich Null bei Platten
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(cteils[0]== 'R' && ICFLAG == 3)
      {
      if(cteils[1]== 'X') ifg= 2;
      if(cteils[1]== 'Y') ifg= 3;
      if(cteils[1]== 'Z') goto Lneu;  /* gibt's gar nicht */
      }                 		

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ..und ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    cteils= strtok(NULL,csep);
    wert= atof(cteils);
			
    fprintf(fi2,"%5ld %5ld %5ld %10.4lf\n",nkn,ifg,iflag1,wert);
    }
		
/*======================================================================
* Z88I2.TXT: Randbedingungen: Kraefte
*=====================================================================*/
  if(strncmp(cstring,"FND",3)== 0)
    {
    iflag1= 1;
    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    nkn= atoi(cteils);	

    cteils= strtok(NULL,csep);
    if(cteils[1]== 'X') ifg= 1;
    if(cteils[1]== 'Y') ifg= 2;
    if(cteils[1]== 'Z') ifg= 3;
                        		
    cteils= strtok(NULL,csep);
    wert= atof(cteils);

    fprintf(fi2,"%5ld %5ld %5ld %10.4lf\n",nkn,ifg,iflag1,wert);
    }
  
Lneu:;
  }  /* Ende while 2.Durchlauf */  

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
  fprintf(fi3,"%5ld %5ld %5ld   Z88I3.TXT,via Z88G V12 COSMOS\n",
  intord,kflag,isflag);
if(LANG == 2)
  fprintf(fi3,"%5ld %5ld %5ld   Z88I3.TXT, by Z88G V12 COSMOS\n",
  intord,kflag,isflag);

/*----------------------------------------------------------------------
* ggf. 3.Durchlauf fuer Platten, wenn Flaechenlasten vorhanden
* Z88I1.TXT: E-Gesetz
*---------------------------------------------------------------------*/
if(ICFLAG == 3 && nfl > 0)
  {
  rewind(fpro);  

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
  while((fgets(cstring,254,fpro)) != NULL)
    {
    if(strncmp(cstring,"PEL",3)== 0)
      {
      i++;

      cteils= strtok(cstring,csep);
      cteils= strtok(NULL,csep);
      nkn= atoi(cteils);

      cteils= strtok(NULL,csep);
      fl= atof(cteils);

      druck[i]= fl;
      id[i]   = nkn;
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
fclose(fpro);
fclose(fi1);
fclose(fi2);
fclose(fi3);

wrim88g(0,TX_Z88CS);
wlog88g(0,LOG_Z88CS);

return(0);
}
