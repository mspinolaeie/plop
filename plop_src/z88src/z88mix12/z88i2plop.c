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
/****************************************************************************
*  Programm z88i2.c - der Iterations- Solver Part 2
*  23.8.2005 Rieg
****************************************************************************/

/***********************************************************************
* Windows95 und NT
***********************************************************************/
#ifdef FR_WIN95
#include <z88i.h>
#include <stdio.h>    /* FILE */
#include <string.h>   /* strcpy */
#endif

#include <stdlib.h>

/***********************************************************************
*  Function-Declarationen
***********************************************************************/
int dyn88i2(void);
int ale88i(int);
int z88bi(void);
int z88ci(void);
int lan88i2(void);
int r1y88i(void);
int r4y88i(void);
int wlog88i2(FR_INT4,int);

/***********************************************************************
*  globale Variable
***********************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fl2,*fi2,*fi4,*fi5,*f1y,*f3y,*f4y,*fo1,*fo2,*fcfg;

/*  
**   fdyn= z88.dyn
**   fl2 = z88i2.log
**   fi2=  z88i2.txt
**   fi4=  z88i4.txt
**   fi5=  z88i5.txt
**   f1y=  z88o1.bny
**   f3y=  z88o3.bny
**   f4y=  z88o4.bny
**   fo1=  z88o1.txt
**   fo2=  z88o2.txt
**   fcfg= z88com.cfg
*/ 

char cdyn[1000];
char cl2[1000];
char ci2[1000];
char ci4[1000];
char ci5[1000];
char c1y[1000];
char c3y[1000];
char c4y[1000];
char co1[1000];
char co2[1000];
char cfg[1000];

#define cdyn_file_name "z88.dyn"
#define cl2_file_name "z88i2.log"
#define ci2_file_name "z88i2.txt"
#define ci4_file_name "z88i4.txt"
#define ci5_file_name "z88i5.txt"
#define c1y_file_name "z88o1.bny"
#define c3y_file_name "z88o3.bny"
#define c4y_file_name "z88o4.bny"
#define co1_file_name "z88o1.txt"
#define co2_file_name "z88o2.txt"
#define cfg_file_name "z88com.cfg"

/*--------------------------------------------------------------------------
* Pointer
*-------------------------------------------------------------------------*/
FR_DOUBLEAY GS;
FR_DOUBLEAY CI;
FR_DOUBLEAY se;
FR_DOUBLEAY rs;
FR_DOUBLEAY xi;
FR_DOUBLEAY xa;
FR_DOUBLEAY v;
FR_DOUBLEAY pk;
FR_DOUBLEAY zz;
FR_DOUBLEAY fak;
FR_DOUBLEAY x;
FR_DOUBLEAY y;
FR_DOUBLEAY z;
FR_DOUBLEAY emod;
FR_DOUBLEAY rnue;
FR_DOUBLEAY qpara;
FR_DOUBLEAY riyy;
FR_DOUBLEAY eyy;
FR_DOUBLEAY rizz;
FR_DOUBLEAY ezz;
FR_DOUBLEAY rit;
FR_DOUBLEAY wt;
FR_DOUBLEAY pres;
FR_DOUBLEAY tr1;
FR_DOUBLEAY tr2;

FR_INT4AY ip;
FR_INT4AY iez;
FR_INT4AY koi;
FR_INT4AY ifrei; 
FR_INT4AY ioffs;
FR_INT4AY koffs;
FR_INT4AY ityp;
FR_INT4AY ivon;
FR_INT4AY ibis;
FR_INT4AY intord;
FR_INT4AY nep;
FR_INT4AY noi;
FR_INT4AY noffs;

/*--------------------------------------------------------------------------
* Char-Arrays
*-------------------------------------------------------------------------*/
char cstore[256];
char cbcall[128];
char cbpref[128];
char cbhelp[512];
char cmess [256];

/*--------------------------------------------------------------------------
* Arrays
*-------------------------------------------------------------------------*/
FR_INT4 mcomp[21];                     /* 21 ist MAXPA */

/* Diese Arrays werden in HEXA88,LQUA88,QSHE88 und CSHE88 verwendet */

FR_DOUBLE xk[21], yk[21], zk[21];      /* 21 ist MAXPA , HEXA88 */
FR_DOUBLE h[21];                       /* 21 ist MAXPA , HEXA88 */
FR_DOUBLE b[361];                      /* ist 6 x 60 +1, HEXA88 */
FR_DOUBLE xx[61];                      /* ist 3 x 20 +1, HEXA88 */
FR_DOUBLE d[37];                       /* ist 6 x 6  +1, HEXA88 */
FR_DOUBLE p[61];                       /* ist 3 x 20 +1, HEXA88 */

/* fuer Plattenberechnung */
FR_DOUBLE be[49];                         /* fuer 16-Knoten Platte  */
FR_DOUBLE hi[49];
FR_DOUBLE hj[49];
FR_DOUBLE hk[49];
FR_DOUBLE bbi[145];
FR_DOUBLE bsv[97];
FR_DOUBLE dbi[10];
FR_DOUBLE dsv[5];

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
FR_DOUBLE  emode,rnuee,qparae,riyye,eyye,rizze,ezze,rite,wte,eps,rp;
FR_DOUBLE  pree,tr1e,tr2e;
FR_INT4    intore,nel,ktyp,maxit,kfoun,jelem;
FR_INT4    LANG,IDYNMEM,ICFLAG;
FR_INT4    ndim,nkp,ne,nfg,neg,nfgp1,nkoi,kflag,ibflag,ipflag,npr,iqflag;

