
/* *** LAST REVISED ON 20-JAN-1994 07:24:49.82 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]CVAX3DX.C */

#include "my.h"


/* Common Block Declarations */

extern struct {
    real a1, a2, a3, b1, b2, b3, b4;
} plt3b_;

#define plt3b_1 plt3b_

#define WORK_DIM 5000 /* memory buffer size */

/* Table of constant values */
static integer c_n2 = -2;
static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__4 = 4;
static real c_b7 = (float)1.5;
static real c_b8 = (float)1.;
static real c_b12 = (float)0.;
static real c_b61 = (float).15;
static real c_b62 = (float)5.02;
static real c_b71 = (float)90.;
static real c_b142 = (float)-.12;

/* Subroutine */ int cvax3dx_(a, inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
	iflag, iaxis, clow, nlev, cval, nch, nmin, iline, ipls, xt, nxt, 
	xastart, xaend, tx, tsx, fdx, yt, nyt, ty, tsy, fdy, zt, nzt, zastart,
	 zaend, tz, tsz, fdz, aminin, amaxin, icol)
real *a;
integer *inx, *inz, *nx, *nz;
real *alpha, *beta, *xh, *yh, *zh;
integer *iflag, *iaxis;
real *clow;
integer *nlev;
real *cval;
integer *nch, *nmin, *iline, *ipls;
char *xt;
integer *nxt;
real *xastart, *xaend, *tx, *tsx, *fdx;
char *yt;
integer *nyt;
real *ty, *tsy, *fdy;
char *zt;
integer *nzt;
real *zastart, *zaend, *tz, *tsz, *fdz, *aminin, *amaxin;
integer *icol;
{
    /* Initialized data */

    static real tpi = (float)3.141592654;
    static logical repeat = FALSE_;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    real r__1, r__2;

    /* External functions */

    /* Builtin functions */
    double atan2(), sqrt(), sin(), cos();
    extern /* Subroutine */ int plot_(), hlt3d_(), plt3d_(), axis3_();
    extern /* Subroutine */ int scale_(), frame_(), cterm_();
    extern /* Subroutine */ int nxtvu_();
    extern /* Subroutine */ int newpen_(), gcontr_(), plotnd_();

    /* Local variables */
    static integer iaff, nadd, nlab;
    static real aamin, aamax;
    static integer ierr;
    static real xlen, zlen, ylen;
    static real zlen1;
    static integer i, iafff, k;
    static integer ilast, jlast, i1, j1, n1;
    static real w2[WORK_DIM], x1, y1;
    static real ae;
    static integer ic[4], jf;
    static real as[2], cv;
    static integer nl;
    static real dy;
    static integer iz, ix, nw;
    static real xp, yp, yscale;
    static real xp1, yp1, daa;
    static integer iaf, jff;
    static real ang;
    static integer icl, ill, ilu;
    static real val1, val2;
    static integer nw1d, nw2d;

/* 	CREATED BY D. LONG     AUG 1987	AT JPL */

/* 	ROUTINE TO PLOT DATA IN 3-D MESH OR HISTOGRAM COLUMN FORM */
/* 	WITH HIDDEN LINE REMOVAL USING PLT3D OR HLT3D */
/* 	WITH A CONTOUR PLOT UNDERNEATH USING GCONTR */

/* 	COORDINATE SYSTEM IS:		Y */
/* 			VARIABLE NAMES:	| */
/* 				      Z/ \X */

/* 	A	REAL ARRAY A(INX,INZ) CONTAINING VERTICAL HEIGHT DATA */
/* 	INX,INZ INTEGERS DIMENSION OF A ARRAY */
/* 	NX,NZ	INTEGERS INDICATING SIZE OF A ARRAY TO PLOT */
/* 	ALPHA	REAL ANGLE (IN DEGREES) OF X AXIS (NX) (ALTITUDE) */
/* 	BETA	REAL ANGLE (IN DEGREES) OF Z AXIS (NZ) (AZIMUTH) */
/* 	XH,YH,ZH REAL LENGTH OF EACH AXIS */
/* 	IFLAG	INTEGER */
/* 		>10000	REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER */
/* 		< 0	REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT */
/* 		= 0	CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT */
/* 		> 0	SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED) */
/* 	(ONE'S DIGIT) = 2 USE PEN COLOR CONTROL ARRAY */
/* 		      = 1 DO NOT USE PEN COLOR ARRAY */
/* 	(TEN'S)       = 0 MESH (PLT3D) USED */
/* 		      = 1 HISTOGRAM (MLT3D) USED */
/* 	(HUNDREDS'S DIGIT) = 0 ASK WHICH SCREEN DEVICE TO USE */
/* 		           <>0 SCREEN DEVICE CODE NUMBER */
/* 	IAXIS	INTEGER AXIS OPTION FLAG */
/* 			= 0	DO NOT PLOT AXIS--FOLLOWING VARIABLES NOT ACCESSED */
/* 			< 0	PLOT AXIS, USE INPUT Y AXIS SCALE--FOLLOWING VARIABLES ACCESSED 
*/
/*			> 0	PLOT AXIS, USE COMPUTED Y AXIS SCALE--FOLLOWING VARIABLES ACCESSE
D*/
/* 	(ONE'S DIGIT)	= 1	PLOT AXIS, Y AXIS SCALE--VARIABLES ACCESSED */
/* 			= 2	PLOT AXIS, AUTO SCALE Y AXIS--VARIABLES ACCESSED */
/* 	(TEN'S DIGIT)	= 0	CONTOUR AXES, MESH AXES, BACK PLANE PLOTTED */
/* 			= 1	CONTOUR AXES, MESH AXES PLOTTED W/O BACK PLANE */
/* 			= 2	CONTOUR AXES PLOTTED W/O MESH AXES */
/* 			= 3	MESH AXES PLOTTED W/O BACK PLANE OR CONTOUR AXES */
/* 			= 4	MESH AXES AND BACK PLANE W/O CONTOUR AXES */
/* 			= 5	CONTOUR AXES W/BACKPLANE AND AXIS LABELED */
/* 				 BUT NO X,Z LABELING ON MESH AXES */
/* 	(HUNDRED'S)	= 0	DEFAULT AXIS PARAMETERS */
/* 			= 1	SPECIALIZED AXIS3 PARAMETERS */
/* 	(THOUSAND'S)	= 0	BACKPLANE AXIS ON BOTH SIDES */
/* 			= 1	BACKPLANCE AXIS ONLY ON LEFT SIDE */
/* 			= 2	BACKPLANCE AXIS ONLY ON RIGHT SIDE */
/* 	CLOW		REAL VERTICAL DISTANCE BETWEEN CONTOUR AND SURFACE PLOT */
/* 	NLEV		INT  NUMBER OF CONTOUR LEVELS */
/* 			     > 0 NUMBER OF LEVELS IN CVAL */
/* 			     = 0 NO CONTOUR PLOT PRODUCED */
/* 			     < 0 IABS(NLEV) LEVELS COMPUTED */
/* 				 FROM (MAX(A)-MIN(A))/ABS(NLEV-1) */
/* 	CVAL		REAL ARRAY OF CONTOUR LEVELS, IF NLEV<0 */
/* 			     CONTOURS USED ARE RETURNED */
/* 	NCH		INT  CONTOUR LABEL OPTION */
/* 			     > 0 LABEL WITH ALPHABETIC CHAR */
/* 			     = 0 NO CONTOUR LABELS */
/* 			     < 0 LABEL WITH CONTOUR VALUE, NCH=# DIGITS */
/* 				 TO RIGHT OF DECIMAL POINT */
/* 	NMIN		INT  MINIMUM NUMBER OF CELLS BEFORE CONTOUR LABELED */
/* 			      < 0 LINE TYPES ARE USED */
/* 			      > 0 LINE TYPES NOT USED */
/* 	ILINE		INT  LINE TYPE/WIDTH ARRAY */
/* 				ILINE(1) = UNDERSIDE OF SURFACE */
/* 				ILINE(2) = INTERCONNECT PATH (RETURN IF USED) */
/* 				ILINE(3) = CONTOUR LINE 1 */
/* 				ILINE(4) = CONTOUR LINE 2 */
/* 				 ...        (LAST RETURNED IF PATH NOT USED) */
/* 	IPLS		INT  CONTROL FOR LINE PATH INTERCONNECTING SURFACES */
/* 			     AND CONTOUR PLOT */
/* 				IPLS(1) = PLOT CODE POINT 1 */
/* 					   = 0 END OF LIST */
/* 					   = 3 MOVE TO, PEN UP */
/* 					   = 2 MOVE TO, PEN DOWN */
/* 				IPLS(2) = X ARRAY INDEX */
/* 				IPLS(3) = Z ARRAY INDEX */
/* 				IPLS(4) = PLOT CODE POINT 2 */
/* 				 ... */
/* FOLLOWING ONLY ACCESSED IF IAXIS IS NOT ZERO */
/* 	XT,YT,ZT	BYTE STRINGS FOR AXIS TITLES */
/* 	NXT,NYT,NZT	INT  LENGTH OF AXIS TITLES */
/* 			     IF ZERO THEN THAT AXIS NOT PLOTTED */
/* 	XASTART,ZASTART	REAL AXIS START VALUES */
/* 	XAEND,ZAEND	REAL AXIS END VALUES */
/* FOLLOWING ONLY ACCESSED IF HUNDRED'S DIGIT OF IAXIS=1 */
/* 	TX,TY,TZ	REAL TICK MARK PATTERN (SEE AXIS3) */
/* 	TSX,TSY,TSZ	REAL SIZE OF TITLE AND NUMBERS OF AXIS */
/* 			  IF <0 DO NOT AUTO-SCALE AXIS BY (x10^POWER) */
/* 	FDX,FDY,FDZ	REAL AXIS NUMBER LABEL FORMAT (SEE AXIS3) */
/* 	AMININ,AMAXIN 	REAL YAXIS SCALING FACTORS (ONLY NEEDED IF IAXIS < 0) 
*/
/* 	ICOL		INTEGER COLOR CONTROL (ACCESSED IF MOD(IFLAG,10)=2) */
/* 				ICOL(1) AXIS LINE COLOR */
/* 				ICOL(2) AXIS NUMERIC LABEL COLOR */
/* 				ICOL(3) AXIS LABEL COLOR */
/* 				ICOL(4) AXIS EXPONENT COLOR */
/* 				ICOL(5) BACK PLANE COLOR */
/* 				ICOL(6) PLOT COLOR UPPER SURFACE */
/* 				ICOL(7) PLOT COLOR LOWER SURFACE */
/* 				ICOL(8) CONTOUR LINE 1 COLOR */
/* 				ICOL(9) CONTOUR LINE 2 COLOR */
/* 				 ...     (LAST VALUE RETURNED) */

    /* Parameter adjustments */
    --icol;
    --ipls;
    --iline;
    --cval;
    a_dim1 = *inx;
    a_offset = a_dim1 + 1;
    a -= a_offset;

/* 	INTIALIZE ROUTINE AND PLOT PACKAGE IF ACCESSED */

    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();
	}		/* CLOSE PLOTTER */
	repeat = FALSE_;
	return 0;
    }

    if (*iaxis < 0) {
	aamax = *amaxin;
	aamin = *aminin;
    } else {
	aamax = a[a_dim1 + 1];
	aamin = a[a_dim1 + 1];
	i__1 = *nz;
	for (iz = 1; iz <= i__1; ++iz) { /* DETERMINE MAX,MIN ARRAY VALUES */
	    i__2 = *nx;
	    for (ix = 1; ix <= i__2; ++ix) {	/* Computing MAX */
		r__1 = aamax, r__2 = a[ix + iz * a_dim1];
		aamax = dmax(r__1,r__2);		/* Computing MIN */
		r__1 = aamin, r__2 = a[ix + iz * a_dim1];
		aamin = dmin(r__1,r__2);
/* L16: */
	    }
	}
    }
    xlen = dabs(*xh);
    zlen = dabs(*zh);
    ylen = dabs(*yh);
    if (abs(*iaxis) % 10 == 2) {		/* SMOOTH SCALE FACTORS */
	as[0] = aamax;
	as[1] = aamin;
	scale_(as, &ylen, &c__2, &c__1, &c__1, &aamin, &daa);
	aamax = ylen * daa + aamin;
    }
    yscale = (float)1.;
    if (aamax - aamin != (float)0.) {
	yscale = ylen / (aamax - aamin);
    }

