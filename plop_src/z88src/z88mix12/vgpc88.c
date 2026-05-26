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
* diese compilerunit vgpc88 enthaelt:
*   vu2s88
*   vu3s88
*
* 16.9.2002 Rieg
***********************************************************************/
/*****************************************************************************
* WindowsNT und 95
*****************************************************************************/
#ifdef FR_WIN95
#include <z88p.h>
#include <math.h>   /* fabs,sin,cos */
#endif

/***********************************************************************
*  function vu2s88
***********************************************************************/
int vu2s88(void)
{
extern FR_DOUBLEAY xgp;
extern FR_DOUBLEAY ygp;
extern FR_DOUBLEAY zgp;

extern double facx,facy,facz,cx,cy,cz,fxcor;

extern FR_INT4AY kgpx;
extern FR_INT4AY kgpy;

extern FR_INT4 igpanz;

extern int ifansi;

extern short ixClient, iyClient;
        
double fx1,fx2,fy1,fy2;

FR_INT4 i;

fx1= ixClient*0.005;
fx2= ixClient*0.5;
fy1= iyClient*0.005;
fy2= iyClient*0.5;

if(ifansi== IDM_XY)
  {
  for(i= 1; i <= igpanz; i++)
    {
    kgpx[i]= (long) (fx1 * (xgp[i] -cx) *facx*fxcor + fx2);
    kgpy[i]= (long)-(fy1 * (ygp[i] -cy) *facy       - fy2);
    }
  }
else if(ifansi== IDM_XZ)
  {
  for(i= 1; i <= igpanz; i++)
    {
    kgpx[i]= (long) (fx1 * (xgp[i] -cx) *facx*fxcor + fx2);
    kgpy[i]= (long)-(fy1 * (zgp[i] -cz) *facz       - fy2);
    }
  }
else if(ifansi== IDM_YZ)
  {
  for(i= 1; i <= igpanz; i++)
    {
    kgpx[i]= (long) (fx1 * (ygp[i] -cy) *facy*fxcor + fx2);
    kgpy[i]= (long)-(fy1 * (zgp[i] -cz) *facz       - fy2);
    }
  }
  
return 0;
}

/***********************************************************************
*  function vu3s88
***********************************************************************/
int vu3s88(void)
{
extern FR_DOUBLEAY xgp;
extern FR_DOUBLEAY ygp;
extern FR_DOUBLEAY zgp;

extern double facx,facy,facz,cx,cy,cz,rotx,roty,rotz,fxcor;

extern FR_INT4AY kgpx;
extern FR_INT4AY kgpy;

extern FR_INT4 igpanz;

extern short ixClient, iyClient;

double gx,gy,gz,hx,hy,hz,wx,wy,wz,sa,sb,sc,sd,se,sf,sg,sh,si,fpi;
double fx1,fx2,fy1,fy2;
        
FR_INT4 i;

fx1= ixClient*0.005;
fx2= ixClient*0.5;
fy1= iyClient*0.005;
fy2= iyClient*0.5;

fpi= 0.0174533;
        
wx= rotx*fpi;
wy= roty*fpi;
wz= rotz*fpi;
        
sa= cos(wy) * cos(wz);
sb= cos(wy) * sin(wz);
sc= -sin(wy);
sd= sin(wx) * sin(wy) * cos(wz) - cos(wx) * sin(wz);
se= sin(wx) * sin(wy) * sin(wz) + cos(wx) * cos(wz);
sf= sin(wx) * cos(wy);
sg= cos(wx) * sin(wy) * cos(wz) + sin(wx) * sin(wz);
sh= cos(wx) * sin(wy) * sin(wz) - sin(wx) * cos(wz);
si= cos(wx) * cos(wy);

for(i= 1; i <= igpanz; i++)
  {
  gx= (xgp[i] - cx) * facx;
  gy= (ygp[i] - cy) * facy;
  gz= (zgp[i] - cz) * facz;
  hx= gx * sa + gy * sb + gz * sc;
  hy= gx * sd + gy * se + gz * sf;
  hz= gx * sg + gy * sh + gz * si;
  kgpx[i]= (long) (fx1 * ((hx - hy) * 0.866) * fxcor + fx2);
  kgpy[i]= (long)-(fy1 * ((hx + hy) * 0.500 +hz)     - fy2);
  }
return 0;
}

