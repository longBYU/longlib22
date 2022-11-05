
/* *** LAST REVISED ON  7-JAN-1994 12:48:09.21 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]SEISPL.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    real xm, dx, ym, dy;
} cseispl_;

#define cseispl_1 cseispl_

/* Table of constant values */

static real c_b2 = (float)1.2;
static real c_b4 = (float)1.;
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c__1 = 1;
static real c_b22 = (float)0.;
static integer c__0 = 0;
static real c_b42 = (float)90.;
static integer c__3 = 3;
static integer c_n3 = -3;

/* Subroutine */ int seispl_(x, y, z, nnd, npd, nn, np, iflag, ntype, size, 
	zero, xaxl, yaxl, xtitl, nxt, ytitl, nyt, title, nt, xmin, xmax, ymin,
	 ymax, icol)
real *x, *y, *z;
integer *nnd, *npd, *nn, *np, *iflag, *ntype;
real *size, *zero, *xaxl, *yaxl;
char *xtitl;
integer *nxt;
char *ytitl;
integer *nyt;
char *title;
integer *nt;
real *xmin, *xmax, *ymin, *ymax;
integer *icol;
{
    /* Initialized data */

    static logical repeat = FALSE_;

    /* System generated locals */
    integer y_dim1, y_offset, i__1, i__2, i__3;
    real r__1, r__2;
    char ch__1[1];

    /* Builtin functions */
    double r_nint(), r_int(), r_lg10(), r_sign();

    /* Local variables */
    static integer nadd;
    extern /* Subroutine */ int grid_(), axis_();
    static real xold, yold;
    extern /* Subroutine */ int plot_();
    static integer i, n;
    extern /* Subroutine */ int scale_(), frame_(), scalg_(), lgrid_(), 
	    cterm_(), lgaxs_();
    static integer n1, n2;
    static real x1, y1, z1, x2, y2;
    static integer ic[4], if_, jf, ii, ik;
    static real cs;
    static integer in, ip, pl, ix, iy;
    static real xl;
    static integer nx, ny;
    static real py[2], yl, xp, yp;
    extern /* Subroutine */ int newpen_(), plotnd_(), symbol_();
    static real gdx, gdy, ddx, ddy;
    static integer ilu;
    static real res;
    static integer inx, iny, ntp, ixx;


/* 	CREATED BY D. LONG       APR, 1985	AT JPL */

/* 	ROUTINE TO PLOT IN THE STYLES OFTEN USED IN SEISMIC PROCESSING */

/* 	X	REAL X DATA ARRAY DIMENSION X(NPD) */
/* 	Y	REAL Y DATA ARRAY DIMENSION Y(NPD,NND) */
/* 	Z	REAL OFFSET VALUE ARRAY DIMENSION Z(NN) */
/* 			OFFSET VALUE IS ADDED TO Y VALUE BEFORE PLOTTING. */
/* 			WHEN USING LOG SCALING NOTE THAT THIS OCCURS AFTER */
/* 			TAKING LOG OF DATA.  THIS ARRAY IS USED FOR VERTICALLY */
/* 			OFFSETTING DIFFERENT PLOTTED LINES. */
/* 	NND	INT  DIMENSION OF Y ARRAY */
/* 	NPD	INT  DIMENSION OF X,Y ARRAYS */
/* 	NN	INT  NUMBER OF LINES ARRAYS */
/* 	NP	INT  NUMBER OF POINTS TO PLOT */
/* 	IFLAG	INT */
/* 	  (MAG) >10000 REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER */
/* 		< 0  REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT) */
/* 		= 0  CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT */
/* 		> 0  SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED) */
/* 	  (ONE'S DIGIT) = 1 X LINEAR, Y LOGRITHMIC (BASE 10) */
/* 	  (ONE'S DIGIT) = 2 X LOGRITHMIC,Y LINEAR */
/* 	  (ONE'S DIGIT) = 3 X LOGRITHMIC,Y LOGRITHMIC */
/* 	  (ONE'S DIGIT) = 4 X LINEAR, Y LINEAR */
/* 	  (TEN'S DIGIT) = 0 NO AXIS OR GRID */
/* 	  (TEN'S DIGIT) = 1 PLOT BOX WITH AXIS TICKS */
/* 	  (TEN'S DIGIT) = 2 PLOT SOLID GRID */
/* 	  (TEN'S DIGIT) = 3 PLOT TICKED GRID W/O BOX */
/* 	  (TEN'S DIGIT) = 4 PLOT TICKED GRID WITH BOX */
/* 	  (TEN'S DIGIT) = 5 PLOT BOX WITH AXIS TICKS AND TICKED GRID */
/* 	  (TEN'S DIGIT) = 6 PLOT W/O BOX OR GRID BUT USE AXISES */
/* 	  (TEN'S DIGIT) = 7 PLOT SOLID LOGRITHMIC GRID */
/* 	  (TEN'S DIGIT) = 8 PLOT DOTTED LOGRITHMIC GRID */
/* 	  (TEN'S DIGIT) = 9 PLOT TICKED LOGRITHMIC GRID */
/*     (HUNDRED'S DIGIT) = 0 ASK WHICH SCREEN DEVICE TO USE */
/* 		      <>0 SCREEN DEVICE CODE NUMBER */
/* 	NTYPE	INT   PLOTTING TYPE CODE */
/* 			< 0 ZERO REFERENCE PLOTTED */
/* 	   MAG(NTYPE)	= 0 SYMBOLS ONLY */
/* 			= 1 SYMBOLS ONLY */
/* 			= 2 POINTS ONLY */
/* 			= 3 CONNECTED POINTS */
/* 			= 4 VERTICAL LINES FROM POINTS TO CENTER LINE */
/* 			= 5 VERTICAL LINES PLUS SYMBOL */
/* 			= 6 CONNECTED POINTS WITH VERTICAL LINES */
/* 			= 7 CONNECTED POINTS WITH VERTICAL LINES ON POSITIVE HALF */
/* 			= 8 CONNECTED POINTS WITH VERTICAL LINES ON NEGATIVE HALF */
/* 			= 9 AREA BETWEEN CONNECTED POINTS AND ZERO FILLED */
/* 			= 10 POSITIVE AREA BETWEEN POINTS AND ZERO FILLED */
/* 			= 11 NEGATIVE AREA BETWEEN POINTS AND ZERO FILLED */
/* 	SIZE	REAL  PLOTTED SYMBOL SCALE (NTYPE = 0,1, OR 4) */
/* 		      SPACING BETWEEN SOLID FILL LINES (NTYPE = 9,10,11) */
/* 		      SIZE < 0.0 WILL MAKE CENTER LINE DOTTED */
/* 	ZERO	REAL  VALUE USED AS PLOT ZERO */
/* 	XAXL	REAL  X AXIS LENGTH IN INCHES */
/* 		< 0  USE INPUT VALUE SCALING--AXIS PLOTTED */
/* 		> 0  USE AUTO SCALING--AXIS PLOTTED */
/* 	YAXL	REAL  Y AXIS LENGTH IN INCHES */
/* 		< 0  USE INPUT VALUE SCALING--AXIS PLOTTED */
/* 		> 0  USE AUTO SCALING--AXIS PLOTTED */

/* NOTE: 	XMIN,XMAX,YMIN,YMAX ARE ACCESSED IF XAXL OR YAXL < 0 */

/* 	XTITL	CHAR  X AXIS TITLE */
/* 	NXT	INT   NUMBER OF CHARACTERS IN X AXIS TITLE STRING */
/* 		< 0  TICKS ON INSIDE OF AXIS */
/* 		= 0  NO AXIS */
/* 		> 0  TICKS ON TITLE SIDE OF AXIS */
/* 	YTITL	CHAR  Y AXIS TITLE */
/* 	NYT	INT   NUMBER OF CHARACTERS IN Y AXIS TITLE STRING */
/* 		< 0  TICKS ON INSIDE OF AXIS */
/* 		= 0  NO AXIS */
/* 		> 0  TICKS ON TITLE SIDE OF AXIS */
/* 	TITLE	CHAR  PLOT TITLE */
/* 	NT	INT   NUMBER OF CHARACTERS IN PLOT TITLE */
/* 		= 0  NO TITLE */
/* 		< 0  USE COLOR ARRAY (REQUIRES XMIN,XMAX,YMIN,YMAX TOO) */
/* 	XMIN	REAL  MINIMUM VALUE DISPLAYED ON X AXIS */
/* 	XMAX	REAL  MAXIMUM VALUE DISPLAYED ON X AXIS */
/* 	YMIN	REAL  MINIMUM VALUE OF Y ARRAY */
/* 	YMAX	REAL  MAXIMUM VALUE OF Y ARRAY */
/* 	ICOL	INT   ARRAY OF PEN COLORS DIMENSIONED ICOL(NP+6) */
/* 			ICOL(1) = GRID COLOR */
/* 			ICOL(2) = AXIS LINE COLOR */
/* 			ICOL(3) = AXIS NUMBERS COLOR */
/* 			ICOL(4) = AXIS TITLE COLOR */
/* 			ICOL(5) = AXIS EXPONENT COLOR */
/* 			ICOL(6) = TITLE COLOR (COLOR UPON RETURN) */
/* 			ICOL(7) = POINT SET COLOR 1 */
/* 			ICOL(8) = POINT SET COLOR 2 */
/* 			   .	     .	          3 */

    /* Parameter adjustments */
    --icol;
    --z;
    y_dim1 = *npd;
    y_offset = y_dim1 + 1;
    y -= y_offset;
    --x;

    /* Function Body */
    cs = (float).21;

/* 	HANDLE PLOT PACKAGE INITIALIZATION */

/* TITLE CHARACTER SIZE */
    pl = 3;
/* DEFAULT PRINTER DATA FILE= FOR003.DAT */
    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();
	}
