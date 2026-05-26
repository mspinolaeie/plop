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
* V11.0  December 12, 2003
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
* TOB88G.C
* 25.3.2004 Rieg
***********************************************************************/
#include <windows.h>
#include <commctrl.h>

#include <z88g.h>


TBBUTTON tbb[] = 
     {
     0, ITC_GO,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
     0, 0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, 0,
     0, 0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, 0,
     1, ITC_NAST, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP, 0, 0, 0, 0,
     2, ITC_COSM, TBSTATE_ENABLED | TBSTATE_CHECKED, 
                                   TBSTYLE_CHECKGROUP, 0, 0, 0, 0,
     0, 0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, 0,
     0, 0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, 0,
     3, ITC_VOLU, TBSTATE_ENABLED | TBSTATE_CHECKED,
                                   TBSTYLE_CHECKGROUP, 0, 0, 0, 0,
     4, ITC_SHEI, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP, 0, 0, 0, 0,
     5, ITC_PLAT, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP, 0, 0, 0, 0,
     6, ITC_TORU, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP, 0, 0, 0, 0,
     0, 0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, 0,
     0, 0,        TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, 0,
     7, ITC_HELP, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
     } ;

/*----------------------------------------------------------------------
* Function InitToolBar
*---------------------------------------------------------------------*/
HWND InitToolBar (HWND hParent)
{
extern HINSTANCE hInstance;

HWND hToolBar= CreateToolbarEx (
               hParent,
               WS_CHILD | WS_VISIBLE       | WS_CLIPSIBLINGS |
               CCS_TOP  | TBSTYLE_TOOLTIPS | WS_BORDER | WS_EX_CLIENTEDGE,
               1,                    /* wID */
               8,                    /* nBitmaps */
               hInstance,            /* zu ladende Bitmap */
               BMP_Z88G  ,           /* zu ladende Bitmap */
               tbb,                  /* Pointer auf TBBUTTON Array */ 
               14,                    /* Anzahl Buttons */
               32,                   /* dxButton */
               32,                   /* dyButton */
               32,                   /* dxBitmap */ 
               32,                   /* dyBitmap */
               sizeof (TBBUTTON)) ;

      
return hToolBar ;
}

