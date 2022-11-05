
/* *** LAST REVISED ON  7-JAN-1994 12:46:26.67 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]SCATPL.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    real xm, dx, ym, dy;
} cscatpl_;

#define cscatpl_1 cscatpl_

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

/* Subroutine */ int scatpl_(x, y, nn, np, iflag, nsym, size, xaxl, yaxl, 
	xtitl, nxt, ytitl, nyt, title, nt, xmin, xmax, ymin, ymax, icol)
real *x, *y;
integer *nn, *np, *iflag, *nsym;
real *size, *xaxl, *yaxl;
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
    integer y_dim1, y_offset, x_dim1, x_offset, i__1, i__2;
    real r__1, r__2;
    char ch__1[1];

    /* Builtin functions */
    double r_nint(), r_int(), r_lg10(), r_sign();

    /* Local variables */
    static integer nadd;
    extern /* Subroutine */ int grid_(), axis_(), plot_();
    static integer isym, i, n;
    extern /* Subroutine */ int scale_(), frame_(), scalg_(), lgrid_(), 
	    cterm_(), lgaxs_();
    static integer n1, n2;
    static real x1, y1;
    static integer ic[4], if_, jf, ii, ik;
    static real cs;
    static integer in, pl, ix, iy;
    static real xl;
    static integer nx, ny;
    static real py[2], yl, xp, yp, sz;
    extern /* Subroutine */ int plotnd_(), symbol_();
    static real gdx, gdy;
    static integer ilu, inx, iny;


/* 	CREATED BY D. LONG       NOV, 1983	AT JPL */

/* 	ROUTINE TO PLOT A SCATTER PLOT WITH SEVERAL DIFFERENT PATTERNS */

/* 	X	REAL X DATA ARRAY DIMENSION X(NP,NN) */
/* 	Y	REAL Y DATA ARRAY DIMENSION Y(NP,NN) */
/* 	NN	INT  # NUMBER OF ARRAYS (IF NN=1 A 1D ARRAY MAY BE USED) */
/* 	NP	INT  # OF POINTS IN ARRAY */
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
/* 	NSYM	INT   SYMBOL ARRAY DIMENSIONED NSYM(NN) */
/* 		      NSYM(I) <  0  NO SYMBOLS, POINT ONLY */
/* 		      NSYM(I) >= 0  SYMBOL NUMBER */
/* 	SIZE    REAL  SIZE OF PLOTTED SYMBOL (IF ZERO 0.1 IS USED) */
/* 	XAXL	REAL  X AXIS LENGTH IN INCHES */
/* 		< 0  USE INPUT VALUE SCALING--AXIS PLOTTED */
/* 		> 0  USE AUTO SCALING--AXIS PLOTTED */
/* 	YAXL	REAL  Y AXIS LENGTH IN INCHES */
/* 		< 0  USE INPUT VALUE SCALING--AXIS PLOTTED */
/* 		> 0  USE AUTO SCALING--AXIS PLOTTED */

/* NOTE: 	XMIN,XMAX,YMIN,YMAX ARE ACCESSED ONLY IF XAXL OR YAXL < 0 */

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
    --nsym;
    y_dim1 = *np;
    y_offset = y_dim1 + 1;
    y -= y_offset;
    x_dim1 = *np;
    x_offset = x_dim1 + 1;
    x -= x_offset;

    /* Function Body */
    pl = 3;
/* PRINTER DATA FILE= FOR003.DAT */
    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();
	}
