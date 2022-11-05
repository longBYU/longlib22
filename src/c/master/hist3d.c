
/* *** LAST REVISED ON 23-DEC-1993 06:28:27.45 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]HIST3D.C */

#include "my.h"

/* Common Block Declarations */

struct {
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

/* Subroutine */ int hist3d_(a, inx, iny, nx, ny, psi, phi, theta, dv, zmin, 
	xh, yh, zh, iflag, iaxis, xt, nxt, xastart, xaend, tx, tsx, pgx, fsx, 
	yt, nyt, yastart, yaend, ty, tsy, pgy, fsy, zt, nzt, tz, tsz, pgz, 
	fsz, aminin, amaxin, icol)
real *a;
integer *inx, *iny, *nx, *ny;
real *psi, *phi, *theta, *dv, *zmin, *xh, *yh, *zh;
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
    integer a_dim1, a_offset, i__1, i__2;
    real r__1, r__2;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe(), do_fio();

    /* Local variables */
    extern /* Subroutine */ int cube_();
    static real amin, amax;
    static integer ierr;
    static real xlen, ylen, zlen;
    static integer iopt;
    extern /* Subroutine */ int plot_(), scale_(), frame_();
    static integer icore;
    extern /* Subroutine */ int cterm_();
    static real x1, y1, z1, y2, x2, z2;
    extern /* Subroutine */ int plt3dh_();
    static integer jf;
    static real sf;
    static logical hidden;
    static real dx, dy, dz;
    static integer iy, ix;
    extern /* Subroutine */ int plotnd_(), init3dh_(), axis3dh_();
    static real daa;
    static integer mne, mnh;
    static real pas[2];
    static integer ilu;

/* 	CREATED BY D. LONG     FEB, 1986	AT JPL */

/* 	ROUTINE TO PLOT DATA IN 3-D COLUMN FORM WITH HIDDEN LINE REMOVAL */
/* 	USING THE INIT3DH ROUTINES. */

/* 	A	(R) ARRAY A(INX,INY) CONTAINING Z AXIS DATA */
/* 	INX,INY (I) DIMENSION OF A ARRAY */
/* 	NX,NY	(I) INDICATING SIZE OF A ARRAY TO PLOT */
/* 	PSI,PHI,THETA (R) ANGLES (IN DEGREES) OF INIT3DH */
/* 	DV	(R) PERSPECTIVE FACTOR OF INIT3DH (9999 = NO PERSPECTIVE) */
/* 		    DV < 0 DO NOT INITIALIZE INIT3DH */
/* 	ZMIN	(R) REFERENCE PLANE VALUE FOR Z AXIS */
/* 	XH,YH,ZH (R) LENGTH OF EACH AXIS (INCHES) */
/* 	IFLAG	(I) PLOT FLAG */
/* 		>1000	REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER */
/* 		< 0	REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT */
/* 		= 0	CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT */
/* 		> 0	SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED) */
/* 	(ONE'S DIGIT) = 2 USE RAM TEK COLOR CONTROL ARRAY */
/* 		      = 1 DO NOT USE RAM TEK COLOR ARRAY */
/* 	(TEN'S DIGIT) = 0 NO HIDDEN LINE REMOVAL FOR AXIS */
/* 		      = 1 HIDDEN LINE REMOVAL OF AXIS */
/* 		      = 2 NO HIDDEN LINES (SKETCH STILL USED) */
/* 		      = 3 NO HIDDEN LINES (SKETCH NOT USED) */
/* 	(HUNDRED'S)   = 0 ASK WHICH SCREEN DEVICE TO USE */
/* 		      <>0 SCREEN DEVICE CODE NUMBER */
/* 	IAXIS	(I) AXIS OPTION FLAG */
/* 			= 0 DO NOT PLOT AXIS--FOLLOWING VARIABLES NOT ACCESSED */
/* 			< 0 PLOT AXIS, USE INPUT Z AXIS SCALE */
/* 			> 0 PLOT AXIS, USE COMPUTED Z AXIS SCALE */
/* 	(ONE'S DIGIT)	= 1 PLOT AXIS, Y AXIS SCALE--VARIABLES ACCESSED */
/* 			= 2 PLOT AXIS, AUTO SCALE Y AXIS--VARIABLES ACCESSED */
/* 	XT,YT,ZT	(B) STRINGS FOR AXIS TITLES */
/* 	NXT,NYT,NZT	(I) LENGTH OF AXIS TITLES */
/* 			     IF ZERO THEN THAT AXIS NOT PLOTTED */
/* 	XASTART,YASTART	(R) AXIS START VALUES */
/* 	XAEND,YAEND	(R) AXIS END VALUES */
/* FOLLOWING ONLY ACCESSED IF IAXIS<>0 */
/* 	TX,TY,TZ	(R) NUMBER OF TICK MARKS (SEE AXIS3DH) */
/* 	TSX,TSY,TSZ	(R) SIZE OF TITLE AND NUMBERS OF AXIS */
/* 			  IF LESS THAN ZERO DO NOT AUTO-SCALE BY (x10^POWER) */
/* 	PGX,PGY,PGZ	(R) ROTATION OF TEXT AND TICKS AROUND AXIS (DEG) */
/* 	FSX,FSY,FSZ	(R) NUMBER FORMAT OF AXISES (SEE AXIS3DH) */
/* 	AMININ,AMAXIN 	(R) ZAXIS SCALING FACTORS (ONLY NEEDED IF IAXIS < 0) */

/* 	ICOL		(I) COLOR INDEX TABLE (ACCESSED IF 1'S DIGIT OF IFLAG=2) */
/* 				ICOL(1) : AXIS COLOR */
/* 				ICOL(2) : COLUMNS */
/* 			    NOTE: IF SKETCH IS USED FOR BOTH AXIS AND COLUMNS */
/* 			    THEN ENTIRE PLOT IS IN COLUMN COLOR */


