
/* *** LAST REVISED ON 20-JAN-1994 08:09:25.17 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]MVAX3D.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    real a1, a2, a3, b1, b2, b3, b4;
} plt3b_;

#define plt3b_1 plt3b_

/* Table of constant values */
static integer c_n2 = -2;
static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__4 = 4;
static real c_b8 = (float)1.5;
static real c_b9 = (float)1.;
static real c_b14 = (float)0.;
static real c_b85 = (float).15;
static real c_b86 = (float)4.01;
static real c_b95 = (float)90.;


/* Subroutine */ int mvax3d_(a, inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
	iflag, iaxis, xt, nxt, xastart, xaend, yt, nyt, zt, nzt, zastart, 
	zaend, aminin, amaxin, icol)
real *a;
integer *inx, *inz, *nx, *nz;
real *alpha, *beta, *xh, *yh, *zh;
integer *iflag, *iaxis;
char *xt;
integer *nxt;
real *xastart, *xaend;
char *yt;
integer *nyt;
char *zt;
integer *nzt;
real *zastart, *zaend, *aminin, *amaxin;
integer *icol;
{
    /* System generated locals */
    integer a_dim1, a_offset;

    /* External functions */
    extern /* Subroutine */ int mvax3dx_();

    /* Local variables */
    static integer ic;
    static real tx, ty, tz;
    static real amn;
    static integer iax;
    static real fdx, fdy, fdz, amx, tsx, tsy, tsz;

/* 	CREATED BY D. LONG  AUG 1987	AT JPL */
/* 	SIMPLIFIES CALLING MVAX3DX ROUTINE */

    /* Parameter adjustments */
    --icol;
    a_dim1 = *inx;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */
    iax = *iaxis % 100;
    if (*iaxis < 0) {
	amn = *aminin;
	amx = *amaxin;
    }
    if (abs(*iflag) % 10 == 2) {
	mvax3dx_(&a[a_offset], inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
		iflag, &iax, xt, nxt, xastart, xaend, &tx, &tsx, &fdx, yt, 
		nyt, &ty, &tsy, &fdy, zt, nzt, zastart, zaend, &tz, &tsz, &
		fdz, &amn, &amx, &icol[1]);
    } else {
	mvax3dx_(&a[a_offset], inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
		iflag, &iax, xt, nxt, xastart, xaend, &tx, &tsx, &fdx, yt, 
		nyt, &ty, &tsy, &fdy, zt, nzt, zastart, zaend, &tz, &tsz, &
		fdz, &amn, &amx, &ic);
    }
    return 0;
} /* mvax3d_ */

#define MAX_WORK 9000			/* internal storage size */

/* ******************************************************************** */

/* Subroutine */ int mvax3dx_(a, inx, inz, nx, nz, alpha, beta, xh, yh, zh, 
	iflag, iaxis, xt, nxt, xastart, xaend, tx, tsx, fdx, yt, nyt, ty, tsy,
	 fdy, zt, nzt, zastart, zaend, tz, tsz, fdz, aminin, amaxin, icol)
real *a;
integer *inx, *inz, *nx, *nz;
real *alpha, *beta, *xh, *yh, *zh;
integer *iflag, *iaxis;
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

    static real dtr = (float).0174532925;
    static real tpi = (float)3.141592654;
    static logical repeat = FALSE_;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    real r__1, r__2;

    /* External functions */
    extern /* Subroutine */ int plot_(), hlt3d_(), plt3d_(), axis3_();
    extern /* Subroutine */ int scale_(), frame_(), cterm_();
    extern /* Subroutine */ int nxtvu_();
    extern /* Subroutine */ int newpen_(), plotnd_();

    /* Builtin functions */
    double atan2(), sqrt(), cos(), sin();

    /* Local variables */
    static integer iaff, nadd;
    static real amin, amax;
    static integer ierr;
    static real xlen, ylen, zlen;
    static real zlen1;
    static integer i, j, k;
    static integer n1;
    static real w2[MAX_WORK];
    static integer ic[4], jf;
    static real as[2];
    static integer jj;
    static real dy;
    static integer iz, ix, nw;
    static real xp, yp, yscale;
    static real xp1, yp1, daa;
    static integer iaf, jff;
    static real ang;
    static integer ilu;
    static real val1, val2;
    static integer nw1d, nw2d;

