
/* *** LAST REVISED ON  7-JAN-1994 15:25:36.05 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]CNDRAW.C */

#include "my.h"

/* Common Block Declarations */

struct {
    real a1, a2, a3, b1, b2, b3, b4;
} plt3b_;

#define plt3b_1 plt3b_

/* Table of constant values */

static real c_b2 = (float)0.;
static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;

/* Subroutine */ int cndraw_(x, y, il, ih, cval, nch, cs, nmin, icl, icol, 
	iline)
real *x, *y;
integer *il, *ih;
real *cval;
integer *nch;
real *cs;
integer *nmin, *icl, *icol, *iline;
{
    /* System generated locals */
    real r__1, r__2, r__3;
    char ch__1[1];

    /* External functions */
    extern /* Subroutine */ int plot_();
    extern /* Subroutine */ int number_(), newpen_(), symbol_();

    /* Local variables */
    static integer ipen, ncnt;
    static real x1, y1;
    static integer ihn;

/* 	ROUTINE TO PLOT CONTOUR LINES AND LABELS */

/* 	X,Y	(R)	LOCATION OF POINT (IN POINTS) */
/* 	IL	(I)	OPERATION ID FLAG */
/* 			= 1 CONTINUE CONTOUR */
/* 			= 2 START CONTOUR AT BOUNDRY */
/* 			= 3 START CONTOUR NOT AT BOUNDRY */
/* 			= 4 FINISH CONTOUR AT BOUNDRY */
/* 			= 5 FINISH CLOSED CONTOUR (NOT AT BOUNDRY) */
/* 	IH	(I)	CONTOUR NUMBER */
/* 			 IF IH > 0 THEN CONTOUR NUMBER IS LOOKED UP IN */
/* 			 CVAL ARRAY.  IF IH < 0 THEN THE FIRST ELEMENT */
/* 			 OF CVAL IS USED AND CONTOUR IS LABELED WITH IABS(IH) */
/* 	CVAL	(R)	CONTOUR VALUE */
/* 	NCH	(I)	CONTOUR LABELING OPTION */
/* 			< 0 LABEL WITH CONTOUR VALUE (NCH IS NUMBER */
/* 				OF DIGITS TO THE LEFT OF DECIMAL */
/* 			= 0 NO LABELING OF CONTOURS */
/* 			> 0 LABEL WITH LETTERS */
/* 	CS	(R)	LABEL SIZE */
/* 			< 0 PLT3D LOCATION SCALING USED WITH Z VALUE */
/* 			    OF ZERO */
/* 			> 0 NORMAL SCALING USED */
/* 	NMIN	(I)	MINIMUM NUMBER OF SEGMENTS TO BE LABELED */
/* 	ICL	(I)	COLOR AND LINE TYPE FLAG */
/* 			= 0 NO COLOR OR LINE TYPE USED */
/* 			= 1 COLOR USED ONLY */
/* 			= 2 LINE TYPE USED ONLY */
/* 			= 3 COLOR AND LINE TYPE USED */
/* 	ICOL	(I)	LINE COLOR FOR EACH CONTOUR */
/* 	ILINE	(I)	LINE TYPE FOR EACH CONTOUR */

    /* Parameter adjustments */
    --iline;
    --icol;

    /* Function Body */
    ipen = 2;
    if (*il == 2 || *il == 3) {		/* LINE TYPE */
	ihn = max(1,*ih);
	if (*icl > 1) {
	    newpen_(&iline[ihn]);
	}
	if (*icl % 2 == 1) {		/* PEN COLOR */
	    r__1 = (real) icol[ihn];
	    plot_(&r__1, &c_b2, &c__0);
	}
	ipen = 3;
	ncnt = 0;
    }
    ++ncnt;
    x1 = *x;
    y1 = *y;
    if (*cs < (float)0.) {
	x1 = plt3b_1.a1 * (*y + (float)1.) + plt3b_1.a2 * (*x + (float)1.) + 
		plt3b_1.a3;
	y1 = plt3b_1.b1 * (*y + (float)1.) + plt3b_1.b2 * (*x + (float)1.) + 
		plt3b_1.b4;
    }
    plot_(&x1, &y1, &ipen);
    if (*il < 4) {
	goto L30;
    }
    if (*nch == 0) {
	goto L30;
    }
    if (ncnt < *nmin) {
	goto L30;
    }
    if (*icl > 1) {			/* RESET LINE TYPE */
	newpen_(&c__1);
    }
    if (*nch < 0) {
	goto L5;
    }
    if (abs(*ih) < 26) {
	goto L10;
    }
L5:
    r__1 = y1 - (float).05;
    r__2 = dabs(*cs);
    r__3 = (real) abs(*nch) / (float)100.;
    number_(&x1, &r__1, &r__2, cval, &c_b2, &r__3, &c_n1);
    goto L30;
L10:
    r__1 = y1 - (float).05;
    r__2 = dabs(*cs);
    ch__1[0] = abs(*ih) + 64;
    symbol_(&x1, &r__1, &r__2, ch__1, &c_b2, &c__1, &c_n1, 1L);
L30:
    return 0;
} /* cndraw_ */

