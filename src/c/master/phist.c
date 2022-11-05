
/* *** LAST REVISED ON  7-JAN-1994 11:56:51.89 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]PHIST.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    real xm, dx, ym, dy;
} cphist_;

#define cphist_1 cphist_

/* Table of constant values */

static integer c__3 = 3;
static real c_b3 = (float)1.;
static integer c_n1 = -1;
static real c_b5 = (float)0.;
static real c_b8 = (float)90.;
static integer c__0 = 0;
static integer c__2 = 2;
static integer c__4 = 4;
static integer c__5 = 5;
static integer c__1 = 1;
static real c_b70 = (float).06;

/* Subroutine */ int phist_(a, npts, title, nt, xl, yl, sub, ns, xlabel, nx, 
	xmin, xmax, amax, iflag, ishad, amean, sigma, icol)
real *a;
integer *npts;
char *title;
integer *nt;
real *xl, *yl;
char *sub;
integer *ns;
char *xlabel;
integer *nx;
real *xmin, *xmax, *amax;
integer *iflag, *ishad;
real *amean, *sigma;
integer *icol;
{
    /* Initialized data */

    static logical repeat = FALSE_;
    static real t1 = (float).1;
    static real xorg = (float)1.;
    static real yorg = (float)1.1;
    static real ylen = (float)4.;
    static real xlen = (float)7.;
    static real cs = (float).2;
    static real cst = (float).25;
    static real csm = (float).14;
    static real t = (float).2;

    /* System generated locals */
    integer i__1;
    real r__1, r__2;

    /* Local variables */
    static integer nadd, iflg;
    extern /* Subroutine */ int rect_(), axis_(), plot_();
    static integer i, m;
    extern /* Subroutine */ int shade_();
    static real w[15];
    extern /* Subroutine */ int frame_(), cterm_();
    static real width;
    static integer n1, n2;
    static real x0, x1, y0, y1, x2, x3, x4;
    static integer ic[4], jf;
    static real cw, xp, xs[5], ys[5], yp;
    extern /* Subroutine */ int number_(), plotnd_(), symbol_();
    static real ang;
    static integer ilu, nnx;


/* 	CREATED BY D. LONG    AUG, 1983	AT JPL */

/* 	GENERALIZED ROUTINE TO PLOT HISTOGRAMS */

/* 	A	REAL	ARRAY CONTAINING HEIGHT OF HISTOGRAM COLUMNS */
/* 	NPTS	INT	NUMBER OF POINTS IN A */
/* 	TITLE	CHAR	TITLE OF HISTOGRAM */
/* 	NT	INT	NUMBER OF CHARACTERS IN TITLE STRING */
/* 			< 0 USE COLOR ARRAY */
/* 	XL	REAL	LENGTH OF X AXIS */
/* 	YL	REAL	LENGTH OF Y AXIS */
/* 	SUB	CHAR	SUBTITLE OF HISTOGRAM */
/* 	NS	INT	NUMBER OF CHARACTERS IN SUB STRING */
/* 	XLABEL	CHAR	X AXIS LABEL OF HISTOGRAM */
/* 	NX	INT	NUMBER OF CHARACTERS IN XLABEL STRING */
/* 	XMIN	REAL	MINIMUM VALUE TO BE PLOTTED ON X AXIS */
/* 	XMAX	REAL	MAXIMUM VALUE TO BE PLOTTED ON X AXIS */
/* 	AMAX	REAL	MAXIMUM VALUE IN ARRRAY */
/* 	IFLAG	INT	FUNCTION CONTROL FLAG */
/* 			>10000	REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER */
/* 			< 0	REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT) */
/* 			= 0	CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT */
/* 			> 0	SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED) */
/* 		ONE'S DIGIT = 2 PLOT A VALUE ATOP HISTOGRAM COLUMN */
/* 			    = 1 DO NOT PLOT NUMBERS */
/* 			    = 0 DO NOT PLOT AXISES */
/* 		TEN'S DIGIT     SCREEN DEVICE CONTROL */
/* 			    = 0 ASK SCREEN DEVICE TYPE */
/* 	ISHAD	INT	SHADING CONTROL FLAG */
/* 			< 0	SHADE WITH SOLID LINE */
/* 			= 0	NO SHADING */
/* 			> 0	SHADE WITH LINE TYPE ISHAD */
/* 	AMEAN	REAL	LINE INDICATING MEAN (IN UNITS OF XMIN, XMAX) */
/* 	SIGMA	REAL	LINES INDICATING 1 SIGMA DEVIATIONS FROM MEAN */
/* 			> 0	MEAN AND SIGMA VALUES PLOTTED */
/* 			= 0	ONLY MEAN VALUE PLOTTED */
/* 			< 0	MEAN AND SIGMA VALUES NOT PLOTTED */
/* 	ICOL	INT	PEN COLOR LIST (ACCESSED ONLY IF NT < 0 */
/* 			ICOL(1) AXIS LINE COLOR */
/* 			ICOL(2) AXIS NUMBERS COLOR */
/* 			ICOL(3) AXIS TITLE COLOR */
/* 			ICOL(4) AXIS EXPONENT COLOR */
/* 			ICOL(5) TITLE COLOR */
/* 			ICOL(6) SUBTITLE COLOR */
/* 			ICOL(7) MEAN MARK COLOR */
/* 			ICOL(8) SIGMA MARK COLOR */
/* 			ICOL(9) HISTOGRAM COLUMN COLORS (RETURN COLOR) */
/* 			ICOL(10) HISTOGRAM COLUM LABEL COLOR */

    /* Parameter adjustments */
    --icol;
    --a;

    /* Function Body */

    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();
	}			/* CLOSE PLOT PACKAGE */
	repeat = FALSE_;
	return 0;
    }
    xlen = dabs(*xl);
    ylen = dabs(*yl);
    if (xlen == (float)0. || ylen == (float)0.) {
	return 0;
    }
