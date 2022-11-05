
/* *** LAST REVISED ON 23-DEC-1993 06:23:17.98 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]GLPLOT.C */

#include "my.h"

/* Common Block Declarations */

struct {
    real xm, dx, ym, dy;
} cglplot_;

#define cglplot_1 cglplot_

/* Table of constant values */

static real c_b2 = (float)1.5;
static real c_b4 = (float)1.;
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c__1 = 1;
static real c_b22 = (float)0.;
static integer c__0 = 0;
static real c_b42 = (float)90.;
static integer c_n3 = -3;
static integer c__3 = 3;

/* Subroutine */ int glplot_(x, y, nnd, npd, nn, np, iflag, nsym, xaxl, yaxl, 
	xt, xc, xf, xtitl, nxt, yt, yc, yf, ytitl, nyt, title, nt, xmin, xmax,
	 ymin, ymax, icol, iline)
real *x, *y;
integer *nnd, *npd, *nn, *np, *iflag, *nsym;
real *xaxl, *yaxl, *xt, *xc, *xf;
char *xtitl;
integer *nxt;
real *yt, *yc, *yf;
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
    integer y_dim1, y_offset, i__1, i__2;
    real r__1, r__2, r__3;

    /* Builtin functions */
    double r_nint(), r_int(), r_lg10();
    integer i_sign();

    /* Local variables */
    static integer nadd;
    extern /* Subroutine */ int grid_(), line_(), plot_(), axis3_();
    static integer i;
    extern /* Subroutine */ int scale_(), frame_(), scalg_(), lgrid_(), 
	    lglin_(), cterm_(), lgaxs_();
    static integer ic[4], if_, jf, ii, ik;
    static real cs;
    static integer in, pl, nx, ny;
    static real py[2];
    static integer ix;
    static real xl;
    static integer iy;
    static real yl, xp, yp;
    extern /* Subroutine */ int newpen_(), plotnd_(), symbol_();
    static real gdx, gdy;
    static integer ilu, inx, iny;


/* 	CREATED BY D. LONG       FEB, 1984	AT JPL */

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
/* 	NSYM	INT   NUMBER OF POINTS BETWEEN SYMBOLS */
/* 		      < 0  SYMBOLS ONLY, NO LINE */
/* 		      = 0  NO SYMBOLS, LINE ONLY */
/* 		      > 0 NUMBER OF POINTS BETWEEN SYMBOLS */
/* 	XAXL	REAL  X AXIS LENGTH IN INCHES */
/* 		< 0  USE INPUT VALUE SCALING--AXIS PLOTTED */
/* 		> 0  USE AUTO SCALING--AXIS PLOTTED */
/* 	YAXL	REAL  Y AXIS LENGTH IN INCHES */
/* 		< 0  USE INPUT VALUE SCALING--AXIS PLOTTED */
/* 		> 0  USE AUTO SCALING--AXIS PLOTTED */

/* NOTE: 	XMIN,XMAX,YMIN,YMAX ARE ACCESSED ONLY IF XAXL OR YAXL < 0 */