/* 	INTIALIZE PLOT PACKAGE */

    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = jf / 100;					/* GRAPHICS DEVICE CODE */
	frame_(&c__3, &ilu, &c_b7, &c_b8, &c_b8);	/* INTIALIZE LONGLIB */
    } else {
	cterm_(&c_n1);			/* PUT TERMINAL IN PLOT MODE */
    }

    iafff = abs(*iaxis) / 1000;		/* BACKPLANE AXIS FLAG */
    iaff = abs(*iaxis) / 100 % 10;	/* AXIS TYPE FLAG */
    iaf = abs(*iaxis) % 100 / 10;	/* BACK PANEL, AXES FLAG */
    jff = jf % 100 / 10;		/* SURFACE FLAG */
    jf %= 10;				/* COLOR FLAG */
    nlab = 0;
    if (iaf == 5) {
	nlab = 100;
    }

/* 	PLOT MESH SURFACE WITH SIMPLE HIDDEN LINE REMOVAL ROUTINE */

    nw1d = 1;
    nw2d = WORK_DIM - nw1d;
    if (jff == 0) {					/* PLT3D */
	nw1d = 1 + min(*nx,*nz) << 2;
	nw2d = WORK_DIM - nw1d - 1;
	if (nw2d < nw1d) {
	    printf("*** CVAX3DX insufficient memory error 1 %d %d %d %d\n",
			nw1d,nw2d,*nx,*nz);
	    goto L42;
	}
    }
    nw = nw2d + 1;
    r__1 = *beta + (float)180.;
    xp = xlen / (float)2. * cos(0.0174533 * *alpha) + (float)2.;
    yp = -(doublereal)(xlen / (float)2. + ylen / (float)2.) * 
		sin( 0.0174533 * *alpha) * 
	    sin( 0.0174533 * r__1) - yscale * aamin + *clow;