/* 	CREATED BY D. LONG     AUG 1987	AT JPL */

/* 	ROUTINE TO PLOT DATA IN 3-D MESH OR HISTOGRAM COLUMN FORM */
/* 	WITH HIDDEN LINE REMOVAL USING PLT3D OR HLT3D */

/* 	COORDINATE SYSTEM HAS ORIGIN AT UPPER LEFT CORNER */
/* 					Y */
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
/* 	(TEN'S DIGIT) = 0 PLOT MESH WITH SIDE PLATES (LOWER SURFACE NOT SHOWN)
 */
/* 		      = 1 MESH W/O SIDE PLATES (LOWER SIDE SURFACE SHOWN */
/* 			  USING SOLID LINE) */
/* 		      = 2 MESH W/O SIDE PLATES (LOWER SIDE SURFACE SHOWN */
/* 			  USING DOTTED LINE) */
/* 		      = 3 MESH W/O SIDE PLATES (LOWER SIDE SURFACE NOT SHOWN) */
/* 		      = 4 HISTOGRAM COLUMNS (LOWER SIDE SURFACE SHOWN */
/* 			  USING SOLID LINE) */
/* 		      = 5 HISTOGRAM COLUMNS (LOWER SIDE SURFACE SHOWN */
/* 			  USING DOTTED LINE) */
/* 		      = 6 HISTOGRAM COLUMNS (LOWER SIDE SURFACE NOT SHOWN) */
/* 	(HUNDREDS'S DIGIT) = 0 ASK WHICH SCREEN DEVICE TO USE */
/* 		           <>0 SCREEN DEVICE CODE NUMBER */
/* 	IAXIS	INTEGER AXIS OPTION FLAG */
/* 			= 0	DO NOT PLOT AXIS--FOLLOWING VARIABLES NOT ACCESSED */
/* 			< 0	PLOT AXIS, USE INPUT Y AXIS SCALE--FOLLOWING VARIABLES ACCESSED */
/*			> 0	PLOT AXIS, USE COMPUTED Y AXIS SCALE--FOLLOWING VARIABLES ACCESSED*/
/* 	(ONE'S DIGIT)	= 1	PLOT AXIS, Y AXIS SCALE--VARIABLES ACCESSED */
/* 			= 2	PLOT AXIS, AUTO SCALE Y AXIS--VARIABLES ACCESSED */
/* 	(TEN'S DIGIT)	= 0	BACK PLANE PLOTTED */
/* 			= 1	BACK PLANE NOT PLOTTED */
/* 	(HUNDRED'S)	= 0	DEFAULT AXIS PARAMETERS */
/* 			= 1	SPECIALIZED AXIS3 PARAMETERS */
/* 	XT,YT,ZT	CHAR STRINGS FOR AXIS TITLES */
/* 	NXT,NYT,NZT	INT  LENGTH OF AXIS TITLES */
/* 			     IF ZERO THEN THAT AXIS NOT PLOTTED */
/* 	XASTART,ZASTART	REAL AXIS START VALUES */
/* 	XAEND,ZAEND	REAL AXIS END VALUES */
/* ONLY ACCESSED IF TEN'S DIGIT OF IAXIS=1 */
/* 	TX,TY,TZ	REAL TICK MARK PATTERN (SEE AXIS3) */
/* 	TSX,TSY,TSZ	REAL SIZE OF TITLE AND NUMBERS OF AXIS */
/* 			  IF <0 DO NOT AUTO-SCALE AXIS BY (x10^POWER) */
/* 	FDX,FDY,FDZ	REAL AXIS NUMBER LABEL FORMAT (SEE AXIS3) */
/* 	AMININ,AMAXIN 	REAL YAXIS SCALING FACTORS (ONLY NEEDED IF IAXIS < 0) */
/* 	ICOL		INTEGER COLOR CONTROL (ACCESSED IF MOD(IFLAG,10)=2) */
/* 				ICOL(1) AXIS LINE COLOR */
/* 				ICOL(2) AXIS NUMERIC LABEL COLOR */
/* 				ICOL(3) AXIS TITLE COLOR */
/* 				ICOL(4) AXIS EXPONENT COLOR */
/* 				ICOL(5) BACK PLANE COLOR (RETURN) */
/* 				ICOL(6) TOP SURFACE COLOR */
/* 				ICOL(7) BOTTOM SURFACE COLOR */

    /* Parameter adjustments */
    --icol;
    a_dim1 = *inx;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */
    ierr=0;

