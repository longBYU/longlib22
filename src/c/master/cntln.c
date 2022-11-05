
/* *** LAST REVISED ON 21-JAN-1994 15:12:36.15 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]CNTLN.C */

#include "my.h"

/* Common Block Declarations */

struct {
    real xmin, dxr, ymin, dyr;
} ccntrplt_;

#define ccntrplt_1 ccntrplt_

/* Table of constant values */

static integer c__1 = 1;
static integer c_n1 = -1;
static integer c__2 = 2;
static integer c__3 = 3;
static real c_b15 = (float)1.5;
static real c_b16 = (float).65;
static real c_b17 = (float)1.;
static real c_b19 = (float)0.;
static real c_b29 = (float)90.;
static integer c__0 = 0;
static real c_b36 = (float).25;
static integer c_n3 = -3;
static integer c__2000 = 2000;
static integer c__1200 = 1200;
static integer c__3194 = 3194;

/* ******************************************************************* */
/* Subroutine */ int cntln_(x, y, z, n, xh, yh, iflag, ncntrs, clist, iaxis, 
	xt, nxt, tx, tsx, fsx, yt, nyt, ty, tsy, fsy, t, nt, xast, xaen, yast,
	 yaen, icol, iline)
real *x, *y, *z;
integer *n;
real *xh, *yh;
integer *iflag, *ncntrs;
real *clist;
integer *iaxis;
char *xt;
integer *nxt;
real *tx, *tsx, *fsx;
char *yt;
integer *nyt;
real *ty, *tsy, *fsy;
char *t;
integer *nt;
real *xast, *xaen, *yast, *yaen;
integer *icol, *iline;
{
    /* Initialized data */

    static logical repeat = FALSE_;

    /* System generated locals */
    integer i__1;
    real r__1, r__2;

    /* Local variables */
    static integer nadd;
    static real xlen, ylen, zcon, xmax, ymax;
    extern /* Subroutine */ int plot_();
    static real zmin, zmax;
    extern /* Subroutine */ int axis3_();
    static integer i, j, k, l, m;
    extern /* Subroutine */ int scale_(), frame_(), cterm_();
    static real x1, y1;
    static integer ib[1200], ic[4], ie[6388]	/* was [3194][2] */, lambda[
	    3194], jf;
    static real fk;
    static integer ip[1200];
    static real dx;
    static integer it[6000]	/* was [2000][3] */;
    static real dy, xi[3194];
    static integer ledges;
    extern /* Subroutine */ int newpen_(), plotnd_();
    static integer ixaxis, iyaxis;
    extern /* Subroutine */ int symbol_(), cntour_();
    static real daa;
    static integer ibe[3194], jff;
    static real eta[3194];
    static integer ite[12776]	/* was [3194][4] */;
    static real pas[2];
    static integer ipp, ilu;
    extern /* Subroutine */ int triangc_();
    static integer itriang;
    extern /* Subroutine */ int interpc_();

/* 	CREATED BY D. LONG     FEB, 1986	AT JPL */

/* 	ROUTINE TO PLOT DATA CONTOURS SPECIFIED AS (X,Y,Z) TRIPLES */

/* 	X,Y,Z	(R) ARRAYS CONTAINING DATA POINTS */
/* 	N	(I) NUMBER OF DATA POINTS */
/* 	XH,YH   (R) LENGTH OF EACH AXIS (INCHES) */
/* 	IFLAG	(I) PLOT FLAG */
/* 		>10000	REPEAT PLOTTING BUT DO NOT INTIALIZE PLOTTER */
/* 		< 0	REPEAT PLOTTING (DON'T CLOSE PLOTTER OUTPUT) */
/* 		= 0	CLOSE PLOTTER OUTPUT--DO NOT PRODUCE PLOT */
/* 		> 0	SINGLE PLOT OUTPUT ONLY (PLOTTER OUTPUT CLOSED) */
/* 	(ONE'S DIGIT) = 1 DO NOT USE COLOR ARRAY OR LINE TYPE ARRAY */
/* 		      = 2 USE COLOR ARRAY BUT NOT LINE TYPE ARRAY */
/* 		      = 3 DO NOT USE COLOR ARRAY BUT USE LINE TYPE ARRAY */
/* 		      = 4 USE COLOR ARRAY AND LINE TYPE ARRAY */
/* 	(TEN'S DIGIT) = 0 JUST X,Y AXES */
/* 		      = 1 X AND Y AXES IN A BOX */
/* 	(HUNDRED'S)   = 0 ASK WHICH SCREEN DEVICE TO USE */
/* 		      <>0 SCREEN DEVICE CODE NUMBER */
/* 	NCNTRS	(I) NUMBER OF CONTOUR LINES TO BE DRAWN */
/* 		    (SELF COMPUTING IF NCNTRS.LE.0) */
/* 	CLIST   (R) ARRAY OF CONSTANT CONTOUR VALUES IF NCNTRS > 0 */
/* 		NOTE: IF NCNTRS <= 0, THEN CLIST(1) = BASE VALUE, */
/* 		AND CLIST(2) = INCREMENT VALUE (DELTA) */
/* 	IAXIS	(I) AXIS OPTION FLAG */
/* 			< 0 DO NOT PLOT AXES */
/* 	(ONE'S DIGIT)	= 1 PLOT Y AXIS USING COMPUTED SCALE */
/* 			= 2 PLOT Y AXIS USING COMPUTED, SMOOTHED SCALE */
/* 			= 3 PLOT Y AXIS USING INPUT SCALE--VARIABLES ACCESSED */
/* 			= 4 PLOT Y AXIS USING INPUT, SMOOTHED SCALE--VARIABLES ACCESSED */
/* 	(TEN'S DIGIT)	= 1 PLOT X AXIS USING COMPUTED SCALE */
/* 			= 2 PLOT X AXIS USING COMPUTED, SMOOTHED SCALE */
/* 			= 3 PLOT X AXIS USING INPUT SCALE--VARIABLES ACCESSED */
/* 			= 4 PLOT X AXIS USING INPUT, SMOOTHED SCALE--VARIABLES ACCESSED */
/* 	(HUNDRED'S)	= 0 NORMAL */
/* 			= 1 TRIANGULATION ONLY PLOTTED */
/* 	XT,YT	(B) STRINGS FOR AXIS TITLES */
/* 	NXT,NYT	(I) LENGTH OF AXIS TITLES */
/* 		     IF ZERO THEN AXIS NOT PLOTTED */
/* 		     IF LESS THAN ZERO THEN AXIS TICKS ARE OPPOSITE AXIS TITLE */
/* FOLLOWING ONLY ACCESSED IF IAXIS > 0 */
/* 	TX,TY	(R) NUMBER OF TICK MARKS (SEE AXIS3) */
/* 	TSX,TSY	(R) SIZE OF TITLE AND NUMBERS OF AXIS */
/* 			  IF LESS THAN ZERO DO NOT AUTO-SCALE BY (x10^POWER) */
/* 	FSX,FSY	(R) NUMBER FORMAT OF AXISES (SEE AXIS3) */
/* 	T	(B) PLOT TITLE */
/* 	NT	(I) NUMBER OF CHARACTERS IN TITLE */
/* 			IF NT=0 NO TITLE PLOTTED */
/* 	XAST,YAST(R) AXIS START VALUES */
/* 	XAEN,YAEN(R) AXIS END VALUES */
/* 	ICOL	(I) COLOR INDEX TABLE (ACCESSED IF 1'S DIGIT OF IFLAG=2 */
/* 			ICOL(1) AXIS LINE COLOR */
/* 			ICOL(2) AXIS NUMERIC LABEL COLOR */
/* 			ICOL(3) AXIS LABEL COLOR */
/* 			ICOL(4) AXIS EXPONENT COLOR */
/* 			ICOL(5) TITLE COLOR */
/* 			ICOL(6) SURFACE COLOR */
/* 	ILINE	(I) LINE TYPE ARRAY */

/* 	EXTERNAL CALLS: */

/* 		INTERPC */
/* 		TRIANGC */
/* 		  MIDC (FUNCTION) */
/* 		CNTOUR */
/* 		  CNTCRV */
/* --------------------------------------------------------------------- 
*/



    /* Parameter adjustments */
    --iline;
    --icol;
    --clist;
    --z;
    --y;
    --x;

    /* Function Body */

    if (*n > 1200) {
	printf("\n*** CNTLN OUT OF SPACE ERROR ***\n");
	cterm_(&c_n1);
    }

    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();
	}
