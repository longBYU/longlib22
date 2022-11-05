
/* *** LAST REVISED ON  7-JAN-1994 13:15:13.28 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]T3DH.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    integer isize;
    real work[100000];
} go_;

#define go_1 go_

/* Table of constant values */

static integer c__2 = 2;
static integer c__1 = 1;
static integer c__3 = 3;
static real c_b7 = (float)1.5;
static real c_b8 = (float).65;
static real c_b9 = (float)1.;
static integer c_n1 = -1;
static real c_b15 = (float)0.;
static integer c__0 = 0;
static real c_b29 = (float)90.;

/* Subroutine */ int t3dh_(a, inx, iny, nx, ny, psi, phi, theta, dv, xh, yh, 
	zh, iflag, iaxis, xt, nxt, xastart, xaend, tx, tsx, pgx, fsx, yt, nyt,
	 yastart, yaend, ty, tsy, pgy, fsy, zt, nzt, tz, tsz, pgz, fsz, 
	aminin, amaxin, icol)
real *a;
integer *inx, *iny, *nx, *ny;
real *psi, *phi, *theta, *dv, *xh, *yh, *zh;
integer *iflag, *iaxis;
char *xt;
integer *nxt;
real *xastart, *xaend, *tx, *tsx, *pgx, *fsx;
char *yt;
integer *nyt;
real *yastart, *yaend, *ty, *tsy, *pgy, *fsy;
char *zt;
integer *nzt;
real *tz, *tsz, *pgz, *fsz, *aminin, *amaxin;
integer *icol;
{
    /* Initialized data */

    static logical repeat = FALSE_;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    real r__1, r__2;

    /* Local variables */
    static real amin, amax;
    static integer ierr;
    static real xlen, ylen, zlen;
    static integer iopt;
    extern /* Subroutine */ int plot_(), scale_(), frame_();
    static integer icore;
    extern /* Subroutine */ int cterm_();
    static real x1, y1, y2, x2;
    extern /* Subroutine */ int plt3dh_();
    static integer jf, nc;
    static real sf;
    static logical hidden;
    static real dx, dy, dz;
    static integer iy, ix;
    static real xx[4], yy[4], zz[4];
    extern /* Subroutine */ int sketch_(), plotnd_(), init3dh_(), axis3dh_();
    static real daa;
    static integer mne, mnh;
    static real pas[2];
    static integer ilu;

/* 	CREATED BY D. LONG     FEB, 1986	AT JPL */

/* 	ROUTINE TO PLOT DATA IN A TRIANGULAR 3-D MESH FORM WITH HIDDEN LINE */

/* 	REMOVAL USING THE INIT3DH ROUTINES. */

/* 	A	(R) ARRAY A(INX,INY) CONTAINING VERTICAL HEIGHT DATA */
/* 	INX,INY (I) DIMENSION OF A ARRAY */
/* 	NX,NY	(I) INDICATING SIZE OF A ARRAY TO PLOT */
/* 	PSI,PHI,THETA (R) ANGLES (IN DEGREES) OF INIT3DH */
/* 	DV	(R) PERSPECTIVE FACTOR OF INIT3DH (9999=NO PERSPECTIVE) */
/* 		    DV < 0 DO NOT INITIALIZE INIT3DH */
/* 	XH,YH,ZH (R) LENGTH OF EACH AXIS (INCHES) */
/* 	IFLAG	(I) PLOT FLAG */
/* 		>1000	REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER */
/* 		< 0	REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT) */
/* 		= 0	CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT */
/* 		> 0	SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED) */
/* 	(ONE'S DIGIT) = 2 USE RAM TEK COLOR CONTROL ARRAY */
/* 		      = 1 DO NOT USE RAM TEK COLOR ARRAY */
/* 	(TEN'S DIGIT) = 0 NO HIDDEN LINE REMOVAL FOR AXIS */
/* 		      = 1 HIDDEN LINE REMOVAL OF AXIS */
/* 		      = 2 NO HIDDEN LINES AT ALL (SKETCH USED) */
/* 		      = 3 NO HIDDEN LINES AT ALL (SKETCH NOT USED) */
/* 	(HUNDRED'S)   = 0 ASK WHICH SCREEN DEVICE TO USE */
/* 		      <>0 SCREEN DEVICE CODE NUMBER */
/* 	IAXIS	(I) AXIS OPTION FLAG */
/* 			= 0	DO NOT PLOT AXIS--FOLLOWING VARIABLES NOT ACCESSED */
/* 			< 0	PLOT AXIS, USE INPUT Z AXIS SCALE */
/* 			> 0	PLOT AXIS, USE COMPUTED Z AXIS SCALE */
/* 	(ONE'S DIGIT)	= 1	PLOT AXIS, Y AXIS SCALE--VARIABLES ACCESSED */
/* 			= 2	PLOT AXIS, AUTO SCALE Y AXIS--VARIABLES ACCESSED */
/* 	XT,YT,ZT	(B) STRINGS FOR AXIS TITLES */
/* 	NXT,NYT,NZT	(I)  LENGTH OF AXIS TITLES */
/* 			     IF ZERO THEN THAT AXIS NOT PLOTTED */
/* 	XASTART,YASTART	(R) AXIS START VALUES */
/* 	XAEND,YAEND	(R) AXIS END VALUES */
/* FOLLOWING ONLY ACCESSED IF IAXIS<>0 */
/* 	TX,TY,TZ	(R) NUMBER OF TICK MARKS (SEE AXIS3DH) */
/* 	TSX,TSY,TSZ	(R) SIZE OF TITLE AND NUMBERS OF AXIS */
/* 			  IF LESS THAN ZERO DO NOT AUTO-SCALE BY (x10^POWER) */
/* 	PGX,PGY,PGZ	(R) ROTATION OF TEXT AND TICKS AROUND AXIS (DEG) */
/* 	FSX,FSY,FSZ	(R) NUMBER FORMAT OF AXISES (SEE AXIS3DH) */
/* 	AMININ,AMAXIN 	(R) YAXIS SCALING FACTORS (ONLY NEEDED IF IAXIS < 0) */

/* 	ICOL		(I) COLOR INDEX TABLE (ACCESSED IF 1'S DIGIT OF IFLAG=2 */
/* 				ICOL(1) AXIS COLOR */
/* 				ICOL(2) SURFACE COLOR */
/* 			    NOTE: WHEN BOTH AXIS AND SURFACE USE SKETCH */
/* 			    BOTH ARE PLOTTED USING SURFACE COLOR */

    /* Parameter adjustments */
    --icol;
    a_dim1 = *inx;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */

    if (go_1.isize < 100000) {
	go_1.isize = 100000;
    }

/* INCREASE WORKSPACE IF NEEDED */
    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();
	}
