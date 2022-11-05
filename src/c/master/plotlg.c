
/* *** LAST REVISED ON  7-JAN-1994 12:05:09.61 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]PLOTLG.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    real xm, dx, ym, dy;
} cplotlg_;

#define cplotlg_1 cplotlg_

/* Table of constant values */

static real c_b2 = (float)1.2;
static real c_b4 = (float)1.;
static integer c_n1 = -1;
static integer c__1 = 1;
static real c_b16 = (float)0.;
static integer c__0 = 0;
static real c_b36 = (float)90.;
static integer c_n3 = -3;
static integer c__3 = 3;
static integer c__2 = 2;

/* Subroutine */ int plotlg_(x, y, np, iflag, xaxl, yaxl, xtitl, nxt, ytitl, 
	nyt, title, nt, xmin, xmax, ymin, ymax, icol, iline)
real *x, *y;
integer *np, *iflag;
real *xaxl, *yaxl;
char *xtitl;
integer *nxt;
char *ytitl;
integer *nyt;
char *title;
integer *nt;
real *xmin, *xmax, *ymin, *ymax;
integer *icol, *iline;
{
    /* Initialized data */

    static logical repeat = FALSE_;

    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;

    /* Builtin functions */
    double r_nint(), r_lg10(), r_int(), r_sign();

    /* Local variables */
    static integer nadd;
    extern /* Subroutine */ int grid_(), line_(), axis_(), plot_(), scale_(), 
	    frame_(), scalg_(), lgrid_(), lglin_(), cterm_(), lgaxs_();
    static integer n1, n2, ic[4], if_, jf, ii, ik;
    static real cs;
    static integer pl, ix, iy;
    static real xl;
    static integer nx, ny;
    static real yl, xp, yp;
    extern /* Subroutine */ int newpen_(), plotnd_(), symbol_();
    static real gdx, gdy;
    static integer ilu, inx, iny;


/* 	CREATED BY D. LONG    OCT, 1983	AT JPL */
/* 	MODIFIED BY D. LONG   FEB, 1986 AT JPL  + ADDED LINE TYPE */

/* 	MASTER ROUTINE TO PLOT A LINE OF DATA IN LOG/LINEAR COMBINATION */

/* 	X	REAL X VALUE ARRAY */
/* 	Y	REAL Y DATA ARRAY */
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
/* 	  (TEN'S DIGIT) = 0 NO GRID OR AXIS */
/* 	  (TEN'S DIGIT) = 1 PLOT BOX WITH AXIS TICKS */
/* 	  (TEN'S DIGIT) = 2 PLOT SOLID CARTESIAN GRID */
/* 	  (TEN'S DIGIT) = 3 PLOT TICKED CARTESIAN GRID W/O BOX */
/* 	  (TEN'S DIGIT) = 4 PLOT TICKED CARTESIAN GRID WITH BOX */
/* 	  (TEN'S DIGIT) = 5 PLOT BOX WITH AXIS TICKS AND TICKED CARTESIAN GRID
 */
/* 	  (TEN'S DIGIT) = 6 PLOT W/O BOX OR GRID BUT INCLUDE AXISES */
/* 	  (TEN'S DIGIT) = 7 PLOT SOLID LOGARITHMIC GRID */
/* 	  (TEN'S DIGIT) = 8 PLOT DOTTED LOGARITHMIC GRID */
/* 	  (TEN'S DIGIT) = 9 PLOT TICKED LOGARITHMIC GRID */
/*     (HUNDRED'S DIGIT) = 0 ASK WHICH SCREEN DEVICE TO USE */
/* 			<>0 SCREEN DEVICE CODE */
/* 	XAXL	REAL  X AXIS LENGTH IN INCHES */
/* 		< 0  USE INPUT VALUE SCALING--AXIS PLOTTED */
/* 		> 0  USE AUTO SCALING--AXIS PLOTTED */
/* 	YAXL	REAL  Y AXIS LENGTH IN INCHES */
/* 		< 0  USE INPUT VALUE SCALING--AXIS PLOTTED */
/* 		> 0  USE AUTO SCALING--AXIS PLOTTED */
/* NOTE: 	XMIN,XMAX,YMIN,YMAX ARE ONLY ACCESSED IF XAXL OR YAXL < 0 */

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
/* 	NT	INT   NUMBER OF CHARACTERS IN PLOT TITLE (<100) */
/* 		= 0  NO TITLE */
/* 		< 0  USE COLOR ARRAY (REQUIRES XMIN,XMAX,YMIN,YMAX TOO) */
/* 			IF ABS(NT)/100 > 0 USE LINE TYPE */
/* 	XMIN	REAL  MINIMUM VALUE DISPLAYED ON X AXIS */
/* 	XMAX	REAL  MAXIMUM VALUE DISPLAYED ON X AXIS */
/* 	YMIN	REAL  MINIMUM VALUE OF Y ARRAY */
/* 	YMAX	REAL  MAXIMUM VALUE OF Y ARRAY */
/* 	ICOL	INT   ARRAY OF PEN COLORS DIMENSIONED 4 */
/* 			ICOL(1) = GRID COLOR */
/* 			ICOL(2) = AXIS LINE COLOR */
/* 			ICOL(3) = AXIS NUMBERS COLOR */
/* 			ICOL(4) = AXIS TITLE COLOR */
/* 			ICOL(5) = AXIS EXPONENT COLOR */
/* 			ICOL(6) = LINE COLOR */
/* 			ICOL(7) = TITLE COLOR (COLOR UPON RETURN) */
/* 	ILINE	INT  LINE TYPE FOR PLOTTED LINE */

    /* Parameter adjustments */
    --icol;
    --y;
    --x;

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
    if (! repeat && jf < 10000) {
	ilu = -(jf / 100);
/* SCREEN DEVICE, CLEAR SCREEN */
	frame_(&pl, &ilu, &c_b2, &c_b2, &c_b4);
/* INTIALIZE PLOT PACKAGE */
    } else {
	cterm_(&c_n1);
/* 		CALL NEWPAGE			!NEW PAGE */
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
    if (if_ == 2 || if_ == 3) {
	r__1 = dabs(*xaxl);
	scalg_(&x[1], &r__1, np, &c__1, &c__1, &cplotlg_1.xm, &cplotlg_1.dx);
/* SMOOTH SCALE FACTORS */
	ik = -1;
	gdx = (float)1. / cplotlg_1.dx;
	nx = cplotlg_1.dx * dabs(*xaxl);
	inx = -1;
    } else {
	r__1 = dabs(*xaxl);
	scale_(&x[1], &r__1, np, &c__1, &c__1, &cplotlg_1.xm, &cplotlg_1.dx);
/* SMOOTH SCALE FACTORS */
	ik = 0;
	gdx = (float)1.;
	inx = 1;
    }
    if (*xaxl < (float)0.) {
/* INPUT SCALING */
	if (if_ == 2 || if_ == 3) {
	    r__1 = dabs(*xmin) + (float)1e-25;
	    cplotlg_1.xm = r_lg10(&r__1);
	    if (cplotlg_1.xm != r_int(&cplotlg_1.xm)) {
		cplotlg_1.xm = r_int(&cplotlg_1.xm) - (float)1.;
	    }
	    r__2 = dabs(*xmax) + (float)1e-25;
	    r__1 = r_lg10(&r__2);
	    cplotlg_1.dx = r_int(&r__1) + (float)1.;
	    cplotlg_1.dx = (cplotlg_1.dx - cplotlg_1.xm) / dabs(*xaxl);
	    gdx = (float)1. / cplotlg_1.dx;
	    nx = cplotlg_1.dx * dabs(*xaxl);
	} else {
	    cplotlg_1.xm = *xmin;
	    cplotlg_1.dx = (*xmax - *xmin) / dabs(*xaxl);
	    gdx = (float)1.;
	}
    }
    if (if_ == 1 || if_ == 3) {
	r__1 = dabs(*yaxl);
	scalg_(&y[1], &r__1, np, &c__1, &c__1, &cplotlg_1.ym, &cplotlg_1.dy);
/* SMOOTH SCALE FACTORS */
	--ik;
	gdy = (float)1. / cplotlg_1.dy;
	ny = cplotlg_1.dy * dabs(*yaxl);
	iny = -1;
    } else {
	r__1 = dabs(*yaxl);
	scale_(&y[1], &r__1, np, &c__1, &c__1, &cplotlg_1.ym, &cplotlg_1.dy);
/* SMOOTH SCALE FACTORS */
	++ik;
	gdy = (float)1.;
	iny = 1;
    }
    if (*yaxl < (float)0.) {
/* INPUT SCALING */
	if (if_ == 1 || if_ == 3) {
	    r__1 = dabs(*ymin) + (float)1e-25;
	    cplotlg_1.ym = r_lg10(&r__1);
	    if (cplotlg_1.ym != r_int(&cplotlg_1.ym)) {
		cplotlg_1.ym = r_int(&cplotlg_1.ym) - (float)1.;
	    }
	    r__2 = dabs(*ymax) + (float)1e-25;
	    r__1 = r_lg10(&r__2);
	    cplotlg_1.dy = r_int(&r__1) + (float)1.;
	    cplotlg_1.dy = (cplotlg_1.dy - cplotlg_1.ym) / dabs(*yaxl);
	    gdy = (float)1. / cplotlg_1.dy;
	    ny = cplotlg_1.dy * dabs(*yaxl);
	} else {
	    cplotlg_1.ym = *ymin;
	    cplotlg_1.dy = (*ymax - *ymin) / dabs(*yaxl);
	    gdy = (float)1.;
	}
    }
    if (jf == 0) {
	goto L77;
    }
/* NO AXIS */
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
	lgrid_(&c_b16, &c_b16, &gdx, &gdy, &i__1, &i__2, &ii);
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
	    plot_(&r__1, &c_b16, &c__0);
	}
/* PEN COLOR */
	grid_(&c_b16, &c_b16, &gdx, &gdy, &nx, &ny);
/* PRODUCE GRID */
	if (jf == 50) {
	    jf = 10;
	}
    }
