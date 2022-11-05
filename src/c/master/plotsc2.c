
/* *** LAST REVISED ON  7-JAN-1994 12:45:18.32 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]PLOTSC2.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    real xm, dx, ym, dy;
} cplotsc2_;

#define cplotsc2_1 cplotsc2_

/* Table of constant values */

static real c_b2 = (float)1.2;
static real c_b4 = (float)1.;
static integer c_n1 = -1;
static integer c__1 = 1;
static integer c__2 = 2;
static real c_b14 = (float)0.;
static integer c__0 = 0;
static real c_b29 = (float)90.;
static integer c__4 = 4;
static integer c_n3 = -3;
static integer c__3 = 3;

/* Subroutine */ int plotsc2_(x, y, y2, np, iflag, xaxl, yaxl, xtitl, nxt, 
	ytitl, nyt, title, nt, xmin, xmax, ymin, ymax, icol)
real *x, *y, *y2;
integer *np, *iflag;
real *xaxl, *yaxl;
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
    integer i__1;
    real r__1, r__2;

    /* Builtin functions */
    double r_nint(), r_sign();

    /* Local variables */
    static integer nadd;
    extern /* Subroutine */ int grid_(), line_(), axis_(), plot_();
    static integer i;
    extern /* Subroutine */ int scale_(), frame_(), cterm_();
    static integer n1, n2, ic[4], jf;
    static real cs;
    static integer pl, ix, iy;
    static real xl;
    static integer nx, ny;
    static real py[2], yl, xp, yp, yx;
    extern /* Subroutine */ int newpen_(), plotnd_(), symbol_();
    static integer ilu;


/* 	CREATED BY D. LONG     OCT, 1983	AT JPL */
/* 	REVISED BY D. LONG     FEB, 1986 -- ADDED CHANGE OF LINE TYPE */
/* 					    FOR SECOND CURVE */

/* 	ROUTINE TO PLOT TWO LINES OF DATA */

/* 	X	REAL X VALUE ARRAY */
/* 	Y	REAL Y DATA ARRAY */
/* 	Y2	REAL Y DATA ARRAY */
/* 	NP	INT  # OF POINTS IN ARRAY */
/* 	IFLAG	INT */
/* 	 (MAG)	>10000 REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER */
/* 		< 0   REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT) */
/* 		= 0   CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT */
/* 		> 0   SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED) */
/* (ONE'S DIGIT) =0  DO NOT PLOT AXISES OR TITLE */
/* 		=1  PLOT A BOX WITH AXIS TICKS */
/* 		=2  PLOT A SOLID GRID */
/* 		=3  PLOT A TICKED GRID W/O BOX */
/* 		=4  PLOT A TICKED GRID WITH BOX */
/* 		=5  PLOT A BOX WITH AXIS TICKS AND TICKED GRID */
/* 		=6  PLOT W/O BOX OR GRID */
/* (TEN'S DIGIT) =0  ASK ABOUT SCREEN DEVICE */
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
/* 		< 0  USE PEN COLOR ARRAY */
/* 			IF ABS(NT)/100 > 0 USE LINE TYPE */
/* 	XMIN	REAL  MINIMUM VALUE DISPLAYED ON X AXIS */
/* 	XMAX	REAL  MAXIMUM VALUE DISPLAYED ON X AXIS */
/* 	YMIN	REAL  MINIMUM VALUE OF Y ARRAY */
/* 	YMAX	REAL  MAXIMUM VALUE OF Y ARRAY */
/* 	ICOL	INT   PEN COLOR CONTROL (ACCESSED ONLY IF NT < 0) */
/* 			ICOL(1) GRID COLOR */
/* 			ICOL(2) AXIS LINE COLOR */
/* 			ICOL(3) AXIS NUMBERS COLOR */
/* 			ICOL(4) AXIS TITLE COLOR */
/* 			ICOL(5) AXIS EXPONENT COLOR */
/* 			ICOL(6) LINE 1 COLOR */
/* 			ICOL(7) LINE 2 COLOR */
/* 			ICOL(8) TITLE COLOR (RETURN) */


    /* Parameter adjustments */
    --icol;
    --y2;
    --y;
    --x;

    /* Function Body */
    pl = 3;
/* PRINTER DATA FILE= FOR003.DAT */
    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();
	}
/* CLOSE PLOTTER */
	repeat = FALSE_;
	return 0;
    }
    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = -jf / 10;
	frame_(&pl, &ilu, &c_b2, &c_b2, &c_b4);
/* INTIALIZE PLOT PACKAGE */
    } else {
	cterm_(&c_n1);
/* 		CALL NEWPAGE			!NEW PAGE */
/* RESTORE PLOT MODE ON TERMINAL */
	jf %= 10;
    }
    jf %= 10;
    nx = (r__1 = r_nint(xaxl), dabs(r__1));
/* GRID SIZES */
    ny = (r__1 = r_nint(yaxl), dabs(r__1));
    r__1 = dabs(*xaxl);
    scale_(&x[1], &r__1, np, &c__1, &c__1, &cplotsc2_1.xm, &cplotsc2_1.dx);
