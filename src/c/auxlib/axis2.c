
/* *** LAST REVISED ON 21-JAN-1994 15:09:36.48 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]AXIS2.C */

#include "my.h"

/* Table of constant values */

static real c_b8 = (float)0.;
static integer c_n3 = -3;
static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__4 = 4;

/* Subroutine */ int axis2_(real *x0, real *y0, char *a0, integer *n0, real *
	s0, real *t0, real *c0, real *d0, integer *nm, integer *nn, integer *
	ml, real *ts, integer *nd, real *sm, integer *icol)
{
    /* System generated locals */
    integer i__1, i__2;
    real r__1, r__2;

    /* Builtin functions */
    double cos(doublereal), sin(doublereal), r_lg10(
	    real *), r_int(real *);

    /* External functions */
    extern /* Subroutine */ int plot_(real *, real *, integer *);
    extern /* Subroutine */ int number_(real *, real *, real *, real *, real *
	    , real *, integer *);
    extern /* Subroutine */ int symbol_(real *, real *, real *, char *, real *
	    , integer *, integer *);

    /* Local variables */
    static integer nddd;
    static logical vert;
    static integer i, k;
    static logical scale, ticks, color;
    static real b3, b4, d1, b6, b7, b8, c1, e1, c2;
    static integer n1, n2;
    static real b1, b2, s1, t2, t1, t5, t3, t4, t6, x1, y1, x2, y2, x3, y3;
    static integer ic;
    static real cs, xl, xm;
    static integer ic2, nc1;
    static integer nm1, ndd;
    static real hor, hmt;

/* 	WRITTEN BY D.LONG   17-OCT-1983		AT JPL */
/* 	REVISED 13-AUG-1987 DGL */
/* 	+ IMPROVED APPEARANCE OF EXPONENT, ADDED EXPONENT COLOR */

/* 	THIS VERSION OF AXIS INCLUDES MINOR TICKS ON AXIS AND A MORE */
/* 	FLEXIBLE METHOD OF SPECIFYING AXIS PARAMETERS. */

/* 	X0  (R)	X COORDINATE OF START OF AXIS */
/* 	Y0  (R)	Y COORDINATE OF START OF AXIS */
/* 	A0  (C)	CHARACTER STRING TO DESCRIBE AXIS */
/* 	N0  (I)	NUMBER OF CHARACTERS IN STRING */
/* 		- ON CLOCKWISE SIDE OF AXIS (NORMAL FOR X) */
/* 		+ ON COUNTER CLOCKWISE SIDE OF AXIS (NORMAL FOR Y) */
/* 		HUNDREDS DIGIT	= 1 NO LABELING OF AXIS--TICKS AND LINE ONLY */
/* 		THOUSANDS DIGIT = 1 HORIZONTAL NUMBERS IN Y AXIS LABEL */
/* 		10 THOUSANDS DIGIT=1 USE NM,ML,ETC. PARAMETERS */
/* 		100 THOURSANDS DIGIT=1 USE COLOR PARAMTERS */
/* 	S0  (R)	LENGTH OF AXIS */
/* 		< 0	TICKS PLACED ON OPPOSITE SIDE OF AXIS LABEL */
/* 		= 0	NO ACTION */
/* 		> 0	NORMAL */
/* 	T0  (R)	ANGLE OF AXIS TO X AXIS OF PAPER */
/* 		0.0 FOR X-AXIS */
/* 		90.0 FOR Y-AXIS */
/* 	C0  (R)	COORDINATE OF MINIMUM TICK ON AXIS */
/* 	D0  (R)	SCALING DISTANCE BETWEEN  1" TICKS */
/* 		NOTE:  THE FOLLOWING ARE ACCESSED ONLY IF ABS(NO)>10000 */
/* 	NM  (I)	NUMBER OF MINOR AXIS TICKS BETWEEN MAJOR TICKS (DEFAULT=0) */
/* 	NN  (I)	NNth MINOR TICK FROM MAJOR IS HIGHLIGHTED */
/* 		(DEFAULT=0 INDICATES NO MINOR TICKS HIGHLIGHTED) */
/* 	ML  (I)	NUMBER OF MAJOR AXIS TICKS (DEFAULT= 1 TICK/INCH) */
/* 		< 0 THEN USE FOLLOWING VARABLES */
/* 	TS  (R)	CHARACTER SIZE OF TITLE AND NUMBER (DEFAULT=.15) */
/* 		< 0 THEN DO NOT AUTO SCALE BY (x10 TO POWER) */
/* 	ND  (I)	NUMBER OF DIGITS TO RIGHT OF DECIMAL POINTS (DEFAULT=1) */
/* 	SM  (R)	MAJOR TICK LENGTH (DEFAULT= .1) (MINOR TICK=1/2 MAJOR TICK) */

/* 	ICOL (I) COLOR ARRAY (ACCESSED ONLY IF ABS(NO)>100000 */
/* 		 ICOL(1) AXIS COLOR */
/* 		 ICOL(2) NUMBER COLOR */
/* 		 ICOL(3) LABEL COLOR */
/* 		 ICOL(4) EXPONENT COLOR */
/* 		PEN COLOR ON RETURN DEPENDS ON LAST ITEM PLOTTED */
/* 		IN THE SEQUENCE INDICATED */

    /* parameter adjustments */
    --icol;

    /* Function Body */
    cs = .15f;				/* CHARACTER SIZE */
    if (*s0 == 0.f) {			/* ZERO LENGTH AXIS */
	goto L200;
    }
    vert = FALSE_;			/* NO VERTICAL NUMBERS ON HORIZONTAL AXIS */
    ticks = TRUE_;			/* PUT ON TICKS */
    scale = TRUE_;			/* (x10 TO POWER SCALING) */
    hor = *t0;
    ndd = 1;				/* NUMBER OF DIGITS TO RIGHT OF DECIMAL */
    t5 = .1f;				/* TICK LENGTH */
    b7 = t5 + .08f;			/* NUMBER DISTANCE FROM AXIS */
    b6 = b7;
    b8 = 0.f;
    nm1 = 0;				/* NUMBER MINOR TICKS */
    n2 = dabs(*s0) + .5f;		/* NUMBER OF MAJOR TICKS */
    s1 = (real) n2;
    xl = 1.f;				/* INCREMENT BETWEEN MAJOR TICKS */
    n1 = abs(*n0);
    color = FALSE_;
    if (n1 > 100000) {			/* USE COLOR ARRAY */
	n1 %= 100000;
	color = TRUE_;
    }
    if (n1 > 10000) {
	n1 %= 10000;
	n2 = abs(*ml);			/* NUMBER MAJOR TICKS */
	s1 = dabs(*s0);
	if (n2 == 0) {
	    n2 = 1;
	}
	xl = dabs(*s0) / (real) n2;	/* SPACING MAJOR TICKS */
	nm1 = abs(*nm) + 1;		/* NUMBER MINOR TICKS */
	xm = xl / (real) nm1;		/* SPACING MINOR TICKS */
	if (*ml < 0) {
	    cs = dabs(*ts);		/* DIFFERENT TITLE SIZE */
	    if (cs == 0.f) {
		cs = .15f;
	    }
	    ndd = abs(*nd);
	    if (*ts < 0.f) {
		scale = FALSE_;
	    }					/* DO NOT SCALE */
	    t5 = dabs(*sm);			/* NEW TICK LENGTH */
	    if (t5 == 0.f) {
		t5 = .1f;
	    }
	}
    }
    if (n1 > 1000) {
	n1 %= 1000;		/* VERTICAL NUMBERS ON HORIZONTAL AXIS */
	vert = TRUE_;
	hor = 0.f;
	r__1 = (real) (*n0);
	b4 = (dabs(t5) * ((*s0 >= 0.0 ? 1.0 : -1.0) + 1.f) / 2.f + .1f) * 
		(r__1 >= 0 ? 1.0 : -1.0);
	b6 = cs * .49f;
    }
    if (n1 > 100) {			/* NO TICKS */
	n1 %= 100;
	ticks = FALSE_;
    }
    if (*n0 < 0) {
	goto L10;
    }
    b3 = cs * (ndd + 2.8f);		/* COUNTER-CLOCKWISE LABELING */
    b4 = cs + t5;
    t2 = *t0;
    goto L20;
L10:
    b3 = -(doublereal)cs * (ndd + 3.f);	/* CLOCKWISE LABELING */
    b4 = -(doublereal)t5 - cs;
    t2 = *t0;
    t5 = -(doublereal)t5;
L20:
    t5 *= (*s0 >= 0 ? 1.0 : -1.0);
    t1 = *t0 * .017453294f;
    t3 = cos(t1);
    t4 = sin(t1);

    t6 = t5 * t3;
    t5 *= t4;
    x1 = *x0;
    y1 = *y0;
    if (color) {				/* COLOR */
	r__1 = (real) icol[1];
	plot_(&r__1, &c_b8, &c__0);
    }
    i__1 = n2;
    for (i = 1; i <= i__1; ++i) {		/* MAJOR TICKS */
	if (nm1 == 0) {
	    goto L106;
	}
	i__2 = nm1;
	for (k = 1; k <= i__2; ++k) {		/* DO MINOR TICKS */
	    x2 = x1 + t3 * (real) (k - 1) * xm;
	    y2 = y1 + t4 * (real) (k - 1) * xm;
	    if (k - 1 == *nn && *nn != 0) {
		hmt = .8f;
	    } else {
		hmt = .5f;
	    }
	    x3 = x2 - t5 * hmt;
	    y3 = y2 + t6 * hmt;
	    plot_(&x2, &y2, &c__3);
/* L105: */
	    plot_(&x3, &y3, &c__2);
	}
L106:
	x2 = x1 - t5;
	y2 = y1 + t6;
	plot_(&x2, &y2, &c__3);
	plot_(&x1, &y1, &c__2);
	x1 += t3 * xl;
	y1 += t4 * xl;
	if (*t0 == 90.f) {
	    x1 = *x0;
	}
/* L100: */
	plot_(&x1, &y1, &c__2);
    }
    x2 = x1 - t5;
    y2 = y1 + t6;
    plot_(&x2, &y2, &c__2);		/* FINISH LAST MAJOR TICK */
/* 	CHECK FOR EXPONENT VALUE */
    d1 = *d0;				/* SCALING FACTOR */
    c1 = *c0 + d1 * s1;			/* STARTING VALUE */
    e1 = 0.f;				/* EXPONENT */
    if (! scale) {
	goto L140;
    }
    if (d1 == 0.f) {
	goto L140;
    }
L110:
    if (dabs(d1) < 10.f) {
	goto L130;
    }
    d1 *= .1f;
    c1 *= .1f;
    e1 += 1.f;
    goto L110;
L120:
    d1 *= 10.f;
    c1 *= 10.f;
    e1 += -1.f;
L130:
    if (dabs(d1) < .5f) {
	goto L120;
    }
L140:					/* PEN AT END OF AXIS */
    if (! ticks) {			/* COLOR */
	if (color) {
	    r__1 = (real) icol[3];
	    plot_(&r__1, &c_b8, &c__0);
	}
	goto L200;
    }
    if (vert) {
	c2 = c1 - n2 * d1;		/* MAKE SPACE FOR VERTICAL NUMBERS */
	ic = 1;				/* ON HORIZONTAL AXIS */
	if (dabs(c2) >= 1.f) {
	    r__1 = dabs(c2);
	    ic = (integer) r_lg10(&r__1);
	}
	ic2 = 1;
	if (dabs(c1) >= 1.f) {
	    r__1 = dabs(c1);
	    ic2 = (integer) r_lg10(&r__1);
	}
	nc1 = max(ic,ic2) + 2;
	if (c2 < 0.f || *c0 < 0.f) {
	    ++nc1;
	}
	if ((real) (*n0) > 0.f) {
	    b4 += (real) (nc1 + ndd) * cs;
	}
	b3 = 0.f;
	r__1 = (real) (*n0);
	b8 = (dabs(t5) * ((*s0 >= 0.0 ? 1.0 : -1.0) + 1.f) / 2.f + .25f + 
		(real) (nc1 + ndd) * cs) * (r__1 >= 0.0 ? 1.0 : -1.0);
    }
    x2 = x1 - b4 * t4 - b7 * t3;	/* LOCATE CENTER NUMBER LABELS */
    y2 = y1 + b4 * t3 - b6 * t4;
    ++n2;
    if (color) {			/* COLOR */
	r__1 = (real) icol[2];
	plot_(&r__1, &c_b8, &c__0);
    }
    nddd = ndd;
    if (ndd == 0) {
	nddd = -1;
    }
    i__1 = n2;
    for (i = 1; i <= i__1; ++i) {	/* LABEL MAJOR TICKS */
	r__1 = (real) nddd / 100.f;
	number_(&x2, &y2, &cs, &c1, &hor, &r__1, &c_n1);
	c1 -= d1 * s1 / (real) (n2 - 1);
	x2 -= t3 * xl;
	y2 -= t4 * xl;
/* L150: */
    }
    if (n1 != 0) {
	c2 = 0.f;
	y2 = 0.f;
	symbol_(&c2, &y2, &cs, a0, &c_b8, &n1, &c_n3);
	b1 = (dabs(*s0) - c2) * .5f;		/* CENTER TITLE */
	if (e1 != 0.f) {			/* PUT ON EXPONENT SPACE */
	    b1 -= cs * 3.f;
	}
	x2 = *x0 + b1 * t3 - b3 * t4 - b8 * t4;
	y2 = *y0 + b1 * t4 + b3 * t3;
	if (color) {				/* COLOR */
	    r__1 = (real) icol[3];
	    plot_(&r__1, &c_b8, &c__0);
	}
	symbol_(&x2, &y2, &cs, a0, &t2, &n1, &c_n1);
    } else {
	c2 = 0.f;
	b1 = dabs(*s0) * .5f;
	x2 = *x0 + b1 * t3 - b3 * t4 - b8 * t4;
	y2 = *y0 + b1 * t4 + b3 * t3;
    }
    if (e1 == 0.f) {			/* NO EXPONENT */
	goto L200;
    }
    if (color) {			/* COLOR */
	r__1 = (real) icol[4];
	plot_(&r__1, &c_b8, &c__0);
    }
    c2 += cs;
    x2 += c2 * t3;
    y2 += c2 * t4;
    symbol_(&x2, &y2, &cs, "(X10", &t2, &c__4, &c_n1);
    x2 = x2 + cs * 3.75f * t3 - cs * t4 * .4f;
    y2 = y2 + cs * 3.75f * t4 + cs * t3 * .4f;
    number_(&x2, &y2, &cs, &e1, &t2, &c_b8, &c_n1);
    r__2 = dabs(e1);
    r__1 = r_lg10(&r__2);
    b2 = r_int(&r__1) + .8f;
    if (e1 < 0.f) {
	b2 += 1;
    }
    x2 = x2 + b2 * cs * t3 + cs * t4 * .4f;
    y2 = y2 + b2 * cs * t4 - cs * t3 * .4f;
    symbol_(&x2, &y2, &cs, ")", &t2, &c__1, &c_n1);
L200:
    return 0;
} /* axis2_ */
