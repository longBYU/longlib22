
/* *** LAST REVISED ON 23-DEC-1993 06:35:26.88 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]LCNTR.C */

#include "my.h"

/* Common Block Declarations */

struct {
    real xm, dx, ym, dy;
} ccntrplt_;

#define ccntrplt_1 ccntrplt_

/* Table of constant values */

static real c_b2 = (float)1.2;
static real c_b4 = (float)1.;
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c__1 = 1;
static real c_b26 = (float)0.;
static integer c__0 = 0;
static real c_b46 = (float)90.;
static real c_b59 = (float).15;
static integer c_n3 = -3;
static integer c__3 = 3;

/* Subroutine */ int lcntr_(v, ndx, ndy, nx, ny, nlevels, cval, nch, nmin, 
	iflag, work, xaxl, yaxl, xtitl, nxt, ytitl, nyt, title, nt, xmin, 
	xmax, ymin, ymax, icol, iline)
real *v;
integer *ndx, *ndy, *nx, *ny, *nlevels;
real *cval;
integer *nch, *nmin, *iflag;
real *work, *xaxl, *yaxl;
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
    integer v_dim1, v_offset, i__1, i__2;
    real r__1, r__2;

    /* Builtin functions */
    double r_nint(), r_lg10(), r_int(), r_sign();

    /* Local variables */
    static integer nadd;
    extern /* Subroutine */ int grid_(), axis_(), plot_(), scale_(), scalg_(),
	     frame_(), lgrid_(), cterm_(), lgaxs_();
    static integer n1, n2;
    static real ae;
    static integer ic[4], if_, jf, ii, ik;
    static real as, cs, cv;
    static integer nl, pl, ix, iy;
    static real xl, py[2], yl, xp, yp;
    extern /* Subroutine */ int gcontr_(), newpen_(), plotnd_(), symbol_();
    static real dx2, dy2, xm2, ym2;
    static integer icl;
    static real gdx, gdy;
    static integer ilu, ngx, ngy, inx, iny;
    static real dxx, dyy;

/* 	CREATED BY D. LONG    MAY, 1986	AT JPL */

/* 	MASTER ROUTINE TO PLOT A CONTOUR PLOT WITH LOG/LINEAR AXIS */
/* 	THIS ROUTINE PLOTS CONTINUOUS CONTOURS AND CAN LABEL THEM */
/* 	USING GCONTR */

