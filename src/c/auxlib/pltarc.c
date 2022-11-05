
/* *** LAST REVISED ON 24-DEC-1993 07:19:09.60 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]PLTARC.C */

#include "my.h"

/* Table of constant values */

static real c_b3 = (float)0.;
static integer c__2 = 2;
static integer c__3 = 3;


/* Subroutine */ int pltarc_(x1, y1, x2, y2, x3, y3)
real *x1, *y1, *x2, *y2, *x3, *y3;
{
    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    double sqrt();

    /* External functions */
    extern doublereal atan2d_();
    extern /* Subroutine */ int circle_();
    extern /* Subroutine */ int plot_();

    /* Local variables */
    static real d, r, a1, a3, x0, y0;
    static real xx, yy;

/* 	PLOTS AN ARC OF A CIRCLE WHICH PASSES THROUGH (X1,Y1) */
/* 	(X2,Y2) AND (X3,Y3) IN SEQUENCE.  IN THE DEGENERATE CASES */
/* 	WHERE POINTS ARE COINCIDENT OR COLINEAR, A STRAIGHT */
/* 	LINE FROM (X1,Y1) TO (X3,Y3) IS PLOTTED. */

/* 	INPUTS: */
/* 	  X1,Y1,X2,Y2,X3,Y3: (R) INPUT POINTS */

/* 	CHECK FOR COINCIDENT POINTS */
    if (*x1 == *x2 && *y1 == *y2) {
	goto L10;
    }
    if (*x1 == *x3 && *y1 == *y3) {
	goto L10;
    }
    if (*x2 == *x3 && *y2 == *y3) {
	goto L10;
    }

    d = (*x1 - *x2) * (*y1 - *y3) - (*x1 - *x3) * (*y1 - *y2);
    if (d == (float)0.) {
	goto L10;
    }
    xx = *x2 * *x2 - *x1 * *x1 + *y2 * *y2 - *y1 * *y1;
    yy = *x3 * *x3 - *x1 * *x1 + *y3 * *y3 - *y1 * *y1;
    x0 = ((*y3 - *y1) * xx + (*y1 - *y2) * yy) * (float).5 / d;
    y0 = ((*x1 - *x3) * xx + (*x2 - *x1) * yy) * (float).5 / d;
/* Computing 2nd power */
    r__1 = *x1 - x0;
/* Computing 2nd power */
    r__2 = *y1 - y0;
    r = sqrt(r__1 * r__1 + r__2 * r__2);
    r__1 = *y1 - y0;
    r__2 = *x1 - x0;
    a1 = atan2d_(&r__1, &r__2);
    r__1 = *y3 - y0;
    r__2 = *x3 - x0;
    a3 = atan2d_(&r__1, &r__2);
    circle_(&x0, &y0, &a1, &a3, &r, &r, &c_b3);
L5:
    return 0;
L10:
    plot_(x1, y1, &c__3);
    plot_(x3, y3, &c__2);
    goto L5;
} /* pltarc_ */