/* 	INTIALIZE ROUTINE AND PLOT PACKAGE IF ACCESSED */

    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();
	}				/* CLOSE PLOTTER */
	repeat = FALSE_;
	return 0;
    }

    if (*iaxis < 0) {
	amax = *amaxin;
	amin = *aminin;
    } else {
	amax = a[a_dim1 + 1];
	amin = a[a_dim1 + 1];
	i__1 = *nz;
	for (iz = 1; iz <= i__1; ++iz) {	/* DETERMINE MAX,MIN ARRAY VALUES */
	    i__2 = *nx;
	    for (ix = 1; ix <= i__2; ++ix) {	/* Computing MAX */
		r__1 = amax, r__2 = a[ix + iz * a_dim1];
		amax = dmax(r__1,r__2);		/* Computing MIN */
		r__1 = amin, r__2 = a[ix + iz * a_dim1];
		amin = dmin(r__1,r__2);
/* L16: */
	    }
	}
    }
    xlen = dabs(*xh);
    zlen = dabs(*zh);
    ylen = dabs(*yh);
    if (abs(*iaxis) % 10 == 2) {
	as[0] = amax;
	as[1] = amin;
	scale_(as, &ylen, &c__2, &c__1, &c__1, &amin, &daa);
	amax = ylen * daa + amin;
    }
    yscale = (float)1.;
    if (amax - amin != (float)0.) {
	yscale = ylen / (amax - amin);
    }

/* 	INTIALIZE PLOT PACKAGE */

    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = jf / 100;				/* GRAPHICS DEVICE CODE */
	frame_(&c__3, &ilu, &c_b8, &c_b9, &c_b9);/* INTIALIZE */
    } else {
	cterm_(&c_n1);				/* PUT TERMINAL IN PLOT MODE */
    }

    iaff = abs(*iaxis) / 100;			/* AXIS TYPE */
    iaf = abs(*iaxis) % 100 / 10;		/* BACK PANEL */
    jff = jf % 100 / 10;			/* SIDE PLATES/SUFACE */
    jf %= 10;

/* 	PLOT SURFACE WITH SIMPLE HIDDEN LINE REMOVAL */

