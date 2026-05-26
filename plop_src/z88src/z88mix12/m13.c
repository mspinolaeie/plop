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
* Compilerunit m13.c fuer Z88O enthaelt:
* fsca88
* malk88
* tet588
* 6.1.2004 Rieg
***********************************************************************/ 
/***********************************************************************
* Windows 95 und NT
***********************************************************************/
#ifdef FR_WIN95
#include <z88o.h>
#include <windows.h>
#include <commctrl.h>
#include <gl\gl.h>
#include <stdio.h>  
#endif

/***********************************************************************
* Font- Structure GLFONT
***********************************************************************/
typedef struct
    {
    GLuint base;        /* DisplayList Nr.erstes Zeichen */
    int    widths[256]; /* Zeichenweite in Pixels */
    int    height;      /* Zeichenhoehe */
    } GLFONT;

/***********************************************************************
* Functions
***********************************************************************/
GLFONT * FontCreate(HDC hdc,const char *typeface,
                    int height,int weight,DWORD italic);
void	 FontPuts(GLFONT *font, const char *cs);
void     FontDelete(GLFONT *font);

/***********************************************************************
* fsca88 zeichnet die Farbskala fuer die Spannungen und Verschiebungen
***********************************************************************/
int fsca88(void)
{
extern GLFONT      *Font;

extern FR_DOUBLE   xm;

extern GLfloat     rot[];
extern GLfloat     gruen[];
extern GLfloat     blau[];

extern FR_DOUBLE   fspa[];

extern FR_INT4     LANG;

extern int         if3d;

char               cstring[80];

/*----------------------------------------------------------------------
* fsca88 zeichnet die Farbskala fuer die Spannungen und Verschiebungen
*---------------------------------------------------------------------*/
glColor3f(rot[1],gruen[1],blau[1]);
glRectd(xm+4,48.0,xm+12,40.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,44.0,0.00);
sprintf(cstring,"%+#10.2lE ~ %+#10.2lE",fspa[1],fspa[2]);
FontPuts(Font,cstring);	

glColor3f(rot[2],gruen[2],blau[2]);
glRectd(xm+4,40.0,xm+12,32.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,36.0,0.00);
sprintf(cstring,"%+#10.2lE ~ %+#10.2lE",fspa[2],fspa[3]);
FontPuts(Font,cstring);	

glColor3f(rot[3],gruen[3],blau[3]);
glRectd(xm+4,32.0,xm+12,24.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,28.0,0.00);
sprintf(cstring,"%+#10.2lE ~ %+#10.2lE",fspa[3],fspa[4]);
FontPuts(Font,cstring);	

glColor3f(rot[4],gruen[4],blau[4]);
glRectd(xm+4,24.0,xm+12,16.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,20.0,0.00);
sprintf(cstring,"%+#10.2lE ~ %+#10.2lE",fspa[4],fspa[5]);
FontPuts(Font,cstring);	

glColor3f(rot[5],gruen[5],blau[5]);
glRectd(xm+4,16.0,xm+12,8.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,12.0,0.00);
sprintf(cstring,"%+#10.2lE ~ %+#10.2lE",fspa[5],fspa[6]);
FontPuts(Font,cstring);	

glColor3f(rot[6],gruen[6],blau[6]);
glRectd(xm+4,8.0,xm+12,0.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,4.0,0.00);
sprintf(cstring,"%+#10.2lE ~ %+#10.2lE",fspa[6],fspa[7]);
FontPuts(Font,cstring);	

glColor3f(rot[7],gruen[7],blau[7]);
glRectd(xm+4,0.0,xm+12,-8.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,-4.0,0.00);
sprintf(cstring,"%+#10.2lE ~ %+#10.2lE",fspa[7],fspa[8]);
FontPuts(Font,cstring);	

glColor3f(rot[8],gruen[8],blau[8]);
glRectd(xm+4,-8.0,xm+12,-16.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,-12.0,0.00);
sprintf(cstring,"%+#10.2lE ~ %+#10.2lE",fspa[8],fspa[9]);
FontPuts(Font,cstring);	

if(if3d == IDM_SHOWSPANN)
  {
  glColor3f(1.0f,0.5f,0.0f);
  glRasterPos3d(xm+4,-20.0,0.00);
  if(LANG == 1)strcpy(cstring,"V-Spannungen (GEH)");
  if(LANG == 2)strcpy(cstring,"v.Mises Stresses");
  FontPuts(Font,cstring);	
  glRasterPos3d(xm+4,-24.0,0.00);
  if(LANG == 1)strcpy(cstring,"in den Eckknoten");
  if(LANG == 2)strcpy(cstring,"in corner nodes");
  FontPuts(Font,cstring);	
  }

if(if3d == IDM_SHOWGAUSS)
  {
  glColor3f(1.0f,0.5f,0.0f);
  glRasterPos3d(xm+4,-20.0,0.00);
  if(LANG == 1)strcpy(cstring,"V-Spannungen (GEH)");
  if(LANG == 2)strcpy(cstring,"v.Mises Stresses");
  FontPuts(Font,cstring);
  glRasterPos3d(xm+4,-24.0,0.00);
  if(LANG == 1)strcpy(cstring,"pro Element gemittelt");
  if(LANG == 2)strcpy(cstring,"mean value per element");
  FontPuts(Font,cstring);		
  }

if(if3d == IDM_SHOWVX)
  {
  glColor3f(1.0f,0.5f,0.0f);
  glRasterPos3d(xm+4,-20.0,0.00);
  if(LANG == 1)strcpy(cstring,"X-Verschiebungen");
  if(LANG == 2)strcpy(cstring,"X Displacements");
  FontPuts(Font,cstring);	
  }

if(if3d == IDM_SHOWVY)
  {
  glColor3f(1.0f,0.5f,0.0f);
  glRasterPos3d(xm+4,-20.0,0.00);
  if(LANG == 1)strcpy(cstring,"Y-Verschiebungen");
  if(LANG == 2)strcpy(cstring,"Y Displacements");
  FontPuts(Font,cstring);	
  }

if(if3d == IDM_SHOWVZ)
  {
  glColor3f(1.0f,0.5f,0.0f);
  glRasterPos3d(xm+4,-20.0,0.00);
  if(LANG == 1)strcpy(cstring,"Z-Verschiebungen");
  if(LANG == 2)strcpy(cstring,"Z Displacements");
  FontPuts(Font,cstring);	
  }

return 0;
}