/* 	V	REAL DATA VALUE ARRAY DIMENSIONED V(NDX,NDY) */
/* 	NDX,NDY	INT  DIMENSIONS OF V */
/* 	NX	INT  NUMBER OF X VALUES */
/* 	NY	INT  NUMBER OF Y VALUES */
/* 	NLEVELS REAL NUMBER OF CONTOUR LEVELS */
/* 			< 0 MIN(V) AND MAX(V) ARE USED WITH UNIFORM STEPS */
/* 	CVAL	REAL ARRAY OF CONTOUR VALUES */
/* 			IF NLEVELS < 0 THIS ARRAY IS FILLED WITH */
/* 			THE VALUES USED FOR CONTOURS: */
/* 			CVAL(J)=MIN(V)+(J-1)*(MAX(V)-MIN(V))/(J-1) */
/* 	NCH	INT  LABELING OPTION FLAG */
/* 			< 0 LABEL WITH CONTOUR VALUE (NCH IS NUMBER */
/* 				OF DIGITS TO THE LEFT OF DECIMAL */
/* 			= 0 NO LABELING OF CONTOURS */
/* 			> 0 LABEL WITH LETTERS */
/* 	NMIN	INT  MINIMUM NUMBER OF CELL FOR CONTOUR TO BE LABLED */
/* 	IFLAG	INT */
/* 		  (MAG) >10000 REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER */
/* 			< 0  REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT) */
/* 			= 0  CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT */
/* 			> 0  SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED) */
/* 				NOTE: AXIS MAY BE LOG, BUT POINTS ARE PLOTTED */
/* 				      LINEARILY SPACED */
/* 	  (ONE'S DIGIT) = 1 X AXIS LINEAR, Y AXIS LOGRITHMIC (BASE 10) */
/* 	  (ONE'S DIGIT) = 2 X AXIS LOGRITHMIC,Y AXIS LINEAR */
/* 	  (ONE'S DIGIT) = 3 X AXIS LOGRITHMIC,Y AXIS LOGRITHMIC */
/* 	  (ONE'S DIGIT) = 4 X AXIS LINEAR, Y AXIS LINEAR */
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
/* 		      <>0 SCREEN DEVICE CODE NUMBER */
/* 	WORK	INT   WORKING ARRAY DIMENSIONED AT LEAST (2*NX*NY+1)/31 */
/* 	XAXL	REAL  X AXIS LENGTH IN INCHES */
/* 			> 0  USE INPUT VALUE AXIS SCALING */
/* 			< 0  USE SMOOTHED AXIS SCALING */
/* 	YAXL	REAL  Y AXIS LENGTH IN INCHES */
/* 			> 0  USE INPUT VALUE SCALING */
/* 			< 0  USE SMOOTHED AXIS SCALING */
/* 	XTITL	CHAR  X AXIS TITLE */
/* 	NXT	INT   NUMBER OF CHARACTERS IN X AXIS TITLE STRING */
/* 			< 0  TICKS ON INSIDE OF AXIS */
/* 			= 0  NO AXIS */
/* 			> 0  TICKS ON TITLE SIDE OF AXIS */
/* 	YTITL	CHAR  Y AXIS TITLE */
/* 	NYT	INT   NUMBER OF CHARACTERS IN Y AXIS TITLE STRING */
/* 			< 0  TICKS ON INSIDE OF AXIS */
/* 			= 0  NO AXIS */
/* 			> 0  TICKS ON TITLE SIDE OF AXIS */
/* 	TITLE	CHAR  PLOT TITLE */
/* 	NT	INT   NUMBER OF CHARACTERS IN PLOT TITLE */
/* 			= 0  NO TITLE */
/* 			< 0  USE PEN COLOR ARRAY */
/* 			IF ABS(NT)/100 > 0 THEN USE LINE TYPE ARRAY */
/* 	XMIN	REAL  MINIMUM VALUE DISPLAYED ON X AXIS */
/* 	XMAX	REAL  MAXIMUM VALUE DISPLAYED ON X AXIS */
/* 	YMIN	REAL  MINIMUM VALUE DISPLAYED ON Y ARRAY */
/* 	YMAX	REAL  MAXIMUM VALUE DISPLAYED ON Y ARRAY */
/* 	ICOL	INT   ARRAY OF PEN COLORS DIMENSIONED ICOL(5+NLEVELS) */
/* 			ICOL(1) = GRID COLOR */
/* 			ICOL(2) = AXIS LINE COLOR */
/* 			ICOL(3) = AXIS NUMBERS COLOR */
/* 			ICOL(4) = AXIS TITLE COLOR */
/* 			ICOL(5) = AXIS EXPONENT COLOR */
/* 			ICOL(6) = TITLE COLOR (COLOR UPON RETURN) */
/* 			ICOL(7) = CONTOUR LEVEL 1 */
/* 			ICOL(8) = CONTOUR LEVEL 2 */
/* 			   .        .      . */
/* 			ICOL(6+NLEVELS) = CONTOUR LEVEL NLEVELS (= AEND) */
/* 	ILINE	INT  ARRAY OF PEN TYPES FOR CONTOURS */

    /* Parameter adjustments */
    --iline;
    --icol;
    --cval;
    v_dim1 = *ndx;
    v_offset = v_dim1 + 1;
    v -= v_offset;

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
	frame_(&pl, &ilu, &c_b2, &c_b2, &c_b4);
/* INTIALIZE PLOT PACKAGE */
    } else {
	cterm_(&c_n1);
/* RESTORE PLOT MODE */
	jf %= 100;
    }
    jf %= 100;
    if_ = jf;
    if (if_ > 10) {
	if_ %= 10;
    }
    jf -= if_;
    r__1 = dabs(*xaxl);
    ngx = r_nint(&r__1);