/* SMOOTH SCALE FACTORS */
    if (*xaxl < (float)0.) {
/* INPUT SCALING */
	cplotsc2_1.xm = *xmin;
	cplotsc2_1.dx = (*xmax - *xmin) / dabs(*xaxl);
    }
    if (*yaxl < (float)0.) {
/* INPUT SCALING */
	cplotsc2_1.ym = *ymin;
	cplotsc2_1.dy = (*ymax - *ymin) / dabs(*yaxl);
    } else {
	cplotsc2_1.ym = y[1];
	yx = y2[1];
	i__1 = *np;
	for (i = 2; i <= i__1; ++i) {
/* Computing MIN */
	    r__1 = y[i], r__2 = y2[i], r__1 = min(r__1,r__2);
	    cplotsc2_1.ym = dmin(r__1,cplotsc2_1.ym);
/* Computing MAX */
	    r__1 = y[i], r__2 = y2[i], r__1 = max(r__1,r__2);
	    yx = dmax(r__1,yx);
/* L5: */
	}
	py[0] = cplotsc2_1.ym;
	py[1] = yx;
	r__1 = dabs(*yaxl);
	scale_(py, &r__1, &c__2, &c__1, &c__1, &cplotsc2_1.ym, &cplotsc2_1.dy)
		;
/* SMOOTH SCALE FACTORS */
    }
    if (jf == 0) {
	goto L77;
    }
    if (jf == 6) {
	goto L76;
    }
    if (jf > 1) {
	if (jf >= 3) {
	    nx = -nx;
	}
	if (jf >= 4) {
	    ny = -ny;
	}
	if (*nt < 0) {
	    r__1 = (real) icol[1];
	    plot_(&r__1, &c_b14, &c__0);
	}
/* PEN COLOR */
	grid_(&c_b14, &c_b14, &c_b4, &c_b4, &nx, &ny);
/* PRODUCE GRID */
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
	nadd = 100000;
/* PEN COLOR */
	ic[0] = icol[2];
	ic[1] = icol[3];
	ic[2] = icol[4];
	ic[3] = icol[5];
    }
    if (*nxt != 0) {
	i__1 = -ix - nadd;
	axis_(&c_b14, &c_b14, xtitl, &i__1, &xl, &c_b14, &cplotsc2_1.xm, &
		cplotsc2_1.dx, &n1, &n2, ic);
/* X-AXIS */
	if (jf == 1) {
	    r__1 = dabs(*yaxl);
	    i__1 = ix + 100 + nadd;
	    axis_(&c_b14, &r__1, xtitl, &i__1, &xl, &c_b14, &cplotsc2_1.xm, &
		    cplotsc2_1.dx, &n1, &n2, ic);
	}
/* X-AXIS */
    }
    iy = abs(*nyt) + 1000;
    r__1 = (real) (*nyt);
    yl = dabs(*yaxl) * r_sign(&c_b4, &r__1);
    if (*nyt != 0) {
	i__1 = iy + nadd;
	axis_(&c_b14, &c_b14, ytitl, &i__1, &yl, &c_b29, &cplotsc2_1.ym, &
		cplotsc2_1.dy, &n1, &n2, ic);
/* Y-AXIS */
	if (jf == 1) {
	    r__1 = dabs(*xaxl);
	    i__1 = -iy - 100 - nadd;
	    axis_(&r__1, &c_b14, ytitl, &i__1, &yl, &c_b29, &cplotsc2_1.ym, &
		    cplotsc2_1.dy, &n1, &n2, ic);
	}
/* Y-AXIS */
    }

L77:
    if (*nt < 0) {
	r__1 = (real) icol[6];
	plot_(&r__1, &c_b14, &c__0);
    }
/* PEN COLOR */
    newpen_(&c__1);
/* SET LINE TYPE */
    line_(&x[1], &y[1], np, &c__1, &c__0, &c__0, &c__1, &c__1, &cplotsc2_1.xm,
	     &cplotsc2_1.dx, &cplotsc2_1.ym, &cplotsc2_1.dy);
/* PLOT DATA */
    if (*nt < 0) {
	r__1 = (real) icol[7];
	plot_(&r__1, &c_b14, &c__0);
    }
/* PEN COLOR */
    newpen_(&c__4);
/* CHANGE LINE TYPE */
    line_(&x[1], &y2[1], np, &c__1, &c__0, &c__0, &c__1, &c__1, &
	    cplotsc2_1.xm, &cplotsc2_1.dx, &cplotsc2_1.ym, &cplotsc2_1.dy);
/* PLOT DATA */
    newpen_(&c__1);
/* RESTORE LINE TYPE */
    cs = (float).21;
/* TITLE CHARACTER SIZE */
    if (*nt < 0) {
	r__1 = (real) icol[8];
	plot_(&r__1, &c_b14, &c__0);
    }
/* PEN COLOR */
    if (*nt != 0 && jf != 0) {
	xp = (float)0.;
	yp = (float)0.;
	i__1 = abs(*nt);
	symbol_(&xp, &yp, &cs, title, &c_b14, &i__1, &c_n3);
/* TITLE LENGTH */
	xp = (r__1 = *xaxl / (float)2., dabs(r__1)) - xp / (float)2.;
	if (xp < (float)0.) {
	    xp = (float)0.;
	}
	r__1 = dabs(*yaxl) + (float).1;
	i__1 = abs(*nt);
	symbol_(&xp, &r__1, &cs, title, &c_b14, &i__1, &c_n1);
/* PLOT TITLE */
    }
    plot_(&c_b14, &c_b14, &c__3);

/* PEN UP */
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
/* PUT TERMINAL TEXT MODE */
    }
    return 0;
} /* plotsc2_ */