/* 	XT,XC,XF	PARAMETERS FOR X AXIS (SEE AXIS3) */
/* 	YT,YC,YF	PARAMETERS FOR Y AXIS (SEE AXIS3) */
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
/* 		< 0  USE COLOR ARRAY */
/* 			(REQUIRES XMIN,XMAX,YMIN,YMAX BE PRESENT) */
/* 			IF IABS(NT)/100)>1 USE LINE TYPE ARRAY */
/* 	XMIN	REAL  MINIMUM VALUE DISPLAYED ON X AXIS */
/* 	XMAX	REAL  MAXIMUM VALUE DISPLAYED ON X AXIS */
/* 	YMIN	REAL  MINIMUM VALUE OF Y ARRAY */
/* 	YMAX	REAL  MAXIMUM VALUE OF Y ARRAY */
/* 	ICOL	INT   ARRAY OF PEN COLORS PEN DIMENSIONED ICOL(5+NN) */
/* 			ICOL(1) = GRID COLOR */
/* 			ICOL(2) = AXIS LINE COLOR */
/* 			ICOL(3) = AXIS NUMBERS COLOR */
/* 			ICOL(4) = AXIS TITLE COLOR */
/* 			ICOL(5) = AXIS EXPONENT COLOR */
/* 			ICOL(6) = TITLE COLOR (COLOR UPON RETURN) */
/* 			ICOL(7) = LINE COLOR 1 */
/* 			ICOL(8) = LINE COLOR 2 */
/* 			   .	     .	     3 */
/* 	ILINE	INT  LINE TYPE ARRAY DIMENSIONED ILINE(NN) */

    /* Parameter adjustments */
    --iline;
    --icol;
    y_dim1 = *npd;
    y_offset = y_dim1 + 1;
    y -= y_offset;
    --x;

    /* Function Body */

    pl = 3;
    if (*iflag == 0) {
	if (repeat) {			/* CLOSE PLOT PACKAGE */
	    plotnd_();
	}
	repeat = FALSE_;
	return 0;
    }
    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = -(jf / 100);	/* SCREEN DEVICE, CLEAR SCREEN */
	frame_(&pl, &ilu, &c_b2, &c_b2, &c_b4);	/* INTIALIZE PLOT PACKAGE */
    } else {
	cterm_(&c_n1);
/* 		CALL NEWPAGE			! NEW PAGE */
/* RESTORE PLOT MODE */
	jf %= 100;
    }
    jf %= 100;
    if_ = jf;
    if (if_ > 10) {
	if_ %= 10;
    }
    jf -= if_;
    nx = (r__1 = r_nint(xaxl), dabs(r__1));	/* GRID SIZES */
    ny = (r__1 = r_nint(yaxl), dabs(r__1));
    if (*xaxl > (float)0.) {			/* INPUT SCALING */
	cglplot_1.xm = x[1];
	cglplot_1.dx = x[1];
	i__1 = *np;
	for (i = 2; i <= i__1; ++i) {	/* Computing MAX and MIN */
	    r__1 = x[i];
	    cglplot_1.dx = dmax(r__1,cglplot_1.dx);
	    r__1 = x[i];
	    cglplot_1.xm = dmin(r__1,cglplot_1.xm);
/* L5: */
	}
	py[0] = cglplot_1.xm;
	py[1] = cglplot_1.dx;
	if (if_ == 2 || if_ == 3) {
	    r__1 = dabs(*xaxl);
	    scalg_(py, &r__1, &c__2, &c__1, &c__1, &cglplot_1.xm, &
		    cglplot_1.dx);	/* SMOOTH SCALE FACTORS */
	    ik = -1;
	    gdx = (float)1. / cglplot_1.dx;
	    nx = cglplot_1.dx * dabs(*xaxl);
	    inx = -1;
	} else {
	    r__1 = dabs(*xaxl);
	    scale_(py, &r__1, &c__2, &c__1, &c__1, &cglplot_1.xm, &
		    cglplot_1.dx);	/* SMOOTH SCALE FACTORS */
	    ik = 0;
	    gdx = (float)1.;
	    inx = 1;
	}
    } else {
	if (if_ == 2 || if_ == 3) {
	    cglplot_1.xm = dabs(*xmin) + (float)1e-25;
	    if (cglplot_1.xm != r_int(&cglplot_1.xm)) {
		cglplot_1.xm = r_int(&cglplot_1.xm) - (float)1.;
	    }
	    r__2 = dabs(*xmax) + (float)1e-25;
	    r__1 = r_lg10(&r__2);
	    cglplot_1.dx = r_int(&r__1) + (float)1.;
	    cglplot_1.dx = (cglplot_1.dx - cglplot_1.xm) / dabs(*xaxl);
	    gdx = (float)1. / cglplot_1.dx;
	    ik = -1;
	    nx = cglplot_1.dx * dabs(*xaxl);
	    inx = -1;
	} else {
	    cglplot_1.xm = *xmin;
	    cglplot_1.dx = (*xmax - *xmin) / dabs(*xaxl);
	    gdx = (float)1.;
	    ik = 0;
	    inx = 1;
	}
    }
    if (*yaxl > (float)0.) {	/* INPUT SCALING */
	cglplot_1.ym = y[y_dim1 + 1];
	cglplot_1.dy = y[y_dim1 + 1];
	i__1 = *nn;
	for (in = 1; in <= i__1; ++in) {
	    i__2 = *np;
	    for (i = 1; i <= i__2; ++i) {	/* Computing MIN */
		r__1 = y[i + in * y_dim1];	/* Computing MAX */
		cglplot_1.ym = dmin(r__1,cglplot_1.ym);
		r__1 = y[i + in * y_dim1];
		cglplot_1.dy = dmax(r__1,cglplot_1.dy);
/* L6: */
	    }
	}
	py[0] = cglplot_1.ym;
	py[1] = cglplot_1.dy;
	if (if_ == 1 || if_ == 3) {
	    r__1 = dabs(*yaxl);
	    scalg_(py, &r__1, &c__2, &c__1, &c__1, &cglplot_1.ym, &
		    cglplot_1.dy);
/* SMOOTH SCALE FACTORS */
	    --ik;
	    gdy = (float)1. / cglplot_1.dy;
	    ny = cglplot_1.dy * dabs(*yaxl);
	    iny = -1;
	} else {
	    r__1 = dabs(*yaxl);
	    scale_(py, &r__1, &c__2, &c__1, &c__1, &cglplot_1.ym, &
		    cglplot_1.dy);
/* SMOOTH SCALE FACTORS */
	    ++ik;
	    gdy = (float)1.;
	    iny = 1;
	}
    } else {
	if (if_ == 1 || if_ == 3) {
	    r__1 = dabs(*ymin) + (float)1e-25;
	    cglplot_1.ym = r_lg10(&r__1);
	    if (cglplot_1.ym != r_int(&cglplot_1.ym)) {
		cglplot_1.ym = r_int(&cglplot_1.ym) - (float)1.;
	    }
	    r__2 = dabs(*ymax) + (float)1e-25;
	    r__1 = r_lg10(&r__2);
	    cglplot_1.dy = r_int(&r__1) + (float)1.;
	    cglplot_1.dy = (cglplot_1.dy - cglplot_1.ym) / dabs(*yaxl);
	    gdy = (float)1. / cglplot_1.dy;
	    ny = cglplot_1.dy * dabs(*yaxl);
	    --ik;
	    iny = -1;
	} else {
	    cglplot_1.ym = *ymin;
	    cglplot_1.dy = (*ymax - *ymin) / dabs(*yaxl);
	    ++ik;
	    gdy = (float)1.;
	    iny = 1;
	}
    }
    if (jf == 0) {	/* NO AXIS OR GRID */
	goto L77;
    }
    if (jf == 60) {	/* NO GRID */
	goto L76;
    }
    if (jf > 60) {	/* LOGRITHMIC GRID */
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
    if (jf >= 20) {	/* CARTESIAN GRID */
	if (jf >= 30) {
	    nx = -nx;
	}
	if (jf >= 40) {
	    ny = -ny;
	}
	if (*nt < 0) {	/* PEN COLOR */
	    r__1 = (real) icol[1];
	    plot_(&r__1, &c_b22, &c__0);
	}
	grid_(&c_b22, &c_b22, &gdx, &gdy, &nx, &ny); /* PRODUCE GRID */
	if (jf == 50) {
	    jf = 10;
	}
    }
L76:
    nadd = 0;
    if (*nt < 0) {
	nadd = 100000;		/* PEN COLOR */
	ic[0] = icol[2];
	ic[1] = icol[3];
	ic[2] = icol[4];
	ic[3] = icol[5];
    }
    ix = abs(*nxt) + nadd;
    xl = dabs(*xaxl) * i_sign(&c__1, nxt);
/* AXIS LENGTH WITH TICK INFOR */
    if (*nxt != 0) {			/* X-AXIS */
	if (if_ == 2 || if_ == 3) {
	    i__2 = -nadd - ix;
	    r__1 = dabs(xl);
	    lgaxs_(&c_b22, &c_b22, xtitl, &i__2, &r__1, &c_b22, &cglplot_1.xm,
		     &cglplot_1.dx, ic);
	    if (jf == 10) {		/* X-AXIS TICKS */
		r__1 = dabs(*yaxl);
		i__2 = ix + 100 + nadd;
		r__2 = dabs(xl);
		lgaxs_(&c_b22, &r__1, xtitl, &i__2, &r__2, &c_b22, &
			cglplot_1.xm, &cglplot_1.dx, ic);
	    }
	} else {
	    i__2 = -nadd - ix;
	    r__1 = cglplot_1.dx * dabs(xl) + cglplot_1.xm;
	    axis3_(&c_b22, &c_b22, xtitl, &i__2, &xl, &c_b22, &cglplot_1.xm, &
		    r__1, xt, xc, xf, ic);	/* X-AXIS */
	    if (jf == 10) {	/* X-AXIS TICKS */
		r__1 = dabs(*yaxl);
		i__2 = -ix - 100 - nadd;
		r__2 = -(doublereal)xl;
		r__3 = cglplot_1.dx * dabs(xl) + cglplot_1.xm;
		axis3_(&c_b22, &r__1, xtitl, &i__2, &r__2, &c_b22, &
			cglplot_1.xm, &r__3, xt, xc, xf, ic);
	    }
	}
    }
    iy = abs(*nyt) + 1000 + nadd;
    yl = dabs(*yaxl) * i_sign(&c__1, nyt);
    if (*nyt != 0) {
	if (if_ == 1 || if_ == 3) {
	    i__2 = nadd + iy;
	    r__1 = dabs(yl);
	    lgaxs_(&c_b22, &c_b22, ytitl, &i__2, &r__1, &c_b42, &cglplot_1.ym,
		     &cglplot_1.dy, ic);	/* Y-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*xaxl);
		i__2 = -iy - 100 - nadd;
		r__2 = dabs(yl);
		lgaxs_(&r__1, &c_b22, ytitl, &i__2, &r__2, &c_b42, &
			cglplot_1.ym, &cglplot_1.dy, ic);
	    }		/* Y-AXIS */
	} else {
	    i__2 = nadd + iy;
	    r__1 = cglplot_1.dy * dabs(yl) + cglplot_1.ym;
	    axis3_(&c_b22, &c_b22, ytitl, &i__2, &yl, &c_b42, &cglplot_1.ym, &
		    r__1, yt, yc, yf, ic);	/* Y-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*xaxl);
		i__2 = -iy - 100 - nadd;
		r__2 = cglplot_1.dy * dabs(yl) + cglplot_1.ym;
		axis3_(&r__1, &c_b22, ytitl, &i__2, &yl, &c_b42, &
			cglplot_1.ym, &r__2, yt, yc, yf, ic);
	    }
	}
    }
L77:
    if (ik == 1) {
	i__2 = *nn;
	for (in = 1; in <= i__2; ++in) {
	    if (*nt < 0) {		/* PEN COLOR */
		r__1 = (real) icol[in + 6];
		plot_(&r__1, &c_b22, &c__0);
	    }
	    if (abs(*nt) / 100 > 0) {	/* LINE TYPE */
		newpen_(&iline[in]);
	    }
	    i__1 = in - 1;
	    line_(&x[1], &y[in * y_dim1 + 1], np, &c__1, nsym, &i__1, &c__1, &
		    c__1, &cglplot_1.xm, &cglplot_1.dx, &cglplot_1.ym, &
		    cglplot_1.dy);	/* PLOT DATA */
/* L78: */
	}
    } else {
	if (ik == -1) {		/* CORRECT FLAG */
	    ik = 1;
	}
	if (ik == 0) {
	    ik = -1;
	}
	i__2 = *nn;
	for (in = 1; in <= i__2; ++in) {
	    if (*nt < 0) {	/* PEN COLOR */
		r__1 = (real) icol[in + 6];
		plot_(&r__1, &c_b22, &c__0);
	    }
	    if (abs(*nt) / 100 > 0) {/* LINE TYPE */
		newpen_(&iline[in]);
	    }
	    i__1 = in - 1;
	    lglin_(&x[1], &y[in * y_dim1 + 1], np, &c__1, nsym, &i__1, &ik, &
		    c__1, &c__1, &cglplot_1.xm, &cglplot_1.dx, &cglplot_1.ym, 
		    &cglplot_1.dy);
/* PLOT DATA */
/* L79: */
	}
    }
    if (abs(*nt) / 100 > 0) {
	newpen_(&c__1);
    }