/* GRID SIZES */
    r__1 = dabs(*yaxl);
    ngy = r_nint(&r__1);
    py[0] = *xmin;
    py[1] = *xmax;
    r__1 = dabs(*xaxl);
    scale_(py, &r__1, &c__2, &c__1, &c__1, &xm2, &dx2);
    if (if_ == 2 || if_ == 3) {
	r__1 = dabs(*xaxl);
	scalg_(py, &r__1, &c__2, &c__1, &c__1, &ccntrplt_1.xm, &ccntrplt_1.dx)
		;
/* SMOOTH SCALE FACTORS */
	ik = -1;
	gdx = (float)1. / ccntrplt_1.dx;
	ngx = ccntrplt_1.dx * dabs(*xaxl);
	inx = -1;
    } else {
	r__1 = dabs(*xaxl);
	scale_(py, &r__1, &c__2, &c__1, &c__1, &ccntrplt_1.xm, &ccntrplt_1.dx)
		;
/* SMOOTH SCALE FACTORS */
	ik = 0;
	gdx = (float)1.;
	inx = 1;
    }
    if (*xaxl > (float)0.) {
/* INPUT SCALING */
	xm2 = *xmin;
	dx2 = (*xmax - *xmin) / dabs(*xaxl);
	if (if_ == 2 || if_ == 3) {
	    r__1 = dabs(*xmin) + (float)1e-25;
	    ccntrplt_1.xm = r_lg10(&r__1);
	    if (ccntrplt_1.xm != r_int(&ccntrplt_1.xm)) {
		ccntrplt_1.xm = r_int(&ccntrplt_1.xm) - (float)1.;
	    }
	    r__2 = dabs(*xmax) + (float)1e-25;
	    r__1 = r_lg10(&r__2);
	    ccntrplt_1.dx = r_int(&r__1) + (float)1.;
	    ccntrplt_1.dx = (ccntrplt_1.dx - ccntrplt_1.xm) / dabs(*xaxl);
	    gdx = (float)1. / ccntrplt_1.dx;
	    ngx = ccntrplt_1.dx * dabs(*xaxl);
	} else {
	    ccntrplt_1.xm = *xmin;
	    ccntrplt_1.dx = (*xmax - *xmin) / dabs(*xaxl);
	    gdx = (float)1.;
	}
    }
    py[0] = *ymin;
    py[1] = *ymax;
    r__1 = dabs(*yaxl);
    scale_(py, &r__1, &c__2, &c__1, &c__1, &ym2, &dy2);
    if (if_ == 1 || if_ == 3) {
	r__1 = dabs(*yaxl);
	scalg_(py, &r__1, &c__2, &c__1, &c__1, &ccntrplt_1.ym, &ccntrplt_1.dy)
		;
/* SMOOTH SCALE FACTORS */
	--ik;
	gdy = (float)1. / ccntrplt_1.dy;
	ngy = ccntrplt_1.dy * dabs(*yaxl);
	iny = -1;
    } else {
	r__1 = dabs(*yaxl);
	scale_(py, &r__1, &c__2, &c__1, &c__1, &ccntrplt_1.ym, &ccntrplt_1.dy)
		;
/* SMOOTH SCALE FACTORS */
	++ik;
	gdy = (float)1.;
	iny = 1;
    }
    if (*yaxl > (float)0.) {
/* INPUT SCALING */
	ym2 = *ymin;
	dy2 = (*ymax - *ymin) / dabs(*yaxl);
	if (if_ == 1 || if_ == 3) {
	    r__1 = dabs(*ymin) + (float)1e-25;
	    ccntrplt_1.ym = r_lg10(&r__1);
	    if (ccntrplt_1.ym != r_int(&ccntrplt_1.ym)) {
		ccntrplt_1.ym = r_int(&ccntrplt_1.ym) - (float)1.;
	    }
	    r__2 = dabs(*ymax) + (float)1e-25;
	    r__1 = r_lg10(&r__2);
	    ccntrplt_1.dy = r_int(&r__1) + (float)1.;
	    ccntrplt_1.dy = (ccntrplt_1.dy - ccntrplt_1.ym) / dabs(*yaxl);
	    gdy = (float)1. / ccntrplt_1.dy;
	    ngy = ccntrplt_1.dy * dabs(*yaxl);
	} else {
	    ccntrplt_1.ym = *ymin;
	    ccntrplt_1.dy = (*ymax - *ymin) / dabs(*yaxl);
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
	i__1 = inx * ngx;
	i__2 = iny * ngy;
	lgrid_(&c_b26, &c_b26, &gdx, &gdy, &i__1, &i__2, &ii);
	goto L76;
    }
    if (jf >= 20) {
/* CARTESIAN GRID */
	if (jf >= 30) {
	    ngx = -ngx;
	}
	if (jf >= 40) {
	    ngy = -ngy;
	}
	if (*nt < 0) {
	    r__1 = (real) icol[1];
	    plot_(&r__1, &c_b26, &c__0);
	}
/* PEN COLOR */
	grid_(&c_b26, &c_b26, &gdx, &gdy, &ngx, &ngy);
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
	    lgaxs_(&c_b26, &c_b26, xtitl, &i__1, &xl, &c_b26, &ccntrplt_1.xm, 
		    &ccntrplt_1.dx, ic);
/* X-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*yaxl);
		i__1 = ix + 100 + nadd;
		lgaxs_(&c_b26, &r__1, xtitl, &i__1, &xl, &c_b26, &
			ccntrplt_1.xm, &ccntrplt_1.dx, ic);
	    }
/* X-AXIS */
	} else {
	    i__1 = -ix - nadd;
	    axis_(&c_b26, &c_b26, xtitl, &i__1, &xl, &c_b26, &ccntrplt_1.xm, &
		    ccntrplt_1.dx, &n1, &n2, ic);
/* X-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*yaxl);
		i__1 = ix + 100 + nadd;
		axis_(&c_b26, &r__1, xtitl, &i__1, &xl, &c_b26, &
			ccntrplt_1.xm, &ccntrplt_1.dx, &n1, &n2, ic);
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
	    lgaxs_(&c_b26, &c_b26, ytitl, &i__1, &yl, &c_b46, &ccntrplt_1.ym, 
		    &ccntrplt_1.dy, ic);
/* Y-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*xaxl);
		i__1 = -iy - 100 - nadd;
		lgaxs_(&r__1, &c_b26, ytitl, &i__1, &yl, &c_b46, &
			ccntrplt_1.ym, &ccntrplt_1.dy, ic);
	    }
/* Y-AXIS */
	} else {
	    i__1 = iy + nadd;
	    axis_(&c_b26, &c_b26, ytitl, &i__1, &yl, &c_b46, &ccntrplt_1.ym, &
		    ccntrplt_1.dy, &n1, &n2, ic);
/* Y-AXIS */
	    if (jf == 10) {
		r__1 = dabs(*xaxl);
		i__1 = -iy - 100 - nadd;
		axis_(&r__1, &c_b26, ytitl, &i__1, &yl, &c_b46, &
			ccntrplt_1.ym, &ccntrplt_1.dy, &n1, &n2, ic);
	    }
/* Y-AXIS */
	}
    }

