
/* *** LAST REVISED ON  7-JAN-1994 12:56:16.27 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]TRIG3DH.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    integer isize;
    real work[100000];
} go_;

#define go_1 go_

/* Table of constant values */

static integer c__1 = 1;
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c__3 = 3;
static real c_b19 = (float)1.5;
static real c_b20 = (float).65;
static real c_b21 = (float)1.;
static real c_b27 = (float)0.;
static integer c__0 = 0;
static real c_b41 = (float)90.;

/* Subroutine */ int trig3dh_(x, y, z, n, psi, phi, theta, dv, xh, yh, zh, 
	iflag, iaxis, xt, nxt, tx, tsx, pgx, fsx, yt, nyt, ty, tsy, pgy, fsy, 
	zt, nzt, tz, tsz, pgz, fsz, xast, xaen, yast, yaen, zast, zaen, icol)
real *x, *y, *z;
integer *n;
real *psi, *phi, *theta, *dv, *xh, *yh, *zh;
integer *iflag, *iaxis;
char *xt;
integer *nxt;
real *tx, *tsx, *pgx, *fsx;
char *yt;
integer *nyt;
real *ty, *tsy, *pgy, *fsy;
char *zt;
integer *nzt;
real *tz, *tsz, *pgz, *fsz, *xast, *xaen, *yast, *yaen, *zast, *zaen;
integer *icol;
{
    /* Initialized data */

    static integer nzz = 2000;
    static integer nw = 1000;
    static logical repeat = FALSE_;

    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;

    /* Local variables */
    static integer ierr;
    static real xlen, ylen, zlen, xmin, ymin, xmax, ymax, zmax, zmin;
    static integer iopt;
    extern /* Subroutine */ int plot_();
    static integer i, j, l, m;
    extern /* Subroutine */ int scale_(), frame_();
    static integer icore;
    extern /* Subroutine */ int cterm_();
    static integer k1;
    extern /* Subroutine */ int plt3dh_();
    static integer ib[1000], ie, jf, nc, ip[1000];
    static logical hidden;
    static real sf, dx, dy;
    static real xx[4], yy[4], zz[4];
    extern /* Subroutine */ int sketch_(), plotnd_();
    static integer ixaxis, iyaxis, izaxis;
    extern /* Subroutine */ int init3dh_(), axis3dh_();
    static real daa;
    static integer ibe, mne, mnh;
    static real pas[2];
    static integer ite, ilu, itt[6000]	/* was [2000][3] */;
    extern /* Subroutine */ int triangc_();

/* 	CREATED BY D. LONG     FEB, 1986	AT JPL */

/* 	ROUTINE TO PLOT DATA SPECIFIED AS (X,Y,Z) TRIPLES AS 3-D SURFACE */
/* 	BY TRIANGULATING AND PLOTTING WITH HIDDEN LINE REMOVAL */
/* 	USING THE INIT3DH ROUTINES. */

/* 	X,Y,Z	 (R) ARRAYS CONTAINING DATA POINTS */
/* 	N	 (I) NUMBER OF DATA POINTS */
/* 	PSI,PHI,THETA (R) ANGLES (IN DEGREES) OF INIT3DH */
/* 	DV	 (R) PERSPECTIVE FACTOR OF INIT3DH (9999=NO PERSPECTIVE) */
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
/* 			< 0 DO NOT PLOT AXES */
/* 	(ONE'S DIGIT)	= 1 PLOT Z AXIS USING COMPUTED SCALE */
/* 			= 2 PLOT Z AXIS USING COMPUTED, SMOOTHED SCALE */
/* 			= 3 PLOT Z AXIS USING INPUT SCALE--VARIABLES ACCESSED */
/* 			= 4 PLOT Z AXIS USING INPUT, SMOOTHED SCALE--VARIABLES ACCESSED */
/* 	(TEN'S DIGIT)	= 1 PLOT Y AXIS USING COMPUTED SCALE */
/* 			= 2 PLOT Y AXIS USING COMPUTED, SMOOTHED SCALE */
/* 			= 3 PLOT Y AXIS USING INPUT SCALE--VARIABLES ACCESSED */
/* 			= 4 PLOT Y AXIS USING INPUT, SMOOTHED SCALE--VARIABLES ACCESSED */
/* 	(HUNDRED'S)	= 1 PLOT X AXIS USING COMPUTED SCALE */
/* 			= 2 PLOT X AXIS USING COMPUTED, SMOOTHED SCALE */
/* 			= 3 PLOT X AXIS USING INPUT SCALE--VARIABLES ACCESSED */
/* 			= 4 PLOT X AXIS USING INPUT, SMOOTHED SCALE--VARIABLES ACCESSED */
/* 	XT,YT,ZT	(B) STRINGS FOR AXIS TITLES */
/* 	NXT,NYT,NZT	(I) LENGTH OF AXIS TITLES */
/* 			     IF ZERO THEN AXIS NOT PLOTTED */
/* FOLLOWING ONLY ACCESSED IF IAXIS > 0 */
/* 	TX,TY,TZ	(R) NUMBER OF TICK MARKS (SEE AXIS3DH) */
/* 	TSX,TSY,TSZ	(R) SIZE OF TITLE AND NUMBERS OF AXIS */
/* 			  IF LESS THAN ZERO DO NOT AUTO-SCALE BY (x10^POWER) */
/* 	PGX,PGY,PGZ	(R) ROTATION OF TEXT AND TICKS AROUND AXIS (DEG) */
/* 	FSX,FSY,FSZ	(R) NUMBER FORMAT OF AXISES (SEE AXIS3DH) */
/* 	XAST,YAST,ZAST	(R) AXIS START VALUES */
/* 	XAEN,YAEN,ZAEN	(R) AXIS END VALUES */
/* 	ICOL		(I) COLOR INDEX TABLE (ACCESSED IF 1'S DIGIT OF IFLAG=2 */
/* 				ICOL(1) AXIS COLOR */
/* 				ICOL(2) SURFACE COLOR */
/* 			    NOTE: WHEN BOTH AXIS AND SURFACE USE SKETCH */
/* 			    BOTH ARE PLOTTED USING SURFACE COLOR */

    /* Parameter adjustments */
    --icol;
    --z;
    --y;
    --x;

    /* Function Body */

    if (go_1.isize < 100000) {
	go_1.isize = 100000;
    }

/* INCREASE WORKSPACE IF NEEDED */
    if (*n > nw) {
	cterm_(&c__1);
	printf("\n*** TRIG3DH: WARNING, STORAGE /GO/ TOO SMALL ***\n");
	cterm_(&c_n1);
    }

    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();
	}