/* COLORS */
    xp = xlen / (float)2. * cos( dtr *  *alpha) + (float)2.;
    r__1 = *beta + (float)180.;
    yp = -(doublereal)(xlen / (float)2. + ylen / (float)2.) * 
	    sin( dtr * *alpha) * 
	    sin( dtr *  r__1) - yscale * amin;
    nw1d = 1;
    nw2d = MAX_WORK - 1;
    if (jff < 4) {
	nw1d = 4*max(*nx,*nz);
	nw2d = MAX_WORK - nw1d - 1;
	if (nw2d < nw1d) {
	    goto L42;
	}
    }
    nw = nw2d + 1;

    if (jff != 0 && jff != 3 && jff != 6) {

/* 	IF WE DON'T PLOT SIDE PLATES THEN PLOT UNDERSIDE OF SURFACE */

	if (jff == 1 || jff == 4) {
	    newpen_(&c__2);
	}
	if (jf == 2) {
	    r__1 = (real) icol[7];
	    plot_(&r__1, &c_b14, &c__0);
	}
	if (jff < 3) {
	    r__1 = *beta + (float)180.;
	    r__2 = -(doublereal)xlen;
	    plt3d_(&a[a_offset], inx, inz, nx, nz, &w2[nw - 1], &nw1d, w2,
		    &nw2d, alpha, &r__1, &r__2, &xp, &zlen, &yp, &yscale,
		    &c_b14, &ierr);
	} else {
	    r__1 = *beta + (float)180.;
	    r__2 = -(doublereal)xlen;
	    hlt3d_(&a[a_offset], inx, inz, nx, nz, w2, &nw1d, w2, &nw2d, 
		    alpha, &r__1, &r__2, &xp, &zlen, &yp, &yscale, &c_b14,
		    &ierr);
	}
	if (jff == 1 || jff == 4) {
	    newpen_(&c__1);
	}
	if (ierr != 0) {
	    goto L42;
	}

/* 	IF BACK PANEL IS DESIRED, PLOT LOWER SIDE OF BACK PANEL */

	if (*iaxis != 0) {
	    dy = (float)1. / yscale;
	    if (*nyt > 0) {			/* PLOT Y AXIS */
		if (iaff == 1) {
		    n1 = (integer) (*ty);
		} else {
		    n1 = (integer) (ylen + (float).5) + 1;
		}
		if (iaf == 0) {
		    if (jf == 2) {
			r__1 = (real) icol[5];
			plot_(&r__1, &c_b14, &c__0);
		    }
		    val2 = (n1 - 1) * dy + amin;
		    w2[nw - 1] = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + 
			    plt3b_1.a3;
		    w2[nw] = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + 
			    plt3b_1.b3 * val2 + plt3b_1.b4;
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
			val1 = (n1 - k - 1) * dy + amin;
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

    }
/* 	PLOT TOP SIDE OF SURFACE */
    if (jf == 2) {
	r__1 = (real) icol[6];
	plot_(&r__1, &c_b14, &c__0);
    }
    if (jff < 4) {
	r__1 = *beta + (float)180.;
	plt3d_(&a[a_offset], inx, inz, nx, nz, &w2[nw - 1], &nw1d, w2, &nw2d, 
		alpha, &r__1, &xlen, &xp, &zlen, &yp, &yscale, &c_b14, &ierr);

    } else {
	r__1 = *beta + (float)180.;
	hlt3d_(&a[a_offset], inx, inz, nx, nz, w2, &nw1d, w2, &nw2d, alpha, &
		r__1, &xlen, &xp, &zlen, &yp, &yscale, &c_b14, &ierr);
    }

    if (ierr == 0) {
	goto L43;
    }
L42:
    cterm_(&c__1);
    printf("\n *** ERROR CALLING PLT3D/HLT3D IN MVAX3DX ***\n");
    printf(" *** INTERNAL WORK SPACE EXCEEDED ***\n");
    return 0;
L43:
/* 	ADD SIDE PLATES */

    if (jff != 0) {
	goto L71;
    }			/* DON'T PLOT SIDE PLATES */
    i__2 = *nx;
    for (i = 1; i <= i__2; ++i) {
	xp = plt3b_1.a1 * *nz + plt3b_1.a2 * i + plt3b_1.a3;
	yp = plt3b_1.b1 * *nz + plt3b_1.b2 * i + plt3b_1.b3 * amin + 
		plt3b_1.b4;
	xp1 = plt3b_1.a1 * *nz + plt3b_1.a2 * i + plt3b_1.a3;
	yp1 = plt3b_1.b1 * *nz + plt3b_1.b2 * i + plt3b_1.b3 * a[i + *nz * 
		a_dim1] + plt3b_1.b4;
	if (i % 2 == 0) {
	    plot_(&xp, &yp, &c__3);
	    plot_(&xp1, &yp1, &c__2);
	} else {
	    plot_(&xp1, &yp1, &c__3);
	    plot_(&xp, &yp, &c__2);
	}
/* L4335: */
    }
    i__2 = *nz;
    for (j = 2; j <= i__2; ++j) {
	jj = *nz - j + 1;
	xp = plt3b_1.a1 * jj + plt3b_1.a2 * *nx + plt3b_1.a3;
	yp = plt3b_1.b1 * jj + plt3b_1.b2 * *nx + plt3b_1.b3 * amin + 
		plt3b_1.b4;
	xp1 = plt3b_1.a1 * jj + plt3b_1.a2 * *nx + plt3b_1.a3;
	yp1 = plt3b_1.b1 * jj + plt3b_1.b2 * *nx + plt3b_1.b3 * a[*nx + jj * 
		a_dim1] + plt3b_1.b4;
	if (j % 2 == 0) {
	    plot_(&xp, &yp, &c__3);
	    plot_(&xp1, &yp1, &c__2);
	} else {
	    plot_(&xp1, &yp1, &c__3);
	    plot_(&xp, &yp, &c__2);
	}
/* L4336: */
    }
/* 	DRAW BOTTOM LINE */

    xp = plt3b_1.a1 * c__1 + plt3b_1.a2 * *nx + plt3b_1.a3;
    yp = plt3b_1.b1 * c__1 + plt3b_1.b2 * *nx + plt3b_1.b3 * amin + 
	    plt3b_1.b4;
    plot_(&xp, &yp, &c__3);
    xp = plt3b_1.a1 * *nz + plt3b_1.a2 * *nx + plt3b_1.a3;
    yp = plt3b_1.b1 * *nz + plt3b_1.b2 * *nx + plt3b_1.b3 * amin + plt3b_1.b4;

    plot_(&xp, &yp, &c__2);
    xp = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + plt3b_1.a3;
    yp = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + plt3b_1.b3 * amin + 
	    plt3b_1.b4;
    plot_(&xp, &yp, &c__2);

/* 	PLOT AXIS LABELS */
L71:
    if (*iaxis != 0) {			/* PLOT AXIS LABELS */
	nadd = 0;
	if (jf == 2) {
	    nadd = 100000;
	    ic[0] = icol[1];
	    ic[1] = icol[2];
	    ic[2] = icol[3];
	    ic[3] = icol[4];
	}
	xp = plt3b_1.a1 * *nz + plt3b_1.a2 * *nx + plt3b_1.a3;
	yp = plt3b_1.b1 * *nz + plt3b_1.b2 * *nx + plt3b_1.b3 * amin + 
		plt3b_1.b4;
	xp1 = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + plt3b_1.a3;
	yp1 = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + plt3b_1.b3 * amin + 
		plt3b_1.b4;
	ang = atan2(yp - yp1, xp - xp1) * (float)180. / tpi;
/* Computing 2nd power */
	r__1 = xp - xp1;
/* Computing 2nd power */
	r__2 = yp - yp1;
	zlen1 = sqrt(r__1 * r__1 + r__2 * r__2);
	if (*nxt > 0) {				/* PLOT X AXIS */
	    if (iaff == 1) {
		i__2 = -nadd - *nxt;
		axis3_(&xp1, &yp1, xt, &i__2, &zlen1, &ang, xastart, xaend, 
			tx, tsx, fdx, ic);
	    } else {
		val1 = (integer) (xlen + (float).5) + (float)1.;
		i__2 = -nadd - *nxt;
		axis3_(&xp1, &yp1, xt, &i__2, &zlen1, &ang, xastart, xaend, &
			val1, &c_b85, &c_b86, ic);
	    }
	}
	xp1 = plt3b_1.a1 * c__1 + plt3b_1.a2 * *nx + plt3b_1.a3;
	yp1 = plt3b_1.b1 * c__1 + plt3b_1.b2 * *nx + plt3b_1.b3 * amin + 
		plt3b_1.b4;
	ang = atan2(yp1 - yp, xp1 - xp) * (float)180. / tpi;
/* Computing 2nd power */
	r__1 = xp1 - xp;
/* Computing 2nd power */
	r__2 = yp1 - yp;
	zlen1 = sqrt(r__1 * r__1 + r__2 * r__2);
	if (*nzt > 0) {				/* PLOT Z AXIS */
	    if (iaff == 1) {
		i__2 = -nadd - *nzt;
		axis3_(&xp, &yp, zt, &i__2, &zlen1, &ang, zaend, zastart, tz, 
			tsz, fdz, ic);
	    } else {
		val1 = (integer) (zlen + (float).5) + (float)1.;
		i__2 = -nadd - *nzt;
		axis3_(&xp, &yp, zt, &i__2, &zlen1, &ang, zaend, zastart, &
			val1, &c_b85, &c_b86, ic);
	    }

/* 	PLOT Y AXISES */

	}
	dy = (float)1. / yscale;
	xp1 = plt3b_1.a1 * *nz + plt3b_1.a2 * *nx + plt3b_1.a3;
	yp1 = plt3b_1.b1 * *nz + plt3b_1.b2 * *nx + plt3b_1.b3 * amax + 
		plt3b_1.b4;
/* Computing 2nd power */
	r__1 = xp1 - xp;
/* Computing 2nd power */
	r__2 = yp1 - yp;
	zlen1 = sqrt(r__1 * r__1 + r__2 * r__2);
	if (*nyt > 0) {			/* PLOT Y AXIS */
	    xp = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + plt3b_1.a3;
/* LEFT SIDE */
	    yp = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + plt3b_1.b3 * amin + 
		    plt3b_1.b4;
	    xp1 = plt3b_1.a1 * c__1 + plt3b_1.a2 * *nx + plt3b_1.a3;
/* RIGHT SIDE */
	    yp1 = plt3b_1.b1 * c__1 + plt3b_1.b2 * *nx + plt3b_1.b3 * amin + 
		    plt3b_1.b4;
	    if (iaff == 1) {
		i__2 = nadd + *nyt;
		axis3_(&xp, &yp, yt, &i__2, &zlen1, &c_b95, &amin, &amax, ty, 
			tsy, fdy, ic);
		i__2 = -nadd - *nyt;
		axis3_(&xp1, &yp1, yt, &i__2, &zlen1, &c_b95, &amin, &amax, 
			ty, tsy, fdy, ic);
		n1 = (integer) (*ty);	/* MAJOR AXIS TICKS */
	    } else {
		val1 = (integer) (ylen + (float).5) + (float)1.;
		i__2 = nadd + *nyt;
		axis3_(&xp, &yp, yt, &i__2, &zlen1, &c_b95, &amin, &amax, &
			val1, &c_b85, &c_b86, ic);
		i__2 = -nadd - *nyt;
		axis3_(&xp1, &yp1, yt, &i__2, &zlen1, &c_b95, &amin, &amax, &
			val1, &c_b85, &c_b86, ic);
		n1 = (integer) (ylen + (float).5) + 1;
	    }
/* 	PLOT BACK PANEL */

	    if (iaf == 0) {
		if (jf == 2) {
		    r__1 = (real) icol[5];
		    plot_(&r__1, &c_b14, &c__0);
		}
		i__2 = n1;
		for (k = 1; k <= i__2; ++k) {
		    val1 = (k - 1) * dy + amin;
		    w2[nw - 1] = plt3b_1.a1 * *nz + plt3b_1.a2 * c__1 + 
			    plt3b_1.a3;
		    w2[nw] = plt3b_1.b1 * *nz + plt3b_1.b2 * c__1 + 
			    plt3b_1.b3 * amin + plt3b_1.b4;
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
			    plt3b_1.b3 * amin + plt3b_1.b4;
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
			    plt3b_1.b3 * amin + plt3b_1.b4;
		    nxtvu_(&c__2, &w2[nw - 1], &c__3, w2, &nw2d, &ierr);
		    if (ierr != 0) {
			goto L42;
		    }
/* L4338: */
		}
	    }
	}
    }

/* 	FINISH UP */
    plot_(&c_b14, &c_b14, &c__3);	/* PEN UP */
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
} /* mvax3dx_ */