/* 	PLOT LOWER SIDE OF SURFACE */

    if (jf == 2) {
	r__1 = (real) icol[7];
	plot_(&r__1, &c_b12, &c__0);
    }			/* COLOR SURFACE LOWER */
    if (*nmin < 0) {
	newpen_(&iline[1]);
    }
    if (jff == 0) {
	r__1 = *beta + (float)180.;
	r__2 = - xlen;
	plt3d_(&a[a_offset], inx, inz, nx, nz, &w2[nw - 1], &nw1d, w2, &nw2d, 
		alpha, &r__1, &r__2, &xp, &zlen, &yp, &yscale, &c_b12, &ierr);

    } else {
	r__1 = *beta + (float)180.;
	r__2 = - xlen;
	hlt3d_(&a[a_offset], inx, inz, nx, nz, w2, &nw1d, w2, &nw2d, alpha, &
		r__1, &r__2, &xp, &zlen, &yp, &yscale, &c_b12, &ierr);
    }
    if (ierr != 0) {
	    printf("*** CVAX3DX memory limit error %d at 2\n",ierr);
	goto L42;
    }

/* 	IF WE ARE SHOWING BACK PANEL, THEN PLOT THE PORTION UNDER SURFACE */

    if (iaf != 2 && *iaxis != 0) {
	dy = (float)1. / yscale;
	if (*nyt > 0) {			/* PLOT Y AXIS */
	    if (iaff == 1) {
		n1 = (integer) (*ty);	/* MAJOR AXIS TICKS */
	    } else {
		n1 = (integer) (ylen + (float).5) + 1;
	    }
	    if (iaf == 0 || iaf == 4 || iaf == 5) {
		if (jf == 2) {
		    r__1 = (real) icol[5];
		    plot_(&r__1, &c_b12, &c__0);
		}
		if (*nmin < 0) {
		    newpen_(&c__1);
		}
		val2 = (n1 - 1) * dy + aamin;
		w2[nw - 1] = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + 
			plt3b_1.a3;
		w2[nw] = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + plt3b_1.b3 * 
			val2 + plt3b_1.b4;
		w2[nw + 1] = plt3b_1.a1 * c__1 + plt3b_1.a2 * c__1 + 
			plt3b_1.a3;
		w2[nw + 2] = plt3b_1.b1 * c__1 + plt3b_1.b2 * c__1 + 
			plt3b_1.b3 * val2 + plt3b_1.b4;
		w2[nw + 3] = plt3b_1.a1 * c__1 + plt3b_1.a2 * *nx + 
			plt3b_1.a3;
		w2[nw + 4] = plt3b_1.b1 * c__1 + plt3b_1.b2 * *nx + 
			plt3b_1.b3 * val2 + plt3b_1.b4;
		nxtvu_(&c_n2, &w2[nw - 1], &c__3, w2, &nw2d, &ierr);
		if (ierr != 0) {
		    goto L42;
		}
		i__2 = n1 - 1;
		for (k = 1; k <= i__2; ++k) {
		    val1 = (n1 - k - 1) * dy + aamin;
		    w2[nw - 1] = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + 
			    plt3b_1.a3;
		    w2[nw] = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + 
			    plt3b_1.b3 * val2 + plt3b_1.b4;
		    w2[nw + 1] = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + 
			    plt3b_1.a3;
		    w2[nw + 2] = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + 
			    plt3b_1.b3 * val1 + plt3b_1.b4;
		    w2[nw + 3] = plt3b_1.a1 * c__1 + plt3b_1.a2 * c__1 + 
			    plt3b_1.a3;
		    w2[nw + 4] = plt3b_1.b1 * c__1 + plt3b_1.b2 * c__1 + 
			    plt3b_1.b3 * val1 + plt3b_1.b4;
		    w2[nw + 5] = plt3b_1.a1 * c__1 + plt3b_1.a2 * c__1 + 
			    plt3b_1.a3;
		    w2[nw + 6] = plt3b_1.b1 * c__1 + plt3b_1.b2 * c__1 + 
			    plt3b_1.b3 * val2 + plt3b_1.b4;
		    nxtvu_(&c_n2, &w2[nw - 1], &c__4, w2, &nw2d, &ierr);
		    if (ierr != 0) {
			goto L42;
		    }
		    w2[nw - 1] = plt3b_1.a1 * c__1 + plt3b_1.a2 * c__1 + 
			    plt3b_1.a3;
		    w2[nw] = plt3b_1.b1 * c__1 + plt3b_1.b2 * c__1 + 
			    plt3b_1.b3 * val1 + plt3b_1.b4;
		    w2[nw + 1] = plt3b_1.a1 * c__1 + plt3b_1.a2 * *nx + 
			    plt3b_1.a3;
		    w2[nw + 2] = plt3b_1.b1 * c__1 + plt3b_1.b2 * *nx + 
			    plt3b_1.b3 * val1 + plt3b_1.b4;
		    w2[nw + 3] = plt3b_1.a1 * c__1 + plt3b_1.a2 * *nx + 
			    plt3b_1.a3;
		    w2[nw + 4] = plt3b_1.b1 * c__1 + plt3b_1.b2 * *nx + 
			    plt3b_1.b3 * val2 + plt3b_1.b4;
		    nxtvu_(&c_n2, &w2[nw - 1], &c__3, w2, &nw2d, &ierr);
		    if (ierr != 0) {
			goto L42;
		    }
/* L338: */
		}
	    }
	}
    }

