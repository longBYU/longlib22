
/* *** LAST REVISED ON  7-JAN-1994 17:13:41.80 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]SHADE.C */

#include "my.h"

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int shade_(a, b, n, i, l, d, t, w, ma, am, da, bm, db)
real *a, *b;
integer *n, *i, *l;
real *d, *t, *w;
integer *ma;
real *am, *da, *bm, *db;
{
    /* Initialized data */

    integer ku = 3;
    integer kd = 2;
    integer kp[2] = {2,3};

    /* System generated locals */
    integer i__1;
    real r__1, r__2;

    /* Builtin functions */
    double sin(), cos();

    /* External functions */
    extern /* Subroutine */ int newpen_();
    extern /* Subroutine */ int plot_();

    /* Local variables */
    static integer i0, i1, i2, i3;
    static real w1, w2, x1, ai, bi;
    static real ao, bo;
    static integer kc;
    static real ct, dt;
    static real th, yc;
    static integer lt;
    static real yl, st, ys, xt, yt;
    static real tx0, ty0, ty1, yt0, yt1, xt0, xt1;

/* 	SHADES AN AREA DEFINED BY THE A AND B ARRAYS */

/* A    (R) ARRAY CONTAINING ABSCISSA VALUES */
/* B    (R) ARRAY CONTAINING ORDINATE VALUES */
/* N    (I) NUMBER OF POINTS IN ARRAY */
/* I    (I)INCREMENT BETWEEN POINTS IN ARRAY */
/* L    (I) SHADE FORMAT CONTROL */
/* 		-3 CLEAR AREA AND OUTLINE */
/* 		-2 CLEAR AREA */
/* 		-1 CLEAR OUTLINE */
/* 		 0 NO ACTION */
/* 		+1 SHADE OUTLINE */
/* 		+2 SHADE AREA */
/* 		+3 SHADE AREA AND OUTLINE */
/* D    (D) DISTANCE BETWEEN SHADING LINES */
/* T    (D) ANGLE OF SHADING LINES */
/* W    (D) WORKING ARRAY DIMENSIONED AT LEAST (3*N) */
/* MA   (I) TYPE OF SHADING (LINE TYPE) IF MA > 0 */
/* AM   (R) MINIMUM VALUE FOR A ARRAY */
/* DA   (R) SCALE FACTOR FOR A ARRAY */
/* BM   (R) MINIMUM VALUE FOR B ARRAY */
/* DB   (R) SCALE FACTOR FOR B ARRAY */

/* 	EQUIVALENCES ARE FOR CONVENIENCE ONLY */

    /* Parameter adjustments */
    w -= 4;
    --b;
    --a;

    /* Function Body */

    if (*n <= 2) {
	goto L110;
    }
    if (*i <= 0) {
	goto L110;
    }
    ao = *am;
    ai = *da;
    bo = *bm;
    bi = *db;
    if (ai <= (float)0.) {
	ai = (float)1.;
    }
    if (bi <= (float)0.) {
	bi = (float)1.;
    }
    lt = abs(*l);
    kd = 2;
    if (*l < 0) {
	kd = 9;
	kp[1] = 9;
    }
    if (lt <= 1) {
	goto L90;
    }
    dt = *d;
    if (dt <= (float)0.) {
	dt = (float).005;
    }
    r__1 = *t / (float)360.;
    th = *t - (int) (r__1) * (float)360.;
    if (th < (float)0.) {
	th += (float)360.;
    }
    th *= (float).0174532;
    st = sin(th);
    ct = cos(th);
    r__1 = (b[1] - bo) / bi;
    r__2 = -(doublereal)((a[1] - ao) / ai);
    ys = r__1 * ct + r__2 * st;
    yl = ys;
    i1 = 1;
    i__1 = *n;
    for (i0 = 1; i0 <= i__1; ++i0) {
	tx0 = (a[i1] - ao) / ai;
	ty0 = (b[i1] - bo) / bi;
	w[i0 * 3 + 1] = tx0 * ct + ty0 * st;
	r__1 = -(doublereal)tx0;
	ty1 = ty0 * ct + r__1 * st;
	w[i0 * 3 + 2] = ty1;
	ys = dmin(ys,ty1);
	yl = dmax(yl,ty1);
	i1 += *i;
/* L20: */
    }
    yc = ys + dt * (float).5;
    if ((real) (*ma) >= 0) {
	newpen_(ma);
    }
L30:
    if (yc > yl) {
	goto L90;
    }
    i1 = 0;
    i__1 = *n;
    for (i0 = 1; i0 <= i__1; ++i0) {
	i2 = i0 + 1;
	if (i2 > *n) {
	    i2 = 1;
	}
	yt0 = w[i0 * 3 + 2];
	yt1 = w[i2 * 3 + 2];
	w1 = dmin(yt0,yt1);
	if (yc < w1) {
	    goto L60;
	}
	w2 = dmax(yt0,yt1);
	if (yc >= w2) {
	    goto L60;
	}
	xt0 = w[i0 * 3 + 1];
	xt1 = w[i2 * 3 + 1];
	x1 = xt0 - (yt0 - yc) * (xt1 - xt0) / (yt1 - yt0);
	++i1;
	i2 = i1;
L40:
	if (i2 == 1) {
	    goto L50;
	}
	i3 = i2 - 1;
	if (w[i3 * 3 + 3] >= x1) {
	    goto L50;
	}
	w[i2 * 3 + 3] = w[i3 * 3 + 3];
	i2 = i3;
	goto L40;
L50:
	w[i2 * 3 + 3] = x1;
L60:
	;
    }
    if (i1 <= 0) {
	goto L80;
    }
    i2 = 1;
    i__1 = i1;
    for (i0 = 1; i0 <= i__1; ++i0) {
	xt0 = w[i0 * 3 + 3];
	r__1 = -(doublereal)yc;
	xt = xt0 * ct + r__1 * st;
	yt = yc * ct + xt0 * st;
	i2 = 3 - i2;
	kc = kp[i2 - 1];
	plot_(&xt, &yt, &kc);
/* L70: */
    }
L80:
    yc += dt;
    goto L30;
L90:
    if (lt / 2 << 1 == lt) {
	goto L110;
    }
    r__1 = (a[1] - ao) / ai;
    r__2 = (b[1] - bo) / bi;
    plot_(&r__1, &r__2, &ku);
    i1 = 1;
    i__1 = *n;
    for (i0 = 2; i0 <= i__1; ++i0) {
	i1 += *i;
	r__1 = (a[i1] - ao) / ai;
	r__2 = (b[i1] - bo) / bi;
	plot_(&r__1, &r__2, &kd);
/* L100: */
    }
    r__1 = (a[1] - ao) / ai;
    r__2 = (b[1] - bo) / bi;
    plot_(&r__1, &r__2, &kd);

/* 	RESET PEN TYPE */

L110:
    if ((real) (*ma) > 0) {
	newpen_(&c__1);
    }
    return 0;
} /* shade_ */

