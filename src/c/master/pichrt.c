
/* *** LAST REVISED ON 25-DEC-1993 17:35:38.40 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]PICHRT.C */

#include "my.h"

/* Table of constant values */

static integer c__3 = 3;
static real c_b3 = (float)1.5;
static real c_b4 = (float)1.;
static integer c_n1 = -1;
static real c_b10 = (float)0.;
static integer c__0 = 0;
static real c_b12 = (float).1;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__4 = 4;
static integer c_n3 = -3;

/* Subroutine */ int pichrt_(x0, y0, rad, d, iflag, ast, n, vals, ish, iwt, 
	labels, nch, cs, aleg, t, nt, tcs, dis, abc, icol)
real *x0, *y0, *rad, *d;
integer *iflag;
real *ast;
integer *n;
real *vals;
integer *ish, *iwt;
char *labels[];
integer *nch;
real *cs, *aleg;
char *t;
integer *nt;
real *tcs, *dis, *abc;
integer *icol;
{
    /* Initialized data */

    static real dtr = (float).0174533;
    static logical repeat = FALSE_;

    /* System generated locals */
    integer i__1, i__2;
    real r__1;

    /* Builtin functions */
    double cos(), sin();

    /* Local variables */
    extern /* Subroutine */ int plot_();
    static integer i;
    static real r;
    extern /* Subroutine */ int shade_();
    static real w[1000], scale;
    extern /* Subroutine */ int frame_(), cterm_();
    static real x1, y1, an;
    static integer jf, il;
    extern /* Subroutine */ int cshade_(), newpen_(), plotnd_(), symbol_();
    static real ang;
    static integer ilu;
    static real ang1;

/* 	ROUTINE TO PLOT A PIE CHART WITH SHADED WEDGES, DESCRIPTIVE */
/* 	LEGENDS AND EXPLODED SLICES. */

/* 	WRITTEN:  DGL  AUG 1987 */

/* 	X0,Y0	(R) CENTER OF PIE CHART */
/* 	RAD	(R) RADIUS OF PIE CHART (RAD>0) */
/* 	D	(R) EXPLODE DISTANCE (D>0) */
/* 	IFLAG	(R) PLOTTING FLAG */
/* 			< 0 DON'T CLOSE PLOT PACKAGE */
/* 			> 0 CLOSE PLOT PACKAGE */
/* 		MAG	> 10000 INIT PLOT PACKAGE */
/* 	(ONE'S DIGIT)   = 1 DON'T USE COLORS */
/* 		        = 2 USE COLORS */
/* 	(HUNDRED'S)	= SCREEN GRAPHICS DEVICE (SEE FRAME) */
/* 	AST	(R) STARTING ANGLE */
/* 	N	(I) NUMBER OF WEDGES */
/* 	VALS	(R) ANGULAR PERCENT OF PIE CHART FOR EACH WEDGE */
/* 		     DIMENSIONED VALS(N), WEDGES INCREMENT CCW */
/* 		     IF VALS(I)<0 THEN WEDGE IS EXPLODED OUT FROM CENTER */
/* 		     D DISTANCE */
/* 	ISH	(R) SHADE OPTION FOR EACH WEDGE DIMENSIONED ISH(N) */
/* 			VALUE OF ISH   SHADE PATTERN */
/* 			    0		 NO SHADING (OUTLINE ONLY) */
/* 			    1		 -45 DEG SOLID LINES */
/* 			    2		 HORIZONTAL SOLID LINES */
/* 			    3		 +45 DEG SOLID LINES */
/* 			    4		 VERTICAL SOLID LINES */
/* 			    5		 -45 DEG DOTTED LINES */
/* 			    6		 HORIZONTAL DOTTED LINES */
/* 			    7		 +45 DEG DOTTED LINES */
/* 			    8		 VERTICAL DOTTED LINES */
/* 			    9		 +/- 45 DEG DOTTED LINES */
/* 			   10		 HORIZONTAL/VERTICAL DOTTED LINES */
/* 			   11		 +/- 45 DEG SOLID LINES */
/* 			   12		 HORIZONTAL/VERTICAL SOLID LINES */
/* 	IWT	(I) PEN WIDTH FOR WEDGE OUTLINES (SEE NEW PEN) */
/* 	LABELS	(C) LABELS FOR WEDGES DIMENSIONED LABELS(N) */
/* 	NCH	(I) MAXIMUM NUMBER OF CHARACTERS IN LABELS */
/* 	ALEG	(R) SIZE OF LEGEND BOX */
/* 		    < 0 LEGENDS LOCATED BELOW PIE CHART */
/* 		    = 0 NO LEGEND (LABELS IGNORED) */
/* 		    > 0 LEGENDS LOCATED AROUND PIE CHART */
/* 	(MAG)	    > 98 LEGEND WITH NO BOXED AREA */
/* 	CS	(R) LEGEND CHARACTER SIZE */
/* 	T	(C) TITLE */
/* 	NT	(I) CHARACTERS IN TITLE */
/* 	TCS	(R) TITLE SIZE */
/* 		    IF TCS <0 THEN INPUT POSITIONS IN ABC USED */
/* 	ABC	(R) LOCATION OF LOWER-LEFT CORNER OF EACH LEGEND */
/* 		    LINE (USED IF TCS<0) */
/* 			ABC(1)=X POSITION LEGEND LABEL 1 */
/* 			ABC(2)=Y POSITION LEGEND LABEL 1 */
/* 			ABC(3)=X POSITION LEGEND LABEL 2 */
/* 			ABC(4)=Y POSITION LEGEND LABEL 2 */
/* 			 ... */
/* 	DIS	(R) SHADING LINE DISTANCE */
/* 	ICOL	(I) COLOR ARRAY */
/* 		    ICOL(1) = TITLE COLOR (RETURN) */
/* 		    ICOL(2) = LEGEND LABEL COLOR */
/* 		    ICOL(3) = COLOR OF WEDGE 1 */
/* 		     ...          ...        2 */

    /* Parameter adjustments */
    --icol;
    --abc;
    --iwt;
    --ish;
    --vals;

    /* Function Body */

/* 	INTIALIZE ROUTINE AND PLOT PACKAGE IF REQUIRED */

    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();
	}		/* CLOSE PLOTTER */
	repeat = FALSE_;
	return 0;
    }

