
/* *** LAST REVISED ON 20-JAN-1994 08:12:42.31 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]HLT3D.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    real a1, a2, a3, b1, b2, b3, b4;
} plt3b_;

#define plt3b_1 plt3b_

/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__4 = 4;
static integer c__5 = 5;

/* Subroutine */ int hlt3d_(a, md, nd, m, n, w1, l, w2, nn, alt, az, xlen, 
	xoff, ylen, yoff, zfac, zoff, ier)
real *a;
integer *md, *nd, *m, *n;
real *w1;
integer *l;
real *w2;
integer *nn;
real *alt, *az, *xlen, *xoff, *ylen, *yoff, *zfac, *zoff;
integer *ier;
{
    /* Initialized data */

    static real dtr = (float).0174532925;

    /* System generated locals */
    integer a_dim1, a_offset;
    real r__1, r__2;

    /* Builtin functions */
    double sin(), cos();

    /* External functions */
    extern /* Subroutine */ int nxtvu_();

    /* Local variables */
    static integer ibeg, jbeg;
    static real talt, d[12];
    static integer i, j, ilast, jlast, istep, jstep;
    static integer ic, id, ll;
    static real xx, zv, yy;
    static integer ifirst, jfirst;
    static real cal, caz, sal;
    static integer iaz;
    static real saz, taz, xsc, ysc;

/* 	ROUTINE TO PLOT COLUMNS IN 3D WITH HIDDEN LINE REMOVAL USING NXTVU */
/* 	WRITTEN 8/17/87 BY D.LONG, JPL */

/* 	A	(R): MD BY ND ARRAY CONTAINING Z VALUES TO BE PLOTTED */
/* 	MD,ND	(I): DIMENSIONS OF A */
/* 	M,N	(I): SIZE OF DATA IN A ARRAY  M,N > 1 */
/* 	W1	(R): WORKING ARRAY OF DIMENSIONED W1(L) */
/* 		      (NOT USED--INCLUDED FOR COMPATIBILITY WITH PLT3D) */
/* 	L	(I): DIMENSION OF W1 ARRAY */
/* 	W2	(R): WORKING ARRAY OF DIMENSIONED W2(NN) */
/* 	NN	(I): DIMENSION OF W2 ARRAY */
/* 	ALT,AZ	(R): VIEWING ALTITUDE, AZIMUTH IN DEGREES */
/* 	XLEN	(R): LENGTH OF UNPROJECTED X AXIS IN INCHES */
/* 			> 0 SURFACE ABOVE PLANE SHOWN */
/* 			< 0 SURFACE BELOW PLANE SHOWN */
/* 	XOFF	(R): ORIGIN OF PLOT */
/* 	YLEN	(R): LENGTH OF UNPROJECTED Y AXIS IN INCHES */
/* 	YOFF	(R): ORIGIN OF PLOT */
/* 	ZFAC	(R): Z COORDINATE SCALE FACTOR (Zplotted=ZFAC*A(I,J)+ZOFF) */
/* 	ZOFF	(R): Z AXIS OFFSET VALUE */
/* 	IER	(I): RETURNED ERROR CODE */
/* 			0: NO ERROR */
/* 			1: WORKING STORAGE W2 INTERNAL SPACE EXCEEDED */
/* 			2: L LESS THAN 2*MIN(M,N) */

    /* Parameter adjustments */
    --w2;
    a_dim1 = *md;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */

    taz = *az * dtr;
    talt = *alt * dtr;
    saz = sin(taz);
    caz = cos(taz);
    sal = sin(talt);
    cal = cos(talt);
    xsc = dabs(*xlen) / (real) (*n - 1);
    id = 1;
    if (*xlen < (float)0.)
	id = -1;
    ysc = *ylen / (real) (*m - 1);
    plt3b_1.a1 = caz * xsc;
    plt3b_1.a2 = -(doublereal)saz * ysc;
    plt3b_1.a3 = *xoff - (plt3b_1.a1 * (real) (*n + 1) + plt3b_1.a2 * (real) (
	    *m + 1)) * (float).5;
    plt3b_1.b1 = saz * sal * xsc;
    plt3b_1.b2 = caz * sal * ysc;
    plt3b_1.b3 = *zfac * cal;
    plt3b_1.b4 = plt3b_1.b3 * *zoff + *yoff - (plt3b_1.b1 * (real) (*n + 1) + 
	    plt3b_1.b2 * (real) (*m + 1)) * (float).5;
    iaz = 1;
    if (plt3b_1.a1 <= (float)0.)
	++iaz;
    if (plt3b_1.a2 <= (float)0.)
	iaz += 2;
    switch ((int)iaz) {
	case 1:  goto L10;
	case 2:  goto L20;
	case 3:  goto L10;
	case 4:  goto L20;
    }
L10:
    ifirst = 1;
    istep = 1;
    ilast = *m;
    goto L30;
L20:
    ifirst = *m;
    istep = -1;
    ilast = 1;
L30:
    switch ((int)iaz) {
	case 1:  goto L50;
	case 2:  goto L50;
	case 3:  goto L40;
	case 4:  goto L40;
    }
L40:
    jfirst = 1;
    jstep = 1;
    jlast = *n;
    goto L60;
L50:
    jfirst = *n;
    jstep = -1;
    jlast = 1;
L60:
    ic = id;

/* 	PLOT ZOFF PLANE LINE */

    ll = 3;
    xx = (real) jfirst;
    yy = (real) (ilast + istep) + (float).001;
    d[(c__1 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__1 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * *
	    zoff + plt3b_1.b4;
    xx = (real) jfirst;
    yy = (real) ifirst;
    d[(c__2 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__2 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * *
	    zoff + plt3b_1.b4;
    xx = (real) (jlast + jstep) + (float).001;
    yy = (real) ifirst;
    d[(c__3 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__3 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * *
	    zoff + plt3b_1.b4;
    nxtvu_(&ic, d, &ll, &w2[1], nn, ier);
    if (*ier != 0)
	return 0;
    ic = id << 1;

    ibeg = ifirst;
    jbeg = jfirst;
L70:

/* 	BOTTOM FRONT EDGE */

    i = ibeg + istep;
    j = jbeg;
L490:
    ll = 1;
    xx = (real) j;
    yy = (real) i;
    d[(c__1 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__1 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * *
	    zoff + plt3b_1.b4;
    i -= istep;
    ++ll;
    yy = (real) i;
    d[(c__2 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__2 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * *
	    zoff + plt3b_1.b4;
    if (j == jlast)
	goto L400;
    j += jstep;
    ++ll;
    xx = (real) j;
    d[(c__3 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__3 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * *
	    zoff + plt3b_1.b4;
L400:
    nxtvu_(&ic, d, &ll, &w2[1], nn, ier);
    if (*ier != 0)
	return 0;
    if (i == ifirst || j - jstep == jlast)
	goto L480;
    goto L490;

/* 	PLOT FRONT CENTER LINES */

L480:
    i = ibeg;
    j = jbeg;
L75:
    xx = (real) j;
    yy = (real) i;
    zv = *zoff;
    if (i != ifirst && j != jfirst) {
	r__1 = a[i - istep + (j - jstep) * a_dim1], r__2 = a[i - istep + j * 
		a_dim1];
	zv = dmin(r__1,r__2);
	r__1 = zv, r__2 = a[i + (j - jstep) * a_dim1];
	zv = dmin(r__1,r__2) + *zoff;
    }
    d[(c__1 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__1 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * zv 
	    + plt3b_1.b4;
    d[(c__2 - 1) * 2] = d[(c__1 - 1) * 2];
    d[(c__2 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * (a[
	    i + j * a_dim1] + *zoff) + plt3b_1.b4;
    nxtvu_(&ic, d, &c__2, &w2[1], nn, ier);
    if (*ier != 0)
	return 0;
    ic = id << 1;
    if (i == ifirst || j == jlast)
	goto L80;
    i -= istep;
    j += jstep;
    goto L75;

/* 	FRONT SIDES */

L80:
    i = ibeg + istep;
    j = jbeg;
L175:
    ll = 2;
    xx = (real) j;
    yy = (real) i;
    d[(c__1 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__1 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * *
	    zoff + plt3b_1.b4;
    d[(c__2 - 1) * 2] = d[(c__1 - 1) * 2];
    d[(c__2 << 1) - 1] = d[(c__1 << 1) - 1] + plt3b_1.b3 * a[i - istep + j * 
	    a_dim1];
    if (i == ifirst)
	goto L275;
    i -= istep;
    ++ll;
    yy = (real) i;
    d[(c__3 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__3 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * (a[
	    i + j * a_dim1] + *zoff) + plt3b_1.b4;
    j += jstep;
    ll += 2;
    xx = (real) j;
    d[(c__4 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__4 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * (a[
	    i + (j - jstep) * a_dim1] + *zoff) + plt3b_1.b4;
    d[(c__5 - 1) * 2] = d[(c__4 - 1) * 2];
    d[(c__5 << 1) - 1] = d[(c__4 << 1) - 1] - plt3b_1.b3 * a[i + (j - jstep) *
	     a_dim1];
L275:
    nxtvu_(&ic, d, &ll, &w2[1], nn, ier);
    if (*ier != 0)
	return 0;
    if (i == ifirst || j - jstep == jlast)
	goto L260;
    goto L175;

/* 	BACK TOP */

L260:
    i = ibeg + istep;
    j = jbeg;
L290:
    ll = 1;
    xx = (real) j;
    yy = (real) i;
    d[(c__1 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__1 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * (a[
	    i - istep + j * a_dim1] + *zoff) + plt3b_1.b4;
    j += jstep;
    ++ll;
    xx = (real) j;
    d[(c__2 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__2 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * (a[
	    i - istep + (j - jstep) * a_dim1] + *zoff) + plt3b_1.b4;
    if (i == ifirst)
	goto L300;
    i -= istep;
    ++ll;
    yy = (real) i;
    d[(c__3 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__3 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * (a[
	    i + (j - jstep) * a_dim1] + *zoff) + plt3b_1.b4;
L300:
    nxtvu_(&ic, d, &ll, &w2[1], nn, ier);
    if (*ier != 0)
	return 0;
    if (i == ifirst || j - jstep == jlast)
	goto L560;
    goto L290;

/* 	BACK BOTTOM */

L560:
    i = ibeg + istep;
    j = jbeg;
L590:
    if (a[i - istep + j * a_dim1] < *zoff) {

/* 	FOR COLUMNS BELOW OFFSET PLANE, SHOW BACK CORNER */

	ll = 2;
	xx = (real) (j + jstep);
	yy = (real) i;
	d[(c__1 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
	d[(c__1 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * 
		(a[i - istep + j * a_dim1] + *zoff) + plt3b_1.b4;
	d[(c__2 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
	d[(c__2 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * 
		*zoff + plt3b_1.b4;
	nxtvu_(&ic, d, &ll, &w2[1], nn, ier);
	if (*ier != 0)
	    return 0;
    }
    ll = 1;
    xx = (real) j;
    yy = (real) i;
    d[(c__1 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__1 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * *
	    zoff + plt3b_1.b4;
    j += jstep;
    ++ll;
    xx = (real) j;
    d[(c__2 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__2 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * *
	    zoff + plt3b_1.b4;
    if (i == ifirst)
	goto L550;
    i -= istep;
    ++ll;
    yy = (real) i;
    d[(c__3 - 1) * 2] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[(c__3 << 1) - 1] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * *
	    zoff + plt3b_1.b4;
L550:
    nxtvu_(&ic, d, &ll, &w2[1], nn, ier);
    if (*ier != 0)
	return 0;
    if (i == ifirst || j - jstep == jlast)
	goto L380;
    goto L590;

/* 	FINISHED ONE LAYER */

L380:
    if (ibeg != ilast) {
	ibeg += istep;
	goto L70;
    }
    jbeg += jstep;
    if (jbeg == jlast)
	return 0;
    goto L70;
} /* hlt3d_ */