/***********************************************************************
* malk88 zeichnet die Knotennummern
***********************************************************************/
int malk88(void)
{
extern GLFONT      *Font;

extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;

extern FR_INT4     jkvon,jkbis,nkp,LANG;

extern GLfloat     node_col[];

FR_INT4            i,ipuf;

char               cstring[80];

/*----------------------------------------------------------------------
* und los
*---------------------------------------------------------------------*/
glColor3f(node_col[0],node_col[1],node_col[2]);

if(jkvon <=  0 || jkbis <=  0) return 0;

if(jkvon > nkp) jkvon= nkp;
if(jkbis > nkp) jkbis= nkp;

if(jkbis < jkvon)
  {
  ipuf=  jkbis;
  jkbis= jkvon;
  jkvon= ipuf;
  } 

for(i= jkvon; i <= jkbis;i++)
  { 
  glRasterPos3d(xv[i],yv[i],zv[i]);
  ltoa(i,cstring,10);
  FontPuts(Font,cstring);
  }	

return 0;
}

/***********************************************************************
* hier beginnt Function tet588: reines FE Netz
***********************************************************************/
int tet588(void)
{
extern GLFONT      *Font;

extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;

extern FR_DOUBLE   xe[];
extern FR_DOUBLE   ye[];
extern FR_DOUBLE   ze[];

extern FR_INT4AY   ityp;
extern FR_INT4AY   koi;
extern FR_INT4AY   koffs;

extern FR_INT4     ne,jevon,jebis;

extern GLfloat     elem_col[],hide_col[];

FR_DOUBLE          xla,yla,zla;

FR_INT4            i,j,k,iflag;

extern int         iflabe;

static FR_INT4     jp7[5]=  {0,1,2,3,4};

static FR_INT4     jp16[13]={0,1,3,2,1,2,4,1,4,3,2,3,4};

static FR_INT4     jp10[25]={0,1,2,3,4,5,6,7,8,
                               1,5,6,2,4,8,7,3,
                               1,5,8,4,2,6,7,3};

FR_INT4            ipuf;

char               cstring[80];

/***********************************************************************
* jevon und jebis checken
***********************************************************************/
if(jevon > ne) jevon= ne;
if(jebis > ne) jebis= ne;

if(jebis < jevon)
  {
  ipuf=  jebis;
  jebis= jevon;
  jevon= ipuf;
  } 

/***********************************************************************
* Schleife ueber alle Elemente
***********************************************************************/
for (i= 1; i <= ne; i++)
  {
  glColor3f(hide_col[0],hide_col[1],hide_col[2]);
  iflag= 0;
  if(iflabe == IDM_ELEMENTE)
    if(i >= jevon && i <= jebis) iflag= 1;

/*----------------------------------------------------------------------
* Stab 4 u. 9, Balken 2 und 13, Welle 5
*---------------------------------------------------------------------*/
  if(ityp[i] == 4 || ityp[i] == 9  || 
     ityp[i] == 2 || ityp[i] == 13 ||
     ityp[i] == 5)
    {       

/*======================================================================
* die zwei Eck-Punkte fuer jeden Stab holen
*=====================================================================*/
  for (j= 1; j <= 2; j++)
    {
    xe[j]= xv[koi[koffs[i]+j-1]];
    ye[j]= yv[koi[koffs[i]+j-1]];
    ze[j]= zv[koi[koffs[i]+j-1]];
    }

/*======================================================================
* ... und rendern
*=====================================================================*/
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xe[1]+xe[2])*0.5;
      yla= (ye[1]+ye[2])*0.5;
      zla= (ze[1]+ze[2])*0.5;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINES);
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[2],ye[2],ze[2]);
    glEnd();

    }  /* Stab 4 u. 9, Balken 2 und 13, Welle 5 */