/* CLOSE PLOT PACKAGE */
	repeat = FALSE_;
	return 0;
    }
    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = -(jf / 100);
/* SCREEN DEVICE, CLEAR SCREEN */
	frame_(&pl, &ilu, &c_b2, &c_b2, &c_b4);
/* INTIALIZE PLOT PACKAGE */
    } else {
	cterm_(&c_n1);
/* 		CALL NEWPAGE				!NEW PAGE */
/* RESTORE PLOT MODE */
	jf %= 100;
    }
    jf %= 100;
    if_ = jf;
    if (if_ > 10) {
	if_ %= 10;
    }
    jf -= if_;
    nx = (r__1 = r_nint(xaxl), dabs(r__1));
/* GRID SIZES */
    ny = (r__1 = r_nint(yaxl), dabs(r__1));

/* 	DETERMINE SCALING PARAMETERS */

    if (*xaxl > (float)0.) {
/* INPUT SCALING */
	cseispl_1.xm = x[1];
	cseispl_1.dx = x[1];
	i__1 = *np;
	for (i = 2; i <= i__1; ++i) {
/* Computing MAX */
	    r__1 = x[i];
	    cseispl_1.xm = dmax(r__1,cseispl_1.xm);
/* Computing MIN */
	    r__1 = x[i];
	    cseispl_1.dx = dmin(r__1,cseispl_1.dx);
/* L4: */
	}
	py[0] = cseispl_1.xm;
	py[1] = cseispl_1.dx;
	if (if_ == 2 || if_ == 3) {
	    r__1 = dabs(*xaxl);
	    scalg_(py, &r__1, &c__2, &c__1, &c__1, &cseispl_1.xm, &
		    cseispl_1.dx);
/* SMOOTH SCALE FACTORS */
	    ik = -1;
	    gdx = (float)1. / cseispl_1.dx;
	    nx = cseispl_1.dx * dabs(*xaxl);
	    inx = -1;
	} else {
	    r__1 = dabs(*xaxl);
	    scale_(py, &r__1, &c__2, &c__1, &c__1, &cseispl_1.xm, &
		    cseispl_1.dx);
/* SMOOTH SCALE FACTORS */
	    ik = 0;
	    gdx = (float)1.;
	    inx = 1;
	}
    } else {
	if (if_ == 2 || if_ == 3) {
	    cseispl_1.xm = dabs(*xmin) + (float)1e-25;
	    if (cseispl_1.xm != r_int(&cseispl_1.xm)) {
		cseispl_1.xm = r_int(&cseispl_1.xm) - (float)1.;
	    }
	    r__2 = dabs(*xmax) + (float)1e-25;
	    r__1 = r_lg10(&r__2);
	    cseispl_1.dx = r_int(&r__1) + (float)1.;
	    cseispl_1.dx = (cseispl_1.dx - cseispl_1.xm) / dabs(*xaxl);
	    gdx = (float)1. / cseispl_1.dx;
	    ik = -1;
	    nx = cseispl_1.dx * dabs(*xaxl);
	    inx = -1;
	} else {
	    cseispl_1.xm = *xmin;
	    cseispl_1.dx = (*xmax - *xmin) / dabs(*xaxl);
	    gdx = (float)1.;
	    ik = 0;
	    inx = 1;
	}
    }
    if (*yaxl > (float)0.) {
/* INPUT SCALING */
	cseispl_1.ym = y[y_dim1 + 1];
	cseispl_1.dy = y[y_dim1 + 1];
	i__1 = *nn;
	for (n = 1; n <= i__1; ++n) {
	    i__2 = *np;
	    for (i = 1; i <= i__2; ++i) {
/* Computing MAX */
		r__1 = y[i + n * y_dim1] + z[n];
		cseispl_1.ym = dmax(r__1,cseispl_1.ym);
/* Computing MIN */
		r__1 = y[i + n * y_dim1] + z[n];
		cseispl_1.dy = dmin(r__1,cseispl_1.dy);
/* L5: */
	    }
	}
	py[0] = cseispl_1.ym;
	py[1] = cseispl_1.dy;
	if (if_ == 1 || if_ == 3) {
	    r__1 = dabs(*yaxl);
	    scalg_(py, &r__1, &c__2, &c__1, &c__1, &cseispl_1.ym, &
		    cseispl_1.dy);
/* SMOOTH SCALE FACTORS */
	    --ik;
	    gdy = (float)1. / cseispl_1.dy;
	    ny = cseispl_1.dy * dabs(*yaxl);
	    iny = -1;
	} else {
	    r__1 = dabs(*yaxl);
	    scale_(py, &r__1, &c__2, &c__1, &c__1, &cseispl_1.ym, &
		    cseispl_1.dy);
/* SMOOTH SCALE FACTORS */
	    ++ik;
	    gdy = (float)1.;
	    iny = 1;
	}
    } else {
	if (if_ == 1 || if_ == 3) {
	    r__1 = dabs(*ymin) + (float)1e-25;
	    cseispl_1.ym = r_lg10(&r__1);
	    if (cseispl_1.ym != r_int(&cseispl_1.ym)) {
		cseispl_1.ym = r_int(&cseispl_1.ym) - (float)1.;
	    }
	    r__2 = dabs(*ymax) + (float)1e-25;
	    r__1 = r_lg10(&r__2);
	    cseispl_1.dy = r_int(&r__1) + (float)1.;
	    cseispl_1.dy = (cseispl_1.dy - cseispl_1.ym) / dabs(*yaxl);
	    gdy = (float)1. / cseispl_1.dy;
	    ny = cseispl_1.dy * dabs(*yaxl);
	    --ik;
	    iny = -1;
	} else {
	    cseispl_1.ym = *ymin;
	    cseispl_1.dy = (*ymax - *ymin) / dabs(*yaxl);
	    ++ik;
	    gdy = (float)1.;
	    iny = 1;
	}
    }
    if (jf == 0) {
	goto L77;
    }

