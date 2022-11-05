
/* *** LAST REVISED ON 24-DEC-1993 07:32:55.04 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]NUMBER.C */

#include "my.h"

/* Table of constant values */

static real c_b94 = (float)1e3;

/* Subroutine */ int number_(real *x, real *y, real *hght, real *z, real *t, 
	real *f0, integer *ipf)
{
    /* System generated locals */
    integer i__2;
    real r__1;
    char ch__1[26];

    /* Builtin functions */
    double r_mod(real *, real *), r_lg10(real *);

    /* External functions */
    extern /* Subroutine */ int symbol_(real *, real *, real *, char *, real *
	    , integer *, integer *);

    /* Local variables */
    static char b[18];
    static real f;
    static integer i;
    static real t1, fa;
    static real hg;
    static integer nd, nn;
    static real alg;
    static integer iff;

/* 	WRITTEN BY D. LONG    AUG, 1983 AT JPL */
/* 	REVISED:	JUNE 1990 */

/* 	PLOTS THE FLOATING POINT NUMBER Z (CAN PLOT AS AN INTEGER) */

/* 	X,Y	(R) COORDINATES OF STRING */
/* 		    (999.,999.) CONTINUE FROM LAST POINT */
/* 	HGHT	(R) HEIGHT OF THE PLOTTED NUMBER */
/* 	Z	(R) FLOATING POINT NUMBER TO BE PLOTTED */
/* 	T	(R) ORIENTATION ANGLE */
/* 	F0	(R) PLOTTING FORMAT (Fn.j) */
/* 		  n = TOTAL NUMBER OF SPACES TO USE (INCLUDING SIGN AND D.P.) */
/* 			[MAX 18 CHARACTERS WIDE] */
/* 		  j = DIGITS TO RIGHT OF DECIMAL POINT (TWO DIGITS EXPECTED) */
/* 			(F4.2 SHOULD BE WRITTEN F4.02) */
/* 		  IF F0 < 0 USE EXPONENTIAL NOTATION (I.E., En,j) */
/* 		  F0 = 1 PLOT IN FLOATING POINT FREE FORMAT */
/* 		  F0 = 0 PLOT INTEGER PORTION WITH NO D.P. (FREE FORMAT) */
/* 		  F0 =-1 PLOT IN EXPONENTIAL FREE FORMAT */
/* 			 NOTE: FREE FORMATS HAVE LEADING SPACES SUPPRESSED */
/* 		  F0 > 1000 PLOT INTEGER PORTION IN FIXED FORMAT WITH */
/* 			n DIGITS AND WITHOUT D.P. */
/* 		  IF n=0 THEN PLOT INTEGER PORTION, DECIMAL POINT, AND */
/* 			 j DIGITS TO RIGHT OF DECIMAL POINT */
/* 		  WHEN Z OVERFLOWS THIS FORMAT, SPACE IS FILLED WITH ASTERICKS */
/* 	IPF	(I) NUMBER CENTERING FLAG (SEE SYMBOL) */
/* 		=-3 X,Y ARE LOWER LEFT CORNER, END OF STRING RETURNED IN X,Y */
/* 			BUT NUMBER IS NOT PLOTTED */
/* 		=-2 X,Y ARE LOWER LEFT CORNER, END OF STRING RETURNED IN X,Y */
/* 		=-1 X,Y ARE LOWER LEFT CORNER */
/* 		= 0 X,Y ARE STRING CENTER */
/* 		=+1 X,Y ARE LOWER RIGHT CORNER */
/* 		=+2 NO PLOT OUTPUT */


/* WORKING BUFFERS */
    iff = 0;
    hg = *hght;
    if (hg == 0.f) {
	hg = .15f;
    }
    t1 = *t;
    nd = 0;
    nn = 0;
    fa = *f0;
    if (dabs(fa) > 1022.f) {
	fa = 0.f;
    }
    if (fa == 0.f) {
	goto L10;
    }
/* INTEGER FORMAT */
    if (fa > 999.f) {			/* PLOT FORMATTED INTEGER */
	nn = r_mod(&fa, &c_b94);
	fa = 0.f;
    } else {				/* PLOT FLOAT OR EXPON NUMBER */
	f = dabs(fa) * 1.000002f;
	nn = f;
	f = (f - nn) * 100.f;
	nd = f;
    }
L10:
    if (nd > 17) {			/* CORRECT SIMPLE INPUT ERRORS */
	nd /= 10;
    }
    if (nn == 0) {			/* DIGITS TO LEFT OF DECIMAL POINT */
	nn = nd + 2;
	if (*z == 0.f && fa == 0.f) {
	    nn = 1;
	}
	if (*z != 0.f) {
	    r__1 = dabs(*z);
	    alg = r_lg10(&r__1);
	    if (alg < 0.f) {
		alg = 0.f;
	    }
	    nn = nd + 2 + alg;
	    if (fa == 0.f) {
		nn = alg + 1;
	    }
	}
	if (*z < 0.f) {
	    ++nn;
	}
	if (fa < 0.f) {
	    nn += 4;
	}
    }
    if (nd > nn) {			/* FORMAT ERROR */
	goto L90;
    }
    if (nn > 18) {			/* MAX CHARACTERS */
	nn = 18;
    }
    if (fa == 0.f) {			/* INTEGER */
	i = *z;
	if (nn / 10 > 0) {
	    i__2 = sprintf(ch__1, "%%%2dd", nn);
	} else {
	    i__2 = sprintf(ch__1, "%%%1dd", nn);
	}
/*	if (i__2 != 0) {
	    goto L90;
	} */
	i__2 = sprintf(b, ch__1, i);
/*	if (i__2 != 0) {
	    goto L90;
	} */
    } else {				/* FLOATING POINT OR EXPONENTIAL */
	if (nn > 1) {
	    if (nd/10 > 0) {
		i__2 = sprintf(ch__1, "%%%2d.%2df", nn,nd);
	    } else {
		if (nn/10 > 0) {
			i__2 = sprintf(ch__1, "%%%2d.%1df", nn,nd);
		} else {
			i__2 = sprintf(ch__1, "%%%1d.%1df", nn,nd);
		}
	    }
	} else {
	    i__2 = sprintf(ch__1, "%%f");
	}
/*	if (i__2 != 0) {
	    goto L90;
	} */
	i__2 = sprintf(b, ch__1, *z);
/*	if (i__2 != 0) {
	    goto L90;
	} */
	if (iff == 1) {			/* REMOVE LEADING SPACES */
	    for (i = 1; i <= 18; ++i) {
		if (*b == ' ') {
		    for (i__2 = i; i__2 < 18; ++i__2)
			b[i__2] = b[i__2+1];
		}
	    }
	    b[17] = 0;
	}
    }
L50:
    symbol_(x, y, &hg, b, &t1, &nn, ipf);
    return 0;
L90:
    for (i = 1; i <= 18; ++i) {
	b[i - 1] = '*';
	if (i == nn - nd) {
	    b[i - 1] = '.';
	}
    }
    goto L50;
} /* number_ */

