
/* *** LAST REVISED ON  7-JAN-1994 12:49:37.52 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]SPLOTS.C */

#include "my.h"

/* Common Block Declarations */

extern struct {
    real xm, dx, ym, dy;
} csplots_;

#define csplots_1 csplots_

union {
    struct {
	real xm1, dx1, ym1, dy1;
    } _1;
    struct {
	real xm, dx, ym, dy;
    } _2;
} csplotsx_;

#define csplotsx_1 (csplotsx_._1)
#define csplotsx_2 (csplotsx_._2)

/* Table of constant values */

static integer c__0 = 0;
static real c_b4 = (float).15;
static integer c__1 = 1;
static real c_b6 = (float).1;
static real c_b23 = (float)1.2;
static real c_b25 = (float)1.;
static integer c_n1 = -1;
static integer c__2 = 2;
static real c_b43 = (float)0.;
static real c_b63 = (float)90.;
static integer c__3 = 3;
static integer c_n3 = -3;


/* Subroutine */ int splots_(x, y, nnd, npd, nn, np, iflag, nopt, as, xaxl, 
	yaxl, xtitl, nxt, ytitl, nyt, title, nt, xmin, xmax, ymin, ymax, icol)
real *x, *y;
integer *nnd, *npd, *nn, *np, *iflag, *nopt;
real *as, *xaxl, *yaxl;
char *xtitl;
integer *nxt;
char *ytitl;
integer *nyt;
char *title;
integer *nt;
real *xmin, *xmax, *ymin, *ymax;
integer *icol;
{
    static integer icdum, nx, ny;
    static real xmn, ymn, xmx, ymx;
    extern /* Subroutine */ int splotsx_();


/* 	CREATED BY D. LONG       MAR, 1984	AT JPL */

/* 	ROUTINE TO PLOT SEVERAL LINES OF DATA IN LOG/LINEAR COMBINATION */
/* 	AXIS FLEXIBILITY IS PROVIDED -- SEE ROUTINE SPLOTSX FOR VARIABLE */
/* 	DESCRIPTION */

    /* Parameter adjustments */
    --icol;
    --y;
    --x;

    /* Function Body */
    if (*xaxl < (float)0. || *nt < 0) {
	xmn = *xmin;
	xmx = *xmax;
	if (*yaxl < (float)0. || *nt < 0) {
	    ymn = *ymin;
	    ymx = *ymax;
	}
    }
    nx = dabs(*xaxl) + (float).5;
    ny = dabs(*yaxl) + (float).5;
    if (*nt < 0) {
	splotsx_(&x[1], &y[1], nnd, npd, nn, np, iflag, nopt, as, xaxl, yaxl, 
		&c__0, &c__0, &nx, &c_b4, &c__1, &c_b6, &c__0, &c__0, &ny, &
		c_b4, &c__1, &c_b6, xtitl, nxt, ytitl, nyt, title, nt, &xmn, &
		xmx, &ymn, &ymx, &icol[1]);
    } else {
	splotsx_(&x[1], &y[1], nnd, npd, nn, np, iflag, nopt, as, xaxl, yaxl, 
		&c__0, &c__0, &nx, &c_b4, &c__1, &c_b6, &c__0, &c__0, &ny, &
		c_b4, &c__1, &c_b6, xtitl, nxt, ytitl, nyt, title, nt, &xmn, &
		xmx, &ymn, &ymx, &icdum);
    }
    csplots_1.xm = csplotsx_1.xm1;
    csplots_1.dx = csplotsx_1.dx1;
    csplots_1.ym = csplotsx_1.ym1;
    csplots_1.dy = csplotsx_1.dy1;
    return 0;
} /* splots_ */


/* Subroutine */ int splotsx_(x, y, nnd, npd, nn, np, iflag, nopt, as, xaxl, 
	yaxl, nmx, nnx, mlx, tsx, ndx, smx, nmy, nny, mly, tsy, ndy, smy, 
	xtitl, nxt, ytitl, nyt, title, nt, xmin, xmax, ymin, ymax, icol)