/* CLOSE PLOTTER */
	repeat = FALSE_;
	return 0;
    }

    xlen = dabs(*xh);
    ylen = dabs(*yh);
    zlen = dabs(*zh);
    izaxis = abs(*iaxis) % 10;
    iyaxis = abs(*iaxis) % 100 / 10;
    ixaxis = abs(*iaxis) % 1000 / 100;
    if (ixaxis > 2) {
	xmax = *xaen;
	xmin = *xast;
    } else {
	xmax = x[1];
	xmin = x[1];
	i__1 = *n;
	for (i = 1; i <= i__1; ++i) {
/* Computing MAX */
	    r__1 = xmax, r__2 = x[i];
	    xmax = dmax(r__1,r__2);
/* Computing MIN */
	    r__1 = xmin, r__2 = x[i];
	    xmin = dmin(r__1,r__2);
/* L16: */
	}
    }
    if (ixaxis == 2 || ixaxis == 4) {
	pas[0] = xmax;
	pas[1] = xmin;
	scale_(pas, &xlen, &c__2, &c__1, &c__1, &xmin, &daa);
	xmax = ylen * daa + xmin;
    }

    if (iyaxis > 2) {
	ymax = *yaen;
	ymin = *yast;
    } else {
	ymax = y[1];
	ymin = y[1];
	i__1 = *n;
	for (i = 1; i <= i__1; ++i) {
/* Computing MAX */
	    r__1 = ymax, r__2 = y[i];
	    ymax = dmax(r__1,r__2);
/* Computing MIN */
	    r__1 = ymin, r__2 = y[i];
	    ymin = dmin(r__1,r__2);
/* L17: */
	}
    }
    if (iyaxis == 2 || iyaxis == 4) {
	pas[0] = ymax;
	pas[1] = ymin;
	scale_(pas, &ylen, &c__2, &c__1, &c__1, &ymin, &daa);
	ymax = ylen * daa + ymin;
    }

    if (izaxis > 2) {
	zmax = *zaen;
	zmin = *zast;
    } else {
	zmax = z[1];
	zmin = z[1];
	i__1 = *n;
	for (i = 1; i <= i__1; ++i) {
/* Computing MAX */
	    r__1 = zmax, r__2 = z[i];
	    zmax = dmax(r__1,r__2);
/* Computing MIN */
	    r__1 = zmin, r__2 = z[i];
	    zmin = dmin(r__1,r__2);
/* L18: */
	}
    }
    if (izaxis == 2 || izaxis == 4) {
	pas[0] = zmax;
	pas[1] = zmin;
	scale_(pas, &zlen, &c__2, &c__1, &c__1, &zmin, &daa);
	zmax = zlen * daa + zmin;
    }