/* 	PLOT GRID */

/* NO AXIS OR GRID */
    if (jf == 60) {
	goto L76;
    }
/* NO GRID */
    if (jf > 60) {
/* LOGRITHMIC GRID */
	ii = 0;
	if (jf == 70) {
	    ii = 1;
	}
	if (jf == 80) {
	    ii = 2;
	}
	i__2 = inx * nx;
	i__1 = iny * ny;
	lgrid_(&c_b22, &c_b22, &gdx, &gdy, &i__2, &i__1, &ii);
	goto L76;
    }
    if (jf >= 20) {
/* CARTESIAN GRID */
	if (jf >= 30) {
	    nx = -nx;
	}
	if (jf >= 40) {
	    ny = -ny;
	}
	if (*nt < 0) {
	    r__1 = (real) icol[1];
	    plot_(&r__1, &c_b22, &c__0);
	}
/* PEN COLOR */
	grid_(&c_b22, &c_b22, &gdx, &gdy, &nx, &ny);
/* PRODUCE GRID */
	if (jf == 50) {
	    jf = 10;
	}
    }
L76:
    nadd = 0;

/* 	PLOT AXES */

    if (*nt < 0) {
	nadd = 100000;
/* PEN COLOR */
	ic[0] = icol[2];
	ic[1] = icol[3];
	ic[2] = icol[4];
	ic[3] = icol[5];
    }
    ix = abs(*nxt);
    r__1 = (real) (*nxt);
    xl = dabs(*xaxl) * r_sign(&c_b4, &r__1);
