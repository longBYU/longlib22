
/* *** LAST REVISED ON 21-JAN-1994 13:48:08.64 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]SCALE.C */

#include "my.h"
#include <math.h>

/* Table of constant values */

static real c_b4 = (float)10.;

/* Subroutine */ int scale_(x, s, n, k, ix, xmin, dx)
real *x, *s;
integer *n, *k, *ix;
real *xmin, *dx;
{
    /* Initialized data */

    static real q[6] = { (float)1.,(float)2.,(float)4.,(float)5.,(float)8.,(
	    float)10. };

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double r_lg10();

    /* Local variables */
    static real xmax;
    static integer i;
    static real sj;
    static integer np;
    static real si, xi;
    static integer idx;
    static real xmm;

/* 	CREATES SMOOTHED LINEAR SCALE FACTORS FROM INPUT DATA */

/* 	X	(R) ARRAY OF DATA TO BE SCANNED FOR MAXIMUM AND MINIMUM */
/* 		    VALUES. */
/* 	S	(R) LENGTH OVER WHICH THIS DATA IS TO BE PLOTTED. */
/* 	N	(I) NUMBER OF DATA POINTS IN THE ARRAY X. */
/* 	K	(I) REPEAT CYCLE OF MIXED ARRAY(NORMALLY 1). */
/* 	IX	(I) FIRST RELEVANT DATA POINT IN X */
/* 	XMIN	(R) SMOOTHED MINIMUM AFTER CALL */
/* 	DX	(R) SMOOTHED INCREMENT AFTER CALL */

/* 	TO USE SMOOTHED VALUES: XPLOTTED=(XVALUE-XM)/DX */

    /* Parameter adjustments */
    --x;

    /* Function Body */
    np = *n * *k;
    xmax = x[1];
    *xmin = xmax;
    i__1 = np;
    i__2 = *k;
    for (i = *ix; i__2 < 0 ? i >= i__1 : i <= i__1; i += i__2) {
	xi = x[i];
	xmax = dmax(xmax,xi);
	*xmin = dmin(*xmin,xi);
/* L100: */
    }
    xmm = *xmin;
    if (*s <= (float)0.) {
	goto L160;
    }
    *dx = (xmax - *xmin) / *s;
    if (*dx <= (float)0.) {
	goto L160;
    }
    sj = (float)0.;
    if (*dx < (float)1.) {
	sj = (float)-1.;
    }
    idx = r_lg10(dx) + sj;
    *dx /= pow( (double) c_b4, (double) idx);
    for (i = 1; i <= 6; ++i) {
	xi = q[i - 1];
	if (xi >= *dx) {
	    goto L120;
	}
/* L110: */
    }
L120:
    *dx = xi * pow( (double) c_b4, (double) idx);
    si = (float)1.;
    sj = (float)0.;
    if (*xmin < (float)0.) {
	goto L130;
    } else if (*xmin == 0) {
	goto L170;
    } else {
	goto L140;
    }
L130:
    si = (float)-1.;
    sj = (float)-.99999;
    *xmin = -(doublereal)(*xmin);
L140:
    idx = r_lg10(xmin) + sj;
    *xmin /= pow( (double) c_b4, (double) idx);
    *xmin -= sj;
    *xmin = (integer) (*xmin) * si * pow( (double) c_b4, (double) idx);
    goto L170;
L160:
    *dx = (float)1.;
    *xmin += (float)-.5;
L170:

/* 	BEFORE EXIT, CHECK TO BE SURE THAT DATA IS CONTAINED WITHIN */
/* 	THE LIMITS XMIN AND XMIN+DX*S.  IF NOT, RESET DX */

    if (xmm < *xmin) {
	*xmin = xmm;
    }
    if (xmax > *xmin + *dx * *s) {
	if (*s > (float)0.) {
	    *dx = (xmax - *xmin) / *s;
	}
	if (*dx <= (float)0.) {
	    *dx = (float)1.;
	}
    }
    return 0;
} /* scale_ */