/* CLOSE PLOTTER */
	repeat = FALSE_;
	return 0;
    }

    if (*iaxis < 0) {
	amax = *amaxin;
	amin = *aminin;
    } else {
	amax = a[a_dim1 + 1];
	amin = a[a_dim1 + 1];
	i__1 = *ny;
	for (iy = 1; iy <= i__1; ++iy) {
/* DETERMINE MAX,MIN ARRAY VALUES */
	    i__2 = *nx;
	    for (ix = 1; ix <= i__2; ++ix) {
/* Computing MAX */
		r__1 = amax, r__2 = a[ix + iy * a_dim1];
		amax = dmax(r__1,r__2);
/* Computing MIN */
		r__1 = amin, r__2 = a[ix + iy * a_dim1];
		amin = dmin(r__1,r__2);
/* L16: */
	    }
	}
    }

    xlen = dabs(*xh);
    ylen = dabs(*yh);
    zlen = dabs(*zh);
    if (abs(*iaxis) % 10 == 2) {
	pas[0] = amax;
	pas[1] = amin;
	scale_(pas, &zlen, &c__2, &c__1, &c__1, &amin, &daa);
	amax = zlen * daa + amin;
    }

/* 	INTIALIZE PLOT PACKAGE */

    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = jf % 10000 / 100;
	frame_(&c__3, &ilu, &c_b7, &c_b8, &c_b9);
/* INTIALIZE */
    } else {
	cterm_(&c_n1);
/* PUT TERMINAL PLOT MODE */
    }

    hidden = TRUE_;
    iopt = jf % 100 / 10;
    if (iopt == 3) {
	iopt = 0;
	hidden = FALSE_;
    }
    jf %= 10;

/* 	INITIALIZE 3DH PACKAGE */

    mne = 3;
/* MAX NUMBER OF EDGES */
    mnh = 0;
/* NO HOLES */
    icore = (mne * 5 + 25 + (mnh << 2)) * *nx * *ny;
    if (*iaxis != 0) {
	icore += 10000;
    }
/* ESTIMATED AXISES SPACE */
    if (icore > go_1.isize) {
	printf("\n*** WARNING: T3DH, /GO/ STORAGE TOO SMALL ***\n");
	cterm_(&c_n1);
    }
    sf = (float)1.;
/* SCALE FACTOR */
    if (iopt == 2) {
	sf = (float)-1.;
    }