/* RESET LINE TYPE */
/* Computing MAX */
    r__1 = dabs(*xc), r__2 = dabs(*yc);
    cs = dmax(r__1,r__2);	/* TITLE CHARACTER SIZE */
    if (*nt < 0) {
	r__1 = (real) icol[6];
	plot_(&r__1, &c_b22, &c__0);
    }			/* PEN COLOR */
    if (*nt != 0 && jf != 0) {	/* TITLE */
	xp = (float)0.;
	yp = (float)0.;
	i__2 = abs(*nt) % 100;
	symbol_(&xp, &yp, &cs, title, &c_b22, &i__2, &c_n3);
/* TITLE LENGTH */
	xp = (r__1 = *xaxl / (float)2., dabs(r__1)) - xp / (float)2.;
	if (xp < (float)0.) {
	    xp = (float)0.;
	}
	r__1 = dabs(yl) + (float).15;
	i__2 = abs(*nt) % 100;
	symbol_(&xp, &r__1, &cs, title, &c_b22, &i__2, &c_n1);
/* PLOT TITLE */
    }
    plot_(&c_b22, &c_b22, &c__3);
    if (*iflag > 0) {
	cterm_(&c__2);			/* ASK IF CLEAR SCREN */
	plotnd_();			/* CLOSE PLOT PACKAGE */
	repeat = FALSE_;
    }
    if (*iflag < 0) {
	repeat = TRUE_;
	cterm_(&c__1);			/* RETURN TO TEXT MODE */
    }
    return 0;
} /* glplot_ */