/* CLOSE PLOTTER */
	repeat = FALSE_;
	return 0;
    }

    xlen = dabs(*xh);
    ylen = dabs(*yh);
    iyaxis = abs(*iaxis) % 10;
    ixaxis = abs(*iaxis) % 100 / 10;
    itriang = abs(*iaxis) % 1000 / 100;
    if (ixaxis > 2) {
	xmax = *xaen;
	ccntrplt_1.xmin = *xast;
    } else {
	xmax = x[1];
	ccntrplt_1.xmin = x[1];
	i__1 = *n;
	for (i = 1; i <= i__1; ++i) {
/* Computing MAX */
	    r__1 = xmax, r__2 = x[i];
	    xmax = dmax(r__1,r__2);
/* Computing MIN */
	    r__1 = ccntrplt_1.xmin, r__2 = x[i];
	    ccntrplt_1.xmin = dmin(r__1,r__2);
/* L16: */
	}
    }
    if (ixaxis == 2 || ixaxis == 4) {
	pas[0] = xmax;
	pas[1] = ccntrplt_1.xmin;
	scale_(pas, &xlen, &c__2, &c__1, &c__1, &ccntrplt_1.xmin, &daa);
	xmax = ylen * daa + ccntrplt_1.xmin;
    }

    if (iyaxis > 2) {
	ymax = *yaen;
	ccntrplt_1.ymin = *yast;
    } else {
	ymax = y[1];
	ccntrplt_1.ymin = y[1];
	i__1 = *n;
	for (i = 1; i <= i__1; ++i) {
/* Computing MAX */
	    r__1 = ymax, r__2 = y[i];
	    ymax = dmax(r__1,r__2);
/* Computing MIN */
	    r__1 = ccntrplt_1.ymin, r__2 = y[i];
	    ccntrplt_1.ymin = dmin(r__1,r__2);
/* L17: */
	}
    }
    if (iyaxis == 2 || iyaxis == 4) {
	pas[0] = ymax;
	pas[1] = ccntrplt_1.ymin;
	scale_(pas, &ylen, &c__2, &c__1, &c__1, &ccntrplt_1.ymin, &daa);
	ymax = ylen * daa + ccntrplt_1.ymin;
    }