L76:
    nadd = 0;
    if (*nt < 0) {
	nadd = 100000;
/* COLOR AXIS */
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
	    lgaxs_(&c_b16, &c_b16, xtitl, &i__1, &xl, &c_b16, &cplotlg_1.xm, &
		    cplotlg_1.dx, ic);
/* X-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*yaxl);
		i__1 = ix + 100 + nadd;
		lgaxs_(&c_b16, &r__1, xtitl, &i__1, &xl, &c_b16, &
			cplotlg_1.xm, &cplotlg_1.dx, ic);
	    }
/* X-AXIS */
	} else {
	    i__1 = -ix - nadd;
	    axis_(&c_b16, &c_b16, xtitl, &i__1, &xl, &c_b16, &cplotlg_1.xm, &
		    cplotlg_1.dx, &n1, &n2, ic);
/* X-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*yaxl);
		i__1 = ix + 100 + nadd;
		axis_(&c_b16, &r__1, xtitl, &i__1, &xl, &c_b16, &cplotlg_1.xm,
			 &cplotlg_1.dx, &n1, &n2, ic);
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
	    lgaxs_(&c_b16, &c_b16, ytitl, &i__1, &yl, &c_b36, &cplotlg_1.ym, &
		    cplotlg_1.dy, ic);
/* Y-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*xaxl);
		i__1 = -iy - 100 - nadd;
		lgaxs_(&r__1, &c_b16, ytitl, &i__1, &yl, &c_b36, &
			cplotlg_1.ym, &cplotlg_1.dy, ic);
	    }
/* Y-AXIS */
	} else {
	    i__1 = iy + nadd;
	    axis_(&c_b16, &c_b16, ytitl, &i__1, &yl, &c_b36, &cplotlg_1.ym, &
		    cplotlg_1.dy, &n1, &n2, ic);
/* Y-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*xaxl);
		i__1 = -iy - 100 - nadd;
		axis_(&r__1, &c_b16, ytitl, &i__1, &yl, &c_b36, &cplotlg_1.ym,
			 &cplotlg_1.dy, &n1, &n2, ic);
	    }
/* Y-AXIS */
	}
    }