/* ERROR RETURN */
    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = -jf / 10;
	frame_(&c__3, &ilu, &xorg, &yorg, &c_b3);	/* OPEN PLOT OUTPUT */
    } else {
	cterm_(&c_n1);				/* RETURN SCREEN TO GRAPHICS */
	jf %= 10;
    }
    jf %= 10;
    m = 0;
    if (*ishad > 0 && *ishad < 11) {
	m = *ishad;
    }
/* SELECT SHADE LINE TYPE */
    iflg = abs(*iflag) % 10;
    cphist_1.ym = (float)0.;
/* BOTTOM Y AXIS */
    cphist_1.dy = (*amax - cphist_1.ym) / ylen;
/* Y SCALE FACTOR */
    nadd = 0;
    if (*nt < 0) {
	nadd = 100000;
/* COLOR AXIS */
	ic[0] = icol[1];
	ic[1] = icol[2];
	ic[2] = icol[3];
	ic[3] = icol[4];
    }
    if (jf != 0) {
	i__1 = nadd + 1001;
	axis_(&c_b5, &c_b5, " ", &i__1, &ylen, &c_b8, &cphist_1.ym, &
		cphist_1.dy, &n1, &n2, ic, 1L);
    }
/* PLOT Y AXIS */
    nnx = *nx;
    if (nnx < 1) {
	nnx = 1;
    }
    cphist_1.dx = (*xmax - *xmin) / xlen;
    cphist_1.xm = *xmin;
    if (jf != 0) {
	i__1 = -nnx - nadd;
	axis_(&c_b5, &c_b5, xlabel, &i__1, &xlen, &c_b5, &cphist_1.xm, &
		cphist_1.dx, &n1, &n2, ic);
    }
