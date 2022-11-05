
/* *** LAST REVISED ON 20-JAN-1994 07:30:53.78 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]NXTVU.C */

#include "my.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;

/* internal routines */

/* Subroutine */ int nxt0vu_(x, y, w, kk, ll, ier)
real *x, *y, *w;
integer *kk, *ll, *ier;
{
    /* Initialized data */

    static real eps = (float).001;		/* ZERO TEST VALUE */

    /* System generated locals */
    real r__1, r__2;

/* 	ROUTINE TO STORE NEW DATA IN SURFACE HISTORY ARRAY IN NXTVU */
/* 	8/11/87 BY D.LONG, JPL */

    /* Parameter adjustments */
    --w;

    /* Function Body */
    if (*kk == 0) {
	goto L10;
    }
    if (*kk << 1 >= *ll - 1) {
	goto L20;
    }
    if ((r__1 = w[(*kk - 1 << 1) + 1] - *x, dabs(r__1)) + (r__2 = w[*kk * 2] 
	    - *y, dabs(r__2)) < eps) {
	return 0;
    }
L10:
    ++(*kk);
    w[(*kk - 1 << 1) + 1] = *x;
    w[*kk * 2] = *y;
    return 0;
L20:
    *ier = 1;
    /* printf("nxt0vu error %d %d\n",2**kk,*ll-1); */
    return 0;
} /* nxt0vu_ */


real anxtvu_(x0, x1, y0, y1, x)
real *x0, *x1, *y0, *y1, *x;
{
    /* System generated locals */
    real ret_val;

/* 	COMPUTE THE EXTENSION OF A LINE FOR NXTVU */
/* 	MODIFIED 8/11/87 BY D.LONG, JPL */

    if (*x0 == *x1) {
	goto L10;
    }
    ret_val = (*x - *x0) * (*y1 - *y0) / (*x1 - *x0) + *y0;
    return ret_val;
L10:
    if (*y1 > *y0) {
	goto L20;
    }
    ret_val = *y0;
    return ret_val;
L20:
    ret_val = *y1;
    return ret_val;
} /* anxtvu_ */


/* main routine */

