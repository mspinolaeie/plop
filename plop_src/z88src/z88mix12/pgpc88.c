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
*  Compilerunit pgpc88 enthaelt:
*  pu2s88
*  pu3s88
*
*  4.10.2005 Rieg
***********************************************************************/

/*----------------------------------------------------------------------
* Windows
*---------------------------------------------------------------------*/
#ifdef FR_WIN95
#include <z88p.h>
#endif

/*----------------------------------------------------------------------
* UNIX
*---------------------------------------------------------------------*/
#ifdef FR_UNIX
#include <z88p.h>
#endif

/***********************************************************************
* Function pu2s88
***********************************************************************/
int pu2s88(void)
{
extern FR_DOUBLEAY xgp;
extern FR_DOUBLEAY ygp;
extern FR_DOUBLEAY zgp;

extern FR_DOUBLE facx,facy,facz,cx,cy,cz;

extern FR_INT4AY kgpx;
extern FR_INT4AY kgpy;

extern FR_INT4 igpanz;

extern int ifansi;
        
FR_INT4 i;

if(ifansi== IDM_XY)
  {
  for(i= 1; i <= igpanz; i++)
    {
    kgpx[i]= (FR_INT4) (36.232 * (((xgp[i] -cx) *facx) + 138.) + 250.);
    kgpy[i]= (FR_INT4) (36.    * (((ygp[i] -cy) *facy) + 100.) + 279.);
    }
  }
else if(ifansi== IDM_XZ)
  {
  for(i= 1; i <= igpanz; i++)
    {
    kgpx[i]= (FR_INT4) (36.232 * (((xgp[i] -cx) *facx) + 138.) + 250.);
    kgpy[i]= (FR_INT4) (36.    * (((zgp[i] -cz) *facz) + 100.) + 279.);
    }
  }
else if(ifansi== IDM_YZ)
  {
  for(i= 1; i <= igpanz; i++)
    {
    kgpx[i]= (FR_INT4) (36.232 * (((ygp[i] -cy) *facy) + 138.) + 250.);
    kgpy[i]= (FR_INT4) (36.    * (((zgp[i] -cz) *facz) + 100.) + 279.);
    }
  }
  
return 0;
}

/***********************************************************************
* Function pu3s88
***********************************************************************/
int pu3s88(void)
{
extern FR_DOUBLEAY xgp;
extern FR_DOUBLEAY ygp;
extern FR_DOUBLEAY zgp;

extern FR_DOUBLE facx,facy,facz,cx,cy,cz,rotx,roty,rotz;

extern FR_INT4AY kgpx;
extern FR_INT4AY kgpy;

extern FR_INT4 igpanz;

FR_DOUBLE gx,gy,gz,hx,hy,hz,wx,wy,wz,sa,sb,sc,sd,se,sf,sg,sh,si,fpi;
        
FR_INT4 i;

fpi= 0.0174533;
        
wx= rotx*fpi;
wy= roty*fpi;
wz= rotz*fpi;
        
sa= FR_COS(wy) * FR_COS(wz);
sb= FR_COS(wy) * FR_SIN(wz);
sc= -FR_SIN(wy);
sd= FR_SIN(wx) * FR_SIN(wy) * FR_COS(wz) - FR_COS(wx) * FR_SIN(wz);
se= FR_SIN(wx) * FR_SIN(wy) * FR_SIN(wz) + FR_COS(wx) * FR_COS(wz);
sf= FR_SIN(wx) * FR_COS(wy);
sg= FR_COS(wx) * FR_SIN(wy) * FR_COS(wz) + FR_SIN(wx) * FR_SIN(wz);
sh= FR_COS(wx) * FR_SIN(wy) * FR_SIN(wz) - FR_SIN(wx) * FR_COS(wz);
si= FR_COS(wx) * FR_COS(wy);

for(i= 1; i <= igpanz; i++)
  {
  gx= (xgp[i] - cx) * facx;
  gy= (ygp[i] - cy) * facy;
  gz= (zgp[i] - cz) * facz;
  hx= gx * sa + gy * sb + gz * sc;
  hy= gx * sd + gy * se + gz * sf;
  hz= gx * sg + gy * sh + gz * si;
  kgpx[i]= (FR_INT4) (36.232 * ((hx - hy) * 0.866      + 138.) + 250.);
  kgpy[i]= (FR_INT4) (36.    * ((hx + hy) * 0.500 + hz + 100.) + 279.);
  }
return 0;
}