/* PLOT X AXIS */
    xp = (float)0.;
    yp = ylen + cs + csm + (float).25;
    if (jf != 0) {
	if (*nt < 0) {
	    r__1 = (real) icol[5];
	    plot_(&r__1, &c_b5, &c__0);
	}
/* PEN COLOR */
	if (*nt != 0) {
	    i__1 = abs(*nt);
	    symbol_(&xp, &yp, &cst, title, &c_b5, &i__1, &c_n1);
	}
/* TITLE */
	if (*nt < 0) {
	    r__1 = (real) icol[6];
	    plot_(&r__1, &c_b5, &c__0);
	}
/* PEN COLOR */
	if (*ns > 0) {
	    r__1 = yp - cs - (float).05;
	    symbol_(&xp, &r__1, &cs, sub, &c_b5, ns, &c_n1);
	}
/* SUBTITLE */
	if (*nt < 0) {
	    r__1 = (real) icol[7];
	    plot_(&r__1, &c_b5, &c__0);
	}
/* PEN COLOR */
	if (*sigma >= (float)0.) {
/* PLOT MEAN */
	    x1 = (*amean - *xmin) / cphist_1.dx;
/* LOCATE MEAN */
	    y0 = (float)0.;
	    y1 = ylen + csm;
	    x2 = x1 - csm * (float)1.5;
	    r__1 = x1 - t1;
	    r__2 = y0 - t1;
	    plot_(&r__1, &r__2, &c__3);
/* START TICK MARK */
	    plot_(&x1, &y0, &c__2);
/* CENTER TICK MARK */
	    r__1 = x1 + t1;
	    r__2 = y0 - t1;
	    plot_(&r__1, &r__2, &c__2);
/* END TICK MARK */
	    r__1 = y0 - t1;
	    plot_(&x1, &r__1, &c__3);
/* START LINE */
	    plot_(&x1, &y1, &c__2);
/* END LINE */
	    r__1 = x1 - t;
	    plot_(&r__1, &y1, &c__3);
/* PUT ON HAT */
	    r__1 = x1 + t;
	    plot_(&r__1, &y1, &c__2);
/* END HAT */
	    r__1 = y1 + (float).05;
	    symbol_(&x2, &r__1, &csm, "MEAN", &c_b5, &c__4, &c_n1, 4L);
	    if (*nt < 0) {
		r__1 = (real) icol[8];
		plot_(&r__1, &c_b5, &c__0);
	    }
/* PEN COLOR */
	    if (*sigma > (float)0.) {
/* PLOT SIGMA */
		y1 = y1 - csm - (float).05;
		x2 = (*amean - *sigma - *xmin) / cphist_1.dx;
/* MEAN - SIGMA */
		x3 = (*amean + *sigma - *xmin) / cphist_1.dx;
/* MEAN + SIGMA */
		x4 = csm * (float)2.1;
		r__1 = x2 - t1;
		r__2 = y0 - t1;
		plot_(&r__1, &r__2, &c__3);
/* START TICK MARK */
		plot_(&x2, &y0, &c__2);
/* CENTER TICK MARK */
		r__1 = x2 + t1;
		r__2 = y0 - t1;
		plot_(&r__1, &r__2, &c__2);
/* END TICK MARK */
		r__1 = y0 - t1;
		plot_(&x2, &r__1, &c__3);
/* START LINE */
		plot_(&x2, &y1, &c__2);
/* END LINE */
		r__1 = x2 - t;
		plot_(&r__1, &y1, &c__3);
/* PUT ON HAT */
		r__1 = x2 + t;
		plot_(&r__1, &y1, &c__2);
/* END HAT */
		r__1 = x2 - x4;
		r__2 = y1 + (float).05;
		symbol_(&r__1, &r__2, &csm, "SIGMA", &c_b5, &c__5, &c_n1, 5L);

		r__1 = x3 - t1;
		r__2 = y0 - t1;
		plot_(&r__1, &r__2, &c__3);
/* START TICK MARK */
		plot_(&x3, &y0, &c__2);
/* CENTER TICK MARK */
		r__1 = x3 + t1;
		r__2 = y0 - t1;
		plot_(&r__1, &r__2, &c__2);
/* END TICK MARK */
		r__1 = y0 - t1;
		plot_(&x3, &r__1, &c__3);
/* START LINE */
		plot_(&x3, &y1, &c__2);
/* END LINE */
		r__1 = x3 - t;
		plot_(&r__1, &y1, &c__3);
/* PUT ON HAT */
		r__1 = x3 + t;
		plot_(&r__1, &y1, &c__2);
/* END HAT */
		r__1 = x3 - x4;
		r__2 = y1 + (float).05;
		symbol_(&r__1, &r__2, &csm, "SIGMA", &c_b5, &c__5, &c_n1, 5L);

	    }
	}
    }

    width = xlen / (real) (*npts);
    cw = width - (float).02;
    if (cw < (float)0.) {
	cw = width;
    }
    if (width > (float).18) {
	cw = (float).18;
    }
    ang = (float)45.;
    x0 = (float)0.;
    y0 = cphist_1.ym;
    x1 = width / (float)2. - cw / (float)2.;

    if (*nt < 0) {
	r__1 = (real) icol[9];
	plot_(&r__1, &c_b5, &c__0);
    }
/* PEN COLOR */
    i__1 = *npts;
    for (i = 1; i <= i__1; ++i) {
	y1 = (a[i] - cphist_1.ym) / cphist_1.dy;
	xs[0] = x0;
	ys[0] = y0 + (float).02;
	xs[1] = x0;
	ys[1] = y1;
	r__1 = x0 + width;
	rect_(&x0, &y0, &r__1, &y1);
/* PLOT HISTOGRAM */
	x0 += width;
	xs[2] = x0;
	ys[2] = y1;
	xs[3] = x0;
	ys[3] = y0 + (float).02;
	if (iflg == 2) {
	    if (*nt < 0) {
		r__1 = (real) icol[10];
		plot_(&r__1, &c_b5, &c__0);
	    }
/* PEN COLOR */
	    r__1 = x0 - x1;
	    r__2 = y1 + (float).08;
	    number_(&r__1, &r__2, &cw, &a[i], &c_b8, &c_b5, &c_n1);
	    if (*nt < 0) {
		r__1 = (real) icol[9];
		plot_(&r__1, &c_b5, &c__0);
	    }
/* PEN COLOR */
	}
	if (m != 0 && y1 > (float).02) {
/* ADD SHADING */
	    shade_(xs, ys, &c__4, &c__1, &c__2, &c_b70, &ang, w, &m, &c_b5, &
		    c_b3, &c_b5, &c_b3);
	    if (ang == (float)45.) {
/* ALTERNATE ANGLES */
		ang = (float)135.;
	    } else {
		ang = (float)45.;
	    }
	}
/* L100: */
    }
    plot_(&c_b5, &c_b5, &c__3);
    if (*iflag > 0) {
	cterm_(&c__2);
/* ASK IF CLEAR SCREEN */
	plotnd_();
/* CLOSE PLOTTER */
	repeat = FALSE_;
    }
    if (*iflag < 0) {
	repeat = TRUE_;
	cterm_(&c__1);
/* PUT TERMINAL IN TEXT MODE */
    }
    return 0;
} /* phist_ */