/* 	PLOT UPPER SIDE OF SURFACE */

    if (jf == 2) {
	r__1 = (real) icol[6];
	plot_(&r__1, &c_b12, &c__0);
    }		/* COLOR SURFACE UPPER */
    if (*nmin < 0) {
	newpen_(&c__1);
    }
    if (jff == 0) {
	r__1 = *beta + (float)180.;
	plt3d_(&a[a_offset], inx, inz, nx, nz, &w2[nw - 1], &nw1d, w2, &nw2d, 
		alpha, &r__1, &xlen, &xp, &zlen, &yp, &yscale, &c_b12, &ierr);

    } else {
	r__1 = *beta + (float)180.;
	hlt3d_(&a[a_offset], inx, inz, nx, nz, w2, &nw1d, w2, &nw2d, alpha, &
		r__1, &xlen, &xp, &zlen, &yp, &yscale, &c_b12, &ierr);
    }
    if (ierr != 0) {
	goto L42;
    }
    if (iaf != 2 && *iaxis != 0) {
	nadd = 0;
	if (jf == 2) {
	    nadd = 100000;
	    ic[0] = icol[1];
	    ic[1] = icol[2];
	    ic[2] = icol[3];
	    ic[3] = icol[4];
	}
	xp = plt3b_1.a1 * *nz + plt3b_1.a2 * *nx + plt3b_1.a3;
	yp = plt3b_1.b1 * *nz + plt3b_1.b2 * *nx + plt3b_1.b3 * aamin + 
		plt3b_1.b4;
	xp1 = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + plt3b_1.a3;
	yp1 = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + plt3b_1.b3 * aamin + 
		plt3b_1.b4;
	ang = atan2(yp - yp1, xp - xp1) * (float)180. / tpi;
	r__1 = xp - xp1;
	r__2 = yp - yp1;
	zlen1 = sqrt(r__1 * r__1 + r__2 * r__2);

	if (*nxt > 0) {					/* PLOT X AXIS */
	    if (iaff == 1) {
		i__2 = -nadd - *nxt - nlab;
		axis3_(&xp1, &yp1, xt, &i__2, &zlen1, &ang, xastart, xaend, 
			tx, tsx, fdx, ic);
	    } else {
		val1 = (integer) (xlen + (float).5) + (float)1.;
		i__2 = -nadd - *nxt - nlab;
		axis3_(&xp1, &yp1, xt, &i__2, &zlen1, &ang, xastart, xaend, &
			val1, &c_b61, &c_b62, ic);
	    }
	}
	xp1 = plt3b_1.a1 * c__1 + plt3b_1.a2 * *nx + plt3b_1.a3;
	yp1 = plt3b_1.b1 * c__1 + plt3b_1.b2 * *nx + plt3b_1.b3 * aamin + 
		plt3b_1.b4;
	ang = atan2(yp1 - yp, xp1 - xp) * (float)180. / tpi;
	r__1 = xp1 - xp;
	r__2 = yp1 - yp;
	zlen1 = sqrt(r__1 * r__1 + r__2 * r__2);

	if (*nzt > 0) {			/* PLOT Z AXIS */
	    if (iaff == 1) {
		i__2 = -nadd - *nzt - nlab;
		axis3_(&xp, &yp, zt, &i__2, &zlen1, &ang, zaend, zastart, tz, 
			tsz, fdz, ic);
	    } else {
		val1 = (integer) (zlen + (float).5) + (float)1.;
		i__2 = -(*nzt) - nlab;
		axis3_(&xp, &yp, zt, &i__2, &zlen1, &ang, zaend, zastart, &
			val1, &c_b61, &c_b62, ic);
	    }
	}

/* 	PLOT Y AXES FOR MESH SURFACE */

	dy = (float)1. / yscale;
	xp1 = plt3b_1.a1 * *nz + plt3b_1.a2 * *nx + plt3b_1.a3;
	yp1 = plt3b_1.b1 * *nz + plt3b_1.b2 * *nx + plt3b_1.b3 * aamax + 
		plt3b_1.b4;
	r__1 = xp1 - xp;
	r__2 = yp1 - yp;
	zlen1 = sqrt(r__1 * r__1 + r__2 * r__2);

	if (*nyt > 0) {			/* PLOT Y AXIS */
	    xp = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + plt3b_1.a3;	/* LEFT SIDE */
	    yp = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + plt3b_1.b3 * aamin + 
		    plt3b_1.b4;
	    xp1 = plt3b_1.a1 * c__1 + plt3b_1.a2 * *nx + plt3b_1.a3;	/* RIGHT SIDE */
	    yp1 = plt3b_1.b1 * c__1 + plt3b_1.b2 * *nx + plt3b_1.b3 * aamin + 
		    plt3b_1.b4;
	    if (iaff == 1) {
		if (iafff != 2) {
		    i__2 = *nyt + nadd;
		    axis3_(&xp, &yp, yt, &i__2, &zlen1, &c_b71, &aamin, &aamax, 
			    ty, tsy, fdy, ic);
		}
		if (iafff != 1) {
		    i__2 = -nadd - *nyt;
		    axis3_(&xp1, &yp1, yt, &i__2, &zlen1, &c_b71, &aamin, &
			    aamax, ty, tsy, fdy, ic);
		}
		n1 = (integer) (*ty);	/* MAJOR AXIS TICKS */
	    } else {
		val1 = (integer) (ylen + (float).5) + (float)1.;
		if (iafff != 2) {
		    i__2 = nadd + *nyt;
		    axis3_(&xp, &yp, yt, &i__2, &zlen1, &c_b71, &aamin, &aamax, 
			    &val1, &c_b61, &c_b62, ic);
		}
		if (iafff != 1) {
		    i__2 = -nadd - *nyt;
		    axis3_(&xp1, &yp1, yt, &i__2, &zlen1, &c_b71, &aamin, &
			    aamax, &val1, &c_b61, &c_b62, ic);
		}
		n1 = (integer) (ylen + (float).5) + 1;
	    }

/* 	PLOT BACK PANEL FOR MESH SURFACE */

	    if (iaf == 0 || iaf == 4 || iaf == 5) {
		if (jf == 2) {
		    r__1 = (real) icol[5];
		    plot_(&r__1, &c_b12, &c__0);
		}
		i__2 = n1;
		for (k = 1; k <= i__2; ++k) {
		    val1 = (k - 1) * dy + aamin;
		    w2[nw - 1] = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + 
			    plt3b_1.a3;
		    w2[nw] = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + 
			    plt3b_1.b3 * aamin + plt3b_1.b4;
		    w2[nw + 1] = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + 
			    plt3b_1.a3;
		    w2[nw + 2] = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + 
			    plt3b_1.b3 * val1 + plt3b_1.b4;
		    w2[nw + 3] = plt3b_1.a1 * c__1 + plt3b_1.a2 * c__1 + 
			    plt3b_1.a3;
		    w2[nw + 4] = plt3b_1.b1 * c__1 + plt3b_1.b2 * c__1 + 
			    plt3b_1.b3 * val1 + plt3b_1.b4;
		    w2[nw + 5] = plt3b_1.a1 * c__1 + plt3b_1.a2 * c__1 + 
			    plt3b_1.a3;
		    w2[nw + 6] = plt3b_1.b1 * c__1 + plt3b_1.b2 * c__1 + 
			    plt3b_1.b3 * aamin + plt3b_1.b4;
		    nxtvu_(&c__2, &w2[nw - 1], &c__4, w2, &nw2d, &ierr);
		    if (ierr != 0) {
			goto L42;
		    }
		    w2[nw - 1] = plt3b_1.a1 * c__1 + plt3b_1.a2 * c__1 + 
			    plt3b_1.a3;
		    w2[nw] = plt3b_1.b1 * c__1 + plt3b_1.b2 * c__1 + 
			    plt3b_1.b3 * val1 + plt3b_1.b4;
		    w2[nw + 1] = plt3b_1.a1 * c__1 + plt3b_1.a2 * *nx + 
			    plt3b_1.a3;
		    w2[nw + 2] = plt3b_1.b1 * c__1 + plt3b_1.b2 * *nx + 
			    plt3b_1.b3 * val1 + plt3b_1.b4;
		    w2[nw + 3] = plt3b_1.a1 * c__1 + plt3b_1.a2 * *nx + 
			    plt3b_1.a3;
		    w2[nw + 4] = plt3b_1.b1 * c__1 + plt3b_1.b2 * *nx + 
			    plt3b_1.b3 * aamin + plt3b_1.b4;
		    nxtvu_(&c__2, &w2[nw - 1], &c__3, w2, &nw2d, &ierr);
		    if (ierr != 0) {
			goto L42;
		    }
/* L4338: */
		}
	    }
	}
    }

