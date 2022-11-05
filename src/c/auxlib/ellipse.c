
/* *** LAST REVISED ON  7-JAN-1994 15:44:06.96 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]ELLIPSE.C */

#include "my.h"

/* Table of constant values */

static integer c__2 = 2;
static integer c__3 = 3;

/* Subroutine */ int ellipse_(x0, y0, smaj, smin, ang, ast, aend)
real *x0, *y0, *smaj, *smin, *ang, *ast, *aend;
{
    /* Initialized data */

    static real err = (float).025;

    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    double cos(), sin(), asin(), sqrt();

    /* External functions */
    extern /* Subroutine */ int plot_();

    /* Local variables */
    static real eang, rang, tang;
    static real r, x, y, x1, y1, aa, co;
    static integer ip;
    static real si, dtheta;

/* 	WRITTEN BY:	DG LONG,  JPL  JUNE 1985 */
/* 	MODIFIED: DGL NOV 7,1985 TO HANDLE DEGENERATE ELLIPSES */

/* 	THIS ROUTINE PLOTS AN ELLIPSE.  THE NUMBER OF LINE SEGMENTS */
/* 	USED TO PLOT THE CURVE IS DEPENDENT ON THE RADIUS OF THE ELLIPSE */
/* 	AT EACH POINT. */

/* 	X0,Y0	(R)	CENTER OF ELLIPSE (HALFWAY BETWEEN FOCI) */
/* 	SMAJ	(R)	LENGTH OF SEMI-MAJOR AXIS (DISTANCE FROM ELLIPSE */
/* 				CENTER TO CURVE THROUGH ONE FOCUS) */
/* 	SMIN	(R)	LENGTH OF SEMI-MINOR AXIS (PERPENDICULAR TO SMAJ) */
/* 				0 < SMIN < SMAJ */
/* 	ANG	(R)	ANGLE FROM HORIZONTAL OF SEMI-MAJOR AXIS (DEG) */
/* 	AST	(R)	START ANGLE OF ELLIPSE CURVE FROM SEMI-MAJOR AXIS (DEG) */
/* 	AEND	(R)	END ANGLE OF ELLIPSE CURVE FROM SEMI-MAJOR AXIS (DEG) */
/* 				AEND > AST */

/* 	AST AND AEND ARE DEFINED USING THE IDENTITY FOR AN ELLIPSE: */
/* 		(X,Y) = (SMAJ * COS(T) , SMIN * SIN(T) ) */

/* WORST-CASE PLOTTING ERROR */
    ip = 3;
    rang = *ang * (float)3.141592654 / (float)180.;
    co = cos(rang);
    si = sin(rang);
    dtheta = asin(err / *smaj);
    tang = *ast * (float)3.141592654 / (float)180.;
    eang = *aend * (float)3.141592654 / (float)180.;

L100:
    x = cos(tang) * *smaj;
    y = sin(tang) * *smin;
    x1 = co * x - si * y + *x0;
    y1 = si * x + co * y + *y0;
    plot_(&x1, &y1, &ip);
    ip = 2;
/* Computing 2nd power */
    r__1 = x;
/* Computing 2nd power */
    r__2 = y;
    r = sqrt(r__1 * r__1 + r__2 * r__2);
    aa = (float)2.;
    if (r > (float)0.) {
	aa = err / r;
    }
    if (dabs(aa) < (float)1.) {
	aa = asin(aa);
    } else {
	aa = (float)0.;
    }
    dtheta = (aa >= (float)1e-5 ? aa : (float) 1e-5);
/* MINIMUM STEP SIZE */
    tang += dtheta;
    if (tang > eang) {
	goto L200;
    }
    goto L100;

L200:
    x = cos(eang) * *smaj;
    y = sin(eang) * *smin;
    x1 = co * x - si * y + *x0;
    y1 = si * x + co * y + *y0;
    plot_(&x1, &y1, &c__2);
    plot_(x0, y0, &c__3);

/* LEAVE PEN AT ELLIPSE CENTER */
    return 0;
} /* ellipse_ */