    /* Parameter adjustments */
    --icol;
    a_dim1 = *inx;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */

/* 	INSURE THAT WE HAVE AT LEAST A MINIMUM SIZE WORKSPACE */

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

/* 	DETERMINE MAX/MIN Z VALUES */

    if (*iaxis < 0) {
	amax = *amaxin;
	amin = *aminin;
    } else {
	amax = *zmin;
	amin = *zmin;
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

/* 	SMOOTH Z VALUES IF DESIRED */

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
/* PUT TERMINAL IN PLOT MODE */
    }

    hidden = TRUE_;
    iopt = jf % 10000 / 10;
    if (iopt == 3) {
	iopt = 0;
	hidden = FALSE_;
    }
    jf %= 10;

/* 	INITIALIZE 3DH PACKAGE */

    mne = 4;		/* MAX NUMBER OF EDGES */
    mnh = 0;		/* NO HOLES */
    icore = (mne * 5 + 25 + (mnh << 2)) * *nx * *ny * 6;
    if (*iaxis != 0) {
	icore += 10000;
    }
/* ESTIMATED AXISES SPACE */
    if (icore > go_1.isize) {
	cterm_(&c__1);
	printf("\n*** HIST3D /go/ INTERNAL STORAGE TOO SMALL ***\n");
	cterm_(&c_n1);
    }
    sf = (float)1.;	/* SCALE FACTOR */
    if (iopt == 2) {
	sf = (float)-1.;
    }
/* NO HIDDEN LINE REMOVAL FOR SKETCH */
    if (*dv > (float)0.) {
	init3dh_(&c_b15, &c_b15, &c_b15, psi, phi, theta, &sf, dv, &mne, &mnh)
		;
    }

/* 	PLOT AXES IF DESIRED */

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
    dx = xlen / (i__2 = *nx + 1, abs(i__2));
    dy = ylen / (i__2 = *ny + 1, abs(i__2));
    dz = (float)1.;
    if (amax - amin != (float)0.) {
	dz = zlen / (amax - amin);
    }
    z1 = *zmin;
    ierr = 0;

    i__2 = abs(*ny);
    for (iy = 1; iy <= i__2; ++iy) {
/* FOR EACH Y CELL */
	y1 = (iy - 1) * dy;
	y2 = iy * dy;
	i__1 = abs(*nx);
	for (ix = 1; ix <= i__1; ++ix) {
/* FOR EACH X CELL */
	    x1 = (ix - 1) * dx;
	    x2 = ix * dx;
	    z2 = (a[ix + iy * a_dim1] - amin) * dz;
	    ierr = 0;
	    if (ix == abs(*nx) && iy == abs(*ny)) {
		ierr = 1;
	    }
	    if (z1 != z2) {
		cube_(&x1, &x2, &y1, &y2, &z1, &z2, &ierr, &hidden);
	    }
	    if (ierr < 0) {
		cterm_(&c__1);
		printf("\n*** WARNING: SKETCH ERROR HAS OCCURED IN HIST3D ***\n");
		cterm_(&c_n1);
	    }
/* L50: */
	}
    }

/* 	FINISH ROUTINE */

    if (! hidden) {
	plt3dh_(&x1, &y1, &z1, &c__3);
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
/* PUT TERMINAL TEXT MODE */
    }
    return 0;
} /* hist3d_ */