L77:
    nl = abs(*nlevels);
    if (nl == 0) {
	nl = 2;
    }
    ae = (float)1e20;
    if (*nlevels <= 0) {
	ae = v[v_dim1 + 1];
	as = v[v_dim1 + 1];
	i__1 = abs(*nx);
	for (ix = 1; ix <= i__1; ++ix) {
	    i__2 = *ny;
	    for (iy = 1; iy <= i__2; ++iy) {
/* Computing MAX */
		r__1 = ae, r__2 = v[ix + iy * v_dim1];
		ae = dmax(r__1,r__2);
/* Computing MIN */
		r__1 = as, r__2 = v[ix + iy * v_dim1];
		as = dmin(r__1,r__2);
/* L65: */
	    }
	}
	i__2 = nl;
	for (ix = 1; ix <= i__2; ++ix) {
	    cval[ix] = as + (ix - 1) * (ae - as) / (real) (nl - 1);
/* L66: */
	}
    }
    dxx = *xaxl / (i__2 = *nx - 1, (real) abs(i__2));
    dyy = *yaxl / (i__2 = *ny - 1, (real) abs(i__2));

    icl = 0;
    if (abs(*nt) / 100 > 0) {
	icl = 2;
    }

/* 	CALL CONTOURING ROUTINE ONCE FOR EACH CONTOUR LEVEL TO MINIMIZE */
/* 	STORAGE SPACE AND PEN CHANGES */

    i__2 = nl;
    for (ix = 1; ix <= i__2; ++ix) {
	cv = cval[ix];
	if (*nt < 0) {
	    r__1 = (real) icol[ix + 6];
	    plot_(&r__1, &c_b26, &c__0);
	}
/* PEN COLOR */
	if (icl != 0) {
	    ic[0] = iline[ix];
	}
/* LINE TYPE */
	i__1 = -ix;
	gcontr_(&v[v_offset], ndx, ndy, nx, ny, &dxx, &dyy, &cv, &i__1, &ae, 
		work, nch, &c_b59, nmin, &icl, ic, ic);
/* L100: */
    }

/* 	PLOT TITLE AND FINISH UP ROUTINE */

    if (abs(*nt) / 100 > 0) {
	newpen_(&c__1);
    }
/* RESET LINE TYPE */
    cs = (float).21;
/* TITLE CHARACTER SIZE */
    if (*nt < 0) {
	r__1 = (real) icol[6];
	plot_(&r__1, &c_b26, &c__0);
    }
/* PEN COLOR */
    if (*nt != 0 && jf != 0) {
/* TITLE */
	xp = (float)0.;
	yp = (float)0.;
	i__2 = abs(*nt) % 100;
	symbol_(&xp, &yp, &cs, title, &c_b26, &i__2, &c_n3);
/* TITLE LENGTH */
	xp = (r__1 = *xaxl / (float)2., dabs(r__1)) - xp / (float)2.;
	if (xp < (float)0.) {
	    xp = (float)0.;
	}
	r__1 = dabs(*yaxl) + (float).15;
	i__2 = abs(*nt) % 100;
	symbol_(&xp, &r__1, &cs, title, &c_b26, &i__2, &c_n1);
/* PLOT TITLE */
    }
    plot_(&c_b26, &c_b26, &c__3);
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
} /* lcntr_ */

