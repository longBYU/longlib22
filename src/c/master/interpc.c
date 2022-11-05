
/* *** LAST REVISED ON 23-DEC-1993 06:31:51.18 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]INTERPC.C */

#include "my.h"

/* Subroutine */ int interpc_(x, y, u, n, zcon, ledges, ie, lambda, xi, eta, 
	j, nz)
real *x, *y, *u;
integer *n;
real *zcon;
integer *ledges, *ie, *lambda;
real *xi, *eta;
integer *j, *nz;
{
    /* System generated locals */
    integer ie_dim1, ie_offset, i__1;

    /* Local variables */
    static integer lcnt;
    static real temp;
    static integer i1, i2;
    static real t1, u1, u2, t2, x1, x2, y1, y2;

/* 	COSMIC CONTOUR ROUTINES ARC-11441 */
/* 	MODIFIED  D.G. LONG, JPL  FEB 1986 */
/* ------------------------------------------------------------------ */

/* ROUTINE INTERPC IS GIVEN A CONSTANT U VALUE (BIGU) FOR WHICH */
/* THE CONTOUR LINE IS TO BE DRAWN.  CHECK ALL GIVEN TRIANGLE EDGES, */
/* (ARRAY IE) AND CHECK THE VALUES OF U AT THE ENDPOINTS. */
/* INTERPOLATE FOR ALL POSSIBLE VALUES ON THE TRIANGLE EDGES. */
/* USE A LINEAR INTERPOLATION SCHEME */

/* X,Y,U     = DEPENDENT AND INDEPENDENT VALUES FOR */
/*             THE RELATION U=F(X,Y)  (INPUT) */
/* ZCON      = CONSTANT VALUE OF Z FOR WHICH INTERPOLATION */
/*             IS ACCESSED  (INPUT) */
/* LEDGES    = NO. OF EDGES IN THE TRIANGULATION  (INPUT) */
/* IE        = EDGE ENDPOINT INDICES FROM TRIANGULATION (INPUT) */
/* LAMBDA    = INDEX OF EDGES FOR INTERPOLATED POINTS  (RETURN) */
/* XI        = LIST OF X-COORDINATES OF INTERPOLATED POINTS */
/* ETA       = LIST OF Y-COORDINATES OF INTERPOLATED POINTS */
/* J         = NUMBER OF VALUES IN XI, ETA LISTS */
/*             (XI, ETA AND J ARE RETURNED) */
/* NZ	    = DIMENSION OF IE,XI,ETA,LAMBDA */
/*     ------------------------------------------------------------------ 
*/


    /* Parameter adjustments */
    --eta;
    --xi;
    --lambda;
    ie_dim1 = *nz;
    ie_offset = ie_dim1 + 1;
    ie -= ie_offset;
    --u;
    --y;
    --x;

    /* Function Body */
    *j = 0;

    i__1 = *ledges;
    for (lcnt = 1; lcnt <= i__1; ++lcnt) {

/* (A) */
/* DETERMINE X,Y,Z FOR THE ENDPOINTS OF THE NEXTEDGE - ORDER THEM */

	i1 = ie[lcnt + ie_dim1];
	i2 = ie[lcnt + (ie_dim1 << 1)];
	x1 = x[i1];
	x2 = x[i2];
	y1 = y[i1];
	y2 = y[i2];
	u1 = u[i1];
	u2 = u[i2];

/* (B) */
/* FUNCTION VALUES EQUAL AT ENDPOINTS OR */
/* CONSTANT ZC NOT BETWEEN THEM? . . */

	if (u1 == u2) {
	    goto L1;
	}
	if (u1 < u2) {
	    goto L100;
	}
	temp = u2;
	u2 = u1;
	u1 = temp;
	temp = x2;
	x2 = x1;
	x1 = temp;
	temp = y2;
	y2 = y1;
	y1 = temp;
L100:
	if (*zcon < u1 || u2 < *zcon) {
	    goto L1;
	}
	if (u2 == *zcon) {
	    u2 = *zcon * (float)1.000001;
	}
	++(*j);

/* (E,F) */
/* LINEAR INTERPOLATION IS ACCESSED */
/* FOR THIS EDGE OVER THE Z-SURFACE */

/* L101: */
	t1 = (u2 - *zcon) / (u2 - u1);
	t2 = (*zcon - u1) / (u2 - u1);
	xi[*j] = t1 * x1 + t2 * x2;
	eta[*j] = t1 * y1 + t2 * y2;
/* L200: */
	lambda[*j] = lcnt;
L1:
	;
    }
    return 0;
} /* interpc_ */


/* Subroutine */ int cntour_(zcon, xi, eta, lambda, j, ibe, ite, nz, dx, xm, 
	dy, ym)