/* CLOSE PLOT PACKAGE */
	repeat = FALSE_;
	return 0;
    }
    jf = abs(*iflag);
    if (! repeat && jf < 1000) {
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
    if (*xaxl > (float)0.) {
/* INPUT SCALING */
	cscatpl_1.xm = x[x_dim1 + 1];
	cscatpl_1.dx = x[x_dim1 + 1];
	i__1 = *nn;
	for (n = 1; n <= i__1; ++n) {
	    i__2 = *np;
	    for (i = 2; i <= i__2; ++i) {
/* Computing MAX */
		r__1 = x[i + n * x_dim1];
		cscatpl_1.xm = dmax(r__1,cscatpl_1.xm);
/* Computing MIN */
		r__1 = x[i + n * x_dim1];
		cscatpl_1.dx = dmin(r__1,cscatpl_1.dx);
/* L4: */
	    }
	}
	py[0] = cscatpl_1.xm;
	py[1] = cscatpl_1.dx;
	if (if_ == 2 || if_ == 3) {
	    r__1 = dabs(*xaxl);
	    scalg_(py, &r__1, &c__2, &c__1, &c__1, &cscatpl_1.xm, &
		    cscatpl_1.dx);
/* SMOOTH SCALE FACTORS */
	    ik = -1;
	    gdx = (float)1. / cscatpl_1.dx;
	    nx = cscatpl_1.dx * dabs(*xaxl);
	    inx = -1;
	} else {
	    r__1 = dabs(*xaxl);
	    scale_(py, &r__1, &c__2, &c__1, &c__1, &cscatpl_1.xm, &
		    cscatpl_1.dx);
/* SMOOTH SCALE FACTORS */
	    ik = 0;
	    gdx = (float)1.;
	    inx = 1;
	}
    } else {
	if (if_ == 2 || if_ == 3) {
	    cscatpl_1.xm = dabs(*xmin) + (float)1e-25;
	    if (cscatpl_1.xm != r_int(&cscatpl_1.xm)) {
		cscatpl_1.xm = r_int(&cscatpl_1.xm) - (float)1.;
	    }
	    r__2 = dabs(*xmax) + (float)1e-25;
	    r__1 = r_lg10(&r__2);
	    cscatpl_1.dx = r_int(&r__1) + (float)1.;
	    cscatpl_1.dx = (cscatpl_1.dx - cscatpl_1.xm) / dabs(*xaxl);
	    gdx = (float)1. / cscatpl_1.dx;
	    ik = -1;
	    nx = cscatpl_1.dx * dabs(*xaxl);
	    inx = -1;
	} else {
	    cscatpl_1.xm = *xmin;
	    cscatpl_1.dx = (*xmax - *xmin) / dabs(*xaxl);
	    gdx = (float)1.;
	    ik = 0;
	    inx = 1;
	}
    }
    if (*yaxl > (float)0.) {
/* INPUT SCALING */
	cscatpl_1.ym = y[y_dim1 + 1];
	cscatpl_1.dy = y[y_dim1 + 1];
	i__2 = *nn;
	for (n = 1; n <= i__2; ++n) {
	    i__1 = *np;
	    for (i = 1; i <= i__1; ++i) {
/* Computing MAX */
		r__1 = y[i + n * y_dim1];
		cscatpl_1.ym = dmax(r__1,cscatpl_1.ym);
/* Computing MIN */
		r__1 = y[i + n * y_dim1];
		cscatpl_1.dy = dmin(r__1,cscatpl_1.dy);
/* L5: */
	    }
	}
	py[0] = cscatpl_1.ym;
	py[1] = cscatpl_1.dy;
	if (if_ == 1 || if_ == 3) {
	    r__1 = dabs(*yaxl);
	    scalg_(py, &r__1, &c__2, &c__1, &c__1, &cscatpl_1.ym, &
		    cscatpl_1.dy);
/* SMOOTH SCALE FACTORS */
	    --ik;
	    gdy = (float)1. / cscatpl_1.dy;
	    ny = cscatpl_1.dy * dabs(*yaxl);
	    iny = -1;
	} else {
	    r__1 = dabs(*yaxl);
	    scale_(py, &r__1, &c__2, &c__1, &c__1, &cscatpl_1.ym, &
		    cscatpl_1.dy);
/* SMOOTH SCALE FACTORS */
	    ++ik;
	    gdy = (float)1.;
	    iny = 1;
	}
    } else {
	if (if_ == 1 || if_ == 3) {
	    r__1 = dabs(*ymin) + (float)1e-25;
	    cscatpl_1.ym = r_lg10(&r__1);
	    if (cscatpl_1.ym != r_int(&cscatpl_1.ym)) {
		cscatpl_1.ym = r_int(&cscatpl_1.ym) - (float)1.;
	    }
	    r__2 = dabs(*ymax) + (float)1e-25;
	    r__1 = r_lg10(&r__2);
	    cscatpl_1.dy = r_int(&r__1) + (float)1.;
	    cscatpl_1.dy = (cscatpl_1.dy - cscatpl_1.ym) / dabs(*yaxl);
	    gdy = (float)1. / cscatpl_1.dy;
	    ny = cscatpl_1.dy * dabs(*yaxl);
	    --ik;
	    iny = -1;
	} else {
	    cscatpl_1.ym = *ymin;
	    cscatpl_1.dy = (*ymax - *ymin) / dabs(*yaxl);
	    ++ik;
	    gdy = (float)1.;
	    iny = 1;
	}
    }
    if (jf == 0) {
	goto L77;
    }
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
	i__1 = inx * nx;
	i__2 = iny * ny;
	lgrid_(&c_b22, &c_b22, &gdx, &gdy, &i__1, &i__2, &ii);
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
	    i__1 = -ix - nadd;
	    lgaxs_(&c_b22, &c_b22, xtitl, &i__1, &xl, &c_b22, &cscatpl_1.xm, &
		    cscatpl_1.dx, ic);
/* X-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*yaxl);
		i__1 = ix + 100 + nadd;
		lgaxs_(&c_b22, &r__1, xtitl, &i__1, &xl, &c_b22, &
			cscatpl_1.xm, &cscatpl_1.dx, ic);
	    }
/* X-AXIS */
	} else {
	    i__1 = -ix - nadd;
	    axis_(&c_b22, &c_b22, xtitl, &i__1, &xl, &c_b22, &cscatpl_1.xm, &
		    cscatpl_1.dx, &n1, &n2, ic);
/* X-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*yaxl);
		i__1 = ix + 100 + nadd;
		axis_(&c_b22, &r__1, xtitl, &i__1, &xl, &c_b22, &cscatpl_1.xm,
			 &cscatpl_1.dx, &n1, &n2, ic);
	    }
/* X-AXIS */
	}
    }
    iy = abs(*nyt) + 1000;
    r__1 = (real) (*nyt);
    yl = dabs(*yaxl) * r_sign(&c_b4, &r__1);
    if (*nyt != 0) {
	if (if_ == 1 || if_ == 3) {
	    i__1 = iy + nadd;
	    lgaxs_(&c_b22, &c_b22, ytitl, &i__1, &yl, &c_b42, &cscatpl_1.ym, &
		    cscatpl_1.dy, ic);
/* Y-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*xaxl);
		i__1 = -iy - 100 - nadd;
		lgaxs_(&r__1, &c_b22, ytitl, &i__1, &yl, &c_b42, &
			cscatpl_1.ym, &cscatpl_1.dy, ic);
	    }
/* Y-AXIS */
	} else {
	    i__1 = iy + nadd;
	    axis_(&c_b22, &c_b22, ytitl, &i__1, &yl, &c_b42, &cscatpl_1.ym, &
		    cscatpl_1.dy, &n1, &n2, ic);
/* Y-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*xaxl);
		i__1 = -iy - 100 - nadd;
		axis_(&r__1, &c_b22, ytitl, &i__1, &yl, &c_b42, &cscatpl_1.ym,
			 &cscatpl_1.dy, &n1, &n2, ic);
	    }
/* Y-AXIS */
	}
    }