/*--------------------------------------------------------------------------
* vorbelegte Variable
*-------------------------------------------------------------------------*/
FR_INT4    MAXGS=0,MAXNFG=0,MAXK=0,MAXE=0,MAXKOI=0,MAXNEG=0;
FR_INT4    MAXESM=3600,MAXPR=0;
int        ifmode= IDM_SOR;


int wrim88i(FR_INT4 i,int iatx)
{ return 0;
}

int wtyp88i(FR_INT4 k,FR_INT4 i)
{	return 0;
}

int wran88i(FR_INT4 k,FR_INT4 i)
{	return 0;
}
/***********************************************************************
* WinMain
***********************************************************************/
int main (int argc, char *argv[])
{
	char *tmpenv;
	char tmpname [1000];
	int iret;

#ifdef gui_plop_version
	if ((tmpenv = getenv ("TEMP")) == NULL && (tmpenv = getenv ("TMP")) == NULL) {
		tmpname [0] = '\0';
	} else {
		sprintf (tmpname, "%s\\", tmpenv);
	}
	printf ("starting z88i2, this will take a while....\n");
#else
	tmpname [0] = '\0';
#endif

	sprintf (cl2, "%s%s", tmpname, cl2_file_name);
	sprintf (ci2, "%s%s", tmpname, ci2_file_name);
	sprintf (ci5, "%s%s", tmpname, ci5_file_name);
	sprintf (c1y, "%s%s", tmpname, c1y_file_name);
	sprintf (c3y, "%s%s", tmpname, c3y_file_name);
	sprintf (c4y, "%s%s", tmpname, c4y_file_name);
	sprintf (co1, "%s%s", tmpname, co1_file_name);
	sprintf (co2, "%s%s", tmpname, co2_file_name);
	sprintf (cfg, "%s", cfg_file_name);
#ifdef gui_plop_version
	if ((tmpenv = getenv ("PLOPDIR")) == NULL) {
		tmpname [0] = '\0';
	} else {
		sprintf (tmpname, "%s\\", tmpenv);
	}
#else
	tmpname [0] = '\0';
#endif
	sprintf (cdyn, "%s%s", tmpname, cdyn_file_name);
	sprintf (ci4, "%s%s", tmpname, ci4_file_name);
	iret= lan88i2();
	if(iret != 0) {
	  ale88i(iret);
	  return(1);
	}
/*===========================================================================
* ICFLAG setzen
*==========================================================================*/
	if(ifmode == IDM_SOR) ICFLAG = 2;


		if     (ICFLAG == 1) wlog88i2(1L,LOG_CFLAGC);
		else if(ICFLAG == 2) wlog88i2(2L,LOG_CFLAGS);

/*----------------------------------------------------------------------
* dynamischen Speicher anfordern: erst ab hier moeglich
*---------------------------------------------------------------------*/
	iret= dyn88i2();
	if(iret != 0)
	  {
	  ale88i(iret);
	  return 1;
	  }

/*----------------------------------------------------------------------
* Einlesen von Z88O1.BNY und Z88O4.BNY
*---------------------------------------------------------------------*/
		iret= r1y88i();
		if(iret != 0)
		  {
		  ale88i(iret);
		  return(1);
		  }

		iret= r4y88i();
		if(iret != 0)
		  {
		  ale88i(iret);
		  return(1);
		  }

/*----------------------------------------------------------------------
* Rechnen
*---------------------------------------------------------------------*/
        iret= z88bi();
		if(iret != 0)
          {
		  ale88i(iret);
		  return(1);
          }                

        iret= z88ci();
		if(iret != 0)
          {
		  ale88i(iret);
		  return(1);
          }                   

/*----------------------------------------------------------------------
* den Speicher wieder freigeben; die UNIX- Version braucht das nicht
*---------------------------------------------------------------------*/
		if(GS)      free(GS);
		if(CI)      free(CI);
		if(se)      free(se);
		if(rs)      free(rs);
		if(xi)      free(xi);
		if(xa)      free(xa);
		if(v)       free(v);
		if(pk)      free(pk);
		if(zz)      free(zz);
		if(fak)     free(fak);
		if(x)       free(x);
		if(y)       free(y);
		if(z)       free(z);
		if(emod)    free(emod);
		if(rnue)    free(rnue);
		if(qpara)   free(qpara);
		if(riyy)    free(riyy);
		if(eyy)     free(eyy);
		if(rizz)    free(rizz);
		if(ezz)     free(ezz);
		if(rit)     free(rit);
		if(wt)      free(wt);
		if(pres)    free(pres);

		if(ip)      free(ip);
		if(iez)     free(iez);
		if(koi)     free(koi);
		if(ifrei)   free(ifrei);
		if(ioffs)   free(ioffs);
		if(koffs)   free(koffs);
		if(ityp)    free(ityp);
		if(ivon)    free(ivon);
		if(ibis)    free(ibis);
		if(intord)  free(intord);
		if(noi)     free(noi);
		if(noffs)   free(noffs);

/*----------------------------------------------------------------------
* Ende Case Go
*---------------------------------------------------------------------*/
		if(LANG == 1) strcpy(cmess,"FE-Prozessor Z88I2 gelaufen");
		if(LANG == 2) strcpy(cmess,"FEA-Solver Z88I2 done");
		printf (cmess);
	  return 0;
}