/* AXIS LENGTH WITH TICK INFOR */
    if (*nxt != 0) {
	if (if_ == 2 || if_ == 3) {
	    i__2 = -ix - nadd;
	    lgaxs_(&c_b22, &c_b22, xtitl, &i__2, &xl, &c_b22, &cseispl_1.xm, &
		    cseispl_1.dx, ic);
/* X-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*yaxl);
		i__2 = ix + 100 + nadd;
		lgaxs_(&c_b22, &r__1, xtitl, &i__2, &xl, &c_b22, &
			cseispl_1.xm, &cseispl_1.dx, ic);
	    }
/* X-AXIS */
	} else {
	    i__2 = -ix - nadd;
	    axis_(&c_b22, &c_b22, xtitl, &i__2, &xl, &c_b22, &cseispl_1.xm, &
		    cseispl_1.dx, &n1, &n2, ic);
/* X-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*yaxl);
		i__2 = ix + 100 + nadd;
		axis_(&c_b22, &r__1, xtitl, &i__2, &xl, &c_b22, &cseispl_1.xm,
			 &cseispl_1.dx, &n1, &n2, ic);
	    }
/* X-AXIS */
	}
    }
    iy = abs(*nyt) + 1000;
    r__1 = (real) (*nyt);
    yl = dabs(*yaxl) * r_sign(&c_b4, &r__1);
    if (*nyt != 0) {
	if (if_ == 1 || if_ == 3) {
	    i__2 = iy + nadd;
	    lgaxs_(&c_b22, &c_b22, ytitl, &i__2, &yl, &c_b42, &cseispl_1.ym, &
		    cseispl_1.dy, ic);
/* Y-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*xaxl);
		i__2 = -iy - 100 - nadd;
		lgaxs_(&r__1, &c_b22, ytitl, &i__2, &yl, &c_b42, &
			cseispl_1.ym, &cseispl_1.dy, ic);
	    }
/* Y-AXIS */
	} else {
	    i__2 = iy + nadd;
	    axis_(&c_b22, &c_b22, ytitl, &i__2, &yl, &c_b42, &cseispl_1.ym, &
		    cseispl_1.dy, &n1, &n2, ic);
/* Y-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*xaxl);
		i__2 = -iy - 100 - nadd;
		axis_(&r__1, &c_b22, ytitl, &i__2, &yl, &c_b42, &cseispl_1.ym,
			 &cseispl_1.dy, &n1, &n2, ic);
	    }
/* Y-AXIS */
	}
    }
