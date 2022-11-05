
/* *** LAST REVISED ON 25-DEC-1993 17:38:06.94 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]BARCHR.C */

#include "my.h"

/* Table of constant values */

static integer c__3 = 3;
static real c_b3 = (float)1.5;
static real c_b4 = (float)1.;
static integer c_n1 = -1;
static real c_b8 = (float)0.;
static integer c__0 = 0;
static integer c__2 = 2;
static integer c_n3 = -3;
static integer c__10 = 10;
static integer c__4 = 4;
static integer c__1 = 1;
static real c_b93 = (float)90.;
static integer c__11 = 11;


/* Subroutine */ int barchr_(vals, nb, ns, ish, iflag, xlen, ylen, vmin, vmax,
	 form, ndiv, sp, slab, nslab, blab, nblab, cs, t, nt, bt, nbt, lt, 
	nlt, tcs, aleg, dis, iwt, icol)
real *vals;
integer *nb, *ns, *ish, *iflag;
real *xlen, *ylen, *vmin, *vmax, *form;
integer *ndiv;
real *sp;
char *slab[];
integer *nslab;
char *blab[];
integer *nblab;
real *cs;
char *t;
integer *nt;
char *bt;
integer *nbt;
char *lt;
integer *nlt;
real *tcs, *aleg, *dis;
integer *iwt, *icol;
{
    /* Initialized data */

    static logical repeat = FALSE_;

    /* System generated locals */
    integer vals_dim1, vals_offset, i__1, i__2, i__3;
    real r__1, r__2;

    /* Local variables */
    extern /* Subroutine */ int plot_();
    static integer i, j, k;
    extern /* Subroutine */ int shade_();
    static real w[1000], scale;
    extern /* Subroutine */ int frame_(), cterm_();
    static integer i1;
    static real x1, y1, am, an;
    static integer jf, nd, ii, il;
    static real av, wb;
    static integer kk, ip;
    static real vm;
    static integer nw;
    static real vx, xx, yy;
    extern /* Subroutine */ int number_(), newpen_(), plotnd_(), symbol_();
    static integer jff, ilu;
    static real vsp;

/* 	ROUTINE TO PLOT A BAR CHART WITH SHADED BARS OR SHADED REGIONS */
/* 	BETWEEN LINES WITH DESCRIPTIVE LEGENDS */

/* 	WRITTEN:  DGL  AUG 1987 */

/* 	VALS	(R) VALUE FOR EACH BAR SEGMENT DIMENSIONED VALS(NB,NS) */
/* 		    WHERE NB IS THE NUMBER OF BARS AND NS IS THE */
/* 		    NUMBER OF SEGMENTS IN EACH BAR */
/* 	NB	(I) NUMBER OF BARS/NUMBER OF POINTS (25>NB>0) */
/* 	NS	(I) NUMBER OF SEGMENTS IN EACH BAR/NUMBER OF LINES (10>NS>0) */
/* 	ISH	(R) SHADE OPTION FOR EACH SEGMENT DIMENSIONED ISH(NS) */
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
/* 	IFLAG	(R) PLOTTING FLAG */
/* 			< 0 DON'T CLOSE PLOT PACKAGE */
/* 			> 0 CLOSE PLOT PACKAGE */
/* 		MAG	> 10000 INIT PLOT PACKAGE */
/* 	(ONE'S DIGIT)   = 1 DON'T USE COLORS */
/* 		        = 2 USE COLORS */
/* 	(TEN'S DIGIT)	= 0 VERTICAL BAR CHART */
/* 			= 1 HORIZONTAL BAR CHART */
/* 			= 2 LINE CHART WITH SHADING BETWEEN LINES */
/* 	(HUNDRED'S)	= SCREEN GRAPHICS DEVICE (SEE FRAME) */
/* 	XLEN	(R) HEIGHT OF CHART */
/* 		    IF XLEN <0 THEN CHART IS PUT IN BOX */
/* 	YLEN	(R) WIDTH OF CHART */
/* 	VMIN	(R) MINIMUM VALUE OF VALS SHOWN ON CHART */
/* 	VMAX	(R) MAXIMUM VALUE OF VALS SHOWN ON CHART */
/* 		    NOTE: IF VMIN=VMAX THEN AUTO SCALING IS USED. */
/* 	FORM	(R) NUMERIC LABEL FORMAT (SEE NUMBER) */
/* 	NDIV	(I) NUMBER OF DIVSIONS ALONG BAR/LINE LENGTH */
/* 		    < 0 LINES ACROSS BAR SPACE SHOWN */
/* 		    = 0 NO DIVISION OR NUMERIC LABELS */
/* 		    > 0 NO LINES ACROSS BAR SPACE SHOWN */
/* 	SP	(R) WIDTH OF BAR */
/* 		    = 0 BARS EVENLY SPACE WITH AUTO SPACING */
/* 		   <> 0 BARS GROUPED IN GROUPS OF INT(SP), WITH SPACING */
/* 			BETWEEN BARS IN GROUPS SPECIFIED BY FRAC(SP) */
/* 	SLAB	(C) SEGMENT LABEL ARRAY DIMENSIONED SLAB(NS) */
/* 	NSLAB	(I) MAXIMUM NUMBER OF CHARACTERS IN SEGMENT LABELS */
/* 	BLAB	(C) BASE LABEL ARRAY DIMENSIONED BLAB(NB) */
/* 	NBLAB	(I) MAXIMUM NUMBER OF CHARACTERS IN BASE LABELS */
/* 	CS	(R) LABEL CHARACTER SIZE */
/* 	T	(C) TITLE ABOVE CHART */
/* 	NT	(I) NUMBER OF CHARACTERS IN TITLE */
/* 	BT	(C) TITLE BESIDE BASE OF BARS */
/* 	NBT	(I) NUMBER OF CHARACTERS IN BT */
/* 	LT	(C) TITLE ALONG SIZE OF BARS */
/* 	NLT	(I) NUMBER OF CHARACTERS IN NLT */
/* 	TCS	(R) TITLE CHARACTER SIZE */
/* 	ALEG	(R) LEGEND LOCATION */
/* 		    ALEG(1)= LEGEND SHADING BOX SIZE */
/* 			      = 0 NO LEGEND */
/* 			      < 0 LEGEND PLOTTED TO RIGHT OF CHART */
/* 				  AND ALEG(2),ALEG(3) NOT USED */
/* 			      > 0 ALEG(2),ALEG(3) USED */
/* 		    ALEG(2)= X POSITION OF LOWER LEFT CORNER OF LEGEND */
/* 		    ALEG(3)= Y POSITION OF LOWER LEFT CORNER OF LEGEND */
/* 	DIS	(R) SHADING LINE DISTANCE */
/* 		    > 0 LINE WEIGHTS NOT USED */
/* 		    < 0 LINE WEIGHTS USED */
/* 	IWT	(I) PEN WIDTH ARRAY (0-9) */
/* 		    IWT(1) = AXIS LINE WIDTH */
/* 		    IWT(2) = DIVISION LINE WIDTH */
/* 		    IWT(3) = BAR OUTLINE/LINE WIDTH */
/* 		    IWT(4) = LABEL WIDTH */
/* 		    IWT(5) = TITLE WIDTH (BT,LT) */
/* 		    IWT(6) = TOP TITLE WIDTH */
/* 	ICOL	(I) COLOR ARRAY */
/* 		    ICOL(1) = TOP OF CHART TITLE COLOR (RETURN) */
/* 		    ICOL(2) = BT TITLE COLOR */
/* 		    ICOL(3) = LT TITLE COLOR */
/* 		    ICOL(4) = AXIS TITLE COLOR */
/* 		    ICOL(5) = SLAB COLOR */
/* 		    ICOL(6) = BLAB COLOR */
/* 		    ICOL(7) = SEGMENT COLOR 1 */
/* 		    ICOL(8) = SEGMENT COLOR 2 */
/* 		     ...          ... */

    /* Parameter adjustments */
    --icol;
    --iwt;
    --aleg;
    --ish;
    vals_dim1 = *nb;
    vals_offset = vals_dim1 + 1;
    vals -= vals_offset;

    /* Function Body */

/* 	INTIALIZE ROUTINE AND PLOT PACKAGE IF REQUIRED */

    if (*iflag == 0) {
	if (repeat) {
	    plotnd_();
	}
/* CLOSE PLOTTER */
	repeat = FALSE_;
	return 0;
    }

/* 	INTIALIZE PLOT PACKAGE */

    jf = abs(*iflag);
    if (! repeat && jf < 10000) {
	ilu = jf / 100;
/* GRAPHICS DEVICE CODE */
	frame_(&c__3, &ilu, &c_b3, &c_b4, &c_b4);
/* INTIALIZE */
    } else {
	cterm_(&c_n1);
/* PUT TERMINAL IN PLOT MODE */
    }
    jff = jf % 100 / 10;
/* OPTION FLAG */
    jf %= 10;

/* COLOR FLAG */
    vm = *vmin;
    vx = *vmax;
    scale = vx - vm;
    if (scale <= (float)0.) {
	vm = vals[vals_dim1 + 1];
	vx = vals[vals_dim1 + 1];
	i__1 = *nb;
	for (i = 1; i <= i__1; ++i) {
	    i__2 = *ns;
	    for (j = 1; j <= i__2; ++j) {
/* Computing MIN */
		r__1 = vals[i + j * vals_dim1];
		vm = dmin(r__1,vm);
/* Computing MAX */
		r__1 = vals[i + j * vals_dim1];
		vx = dmax(r__1,vx);
/* L10: */
	    }
	}
	scale = vx - vm;
	if (scale == (float)0.) {
	    scale = (float)1.;
	}
    }

/* 	MAKE CHART AXISES */

    if (*dis < (float)0.) {
	i__2 = iwt[1] * 10;
	newpen_(&i__2);
    }
    if (jf == 2) {
	r__1 = (real) icol[4];
	plot_(&r__1, &c_b8, &c__0);
    }
    plot_(&c_b8, ylen, &c__3);
    plot_(&c_b8, &c_b8, &c__2);
    r__1 = dabs(*xlen);
    plot_(&r__1, &c_b8, &c__2);
    if (*xlen < (float)0.) {
	r__1 = dabs(*xlen);
	plot_(&r__1, ylen, &c__2);
	plot_(&c_b8, ylen, &c__2);
    }

/* 	MAKE AXIS LABELS */

    nd = abs(*ndiv);
    am = (float)0.;
    if (nd == 0) {
	goto L50;
    }
    if (*dis < (float)0.) {
	i__2 = iwt[4] * 10;
	newpen_(&i__2);
    }
    scale /= (real) nd;
    if (jff != 1) {

/* 	COMPUTE NUMERIC LABEL LENGTHS */

	i__2 = nd;
	for (i = 0; i <= i__2; ++i) {
	    av = vm + scale * i;
	    x1 = (float)0.;
	    y1 = (float)0.;
	    number_(&x1, &y1, cs, &av, &c_b8, form, &c_n3);
	    am = dmax(am,x1);
/* L15: */
	}

/* 	DISPLAY NUMERIC LABELS ON Y AXIS */

	i__2 = nd;
	for (i = 0; i <= i__2; ++i) {
	    av = vm + scale * i;
	    x1 = -(doublereal)am - *cs / (float)2.;
	    y1 = i * *ylen / nd;
	    number_(&x1, &y1, cs, &av, &c_b8, form, &c_n1);
/* L20: */
	}
	if (*ndiv < 0) {
	    if (*dis < (float)0.) {
		newpen_(&c__10);
	    }
	    i__2 = nd;
	    for (i = 1; i <= i__2; ++i) {
		y1 = i * *ylen / nd;
		plot_(&c_b8, &y1, &c__3);
		r__1 = dabs(*xlen);
		plot_(&r__1, &y1, &c__2);
/* L25: */
	    }
	}
    } else {

/* 	DISPLAY NUMERIC LABELS ON X AXIS */

	i__2 = nd;
	for (i = 0; i <= i__2; ++i) {
	    av = vm + scale * i;
	    y1 = -(doublereal)(*cs);
	    x1 = i * dabs(*xlen) / nd;
	    number_(&x1, &y1, cs, &av, &c_b8, form, &c__0);
/* L30: */
	}
	if (*ndiv < 0) {
	    if (*dis < (float)0.) {
		newpen_(&c__10);
	    }
	    i__2 = nd;
	    for (i = 1; i <= i__2; ++i) {
		x1 = i * dabs(*xlen) / nd;
		plot_(&x1, &c_b8, &c__3);
		plot_(&x1, ylen, &c__2);
/* L35: */
	    }
	}
    }

/* 	MAKE CHART BARS/LINES */

L50:
    if (*ylen == (float)0. || *xlen == (float)0.) {
	goto L200;
    }
    if (jff == 1) {
	scale = dabs(*xlen) / scale / (real) nd;
    } else {
	scale = *ylen / scale / (real) nd;
    }

    if (jff < 2) {

/* 	MAKE BAR CHART */

	vsp = dabs(*xlen) / (real) (*nb);
/* VERTICAL BARS */
	if (jff == 1) {
	    vsp = *ylen / (real) (*nb);
	}
/* HORIZONTAL BARS */
	wb = (dabs(*sp) - (integer) dabs(*sp)) / (float)2.;
	kk = (integer) dabs(*sp);
	if (kk == 1) {
	    kk = 0;
	}
	if (wb == (float)0.) {
	    wb = vsp * (float).4;
	}
/* AUTO SCALE */
	i__2 = *nb;
	for (i = 1; i <= i__2; ++i) {
	    i__1 = *ns;
	    for (j = 1; j <= i__1; ++j) {
		if (jf == 2) {
		    r__1 = (real) icol[j + 6];
		    plot_(&r__1, &c_b8, &c__0);
		}

/* 	DO AREA OUTLINE */

		if (jff == 1) {
/* HORIZONTAL BARS */
		    y1 = (i - (float).5) * vsp;
		    if (kk != 0) {
			k = (i - 1) % kk;
			y1 += (vsp - wb) * ((real) k - (real) (kk - 1) / (
				float)2.);
		    }
		    yy = wb;
		    if (j > 1) {
			av = (float)0.;
			i__3 = j - 1;
			for (k = 1; k <= i__3; ++k) {
			    av += vals[i + k * vals_dim1];
/* L112: */
			}
			x1 = (av - vm) * scale;
			av += vals[i + j * vals_dim1];
			xx = (av - vm) * scale;
		    } else {
			x1 = (float)0.;
			xx = (vals[i + j * vals_dim1] - vm) * scale;
		    }
		    w[0] = x1;
		    w[1] = y1 - yy;
		    w[2] = xx;
		    w[3] = y1 - yy;
		    w[4] = xx;
		    w[5] = y1 + yy;
		    w[6] = x1;
		    w[7] = y1 + yy;
		} else {
/* VERTICAL BARS */
		    x1 = (i - (float).5) * vsp;
		    if (kk != 0) {
			k = (i - 1) % kk;
			x1 += (vsp - wb) * ((real) k - (real) (kk - 1) / (
				float)2.);
		    }
		    xx = wb;
		    if (j > 1) {
			av = (float)0.;
			i__3 = j - 1;
			for (k = 1; k <= i__3; ++k) {
			    av += vals[i + k * vals_dim1];
/* L113: */
			}
			y1 = (av - vm) * scale;
			av += vals[i + j * vals_dim1];
			yy = (av - vm) * scale;
		    } else {
			y1 = (float)0.;
			yy = (vals[i + j * vals_dim1] - vm) * scale;
		    }
		    w[0] = x1 - xx;
		    w[1] = y1;
		    w[2] = x1 + xx;
		    w[3] = y1;
		    w[4] = x1 + xx;
		    w[5] = yy;
		    w[6] = x1 - xx;
		    w[7] = yy;
		}

/* 	OUTLINE AREA */

		an = (float)0.;
		il = 0;
		if (*dis < (float)0.) {
		    i__3 = iwt[3] * 10;
		    newpen_(&i__3);
		}
		r__1 = dabs(*dis);
		shade_(w, &w[1], &c__4, &c__2, &c__1, &r__1, &an, &w[8], &il, 
			&c_b8, &c_b4, &c_b8, &c_b4);
		if (ish[j] == 0) {
		    goto L75;
		}

/* 	FILL WITH DESIRED PATTEN */

		an = ((ish[j] - 1) % 4 - 1) * (float)45.;
		il = 10;
		if (ish[j] > 4 && ish[j] < 11) {
		    il = 11;
		}
		r__1 = dabs(*dis);
		shade_(w, &w[1], &c__4, &c__2, &c__2, &r__1, &an, &w[8], &il, 
			&c_b8, &c_b4, &c_b8, &c_b4);
		if (ish[j] > 8) {
		    an += (float)90.;
		    il = 11;
		    if (ish[j] > 10) {
			il = 10;
		    }
		    r__1 = dabs(*dis);
		    shade_(w, &w[1], &c__4, &c__2, &c__2, &r__1, &an, &w[8], &
			    il, &c_b8, &c_b4, &c_b8, &c_b4);
		}
L75:
		;
	    }
/* L100: */
	}
	if (il != 10) {
	    newpen_(&c__1);
	}
    } else {

/* 	USE SHADING BETWEEN LINES */

	vsp = dabs(*xlen) / (real) (*nb - 1);
	i__2 = *ns;
	for (j = 1; j <= i__2; ++j) {
	    i__1 = *nb;
	    for (i = 1; i <= i__1; ++i) {
		x1 = (i - 1) * vsp;
		if (j > 1) {
		    av = (float)0.;
		    i__3 = j;
		    for (k = 1; k <= i__3; ++k) {
			av += vals[i + k * vals_dim1];
/* L212: */
		    }
		    y1 = (av - vm) * scale;
		} else {
		    y1 = (vals[i + j * vals_dim1] - vm) * scale;
		}
		w[(i << 1) - 2] = x1;
		w[(i << 1) - 1] = y1;
/* L250: */
	    }
	    if (j == 1) {
		i = *nb + 1;
		w[(i << 1) - 2] = x1;
		w[(i << 1) - 1] = (float)0.;
		++i;
		w[(i << 1) - 2] = (float)0.;
		w[(i << 1) - 1] = (float)0.;
	    } else {
		i = *nb;
		i__1 = *nb;
		for (ii = 1; ii <= i__1; ++ii) {
		    i1 = *nb - ii + 1;
		    x1 = (i1 - 1) * vsp;
		    av = (float)0.;
		    i__3 = j - 1;
		    for (k = 1; k <= i__3; ++k) {
			av += vals[i1 + k * vals_dim1];
/* L213: */
		    }
		    y1 = (av - vm) * scale;
		    ++i;
		    w[(i << 1) - 2] = x1;
		    w[(i << 1) - 1] = y1;
/* L260: */
		}
		i = *nb << 1;
	    }
	    nw = (i << 1) + 2;
	    if (jf == 2) {
		r__1 = (real) icol[j + 6];
		plot_(&r__1, &c_b8, &c__0);
	    }

/* 	PLOT LINE FOR THIS SEGMENT */

	    if (*dis < (float)0.) {
		i__1 = iwt[3] * 10;
		newpen_(&i__1);
	    }
	    ip = 3;
	    i__1 = i;
	    for (k = 1; k <= i__1; ++k) {
		plot_(&w[(k << 1) - 2], &w[(k << 1) - 1], &ip);
		ip = 2;
/* L275: */
	    }
	    if (ish[j] == 0) {
		goto L300;
	    }

/* 	FILL WITH DESIRED PATTEN */

	    an = ((ish[j] - 1) % 4 - 1) * (float)45.;
	    il = 10;
	    if (ish[j] > 4 && ish[j] < 11) {
		il = 11;
	    }
	    r__1 = dabs(*dis);
	    shade_(w, &w[1], &i, &c__2, &c__2, &r__1, &an, &w[nw - 1], &il, &
		    c_b8, &c_b4, &c_b8, &c_b4);
	    if (ish[j] > 8) {
		an += (float)90.;
		il = 11;
		if (ish[j] > 10) {
		    il = 10;
		}
		r__1 = dabs(*dis);
		shade_(w, &w[1], &i, &c__2, &c__2, &r__1, &an, &w[nw - 1], &
			il, &c_b8, &c_b4, &c_b8, &c_b4);
	    }
L300:
	    ;
	}
    }
    if (il != 0) {
	newpen_(&c__1);
    }

/* 	ADD BASE LABELS */

    if (*nblab != 0) {
	if (*dis < (float)0.) {
	    i__2 = iwt[4] * 10;
	    newpen_(&i__2);
	}
	if (jf == 2) {
	    r__1 = (real) icol[6];
	    plot_(&r__1, &c_b8, &c__0);
	}
	k = *nb;
	if (kk != 0) {
	    k = (*nb - 1) % kk;
	}
	j = 1;
	if (kk != 0) {
	    j = kk;
	}
	i__2 = k;
	for (i = 1; i <= i__2; ++i) {
	    if (jff == 1) {			/* HORIZONTAL BARS */
		y1 = ((i - 1) * j + (float).5) * vsp;
		x1 = -(doublereal)(*cs);
		symbol_(&x1, &y1, cs, blab, &c_b93, nblab, &c__0);
	    } else {				/* VERTICAL ORIENTATION */
		x1 = ((i - 1) * j + (float).5) * vsp;
		if (jff == 2) {
		    x1 = (i - 1) * j * vsp;
		}
		y1 = -(doublereal)(*cs);
		symbol_(&x1, &y1, cs, blab[i-1], &c_b8, nblab, &c__0);
	    }
/* L320: */
	}
    }

/* 	PLOT LEGEND IF SELECTED */

    if (aleg[1] == (float)0.) {
	goto L160;
    }
    if (aleg[1] < (float)0.) {
	x1 = dabs(*xlen) + (float).2;
	y1 = (*ylen - *nb * dabs(aleg[1])) * (float).5;
    } else {
	x1 = aleg[2];
	y1 = aleg[3];
    }
    i__2 = *ns;
    for (i = 1; i <= i__2; ++i) {

/* 	MAKE SHADING BOX */

	w[0] = x1;
	w[1] = y1;
	w[2] = x1 + dabs(aleg[1]);
	w[3] = y1;
	w[4] = x1 + dabs(aleg[1]);
	w[5] = y1 + dabs(aleg[1]);
	w[6] = x1;
	w[7] = y1 + dabs(aleg[1]);
	xx = x1 + dabs(aleg[1]) + (float).12;
	yy = y1 + (dabs(aleg[1]) - *cs) * (float).5;
	an = (float)0.;
	if (jf == 2) {
	    r__1 = (real) icol[i + 6];
	    plot_(&r__1, &c_b8, &c__0);
	}
	il = 10;
	r__1 = dabs(*dis);
	shade_(w, &w[1], &c__4, &c__2, &c__1, &r__1, &an, &w[8], &il, &c_b8, &
		c_b4, &c_b8, &c_b4);
	if (ish[i] == 0) {
	    goto L220;
	}
	an = ((ish[i] - 1) % 4 - 1) * (float)45.;
	il = 0;
	if (ish[i] > 4 && ish[i] < 11) {
	    il = 1;
	}
	r__1 = dabs(*dis);
	shade_(w, &w[1], &c__4, &c__2, &c__2, &r__1, &an, &w[8], &il, &c_b8, &
		c_b4, &c_b8, &c_b4);
	if (ish[i] > 8) {
	    an += (float)90.;
	    il = 1;
	    if (ish[i] > 10) {
		il = 0;
	    }
	    r__1 = dabs(*dis);
	    shade_(w, &w[1], &c__4, &c__2, &c__2, &r__1, &an, &w[8], &il, &
		    c_b8, &c_b4, &c_b8, &c_b4);
	}
L220:

/* 	ADD SEGMENT LEGEND LABELS */

	if (*nslab != 0) {
	    if (*dis < (float)0.) {
		i__1 = iwt[4] * 10;
		newpen_(&i__1);
	    }
	    if (jf == 2) {
		r__1 = (real) icol[5];
		plot_(&r__1, &c_b8, &c__0);
	    }
	    symbol_(&xx, &yy, cs, slab[i-1], &c_b8, nslab, &c_n1);
	}
	y1 += dabs(aleg[1]) * (float)1.2;
/* L225: */
    }

/* 	ADD TITLES */
L160:
    if (*nbt > 0) {
	if (jf == 2) {
	    r__1 = (real) icol[4];
	    plot_(&r__1, &c_b8, &c__0);
	}
	if (*dis < (float)0.) {
	    i__2 = iwt[4] * 10;
	    newpen_(&i__2);
	}
	x1 = (float)0.;
	y1 = (float)0.;
	symbol_(&x1, &y1, cs, bt, &c_b8, nbt, &c_n3);
	if (jff != 1) {		/* VERTICAL */
	    x1 = (dabs(*xlen) - x1) * (float).5;
	    y1 = *cs * (float)-3.;
	    symbol_(&x1, &y1, cs, bt, &c_b8, nbt, &c_n1);
	} else {		/* HORIZONTAL BARS */
	    y1 = (*ylen - x1) * (float).5;
	    x1 = -(doublereal)(*cs) * (float)3.;
	    symbol_(&x1, &y1, cs, bt, &c_b93, nbt, &c_n1);
	}
    }
    if (*nlt > 0) {
	if (jf == 2) {
	    r__1 = (real) icol[4];
	    plot_(&r__1, &c_b8, &c__0);
	}
	if (*dis < (float)0.) {
	    i__2 = iwt[4] * 10;
	    newpen_(&i__2);
	}
	x1 = (float)0.;
	y1 = (float)0.;
	symbol_(&x1, &y1, cs, lt, &c_b8, nlt, &c_n3);
	if (jff != 1) {		/* VERTICAL */
	    y1 = (*ylen - x1) * (float).5;
	    x1 = -(doublereal)am - *cs;
	    symbol_(&x1, &y1, cs, lt, &c_b93, nlt, &c_n1);
	} else {		/* HORIZONTAL BARS */
	    x1 = (dabs(*xlen) - x1) * (float).5;
	    y1 = *cs * (float)-3.;
	    symbol_(&x1, &y1, cs, lt, &c_b8, nlt, &c_n1);
	}
    }
    if (jf == 2) {
	r__1 = (real) icol[1];
	plot_(&r__1, &c_b8, &c__0);
    }
    if (*nt > 0) {
	an = -(doublereal)an;
	if (*dis < (float)0.) {
	    i__2 = iwt[6] * 10;
	    newpen_(&i__2);
	}
	r__1 = *ylen + (float).1;
	r__2 = dabs(*tcs);
	symbol_(&an, &r__1, &r__2, t, &c_b8, nt, &c_n1);
    }

/* 	FINISH UP */
L200:
    if (*dis < (float)0.) {	/* RESTORE LINETYPE/WIDTH */
	newpen_(&c__11);
    }
    plot_(&c_b8, &c_b8, &c__3);	/* PEN UP */
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
} /* barchr_ */