L77:
    if (*nt < 0) {
	r__1 = (real) icol[6];
	plot_(&r__1, &c_b16, &c__0);
    }
/* PEN COLOR */
    if (abs(*nt) / 100 > 0) {
	newpen_(iline);
    }
/* LINE TYPE */
    if (ik == 1) {
	line_(&x[1], &y[1], np, &c__1, &c__0, &c__0, &c__1, &c__1, &
		cplotlg_1.xm, &cplotlg_1.dx, &cplotlg_1.ym, &cplotlg_1.dy);
/* PLOT DATA */
    } else {
	if (ik == -1) {
	    ik = 1;
	}
/* CORRECT FLAG */
	if (ik == 0) {
	    ik = -1;
	}
	lglin_(&x[1], &y[1], np, &c__1, &c__0, &c__0, &ik, &c__1, &c__1, &
		cplotlg_1.xm, &cplotlg_1.dx, &cplotlg_1.ym, &cplotlg_1.dy);
/* PLOT DATA */
    }
    if (abs(*nt) / 100 > 0) {
	newpen_(&c__1);
    }
/* RESTORE LINE TYPE */
    cs = (float).21;
/* TITLE CHARACTER SIZE */
    if (*nt < 0) {
	r__1 = (real) icol[7];
	plot_(&r__1, &c_b16, &c__0);
    }
/* PEN COLOR */
    if (*nt != 0 && jf != 0) {
/* PLOT TITLE */
	xp = (float)0.;
	yp = (float)0.;
	i__1 = abs(*nt) % 100;
	symbol_(&xp, &yp, &cs, title, &c_b16, &i__1, &c_n3);
/* TITLE LENGTH */
	xp = (r__1 = *xaxl / (float)2., dabs(r__1)) - xp / (float)2.;
	if (xp < (float)0.) {
	    xp = (float)0.;
	}
	r__1 = dabs(*yaxl) + (float).15;
	i__1 = abs(*nt) % 100;
	symbol_(&xp, &r__1, &cs, title, &c_b16, &i__1, &c_n1);
/* PLOT TITLE */
    }
    plot_(&c_b16, &c_b16, &c__3);
/* PEN UP */
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
} /* plotlg_ */

