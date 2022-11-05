
/* *** LAST REVISED ON  7-JAN-1994 12:37:18.85 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]PLOTSC.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    real xm, dx, ym, dy;
} cplotsc_;

#define cplotsc_1 cplotsc_

/* Table of constant values */

static real c_b2 = (float)1.2;
static real c_b4 = (float)1.;
static integer c_n1 = -1;
static integer c__1 = 1;
static real c_b12 = (float)0.;
static integer c__0 = 0;
static real c_b27 = (float)90.;
static integer c_n3 = -3;
static integer c__3 = 3;
static integer c__2 = 2;


/* Subroutine */ int plotsc_(x, y, np, iflag, xaxl, yaxl, xtitl, nxt, ytitl, 
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
    integer i__1;
    real r__1;

    /* Builtin functions */
    double r_nint(), r_sign();

    /* Local variables */
    static integer nadd;
    extern /* Subroutine */ int grid_(), line_(), axis_(), plot_();
    static integer i;
    extern /* Subroutine */ int scale_(), frame_(), cterm_();
    static integer ic[4], jf;
    static real cs;
    static integer pl, ix, iy;
    static real xl;
    static integer nx, ny;
    static real yl, xp, yp;
    extern /* Subroutine */ int newpen_(), plotnd_();
    static integer nd1, nd2;
    extern /* Subroutine */ int symbol_();
    static integer ilu;


/* 	CREATED BY D. LONG    OCT, 1983	AT JPL */
/* 	MODIFIED BY D. LONG   FEB, 1986 AT JPL + ADDED LINE TYPE */

/* 	ROUTINE TO PLOT A LINE OF DATA */

/* 	X	REAL X VALUE ARRAY */
/* 	Y	REAL Y DATA ARRAY */
/* 	NP	INT  # OF POINTS IN ARRAY */
/* 	IFLAG	INT */
/* 	 (MAG)	>10000 REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER */
/* 		< 0  REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT) */
/* 		= 0  CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT */
/* 		> 0  SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED) */
/* (ONE'S DIGIT) =0  DO NOT PLOT AXISES OR TITLE */
/* 		=1  PLOT BOX WITH AXIS TICK MARKS */
/* 		=2  PLOT A SOLID GRID */
/* 		=3  PLOT TICKED GRID W/O BOX */
/* 		=4  PLOT TICKED GRID WITH BOX */
/* 		=5  PLOT BOX WITH AXIS TICK MARKS AND TICKED GRID */
/* 		=6  PLOT WITH NO BOX OR GRID */
/* (TEN'S DIGIT) =0  ASK WHICH SCREEN DEVICE TO USE */
/* 		<>0 SCREEN DEVICE CODE */
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
/* 		< 0  USE PEN COLOR ARRAY (XMIN-YMAX ALSO ACCESSED) */
/* 			IF ABS(NT)/100 > 0 USE LINE TYPE */
/* 	XMIN	REAL  MINIMUM VALUE DISPLAYED ON X AXIS */
/* 	XMAX	REAL  MAXIMUM VALUE DISPLAYED ON X AXIS */
/* 	YMIN	REAL  MINIMUM VALUE OF Y ARRAY */
/* 	YMAX	REAL  MAXIMUM VALUE OF Y ARRAY */
/* 	ICOL	INT   PEN COLOR CONTROL ARRAY (ACCESSED ONLY IF NT < 0) */
/* 			ICOL(1) GRID COLOR */
/* 			ICOL(2) AXIS LINE COLOR */
/* 			ICOL(3) AXIS NUMBERS COLOR */
/* 			ICOL(4) AXIS LABEL COLOR */
/* 			ICOL(5) AXIS EXPONENT COLOR */
/* 			ICOL(6) PLOTTED LINE COLOR */
/* 			ICOL(7) TITLE COLOR (RETURN COLOR) */
/* 	ILINE	INT  LINE TYPE OF PLOTTED LINE */

    /* Parameter adjustments */
    --icol;
    --y;
    --x;

    /* Function Body */

    pl = 3;
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
	ilu = -(jf / 10);
	frame_(&pl, &ilu, &c_b2, &c_b2, &c_b4);
/* INTIALIZE PLOT PACKAGE */
    } else {
	cterm_(&c_n1);
/* 		CALL NEWPAGE			!NEW PAGE */
/* RESTORE PLOT MODE */
	jf %= 10;
    }
    jf %= 10;
    nx = (r__1 = r_nint(xaxl), dabs(r__1));
/* GRID SIZES */
    ny = (r__1 = r_nint(yaxl), dabs(r__1));
    r__1 = dabs(*xaxl);
    scale_(&x[1], &r__1, np, &c__1, &c__1, &cplotsc_1.xm, &cplotsc_1.dx);
/* SMOOTH SCALE FACTORS */
    if (*xaxl < (float)0.) {
/* INPUT SCALE FACTORS */
	cplotsc_1.xm = *xmin;
	cplotsc_1.dx = (*xmax - *xmin) / dabs(*xaxl);
    }
    r__1 = dabs(*yaxl);
    scale_(&y[1], &r__1, np, &c__1, &c__1, &cplotsc_1.ym, &cplotsc_1.dy);