real *zcon, *xi, *eta;
integer *lambda, *j, *ibe, *ite, *nz;
real *dx, *xm, *dy, *ym;
{
    /* System generated locals */
    integer ite_dim1, ite_offset, i__1;

    /* Local variables */
    static integer jcnt, lcnt;
    extern /* Subroutine */ int plot_();
    static integer j1big, i, j1, l1;
    static real x1, y1;
    static integer jj, kk, ip, npoint;


/* 	COSMIC CONTOUR ROUTINES ARC-11441 */
/* 	MODIFIED  D.G. LONG, JPL  FEB 1986 */
/* ------------------------------------------------------------------ */

/* A SET OF J INTERPOLATED POINTS FOR Z=ZCON  (XI(I),ETA(I) ON EDGE */
/* LAMBDA(I) FOR I=1,J), THE CONTOUR LINES MUST NOW BE DRAWN.  THERE */
/* MAY BE SEVERAL LINES, EITHER OPEN OR CLOSED CONTOURS.  THIS */
/* ALGORITHM WILL USE THE TRIANGULATION RELATIONSHIPS TO SORT OUT */
/* EACH LINE IN ORDER.  AS EACH CONTOUR LINE IS ESTABLISHED, USER */
/* SUPPLIED PROGRAM CNTCRV IS CALLED TO OUTPUT IT TO THE GRAPHICS */
/* DEVICE BEING USED. */

/* ARGUMENTS (ALL ARE INPUTS) - */
/*  ZCON    = CONSTANT VALUE OF Z UNDER CONSIDERATION */
/*  XI(J)   = ARRAY OF X COORDIANTES OF INTERPOLATED POINTS */
/*  ETA(J)  = ARRAY OF Y COORDIANTES OF INTERPOLATED POINTS */
/*  LAMBDA(J) = ARRAY OF EDGE NUMBERS FOR J-TH INTERPOLATED POINT */
/*  J       = NUMBER OF POINTS IN THE LIST OF INTERPOLATED POINTS */
/*  IBE     = THE LIST OF BOUNDARY EDGES TAKEN FROM THE TRIANGULATI */
/*  ITE     = LINKED LIST OF INDICES OF ADJACENT EDGES PROVIDED */
/*  		BY THE TRIANGULATION PROCEDURE. */
/*  NZ	   = DIMENSION OF XI,ETA,LAMBDA,IBE,ITE */
/*  DX,XM   = PLOTTING SCALE FACTOR AND MINIMUM VALUE FOR X DIRECTION */
/*  DY,YM   = PLOTTING SCALE FACTOR AND MINIMUM VALUE FOR X DIRECTION */

/*  EXTERNAL CALLS: */
/*   (CNTCRV)/(PLOT) */

/* ------------------------------------------------------------------ */

/* CC	DIMENSION XX(1495),YY(1495) */

/* (A) */
/* INITIALIZE LOCAL VARIABLES */

    /* Parameter adjustments */
    ite_dim1 = *nz;
    ite_offset = ite_dim1 + 1;
    ite -= ite_offset;
    --ibe;
    --lambda;
    --eta;
    --xi;

    /* Function Body */
    if (*j == 0) {
	return 0;
    }
L10:
    j1 = 0;

/* (B,C) */
/* SEARCH THE LIST OF EDGES FOR A BOUNDARY EDGE (BE(I)=1) */

L1:
    ++j1;
    l1 = lambda[j1];
    if (ibe[l1] == 1) {
	goto L2;
    }
    if (j1 < *j) {
	goto L1;
    }
    goto L11;

/* SEARCH FOR A BOUNDARY EDGE AND PUT IT AT THE TOP OF THE LIST. */

/* (D) */
/* PUT THIS INTERPOLATED POINT AT THE TOP OF THE */
/* LIST FOR THIS CONTOUR,  SET J1 */

L2:
    if (j1 == *j) {
	goto L3;
    }
    xi[*j + 1] = xi[j1];
    eta[*j + 1] = eta[j1];
    lambda[*j + 1] = lambda[j1];
    i__1 = *j;
    for (jcnt = j1; jcnt <= i__1; ++jcnt) {
	xi[jcnt] = xi[jcnt + 1];
	eta[jcnt] = eta[jcnt + 1];
/* L101: */
	lambda[jcnt] = lambda[jcnt + 1];
    }

/* (E) */
/* SEARCH THE REMAINING POINTS FOR AN ADJACENT (COMMON) EDGE */

L3:
    j1big = *j;
    lcnt = l1;
L6:
    --j1big;
    j1 = 0;
L5:
    ++j1;
    l1 = lambda[j1];
    for (i = 1; i <= 4; ++i) {
	if (l1 == ite[lcnt + i * ite_dim1]) {
	    goto L4;
	}
/* L102: */
    }
/* (F) */
/* ERROR - THERE IS NO NEXT POINT. */
    if (j1 < j1big) {
	goto L5;
    }
    goto L800;

/* (G) */
/* PUT THIS POINT AT THE TOP OF THE LIST. */
/* CONTINUE IF ITS NOT A BOUNDARY EDGE. */

L4:
    xi[*j + 1] = xi[j1];
    eta[*j + 1] = eta[j1];
    lambda[*j + 1] = lambda[j1];
    i__1 = *j;
    for (jcnt = j1; jcnt <= i__1; ++jcnt) {
	xi[jcnt] = xi[jcnt + 1];
	eta[jcnt] = eta[jcnt + 1];
/* L103: */
	lambda[jcnt] = lambda[jcnt + 1];
    }
    lcnt = l1;
    if (ibe[l1] != 1) {
	goto L6;
    }

/* (H) */
/* DRAW THE OPEN CONTOUR LINE THROUGH THE POINTS */
/* XI(J1),ETA(J1) ...... XI(J1+1),ETA(J1+1) ...... XI(J),ETA(J) */
/* THEN RESET J AND CONTINUE */
/* ---------------------------------------------------------------- */

    npoint = *j - j1big + 1;
    if (npoint <= 1) {
	goto L300;
    }
    ip = 3;
    i__1 = npoint;
    for (i = 1; i <= i__1; ++i) {
	x1 = *dx * (xi[i + j1big - 1] - *xm);
	y1 = *dy * (eta[i + j1big - 1] - *ym);
	plot_(&x1, &y1, &ip);
	ip = 2;
/* L290: */
    }
/* C	CALL CNTCRV (XI(J1BIG),ETA(J1BIG),NPOINT,ZCON) */

/* ---------------------------------------------------------------- */

L300:
    *j = j1big - 1;

/* (I) */
/* ARE THERE ANY MORE POINTS LEFT? . . */

    if (*j <= 0) {
	goto L800;
    } else {
	goto L10;
    }

/* (J) */
/* NOW DRAW INTERNAL LINES (CLOSED CONTOURS THAT DO NOT START */
/* OR STOP AT BOUNDARY EDGES).  THE POINT AT J1BIG=J IN */
/* THE LIST IS CHOSEN TO START THE CONTOUR. */

L11:
    j1big = *j + 1;
    lcnt = lambda[*j];

/* (K,M,P) */
/* FIND THE NEXT POINT FOR THIS CONTOUR (ON AN EDGE WITH A COMMON */
/* END POINT).  PUT IT AT THE TOP OF THE LIST, AND REPEAT UNTIL */
/* NO MORE COMMON EDGES REMAIN FOR THIS LINE. */

L16:
    --j1big;
    j1 = 0;
    if (j1big > *j) {
	j1 = 1;
    }
L15:
    ++j1;
    l1 = lambda[j1];
    for (i = 1; i <= 4; ++i) {
	if (l1 == ite[lcnt + i * ite_dim1]) {
	    goto L14;
	}
/* L104: */
    }
    if (j1 < j1big) {
	goto L15;
    }
/* (L) */
/* OTHERWISE, NO ADJACENT EDGE WAS FOUND. */
/* THIS CONTOUR LINE IS COMPLETE, GO DRAW IT. */
    goto L17;

L14:
    xi[*j + 1] = xi[j1];
    eta[*j + 1] = eta[j1];
    lambda[*j + 1] = lambda[j1];
    i__1 = *j;
    for (jcnt = j1; jcnt <= i__1; ++jcnt) {
	xi[jcnt] = xi[jcnt + 1];
	eta[jcnt] = eta[jcnt + 1];
/* L105: */
	lambda[jcnt] = lambda[jcnt + 1];
    }
    lcnt = l1;
    if (j1big != 1) {
	goto L16;
    }

/* (O) */
/* DRAW THE CLOSED CONTOUR LINE, THE INTERPOLATED LINE THROUGH */
/* XI(J1),ETA(J1) ...... XI(J),ETA(J) ...... XI(J1),ETA(J1) */

L17:
    jj = j1big;
    if (j1big != 1) {
	jj = j1big + 1;
    }
/* C	KNT = 0 */
    ip = 3;
    i__1 = *j;
    for (kk = jj; kk <= i__1; ++kk) {
/* C		KNT = KNT+1 */
	x1 = *dx * (xi[kk] - *xm);
	y1 = *dy * (eta[kk] - *ym);
	plot_(&x1, &y1, &ip);
	ip = 2;
/* C		XX(KNT) = XI(KK) */
/* C		YY(KNT) = ETA(KK) */
/* L510: */
    }
    x1 = *dx * (xi[jj] - *xm);
    y1 = *dy * (eta[jj] - *ym);
    plot_(&x1, &y1, &ip);
/* C	XX(KNT+1) = XX(1) */
/* C	YY(KNT+1) = YY(1) */
/* C	NPOINT = KNT+1 */
/* C	CALL CNTCRV (XX(1),YY(1),NPOINT,ZCON) */

/* (P) */
/* RESET J.  ESTABLISH THE NEXT CONTOUR LINE FOR REMAINING POINTS */
/* OR QUIT THE PROCEDURE IF NO MORE POINTS REMAIN. */

    *j = j1big - 1;
    if (*j > 0) {
	++(*j);
    }
    if (*j <= 0) {
	goto L800;
    } else {
	goto L11;
    }
L800:
    return 0;
} /* cntour_ */



