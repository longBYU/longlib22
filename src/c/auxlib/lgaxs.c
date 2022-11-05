
/* *** LAST REVISED ON 24-DEC-1993 07:08:50.89 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]LGAXS.C */

#include "my.h"

/* Table of constant values */
static real c_b6 = (float)0.;
static real c_b4 = (float)1.;

static integer c_n3 = -3;
static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;

/* Subroutine */ int lgaxs_(x0, y0, a0, n0, s0, t0, c0, d0, icol)
real *x0, *y0;
char *a0;
integer *n0;
real *s0, *t0, *c0, *d0;
integer *icol;
{
    /* Initialized data */

    static real cs = (float).15;	/* CHARACTER SIZE */

    /* System generated locals */
    integer i__1;
    real r__1, r__2;

    /* Builtin functions */
    double r_sign(), cos(), sin(), r_lg10(), r_int();

    /* External functions */
    extern /* Subroutine */ int plot_(real *, real *, integer *);
    extern /* Subroutine */ int number_(real *, real *, real *, real *, real *
	    , real *, integer *);
    extern /* Subroutine */ int symbol_();

    /* Local variables */
    static integer i, j;
    static logical color;
    static real b3, b4, c1, b6, b7, b8, b1;
    static integer n1, n2;
    static real t1, t2, t3, t5, t4, t6, s5, s6, x1, y1, x2, y2, aj, at;
    static logical labels;
    static real xl;
    static real ht3, ht4, hor;

/* 	THIS ROUTINE PLOTS A LOG AXIS WITH EXPONENT LABELING */
/* 	MODIFIED FROM AXIS D.LONG 22-OCT-83	AT JPL */

/* 	X0	X COORDINATE OF START OF AXIS */
/* 	Y0	Y COORDINATE OF START OF AXIS */
/* 	A0	CHARACTER STRING TO DESCRIBE AXIS */
/* 	N0	NUMBER OF CHARACTERS IN STRING */
/* 		- ON CLOCKWISE SIDE OF AXIS (NORMAL FOR X) */
/* 		+ ON COUNTER CLOCKWISE SIDE OF AXIS (NORMAL FOR Y) */
/* 		HUNDREDS DIGIT	   = 1 TICKS AND LINE ONLY--NO LABELING */
/* 		THOUSANDS DIGIT    = 1 HORIZONTAL NUMBERS IN Y AXIS LABEL */
/* 		100 THOUSANDS DIGIT = 1 USE COLOR ARRAY */
/* 	S0	LENGTH OF AXIS */
/* 		< 0	TICKS ON OPPOSITE SIDE OF AXIS FROM LABEL */
/* 		= 0	NO ACTION (DUMMY CALL) */
/* 		> 0	TICKS ON SAME SIDE AS AXIS LABEL (NORMAL) */
/* 	T0	ANGLE OF AXIS TO X AXIS OF PAPER */
/* 		0.0 FOR X-AXIS */
/* 		90.0 FOR Y-AXIS */
/* 	C0	COORDINATE OF MINIMUM TICK ON AXIS */
/* 	D0	SCALING FACTOR EXPONENT OF THE FORM (NMAX-NMIN)/LENGTH */
/* 	ICOL	COLOR ARRAY (NEEDED ONLY IF MAG(NO)>=10000) */
/* 		ICOL(1) AXIS COLOR */
/* 		ICOL(2) NUMBERS COLOR */
/* 		ICOL(3) TITLE COLOR (RETURN) */

    /* Parameter adjustments */
    --icol;

    /* Function Body */
    n1 = abs(*n0);
    labels = TRUE_;
    hor = *t0;
    if (*s0 == (float)0.) {
	return 0;
    }
    t5 = (float).1;			/* TICK LENGTH */
    b7 = t5 + (float).08;		/* NUMBER DISTANCE FROM AXIS */
    b6 = b7;
    b8 = (float)0.;
    if (*n0 < 0) {
	goto L10;
    }
    b3 = cs * (float)4.;
    b4 = cs + (float).08;
    t2 = *t0;
    goto L20;
L10:
    b3 = -(doublereal)cs * (float)4.;
    b4 = -(doublereal)t5 - cs - (float).05;
    t2 = *t0;
    t5 = -(doublereal)t5;
L20:
    color = FALSE_;
    if (n1 >= 100000) {
	n1 %= 100000;
	color = TRUE_;
    }
    if (n1 >= 10000) {
	n1 %= 10000;
    }
    if (n1 >= 1000) {
	n1 %= 1000;
	hor = (float)0.;
	r__1 = (real) (*n0);
	b4 = (dabs(t5) + (float).05) * r_sign(&c_b4, &r__1);
	if (*n0 > 0) {
	    b4 += cs * (float)3.5;
	}
	b6 = cs * (float).5;
	r__1 = (real) (*n0);
	b8 = (cs * (float).5 + dabs(t5)) * r_sign(&c_b4, &r__1);
	if (*n0 < 0) {
	    b8 -= cs * (float)1.6;
	}
    }
    if (n1 >= 100) {
	n1 %= 100;
	labels = FALSE_;
    }
    n2 = (r__1 = *s0 * *d0, dabs(r__1)) + (float).5;	/* NUMBER OF TICKS */
    xl = dabs(*s0) / (real) n2;		/* DISTANCE BETWEEN TICKS */
    t1 = *t0 * (float).017453294;
    t3 = cos(t1);
    t4 = sin(t1);
    ht3 = cos(hor * (float).017453294);
    ht4 = sin(hor * (float).017453294);
    t6 = t5 * t3;
    t5 *= t4;

    if (color) {			/* COLOR */
	r__1 = (real) icol[1];
	plot_(&r__1, &c_b6, &c__0);
    }
    s5 = r_sign(&c_b4, s0) * t5;
    s6 = r_sign(&c_b4, s0) * t6;
    x1 = *x0;
    y1 = *y0;
    plot_(&x1, &y1, &c__3);
    i__1 = n2;
    for (i = 1; i <= i__1; ++i) {	/* PLOT MAJOR TICKS */
	for (j = 2; j <= 10; ++j) {	/* PLOT MINOR TICKS */
	    at = (float).6;
	    if (j == 2) {
		at = (float)1.;
	    }
	    x2 = x1 - s5 * at;
	    y2 = y1 + s6 * at;
	    plot_(&x2, &y2, &c__3);
	    plot_(&x1, &y1, &c__2);
	    r__1 = (real) j;
	    r__2 = (real) (j - 1);
	    aj = r_lg10(&r__1) - r_lg10(&r__2);
	    x1 += t3 * xl * aj;
	    y1 += t4 * xl * aj;
	    if (*t0 == (float)90.) {
		x1 = *x0;
	    }
	    plot_(&x1, &y1, &c__2);
	}
    }
    x2 = x1 - s5;
    y2 = y1 + s6;
    plot_(&x2, &y2, &c__2);

    if (color) {			/* COLOR */
	r__1 = (real) icol[3];
	plot_(&r__1, &c_b6, &c__0);
    }
    if (! labels) {
	return 0;
    }
    c1 = r_int(c0);
    x2 = *x0 - b4 * t4 - b7 * t3;	/* LOCATE CENTER NUMBER LABELS */
    y2 = *y0 + b4 * t3 - b6 * t4;
    ++n2;
    if (color) {	/* COLOR */
	r__1 = (real) icol[2];
	plot_(&r__1, &c_b6, &c__0);
    }
    i__1 = n2;
    for (i = 1; i <= i__1; ++i) {
	symbol_(&x2, &y2, &cs, "10", &hor, &c__2, &c_n1, 2L);
	x1 = x2 - cs * (float).6 * ht4 + cs * (float)2. * ht3;
	y1 = y2 + cs * (float).6 * ht3 + cs * (float)2. * ht4;
	if (c1 == (float)0.) {
	    r__1 = cs * (float).8;
	    symbol_(&x1, &y1, &r__1, "0", &hor, &c__1, &c_n1, 1L);
	} else {
	    r__1 = cs * (float).8;
	    number_(&x1, &y1, &r__1, &c1, &hor, &c_b6, &c_n1);
	}
	c1 += r_sign(&c_b4, d0);
	x2 += t3 * xl;
	y2 += t4 * xl;
    }
    if (n1 < 1) {
	goto L155;
    }
    x1 = (float)0.;
    y1 = (float)0.;
    symbol_(&x1, &y1, &cs, a0, &t2, &n1, &c_n3);	/* GET TITLE LENGTH */
    b1 = (dabs(*s0) - x1) * (float).5;
    x2 = *x0 + b1 * t3 - b3 * t4 - b8 * t4;
    y2 = *y0 + b1 * t4 + b3 * t3;
    if (color) {	/* COLOR */
	r__1 = (real) icol[3];
	plot_(&r__1, &c_b6, &c__0);
    }
    symbol_(&x2, &y2, &cs, a0, &t2, &n1, &c_n1);
L155:
    return 0;
} /* lgaxs_ */