L77:
    sz = *size;
    if (*size <= (float)0.) {
	sz = (float).1;
    }
/* DEFAULT SYMBOL SIZE */
    i__1 = *nn;
    for (in = 1; in <= i__1; ++in) {
	isym = nsym[in];
	if (*nt < 0) {
	    r__1 = (real) icol[in + 6];
	    plot_(&r__1, &c_b22, &c__0);
	}
/* PEN COLOR */
	i__2 = *np;
	for (i = 1; i <= i__2; ++i) {
	    x1 = x[i + in * x_dim1];
	    if (if_ == 2 || if_ == 3) {
		r__1 = dabs(x1) + (float)1e-25;
		x1 = r_lg10(&r__1);
	    }
	    y1 = y[i + in * y_dim1];
	    if (if_ == 1 || if_ == 3) {
		r__1 = dabs(y1) + (float)1e-25;
		y1 = r_lg10(&r__1);
	    }
	    x1 = (x1 - cscatpl_1.xm) / cscatpl_1.dx;
	    y1 = (y1 - cscatpl_1.ym) / cscatpl_1.dy;
	    if (isym < 0) {
/* DOTS ONLY */
		plot_(&x1, &y1, &c__3);
		plot_(&x1, &y1, &c__2);
	    } else {
/* SYMBOLS INSTEAD */
		ch__1[0] = isym;
		symbol_(&x1, &y1, &sz, ch__1, &c_b22, &c__1, &c_n1, 1L);
	    }
/* L79: */
	}
    }
    cs = (float).21;
/* TITLE CHARACTER SIZE */
    if (*nt < 0) {
	r__1 = (real) icol[6];
	plot_(&r__1, &c_b22, &c__0);
    }
/* PEN COLOR */
    if (*nt != 0 && jf != 0) {
/* PLOT TITLE */
	xp = (float)0.;
	yp = (float)0.;
	i__2 = abs(*nt);
	symbol_(&xp, &yp, &cs, title, &c_b22, &i__2, &c_n3);
/* TITLE LENGTH */
	xp = (r__1 = *xaxl / (float)2., dabs(r__1)) - xp / (float)2.;
	if (xp < (float)0.) {
	    xp = (float)0.;
	}
	r__1 = dabs(*yaxl) + (float).15;
	i__2 = abs(*nt);
	symbol_(&xp, &r__1, &cs, title, &c_b22, &i__2, &c_n1);
/* PLOT TITLE */
    }
    plot_(&c_b22, &c_b22, &c__3);
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
} /* scatpl_ */

