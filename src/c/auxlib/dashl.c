
/* *** LAST REVISED ON 21-JAN-1994 13:47:51.89 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]DASHL.C */

#include "my.h"
#include <math.h>

/* Table of constant values */
static real c_b5 = (float)0.;
static real c_b4 = (float).14;
static doublereal c_b9 = .5;
static integer c_n1 = -1;
static integer c__3 = 3;

/* Subroutine */ int dashl_(x, y, n, k, j, l, ix, iy, xmin, dx, ymin, dy)
real *x, *y;
integer *n, *k, *j, *l, *ix, *iy;
real *xmin, *dx, *ymin, *dy;
{
    /* Initialized data */

    static real dl = (float).3;
    static real sl = (float).15;

    /* System generated locals */
    real r__1, r__2;
    doublereal d__1;
    char ch__1[1];

    /* Builtin functions */
    double atan2(), cos(), sin();

    /* External functions */
    extern /* Subroutine */ int plot_(real *, real *, integer *);
    extern /* Subroutine */ int symbol_(real *, real *, real *, char *, real *
	    , integer *, integer *);

    /* Local variables */
    static real a, d, d0;
    static integer i2, i3, i4, i5;
    static real x0, y0, x1, y1, dc, dd;
    static integer la;
    static integer i2y;
    static logical pen;

/* 	MODIFIED FROM LINE D.LONG 24-MAY-1983 AT JPL */

/* 	X	(R) ARRAY OF UNSCALED ABCISSA VALUES */
/* 	Y	(R) ARRAY OF UNSCALED ORDINATE VALUES */
/* 	N	(I) NUMBER OF POINTS IN THE ARRAY */
/* 	K	(I) REPEAT CYCLE OF A MIXED ARRAY (NORMALLY =1) */
/* 	J	(I) >0, SYMBOL AND LINE SYMBOL PLOTTED EVERY JTH POINT */
/* 		    =0, LINE ONLY */
/* 		    <0, SYMBOL ONLY SYMBOL PLOTTED EVERY JTH POINT */
/* 	L	(I) NUMBER OF SYMBOL ,SEE SYMBOL ROUTINE FOR LIST */
/* 	IX,IY	(I) FIRST REVALENT VALUE IN X,Y ARRAY */
/* 	XMIN,YMIN (R) MINIMUM VALUES IN ARRAY (DETERMINED BY SCALE) */
/* 	DX,DY	(R) SCALED (SMOOTHED) INCREMENT (DETERMINED BY SCALE) */

    /* Parameter adjustments */
    --y;
    --x;

    /* Function Body */
/* DASH AND SPACE LENGTH */
    if (*n < 1) {
	goto L110;
    }
    la = *l;
    if (la < 0 || la > 117) {
	la = (float)100.;
    }
    i2 = *ix;
    i2y = *iy;
    i3 = 3;
    if (*j >= 0) {
	i3 = 2;
    }
    if (*dx != (float)0.) {
	x0 = (x[i2] - *xmin) / *dx;
    } else {
	x0 = (float)0.;
    }
    if (*dy != (float)0.) {
	y0 = (y[i2y] - *ymin) / *dy;
    } else {
	y0 = (float)0.;
    }
    plot_(&x0, &y0, &c__3);
    i4 = i3;
    i5 = *n - 1;
    d = (float)0.;
    pen = TRUE_;
    if (*j != 0) {
	if ((i2 - 1) % *j == 0) {
	    ch__1[0] = la;
	    symbol_(&x0, &y0, &c_b4, ch__1, &c_b5, &c_n1, &c_n1);
	}
    }
    if (i5 <= 0) {
	goto L110;
    }
L100:
    if (*dx != (float)0.) {
	x1 = (x[i2] - *xmin) / *dx;
    } else {
	x1 = (float)0.;
    }
    if (*dy != (float)0.) {
	y1 = (y[i2y] - *ymin) / *dy;
    } else {
	y1 = (float)0.;
    }
/* Computing 2nd power */
    r__1 = x1 - x0;
/* Computing 2nd power */
    r__2 = y1 - y0;
    d__1 = (doublereal) (r__1 * r__1 + r__2 * r__2);
    d0 = pow( (double) d__1, (double) c_b9);
    i4 = 3;
    dc = sl;
    if (pen) {
	dc = dl;
    }
    if (d + d0 < dc) {
	if (pen) {
	    i4 = i3;
	}
	plot_(&x1, &y1, &i4);
	if (*j != 0) {
	    if ((i2 - 1) % *j == 0) {
		ch__1[0] = la;
		symbol_(&x1, &y1, &c_b4, ch__1, &c_b5, &c_n1, &c_n1);
	    }
	}
	d = d0 + d;
	x0 = x1;
	y0 = y1;
	goto L105;
    }
    dd = dc - d;
    d = (float)0.;
    a = atan2(y1 - y0, x1 - x0);
    x0 += dd * cos(a);
    y0 += dd * sin(a);
    if (pen) {
	i4 = i3;
    }
    plot_(&x0, &y0, &i4);
    pen = ! pen;
    goto L100;
L105:
    i2 += *k;
    i2y += *k;
    --i5;
    if (i5 > 0) {
	goto L100;
    }
L110:
    return 0;
} /* dashl_ */