/*----------------------------------------------------------------------
* Scheibe 7, Torus 8, Scheibe 11, Torus 12 und Platte 19 u. 20
*---------------------------------------------------------------------*/
  if(ityp[i] == 7  || ityp[i] == 8  || 
     ityp[i] == 11 || ityp[i] == 12 ||
     ityp[i] == 19 || ityp[i] == 20)
    {       

/*======================================================================
* die vier Eck-Punkte fuer jede Scheibe oder Platte holen
*=====================================================================*/
  if(ityp[i] != 19)
    {
    for (j= 1; j <= 4; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }
    }
  else
    {
    xe[1]= xv[koi[koffs[i]]];
    ye[1]= yv[koi[koffs[i]]];
    ze[1]= zv[koi[koffs[i]]];

    xe[2]= xv[koi[koffs[i]+12]];
    ye[2]= yv[koi[koffs[i]+12]];
    ze[2]= zv[koi[koffs[i]+12]];

    xe[3]= xv[koi[koffs[i]+15]];
    ye[3]= yv[koi[koffs[i]+15]];
    ze[3]= zv[koi[koffs[i]+15]];

    xe[4]= xv[koi[koffs[i]+3]];
    ye[4]= yv[koi[koffs[i]+3]];
    ze[4]= zv[koi[koffs[i]+3]];
    }

/*======================================================================
* ... und rendern
*=====================================================================*/
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xe[1]+xe[3])*0.5;
      yla= (ye[1]+ye[3])*0.5;
      zla= (ze[1]+ze[3])*0.5;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_QUADS);
      for(k= 1; k <= 4; k++)
        glVertex3d(xe[jp7[k]],ye[jp7[k]],ze[jp7[k]]);
    glEnd();

    }  /* Scheibe 7,11, Torus 8,12 und Platte 19 u. 20 */

/*----------------------------------------------------------------------
* Scheibe 3, Torus 6, Scheibe 14, Torus 15 und Platte 18
*---------------------------------------------------------------------*/
  if(ityp[i] == 3  || ityp[i] == 14 || 
     ityp[i] == 6  || ityp[i] == 15 ||
     ityp[i] == 18)
    {       

/*======================================================================
* die drei Eck-Punkte fuer jede Scheibe oder Platte holen
*=====================================================================*/
  for (j= 1; j <= 3; j++)
    {
    xe[j]= xv[koi[koffs[i]+j-1]];
    ye[j]= yv[koi[koffs[i]+j-1]];
    ze[j]= zv[koi[koffs[i]+j-1]];
    }

/*======================================================================
* ... und rendern
*=====================================================================*/
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xe[1]+xe[2]+xe[3])*0.333;
      yla= (ye[1]+ye[2]+ye[3])*0.333;
      zla= (ze[1]+ze[2]+ze[3])*0.333;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_TRIANGLES);
      for(k= 1; k <= 3; k++)
        glVertex3d(xe[jp7[k]],ye[jp7[k]],ze[jp7[k]]);
    glEnd();

    }  /* Scheibe 3,14, Torus 6,15 und Platte 18 */

/*----------------------------------------------------------------------
* Tetraeder 16 und 17
*---------------------------------------------------------------------*/
  if(ityp[i] == 16 || ityp[i] == 17)
    {       
       
/*======================================================================
* die vier Punkte fuer jeden Tetraeder holen
*=====================================================================*/
    for (j= 1; j <= 4; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xe[1]+xe[2]+xe[3]+xe[4])*0.25;
      yla= (ye[1]+ye[2]+ye[3]+ye[4])*0.25;
      zla= (ze[1]+ze[2]+ze[3]+ze[4])*0.25;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_TRIANGLES);
      for(k= 1; k <= 12; k++)
        glVertex3d(xe[jp16[k]],ye[jp16[k]],ze[jp16[k]]);
    glEnd();

    }  /* Ende Tetraeder 16 und 17 */

/*----------------------------------------------------------------------
* Hexaeder 1 und 10
*---------------------------------------------------------------------*/
  if(ityp[i] == 1 || ityp[i] == 10)
    {       
/*======================================================================
* die acht Punkte fuer jeden Hexaeder holen
*=====================================================================*/
    for (j= 1; j <= 8; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xe[1]+xe[7])*0.5;
      yla= (ye[1]+ye[7])*0.5;
      zla= (ze[1]+ze[7])*0.5;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_QUADS);
      for(k= 1; k <= 24; k++)
        glVertex3d(xe[jp10[k]],ye[jp10[k]],ze[jp10[k]]);
    glEnd();

    }  /* Ende Hexaeder 1 und 10 */

  }  /* Ende Schleife ueber alle Elemente */

return 0;
}

