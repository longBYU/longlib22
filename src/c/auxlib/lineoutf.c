
/* *** LAST REVISED ON 24-DEC-1993 07:14:22.35 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]LINEOUTF.C */

#include "my.h"

/* Subroutine */ int lineoutf_(rx1, ry1, rx2, ry2, res, ixwide, iywide, ibnt, 
	iadd, xx)
real *rx1, *ry1, *rx2, *ry2, *res;
integer *ixwide, *iywide, *ibnt, *iadd;
real *xx;
{
    /* System generated locals */
    integer i__1;
    real r__1, r__2, r__3;

    /* Builtin functions */
    integer i_nint();
    double sqrt();

    /* Local variables */
    static integer d, x, y, index, i1, i2, x1, y1, x2, y2, dx, dy, jx, jy, 
	    ix0, iy0, dif;
    static logical inv;
    static integer ixw, iyy;

/* 	COMPUTE THE LIST OF PIXELS (LEXICOGRAPHIC ORDER) A ALONG THE */
/* 	LINE FROM (RX1,RY1) TO (RX2,RY2) WITH ENHANCED RESOLUTION */

/* 	RX1,RY1	(R)	START POINT OF LINE SEGMENT */
/* 	RX2,RY2	(R)	STOP POINT OF LINE SEGMENT */
/* 	RES	(R)	RESOLUTION ENHANCEMENT FACTOR */
/* 	IXWIDE	(I)	X DIMENSION (0 <= IX <= IXWIDE-1) */
/* 	IYWIDE	(I)	Y DIMENSION (0 <= IY <= IYWIDE-1) */
/* 	IBNT	(I)	RETURNED NUMBER OF PIXELS */
/* 	IADD	(I)	RETURNED ARRAY OF PIXEL INDEXES */
/* 	XX	(R)	DISTANCE OF PIXEL FROM START */

/* 	LEXICOGRAPHIC INDEX IS: N=IY*IXWIDE+IX+1 */


    /* Parameter adjustments */
    --xx;
    --iadd;

    /* Function Body */
    r__2 = (r__1 = (*rx1 - *rx2) * *res, dabs(r__1));
    dx = i_nint(&r__2);
    r__2 = (r__1 = (*ry1 - *ry2) * *res, dabs(r__1));
    dy = i_nint(&r__2);
    r__1 = *rx1 * *res;
    x1 = i_nint(&r__1);
    r__1 = *rx2 * *res;
    x2 = i_nint(&r__1);
    r__1 = *ry1 * *res;
    y1 = i_nint(&r__1);
    r__1 = *ry2 * *res;
    y2 = i_nint(&r__1);
    r__1 = *rx1 * *res;
    ix0 = i_nint(&r__1);
    r__1 = *ry1 * *res;
    iy0 = i_nint(&r__1);
    if (x1 < 0)
	x1 = 0;
    if (x2 < 0)
	x2 = 0;
    if (y1 < 0)
	y1 = 0;
    if (y2 < 0)
	y2 = 0;
    if ((real) x1 >= *ixwide * *res)
	x1 = *ixwide * *res - 1;
    if ((real) x2 >= *ixwide * *res)
	x2 = *ixwide * *res - 1;
    if ((real) y1 >= *iywide * *res)
	y1 = *iywide * *res - 1;
    if ((real) y2 >= *iywide * *res)
	y2 = *iywide * *res - 1;
    inv = FALSE_;
    if (dx < dy) {
	x = x1;
	x1 = y1;
	y1 = x;
	x = x2;
	x2 = y2;
	y2 = x;
	x = dy;
	dy = dx;
	dx = x;
	inv = TRUE_;
	i1 = ix0;
	ix0 = iy0;
	iy0 = i1;
    }
    if (x2 < x1) {
	x = x1;
	x1 = x2;
	x2 = x;
	y = y1;
	y1 = y2;
	y2 = y;
    }
    dif = 1;
    if (y2 < y1)
	dif = -1;
    d = (dy << 1) - dx;
    i1 = dy << 1;
    i2 = dy - dx << 1;
    y = y1;
    iyy = 0;

    ixw = *ixwide;
    *ibnt = 0;
    i__1 = x2;
    for (x = x1; x <= i__1; ++x) {
	++(*ibnt);
	if (inv) {
	    r__1 = (x + iyy) / *res;
	    jx = i_nint(&r__1);
	    r__1 = y / *res;
	    jy = i_nint(&r__1);
	} else {
	    r__1 = (y + iyy) / *res;
	    jx = i_nint(&r__1);
	    r__1 = x / *res;
	    jy = i_nint(&r__1);
	}
	index = jx * ixw + jy + 1;
	iadd[*ibnt] = index;
/* Computing 2nd power */
	r__1 = (real) (x - ix0);
/* Computing 2nd power */
	r__2 = (real) (y - iy0);
/* Computing 2nd power */
	r__3 = *res;
	xx[*ibnt] = (r__1 * r__1 + r__2 * r__2) / (r__3 * r__3);
/* 		XX(IBNT)=(X-IX0)**2+(Y-IY0)**2 */
	if (xx[*ibnt] > (float)0.) {
	    xx[*ibnt] = sqrt(xx[*ibnt]);
	}
	if (d < 0) {
	    d += i1;
	} else {
	    d += i2;
	    y += dif;
	}
    }
    return 0;
} /* lineoutf_ */