/* 	INTIALIZE PLOT PACKAGE */

    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = jf / 100;			/* GRAPHICS DEVICE CODE */
	frame_(&c__3, &ilu, &c_b3, &c_b4, &c_b4);/* INTIALIZE */
    } else {
	cterm_(&c_n1);		/* PUT TERMINAL IN PLOT MODE */
    }
    jf = *iflag % 10;

/* 	MUST HAVE POSITIVE RADIUS */

/* COLOR FLAG */
    if (*rad <= (float)0. || *n < 1) {
	goto L200;
    }
    scale = (float)0.;
    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
	scale += (r__1 = vals[i], dabs(r__1));
/* L10: */
    }
    if (scale == (float)0.) {
	goto L200;
    }
    scale = (float)360. / scale;

    ang = *ast;
    i__1 = *n;
    for (i = 1; i <= i__1; ++i) {
	if (vals[i] == (float)0.) {
	    goto L100;
	}
	ang1 = ang + (r__1 = vals[i], dabs(r__1)) * scale;
	x1 = *x0;
	y1 = *y0;
	if (vals[i] < (float)0.) {
	    x1 = *x0 + cos((ang + ang1) * dtr / (float)2.) * *d;
	    y1 = *y0 + sin((ang + ang1) * dtr / (float)2.) * *d;
	}
	if (jf == 2) {
	    r__1 = (real) icol[i + 2];
	    plot_(&r__1, &c_b10, &c__0);
	}

/* 	DO OUTLINE */

	an = (float)0.;
	il = 0;
	i__2 = iwt[i] * 10;
	cshade_(&x1, &y1, rad, &ang, &ang1, &c_b12, &c__1, dis, &an, w, &il, 
		&i__2);

/* 	FILL REGION WITH DESIRED FILL PATTERN */

	if (ish[i] == 0) {
	    goto L90;
	}
	an = ((ish[i] - 1) % 4 - 1) * (float)45.;
	il = 10;
	if (ish[i] > 4 && ish[i] < 11) {
	    il = 11;
	}
	cshade_(&x1, &y1, rad, &ang, &ang1, &c_b12, &c__2, dis, &an, w, &il, &
		c_n1);
	if (ish[i] > 8) {
	    an += (float)90.;
	    il = 11;
	    if (ish[i] > 10) {
		il = 10;
	    }
	    cshade_(&x1, &y1, rad, &ang, &ang1, &c_b12, &c__2, dis, &an, w, &
		    il, &c_n1);
	}
L90:
	ang = ang1;
L100:
	;
    }
    if (il == 11) {
	newpen_(&c__1);
    }