L77:

/* 	NOW PLOT DATA */

    res = dabs(*size);
    ntp = abs(*ntype);
    i__2 = *nn;
    for (in = 1; in <= i__2; ++in) {
	if (*nt < 0) {
	    r__1 = (real) icol[in + 6];
	    plot_(&r__1, &c_b22, &c__0);
	}
/* PEN COLOR */
	z1 = *zero + z[in];
	if (if_ == 1 || if_ == 3) {
	    r__1 = dabs(z1) + (float)1e-25;
	    z1 = r_lg10(&r__1);
	}
	z1 = (z1 - cseispl_1.ym) / cseispl_1.dy;
	ip = 3;
	i__1 = *np;
	for (i = 1; i <= i__1; ++i) {
	    x1 = x[i];
	    if (if_ == 2 || if_ == 3) {
		r__1 = dabs(x1) + (float)1e-25;
		x1 = r_lg10(&r__1);
	    }
	    y1 = y[i + in * y_dim1] + z[in];
	    if (if_ == 1 || if_ == 3) {
		r__1 = dabs(y1) + (float)1e-25;
		y1 = r_lg10(&r__1);
	    }
	    x1 = (x1 - cseispl_1.xm) / cseispl_1.dx;
	    y1 = (y1 - cseispl_1.ym) / cseispl_1.dy;
	    if (i == 1) {
		xold = x1;
	    }
	    if (i == 1) {
		yold = y1;
	    }
	    if (ntp == 0 || ntp == 1) {
/* SYMBOLS ONLY */
		r__1 = dabs(*size);
		ch__1[0] = in;
		symbol_(&x1, &y1, &r__1, ch__1, &c_b22, &c__1, &c_n1, 1L);
		if (*ntype < 0) {
/* ADD CENTER LINE */
		    if (*size < (float)0.) {
			newpen_(&c__2);
		    }
		    plot_(&xold, &z1, &c__3);
		    plot_(&x1, &z1, &c__2);
		    if (*size < (float)0.) {
			newpen_(&c__1);
		    }
		}
	    }
	    if (ntp == 2) {
/* DOTS ONLY */
		plot_(&x1, &y1, &c__3);
		plot_(&x1, &y1, &c__2);
		if (*ntype < 0) {
/* ADD CENTER LINE */
		    if (*size < (float)0.) {
			newpen_(&c__2);
		    }
		    plot_(&xold, &z1, &c__3);
		    plot_(&x1, &z1, &c__2);
		    if (*size < (float)0.) {
			newpen_(&c__1);
		    }
		}
	    }
	    if (ntp == 3) {
/* CONNECTED POINTS */
		if (*ntype < 0) {
		    plot_(&xold, &yold, &c__3);
		}
		plot_(&x1, &y1, &ip);
		if (*ntype < 0) {
/* ADD CENTER LINE */
		    if (*size < (float)0.) {
			newpen_(&c__2);
		    }
		    plot_(&xold, &z1, &c__3);
		    plot_(&x1, &z1, &c__2);
		    if (*size < (float)0.) {
			newpen_(&c__1);
		    }
		}
	    }
	    if (ntp == 4) {
/* VERTICAL LINES ONLY */
		plot_(&x1, &y1, &c__3);
		plot_(&x1, &z1, &c__2);
		if (*ntype < 0) {
/* ADD CENTER LINE */
		    if (*size < (float)0.) {
			newpen_(&c__2);
		    }
		    plot_(&x1, &z1, &c__3);
		    plot_(&xold, &z1, &c__2);
		    if (*size < (float)0.) {
			newpen_(&c__1);
		    }
		}
	    }
	    if (ntp == 5) {
/* VERTICAL LINES PLUS SYMBOL */
		r__1 = dabs(*size);
		ch__1[0] = in;
		symbol_(&x1, &y1, &r__1, ch__1, &c_b22, &c__1, &c_n1, 1L);
		plot_(&x1, &z1, &c__2);
		if (*ntype < 0) {
/* ADD CENTER LINE */
		    if (*size < (float)0.) {
			newpen_(&c__2);
		    }
		    plot_(&x1, &z1, &c__3);
		    plot_(&xold, &z1, &c__2);
		    if (*size < (float)0.) {
			newpen_(&c__1);
		    }
		}
	    }
	    if (ntp == 6) {
/* CONNECTED LINES */
		plot_(&x1, &y1, &ip);
		plot_(&x1, &z1, &c__2);
		if (*ntype < 0) {
/* ADD CENTER LINE */
		    if (*size < (float)0.) {
			newpen_(&c__2);
		    }
		    plot_(&x1, &z1, &c__3);
		    plot_(&xold, &z1, &c__2);
		    if (*size < (float)0.) {
			newpen_(&c__1);
		    }
		}
		plot_(&x1, &y1, &c__3);
	    }
	    if (ntp == 7) {
/* POSITIVE HALF CONNECTED LINES */
		plot_(&x1, &y1, &ip);
		if (y1 > z1) {
		    plot_(&x1, &z1, &c__2);
		    plot_(&x1, &y1, &c__2);
		}
		if (*ntype < 0) {
/* ADD CENTER LINE */
		    if (*size < (float)0.) {
			newpen_(&c__2);
		    }
		    plot_(&xold, &z1, &c__3);
		    plot_(&x1, &z1, &c__2);
		    if (*size < (float)0.) {
			newpen_(&c__1);
		    }
		    plot_(&x1, &y1, &c__3);
		}
	    }
	    if (ntp == 8) {
/* NEGATIVE HALF CONNECTED LINES */
		plot_(&x1, &y1, &ip);
		if (y1 < z1) {
		    plot_(&x1, &z1, &c__2);
		    plot_(&x1, &y1, &c__2);
		}
		if (*ntype < 0) {
/* ADD CENTER LINE */
		    if (*size < (float)0.) {
			newpen_(&c__2);
		    }
		    plot_(&xold, &z1, &c__3);
		    plot_(&x1, &z1, &c__2);
		    if (*size < (float)0.) {
			newpen_(&c__1);
		    }
		    plot_(&x1, &y1, &c__3);
		}
	    }
	    if (ntp == 9) {
/* FILLED AREA */
		plot_(&xold, &yold, &c__3);
		plot_(&x1, &y1, &c__2);
		ddx = x1 - xold;
		if (ddx != (float)0.) {
		    ixx = ddx / res;
		    ddy = (y1 - yold) / (x1 - xold) * res;
		    i__3 = ixx;
		    for (ix = 1; ix <= i__3; ++ix) {
			x2 = xold + ix * res;
			y2 = yold + ix * ddy;
			plot_(&x2, &z1, &c__3);
			plot_(&x2, &y2, &c__2);
/* L80: */
		    }
		}
	    }
	    if (ntp == 10) {
/* POSITIVE HALF FILLED AREA */
		plot_(&xold, &yold, &c__3);
		plot_(&x1, &y1, &c__2);
		ddx = x1 - xold;
		if (ddx != (float)0.) {
		    ixx = ddx / res;
		    ddy = (y1 - yold) / (x1 - xold) * res;
		    i__3 = ixx;
		    for (ix = 1; ix <= i__3; ++ix) {
			x2 = xold + ix * res;
			y2 = yold + ix * ddy;
			if (y2 > z1) {
			    plot_(&x2, &z1, &c__3);
			    plot_(&x2, &y2, &c__2);
			}
/* L82: */
		    }
		}
		if (*ntype < 0) {
		    if (*size < (float)0.) {
			newpen_(&c__2);
		    }
		    plot_(&xold, &z1, &c__3);
		    plot_(&x1, &z1, &c__2);
		    if (*size < (float)0.) {
			newpen_(&c__1);
		    }
		}
	    }
	    if (ntp == 11) {
/* POSITIVE HALF FILLED AREA */
		plot_(&xold, &yold, &c__3);
		plot_(&x1, &y1, &c__2);
		ddx = x1 - xold;
		if (ddx != (float)0.) {
		    ixx = ddx / res;
		    ddy = (y1 - yold) / (x1 - xold) * res;
		    i__3 = ixx;
		    for (ix = 1; ix <= i__3; ++ix) {
			x2 = xold + ix * res;
			y2 = yold + ix * ddy;
			if (y2 < z1) {
			    plot_(&x2, &z1, &c__3);
			    plot_(&x2, &y2, &c__2);
			}
/* L84: */
		    }
		}
		if (*ntype < 0) {
		    if (*size < (float)0.) {
			newpen_(&c__2);
		    }
		    plot_(&xold, &z1, &c__3);
		    plot_(&x1, &z1, &c__2);
		    if (*size < (float)0.) {
			newpen_(&c__1);
		    }
		}
	    }

	    xold = x1;
	    yold = y1;
	    ip = 2;
/* L79: */
	}
    }