/* SMOOTH SCALE FACTORS */
    if (*yaxl < (float)0.) {
/* INPUT SCALE FACTORS */
	cplotsc_1.ym = *ymin;
	cplotsc_1.dy = (*ymax - *ymin) / dabs(*yaxl);
    }
    if (jf == 0) {
	goto L77;
    }
    if (jf == 6) {
	goto L76;
    }
    if (jf > 1) {
/* GRID */
	if (jf >= 3) {
	    nx = -nx;
	}
/* TICKED GRID */
	if (jf > 4) {
	    ny = -ny;
	}
/* BOXED TICKED GRID */
	if (*nt < 0) {
	    r__1 = (real) icol[1];
	    plot_(&r__1, &c_b12, &c__0);
	}
/* PEN COLOR */
	grid_(&c_b12, &c_b12, &c_b4, &c_b4, &nx, &ny);
/* PLOT GRID */
	if (jf == 5) {
	    jf = 1;
	}
    }
L76:
    ix = abs(*nxt);
    r__1 = (real) (*nxt);
    xl = dabs(*xaxl) * r_sign(&c_b4, &r__1);
    nadd = 0;
    if (*nt < 0) {
	ic[0] = icol[2];
	ic[1] = icol[3];
	ic[2] = icol[4];
	ic[3] = icol[5];
	nadd = 100000;
/* PEN COLOR */
    }
    if (*nxt != 0) {
	i__1 = -ix - nadd;
	axis_(&c_b12, &c_b12, xtitl, &i__1, &xl, &c_b12, &cplotsc_1.xm, &
		cplotsc_1.dx, &nd1, &nd2, ic);
/* X-AXIS */
	if (jf == 1) {
	    r__1 = dabs(*yaxl);
	    i__1 = ix + 100 + nadd;
	    axis_(&c_b12, &r__1, xtitl, &i__1, &xl, &c_b12, &cplotsc_1.xm, &
		    cplotsc_1.dx, &nd1, &nd2, ic);
	}
/* X-AXIS */
    }
    iy = abs(*nyt) + 1000;
    r__1 = (real) (*nyt);
    yl = dabs(*yaxl) * r_sign(&c_b4, &r__1);
    if (*nyt != 0) {
	i__1 = iy + nadd;
	axis_(&c_b12, &c_b12, ytitl, &i__1, &yl, &c_b27, &cplotsc_1.ym, &
		cplotsc_1.dy, &nd1, &nd2, ic);
/* Y-AXIS */
	if (jf == 1) {
	    r__1 = dabs(*xaxl);
	    i__1 = -iy - 100 - nadd;
	    axis_(&r__1, &c_b12, ytitl, &i__1, &yl, &c_b27, &cplotsc_1.ym, &
		    cplotsc_1.dy, &nd1, &nd2, &i);
	}
/* Y-AXIS */
    }
L77:
    if (*nt < 0) {
	r__1 = (real) icol[6];
	plot_(&r__1, &c_b12, &c__0);
    }
/* PEN COLOR */
    if (abs(*nt) / 100 > 0) {
	newpen_(iline);
    }
/* LINE TYPE */
    line_(&x[1], &y[1], np, &c__1, &c__0, &c__0, &c__1, &c__1, &cplotsc_1.xm, 
	    &cplotsc_1.dx, &cplotsc_1.ym, &cplotsc_1.dy);
/* PLOT DATA */
    cs = (float).21;
/* TITLE CHARACTER SIZE */
    if (*nt < 0) {
	r__1 = (real) icol[7];
	plot_(&r__1, &c_b12, &c__0);
    }
/* PEN COLOR */
    if (abs(*nt) / 100 > 0) {
	newpen_(&c__1);
    }
/* LINE TYPE */
    if (*nt != 0 && jf != 0) {
/* PLOT TITLE */
	xp = (float)0.;
	yp = (float)0.;
	i__1 = abs(*nt) % 100;
	symbol_(&xp, &yp, &cs, title, &c_b12, &i__1, &c_n3);
/* TITLE LENGTH */
	xp = (r__1 = *xaxl / (float)2., dabs(r__1)) - xp / (float)2.;
	if (xp < (float)0.) {
	    xp = (float)0.;
	}
	r__1 = dabs(*yaxl) + (float).15;
	i__1 = abs(*nt) % 100;
	symbol_(&xp, &r__1, &cs, title, &c_b12, &i__1, &c_n1);
/* PLOT TITLE */
    }
    plot_(&c_b12, &c_b12, &c__3);		/* PEN UP */
    if (*iflag > 0) {
	cterm_(&c__2);			/* ASK IF CLEAR SCREEN */
	plotnd_();			/* CLOSE PLOTTER */
	repeat = FALSE_;
    }
    if (*iflag < 0) {
	repeat = TRUE_;
	cterm_(&c__1);			/* TERMINAL TO TEXT MODE */
    }
    return 0;
} /* plotsc_ */