/* Subroutine */ int cube_(x1, x2, y1, y2, z1, z2, ierr, hide)
real *x1, *x2, *y1, *y2, *z1, *z2;
integer *ierr;
logical *hide;
{
    static integer i;
    extern /* Subroutine */ int plt3dh_();
    static integer nc, ip;
    static real xx[5];
    extern /* Subroutine */ int sketch_();
    static real yy[5], zz[5];
    static integer ier;


/* 	PLOTS A 3D SOLID 'CUBE' USING SKETCH OR PLOT3DH */

/* 	X1,Y1,Z1 (R) ONE CORNER OF CUBE */
/* 	X2,Y2,Z2 (R) OPOSITE CORNER OF CUBE */
/* 	IERR	 (I) OPTION/ERR FLAG FOR LAST CALL TO SKETCH */
/* 	HIDE	 (L) IF TRUE USE SKETCH ELSE USE PLT3DH */


    ier = 0;
    nc = 5;

    xx[0] = *x1;
    xx[1] = *x2;
    xx[2] = *x2;
    xx[3] = *x1;
    xx[4] = *x1;
    yy[0] = *y1;
    yy[1] = *y1;
    yy[2] = *y2;
    yy[3] = *y2;
    yy[4] = *y1;
    zz[0] = *z1;
    zz[1] = *z1;
    zz[2] = *z1;
    zz[3] = *z1;
    zz[4] = *z1;
    if (*hide) {
	sketch_(xx, yy, zz, &nc, &ier);
/* BOTTOM */
    } else {
	ip = 3;
	for (i = 1; i <= 5; ++i) {
	    plt3dh_(&xx[i - 1], &yy[i - 1], &zz[i - 1], &ip);
	    ip = 2;
/* L1: */
	}
    }
    if (ier < 0) {
	goto L10;
    }
    xx[0] = *x1;
    xx[1] = *x2;
    xx[2] = *x2;
    xx[3] = *x1;
    xx[4] = *x1;
    yy[0] = *y1;
    yy[1] = *y1;
    yy[2] = *y2;
    yy[3] = *y2;
    yy[4] = *y1;
    zz[0] = *z2;
    zz[1] = *z2;
    zz[2] = *z2;
    zz[3] = *z2;
    zz[4] = *z2;
    if (*hide) {
	sketch_(xx, yy, zz, &nc, &ier);
/* TOP */
    } else {
	ip = 3;
	for (i = 1; i <= 5; ++i) {
	    plt3dh_(&xx[i - 1], &yy[i - 1], &zz[i - 1], &ip);
	    ip = 2;
/* L2: */
	}
    }
    if (ier < 0) {
	goto L10;
    }
    xx[0] = *x1;
    xx[1] = *x1;
    xx[2] = *x1;
    xx[3] = *x1;
    xx[4] = *x1;
    yy[0] = *y1;
    yy[1] = *y1;
    yy[2] = *y2;
    yy[3] = *y2;
    yy[4] = *y1;
    zz[0] = *z1;
    zz[1] = *z2;
    zz[2] = *z2;
    zz[3] = *z1;
    zz[4] = *z1;
    if (*hide) {
	sketch_(xx, yy, zz, &nc, &ier);
/* LEFT SIDE */
    } else {
	ip = 3;
	for (i = 1; i <= 5; ++i) {
	    plt3dh_(&xx[i - 1], &yy[i - 1], &zz[i - 1], &ip);
	    ip = 2;
/* L3: */
	}
    }
    if (ier < 0) {
	goto L10;
    }
    xx[0] = *x2;
    xx[1] = *x2;
    xx[2] = *x2;
    xx[3] = *x2;
    xx[4] = *x2;
    yy[0] = *y1;
    yy[1] = *y1;
    yy[2] = *y2;
    yy[3] = *y2;
    yy[4] = *y1;
    zz[0] = *z1;
    zz[1] = *z2;
    zz[2] = *z2;
    zz[3] = *z1;
    zz[4] = *z1;
    if (*hide) {
	sketch_(xx, yy, zz, &nc, &ier);
/* RIGHT SIDE */
    } else {
	ip = 3;
	for (i = 1; i <= 5; ++i) {
	    plt3dh_(&xx[i - 1], &yy[i - 1], &zz[i - 1], &ip);
	    ip = 2;
/* L4: */
	}
    }
    if (ier < 0) {
	goto L10;
    }
    xx[0] = *x1;
    xx[1] = *x2;
    xx[2] = *x2;
    xx[3] = *x1;
    xx[4] = *x1;
    yy[0] = *y1;
    yy[1] = *y1;
    yy[2] = *y1;
    yy[3] = *y1;
    yy[4] = *y1;
    zz[0] = *z1;
    zz[1] = *z1;
    zz[2] = *z2;
    zz[3] = *z2;
    zz[4] = *z1;
    if (*hide) {
	sketch_(xx, yy, zz, &nc, &ier);
/* FRONT */
    } else {
	ip = 3;
	for (i = 1; i <= 5; ++i) {
	    plt3dh_(&xx[i - 1], &yy[i - 1], &zz[i - 1], &ip);
	    ip = 2;
/* L5: */
	}
    }
    if (ier < 0) {
	goto L10;
    }
    xx[0] = *x1;
    xx[1] = *x2;
    xx[2] = *x2;
    xx[3] = *x1;
    xx[4] = *x1;
    yy[0] = *y2;
    yy[1] = *y2;
    yy[2] = *y2;
    yy[3] = *y2;
    yy[4] = *y2;
    zz[0] = *z1;
    zz[1] = *z1;
    zz[2] = *z2;
    zz[3] = *z2;
    zz[4] = *z1;
    if (*hide) {
	sketch_(xx, yy, zz, &nc, ierr);
/* BACK */
    } else {
	ip = 3;
	for (i = 1; i <= 5; ++i) {
	    plt3dh_(&xx[i - 1], &yy[i - 1], &zz[i - 1], &ip);
	    ip = 2;
/* L6: */
	}
    }
L10:
    *ierr = ier;
    return 0;
} /* cube_ */