/* 	PLOT LEGEND IF SELECTED */

    if (*aleg == (float)0.) {
	goto L160;
    }
    if (*aleg < (float)0. || *tcs < (float)0.) {
	y1 = *y0 - *cs * *nch / (float)2.;
	i__1 = *n;
	for (i = 1; i <= i__1; ++i) {
	    x1 = *x0 - *rad - *cs * (float)1.1 * *n - (float).1;
	    if (*tcs < (float)0.) {
		x1 = abc[(i << 1) - 1];
		y1 = abc[i * 2];
	    }
	    if (dabs(*aleg) < (float)99.) {
		w[0] = x1;
		w[1] = y1;
		w[2] = x1 + dabs(*aleg);
		w[3] = y1;
		w[4] = x1 + dabs(*aleg);
		w[5] = y1 + dabs(*aleg);
		w[6] = x1;
		w[7] = y1 + dabs(*aleg);
		x1 = x1 + dabs(*aleg) + (float).2;
		an = (float)0.;
		if (jf == 2) {
		    r__1 = (real) icol[i + 2];
		    plot_(&r__1, &c_b10, &c__0);
		}
		il = 0;
		shade_(w, &w[1], &c__4, &c__2, &c__1, dis, &an, &w[8], &il, &
			c_b10, &c_b4, &c_b10, &c_b4);
		if (ish[i] == 0) {
		    goto L120;
		}
		an = ((ish[i] - 1) % 4 - 1) * (float)45.;
		il = 0;
		if (ish[i] > 4 && ish[i] < 11) {
		    il = 1;
		}
		shade_(w, &w[1], &c__4, &c__2, &c__2, dis, &an, &w[8], &il, &
			c_b10, &c_b4, &c_b10, &c_b4);
		if (ish[i] > 8) {
		    an += (float)90.;
		    il = 1;
		    if (ish[i] > 10) {
			il = 0;
		    }
		    shade_(w, &w[1], &c__4, &c__2, &c__2, dis, &an, &w[8], &
			    il, &c_b10, &c_b4, &c_b10, &c_b4);
		}
	    }
L120:
	    if (il == 1) {
		newpen_(&c__1);
	    }
	    if (jf == 2) {
		r__1 = (real) icol[2];
		plot_(&r__1, &c_b10, &c__0);
	    }
	    symbol_(&x1, &y1, cs, labels[i-1], &c_b10, nch, &c_n1);
	    y1 += *cs * (float)1.5;
/* L125: */
	}
    } else {
	ang = *ast;
	i__1 = *n;
	for (i = 1; i <= i__1; ++i) {
	    ang1 = ang + (r__1 = vals[i], dabs(r__1)) * scale;

/* 	COMPUTE LABEL LENGTH AND TRY TO LOCATE TO LOOK NICE */

	    w[0] = (float)0.;
	    w[1] = (float)0.;
	    symbol_(w, &w[1], cs, labels[i-1], &c_b10, nch, &c_n3);
	    r = *rad + *cs + (float).1;
	    if (vals[i] < (float)0.) {
		r += *d;
	    }
	    x1 = *x0 + cos((ang + ang1) * dtr / (float)2.) * r;
	    y1 = *y0 + sin((ang + ang1) * dtr / (float)2.) * r;
	    if (x1 < *x0) {
		x1 -= w[0];
	    }
	    if (vals[i] == (float)0.) {
		goto L140;
	    }
	    if (dabs(*aleg) < (float)99.) {
		if (x1 < *x0) {
		    x1 -= dabs(*aleg);
		}
		if (y1 < *y0) {
		    y1 -= dabs(*aleg);
		}
		w[0] = x1;
		w[1] = y1;
		w[2] = x1 + dabs(*aleg);
		w[3] = y1;
		w[4] = x1 + dabs(*aleg);
		w[5] = y1 + dabs(*aleg);
		w[6] = x1;
		w[7] = y1 + dabs(*aleg);
		x1 = x1 + dabs(*aleg) + (float).2;
		an = (float)0.;
		if (jf == 2) {
		    r__1 = (real) icol[i + 2];
		    plot_(&r__1, &c_b10, &c__0);
		}
		shade_(w, &w[1], &c__4, &c__2, &c__1, dis, &an, &w[8], &c__0, 
			&c_b10, &c_b4, &c_b10, &c_b4);
		if (ish[i] == 0) {
		    goto L140;
		}
		an = ((ish[i] - 1) % 4 - 1) * (float)45.;
		il = 0;
		if (ish[i] > 4 && ish[i] < 11) {
		    il = 1;
		}
		shade_(w, &w[1], &c__4, &c__2, &c__2, dis, &an, &w[8], &il, &
			c_b10, &c_b4, &c_b10, &c_b4);
		if (ish[i] > 8) {
		    an += (float)90.;
		    il = 1;
		    if (ish[i] > 10) {
			il = 0;
		    }
		    shade_(w, &w[1], &c__4, &c__2, &c__2, dis, &an, &w[8], &
			    il, &c_b10, &c_b4, &c_b10, &c_b4);
		}
	    }
L140:
	    if (il == 1) {
		newpen_(&c__1);
	    }
	    if (jf == 2) {
		r__1 = (real) icol[2];
		plot_(&r__1, &c_b10, &c__0);
	    }
	    symbol_(&x1, &y1, cs, labels[i-1], &c_b10, nch, &c_n1);
	    y1 += *cs * (float)1.5;
	    ang = ang1;
/* L150: */
	}
    }