real *x, *y;
integer *nnd, *npd, *nn, *np, *iflag, *nopt;
real *as, *xaxl, *yaxl;
integer *nmx, *nnx, *mlx;
real *tsx;
integer *ndx;
real *smx;
integer *nmy, *nny, *mly;
real *tsy;
integer *ndy;
real *smy;
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
    extern /* Subroutine */ int grid_();
    static integer norg;
    extern /* Subroutine */ int plot_();
    static integer nsym;
    extern /* Subroutine */ int axis2_();
    static integer nopt1, nopt2, i;
    extern /* Subroutine */ int scale_(), frame_(), scalg_(), lgrid_(), 
	    cterm_(), lgaxs_();
    static integer npcnt;
    static real x1, y1, y2, y3;
    static integer ic[4], if_, jf, ii;
    static real cs;
    static integer in, pl, ix, iy;
    static real xl;
    static integer nx, ny;
    static real py[2], yl, xp, yp;
    extern /* Subroutine */ int plotnd_(), symbol_();
    static real gdx, gdy;
    static integer ilu, ikx, iky, inx, iny, nls, nnn;


/* 	CREATED BY D. LONG       MAR, 1984	AT JPL */

/* 	ROUTINE TO PLOT SEVERAL LINES OF DATA IN LOG/LINEAR COMBINATION */
/* 	AXIS FLEXIBILITY IS PROVIDED */

/* 	X	REAL X VALUE ARRAY */
/* 	Y	REAL Y DATA ARRAY DIMENSION Y(NPD,NND) */
/* 	NND	INT  DIMENSION OF Y */
/* 	NPD	INT  DIMENSION OF Y */
/* 	NN	INT  # NUMBER OF LINES TO PLOT */
/* 	NP	INT  # OF POINTS IN IN LINE */
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
/* 			<>0 SCREEN DEVICE NUMBER CODE */
/* 	NOPT	INT  OPTION FOR POINT DISPLAY */
/* 	  (ONE'S DIGIT) = 0 POINTS WITH NO CONNECTION */
/* 	  (ONE'S DIGIT) = 1 LINE ONLY */
/* 	  (ONE'S DIGIT) = 2 SYMBOLS WITH NO CONNECTION */
/* 	  (ONE'S DIGIT) = 3 LINE CONNECTED SYMBOLS */
/* 	  (ONE'S DIGIT) = 4 LINE FROM POINT TO X AXIS PLOTTED WITH NO SYMBOLS 
*/
/* 	  (ONE'S DIGIT) = 5 LINE FROM POINT TO X AXIS AND INTERPOLATED LINE */

/* 	  (ONE'S DIGIT) = 6 LINE FROM POINT TO X AXIS PLOTTED WITH SYMBOLS */
/* 	  (TEN'S DIGIT) = 0 NORMAL */
/* 	  (TEN'S DIGIT) = 1 PLOT ERROR BARS USING NEXT TWO LINES AS BAR WITHS 
*/
/* 	  (TEN'S DIGIT) = 2 PLOT ERROR BARS WITHOUT ENDS */
/*     	  (HUNDRED'S) NUMBER OF POINTS BETWEEN SYMBOLS AND BARS (0=1) */
/* 	AS	REAL  PLOT SYMBOL SIZE */
/* 	XAXL	REAL  X AXIS LENGTH IN INCHES */
/* 		< 0  USE INPUT VALUE SCALING--AXIS PLOTTED */
/* 		> 0  USE AUTO SCALING--AXIS PLOTTED */
/* 	YAXL	REAL  Y AXIS LENGTH IN INCHES */
/* 		< 0  USE INPUT VALUE SCALING--AXIS PLOTTED */
/* 		> 0  USE AUTO SCALING--AXIS PLOTTED */

/* NOTE: 	XMIN,XMAX,YMIN,YMAX ARE ACCESSED ONLY IF XAXL OR YAXL < 0 */

/* 	NMX...SMY    PARAMETERS FOR PLOT AXISES (SEE ROUTINE AXIS2) */
/* 			ALL PARAMETERS MUST BE PRESENT AND WILL BE USED */
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
/* 	ICOL	INT   ARRAY OF PEN COLORS DIMENSIONED ICOL(6+NN) */
/* 			ICOL(1) = GRID COLOR */
/* 			ICOL(2) = AXIS LINE COLOR */
/* 			ICOL(3) = AXIS NUMBERS COLOR */
/* 			ICOL(4) = AXIS TITLE COLOR */
/* 			ICOL(5) = AXIS EXPONENT COLOR */
/* 			ICOL(6) = TITLE COLOR (COLOR UPON RETURN) */
/* 			ICOL(7) = LINE COLOR 1 */
/* 			ICOL(8) = LINE COLOR 2 */
/* 			   .	     .	     3 */

    /* Parameter adjustments */
    --icol;
    y_dim1 = *npd;
    y_offset = y_dim1 + 1;
    y -= y_offset;
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
	ilu = -(jf / 100);
