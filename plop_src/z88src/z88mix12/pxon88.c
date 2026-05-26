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
* a small utility for use with Z88
* pxon88 puts xon/xoff- command in plotfile z88o6.txt:
* not magnificent, but it works .. and that counts
* 23.3.2002 Rieg
***********************************************************************/
#include <stdio.h>

int main(void)
{
FILE *ftmp, *f6;
int c;

printf("Xon/Xoff- Command to Z88O6.TXT ...");

ftmp= fopen("z88o6.tmp","wb");
rewind(ftmp);
 
fputs("\x01B.I256;;17:;\x01B.N;19:;\x00D\x00A",ftmp);

f6= fopen("z88o6.txt","rb"); 
rewind(f6);

while( (c= fgetc(f6)) != EOF)   
  fputc(c,ftmp);
  
fclose(ftmp);
fclose(f6);

remove("z88o6.txt");
rename("z88o6.tmp","z88o6.txt");

printf("Done !\n");
return(0);
}