/* 	DRAW AXES FOR CONTOUR PLOT */

    if (*nlev == 0) {
	goto L900;
    }
    plt3b_1.b4 -= *clow;
    if ((iaf < 3 || iaf == 5) && *iaxis != 0) {
	nadd = 0;
	if (jf == 2) {
	    nadd = 100000;
	    ic[0] = icol[1];
	    ic[1] = icol[2];
	    ic[2] = icol[3];
	    ic[3] = icol[4];
	}
	xp = plt3b_1.a1 * *nz + plt3b_1.a2 * *nx + plt3b_1.a3;
	yp = plt3b_1.b1 * *nz + plt3b_1.b2 * *nx + plt3b_1.b3 * aamin + 
		plt3b_1.b4;
	xp1 = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + plt3b_1.a3;
	yp1 = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + plt3b_1.b3 * aamin + 
		plt3b_1.b4;
	ang = atan2(yp - yp1, xp - xp1) * (float)180. / tpi;
	r__1 = xp - xp1;
	r__2 = yp - yp1;

	zlen1 = sqrt(r__1 * r__1 + r__2 * r__2);
	if (*nxt > 0) {		/* PLOT X AXIS */
	    if (iaff == 1) {
		i__2 = -nadd - *nxt;
		axis3_(&xp1, &yp1, xt, &i__2, &zlen1, &ang, xastart, xaend, 
			tx, tsx, fdx, ic);
	    } else {
		val1 = (integer) (xlen + (float).5) + (float)1.;
		i__2 = -nadd - *nxt;
		axis3_(&xp1, &yp1, xt, &i__2, &zlen1, &ang, xastart, xaend, &
			val1, &c_b61, &c_b62, ic);
	    }
	}
	plot_(&xp1, &yp1, &c__3);
	xp1 = plt3b_1.a1 * c__1 + plt3b_1.a2 * c__1 + plt3b_1.a3;
	yp1 = plt3b_1.b1 * c__1 + plt3b_1.b2 * c__1 + plt3b_1.b3 * aamin + 
		plt3b_1.b4;
	plot_(&xp1, &yp1, &c__2);
	xp1 = plt3b_1.a1 * c__1 + plt3b_1.a2 * *nx + plt3b_1.a3;
	yp1 = plt3b_1.b1 * c__1 + plt3b_1.b2 * *nx + plt3b_1.b3 * aamin + 
		plt3b_1.b4;
	plot_(&xp1, &yp1, &c__2);
	ang = atan2(yp1 - yp, xp1 - xp) * (float)180. / tpi;
	r__1 = xp1 - xp;
	r__2 = yp1 - yp;
	zlen1 = sqrt(r__1 * r__1 + r__2 * r__2);
	if (*nzt > 0) {					/* PLOT Z AXIS */
	    if (iaff == 1) {
		i__2 = -nadd - *nzt;
		axis3_(&xp, &yp, zt, &i__2, &zlen1, &ang, zaend, zastart, tz, 
			tsz, fdz, ic);
	    } else {
		val1 = (integer) (zlen + (float).5) + (float)1.;
		i__2 = -nadd - *nzt;
		axis3_(&xp, &yp, zt, &i__2, &zlen1, &ang, zaend, zastart, &
			val1, &c_b61, &c_b62, ic);
	    }
	}
    } else {

/* 	BOX CONTOUR PLOT AREA */

	if (jf == 2) {
	    r__1 = (real) icol[1];
	    plot_(&r__1, &c_b12, &c__0);
	}
	xp = plt3b_1.a1 * *nz + plt3b_1.a2 * *nx + plt3b_1.a3;
	yp = plt3b_1.b1 * *nz + plt3b_1.b2 * *nx + plt3b_1.b3 * aamin + 
		plt3b_1.b4;
	plot_(&xp, &yp, &c__3);
	xp1 = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + plt3b_1.a3;
	yp1 = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + plt3b_1.b3 * aamin + 
		plt3b_1.b4;
	plot_(&xp1, &yp1, &c__2);
	xp1 = plt3b_1.a1 * c__1 + plt3b_1.a2 * c__1 + plt3b_1.a3;
	yp1 = plt3b_1.b1 * c__1 + plt3b_1.b2 * c__1 + plt3b_1.b3 * aamin + 
		plt3b_1.b4;
	plot_(&xp1, &yp1, &c__2);
	xp1 = plt3b_1.a1 * c__1 + plt3b_1.a2 * *nx + plt3b_1.a3;
	yp1 = plt3b_1.b1 * c__1 + plt3b_1.b2 * *nx + plt3b_1.b3 * aamin + 
		plt3b_1.b4;
	plot_(&xp1, &yp1, &c__2);
	plot_(&xp, &yp, &c__2);
    }

