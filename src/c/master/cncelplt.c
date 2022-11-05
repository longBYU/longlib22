
/* *** LAST REVISED ON 23-DEC-1993 05:43:41.51 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]CNCELPLT.C */

#include "my.h"

/* Table of constant values */

static integer c__3 = 3;
static integer c__2 = 2;
static real c_b26 = (float)1.5;


/* Subroutine */ int cncelplt_(x1, y1, x2, y2, tv, v1, v2, v3, v4, v5, v6, v7,
	 v8)
real *x1, *y1, *x2, *y2, *tv, *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8;
{
    extern doublereal poly1int_();
    extern /* Subroutine */ int plot_();
    static real c, c1, c2;
    static integer if_;
    static real yi1, xi2, yi3, xi4;
    extern integer segcode_();


/* 	CREATED BY D. LONG     NOV, 1983	AT JPL */
/* 	SUBPROGRAM OF CNTRPLT */
/* 	COMPUTES AND PLOTS CELL SECTIONED CONTOURS */

/* 	POINT ID MAP: */
/* 			  (2) */
/* 			2.   3. */
/* 		    (1)	       (4) */
/* 			1.   4. */
/* 			  (8) */


    if_ = segcode_(y1, y2, v1, v2, tv, &yi1);
    if_ += segcode_(x1, x2, v2, v3, tv, &xi2) << 1;
    if_ += segcode_(y2, y1, v3, v4, tv, &yi3) << 2;
    if_ += segcode_(x2, x1, v4, v1, tv, &xi4) << 3;

    switch ((int)(if_ + 1)) {
	case 1:  goto L50;
	case 2:  goto L50;
	case 3:  goto L50;
	case 4:  goto L103;
	case 5:  goto L50;
	case 6:  goto L105;
	case 7:  goto L106;
	case 8:  goto L107;
	case 9:  goto L50;
	case 10:  goto L109;
	case 11:  goto L110;
	case 12:  goto L111;
	case 13:  goto L112;
	case 14:  goto L113;
	case 15:  goto L114;
	case 16:  goto L115;
    }
    goto L50;
L103:
    plot_(x1, &yi1, &c__3);
    plot_(&xi2, y2, &c__2);
    goto L50;
L105:
    plot_(x1, &yi1, &c__3);
    plot_(x2, &yi3, &c__2);
    goto L50;
L106:
    plot_(&xi2, y2, &c__3);
    plot_(x2, &yi3, &c__2);
    goto L50;
L107:
    if (*v3 == *tv) {
	goto L103;
    }
    goto L106;
L109:
    plot_(x1, &yi1, &c__3);
    plot_(&xi4, y1, &c__2);
    goto L50;
L110:
    plot_(&xi4, y1, &c__3);
    plot_(&xi2, y2, &c__2);
    goto L50;
L111:
    if (*v1 == *tv) {
	goto L103;
    }
    goto L109;
L112:
    plot_(&xi4, y1, &c__3);
    plot_(x2, &yi3, &c__2);
    goto L50;
L113:
    if (*v1 == *tv) {
	goto L112;
    }
    goto L109;
L114:
    if (*v3 == *tv) {
	goto L112;
    }
    goto L106;
L115:
    if (*v1 == *tv) {
	goto L50;
    }
    c1 = poly1int_(v5, v1, v3, v7, &c_b26);
    c2 = poly1int_(v6, v2, v4, v8, &c_b26);
    c = (c1 + c2) / (float)2.;
    if (c > *tv) {
	if (*v1 > *tv) {
	    plot_(x1, &yi1, &c__3);
	    plot_(&xi2, y2, &c__2);
	    goto L112;
	} else {
	    plot_(x1, &yi1, &c__3);
	    plot_(&xi4, y1, &c__2);
	    goto L106;
	}
    } else {
	if (*v1 < *tv) {
	    plot_(x1, &yi1, &c__3);
	    plot_(&xi2, y2, &c__2);
	    goto L112;
	} else {
	    plot_(x1, &yi1, &c__3);
	    plot_(&xi4, y1, &c__2);
	    goto L106;
	}
    }
L50:
    return 0;
} /* cncelplt_ */


integer segcode_(x1, x2, v1, v2, tv, x0)
real *x1, *x2, *v1, *v2, *tv, *x0;
{
    /* System generated locals */
    integer ret_val;

    /* Local variables */
    static real sc;


/* 	CREATED BY D. LONG  NOV, 1983 	AT JPL */
/* 	SUBFUNCTION OF CNTRPLT */
/* 	DETERMINES IF INTERSECTION AND COMPUTES LOCATION */

    sc = (float)0.;
    if (dmax(*v1,*v2) >= *tv && dmin(*v1,*v2) <= *tv) {
	sc = (float)1.;
	if (*v2 != *v1) {
	    *x0 = (*x2 - *x1) * (*tv - *v1) / (*v2 - *v1) + *x1;
	} else {
	    *x0 = *x1;
	}
    }
    ret_val = sc;
    return ret_val;
} /* segcode_ */


doublereal poly1int_(v0, v1, v2, v3, d)
real *v0, *v1, *v2, *v3, *d;
{
    /* System generated locals */
    real ret_val, r__1;

    /* Local variables */
    static real c0, c1, c2;

/* 	CREATED BY D. LONG     NOV, 1983	AT JPL */
/* 	SUBFUNCTION OF CNTRPLT */
/* 	DOES LEAST SQUARES CURVE INTERPLOATION */
/* 	V0..V3 ASSUMMED EQUALLY SPACED AND 1.0 DISTANCE */
/* 	D IS POINT OF INTERPOLATED VALUE */

    c0 = *v0 * (float).95 + *v1 * (float).15 - *v2 * (float).15 + *v3 * (
	    float).05;
    c1 = *v0 * (float)-1.05 + *v1 * (float).65 + *v2 * (float).85 - *v3 * (
	    float).45;
    c2 = *v0 * (float).25 - *v1 * (float).25 - *v2 * (float).25 + *v3 * (
	    float).25;

/* Computing 2nd power */
    r__1 = *d;
    ret_val = c0 + c1 * *d + c2 * (r__1 * r__1);
    return ret_val;
} /* poly1int_ */

