
/* *** LAST REVISED ON 24-DEC-1993 07:13:31.96 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]LINE2.C */

#include "my.h"

/* Table of constant values */
static real c_b4 = (float)0.;
static real c_b3 = (float).14;
static integer c_n1 = -1;
static integer c__3 = 3;


/* Subroutine */ int line2_(x, y, n, k, j, l, ix, iy, xmin, dx, ymin, dy, ddx)

real *x, *y;
integer *n, *k, *j, *l, *ix, *iy;
real *xmin, *dx, *ymin, *dy, *ddx;
{
    /* System generated locals */
    real r__1;
    char ch__1[1];

    /* External functions */
    extern /* Subroutine */ int plot_(real *, real *, integer *);
    extern /* Subroutine */ int symbol_(real *, real *, real *, char *, real *
	    , integer *, integer *);

    /* Local variables */
    static logical together;
    static integer i2, i3, i4, i5;
    static real xlast, x1, y1;
    static integer ja, la, nc;

/* 	THIS VERSION, WHEN CONNECTING POINTS PUTS GAPS WHEN */
/* 	DISTANCE BETWEEN X VALUES EXCEEDS DDX */

/* 	X	(R) ARRAY OF UNSCALED ABCISSA VALUES */
/* 	Y	(R) ARRAY OF UNSCALED ORDINATE VALUES */
/* 	N	(I) NUMBER OF POINTS IN THE ARRAY */
/* 	K	(I) REPEAT CYCLE OF A MIXED ARRAY (NORMALLY =1) */
/* 	J	(I) >0, SYMBOL AND LINE SYMBOL EVERY JTH POINT */
/* 		    =0, LINE ONLY */
/* 		    <0, SYMBOL ONLY SYMBOL EVERY JTH POINT */
/* 	L	(I) NUMBER OF SYMBOL ,SEE SYMBOL ROUTINE FOR LIST */
/* 	IX,IY	(I) FIRST REVALENT VALUE IN X,Y ARRAY */
/* 	XMIN,YMIN (R) MINIMUM VALUES IN ARRAY (DETERMINED BY SCALE) */
/* 	DX,DY	(R) SCALED SMOOTHED INCREMENTS (DETERMINED BY SCALE) */
/* 		    IF DX=0.0, THE PLOTTED X IS ZERO */
/* 		    IF DY=0.0, THE PLOTTED Y IS ZERO */
/* 	DDX	(R) CONTINUITY IN POINTS ONLY IF SEPARATION IN X VALUES */
/* 			IS LESS THAN DDX */

/* 	XPLOTTED=(X(I)-XMIN)/DX */
/* 	YPLOTTED=(Y(I)-YMIN)/DY */

    /* Parameter adjustments */
    --y;
    --x;

    /* Function Body */
    if (*n < 1) {
	return 0;
    }
    ja = abs(*j);
    nc = -1;
    if (*j > 0) {
	nc = -2;
    }
    la = *l;
    if (la < 0 || la > 117) {
	la = 100;
    }
    i2 = 1;
    i3 = 3;
    if (*j >= 0) {
	i3 = 2;
    }
    i4 = 3;
    i5 = *n;
    xlast = x[1];
L100:
    if (*dx != (float)0.) {
	x1 = (x[i2] - *xmin) / *dx;
	if ((r__1 = x[i2] - xlast, dabs(r__1)) > *ddx && *ddx > (float)0.) {
	    together = FALSE_;
	} else {
	    together = TRUE_;
	}
	xlast = x[i2];
    } else {
	x1 = (float)0.;
    }
    if (*dy != (float)0.) {
	y1 = (y[i2] - *ymin) / *dy;
    } else {
	y1 = (float)0.;
    }
    if (together) {
	plot_(&x1, &y1, &i4);
    }
    i4 = i3;
    if (*j != 0) {
	if ((i2 - 1) % ja == 0) {
	    ch__1[0] = la;
	    symbol_(&x1, &y1, &c_b3, ch__1, &c_b4, &nc, &c_n1);
	}
    } else {
	if (together) {
	    plot_(&x1, &y1, &i4);
	} else {
	    r__1 = y1 - (float).005;
	    plot_(&x1, &r__1, &c__3);
	    plot_(&x1, &y1, &i4);
	}
    }
    i2 += *k;
    --i5;
    if (i5 > 0) {
	goto L100;
    }
    return 0;
} /* line2_ */