/* Subroutine */ int triangc_(x, y, nn, t, nzz, m, p, b, nw, l, nz, e, be, te)

real *x, *y;
integer *nn, *t, *nzz, *m, *p, *b, *nw, *l, *nz, *e, *be, *te;
{
    /* System generated locals */
    integer t_dim1, t_offset, e_dim1, e_offset, te_dim1, te_offset, i__1, 
	    i__2;
    real r__1, r__2, r__3, r__4;

    /* Builtin functions */
    double sqrt();

    /* Local variables */
    extern integer midc_();
    static real dmin_;
    static integer jcnt, kcnt, lcnt, mcnt;
    static doublereal term;
    static integer kknt;
    static doublereal d;
    static integer j, k, n, bflag;
    static doublereal s;
    static integer b1, b2;
    static doublereal d1;
    static integer i1, i2, j1, k1, k2, k3, k0, p1, p2, l1, l2, l3, bj, lambda,
	     lj;
    static doublereal tc;
    static integer km, pj, kn;
    static real x12, y12;
    static integer kt, nq, kk, kl, ll, pk0;
    static real x1b, y1b;
    static integer pk3, kp1, pkl;
    static real dst, xqb, yqb;


/* 	COSMIC CONTOUR ROUTINES ARC-11441 */
/* 	MODIFIED  D.G. LONG, JPL  FEB 1986 */
/*     ------------------------------------------------------------------ 
*/

/* A SET OF N DATA POINTS ARE KNOWN (X(I),Y(I),I=1,N)  THEY ARE TO */
/* BE CONNECTED BY LINES TO FORM A SET OF TRIANGLES. THE FINAL */
/* TRIANGULATION ESTABLISHES A CONVEX POLYGON DEFINED BY LINKED */
/* LISTS OF EDGE NUMBERS, END POINTS AND BOUNDARY EDGES. */

/*     INPUT */
/*       X   = ARRAY OF ABSCISSAS */
/*       Y   = ARRAY OF ORDINATES */
/*       NN  = NUMBER OF POINTS IN X AND Y */
/* 		IF NN < 0 THEN BE AND TE ARRAYS ARE NOT USED */
/* 	NW  = DIMENSION OF WORKING ARRAY */
/* 	P,B = INTEGER WORKING ARRAYS P(NW),B(NW) */
/* 	NZ  = DIMENSION OF INDEXING ARRAYS E,BE,TE */
/* 	NZZ = DIMENSION OF INDEXING ARRAY T */

/*     OUTPUT */
/*       L   = NUMBER OF EDGES LISTED IN E, BE AND TE */
/* 	T   = INDICES OF AJACENT TRIANGLE EDGES -- T(NZZ,3) */
/*  IF NN>0 THEN */
/*       E   = INTEGER LIST OF INDICES OF EACH TRIANGLE EDGE -- E(NZ,2) */

/*       BE  = 1 IF I OF E IS A BOUNDARY EDGE -- BE(NZ) */
/*       TE  = INDICES OF NEIGHBORING EDGES FOR EACH TRIANGLE -- TE(NZ,4) 
*/

/*     LOCAL VARIABLES */
/*       P   = INDICES OF POINTS OUTSIDE THE BOUNDARY */
/*       J   = NO. OF VALUES IN LIST P */
/*       B   = INDEX OF POINTS ON THE BOUNDARY ..  INORDER */
/*       T   = INDICES OF ADJACENT TRIANGLE EDGES */
/*       K   = NO. OF POINTS LISTED IN ARRAY B */
/*       M   = NO. OF ROWS USED IN ARRAY T */
/*       X   = ARRAY OF SCALED X DATA */
/*       Y   = ARRAY OF SCALED Y DATA */

/* 	EXTERNAL CALLS: */
/* 		MIDC (INTEGER FUNCTION) */

/*     ------------------------------------------------------------------ 
*/




/* DOUBLE PRECISION SPECIFICATION STATEMENTS */


/* (A) */
/* THE PROCEDURE BEGINS WITH NO BOUNDARY, NO EDGES, AND */
/* ALL X-Y DATA POINTS UNDER CONSIDERATION */
/* INITIALIZE LOCAL VARIABLES. */

    /* Parameter adjustments */
    te_dim1 = *nz;
    te_offset = te_dim1 + 1;
    te -= te_offset;
    --be;
    e_dim1 = *nz;
    e_offset = e_dim1 + 1;
    e -= e_offset;
    --b;
    --p;
    t_dim1 = *nzz;
    t_offset = t_dim1 + 1;
    t -= t_offset;
    --y;
    --x;

    /* Function Body */
    n = abs(*nn);
    j = n;
    k = 0;
    *l = 0;
    *m = 0;
    kknt = 0;
    i__1 = j;
    for (jcnt = 1; jcnt <= i__1; ++jcnt) {
/* L100: */
	p[jcnt] = jcnt;
    }

/* (B) */
/* BEGIN BY TAKING THE LAST PAIR OF POINTS (X,Y(J)) IN THE */
/* LIST TO BE THE FIRST BOUNDARY POINT */

    b[1] = j;
    --j;

/* (C) */
/* FROM THE REMAINING POINTS, FIND THE POINT NEAREST THE FIRST */

    i2 = 1;
    i1 = b[1];
/* Computing 2nd power */
    r__1 = x[i1] - x[1];
/* Computing 2nd power */
    r__2 = y[i1] - y[1];
    dmin_ = r__1 * r__1 + r__2 * r__2;
    i__1 = j;
    for (j1 = 2; j1 <= i__1; ++j1) {
/* Computing 2nd power */
	r__1 = x[i1] - x[j1];
/* Computing 2nd power */
	r__2 = y[i1] - y[j1];
	dst = r__1 * r__1 + r__2 * r__2;
	if (dst >= dmin_) {
	    goto L270;
	}
	i2 = j1;
	dmin_ = dst;
L270:
	;
    }

/* (D) */
/* NOW B(1) TO B(I2) IS THE FIRST EDGE. */
/* THERE IS ONE EDGE AND TWO BOUNDARY POINTS. */

    --j;
    if (i2 > j) {
	goto L275;
    }
    i__1 = j;
    for (jcnt = i2; jcnt <= i__1; ++jcnt) {
	p[jcnt] = p[jcnt + 1];
/* L274: */
    }
L275:
    k = 2;
    b[2] = i2;
    *l = 1;
    if (*nn > 0) {
	e[e_dim1 + 1] = min(b[1],b[2]);
	e[(e_dim1 << 1) + 1] = max(b[1],b[2]);
    }

/* (E) */
/* NOW BEGIN CIRCLING AROUND THE BOUNDARY OF THE POLYGON, */
/* CONSIDERING, IN ORDER, EACH BOUNDARY EDGE.  MAINTAIN THE */
/* FOLLOWING INDICES - */
/*  K1 = B ARRAY INDEX OF THE CURRENT EDGE - POINT 1 */
/*  K2 = B ARRAY INDEX OF THE CURRENT EDGE - POINT 2 */
/*  B1,B2 = INDICES OF BOUNDARY POINT COORDINATES */

    k1 = 0;
    kt = 0;
L11:
    ++k1;
    if (k1 > k) {
	k1 = 1;
    }
L12:
    k2 = k1 + 1;
    if (k2 > k) {
	k2 = 1;
    }
    b1 = b[k1];
    b2 = b[k2];
    ++kt;

/* (F) */
/* CONSIDER THE BOUNDARY EDGE FROM B1 TO B2.  FOR ALL POINTS NOT */
/* YET TRIANGULATED (THE J POINTS REMAINING IN P), FIND THE */
/* POINT THAT, WHEN TRIANGULATED WITH B1,B2, MINIMIZES THE LENGTH */
/* OF THE TWO NEW EDGES TO BE DRAWN. */

    d1 = (float)0.;
    j1 = 0;
    bflag = 0;
    if (j == 0) {
	goto L6;
    }
    i__1 = j;
    for (lj = 1; lj <= i__1; ++lj) {
	pj = p[lj];
	term = (y[pj] - y[b1]) * (x[b2] - x[b1]) - (x[pj] - x[b1]) * (y[b2] - 
		y[b1]);
	if (term <= 0.) {
	    goto L1;
	}
/* Computing 2nd power */
	r__1 = x[pj] - x[b1];
/* Computing 2nd power */
	r__2 = y[pj] - y[b1];
/* Computing 2nd power */
	r__3 = x[pj] - x[b2];
/* Computing 2nd power */
	r__4 = y[pj] - y[b2];
	d = sqrt(r__1 * r__1 + r__2 * r__2) + sqrt(r__3 * r__3 + r__4 * r__4);

	if (j1 != 0 && d1 < d) {
	    goto L1;
	}
	j1 = lj;
	d1 = d;
L1:
	;
    }

/* (G) */
/* IF LESS THAN THREE EDGES EXIST (NO TRIANGLE DEFINED YET), */
/* THEN THERE ARE NO ADJACENT BOUNDARY POINTS TO BE CONSIDERED. */
/* SO GO TO SECTION J. */

    if (k <= 3) {
	goto L3;
    }

/* (H) */
/* CONSIDER THE ADJACENT BOUNDARY POINT OF THE NEXT EDGE OF THE */
/* POLYGON.  CALL ITS INDEX NUMBER K3 AND SEE IF ITS CLOSER TO */
/* THE CURRENT EDGE THAN P(J1). */

L6:
    k3 = k2 + 1;
    if (k3 > k) {
	k3 = 1;
    }
    pk3 = b[k3];
    term = (y[pk3] - y[b1]) * (x[b2] - x[b1]) - (x[pk3] - x[b1]) * (y[b2] - y[
	    b1]);
    if (term <= 0.) {
	goto L2;
    }
/* Computing 2nd power */
    r__1 = x[pk3] - x[b1];
/* Computing 2nd power */
    r__2 = y[pk3] - y[b1];
/* Computing 2nd power */
    r__3 = x[pk3] - x[b2];
/* Computing 2nd power */
    r__4 = y[pk3] - y[b2];
    d = sqrt(r__1 * r__1 + r__2 * r__2) + sqrt(r__3 * r__3 + r__4 * r__4);
    if (j1 != 0 && d1 < d) {
	goto L2;
    }
    j1 = k3;
    d1 = d;
    bflag = 1;

/* (I) */
/* CONSIDER THE ADJACENT BOUNDARY POINT OF THE PREVIOUS EDGE OF */
/* THE POLYGON.  CALL ITS INDEX NUMBER K0 AND SEE IF ITS CLOSER */
/* TO THE CURRENT EDGE THAN P(J1) AND B(K3). */

L2:
    k0 = k1 - 1;
    if (k0 < 1) {
	k0 = k;
    }
    pk0 = b[k0];
    term = (y[pk0] - y[b1]) * (x[b2] - x[b1]) - (x[pk0] - x[b1]) * (y[b2] - y[
	    b1]);
    if (term <= 0.) {
	goto L3;
    }
/* Computing 2nd power */
    r__1 = x[pk0] - x[b1];
/* Computing 2nd power */
    r__2 = y[pk0] - y[b1];
/* Computing 2nd power */
    r__3 = x[pk0] - x[b2];
/* Computing 2nd power */
    r__4 = y[pk0] - y[b2];
    d = sqrt(r__1 * r__1 + r__2 * r__2) + sqrt(r__3 * r__3 + r__4 * r__4);
    if (j1 != 0 && d1 < d) {
	goto L3;
    }
    j1 = k0;
    d1 = d;
    bflag = -1;
L3:

/* (J) */
/* SKIP THE NEXT SECTION IF J1 IS STILL ZERO, SINCE A CANDIDATE */
/* POINT FOR TRIANGULATION WITH EDGE B1,B2 WAS NOT FOUND. */

    if (j1 == 0) {
	goto L9;
    }

/* (K,L) */
/* IF THE SEARCH FOR A CANDIDATE POINT HAS ALREADY CONSIDERED EACH */
/* BOUNDARY EDGE AT LEAST ONCE (KT.GT.K) OR IF THE BOUNDARY IS */
/* BEING CHECKED FOR CONCAVE EDGES (J=0), THEN THE NEXT SECTION */
/* (SECTION M) CAN BE OMMITTED. */

    if (kt > k || j == 0) {
	goto L9;
    }

/* (M) */
/* AT THIS POINT THE USER MAY INSERT ANY ADDITIONAL CONSTRAINT */
/* ON THE TRIANGLE TO BE FORMED BY THE POINT PJ1.  IF THE */
/* CANDIDATE TRIANGLE FAILS THE TEST, IT IS DELETED FROM */
/* CONSIDERATION BY SETTING THE VARIABLE J1 TO ZERO. */

L9:

/* (N,O) */
/* THE NEXT PROCEDURE CHECKS ALL BOUNDARY EDGES OF THE POLYGON */
/* FOR INTERSECTION WITH THE CANDIDATE TRIANGLE.  IF ANY EXISTING */
/* BOUNDARY EDGE INTERSECTS ANY OF THE EDGES TO BE FORMED BY THE */
/* CANDIDATE TRIANGLE, THEN THE CANDIDATE POINT IS REJECTED.  IF */
/* BFLAG IS NOT ZERO, THEN THE EDGE DEFINED BY J1=K0 OR J1=K3 IS */
/* EXEMPT FORM THIS TEST. */

/* IF THERE ARE THREE OR LESS EXISTING BOUNDARY EDGES OR IF */
/* J1 HAS BEEN SET TO ZERO, THIS TEST IS OMMITTED. */

    if (k <= 3 || j1 == 0) {
	goto L7;
    }
    if (bflag == 0) {
	nq = p[j1];
    }
    if (bflag == 1) {
	nq = b[k3];
    }
    if (bflag == -1) {
	nq = b[k0];
    }
    i__1 = k;
    for (kcnt = 1; kcnt <= i__1; ++kcnt) {
	if (kcnt == k1) {
	    goto L108;
	}
	kn = kcnt + 1;
	if (kcnt == k) {
	    kn = 1;
	}
	if (bflag == -1 && (kcnt == k0 || kn == k0)) {
	    goto L108;
	}
	if (bflag == 1 && (kcnt == k3 || kn == k3)) {
	    goto L108;
	}
	p1 = b[kcnt];
	p2 = b[kn];
	for (jcnt = 1; jcnt <= 2; ++jcnt) {
	    if (jcnt == 1 && (bflag == 0 || bflag == 1) && kcnt == k0) {
		goto L108;
	    }
	    if (jcnt == 2 && (bflag == 0 || bflag == -1) && kcnt == k2) {
		goto L108;
	    }
	    bj = b1;
	    if (jcnt == 2) {
		bj = b2;
	    }
	    xqb = x[nq] - x[bj];
	    yqb = y[nq] - y[bj];
	    x12 = x[p1] - x[p2];
	    y12 = y[p1] - y[p2];
	    d = xqb * y12 - yqb * x12;
	    if (d == 0.) {
		goto L8;
	    }
	    x1b = x[p1] - x[bj];
	    y1b = y[p1] - y[bj];
	    s = (x1b * y12 - y1b * x12) / d;
	    if (s < 0. || s > 1.) {
		goto L8;
	    }
	    tc = (xqb * y1b - yqb * x1b) / d;
	    if (tc < 0. || tc > 1.) {
		goto L8;
	    }
	    j1 = 0;
	    goto L7;
L8:
	    ;
	}
L108:
	;
    }
L7:

/* (P,Q) */
/* IF J1 IS ZERO, THEN THE CANDIDATE POINT DID NOT PASS THE ABOVE */
/* TESTS OR NO POINT WAS FOUND.  IF BFLAG IS NOT ZERO, THEN A */
/* POINT ON THE BOUNDARY WAS FOUND. */

    if (j1 == 0) {
	goto L10;
    }
    if (bflag < 0) {
	goto L150;
    } else if (bflag == 0) {
	goto L160;
    } else {
	goto L4;
    }

/* THE TRIANGULATED POINT IS OUTSIDE THE BOUNDARY.  ESTABLISH TWO */
/* NEW EDGES, A NEW BOUNDARY POINT AND DELETE ONE POINT FROM */
/* OUTSIDE THE BOUNDARY. */

L160:
    if (*nn > 0) {
/* Computing MIN */
	i__1 = p[j1], i__2 = b[k1];
	e[*l + 1 + e_dim1] = min(i__1,i__2);
/* Computing MAX */
	i__1 = p[j1], i__2 = b[k1];
	e[*l + 1 + (e_dim1 << 1)] = max(i__1,i__2);
/* Computing MIN */
	i__1 = p[j1], i__2 = b[k2];
	e[*l + 2 + e_dim1] = min(i__1,i__2);
/* Computing MAX */
	i__1 = p[j1], i__2 = b[k2];
	e[*l + 2 + (e_dim1 << 1)] = max(i__1,i__2);
    }
    kt = 0;
    *l += 2;
    ++(*m);
/* Computing MIN */
    i__1 = p[j1], i__2 = b[k1], i__1 = min(i__1,i__2), i__2 = b[k2];
    t[*m + t_dim1] = min(i__1,i__2);
    t[*m + (t_dim1 << 1)] = midc_(&p[j1], &b[k1], &b[k2]);
/* Computing MAX */
    i__1 = p[j1], i__2 = b[k1], i__1 = max(i__1,i__2), i__2 = b[k2];
    t[*m + t_dim1 * 3] = max(i__1,i__2);
    if (k1 == k) {
	goto L140;
    }
    km = k;
    kp1 = k1 + 1;
L147:
    b[km + 1] = b[km];
    --km;
    if (km >= kp1) {
	goto L147;
    }
L140:
    b[k1 + 1] = p[j1];
    ++k;
    --j;
    if (j1 > j) {
	goto L10;
    }
    i__1 = j;
    for (jcnt = j1; jcnt <= i__1; ++jcnt) {
/* L144: */
	p[jcnt] = p[jcnt + 1];
    }
    goto L10;

/* (S) */
/* THE TRIANGULATED POINT IS THE NEXT POINT ON THE BOUNDARY. */
/* ESTABLISH ONE NEW EDGE (FROM B(K1) TO B(K3)), ONE NEW */
/* TRIANGLE (FROM B(K1) TO B(K2) TO B(K3)), AND DELETE ONE POINT */
/* FROM THE BOUNDARY (B(K2)). */

L4:
    if (*nn > 0) {
/* Computing MIN */
	i__1 = b[k3], i__2 = b[k1];
	e[*l + 1 + e_dim1] = min(i__1,i__2);
/* Computing MAX */
	i__1 = b[k3], i__2 = b[k1];
	e[*l + 1 + (e_dim1 << 1)] = max(i__1,i__2);
    }
    kk = 0;
    kknt = 0;
    kt = 0;
    ++(*l);
    --k;
    ++(*m);
/* Computing MIN */
    i__1 = b[k1], i__2 = b[k2], i__1 = min(i__1,i__2), i__2 = b[k3];
    t[*m + t_dim1] = min(i__1,i__2);
    t[*m + (t_dim1 << 1)] = midc_(&b[k1], &b[k2], &b[k3]);
/* Computing MAX */
    i__1 = b[k1], i__2 = b[k2], i__1 = max(i__1,i__2), i__2 = b[k3];
    t[*m + t_dim1 * 3] = max(i__1,i__2);
    if (k2 > k) {
	goto L155;
    }
    i__1 = k;
    for (kcnt = k2; kcnt <= i__1; ++kcnt) {
/* L151: */
	b[kcnt] = b[kcnt + 1];
    }
L155:
    if (k2 == 1) {
	--k1;
    }
    goto L10;

/* (R) */
/* THE TRIANGULATED POINT IS THE PREVIOUS POINT ON THE BOUNDARY. */
/* ESTABLISH A NEW EDGE (FROM B(K0) TO B(K2)), ONE NEW TRIANGLE */
/* (FROM B(K0) TO B(K1) TO B(K2)), AND DELETE ONE POINT FROM THE */
/* BOUNDARY (B(K1)) */

L150:
    if (*nn > 0) {
/* Computing MIN */
	i__1 = b[k0], i__2 = b[k2];
	e[*l + 1 + e_dim1] = min(i__1,i__2);
/* Computing MAX */
	i__1 = b[k0], i__2 = b[k2];
	e[*l + 1 + (e_dim1 << 1)] = max(i__1,i__2);
    }
    kk = 0;
    kknt = 0;
    kt = 0;
    ++(*l);
    --k;
    ++(*m);
/* Computing MIN */
    i__1 = b[k0], i__2 = b[k1], i__1 = min(i__1,i__2), i__2 = b[k2];
    t[*m + t_dim1] = min(i__1,i__2);
    t[*m + (t_dim1 << 1)] = midc_(&b[k0], &b[k1], &b[k2]);
/* Computing MAX */
    i__1 = b[k0], i__2 = b[k1], i__1 = max(i__1,i__2), i__2 = b[k2];
    t[*m + t_dim1 * 3] = max(i__1,i__2);
    if (k1 > k) {
	goto L157;
    }
    i__1 = k;
    for (kcnt = k1; kcnt <= i__1; ++kcnt) {
/* L158: */
	b[kcnt] = b[kcnt + 1];
    }
L157:
    --k1;
    if (k1 < 1) {
	k1 = k;
    }

/* (T) */
/* IF THERE ARE ANY POINTS REMAINING OUTSIDE THE BOUNDARY, THEN */
/* REPEAT THE PROCEDURE FOR THE NEXT EDGE. */

L10:
    if (j > 0 && j1 != 0) {
	goto L12;
    }
    if (j > 0) {
	goto L11;
    }

/* (U,V,W) */
/* ALL POINTS HAVE BEEN TRIANGULATED.  CHECK THAT ALL BOUNDARY */
/* EDGES FORM A CONCAVE POLYGON. */

    if (kk != 0) {
	goto L55;
    }
    kk = 1;
    kl = 0;
L55:
    ++kknt;
    if (kknt > n) {
	goto L170;
    }
L5:
    ++kl;
    k2 = kl + 1;
    if (k2 > k) {
	k2 = 1;
    }
    k1 = kl - 1;
    if (k1 < 1) {
	k1 = k;
    }
    pkl = b[kl];
    b1 = b[k1];
    b2 = b[k2];
    term = (y[pkl] - y[b1]) * (x[b2] - x[b1]) - (x[pkl] - x[b1]) * (y[b2] - y[
	    b1]);
    if (term < 0.) {
	goto L11;
    }
    if (kl < k) {
	goto L5;
    }

/* (X) */
/* THE TRIANGULATION IS COMPLETE AND HAS BEEN CHECKED FOR A */
/* CONCAVE BOUNDARY.  NOW IDENTIFY THE BOUNDARY EDGES. */

    if (*nn < 0) {
	return 0;
    }
L170:
    i__1 = *l;
    for (lcnt = 1; lcnt <= i__1; ++lcnt) {
	be[lcnt] = 0;
	kl = 0;
L21:
	++kl;
	if (e[lcnt + e_dim1] != b[kl]) {
	    goto L22;
	}
/* % */
	k1 = kl + 1;
	if (k1 > k) {
	    k1 = 1;
	}
	if (e[lcnt + (e_dim1 << 1)] != b[k1]) {
	    goto L162;
	}
/* % */
	be[lcnt] = 1;
	goto L23;
L162:
	k1 = kl - 1;
	if (k1 < 1) {
	    k1 = k;
	}
	if (e[lcnt + (e_dim1 << 1)] != b[k1]) {
	    goto L22;
	}
/* % */
	if (*nn > 0) {
	    be[lcnt] = 1;
	}
	goto L23;
L22:
	if (kl < k) {
	    goto L21;
	}
L23:
	;
    }

/* (Y) */
/* FINALLY, ESTABLISH THE INDICES OF ADJACENT EDGES FOR EACH */
/* EDGE IN THE TRIANGULATION.  EACH BOUNDARY EDGE WILL HAVE TWO */
/* ADJACENT EDGES - EACH INTERIOR EDGE WILL HAVE FOUR. */

    for (ll = 1; ll <= 4; ++ll) {
	i__1 = *l;
	for (lcnt = 1; lcnt <= i__1; ++lcnt) {
/* L190: */
	    te[lcnt + ll * te_dim1] = 0;
	}
    }
    i__1 = *m;
    for (mcnt = 1; mcnt <= i__1; ++mcnt) {
	i__2 = *l;
	for (ll = 1; ll <= i__2; ++ll) {
	    if (e[ll + e_dim1] == t[mcnt + t_dim1] && e[ll + (e_dim1 << 1)] ==
		     t[mcnt + (t_dim1 << 1)]) {
		l1 = ll;
	    }
	    if (e[ll + e_dim1] == t[mcnt + (t_dim1 << 1)] && e[ll + (e_dim1 <<
		     1)] == t[mcnt + t_dim1 * 3]) {
		l2 = ll;
	    }
	    if (e[ll + e_dim1] == t[mcnt + t_dim1] && e[ll + (e_dim1 << 1)] ==
		     t[mcnt + t_dim1 * 3]) {
		l3 = ll;
	    }
/* L192: */
	}
	lambda = 0;
	if (te[l1 + te_dim1] != 0) {
	    lambda = 2;
	}
	te[l1 + (lambda + 1) * te_dim1] = l2;
	te[l1 + (lambda + 2) * te_dim1] = l3;
	lambda = 0;
	if (te[l2 + te_dim1] != 0) {
	    lambda = 2;
	}
	te[l2 + (lambda + 1) * te_dim1] = l1;
	te[l2 + (lambda + 2) * te_dim1] = l3;
	lambda = 0;
	if (te[l3 + te_dim1] != 0) {
	    lambda = 2;
	}
	te[l3 + (lambda + 1) * te_dim1] = l1;
	te[l3 + (lambda + 2) * te_dim1] = l2;
/* L191: */
    }

    return 0;
} /* triangc_ */


integer midc_(i, j, k)
integer *i, *j, *k;
{
    /* System generated locals */
    integer ret_val;


/* THIS FUNCTION SUBPROGRAM IS USED BY THE TRIANGULATION ALGORITHM */
/* TO FIND THE MIDDLE VALUE OF THE THREE INTEGER ARGUMENTS (THE */
/* VALUE WHICH IS NEITHER A MINIMUM OR A MAXIMUM).  I, J AND K ARE */
/* ARE ASSUMED TO BE DISCRETE VALUES WITH NO TWO EQUAL. */

    if (*j < *i && *i < *k) {
	goto L100;
    }
    if (*k < *i && *i < *j) {
	goto L100;
    }
    if (*i < *j && *j < *k) {
	goto L200;
    }
    if (*k < *j && *j < *i) {
	goto L200;
    }
    ret_val = *k;
    return ret_val;
L100:
    ret_val = *i;
    return ret_val;
L200:
    ret_val = *j;
    return ret_val;
} /* midc_ */