/* SCREEN DEVICE, CLEAR SCREEN */
	frame_(&pl, &ilu, &c_b23, &c_b23, &c_b25);
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
    nsym = abs(*nopt) / 100;
    nopt1 = abs(*nopt) % 10;
    nopt2 = (abs(*nopt) % 100 - nopt1) / 10;
    if (nsym == 0) {
	nsym = 1;
    }
    nx = (r__1 = r_nint(xaxl), dabs(r__1));
/* GRID SIZES */
    ny = (r__1 = r_nint(yaxl), dabs(r__1));
    if (*xaxl > (float)0.) {
/* INPUT SCALING */
	csplotsx_2.xm = x[1];
	csplotsx_2.dx = x[1];
	i__1 = *np;
	for (i = 2; i <= i__1; ++i) {
/* Computing MAX */
	    r__1 = x[i];
	    csplotsx_2.xm = dmax(r__1,csplotsx_2.xm);
/* Computing MIN */
	    r__1 = x[i];
	    csplotsx_2.dx = dmin(r__1,csplotsx_2.dx);
/* L5: */
	}
	py[0] = csplotsx_2.xm;
	py[1] = csplotsx_2.dx;
	if (if_ == 2 || if_ == 3) {
	    r__1 = dabs(*xaxl);
	    scalg_(py, &r__1, &c__2, &c__1, &c__1, &csplotsx_2.xm, &
		    csplotsx_2.dx);
/* SMOOTH SCALE FACTORS */
	    ikx = -1;
	    gdx = (float)1. / csplotsx_2.dx;
	    nx = csplotsx_2.dx * dabs(*xaxl);
	    inx = -1;
	} else {
	    r__1 = dabs(*xaxl);
	    scale_(py, &r__1, &c__2, &c__1, &c__1, &csplotsx_2.xm, &
		    csplotsx_2.dx);
/* SMOOTH SCALE FACTORS */
	    ikx = 1;
	    gdx = (float)1.;
	    inx = 1;
	}
    } else {
	if (if_ == 2 || if_ == 3) {
	    csplotsx_2.xm = dabs(*xmin) + (float)1e-25;
	    if (csplotsx_2.xm != r_int(&csplotsx_2.xm)) {
		csplotsx_2.xm = r_int(&csplotsx_2.xm) - (float)1.;
	    }
	    r__2 = dabs(*xmax) + (float)1e-25;
	    r__1 = r_lg10(&r__2);
	    csplotsx_2.dx = r_int(&r__1) + (float)1.;
	    csplotsx_2.dx = (csplotsx_2.dx - csplotsx_2.xm) / dabs(*xaxl);
	    gdx = (float)1. / csplotsx_2.dx;
	    ikx = -1;
	    nx = csplotsx_2.dx * dabs(*xaxl);
	    inx = -1;
	} else {
	    csplotsx_2.xm = *xmin;
	    csplotsx_2.dx = (*xmax - *xmin) / dabs(*xaxl);
	    gdx = (float)1.;
	    ikx = 1;
	    inx = 1;
	}
    }
    if (*yaxl > (float)0.) {
/* INPUT SCALING */
	csplotsx_2.ym = y[y_dim1 + 1];
	csplotsx_2.dy = y[y_dim1 + 1];
	i__1 = *nn;
	for (in = 1; in <= i__1; ++in) {
	    i__2 = *np;
	    for (i = 1; i <= i__2; ++i) {
/* Computing MAX */
		r__1 = y[i + in * y_dim1];
		csplotsx_2.ym = dmax(r__1,csplotsx_2.ym);
/* Computing MIN */
		r__1 = y[i + in * y_dim1];
		csplotsx_2.dy = dmin(r__1,csplotsx_2.dy);
/* L6: */
	    }
	}
	py[0] = csplotsx_2.ym;
	py[1] = csplotsx_2.dy;
	if (if_ == 1 || if_ == 3) {
	    r__1 = dabs(*yaxl);
	    scalg_(py, &r__1, &c__2, &c__1, &c__1, &csplotsx_2.ym, &
		    csplotsx_2.dy);
/* SMOOTH SCALE FACTORS */
	    iky = -1;
	    gdy = (float)1. / csplotsx_2.dy;
	    ny = csplotsx_2.dy * dabs(*yaxl);
	    iny = -1;
	} else {
	    r__1 = dabs(*yaxl);
	    scale_(py, &r__1, &c__2, &c__1, &c__1, &csplotsx_2.ym, &
		    csplotsx_2.dy);
/* SMOOTH SCALE FACTORS */
	    iky = 1;
	    gdy = (float)1.;
	    iny = 1;
	}
    } else {
	if (if_ == 1 || if_ == 3) {
	    r__1 = dabs(*ymin) + (float)1e-25;
	    csplotsx_2.ym = r_lg10(&r__1);
	    if (csplotsx_2.ym != r_int(&csplotsx_2.ym)) {
		csplotsx_2.ym = r_int(&csplotsx_2.ym) - (float)1.;
	    }
	    r__2 = dabs(*ymax) + (float)1e-25;
	    r__1 = r_lg10(&r__2);
	    csplotsx_2.dy = r_int(&r__1) + (float)1.;
	    csplotsx_2.dy = (csplotsx_2.dy - csplotsx_2.ym) / dabs(*yaxl);
	    gdy = (float)1. / csplotsx_2.dy;
	    ny = csplotsx_2.dy * dabs(*yaxl);
	    iky = -1;
	    iny = -1;
	} else {
	    csplotsx_2.ym = *ymin;
	    csplotsx_2.dy = (*ymax - *ymin) / dabs(*yaxl);
	    iky = 1;
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
	i__2 = inx * nx;
	i__1 = iny * ny;
	lgrid_(&c_b43, &c_b43, &gdx, &gdy, &i__2, &i__1, &ii);
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
	    plot_(&r__1, &c_b43, &c__0);
	}
/* PEN COLOR */
	grid_(&c_b43, &c_b43, &gdx, &gdy, &nx, &ny);
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
    xl = dabs(*xaxl) * r_sign(&c_b25, &r__1);
/* AXIS LENGTH WITH TICK INFOR */
    if (*nxt != 0) {
	if (if_ == 2 || if_ == 3) {
	    i__2 = -ix - nadd;
	    lgaxs_(&c_b43, &c_b43, xtitl, &i__2, &xl, &c_b43, &csplotsx_2.xm, 
		    &csplotsx_2.dx, ic);
/* X-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*yaxl);
		i__2 = ix + 100 + nadd;
		lgaxs_(&c_b43, &r__1, xtitl, &i__2, &xl, &c_b43, &
			csplotsx_2.xm, &csplotsx_2.dx, ic);
	    }
/* X-AXIS */
	} else {
	    i__2 = -ix - nadd - 10000;
	    i__1 = -abs(*mlx);
	    axis2_(&c_b43, &c_b43, xtitl, &i__2, &xl, &c_b43, &csplotsx_2.xm, 
		    &csplotsx_2.dx, nmx, nnx, &i__1, tsx, ndx, smx, ic);
/* X-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*yaxl);
		i__2 = ix + nadd + 10100;
		i__1 = -abs(*mlx);
		axis2_(&c_b43, &r__1, xtitl, &i__2, &xl, &c_b43, &
			csplotsx_2.xm, &csplotsx_2.dx, nmx, nnx, &i__1, tsx, 
			ndx, smx, ic);
	    }
/* X-AXIS */
	}
    }
    iy = abs(*nyt) + 1000;
    r__1 = (real) (*nyt);
    yl = dabs(*yaxl) * r_sign(&c_b25, &r__1);
    if (*nyt != 0) {
	if (if_ == 1 || if_ == 3) {
	    i__2 = iy + nadd;
	    lgaxs_(&c_b43, &c_b43, ytitl, &i__2, &yl, &c_b63, &csplotsx_2.ym, 
		    &csplotsx_2.dy, ic);
/* Y-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*xaxl);
		i__2 = -iy - 100 - nadd;
		lgaxs_(&r__1, &c_b43, ytitl, &i__2, &yl, &c_b63, &
			csplotsx_2.ym, &csplotsx_2.dy, ic);
	    }
/* Y-AXIS */
	} else {
	    i__2 = iy + nadd + 10000;
	    i__1 = -abs(*mly);
	    axis2_(&c_b43, &c_b43, ytitl, &i__2, &yl, &c_b63, &csplotsx_2.ym, 
		    &csplotsx_2.dy, nmy, nny, &i__1, tsy, ndy, smy, ic);
/* Y-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*xaxl);
		i__2 = -iy - nadd - 10100;
		i__1 = -abs(*mly);
		axis2_(&r__1, &c_b43, ytitl, &i__2, &yl, &c_b63, &
			csplotsx_2.ym, &csplotsx_2.dy, nmy, nny, &i__1, tsy, 
			ndy, smy, ic);
	    }
/* Y-AXIS */
	}
    }
L77:
    nls = 1;
    nnn = *nn;
    if (nopt2 > 0) {
	nls = 3;
	nnn = *nn * nls;
    }
    i__2 = nnn;
    i__1 = nls;
    for (in = 1; i__1 < 0 ? in >= i__2 : in <= i__2; in += i__1) {
/* FOR EACH LINE */
	if (*nt < 0) {
	    r__1 = (real) icol[(in << 1) + 5];
	    plot_(&r__1, &c_b43, &c__0);
	}
/* PEN COLOR */
	npcnt = 1;
	norg = 3;
	i__3 = *np;
	for (ii = 1; ii <= i__3; ++ii) {
/* FOR EACH POINT */
	    x1 = (x[ii] - csplotsx_2.xm) / csplotsx_2.dx;
	    if (ikx < 0) {
		r__1 = dabs(x1) + (float)1e-25;
		x1 = r_lg10(&r__1);
	    }
/* LOG X */
	    y1 = (y[ii + in * y_dim1] - csplotsx_2.ym) / csplotsx_2.dy;
	    if (iky < 0) {
		r__1 = dabs(y1) + (float)1e-25;
		y1 = r_lg10(&r__1);
	    }
/* LOG Y */
	    plot_(&x1, &y1, &norg);
	    if (nopt1 == 0) {
		plot_(&x1, &y1, &c__2);
	    }
/* POINT ONLY */
	    if (nopt1 % 2 == 1) {
		norg = 2;
	    }
/* FOR LINE */
	    if (nopt1 > 3) {
		plot_(&x1, &c_b43, &c__2);
	    }
/* FOR VERTICAL LINE TO X AXIS */
	    ++npcnt;
	    if (npcnt > nsym) {
		npcnt = 1;
		if (nopt1 == 2 || nopt1 == 3 || nopt1 == 6) {
		    if ((real) (*nt) < (float)0.) {
			r__1 = (real) icol[(in << 1) + 6];
			plot_(&r__1, &c_b43, &c__0);
		    }
/* PEN COLOR */
		    ch__1[0] = in;
		    symbol_(&x1, &y1, as, ch__1, &c_b43, &c__1, &c_n1, 1L);
		}
		if (nopt2 > 0) {
		    if ((real) (*nt) < (float)0.) {
			r__1 = (real) icol[(in << 1) + 6];
			plot_(&r__1, &c_b43, &c__0);
		    }
/* PEN COLOR */
		    y2 = (y[ii + (in + 1) * y_dim1] - csplotsx_2.ym) / 
			    csplotsx_2.dy;
		    if (iky < 0) {
			r__1 = dabs(y2) + (float)1e-25;
			y2 = r_lg10(&r__1);
		    }
		    y3 = (y[ii + (in + 2) * y_dim1] - csplotsx_2.ym) / 
			    csplotsx_2.dy;
		    if (iky < 0) {
			r__1 = dabs(y3) + (float)1e-25;
			y3 = r_lg10(&r__1);
		    }
		    if (nopt2 == 1) {
			r__1 = x1 - *as / (float)2.;
			plot_(&r__1, &y2, &c__3);
			r__1 = x1 + *as / (float)2.;
			plot_(&r__1, &y2, &c__2);
		    }
		    plot_(&x1, &y2, &c__3);
		    plot_(&x1, &y3, &c__2);
		    if (nopt2 == 1) {
			r__1 = x1 - *as / (float)2.;
			plot_(&r__1, &y3, &c__3);
			r__1 = x1 + *as / (float)2.;
			plot_(&r__1, &y3, &c__2);
		    }
		}
	    }
	    if (*nt < 0) {
		r__1 = (real) icol[(in << 1) + 5];
		plot_(&r__1, &c_b43, &c__0);
	    }
/* PEN COLOR */
	    plot_(&x1, &y1, &c__3);
/* L78: */
	}
    }
    cs = (float).21;
/* TITLE CHARACTER SIZE */
    if (*nt < 0) {
	r__1 = (real) icol[6];
	plot_(&r__1, &c_b43, &c__0);
    }
/* PEN COLOR */
    if (*nt != 0 && jf != 0) {
/* TITLE */
	xp = (float)0.;
	yp = (float)0.;
	i__3 = abs(*nt);
	symbol_(&xp, &yp, &cs, title, &c_b43, &i__3, &c_n3);
/* TITLE LENGTH */
	xp = (r__1 = *xaxl / (float)2., dabs(r__1)) - xp / (float)2.;
	if (xp < (float)0.) {
	    xp = (float)0.;
	}
	r__1 = dabs(*yaxl) + (float).15;
	i__3 = abs(*nt);
	symbol_(&xp, &r__1, &cs, title, &c_b43, &i__3, &c_n1);
/* PLOT TITLE */
    }
    plot_(&c_b43, &c_b43, &c__3);
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
} /* splotsx_ */

