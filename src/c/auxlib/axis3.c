
/* *** LAST REVISED ON 24-DEC-1993 07:39:06.19 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]AXIS3.C */

#include "my.h"

/* Table of constant values */
static real c_b8 = (float)0.;
static doublereal c_b117 = 10.;
static real c_b94 = (float)1e3;

static integer c_n3 = -3;
static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__4 = 4;

/* Subroutine */ int axis3_(real *x0, real *y0, char *t, integer *n0, real *
	s0, real *a0, real *b0, real *c0, real *d0, real *e0, real *f0, 
	integer *icol)
{
    /* Initialized data */

    static real space = .08f;

    /* System generated locals */
    integer i__1, i__2, i__3;
    real r__1, r__2;
    doublereal d__1;

    /* Builtin functions */
    double cos(doublereal), sin(doublereal), r_lg10(real *), r_mod(real *, 
	    real *), r_int(real *), pow_dd(doublereal *, doublereal *);

    /* External functions */
    extern /* Subroutine */ int plot_(real *, real *, integer *);
    extern /* Subroutine */ int number_(real *, real *, real *, real *, real *
	    , real *, integer *);
    extern /* Subroutine */ int symbol_(real *, real *, real *, char *, real *
	    , integer *, integer *);

    /* Local variables */
    static integer i, j, k;
    static real e1, c1;
    static integer n1;
    static real x1, y1, y2, x2, x3, fa;
    static integer nc;
    static real co;
    static integer nd, ng;
    static real cs, x01, y01, si, tl, xj, xn, xs;
    static real tl1, ang;
    static integer ndd;
    static real hor;
    static integer njt;
    static real dnx, dny;
    static integer nnt;
    static real dty, dtx;
    static integer nst;

/* 	WRITTEN BY DGL  17-OCT-1983 */
/* 	REVISED BY DGL  28-AUG-1987 */

/* 	PLOTS A SINGLE COORDINATE AXIS USING SYMBOL AND NUMBER. */
/* 	THIS VERSION OF AXIS CAN HANDLE NON-INTEGER AXIS LENGTH */
/* 	AND PERMITS FORMATTING OF THE NUMERIC LABELS. */

/* 	X0  (R)	X COORDINATE OF START OF AXIS */
/* 	Y0  (R)	Y COORDINATE OF START OF AXIS */
/* 	T   (C)	CHARACTER STRING TO DESCRIBE AXIS */
/* 	N0  (I)	NUMBER OF CHARACTERS IN STRING */
/* 		- ON CLOCKWISE SIDE OF AXIS (NORMAL FOR X) */
/* 		+ ON COUNTER CLOCKWISE SIDE OF AXIS (NORMAL FOR Y) */
/* 		HUNDREDS DIGIT	= 1 NO LABELING OF AXIS--TICKS AND LINE ONLY */
/* 		THOUSANDS DIGIT = 1 HORIZONTAL NUMBERS IN Y AXIS LABEL */
/* 	S0  (R)	LENGTH OF AXIS IN INCHES */
/* 		< 0	TICKS PLACED ON OPPOSITE SIDE OF AXIS LABEL */
/* 		= 0	NO ACTION (NOP) */
/* 		> 0	NORMAL */
/* 	A0  (R)	ANGLE OF AXIS WITH RESPECT TO X AXIS OF PAPER */
/* 			0.0 FOR X-AXIS */
/* 			90.0 FOR Y-AXIS */
/* 	B0  (R)	MINIMUM VALUE ON TICK AXIS */
/* 	C0  (R)	MAXIMUM VALUE ON TICK AXIS */
/* 	D0  (R)	INT(D0) = NUMBER OF MAJOR AXIS TICKS */
/*		INT((INT(D0)-D0)*100) = NUMBER OF MINOR AXIS TICKS BETWEEN MAJOR TICKS*/
/* 		INT(MOD((INT(D0)-D0)*10000,100) = NUMBER OF SUB MINOR AXIS TICKS */
/* 			BETWEEN MINOR TICKS */
/* 	E0  (R)	CHARACTER SIZE OF TITLE AND NUMBER (IF E0=0, DEFAULTS TO 0.15) */
/* 			< 0 THEN DO NOT AUTO SCALE BY (x10 TO POWER) */
/* 	F0  (R)	NUMBER SPECIFICATION (FORMAT FX.Y) */
/* 		 (SEE NUMBER) */
/* 		 -1 WILL AUTOMATICALLY GENERATE A "NICE" FORMAT */
/* 	ICOL (I) OPTIONAL COLOR ARRAY (ACCESSED ONLY IF 100000'S DIGIT <> 0) */
/* 		 ICOL(1) = AXIS LINE AND TICK COLOR */
/* 		 ICOL(2) = NUMERIC LABEL COLOR */
/* 		 ICOL(3) = TITLE COLOR */
/* 		 ICOL(4) = EXPONENT COLOR */
/* 		PEN COLOR ON RETURN WILL DEPEND ON OPTIONS IN THE */
/* 		ORDER LISTED ABOVE */

    /* parameter adjustments */
    --icol;

    /* Function Body */
    tl = .1f;				/* TICK LENGTH */
    x01 = *x0;
    y01 = *y0;
    ang = *a0;				/* ROTATION ANGLE */
    e1 = *e0;				/* CHARACTER SIZE */
    cs = dabs(e1);
    if (cs == 0.f) {
	cs = .15f;
    }
    if (*s0 == 0.f) {			/* ZERO LENGTH AXIS */
	goto L1000;
    }
    x1 = *d0 * 1.000002f;
    njt = dabs(x1);			/* NUMBER OF MAJOR TICKS */
    nnt = (dabs(x1) - njt) * 100.f;	/* NUMBER OF MINOR TICKS */
    nst = ((dabs(x1) - njt) * 100.f - nnt) * 100.f; /* NUMBER OF SUB-MINOR TICKS */
    if (njt < 2) {
	njt = 2;
    }
    xj = dabs(*s0) / (njt - 1);		/* INCREMENT BETWEEN MAJOR TICKS */
    xn = xj;
    if (nnt != 0) {			/* INCREMENT BETWEEN MINOR TICKS */
	xn /= nnt + 1;
    }
    xs = xn / (nst + 1);		/* INCREMENT BETWEEN SUB-MINOR TICKS */
    n1 = *n0 % 100000;
    if (abs(n1) / 1000 != 0) {		/* ROTATION ANGLE */
	hor = 90.f;
    }
    co = cos(ang * .017453294f);	/* AXIS ANGLE ROTATION */
    si = sin(ang * .017453294f);
    hor = ang;				/* ANGLE OF NUMBER LABELS */
    nc = abs(n1) % 100;

/* DECODE NUMBER FORMAT */

/* NUMBER OF CHARACTERS IN TITLE */
    fa = *f0;
    if (fa == -1.f) {			/* INPUT WAS -1.0 */
	fa = 1003.f;			/* DEFAULT AUTO SCALING FORMAT */
	if (e1 < 0.f) {			/* NO AUTO SCALING SO MAKE */
	    ng = 1;			/* FORMAT TO FIT */
	    if (*b0 != 0.f) {		/* Computing MAX */
		r__1 = dabs(*b0);
		i__1 = ng, i__2 = (integer) (r_lg10(&r__1) + .001f);
		ng = max(i__1,i__2);
	    }
	    if (*c0 != 0.f) {		/* Computing MAX */
		r__1 = dabs(*c0);
		i__1 = ng, i__2 = (integer) (r_lg10(&r__1) + .001f);
		ng = max(i__1,i__2);
	    }
	    if (*b0 < 0.f || *c0 < 0.f) {
		++ng;
	    }
	    fa = (real) ng + 1e3f;
	}
    }
    if (dabs(fa) > 1e3f) {		/* INPUT DESIRED IS INTEGER */
	nd = dabs(fa) - 1e3f;		/* INPUT INTEGER VALUE */
	fa = (real) nd * 1.01f + 3.f;	/* DEFAULT FORMAT FOR NOT AUTOSCALE */
	if (e1 < 0.f) {			/* NO AUTO SCALING TO MAKE FORMAT */
	    ng = 2;			/* WHICH FITS */
	    if (*b0 != 0.f) {		/* Computing MAX */
		r__1 = dabs(*b0);
		i__1 = ng, i__2 = (integer) (r_lg10(&r__1) + .001f) + 1;
		ng = max(i__1,i__2);
	    }
	    if (*c0 != 0.f) {		/* Computing MAX */
		r__1 = dabs(*c0);
		i__1 = ng, i__2 = (integer) (r_lg10(&r__1) + .001f) + 1;
		ng = max(i__1,i__2);
	    }
	    if (*b0 < 0.f || *c0 < 0.f) {
		++ng;
	    }
	    fa = (real) ng + (real) nd * 1.01f;
	}
    }
    r__1 = dabs(fa);
    nd = r_mod(&r__1, &c_b94);		/* NUMBER OF DIGITS */
    r__1 = dabs(fa);
    ng = (r_mod(&r__1, &c_b94) - nd + 1e-4f) * 100.f; /* NUMBER OF DIGITS RIGHT OF D.P. */
    if (ng > 17) {			/* CORRECT INPUT SIMPLE ERRORS */
	ng /= 10;
    }
    if (fa < 0.f) {			/* EXPONENTIAL NOTATION */
	nd += -4;
    }
    if (nd <= 0) {
	nd = ng;
    }
    ndd = nd;
    if (fa < 0.f) {			/* EXPONENTIAL NOTATION */
	ndd = nd + 4;
    }
    if (dabs(fa) > 1e3f) {		/* FORMATTED INTEGER */
	ng = -1;
    }

    tl1 = tl;
    if (*s0 < 0.f) {			/* REVERSE SIDE OF TICKS */
	tl1 = -(doublereal)tl;
    }
    if (*s0 < 0.f) {			/* REVERSE SIDE OF TICKS */
	tl = 0.f;
    }
    if (abs(n1) / 1000 != 0) {
	goto L10;
    }
    dnx = -ndd * cs / 2.f;		/* NUMBER LABEL DISTANCE FROM AXIS */
    dny = -(doublereal)tl - space - cs;	/* NUMBER LABEL DISTANCE FROM AXIS */
    dty = dny - cs - space;		/* TITLE DISTANCE FROM AXIS */
    goto L20;
L10:		/* HORIZONTAL NUMBERS ON VERTICAL AXIS */
    dnx = -(doublereal)cs / 2.f;	/* NUMBER LABEL DISTANCE FROM AXIS */
    dny = -(doublereal)tl - space;	/* NUMBER LABEL DISTANCE FROM AXIS */
    dty = dny - ndd * cs - space * 2.f;	/* TITLE DISTANCE FROM AXIS */
    hor = ang - 90.f;
L20:
    if (n1 < 0) {			/* CLOCKWISE TITLES */
	goto L30;
    }
    dny = -(doublereal)dny - cs;	/* COUNTER-CLOCKWISE TITLES */
    dty = -(doublereal)dty - cs;
    tl1 = -(doublereal)tl1;		/* CHANGE SIDES OF TICKS */
    if (abs(n1) < 1000) {
	goto L30;
    }
    dny += cs * ndd;
    dty = dny + space;
L30:
    x1 = 0.f;				/* FIRST MAJOR TICK */
    y1 = 0.f;
    y2 = -(doublereal)tl1;
    if (abs(*n0) >= 100000) {
	r__1 = (real) icol[1];
	plot_(&r__1, &c_b8, &c__0);
    }
    r__1 = co * x1 - si * y1 + x01;
    r__2 = si * x1 + co * y1 + y01;
    plot_(&r__1, &r__2, &c__3);
    r__1 = co * x1 - si * y2 + x01;
    r__2 = si * x1 + co * y2 + y01;
    plot_(&r__1, &r__2, &c__2);
    i__1 = njt - 1;
    for (i = 1; i <= i__1; ++i) {		/* MAJOR TICKS */
	r__1 = co * x1 - si * y1 + x01;
	r__2 = si * x1 + co * y1 + y01;
	plot_(&r__1, &r__2, &c__3);
	x1 = xj * i;
	y2 = -(doublereal)tl1;
	r__1 = co * x1 - si * y1 + x01;
	r__2 = si * x1 + co * y1 + y01;
	plot_(&r__1, &r__2, &c__2);
	r__1 = co * x1 - si * y2 + x01;
	r__2 = si * x1 + co * y2 + y01;
	plot_(&r__1, &r__2, &c__2);
	i__2 = nnt + 1;
	for (j = 1; j <= i__2; ++j) {		/* MINOR TICKS */
	    y2 = -(doublereal)tl1 * .7f;
	    x2 = x1 + xn * j - xj;
	    r__1 = co * x2 - si * y1 + x01;
	    r__2 = si * x2 + co * y1 + y01;
	    plot_(&r__1, &r__2, &c__3);
	    r__1 = co * x2 - si * y2 + x01;
	    r__2 = si * x2 + co * y2 + y01;
	    plot_(&r__1, &r__2, &c__2);
	    y2 = -(doublereal)tl1 * .4f;
	    i__3 = nst;
	    for (k = 1; k <= i__3; ++k) {	/* SUB MINOR TICKS */
		x3 = x2 + xs * k - xn;
		r__1 = co * x3 - si * y1 + x01;
		r__2 = si * x3 + co * y1 + y01;
		plot_(&r__1, &r__2, &c__3);
		r__1 = co * x3 - si * y2 + x01;
		r__2 = si * x3 + co * y2 + y01;
		plot_(&r__1, &r__2, &c__2);
/* L120: */
	    }
/* L110: */
	}
/* L100: */
    }
    if (abs(n1) % 1000 > 100) {			/* NO LABELING */
	goto L1000;
    }
    xs = 0.f;					/* EXPONENT */
    if (e1 < 0.f) {
	goto L140;
    }

/* 	COMPUTE AUTO EXPONENT SCALING SO THAT THE FORMATED LABEL */
/* 	HAS THE INTEGER PORTION FILLED AS MUCH AS POSSIBLE */

/* NO AUTO SCALING */
    i = nd - ng - 1;
    if (*b0 < 0.f || *c0 < 0.f) {
	--i;
    }
    if (*b0 != 0.f) {
	r__1 = dabs(*b0) + 1e-30f;
	x1 = r_lg10(&r__1);
	r__2 = x1 - .001f;
	if (x1 < 0.f && (r__1 = r_int(&r__2) - x1, dabs(r__1)) > .001f) {
	    x1 += -1.f;
	}
	if (x1 >= 0.f) {
	    x1 += 1.f;
	}
	x1 = r_int(&x1);
    } else {
	x1 = 0.f;
    }
    if (*c0 != 0.f) {
	r__1 = dabs(*c0) + 1e-30f;
	y1 = r_lg10(&r__1);
	r__2 = y1 - .001f;
	if (y1 < 0.f && (r__1 = r_int(&r__2) - y1, dabs(r__1)) > .001f) {
	    y1 += -1.f;
	}
	if (y1 >= 0.f) {
	    y1 += 1.f;
	}
	y1 = r_int(&y1);
    } else {
	y1 = 0.f;
    }
    x2 = (x1 < y1 ? x1 : y1);
    x3 = (x1 > y1 ? x1 : y1);
    if (x3 < 0.f) {
	x3 += 1;
    }
    if (x2 < 0.f && (real) ng <= 2 - x2) {
	xs = nd - ng - 1 - x2;
    }
    if ((real) i < x3 + xs) {
	xs = i - x3;
    }
L140:
    y1 = dny;
    y2 = (*c0 - *b0) / (njt - 1);
    if (abs(*n0) >= 100000) {
	r__1 = (real) icol[2];
	plot_(&r__1, &c_b8, &c__0);
    }
    e1 = xs;					/* EXPONENT VALUE */
    i__1 = njt;
    for (i = 1; i <= i__1; ++i) {		/* LABEL MAJOR TICKS */
	x1 = (i - 1) * xj + dnx;
	d__1 = (doublereal) e1;
	c1 = (y2 * (i - 1) + *b0) * pow_dd(&c_b117, &d__1);
	r__1 = co * x1 - si * y1 + x01;
	r__2 = si * x1 + co * y1 + y01;
	number_(&r__1, &r__2, &cs, &c1, &hor, f0, &c_n1);
/* L150: */
    }

/* 	PLOT TITLE */

    if (nc != 0) {
	y1 = 0.f;
	x1 = 0.f;
	symbol_(&x1, &y1, &cs, t, &c_b8, &nc, &c_n3);	/* GET TITLE LENGTH */
	dtx = (dabs(*s0) - x1) / 2.f;			/* CENTER TITLE */
	if (e1 != 0.f) {				/* ADD EXPONENT SPACE */
	    dtx -= cs * 3.f;
	}
	if (abs(*n0) >= 100000) {
	    r__1 = (real) icol[3];
	    plot_(&r__1, &c_b8, &c__0);
	}
	r__1 = co * dtx - si * dty + x01;
	r__2 = si * dtx + co * dty + y01;
	symbol_(&r__1, &r__2, &cs, t, &ang, &nc, &c_n1);
	dtx += x1;
    } else {
	dtx = dabs(*s0) / 2.f;
	if (e1 != 0.f) {			/* ADD EXPONENT SPACE */
	    dtx -= cs * 3.f;
	}
    }
    x1 = dtx + cs / 2.f;
    y1 = dty;
    if (e1 == 0.f) {				/* NO EXPONENT */
	goto L1000;
    }
    if (abs(*n0) >= 100000) {
	r__1 = (real) icol[4];
	plot_(&r__1, &c_b8, &c__0);
    }
    e1 = -(doublereal)e1;
    r__1 = co * x1 - si * y1 + x01;
    r__2 = si * x1 + co * y1 + y01;
    symbol_(&r__1, &r__2, &cs, "(X10", &ang, &c__4, &c_n1);
    x1 += cs * 3.75f;
    y1 += cs * .4f;
    r__1 = co * x1 - si * y1 + x01;
    r__2 = si * x1 + co * y1 + y01;
    number_(&r__1, &r__2, &cs, &e1, &ang, &c_b8, &c_n1);
    r__2 = dabs(e1);
    r__1 = r_lg10(&r__2);
    x2 = r_int(&r__1) + .75f;
    if (e1 < 0.f) {
	x2 += 1.f;
    }
    x1 += x2 * cs;
    y1 -= cs * .4f;
    r__1 = co * x1 - si * y1 + x01;
    r__2 = si * x1 + co * y1 + y01;
    symbol_(&r__1, &r__2, &cs, ")", &ang, &c__1, &c_n1);
L1000:
    return 0;
} /* axis3_ */

