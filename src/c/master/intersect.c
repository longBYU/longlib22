
/* *** LAST REVISED ON 23-DEC-1993 06:32:39.70 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MASTER]INTERSECT.C */

#include "my.h"

/* Subroutine */ int intersect_(flag_, x, y, ax1, ay1, ax2, ay2, bx1, by1, 
	bx2, by2, a)
logical *flag_;
real *x, *y, *ax1, *ay1, *ax2, *ay2, *bx1, *by1, *bx2, *by2;
logical *a;
{
    /* System generated locals */
    real r__1, r__2;

    /* Local variables */
    static logical vert;
    static real denom, ca, cb, da, db, ma, mb, da1, da2, db1, db2;

/* 	CREATED BY D. LONG     AUG, 1983	AT JPL */
/* 	SUBPROGRAM OF VAX3DX */

/* 	DETERMINE IF TWO SEGMENTS INTERSECT AND THE POINT OF INTERSECTION */
/* 	IF STARTING POINTS OF SEGMENTS ARE THE SAME SEGMENTS ARE NOT */
/* 	CONSIDERED TO BE INTERSECTING */

    vert = FALSE_;
    *flag_ = FALSE_;

    if (*ax1 == *bx1 && *ay1 == *by1) {		/* SAME START POINT */
	return 0;
    }
    if (*ax2 == *bx2 && *ay2 == *by2) {		/* SAME END POINT */
	*flag_ = TRUE_;
	*x = *ax2;
	*y = *ay2;
	return 0;
    }

    denom = *ax1 - *ax2;
    if (denom == (float)0.) {			/* VERTICAL LINE */
	ma = (float)1e10;
	vert = TRUE_;
    } else {
	ma = (*ay1 - *ay2) / denom;		/* SLOPE OF SEGMENT A */
    }
    denom = *bx1 - *bx2;
    if (denom == (float)0.) {			/* VERTICAL LINE */
	mb = (float)1e10;
	vert = TRUE_;
    } else {
	mb = (*by1 - *by2) / denom;		/* SLOPE OF SEGMENT B */
    }
    if (ma == mb) {				/* PARALELL */
	return 0;
    }
    ca = *ay1 - ma * *ax1;
    cb = *by1 - mb * *bx1;
    if (vert) {
	if (ma == (float)1e10) {
	    *x = *ax1;
	    *y = *x * mb + cb;
	}
	if (mb == (float)1e10) {
	    *x = *bx1;
	    *y = *x * ma + ca;
	}
    } else {
	*x = (ca - cb) / (mb - ma);
	*y = ma * *x + ca;
    }
/* 	INTERSECTION OF LINES THROUGH POINTS IS AT X,Y */
/* Computing 2nd power */
    r__1 = *ax1 - *ax2;
/* Computing 2nd power */
    r__2 = *ay1 - *ay2;
    da = r__1 * r__1 + r__2 * r__2;
/* Computing 2nd power */
    r__1 = *ax1 - *x;
/* Computing 2nd power */
    r__2 = *ay1 - *y;
    da1 = r__1 * r__1 + r__2 * r__2;
    if (da1 > da) {
	return 0;
    }
/* Computing 2nd power */
    r__1 = *ax2 - *x;
/* Computing 2nd power */
    r__2 = *ay2 - *y;
    da2 = r__1 * r__1 + r__2 * r__2;
    if (da2 > da) {
	return 0;
    }
/* Computing 2nd power */
    r__1 = *bx1 - *bx2;
/* Computing 2nd power */
    r__2 = *by1 - *by2;
    db = r__1 * r__1 + r__2 * r__2;
/* Computing 2nd power */
    r__1 = *bx1 - *x;
/* Computing 2nd power */
    r__2 = *by1 - *y;
    db1 = r__1 * r__1 + r__2 * r__2;
    if (db1 > db) {
	return 0;
    }
/* Computing 2nd power */
    r__1 = *bx2 - *x;
/* Computing 2nd power */
    r__2 = *by2 - *y;
    db2 = r__1 * r__1 + r__2 * r__2;
    if (db2 > db) {
	return 0;
    }
    if (ma > mb) {
	*a = TRUE_;
    } else {
	*a = FALSE_;
    }
    *flag_ = TRUE_;
    return 0;
} /* intersect_ */
