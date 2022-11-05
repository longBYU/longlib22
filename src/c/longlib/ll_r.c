
/* *** LAST REVISED ON  7-JAN-1994 08:09:58.56 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.LONGLIB]LL_R.C */

#include <stdio.h>
#include <stdlib.h>

#include "my.h"

/* prototype functions */

char getch();

extern struct {
    integer ichan, imr[128];
    real rre[2], rox, roy, rsf;
    integer nimr;
    real rang;
    integer mm, ipw, ipsc, icol;
    real rvp[4];
    integer irid;
    real rlim[2];
    integer irxlim, irylim, iddev;
} rmtek_;        /*This structure is used by the ramxlib routines*/

#define rmtek_1 rmtek_

/* Table of constant values */

static integer c__2 = 2;


/* Subroutine */ int rterm_(ix)
integer *ix;
{
    /* Local variables */
    static integer ians, ierr;
    extern /* Subroutine */ int ramclose_();
    static char ans;
    extern /* Subroutine */ int rmclear_(), ramopen_();

/* 	C VERSION:   DGL DEC. 1993 */
/* 	CLEARS RAMTEK SCREEN -- SIMILAR TO CTERM */

/* IX	CONTROL FLAG */
/* 	= 0 CLEAR RAMTEK SCREEN */
/* 	= 2 ASK IF RAMTEK SCREEN CLEAR */
/* 	=-2 CLEAR RAMTEK SCREEN */
/* 	=-4 CLEAR RAMTEK SCREEN */
/* 	= 3 CLOSE RAMTEK CHANNEL */
/* 	=-3 REOPEN CLOSED RAMTEK CHANNEL */



    if (rmtek_1.ichan == -99 && *ix == 2) {
	goto L80;
    }
    if (rmtek_1.ichan == -99 && *ix == -3) {
	goto L80;
    }
    if (rmtek_1.ichan <= 0) {
	return 0;
    }
    if (abs(*ix) > 4) {
	return 0;
    }
    switch ((int)(*ix + 5)) {
	case 1:  goto L10;
	case 2:  goto L15;
	case 3:  goto L10;
	case 4:  goto L15;
	case 5:  goto L10;
	case 6:  goto L15;
	case 7:  goto L20;
	case 8:  goto L30;
	case 9:  goto L15;
    }
L10:		/* CLEAR RAMTEK SCREEN */
    rmclear_(&rmtek_1.ichan, &ierr);
L15:
    return 0;
L20:		/* ASK IF SCREEN CLEAR */
    printf("\nClear Ramtek Screen? (y/n) [y] ");
    ans = getch();
    ians = ans;
    if (ians >= 96) {
	ians += -32;
    }
    if (ians == 89 || ians == 32) {
	goto L10;
    } else {
	if (ians == 81) {
	    goto L30;
	}	/* TEMP. CLOSE CHANNEL */
	if (ians == 83) {
	    ramclose_(&rmtek_1.ichan);
	    rmtek_1.ichan = -99;	/* SKIP PLOT MODE */
	}
    }
    return 0;

L30:					/* TEMP. CLOSE CHANNEL */
    ramclose_(&rmtek_1.ichan);
    rmtek_1.ichan = -99;
    return 0;

L80:
    ramopen_(&rmtek_1.ichan, &rmtek_1.irid, &rmtek_1.iddev, &ierr);
    if (rmtek_1.ichan < 0) {
	printf("\n *** ERROR *** CAN NOT REOPEN RAMTEK CHANNEL \n");
    }
    return 0;
} /* rterm_ */


/* Subroutine */ int rambox_(ichan, ix1, iy1, ix2, iy2, jcol)
integer *ichan, *ix1, *iy1, *ix2, *iy2, *jcol;
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static integer ierr, mplot[4], iy;
    extern /* Subroutine */ int rmplot_();
    static integer iyy1, iyy2;


/* 	FILLS IN A BOX ON THE RAMTEK */
/* 	(IX1,IY1):	LOWER LEFT CORNER (IN PIXELS) */
/* 	(IX2,IY2):	UPPER RIGHT CORNER (IN PIXELS) */
/* 	JCOL:		COLOR INDEX */


    if (*ichan <= 0)
       goto L5;
    if (*ix2 < 1)
	goto L5;
    if (*ix1 > rmtek_1.irxlim)
	goto L5;
    if (*iy2 < 1)
	goto L5;
    if (*iy1 > rmtek_1.irylim)
	goto L5;

    mplot[0] = max(1,*ix1);
    mplot[2] = min(rmtek_1.irxlim,*ix2);
/* Computing MAX */
    i__1 = 1, i__2 = min(*iy1,*iy2);
    iyy1 = max(i__1,i__2);
/* Computing MIN */
    i__1 = rmtek_1.irylim, i__2 = max(*iy1,*iy2);
    iyy2 = min(i__1,i__2);

    i__1 = iyy2;
    for (iy = iyy1; iy <= i__1; ++iy) {
	mplot[1] = iy;
	mplot[3] = iy;
	rmplot_(&rmtek_1.ichan, &c__2, mplot, jcol, &ierr);
    }
L5:
    return 0;
} /* rambox_ */


/* Subroutine */ int rmwopt_0_(n__, iwind, ierr)
int n__;
integer *iwind, *ierr;
{
    switch(n__) {
	case 1: goto L_rmsave;
	}


L_rmsave:
    return 0;
} /* rmwopt_ */

/* Subroutine */ int rmwopt_(iwind, ierr)
integer *iwind, *ierr;
{
    return rmwopt_0_(0, iwind, ierr);
    }

/* Subroutine */ int rmsave_()
{
    return rmwopt_0_(1, (integer *)0, (integer *)0);
    }
