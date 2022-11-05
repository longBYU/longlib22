
/* *** LAST REVISED ON 24-DEC-1993 07:00:06.24 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]CSHADE.C */

#include "my.h"

/* Subroutine */ int cshade_(am, bm, rad, a1, a2, res, l, d, t, w, ma1, ma2)
real *am, *bm, *rad, *a1, *a2, *res;
integer *l;
real *d, *t, *w;
integer *ma1, *ma2;
{
    /* Initialized data */

    static integer kp[2] = { 2,3 };
    static real dtr = (float).0174532;

    /* System generated locals */
    integer i__1;
    real r__1;

    /* Builtin functions */
    double atan(), r_int(), sin(), cos();

    /* External functions */
    extern /* Subroutine */ int newpen_();
    extern /* Subroutine */ int plot_();

    /* Local variables */
    static integer n, i0, i1, i2, i3;
    static real w1, w2, x1;
    static integer kc;
    static real ct, dt;
    static integer ip;
    static real th, yc, anginc;
    static integer lt;
    static real yl, st, ys, xt, yt;
    static real tx0, ty0, ty1, yt0, yt1, xt0, xt1, ang;

/* 	SHADES A CIRCULAR SEGMENT OR FULL CIRLE */
/* 	WRITTEN AUG 1987 BY D. LONG */

/* AM,BM(R) CENTER OF CIRCLE */
/* RAD  (R) RADIUS OF CIRCLE SEGMENT */
/* RES  (R) ALONG ARC RESOLUTION */
/* A1,A2(R) START,END ANGLES FOR SEGMENT.  IF A2-A1 >= 360, FULL CIRCLE USED*/
/* 	    A2 => A1 */
/* L    (I) SHADE FORMAT CONTROL */
/* 		-3 CLEAR AREA AND OUTLINE */
/* 		-2 CLEAR AREA */
/* 		-1 CLEAR OUTLINE */
/* 		 0 NO ACTION */
/* 		+1 DRAW OUTLINE */
/* 		+2 SHADE AREA */
/* 		+3 SHADE AREA AND OUTLINE */
/* D    (D) DISTANCE BETWEEN SHADING LINES */
/* T    (D) ANGLE OF SHADING LINES */
/* W    (D) WORKING ARRAY DIMENSIONED AT LEAST */
/* 		3*INT((A2-A1)/(180*ATAN(RES/RAD)/PI))+9 */
/* MA1   (I) LINE TYPE OF SHADING (IF MA1 => 0) */
/* MA2   (I) LINE TYPE OF OUTLINE (IF MA2 => 0) */

    /* Parameter adjustments */
    w -= 4;

    /* Function Body */

    if (*rad <= (float)0.) {
	goto L110;
    }
    lt = abs(*l);
    kp[0] = 2;
    if (*l < 0) {
	kp[0] = 9;
    }
    anginc = (float)60.;
    if (*res > (float)0.) {
	anginc = atan(*res / *rad) / dtr;
    }
    if (lt <= 1) {
	goto L90;
    }
    dt = *d;
    if (dt <= (float)0.) {
	dt = (float).005;
    }
    r__1 = *t / (float)360.;
    th = *t - r_int(&r__1) * (float)360.;
    if (th < (float)0.) {
	th += (float)360.;
    }
    th *= dtr;
    st = sin(th);
    ct = cos(th);

/* 	FILL WORKING ARRAY AND COMPUTE MAX/MIN */

    i1 = 1;
    ang = *a1;
L10:
    tx0 = *rad * cos(ang * dtr) + *am;
    ty0 = *rad * sin(ang * dtr) + *bm;
    w[i1 * 3 + 1] = tx0 * ct + ty0 * st;
    r__1 = -(doublereal)tx0;
    ty1 = ty0 * ct + r__1 * st;
    w[i1 * 3 + 2] = ty1;
    if (i1 == 1) {
	ys = ty1;
	yl = ty1;
    }
    ys = dmin(ys,ty1);
    yl = dmax(yl,ty1);
    ++i1;
    if (ang == *a2) {
	goto L20;
    }
    ang += anginc;
    if (ang > *a2) {
	ang = *a2;
    }
    goto L10;
L20:

/* 	ADD SEGMENT LINES IF REQUIRED */

    if (*a2 - *a1 < (float)360.) {
	tx0 = *am;
	ty0 = *bm;
	w[i1 * 3 + 1] = tx0 * ct + ty0 * st;
	r__1 = -(doublereal)tx0;
	ty1 = ty0 * ct + r__1 * st;
	w[i1 * 3 + 2] = ty1;
	ys = dmin(ys,ty1);
	yl = dmax(yl,ty1);
	++i1;
	tx0 = *rad * cos(*a1 * dtr) + *am;
	ty0 = *rad * sin(*a1 * dtr) + *bm;
	w[i1 * 3 + 1] = tx0 * ct + ty0 * st;
	r__1 = -(doublereal)tx0;
	ty1 = ty0 * ct + r__1 * st;
	w[i1 * 3 + 2] = ty1;
	ys = dmin(ys,ty1);
	yl = dmax(yl,ty1);
	++i1;
    }

/* 	SHADE AREA */

    n = i1 - 1;
    yc = ys + dt * (float).5;
    if (*ma1 >= 0) {
	newpen_(ma1);
    }
L30:
    if (yc > yl) {
	goto L90;
    }
    i1 = 0;
    i__1 = n;
    for (i0 = 1; i0 <= i__1; ++i0) {
	i2 = i0 + 1;
	if (i2 > n) {
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

/* 	PLOT AREA OUTLINE */

    if (*ma2 >= 0) {
	newpen_(ma2);
    }
    ang = *a1;
    ip = kp[1];
L100:
    tx0 = *rad * cos(ang * dtr) + *am;
    ty0 = *rad * sin(ang * dtr) + *bm;
    plot_(&tx0, &ty0, &ip);
    ip = kp[0];
    if (ang == *a2) {
	goto L105;
    }
    ang += anginc;
    if (ang > *a2) {
	ang = *a2;
    }
    goto L100;
L105:

/* 	ADD SEGMENT LINES IF REQUIRED */

    if (*a2 - *a1 < (float)360.) {
	plot_(am, bm, &ip);
	tx0 = *rad * cos(*a1 * dtr) + *am;
	ty0 = *rad * sin(*a1 * dtr) + *bm;
	plot_(&tx0, &ty0, &ip);
    }

/* 	ALL DONE */

L110:
    return 0;
} /* cshade_ */