integer pow2_(p)
integer p;
{
return 1 << p;
}


/* Subroutine */ int gcontr_(z, ndx, ndy, nx, ny, xl, yl, cv, nc, zmax, 
	bitmap, nch, cs, nmin, icl, icol, iline)
real *z;
integer *ndx, *ndy, *nx, *ny;
real *xl, *yl, *cv;
integer *nc;
real *zmax;
integer *bitmap;
integer *nch;
real *cs;
integer *nmin, *icl, *icol, *iline;
{
    /* Initialized data */

    static integer l1[4] = { 0,0,-1,-1 };
    static integer i1[2] = { 1,0 };
    static integer i2[2] = { 1,-1 };
    static integer i3[6] = { 1,0,0,1,1,0 };
    static integer nbpw = 31;

    /* External functions */
    extern /* Subroutine */ int cndraw_();

    /* System generated locals */
    integer z_dim1, z_offset, i__1, i__2, i__3;
    static integer equiv_3[4], equiv_5[2];
    static real equiv_7[2];

    /* Local variables */
    static real cval;
    static integer ibit[32];
    static real dmax_;
    static integer idir;
#define imin (equiv_3 + 2)
#define jmin (equiv_3 + 3)
#define imax (equiv_3)
#define jmax (equiv_3 + 1)
    static integer nbit, icur, jcur, nblw, loop;
    int jump;
    static real xint[4];
#define i (equiv_5)
#define j (equiv_5 + 1)
    static integer k, l, iedge, n, iflag;
#define x (equiv_7)
#define y (equiv_7 + 1)
    static integer ibkey, nword;
#define l2 (equiv_3)
    static real z1, z2;
    static integer ii;
#define ij (equiv_5)
    static integer jj, ni, ll, ks, ix;
    static real xx;
#define xy (equiv_7)
    static real yy, zz;
    static integer nxidir, iij, icv, ncv;

/* 	DRAWS CONTOURS THROUGH EQUAL VALUES OF AN ORTHOGONAL ARRAY */

/* 	Z	(R)	ARRAY FOR WHICH CONTOURS DRAWN */
/* 			DIMENSIONED Z(NDX,NDY) (X,Y) */
/* 	NDX,NDY	(I)	DIMENSION OF Z */
/* 	NX,NY	(I)	NUMBER OF X,Y POINTS IN Z TO USE (NX<=NRZ) */
/* 	XL,YL	(R)	SCALE FACTORS FOR X,Y POINTS (INCHES/POINT) */
/* 	CV	(R)	ARRAY OF CONTOUR VALUES TO BE DRAWN DIM DV(NCV) */
/* 			CV < 0 CAUSES PLT3D PLOTTING PARAMETERS TO BE USED */
/* 			FOR OUTPUTTING CONTOUR VALUES */
/* 	NC	(I)	NUMBER OF CONTOURS IN CV (SET TO NCV) */
/* 			 IF NCV < 0 THEN ONLY ONE CONTOUR IS ASSUMED.  IT */
/* 			 WILL BE LABELED AS CONTOUR IABS(NC) AND NCV WILL BE */
/* 			 EQUAL TO 1 WHEREVER IT APPEARS. */
/* 	ZMAX	(R)	MAXIMUM VALUE OF Z FOR CONSIDERATION.  A POINT */
/* 			Z(I,J) WHIC EXCEEDS ZMAX WILL CAUSE THIS POINT AND */
/* 			THE LINE SEGMENTS WHICH RADIATE OUT FROM IT TO NOT */
/* 			BE CONSIDERED WHEN CONTOURING. */
/* 	BITMAP	(I*4)	WORK SPACE DIMENSIONED AT LEAST */
/* 			(2*NX*NY*NCV+NBPW-1)/NBPW WHERE NBPW IS THE */
/* 			NUMBER OF USEFUL BITS IN A WORD (NBPW=31) */
/* 	NCH	(I)	CONTOUR LABELING OPTION */
/* 			< 0 LABEL WITH CONTOUR VALUE (NCH IS NUMBER */
/* 				OF DIGITS TO THE LEFT OF DECIMAL) */
/* 			= 0 NO LABELING OF CONTOURS */
/* 			> 0 LABEL WITH LETTERS */
/* 	CS	(R)	SIZE OF LABELS */
/* 			> 0 NORMAL LINEAR OPERATION */
/* 			< 0 PLT3D TRANSFORMATION USED (XL,YL SHOULD BE 1.0) */
/* 	NMIN	(I)	MINIMUM NUMBER OF SEGMENTS CROSSED FOR CONTOUR */
/* 			TO BE LABELED */
/* 	ICL	(I)	COLOR AND LINE TYPE FLAG */
/* 			= 0 NO COLOR OR LINE TYPE USED */
/* 			= 1 COLOR USED ONLY */
/* 			= 2 LINE TYPE USED ONLY */
/* 			= 3 COLOR AND LINE TYPE USED */
/* 	ICOL	(I)	LINE COLOR FOR EACH CONTOUR */
/* 	ILINE	(I)	LINE TYPE FOR EACH CONTOUR */

/* LIMITS USED IN SPIRAL SEARCH */
/* NEIGHBOR COMPUTATIONS */
/* INTERSECTIONS OF CONTOURS WITH CELL EDGES */
/* COORDINATES FOR PLOTTING */

    /* Parameter adjustments */
    --iline;
    --icol;
    --bitmap;
    --cv;
    z_dim1 = *ndx;
    z_offset = z_dim1 + 1;
    z -= z_offset;

    /* Function Body */

/* 	COMPUTE BITS ARRAY */

    ncv = 1;
    if (*nc > 0) {
	ncv = *nc;
    }
    i__1 = nbpw;
    for (*i = 1; *i <= i__1; ++(*i)) {
	i__2 = *i - 1;
	ibit[*i - 1] = pow2_(i__2);
    }

    l1[0] = *nx;
    l1[1] = *ny;
    dmax_ = *zmax;

/* 	SET INITIAL POSITION */

    *x = (real) (*nx);
    *y = (real) (*ny);
    icur = *x;
    jcur = *y;

/* 	CLEAR BITMAP */
/* 	FILLS BITMAP WITH N ZEROS.  NBPW IS THE NUMBER OF USEFUL BITS IN */
/* 	A WORD (USUALLY 1 LESS THAN THE NUMBER OF BITS) */

    n = (*nx << 1) * *ny * ncv;
    loop = n / nbpw;
    nblw = n % nbpw;
    if (loop != 0) {
      i__1 = loop;
      for (*i = 1; *i <= i__1; ++(*i)) {
	bitmap[*i] = 0;
      }
    }
    if (nblw != 0) {
	bitmap[loop + 1] = 0;
    }

/* 	SEARCH ALONG RECTANGULAR SPIRAL PATH FOR A LINE SEGMENT THAT */
/* 	1. END POINTS ARE NOT EXCLUDED */
/* 	2. NO MARK HAS BEEN RECORDED FOR THE SEGMENT */
/* 	3. VALUES OF Z AT END OF SEGMENT ARE SUTCH THAT ONE Z IS LESS THAN */
/* 	   THE CURRENT CONTOUR VALUE, AND THE OTHER IS GREATER THAN OR EQUAL*/
/* 	   TO THE CURRENT CONTOUR VALUE */

    ibkey = 0;
L10:
    *i = icur;
    *j = jcur;
L20:
    *imax = *i;
    *imin = -(*i);
    *jmax = *j;
    *jmin = -(*j);
    idir = 0;

/* 	DIRECTION CODE: */
/* 	 0: +I   1:+J   2:-I   3:-J */

L30:
    nxidir = idir + 1;
    k = nxidir;
    if (nxidir > 3) {
	nxidir = 0;
    }
L40:
    *i = abs(*i);
    *j = abs(*j);
    if (z[*i + *j * z_dim1] > dmax_) {
	goto L140;
    }
    l = 1;
/* L=1 MEANS HORIZONTAL LINE, L=2 MEANS VERTICAL LINE */
L50:
    if (ij[l - 1] >= l1[l - 1]) {
	goto L130;
    }
    ii = *i + i1[l - 1];
    jj = *j + i1[3 - l - 1];
    if (z[ii + jj * z_dim1] > dmax_) {
	goto L130;
    }

    jump = 0;

/* THE NEXT 15 STATEMENTS DETECT BOUNDRIES */

L60:
    ix = 1;
    if (ij[3 - l - 1] == 1) {
	goto L80;
    }
    ii = *i - i1[3 - l - 1];
    jj = *j - i1[l - 1];
    if (z[ii + jj * z_dim1] > dmax_) {
	goto L70;
    }
    ii = *i + i2[l - 1];
    jj = *j + i2[3 - l - 1];
    if (z[ii + jj * z_dim1] < dmax_) {
	ix = 0;
    }
L70:
    if (ij[3 - l - 1] >= l1[3 - l - 1]) {
	goto L90;
    }
L80:
    ii = *i + i1[3 - l - 1];
    jj = *j + i1[l - 1];
    if (z[ii + jj * z_dim1] > dmax_) {
	goto L90;
    }
    if (z[*i + 1 + (*j + 1) * z_dim1] < dmax_) {
	switch (jump) {
	    case 0: goto L100;
	    case 1: goto L280;
	}
    }
/* (100 OR 280) */
L90:
    ix += 2;
    switch (jump) {
	case 0: goto L100;
	case 1: goto L280;
    }
/* (100 OR 280) */
L100:
    if (ix == 3) {
	goto L130;
    }
    if (ix + ibkey == 0) {
	goto L130;
    }
/* DETERMINE WHETHER LINE SEGMENT IS CROSSED BY CONTOUR */
    ii = *i + i1[l - 1];
    jj = *j + i1[3 - l - 1];
    z1 = z[*i + *j * z_dim1];
    z2 = z[ii + jj * z_dim1];
    i__1 = ncv;
    for (icv = 1; icv <= i__1; ++icv) {
/* C		IF (IGET(BITMAP,2*(NX*(NY*(ICV-1)+J-1)+I-1)+L).NE.0) GOTO 120 */

	i__2 = ((*nx * (*ny * (icv - 1) + *j - 1) + *i - 1) << 1) + l;
	i__3 = nbpw - (i__2 - 1) % nbpw - 1;
	if (((bitmap[(i__2 - 1) / nbpw + 1] / pow2_(i__3)) % 2) != 0) {
	    goto L120;
	}
	if (cv[icv] <= dmin(z1,z2)) {
	    goto L110;
	}
	if (cv[icv] <= dmax(z1,z2)) {
	    goto L190;
	}
L110:
/* 	MARK BIT MAP */

/* C		CALL MARK1(BITMAP,2*(NX*(NY*(ICV-1)+J-1)+I-1)+L,NBPW) */
	ll = (*nx * (*ny * (icv - 1) + *j - 1) + *i - 1 << 1) + l;
	nword = (ll - 1) / nbpw + 1;
	nbit = (ll - 1) % nbpw;
	iij = ibit[nbpw - nbit - 1];
	bitmap[nword] += iij * (1 - bitmap[nword] / iij % 2);
L120:
	;
    }
L130:
    ++l;
    if (l <= 2) {
	goto L50;
    }
L140:
    l = idir % 2 + 1;
    ij[l - 1] = ( l1[k - 1] >= 0 ? ij[l - 1] : - ij[l - 1]);

/* 	LINES FROM Z(I,J) TO Z(I+1,J) AND Z(I,J+1) ARE NOT SATISFACTORY, */
/* 	SO CONTINUE SPIRAL */

L150:
    if (ij[l - 1] >= l1[k - 1]) {
	goto L170;
    }
    ++ij[l - 1];
    if (ij[l - 1] > l2[k - 1]) {
	goto L160;
    }
    goto L40;
L160:
    l2[k - 1] = ij[l - 1];
    idir = nxidir;
    goto L30;
L170:
    if (idir == nxidir) {
	goto L180;
    }
    ++nxidir;
    ij[l - 1] = l1[k - 1];
    k = nxidir;
    l = 3 - l;
    ij[l - 1] = l2[k - 1];
    if (nxidir > 3) {
	nxidir = 0;
    }
    goto L150;
L180:
    if (ibkey != 0) {
	return 0;
    }
    ibkey = 1;
    goto L10;

/* AN ACCEPTABLE LINE SEGMENT HAS BEEN FOUND.  FOLLOW CONTOUR UNTIL IT */
/* HITS THE BOUNDRY OR CLOSES */

L190:
    iedge = l;
    cval = cv[icv];
    if (ix != 1) {
	iedge += 2;
    }
    iflag = ibkey + 2;
    xint[iedge - 1] = (cval - z1) / (z2 - z1);
L200:
    xy[l - 1] = (real) ij[l - 1] + xint[iedge - 1];
    xy[3 - l - 1] = (real) ij[3 - l - 1];

/* 	MARK BIT MAP */

/* C	CALL MARK1(BITMAP,2*(NX*(NY*(ICV-1)+J-1)+I-1)+L,NBPW) */
    ll = (*nx * (*ny * (icv - 1) + *j - 1) + *i - 1 << 1) + l;
    nword = (ll - 1) / nbpw + 1;
    nbit = (ll - 1) % nbpw;
    iij = ibit[nbpw - nbit - 1];
    bitmap[nword] += iij * (1 - bitmap[nword] / iij % 2);

    xx = (*x - (float)1.) * *xl;
    yy = (*y - (float)1.) * *yl;
    cndraw_(&xx, &yy, &iflag, nc, &cval, nch, cs, nmin, icl, &icol[1], &iline[
	    1]);
    if (iflag < 4) {
	goto L210;
    }
    icur = *i;
    jcur = *j;
    goto L20;

/* CONTINUE CONTOUR.  EDGES ARE NUMBERED CLOCKWISE WITH BOTTOM EDGE BEING */
/* EDGE NUMBER ONE. */

L210:
    ni = 1;
    if (iedge < 3) {
	goto L220;
    }
    *i -= i3[iedge - 1];
    *j -= i3[iedge + 1];
L220:
    for (k = 1; k <= 4; ++k) {
	if (k == iedge) {
	    goto L250;
	}
	ii = *i + i3[k - 1];
	jj = *j + i3[k];
	z1 = z[ii + jj * z_dim1];
	ii = *i + i3[k];
	jj = *j + i3[k + 1];
	z2 = z[ii + jj * z_dim1];
	if (cval <= dmin(z1,z2)) {
	    goto L250;
	}
	if (cval > dmax(z1,z2)) {
	    goto L250;
	}
	if (k == 1) {
	    goto L230;
	}
	if (k != 4) {
	    goto L240;
	}
L230:
	zz = z1;
	z1 = z2;
	z2 = zz;
L240:
	xint[k - 1] = (cval - z1) / (z2 - z1);
	++ni;
	ks = k;
L250:
	;
    }
    if (ni == 2) {
	goto L260;
    }

/* CONTOUR CROSSES ALL FOUR EDGES OF THE CELL. CHOOSE LINES TOP-TO-LEFT AND*/
/* BOTTOM TO RIGHT IF THE INTERPOLATION POINT ON THE TOP EDGE IS LESS THAN*/
/* THE INTERPOLATION POINT ON THE BOTTOM EDGE. OTHERWISE CHOSE THE OTHER */
/* PAIR.  METHOD PRODUCES SAME RESULTS FOR REVERSED AXES. CONTOUR MAY CLOSE*/
/* AT ANY EDGE, BUT MUST NOT CROSS ITSELF IN ANY CELL. */

    ks = 5 - iedge;
    if (xint[2] < xint[0]) {
	goto L260;
    }
    ks = 3 - iedge;
    if (ks <= 0) {
	ks += 4;
    }

L260:
    l = ks;
    iflag = 1;
    jump = 1;
    if (ks < 3) {
	goto L270;
    }
    *i += i3[ks - 1];
    *j += i3[ks + 1];
    l = ks - 2;
L270:
    i__1 = (*nx * (*ny * (icv - 1) + *j - 1) + *i - 1 << 1) + l;
    i__2 = nbpw - (i__1 - 1) % nbpw - 1;
    if (bitmap[(i__1 - 1) / nbpw + 1] / pow2_(i__2) % 2 == 0) {
	goto L60;
    }
    iflag = 5;
    goto L290;
L280:
    if (ix != 0) {
	iflag = 4;
    }
L290:
    iedge = ks + 2;
    if (iedge > 4) {
	iedge += -4;
    }
    xint[iedge - 1] = xint[ks - 1];
    goto L200;
} /* gcontr_ */

#undef xy
#undef ij
#undef l2
#undef y
#undef x
#undef j
#undef i
#undef jmax
#undef imax
#undef jmin
#undef imin
