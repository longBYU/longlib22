
/* *** LAST REVISED ON 24-DEC-1993 07:17:40.32 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]PLRLN.C */

#include "my.h"

/* Table of constant values */

static real c_b4 = (float).14;
static real c_b5 = (float)0.;
static integer c_n1 = -1;


/* Subroutine */ int plrln_(r, t, n, j, l, ir, rmin, dr)
real *r, *t;
integer *n, *j, *l, *ir;
real *rmin, *dr;
{
    /* System generated locals */
    char ch__1[1];

    /* Builtin functions */
    double cos(), sin();

    /* External functions */
    extern /* Subroutine */ int plot_();
    extern /* Subroutine */ int symbol_();

    /* Local variables */
    static integer k, i2, i3, i4, i5;
    static real r1, t1, x1, y1;
    static integer la, ix;
    static real tpi;

/* 	DRAWS A CONNECTED AND/OR SYMBOLED LINE WHEN POINTS ARE SPECIFIED */
/* 	IN POLAR COORDINATES. */

/* 	R	(R) ARRAY OF UNSCALED RADIUS VALUES */
/* 	T	(R) ARRAY OF UNSCALED ANGLE VALUES IN DEGREES */
/* 	N	(I) NUMBER OF POINTS IN THE ARRAY */
/* 	J	(I) >0, SYMBOL AND LINE.  SYMBOLS PLOTTED EVERY JTH POINT */
/* 		    =0, LINE ONLY */
/* 		    <0, SYMBOL ONLY. SYMBOLS PLOTTED EVERY JTH POINT */
/* 	L	(I) NUMBER OF SYMBOL ,SEE SYMBOL ROUTINE FOR LIST */
/* 	IR	(I) FIRST REVALENT VALUE IN ARRAYS */
/* 	RMIN	(R) MINIMUM VALUES IN R ARRAY (DETERMINED BY SCALE) */
/* 	DR	(R) SCALED (SMOOTHED) INCREMENT (DETERMINED BY SCALE) */
/* 		    IF DR=0.0, THEN PLOTTED R IS ZERO */

    /* Parameter adjustments */
    --t;
    --r;

    /* Function Body */
    k = 1;
    tpi = (float).017453292522222223;
    if (*n < 1) {
	goto L110;
    }
    la = *l;
    if (la < 0 || la > 117) {
	la = 100;
    }
    i2 = *ir;
    i3 = 3;
    if (*j >= 0) {
	i3 = 2;
    }
    i4 = 3;
    i5 = *n - *ir + 1;
L100:
    if (*dr != (float)0.) {
	r1 = (r[i2] - *rmin) / *dr;
    } else {
	r1 = (float)0.;
    }
    t1 = t[i2] * tpi;
    x1 = r1 * cos(t1);
    y1 = r1 * sin(t1);
    plot_(&x1, &y1, &i4);
    i4 = i3;
    if (*j != 0) {
	if ((i2 - ix) % (*j * k) == 0) {
	    ch__1[0] = la;
	    symbol_(&x1, &y1, &c_b4, ch__1, &c_b5, &c_n1, &c_n1);
	}
    }
    i2 += k;
    i5 -= k;
    if (i5 > 0) {
	goto L100;
    }
L110:
    return 0;
} /* plrln_ */

