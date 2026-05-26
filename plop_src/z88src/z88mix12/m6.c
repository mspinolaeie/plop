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
* Composed and edited and coypright by 
* Professor Dr.-Ing. Frank Rieg, University of Bayreuth, Germany
*
* eMail: 
* frank.rieg@uni-bayreuth.de
* dr.frank.rieg@t-online.de
* 
* V10.0  December 12, 2001
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
* Compilerunit m6.c enthaelt:  rsto88 und wsto88
* 23.3.2002 Rieg
***********************************************************************/

/*----------------------------------------------------------------------
* WindowsNT und 95
*---------------------------------------------------------------------*/
#ifdef FR_WIN95
#include <z88p.h>
#include <stdio.h>   /* fopen,fprintf,fgets,sscanf,sprintf,fclose */
#endif

/*----------------------------------------------------------------------
* UNIX
*---------------------------------------------------------------------*/
#ifdef FR_UNIX
#include <z88p.h>
#include <stdio.h>   /* fopen,fprintf,fgets,sscanf,sprintf,fclose */
#endif

/***********************************************************************
* Functions
***********************************************************************/
int wlog88p(FR_INT4,int);

/***********************************************************************
* hier beginnt Function rsto88
***********************************************************************/
int rsto88(void)
{
extern FILE *f8;

extern FR_DOUBLE facx,facy,facz,cx,cy,cz,rotx,roty,rotz;
extern FR_DOUBLE fux,fuy,fuz,fxcor;
extern FR_INT4 ndim;
extern int ifansi,iflabe;
extern char csto[],cintfn[],cstrn[];

char cline[256];
        
f8= fopen(csto,"r");
if(f8 == NULL)
  {
  wlog88p(0,LOG_NOSTO); 
  return 1;
  }
        
wlog88p(0,LOG_REASTO);
         
fgets(cline,256,f8);
sscanf(cline,"%s",cintfn);

fgets(cline,256,f8);
sscanf(cline,"%s",cstrn);
fgets(cline,256,f8);
sscanf(cline,"%lf %lf %lf",&facx,&facy,&facz);

fgets(cline,256,f8);
sscanf(cline,"%lf %lf %lf",&cx,&cy,&cz);

fgets(cline,256,f8);
sscanf(cline,"%lf %lf %lf",&rotx,&roty,&rotz);

fgets(cline,256,f8);
sscanf(cline,"%lf %lf %lf",&fux,&fuy,&fuz);

fgets(cline,256,f8);
sscanf(cline,"%lf",&fxcor);

fgets(cline,256,f8);
sscanf(cline,"%ld %d %d",&ndim,&ifansi,&iflabe);

fclose(f8);
wlog88p(0,LOG_REASTOOK);
return 0;
}

/***********************************************************************
* hier beginnt Function wsto88
***********************************************************************/
int wsto88(void)
{
extern FILE *f8;
extern FR_DOUBLE facx,facy,facz,cx,cy,cz,rotx,roty,rotz;
extern FR_DOUBLE fux,fuy,fuz,fxcor;
extern FR_INT4 ndim;
extern int ifansi,iflabe;
extern char csto[],cintfn[],cstrn[];

char cline[256];
        
f8= fopen(csto,"w+");
if(f8 == NULL)
  {
  wlog88p(0,LOG_NOOPENSTO);
  return(AL_NOOPENSTO);
  }
          
wlog88p(0,LOG_WRISTO);

sprintf(cline,"%s\n",cintfn);
fputs(cline,f8);

sprintf(cline,"%s\n",cstrn);
fputs(cline,f8);

sprintf(cline,"%lf %lf %lf\n",facx,facy,facz);
fputs(cline,f8);

sprintf(cline,"%lf %lf %lf\n",cx,cy,cz);
fputs(cline,f8);

sprintf(cline,"%lf %lf %lf\n",rotx,roty,rotz);
fputs(cline,f8);

sprintf(cline,"%lf %lf %lf\n",fux,fuy,fuz);
fputs(cline,f8);

sprintf(cline,"%lf\n",fxcor);
fputs(cline,f8);

sprintf(cline,"%ld %d %d\n",ndim,ifansi,iflabe);
fputs(cline,f8);
        
fclose(f8);
wlog88p(0,LOG_WRISTOOK);
return 0;
}