/* 	ADD TITLE IF SELECTED */

L160:
    if (jf == 2) {
	r__1 = (real) icol[1];
	plot_(&r__1, &c_b10, &c__0);
    }
    if (*nt > 0) {
	x1 = (float)0.;
	y1 = (float)0.;
	r__1 = dabs(*tcs);
	symbol_(&x1, &y1, &r__1, t, &c_b10, nt, &c_n3);
	x1 = *x0 - x1 / (float)2.;
	y1 = *y0 + *rad + *cs + (float).2;
	if (dabs(*aleg) < (float)98.) {
	    y1 += dabs(*aleg);
	}
	r__1 = dabs(*tcs);
	symbol_(&x1, &y1, &r__1, t, &c_b10, nt, &c_n1);
    }

/* 	FINISH UP */

L200:
    plot_(&c_b10, &c_b10, &c__3);/* PEN UP */
    if (*iflag > 0) {
	cterm_(&c__2);		/* CLEAR TERMINAL */
	plotnd_();		/* CLOSE PLOT OUTPUT */
	repeat = FALSE_;
    }
    if (*iflag < 0) {
	repeat = TRUE_;
	cterm_(&c__1);		/* PUT TERMINAL IN TEXT MODE */
    }
    return 0;
} /* pichrt_ */