/* NO HIDDEN LINE REMOVAL */
    if (*dv > (float)0.) {
	init3dh_(&c_b15, &c_b15, &c_b15, psi, phi, theta, &sf, dv, &mne, &mnh)
		;
    }

    if (*iaxis != 0) {
/* PLOT AXIS LABELS */
	if (jf == 2) {
	    r__1 = (real) icol[1];
	    plot_(&r__1, &c_b15, &c__0);
	}
/* RAM TEK COLOR */
	if (*nxt > 0) {
/* PLOT X AXIS */
	    axis3dh_(&c_b15, &c_b15, &c_b15, &c_b15, &c_b15, pgx, xt, nxt, &
		    xlen, xastart, xaend, tx, tsx, fsx, &iopt);
	}
	if (*nyt > 0) {
/* PLOT Y AXIS */
	    axis3dh_(&c_b15, &c_b15, &c_b15, &c_b15, &c_b29, pgy, yt, nyt, &
		    ylen, yastart, yaend, ty, tsy, fsy, &iopt);
	}
	if (*nzt > 0) {
/* PLOT Z AXIS */
	    r__1 = -(doublereal)zlen;
	    axis3dh_(&c_b15, &c_b15, &c_b15, &c_b29, &c_b15, pgz, zt, nzt, &
		    r__1, &amin, &amax, tz, tsz, fsz, &iopt);
	}
    }
    if (jf == 2) {
	r__1 = (real) icol[2];
	plot_(&r__1, &c_b15, &c__0);
    }

/* 	BEGIN SURFACE PLOTTING */

/* RAM TEK COLOR */
    dx = xlen / abs(*nx);
    dy = ylen / abs(*ny);
    dz = (float)1.;
    if (amax - amin != (float)0.) {
	dz = zlen / (amax - amin);
    }

    i__2 = abs(*ny) - 1;
    for (iy = 1; iy <= i__2; ++iy) {
/* FOR EACH Y CELL */
	y1 = (iy - 1) * dy;
	y2 = iy * dy;
	i__1 = abs(*nx) - 1;
	for (ix = 1; ix <= i__1; ++ix) {
/* FOR EACH X CELL */
	    x1 = (ix - 1) * dx;
	    x2 = ix * dx;

	    xx[0] = x1;
	    xx[1] = x2;
	    xx[2] = x2;
	    xx[3] = x1;
	    yy[0] = y1;
	    yy[1] = y1;
	    yy[2] = y2;
	    yy[3] = y1;
	    zz[0] = (a[ix + iy * a_dim1] - amin) * dz;
	    zz[1] = (a[ix + 1 + iy * a_dim1] - amin) * dz;
	    zz[2] = (a[ix + 1 + (iy + 1) * a_dim1] - amin) * dz;
	    zz[3] = zz[0];
	    nc = 4;
	    ierr = 0;
	    if (hidden) {
		sketch_(xx, yy, zz, &nc, &ierr);
	    } else {
		ierr = 3;
		i__3 = nc;
		for (jf = 1; jf <= i__3; ++jf) {
		    plt3dh_(&xx[jf - 1], &yy[jf - 1], &zz[jf - 1], &ierr);
		    ierr = 2;
/* L20: */
		}
	    }
	    if (ierr < 0) {
		cterm_(&c__1);
		printf("\n *** WARNING: T3DH SKETCH ERROR HAS OCCURED ***\n");
		cterm_(&c_n1);
	    }

	    xx[0] = x1;
	    xx[1] = x1;
	    xx[2] = x2;
	    xx[3] = x1;
	    yy[0] = y1;
	    yy[1] = y2;
	    yy[2] = y2;
	    yy[3] = y1;
	    zz[0] = (a[ix + iy * a_dim1] - amin) * dz;
	    zz[1] = (a[ix + (iy + 1) * a_dim1] - amin) * dz;
	    zz[2] = (a[ix + 1 + (iy + 1) * a_dim1] - amin) * dz;
	    zz[3] = zz[0];
	    nc = 4;
	    ierr = 0;
	    if (iy == abs(*ny) - 1 && ix == abs(*nx) - 1) {
		ierr = 1;
	    }
	    if (hidden) {
		sketch_(xx, yy, zz, &nc, &ierr);
	    } else {
		ierr = 3;
		i__3 = nc;
		for (jf = 1; jf <= i__3; ++jf) {
		    plt3dh_(&xx[jf - 1], &yy[jf - 1], &zz[jf - 1], &ierr);
		    ierr = 2;
/* L25: */
		}
	    }
	    if (ierr < 0) {
		cterm_(&c__1);
		printf("\n *** WARNING: T3DH SKETCH ERROR HAS OCCURED ***\n");
		cterm_(&c_n1);
	    }
/* L50: */
	}
    }

/* 	FINISH ROUTINE */

    if (! hidden) {
	plt3dh_(xx, yy, zz, &c__3);
    }
/* PEN UP */
/* L999: */
    plot_(&c_b15, &c_b15, &c__3);
/* PEN UP */
    if (*iflag > 0) {
	cterm_(&c__2);
/* CLEAR TERMINAL */
	plotnd_();
/* CLOSE PLOT OUTPUT */
	repeat = FALSE_;
    }
    if (*iflag < 0) {
	repeat = TRUE_;
	cterm_(&c__1);
/* PUT TERMINAL IN TEXT MODE */
    }
    return 0;
} /* t3dh_ */

