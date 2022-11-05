
/* *** LAST REVISED ON 20-JAN-1994 07:29:20.82 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]PLT3D.C */

#include "my.h"

/* Common Block Declarations */

struct {
    real a1, a2, a3, b1, b2, b3, b4;
} plt3b_;

#define plt3b_1 plt3b_

/* Subroutine */ int plt3d_(a, md, nd, m, n, d, l, w2, nn, alt, az, xlen, 
	xoff, ylen, yoff, zfac, zoff, ier)
real *a;
integer *md, *nd, *m, *n;
real *d;
integer *l;
real *w2;
integer *nn;
real *alt, *az, *xlen, *xoff, *ylen, *yoff, *zfac, *zoff;
integer *ier;
{
    /* Initialized data */

    static real dtr = (float).0174532925;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Builtin functions */
    double sin(), cos();

    /* External functions */
    extern /* Subroutine */ int nxtvu_();

    /* Local variables */
    static integer ibeg, jbeg, lmax;
    static real talt;
    static integer lnth, i, j, ilast, jlast, istep, jstep;
    static integer ic, id, ll;
    static real xx, yy;
    static integer ifirst, jfirst;
    static real cal, caz, sal;
    static integer lli, iaz;
    static real saz, taz, xsc, ysc;

/* 	ROUTINE TO PLOT A GRID SCRIBED ON A 3D SURFACE USING NXTVU */
/* 	TO PROVIDE HIDDEN LINE REMOVAL */
/* 	MODIFIED 8/11/87 BY D.LONG, JPL */

/* 	A	(R): MD BY ND ARRAY CONTAINING Z VALUES TO BE PLOTTED */
/* 	MD,ND	(I): DIMENSIONS OF A */
/* 	M,N	(I): SIZE OF DATA IN A ARRAY  M,N > 1 */
/* 	D	(R): WORKING ARRAY OF DIMENSIONED D(L) */
/* 	L	(I): DIMENSION OF D ARRAY */
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
    --d;
    a_dim1 = *md;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */
    lmax = min(*m,*n) << 1;
    if (*l < lmax << 1) {
	goto L500;
    }
    taz = *az * dtr;
    talt = *alt * dtr;
    saz = sin(taz);
    caz = cos(taz);
    sal = sin(talt);
    cal = cos(talt);
    xsc = dabs(*xlen) / (real) (*n - 1);
    id = 1;
    if (*xlen < (float)0.) {
	id = -1;
    }
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
    if (plt3b_1.a1 <= (float)0.) {
	++iaz;
    }
    if (plt3b_1.a2 <= (float)0.) {
	iaz += 2;
    }
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
    switch ((int)iaz) {
	case 1:  goto L64;
	case 2:  goto L62;
	case 3:  goto L62;
	case 4:  goto L64;
    }
L62:
    lli = 1;
    goto L66;
L64:
    lli = -1;
L66:
    ic = id;
    ibeg = ifirst + istep;
L70:
    i__2 = ((i__1 = ibeg - ifirst, abs(i__1)) << 1) + 1;
    lnth = min(i__2,lmax);
    if (lli == -1) {
	goto L72;
    }
    ll = 0;
    goto L74;
L72:
    ll = lnth + 1;
L74:
    i = ibeg;
    j = jfirst;
    xx = (real) j;
    yy = (real) i;
    ll += lli;
    d[(ll - 1 << 1) + 1] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[ll * 2] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * (a[i + j * 
	    a_dim1] + *zoff) + plt3b_1.b4;
L80:
    i -= istep;
    yy = (real) i;
    ll += lli;
    d[(ll - 1 << 1) + 1] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[ll * 2] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * (a[i + j * 
	    a_dim1] + *zoff) + plt3b_1.b4;
    if (j == jlast) {
	goto L85;
    }
    j += jstep;
    xx = (real) j;
    ll += lli;
    d[(ll - 1 << 1) + 1] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[ll * 2] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * (a[i + j * 
	    a_dim1] + *zoff) + plt3b_1.b4;
    if (i != ifirst) {
	goto L80;
    }
L85:
    nxtvu_(&ic, &d[1], &lnth, &w2[1], nn, ier);
    if (*ier != 0) {
/*	printf("nxtvu error %d at 85\n",*ier); */
	return 0;
    }
    ic = id << 1;
    if (ibeg == ilast) {
	goto L90;
    }
    ibeg += istep;
    goto L70;
L90:
    jbeg = jfirst;
L100:
    i__2 = ((i__1 = jbeg - jlast, abs(i__1)) << 1) + 1;
    lnth = min(i__2,lmax);
    if (lli == -1) {
	goto L102;
    }
    ll = 0;
    goto L104;
L102:
    ll = lnth + 1;
L104:
    i = ilast;
    j = jbeg;
    xx = (real) j;
    yy = (real) i;
    ll += lli;
    d[(ll - 1 << 1) + 1] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[ll * 2] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * (a[i + j * 
	    a_dim1] + *zoff) + plt3b_1.b4;
L110:
    j += jstep;
    xx = (real) j;
    ll += lli;
    d[(ll - 1 << 1) + 1] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[ll * 2] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * (a[i + j * 
	    a_dim1] + *zoff) + plt3b_1.b4;
    if (i == ifirst) {
	goto L120;
    }
    i -= istep;
    yy = (real) i;
    ll += lli;
    d[(ll - 1 << 1) + 1] = plt3b_1.a1 * xx + plt3b_1.a2 * yy + plt3b_1.a3;
    d[ll * 2] = plt3b_1.b1 * xx + plt3b_1.b2 * yy + plt3b_1.b3 * (a[i + j * 
	    a_dim1] + *zoff) + plt3b_1.b4;
    if (j != jlast) {
	goto L110;
    }
L120:
    i__1 = id << 1;
    nxtvu_(&i__1, &d[1], &lnth, &w2[1], nn, ier);
    if (*ier != 0) {
/*	printf("nxtvu error %d at 120\n",*ier); */
	return 0;
    }
    jbeg += jstep;
    if (jbeg == jlast) {
	return 0;
    }
    goto L100;
L500:
    *ier = 2;
    return 0;
} /* plt3d_ */