/* 	INTIALIZE PLOT PACKAGE */

    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = jf % 10000 / 100;
	frame_(&c__3, &ilu, &c_b15, &c_b16, &c_b17);
/* INTIALIZE */
    } else {
	cterm_(&c_n1);
/* PUT TERMINAL */
    }
    jff = jf % 100 / 10;
    jf %= 10;

    if (*iaxis > 0) {
/* PLOT AXIS LABELS */
	nadd = 0;
	if (jf == 2 || jf == 4) {
	    nadd = 100000;
	    ic[0] = icol[1];
	    ic[1] = icol[2];
	    ic[2] = icol[3];
	    ic[3] = icol[4];
	}
	if (*nxt != 0) {
/* PLOT X AXIS */
	    i__1 = -nadd - abs(*nxt);
	    r__1 = xlen * (*nxt >= 0 ? 1 : -1);
	    axis3_(&c_b19, &c_b19, xt, &i__1, &r__1, &c_b19, &ccntrplt_1.xmin,
		     &xmax, tx, tsx, fsx, ic);
	    if (jff == 1) {
		i__1 = nadd + 101;
		r__1 = xlen * (*nxt >= 0 ? 1 : -1);
		axis3_(&xlen, &c_b19, xt, &i__1, &r__1, &c_b19, &
			ccntrplt_1.xmin, &xmax, tx, tsx, fsx, ic);
	    }
	}
	if (*nyt != 0) {
/* PLOT Y AXIS */
	    i__1 = abs(*nyt) + 1000 + nadd;
	    r__1 = ylen * (*nyt >= 0 ? 1 : -1);
	    axis3_(&c_b19, &c_b19, yt, &i__1, &r__1, &c_b29, &ccntrplt_1.ymin,
		     &ymax, ty, tsy, fsy, ic);
	    if (jff == 1) {
		i__1 = nadd + 101;
		r__1 = ylen * (*nyt >= 0 ? 1 : -1);
		axis3_(&c_b19, &c_b19, yt, &i__1, &r__1, &c_b29, &
			ccntrplt_1.ymin, &ymax, ty, tsy, fsy, ic);
	    }
	}
    }

/* 	ADD TITLE */

    if (jf == 2 || jf == 4) {		/* COLOR */
	r__1 = (real) icol[5];
	plot_(&r__1, &c_b19, &c__0);
    }
    if (*nt > 0) {
	x1 = (float)0.;
	y1 = (float)0.;			/* GET TITLE LENGTH */
	symbol_(&x1, &y1, &c_b36, t, &c_b19, nt, &c_n3);
	x1 = (xlen - x1) / (float)2.;
	r__1 = ylen + (float).1;
/* PLOT TITLE */
	symbol_(&x1, &r__1, &c_b36, t, &c_b19, nt, &c_n1);
    }