/* 	INTIALIZE PLOT PACKAGE */

    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = jf % 10000 / 100;
	frame_(&c__3, &ilu, &c_b19, &c_b20, &c_b21);
/* INTIALIZE */
    } else {
	cterm_(&c_n1);
/* PUT TERMINAL IN PLOT MODE */
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
    icore = (mne * 5 + 25 + (mnh << 2)) * *n * *n;
    if (*iaxis != 0) {
	icore += 10000;
    }
/* ESTIMATED AXISES SPACE */
    if (icore > go_1.isize) {
	cterm_(&c__1);
	printf("\n*** TRIG3DH: WARNING, STORAGE /GO/ TOO SMALL ***\n");
	cterm_(&c_n1);
    }
    sf = (float)1.;
/* SCALE FACTOR */
    if (iopt == 2) {
	sf = (float)-1.;
    }
/* NO HIDDEN LINE REMOVAL */
    if (*dv > (float)0.) {
	init3dh_(&c_b27, &c_b27, &c_b27, psi, phi, theta, &sf, dv, &mne, &mnh)
		;
    }

    if (*iaxis != 0) {
/* PLOT AXIS LABELS */
	if (jf == 2) {
	    r__1 = (real) icol[1];
	    plot_(&r__1, &c_b27, &c__0);
	}
/* RAM TEK COLOR */
	if (*nxt > 0) {
/* PLOT X AXIS */
	    axis3dh_(&c_b27, &c_b27, &c_b27, &c_b27, &c_b27, pgx, xt, nxt, &
		    xlen, &xmin, &xmax, tx, tsx, fsx, &iopt, 1L);
	}
	if (*nyt > 0) {
/* PLOT Y AXIS */
	    axis3dh_(&c_b27, &c_b27, &c_b27, &c_b27, &c_b41, pgy, yt, nyt, &
		    ylen, &ymin, &ymax, ty, tsy, fsy, &iopt, 1L);
	}
	if (*nzt > 0) {
/* PLOT Z AXIS */
	    r__1 = -(doublereal)zlen;
	    axis3dh_(&c_b27, &c_b27, &c_b27, &c_b41, &c_b27, pgz, zt, nzt, &
		    r__1, &zmin, &zmax, tz, tsz, fsz, &iopt, 1L);
	}
    }
    if (jf == 2) {
	r__1 = (real) icol[2];
	plot_(&r__1, &c_b27, &c__0);
    }

/* 	BEGIN SURFACE PLOTTING */

/* RAM TEK COLOR */
    dx = (float)1.;
    dy = (float)1.;
    if (xmax - xmin != (float)0.) {
	dx = xlen / (xmax - xmin);
    }
    if (ymax - ymin != (float)0.) {
	dy = ylen / (ymax - ymin);
    }

    i__1 = -(*n);
    triangc_(&x[1], &y[1], &i__1, itt, &nzz, &m, ip, ib, &nw, &l, &nzz, &ie, &
	    ibe, &ite);
    i__1 = m;
    for (i = 1; i <= i__1; ++i) {
	for (j = 1; j <= 3; ++j) {
	    k1 = itt[i + j * 2000 - 2001];
	    xx[j - 1] = (x[k1] - xmin) * dx;
	    yy[j - 1] = (y[k1] - ymin) * dy;
	    zz[j - 1] = (z[k1] - zmin) * dy;
/* L15: */
	}
	xx[3] = xx[0];
	yy[3] = yy[0];
	zz[3] = zz[0];
	nc = 4;
	ierr = 0;
	if (i == m) {
	    ierr = 1;
	}
	if (hidden) {
	    sketch_(xx, yy, zz, &nc, &ierr);
	} else {
	    ierr = 3;
	    i__2 = nc;
	    for (jf = 1; jf <= i__2; ++jf) {
		plt3dh_(&xx[jf - 1], &yy[jf - 1], &zz[jf - 1], &ierr);
		ierr = 2;
/* L25: */
	    }
	}
	if (ierr < 0) {
	    cterm_(&c__1);
	    printf("\n*** TRIG3DH: SKETCH ERROR HAS OCCURRED ***\n");
	    cterm_(&c_n1);
	}
/* L50: */
    }
    if (! hidden) {
	plt3dh_(&xx[jf - 1], &yy[jf - 1], &zz[jf - 1], &c__3);
    }

/* 	FINISH ROUTINE */

/* PEN UP */
/* L999: */
    plot_(&c_b27, &c_b27, &c__3);
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
} /* trig3dh_ */

