
/* *** LAST REVISED ON 24-DEC-1993 07:16:50.38 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]PLRAX.C */

#include "my.h"

/* Table of constant values */
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c__3 = 3;
static real c_b4 = (float)0.;
static real c_b5 = (float).01;

/* Subroutine */ int plrax_(x0, y0, r0, astar, aend, al0, al1)
real *x0, *y0, *r0, *astar, *aend, *al0, *al1;
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double cos(), sin();

    /* External functions */
    extern /* Subroutine */ int plot_();
    extern /* Subroutine */ int circle_();
    extern /* Subroutine */ int number_();

    /* Local variables */
    static integer i, j;
    static real t;
    static integer n1;
    static real r1, x1, y1, x2, y2, ac, ad;
    static integer nd;
    static real cs, rd, ct, xd, yd;
    static real rt, st;
    static real rt1, rt2, tpi;

/* 	CREATED D. LONG 8-AUG-83	AT JPL */
/* 	PLOTS A POLAR COORDINATE SYSTEM AXIS */
/* 	X0,Y0	(R) X,Y  COORDINATE VALUES FOR CIRCULAR AXIS CENTER */
/* 	R0	(R) RADIUS OF AXIS */
/* 	ASTAR	(R) STARTING ANGLE OF AXIS, IN DEGREES FROM HORIZONTAL */
/* 	AEND	(R) ENDING ANGLE OF AXIS IN DEGREES FROM HORIZONTAL */
/* 			0.,360. YIELDS FULL CIRCLE PLOT */
/* 	AL0	(R) STARTING ANGLE LABEL NUMERIC VALUE */
/* 	AL1	(R) ENDING ANGLE LABEL NUMERIC VALUE */
/* 	NOTE:	IF AL0=AL1 THEN NO LABEL NUMBERS ARE PLOTTED */

    tpi = (float).017453292522222223;
    cs = (float).15;
    xd = cs * (float)2.51;
    yd = cs / (float)2.;
    n1 = *r0 + (float).5;
    if (n1 < 1) {
	return 0;
    }
    rt = (real) n1 + (float).1;
    rd = *aend - *astar;
    nd = rd / (float)90. + (float).49;
    if (*astar == *aend) {
	return 0;
    }
    t = *astar * tpi;
    x1 = cos(t) * rt;
    y1 = sin(t) * rt;
    plot_(x0, y0, &c__3);
    plot_(&x1, &y1, &c__2);
    x2 = x1 + cos(t) * xd - xd + (float).05;
    y2 = y1 + sin(t) * (yd + (float).15) - yd;
    if (*al0 != *al1) {
	number_(&x2, &y2, &cs, al0, &c_b4, &c_b5, &c_n1);
    }
    ac = (*al1 - *al0) / (*aend - *astar);
    if (nd * (float)90. > *aend) {
	goto L150;
    }
    i__1 = nd;
    for (i = 1; i <= i__1; ++i) {
	t = (*astar + (real) (i - 1) * (float)90. + (float)45.) * tpi;
	ct = cos(t);
	st = sin(t);
	i__2 = n1;
	for (j = 1; j <= i__2; ++j) {
	    rt1 = j - (float).1;
	    rt2 = j + (float).1;
	    x1 = ct * rt1;
	    y1 = st * rt1;
	    plot_(&x1, &y1, &c__3);
	    x1 = ct * rt2;
	    y1 = st * rt2;
	    plot_(&x1, &y1, &c__2);
	}
	if (*astar + (float)360. == *aend && i == nd) {
	    goto L175;
	}
	t = (*astar + (real) i * (float)90.) * tpi;
	ct = cos(t);
	st = sin(t);
	x1 = ct * rt;
	y1 = st * rt;
	plot_(&x1, &y1, &c__3);
	plot_(x0, y0, &c__2);
	x2 = x1 + ct * xd - xd + (float).05;
	y2 = y1 + st * (yd + (float).15) - yd;
	ad = ac * (real) i * (float)90. + *al0;
	if (*al1 != *al0) {
	    number_(&x2, &y2, &cs, &ad, &c_b4, &c_b5, &c_n1);
	}
    }
L150:
    if (*astar + (real) nd * (float)90. != *aend) {
	t = *aend * tpi;
	ct = cos(t);
	st = sin(t);
	x1 = ct * rt;
	y1 = st * rt;
	plot_(&x1, &y1, &c__3);
	plot_(x0, y0, &c__2);
	x2 = x1 + ct * xd - xd + (float).05;
	y2 = y1 + st * (yd + (float).15) - yd;
	ad = ac * (real) i * (float)90. + *al0;
	if (*al1 != *al0) {
	    number_(&x2, &y2, &cs, &ad, &c_b4, &c_b5, &c_n1);
	}
    }
L175:
    i__1 = n1;
    for (i = 1; i <= i__1; ++i) {
	r1 = (real) i;
	circle_(x0, y0, astar, aend, &r1, &r1, &c_b4);
    }
    return 0;
} /* plrax_ */

