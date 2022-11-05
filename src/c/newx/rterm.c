
/* *** LAST REVISED ON 11-AUG-1994 05:01:39.70 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.DECW]RTERM.C */

/*  rterm Routines for the Longlib graphics library */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define abs(x) ((x) >= 0 ? (x) : -(x))
#define min(a,b) ((a) <= (b) ? (a) : (b))
#define max(a,b) ((a) >= (b) ? (a) : (b))

/* function prototypes */
char getch();

extern int ramclose_(int *ichan);
extern int ramopen_(int *ichan, int *irid, int *iddev, int *ierr);
extern int rminfo_(int *ichan, int *iopen, int *ix, int *iy, int *ncol, int *lcol, int *xw, int *yw, int *isize);
extern int rmpause_(int *ichan, int *iwait);
extern int rmclear_(int *ichan, int *ierr);


extern struct {
  int ichan, imr[128];
  float rre[2], rox, roy, rsf;
  int nimr;
  float rang;
  int mm, ipw, ipsc, icol;
  float rvp[4];
  int irid;
  float rlim[2];
  int irxlim, irylim, iddev;
} rmtek_;

#define rmtek_1 rmtek_

int rterm_(int *x)
/*Clears Ramtek screen
  Input
  ix   Control flag
   0	clear Ramtek screen
   2	ask if Ramtek screen clear
  -2	clear Ramtek screen
  -4	clear Ramtek screen
   3	close Ramtek screen
  -3	reopen closed Ramtek screen  */
 
{
  char c;
  int ichan = rmtek_1.ichan, ix = *x;
  int iopen, ierr, ixx, iy, ncol, lcol, xw[2], yw[2], isize;
  int iwait = 0;

  if(ichan > 0)
     rmpause_(&ichan, &iwait);
  else
     return 0;
  if(abs(ix) > 4)
     return 0;
  if(ichan == -99 && (ix == 2 || ix == -3))  {
     ramopen_(&ichan, &rmtek_1.irid, &rmtek_1.iddev, &ierr);
     rminfo_(&ichan, &iopen, &ixx, &iy, &ncol, &lcol, xw, yw, &isize);
     if(ichan <= 0)
        printf("*** XLonglib ERROR:  Can not reopen Ramtek channel");
  }
  else {
     switch(ix)  {
       case 0:
       case -2:
       case -4:
         rmclear_(&ichan, &ierr);
         break;
       case 1:
       case -1:
       case 4:
       case -3:
         return 0;
       case 3:
         ramclose_(&ichan);
         ichan = -99;
         return 0; 
       case 2:
	 rmpause_(&ichan, &iwait);
         printf("Clear Ramtek Screen? (y/n) [y]");
	 rmpause_(&ichan, &iwait);
         c = getch();
         c = toupper(c);  /*convert to upper case*/
         if(c == 'Y' || c == ' ' || c == 13) /*13 = carriage return*/
            rmclear_(&ichan, &ierr);
         else if(c == 'Q')  { /*temporarily close channel*/
            ramclose_(&ichan);
            rmtek_1.ichan = -99;
            return 0;
            }
         else if(c == 'S') { /*disable plotting*/
            ramclose_(&ichan);
            rmtek_1.ichan = -99;
            }
       }
     }
     
     return 0;
}
