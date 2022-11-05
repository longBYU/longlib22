
/* *** LAST REVISED ON 11-AUG-1994 04:54:03.19 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.LONGLIB]LL_RU.C */

#include "my.h"

# define EOF -1

/* function prototypes */

extern int rmplot_(int *x, int *y, int *p, int *pt, int *ier);
extern int rminfo_(int *ichtest, int *iopen, int *ix, int *iy, int *ncol, int *lcol, int *xw, int *yw, int *isize);


typedef struct {
    integer ichan, imr[128];
    real rre[2], rox, roy, rsf;
    integer nimr;
    real rang;
    integer mm, ipw, ipsc, icol;
    real rvp[4];
    integer irid;
    real rlim[2];
    integer irxlim, irylim, iddev;
} rmtek_common;        /*This structure is used by the ramxlib routines*/

extern rmtek_common rmtek_;

#define MAXCHAN 4
static rmtek_common keep[MAXCHAN];


int rmwopt_(int *wind, int *ierr)
/*Changes channel/window on Ramtek device from previously stored values

  Input:
    iwind   desired window number
  */
{
  int iwind = *wind;
  int ichtest = *wind;
  int ichan = 1, zero = 0;
  int p[2];
  int ier, pt;
  int iopen =1;
    
  rmplot_(&zero, &zero, p, &pt, &ier);
  if(iwind < 0 || iwind > MAXCHAN)  
     return -1; 
  
  if(iopen > 0)
     ichan = ichtest;
  if(ichan <= 0 || ichan > MAXCHAN)
     return -1;
  rmtek_ = keep[ichan-1];
  return ichan;
}


int rmsave_(void)
/*Save the current Ramtek context (part of the subroutine rmwopt_ in FORTRAN)*/
{
  int ich;
  int p[1];
  int ier, pt, zero = 0;
  int iopen, ix, iy, ncol, lcol, xw[2], yw[2], isize;
  
  rmplot_(&zero,&zero,p,&pt,&ier);
  ich = rmtek_.ichan;
  if(ich < 0)
     return 0;
  rminfo_(&ich, &iopen, &ix, &iy, &ncol, &lcol, xw, yw, &isize);

  if(ich < 0 || ich > MAXCHAN)
     return 0;
  keep[ich-1] = rmtek_;  
  return 0;
} 