/* 	CALL CONTOURING ROUTINE ONCE FOR EACH CONTOUR LEVEL */

    plt3b_1.b4 += plt3b_1.b3 * aamin;
    ae = (float)1.e20;
    icl = 0;
    if (*nmin < 0) {
	icl = 2;
    }
    nl = abs(*nlev);
    i__2 = nl;
    for (ix = 1; ix <= i__2; ++ix) {
	if (*nlev < 1) {		/* COMPUTE LEVELS */
	    cval[ix] = (ix - 1) * (aamax - aamin) / (nl - 1) + aamin;
	} else if (*nlev == -1) {
	    cval[ix] = aamin;
	}
	cv = cval[ix];
	if (jf == 2) {			/* COLOR */
	    r__1 = (real) icol[ix + 8];
	    plot_(&r__1, &c_b12, &c__0);
	}
	if (icl != 0) {			/* LINE TYPE */
	    ill = iline[ix + 2];
	}
	i__1 = -ix - 64;
	i__3 = abs(*nmin);
	gcontr_(&a[a_offset], inx, inz, nx, nz, &c_b8, &c_b8, &cv, &i__1, &ae,
		 w2, nch, &c_b142, &i__3, &c__0, &icl, &ill);
/* L100: */
    }

/* 	NOW DRAW INTERCONNECTING PATH LINES */

    if (ipls[1] != 0) {
	if (jf == 2) {			/* COLOR */
	    r__1 = (real) icol[8];
	    plot_(&r__1, &c_b12, &c__0);
	}
	if (icl != 0) {			/* LINE TYPE */
	    newpen_(&iline[2]);
	}
	ill = 1;
	ilast = 1;
	jlast = 1;
L150:
	i = (ill - 1) * 3 + 1;
	if (ipls[i] <= 0) {
	    goto L900;
	}
	if (ipls[i] == 2) {
	    i1 = ilast;
	    j1 = jlast;
	    r__1 = a[i1 + j1 * a_dim1] - aamin;
	    x1 = plt3b_1.a1 * j1 + plt3b_1.a2 * i1 + plt3b_1.a3;
	    r__1 = a[i1 + j1 * a_dim1] - aamin;
	    y1 = plt3b_1.b1 * j1 + plt3b_1.b2 * i1 + plt3b_1.b3 * r__1 + 
		    plt3b_1.b4 + *clow;
	    plot_(&x1, &y1, &c__3);
	    i1 = ipls[i + 1];
	    j1 = ipls[i + 2];
	    r__1 = a[i1 + j1 * a_dim1] - aamin;
	    x1 = plt3b_1.a1 * j1 + plt3b_1.a2 * i1 + plt3b_1.a3;
	    r__1 = a[i1 + j1 * a_dim1] - aamin;
	    y1 = plt3b_1.b1 * j1 + plt3b_1.b2 * i1 + plt3b_1.b3 * r__1 + 
		    plt3b_1.b4 + *clow;
	    plot_(&x1, &y1, &c__2);
	    i1 = ilast;
	    j1 = jlast;
	    x1 = plt3b_1.a1 * j1 + plt3b_1.a2 * i1 + plt3b_1.a3;
	    y1 = plt3b_1.b1 * j1 + plt3b_1.b2 * i1 + plt3b_1.b3 * c_b12 + 
		    plt3b_1.b4;
	    plot_(&x1, &y1, &c__3);
	    i1 = ipls[i + 1];
	    j1 = ipls[i + 2];
	    x1 = plt3b_1.a1 * j1 + plt3b_1.a2 * i1 + plt3b_1.a3;
	    y1 = plt3b_1.b1 * j1 + plt3b_1.b2 * i1 + plt3b_1.b3 * c_b12 + 
		    plt3b_1.b4;
	    plot_(&x1, &y1, &c__2);
	}
	i1 = ipls[i + 1];
	j1 = ipls[i + 2];
	r__1 = a[i1 + j1 * a_dim1] - aamin;
	x1 = plt3b_1.a1 * j1 + plt3b_1.a2 * i1 + plt3b_1.a3;
	r__1 = a[i1 + j1 * a_dim1] - aamin;
	y1 = plt3b_1.b1 * j1 + plt3b_1.b2 * i1 + plt3b_1.b3 * r__1 + 
		plt3b_1.b4 + *clow;
	plot_(&x1, &y1, &c__3);
	x1 = plt3b_1.a1 * j1 + plt3b_1.a2 * i1 + plt3b_1.a3;
	y1 = plt3b_1.b1 * j1 + plt3b_1.b2 * i1 + plt3b_1.b3 * c_b12 + 
		plt3b_1.b4;
	plot_(&x1, &y1, &c__2);
	ilast = ipls[i + 1];
	jlast = ipls[i + 2];
	++ill;
	goto L150;
    }

/* 	FINISH UP */
L900:
    plot_(&c_b12, &c_b12, &c__3);	/* PEN UP */
    if (*iflag > 0) {
	cterm_(&c__2);			/* CLEAR TERMINAL */
	plotnd_();			/* CLOSE PLOT OUTPUT */
	repeat = FALSE_;
    }
    if (*iflag < 0) {
	repeat = TRUE_;
	cterm_(&c__1);			/* PUT TERMINAL IN TEXT MODE */
    }
    return 0;

L42:
    cterm_(&c__1);
    printf("\n*** ERROR CALLING PLT3D/HLT3D IN CVAX3DX ***");
    printf("\n*** INTERNAL WORKING SPACE EXCEEDED *** %d\n",ierr);
    return 0;
} /* cvax3dx_ */