/* 	PLOT TITLE */

    if (*nt < 0) {
	r__1 = (real) icol[6];
	plot_(&r__1, &c_b22, &c__0);
    }
/* PEN COLOR */
    if (*nt != 0 && jf != 0) {
/* TITLE */
	xp = (float)0.;
	yp = (float)0.;
	i__1 = abs(*nt);
	symbol_(&xp, &yp, &cs, title, &c_b22, &i__1, &c_n3);
/* TITLE LENGTH */
	xp = (r__1 = *xaxl / (float)2., dabs(r__1)) - xp / (float)2.;
	if (xp < (float)0.) {
	    xp = (float)0.;
	}
	r__1 = dabs(*yaxl) + (float).15;
	i__1 = abs(*nt);
	symbol_(&xp, &r__1, &cs, title, &c_b22, &i__1, &c_n1);
/* PLOT TITLE */
    }
    plot_(&c_b22, &c_b22, &c__3);

/* 	PLOT PACKAGE STUFF */

    if (*iflag > 0) {
	cterm_(&c__2);
/* ASK IF CLEAR SCREN */
	plotnd_();
/* CLOSE PLOT PACKAGE */
	repeat = FALSE_;
    }
    if (*iflag < 0) {
	repeat = TRUE_;
	cterm_(&c__1);
/* RETURN TO TEXT MODE */
    }
    return 0;
} /* seispl_ */