/* 	BEGIN SURFACE PLOTTING */

    dx = (float)1.;
    dy = (float)1.;
    if (xmax - ccntrplt_1.xmin != (float)0.) {
	dx = xlen / (xmax - ccntrplt_1.xmin);
    }
    if (ymax - ccntrplt_1.ymin != (float)0.) {
	dy = ylen / (ymax - ccntrplt_1.ymin);
    }

/* CALL ROUTINE TRAING TO TRIANGULATE X-Y DATA POINTS */

    triangc_(&x[1], &y[1], n, it, &c__2000, &m, ip, ib, &c__1200, &ledges, &
	    c__3194, ie, ibe, ite);

/* 	PLOT TRIANGULATED SURFACE IF DESIRED */

    ccntrplt_1.dxr = (float)1. / dx;
    ccntrplt_1.dyr = (float)1. / dy;
    if (itriang == 1) {
	i__1 = m;
	for (i = 1; i <= i__1; ++i) {
	    ipp = 3;
	    for (j = 1; j <= 3; ++j) {
		l = it[i + j * 2000 - 2001];
		x1 = dx * (x[l] - ccntrplt_1.xmin);
		y1 = dy * (y[l] - ccntrplt_1.ymin);
		plot_(&x1, &y1, &ipp);
		ipp = 2;
/* L33: */
	    }
	    l = it[i - 1];
	    x1 = dx * (x[l] - ccntrplt_1.xmin);
	    y1 = dy * (y[l] - ccntrplt_1.ymin);
	    plot_(&x1, &y1, &c__2);
/* L35: */
	}
	goto L300;
    }

/* DETERMINE THE RANGE OF THE Z DATA UNDER CONSIDERATION */

/* L120: */
    zmin = z[1];
    zmax = zmin;
    i__1 = *n;
    for (k = 2; k <= i__1; ++k) {
/* Computing MIN */
	r__1 = zmin, r__2 = z[k];
	zmin = dmin(r__1,r__2);
/* Computing MAX */
	r__1 = zmax, r__2 = z[k];
	zmax = dmax(r__1,r__2);
/* L50: */
    }
    k = 0;

/* HAS A CONTOUR LIST BEEN GIVEN? . . */

    k = 0;
    fk = (float)-1.;
L200:
    if (*ncntrs > 0) {
	goto L180;
    }

/* DETERMINE (NEXT) CONTOUR CONSTANT VALUE */

L210:
    fk += (float)1.;
    zcon = fk * clist[2] + clist[1];
    if (zcon > zmin && zcon < zmax) {
	goto L150;
    }
    if (zcon > zmax && clist[2] >= (float)0.) {
	goto L300;
    }
    if (zcon < zmin && clist[2] <= (float)0.) {
	goto L300;
    }
    goto L210;

L180:
    ++k;
    if (k > *ncntrs) {
	goto L300;
    }
    zcon = clist[k];
    if (zcon < zmin || zcon > zmax) {
	goto L200;
    }

/* CALL ROUTINE INTERPC TO */
/* INTERPOLATE FOR CONTOUR LINE DATA POINTS */

L150:
    interpc_(&x[1], &y[1], &z[1], n, &zcon, &ledges, ie, lambda, xi, eta, &j, 
	    &c__3194);

/* ANY DATA POINTS FOUND? . . */
/* CALL ROUTINE CNTOUR TO SORT THE INTERPOLATED POINTS */
/* ON THE CONTOUR LINE AND DRAW IT */

    if (jf == 2 || jf == 4) {
	r__1 = (real) icol[k + 5];
	plot_(&r__1, &c_b19, &c__0);
    }
/* COLOR */
    if (jf == 3 || jf == 4) {
	newpen_(&iline[k]);
    }
/* LINE TYPE */
    if (j != 0) {
	cntour_(&zcon, xi, eta, lambda, &j, ibe, ite, &c__3194, &dx, &
		ccntrplt_1.xmin, &dy, &ccntrplt_1.ymin);
    }
    goto L200;

/* 	FINISH ROUTINE */

L300:
    plot_(&c_b19, &c_b19, &c__3);
/* PEN UP */
    if (jf == 3 || jf == 4) {
	newpen_(&c__1);
    }
/* RESET LINE TYPE */
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
} /* cntln_ */