/* Subroutine */ int nxtvu_(ic, d, n, w, nn, ier)
integer *ic;
real *d;
integer *n;
real *w;
integer *nn, *ier;
{
    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;

    /* External functions */
    extern /* Subroutine */ int plot_();
    extern /* Subroutine */ int nxt0vu_();
    extern real anxtvu_();

    /* Local variables */
    static real frac;
    static integer i, j;
    static real x0, x1, di;
    static integer ii, jj, kk, ll;
    static real xi;
    static real xl, yl, yi, ya0, yb0, ya1, yb1;
    static integer isw, iov0, iov1;

/* 	ROUTINE TO PLOT VISIBLE LINES LINES FOR USE WITH PLT3D */
/* 	LINES BEHIND A PLANAR SURFACE STORED IN W ARE NOT PLOTTED */
/* 	MODIFIED 8/11/87 BY D.LONG, JPL */

/* 	IC	(I)	INTIALIZE/DIRECTION CODE */
/* 			 > 0 PLOT SURFACE ABOVE W */
/* 			 < 0 PLOT SURFACE BELOW W */
/* 			 = +1 FIRST CALL FOR ABOVE SURFACE */
/* 			 = +2 FOR SUBSEQUENT CALLS ABOVE SURFACE */
/* 			 = -1 FIRST CALL FOR BELOW SURFACE */
/* 			 NOTE THAT VISIBLE EDGE IS NOT PLOTTED */
/* 			 FOR BELOW PLOT OPTION */
/* 			 = -2 FOR SUBSEQUENT CALLS BELOW SURFACE */
/* 	D	(R)	INPUT POINT PAIRS */
/* 			 D(1) = X(1) */
/* 			 D(2) = Y(1) */
/* 			  ... */
/* 	N	(I)	NUMBER OF POINT PAIRS IN D ARRAY */
/* 	W	(R)	ARRAY STORING TOP (BOTOM) HIDDEN PLANE */
/* 			 (SHOULD NOT BE MODIFIED BETWEEN CALLS) */
/* 	NN	(I)	DIMENSION OF W */
/* 	IER	(I)	RETURNED ERROR FLAG */
/* 			 = 0, OK */
/* 		 	 = 1 OUT OF SPACE ERROR IN W */

/* 	DETERMINE DIRECTION AND INITIALIZE */

    /* Parameter adjustments */
    --w;
    --d;

    /* Function Body */
    di = (float)1.;
    if (*ic < 0) {
	di = (float)-1.;
    }
    if (abs(*ic) != 1 && *ic != 0) {
	goto L20;
    }

/* 	CHECK OVERFLOW BUFFER */

    if (*n > *nn / 2) {
	goto L500;
    }
    ll = *nn / 2 - *n + 1;
    i = ll;
    w[(i - 1 << 1) + 1] = d[(c__1 - 1 << 1) + 1];
    w[i * 2] = di * d[c__1 * 2];
    if (*ic > 0) {
	plot_(&d[(c__1 - 1 << 1) + 1], &d[c__1 * 2], &c__3);
    }
    i__1 = *n;
    for (j = 2; j <= i__1; ++j) {
	++i;
	w[(i - 1 << 1) + 1] = d[(j - 1 << 1) + 1];
	w[i * 2] = di * d[j * 2];
	if (*ic > 0) {
	    plot_(&d[(j - 1 << 1) + 1], &d[j * 2], &c__2);
	}
/* L10: */
    }
    *ier = 0;
    return 0;
L20:
    if (*ier != 0) {
	return 0;
    }
    ii = 1;
    jj = ll;
    kk = 0;
    ya0 = di * d[c__1 * 2];
    yb0 = w[ll * 2];
    if (d[(c__1 - 1 << 1) + 1] - w[(ll - 1 << 1) + 1] <= (float)0.) {
	goto L30;
    } else {
	goto L70;
    }
L30:
    r__1 = di * ya0;
    plot_(&d[(c__1 - 1 << 1) + 1], &r__1, &c__3);
L40:
    r__1 = di * d[ii * 2];
    nxt0vu_(&d[(ii - 1 << 1) + 1], &r__1, &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 40\n",*ier); */
    if (ii == *n) {
	goto L360;
    }
    ++ii;
    ya0 = di * d[ii * 2];
    if (d[(ii - 1 << 1) + 1] > w[(ll - 1 << 1) + 1]) {
	goto L50;
    }
    r__1 = di * ya0;
    plot_(&d[(ii - 1 << 1) + 1], &r__1, &c__2);
    goto L40;
L50:
    --ii;
    xl = d[(ii - 1 << 1) + 1];
    yl = di * d[ii * 2];
    i__1 = ii + 1;
    i__2 = ii + 1;
    r__1 = di * d[ii * 2];
    r__2 = di * d[i__2 * 2];
    ya0 = anxtvu_(&d[(ii - 1 << 1) + 1], &d[(i__1 - 1 << 1) + 1], &r__1, &
	    r__2, &w[(ll - 1 << 1) + 1]);
    x0 = w[(ll - 1 << 1) + 1];
    if (ya0 > yb0) {
	goto L90;
    }
    r__1 = di * ya0;
    plot_(&x0, &r__1, &c__2);
    nxt0vu_(&x0, &ya0, &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 70a\n",*ier); */
    nxt0vu_(&x0, &yb0, &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 70b\n",*ier); */
    goto L100;
L70:
    nxt0vu_(&w[(jj - 1 << 1) + 1], &w[jj * 2], &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 80\n",*ier); */
    if (jj == *nn / 2) {
	goto L380;
    }
    ++jj;
    yb0 = w[jj * 2];
    if (d[(c__1 - 1 << 1) + 1] - w[(jj - 1 << 1) + 1] >= (float)0.) {
	goto L70;
    } else {
	goto L80;
    }
L80:
    --jj;
    i__1 = jj + 1;
    i__2 = jj + 1;
    yb0 = anxtvu_(&w[(jj - 1 << 1) + 1], &w[(i__1 - 1 << 1) + 1], &w[jj * 2], 
	    &w[i__2 * 2], &d[(c__1 - 1 << 1) + 1]);
    x0 = d[(c__1 - 1 << 1) + 1];
    if (ya0 <= yb0) {
	goto L100;
    }
    nxt0vu_(&x0, &yb0, &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 90a\n",*ier); */
    nxt0vu_(&x0, &ya0, &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 90b\n",*ier); */
    xl = x0;
    yl = ya0;
L90:
    iov0 = 1;
    goto L120;
L100:
    iov0 = 0;
L120:
    if (ii == *n) {
	goto L300;
    }
    if (jj == *nn / 2) {
	goto L310;
    }
    i__1 = ii + 1;
    i__2 = jj + 1;
    if (d[(i__1 - 1 << 1) + 1] > w[(i__2 - 1 << 1) + 1]) {
	goto L130;
    }
    isw = 1;
    ++ii;
    x1 = d[(ii - 1 << 1) + 1];
    ya1 = di * d[ii * 2];
    i__1 = jj + 1;
    i__2 = jj + 1;
    yb1 = anxtvu_(&w[(jj - 1 << 1) + 1], &w[(i__1 - 1 << 1) + 1], &w[jj * 2], 
	    &w[i__2 * 2], &x1);
    goto L140;
L130:
    i__1 = jj + 1;
    if (w[(i__1 - 1 << 1) + 1] > d[(*n - 1 << 1) + 1]) {
	goto L340;
    }
    isw = -1;
    ++jj;
    x1 = w[(jj - 1 << 1) + 1];
    i__1 = ii + 1;
    i__2 = ii + 1;
    r__1 = di * d[ii * 2];
    r__2 = di * d[i__2 * 2];
    ya1 = anxtvu_(&d[(ii - 1 << 1) + 1], &d[(i__1 - 1 << 1) + 1], &r__1, &
	    r__2, &x1);
    yb1 = w[jj * 2];
L140:
    if (ya1 <= yb1) {
	goto L160;
    }
    iov1 = 1;
    if (iov0 == 0) {
	goto L170;
    }
L150:
    if (isw == -1) {
	goto L200;
    }
    nxt0vu_(&x1, &ya1, &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 160\n",*ier); */
    r__1 = di * yl;
    plot_(&xl, &r__1, &c__3);
    r__1 = di * ya1;
    plot_(&x1, &r__1, &c__2);
    xl = x1;
    yl = ya1;
    goto L200;
L160:
    iov1 = 0;
    if (iov0 == 0) {
	goto L190;
    }
L170:
    if (ya1 - yb1 + yb0 - ya0 == (float)0.) {
	frac = (float)1.;
    } else {
	frac = (yb0 - ya0) / (ya1 - yb1 + yb0 - ya0);
    }
    xi = (x1 - x0) * frac + x0;
    yi = (ya1 - ya0) * frac + ya0;
    nxt0vu_(&xi, &yi, &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 180\n",*ier); */
    if (iov0 == 0) {
	goto L180;
    }
    r__1 = di * yl;
    plot_(&xl, &r__1, &c__3);
    r__1 = di * yi;
    plot_(&xi, &r__1, &c__2);
    xl = xi;
    yl = yi;
    goto L190;
L180:
    xl = xi;
    yl = yi;
    goto L150;
L190:
    if (isw == 1) {
	goto L200;
    }
    nxt0vu_(&w[(jj - 1 << 1) + 1], &w[jj * 2], &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 200\n",*ier); */
L200:
    if (*ier != 0) {
	return 0;
    }
    x0 = x1;
    ya0 = ya1;
    yb0 = yb1;
    iov0 = iov1;
    goto L120;
L310:
    i__1 = *nn / 2;
    x1 = w[(i__1 - 1 << 1) + 1];
    i__1 = ii + 1;
    i__2 = ii + 1;
    r__1 = di * d[ii * 2];
    r__2 = di * d[i__2 * 2];
    ya1 = anxtvu_(&d[(ii - 1 << 1) + 1], &d[(i__1 - 1 << 1) + 1], &r__1, &
	    r__2, &x1);
    i__1 = *nn / 2;
    yb1 = w[i__1 * 2];
    if (ya1 > yb1) {
	goto L320;
    }
    nxt0vu_(&x1, &yb1, &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 380a\n",*ier); */
    nxt0vu_(&x1, &ya1, &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 380b\n",*ier); */
    r__1 = di * ya1;
    plot_(&x1, &r__1, &c__3);
    goto L330;
L380:
    ii = 1;
L320:
    plot_(&d[(ii - 1 << 1) + 1], &d[ii * 2], &c__3);
L330:
    if (ii == *n) {
	goto L400;
    }
    ++ii;
    r__1 = di * d[ii * 2];
    nxt0vu_(&d[(ii - 1 << 1) + 1], &r__1, &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 300b\n",*ier); */
    plot_(&d[(ii - 1 << 1) + 1], &d[ii * 2], &c__2);
    goto L330;
L300:
    if (jj == *nn / 2) {
	goto L400;
    }
L340:
    x1 = d[(*n - 1 << 1) + 1];
    ya1 = di * d[*n * 2];
    i__1 = jj + 1;
    i__2 = jj + 1;
    yb1 = anxtvu_(&w[(jj - 1 << 1) + 1], &w[(i__1 - 1 << 1) + 1], &w[jj * 2], 
	    &w[i__2 * 2], &x1);
    if (ya1 <= yb1) {
	goto L350;
    }
    nxt0vu_(&x1, &ya1, &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 360a\n",*ier); */
    nxt0vu_(&x1, &yb1, &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 360b\n",*ier); */
    r__1 = di * ya1;
    plot_(&x1, &r__1, &c__2);
L350:
    if (jj == *nn / 2) {
	goto L400;
    }
    ++jj;
    nxt0vu_(&w[(jj - 1 << 1) + 1], &w[jj * 2], &w[1], &kk, &ll, ier);
/*    if (*ier !=0 ) printf("nxt0vu_ error %d 360\n",*ier); */
    goto L350;
L360:
    jj = 0;
    goto L350;
L400:
    ll = *nn / 2 - kk + 1;
    i = ll;
    i__1 = kk;
    for (j = 1; j <= i__1; ++j) {
	w[(i - 1 << 1) + 1] = w[(j - 1 << 1) + 1];
	w[i * 2] = w[j * 2];
	++i;
/* L410: */
    }
    return 0;
L500:
    *ier = 1;
    return 0;
} /* nxtvu_ */
