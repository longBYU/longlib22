
/* *** LAST REVISED ON 25-DEC-1993 22:25:16.82 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]SCALG.C */

#include "my.h"

/* Subroutine */ int scalg_(x, s, n, k, ix, xmin, dx)
real *x, *s;
integer *n, *k, *ix;
real *xmin, *dx;
{
    /* System generated locals */
    integer i__1, i__2;
    real r__1;

    /* Builtin functions */
    double r_lg10(), r_nint();

    /* Local variables */
    static real xmax;
    static integer i;
    static real sj;
    static integer np;
    static real xi, sj2;


/* 	COMPUTES SCALE FACTORS FOR INPUT DATA USING LOG SCALING */
/* 	MODIFIED FROM SCALE D.LONG 4-AUG-83	AT JPL */

/* 	X	ARRAY OF DATA TO BE SCANNED FOR MAXIMUM AND MINIMUM */
/* 		VALUES. */
/* 	S	LENGTH OVER WHICH THIS DATA IS TO BE PLOTTED. */
/* 	N	NUMBER OF DATA POINTS IN THE ARRAY X. */
/* 	K	REPEAT CYCLE OF MIXED ARRAY(NORMALLY 1). */
/* 	IX	FIRST RELEVANT DATA POINT IN X */
/* 	XMIN	SMOOTHED MINIMUM AFTER CALL */
/* 	DX	SMOOTHED INCREMENT AFTER CALL */

/* 	NOTE: IF X(I)=0.0 THEN 1.E-38 IS USED INSTEAD. */
/* 	      ABSOLUTE VALUE OF X ARRAY IS USED. */

    /* Parameter adjustments */
    --x;

    /* Function Body */
    np = *n * *k;
    xi = dabs(x[1]);
    if (xi == (float)0.) {
	xi = (float)1e-38;
    }
    xmax = r_lg10(&xi);
    *xmin = xmax;
    i__1 = np;
    i__2 = *k;
    for (i = 1; i__2 < 0 ? i >= i__1 : i <= i__1; i += i__2) {
	xi = (r__1 = x[i], dabs(r__1));
	if (xi == (float)0.) {
	    xi = (float)1e-38;
	}
	xi = r_lg10(&xi);
	xmax = dmax(xmax,xi);
	*xmin = dmin(*xmin,xi);
/* L100: */
    }
    sj = (int) (*xmin);
    if (*xmin < sj) {
	sj += (float)-1.;
    }
    r__1 = xmax + (float).5;
    sj2 = r_nint(&r__1);
    *dx = (sj2 - sj) / *s;
    *xmin = sj;
    return 0;
} /* scalg_ */

