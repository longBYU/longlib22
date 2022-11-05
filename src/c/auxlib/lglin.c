
/* *** LAST REVISED ON 24-DEC-1993 07:11:15.05 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]LGLIN.C */

#include "my.h"

/* Table of constant values */

static real c_b6 = (float).14;
static real c_b7 = (float)0.;
static integer c_n1 = -1;

/* Subroutine */ int lglin_(x, y, n, k, j, l, lg, ix, iy, xmin, dx, ymin, dy)
real *x, *y;
integer *n, *k, *j, *l, *lg, *ix, *iy;
real *xmin, *dx, *ymin, *dy;
{
    /* System generated locals */
    real r__1;
    char ch__1[1];

    /* Builtin functions */
    double r_lg10();

    /* External functions */
    extern /* Subroutine */ int plot_(real *, real *, integer *);
    extern /* Subroutine */ int symbol_(real *, real *, real *, char *, real *
	    , integer *, integer *);

    /* Local variables */
    static integer i2, i3, i4, i5;
    static real x1, y1;
    static integer la;
    static real xi, yi;

/* 	PLOTS A LOGRITHMIC LINE */
/* 	D.LONG 8-AUG-1983	AT JPL */

/* 	X	(R) ARRAY OF ABCISSA VALUES */
/* 	Y	(R) ARRAY OF ORDINATE VALUES */
/* 	N	(I) NUMBER OF POINTS IN THE ARRAY */
/* 	K	(I) REPEAT CYCLE OF A MIXED ARRAY (NORMALLY =1) */
/* 	J	(I) >0, SYMBOL AND LINE.  SYMBOLS PLOTTED EVERY JTH POINT */
/* 		    =0, LINE ONLY */
/* 		    <0, SYMBOL ONLY. SYMBOLS PLOTTED EVERY JTH POINT */
/* 	L	(I) NUMBER OF SYMBOL */
/* 	LG	(I) = -2 : X AND Y ARE LOGARITHMIC */
/* 		    = -1 : X IS LOGARITHMIC, Y IS LINEAR */
/* 		    =  1 : X IS LINEAR, Y IS LOGARITHMIC */
/* 	IX,IY	(I) FIRST REVALENT VALUE IN X,Y ARRAY */
/* 	XMIN,YMIN (R) MINIMUM VALUES IN ARRAY (DETERMINED BY SCALG) */
/* 	DX,DY	(R) SCALED (SMOOTHED) INCREMENT (DETERMINED BY SCALG) */

/* 	NOTE: IF LOG OF ZERO IS GOING TO OCCUR 1.E-38 IS SUBSTITUTED. */
/* 	      ABSOLUTE VALUE OF X,Y ARRAYS ARE USED WHEN LOG IS COMPUTED. */

    /* Parameter adjustments */
    --y;
    --x;

    /* Function Body */
    if (*n < 1) {
	goto L110;
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
L100:
    xi = x[i2];
    yi = y[i2];
    if (*lg == 1) {
	goto L101;
    }
    if (xi == (float)0.) {
	xi = (float)1e-38;
    }
    r__1 = dabs(xi);
    xi = r_lg10(&r__1);
L101:
    if (*lg == -1) {
	goto L102;
    }
    if (yi == (float)0.) {
	yi = (float)1e-38;
    }
    r__1 = dabs(yi);
    yi = r_lg10(&r__1);
L102:
    if (*dx != (float)0.) {
	x1 = (xi - *xmin) / *dx;
    } else {
	x1 = (float)0.;
    }
    if (*dy != (float)0.) {
	y1 = (yi - *ymin) / *dy;
    } else {
	y1 = (float)0.;
    }
    plot_(&x1, &y1, &i4);
    i4 = i3;
    if (*j != 0) {
	if ((i2 - *ix) % (*j * *k) == 0) {
	    ch__1[0] = la;
	    symbol_(&x1, &y1, &c_b6, ch__1, &c_b7, &c_n1, &c_n1);
	}
    }
    i2 += *k;
    --i5;
    if (i5 > 0) {
	goto L100;
    }
L110:
    return 0;
} /* lglin_ */

