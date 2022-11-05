
/* *** LAST REVISED ON 24-DEC-1993 07:06:06.53 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]GRID.C */

#include "my.h"

/* Table of constant values */
static integer c__2 = 2;
static integer c__3 = 3;


/* Subroutine */ int grid_(x, y, dx, dy, nx, ny)
real *x, *y, *dx, *dy;
integer *nx, *ny;
{
    /* System generated locals */
    integer i__1, i__2;

    /* External functions */
    extern /* Subroutine */ int plot_(real *, real *, integer *);

    /* Local variables */
    static real t, x0, x1, x2, y1, y2, y0, ex, ey;
    static integer ix, iy, nx1, ny1;

/* 	ROUTINE TO PRODUCE CARTESIAN GRID */

/* 	CREATED BY D. LONG    AUG, 1983	AT JPL */

/* 	X,Y	CORRDINATES OF BOTTOM LEFT CORNER */
/* 	DX,DY	SPACING OF GRID LINES IN X AND Y DIRECTIONS */
/* 	NX,NY	NUMBER OF GRIDS IN X AND Y DIRECTIONS */
/* 		IF NY > 0 AND NX > 0 THEN SOLID GRID DRAWN */
/* 		IF NY < 0 OR NX < 0  TICK MARKS USED */
/* 		IF NY < 0 AND NX < 0 THEN GRID AREA IS BOXED */

    if (*nx < 0 || *ny < 0) {
	goto L200;
    }
    if (*nx == 0 || *ny == 0) {
	return 0;
    }
    plot_(x, y, &c__3);
    i__1 = *nx;
    for (ix = 0; ix <= i__1; ++ix) {
	x1 = *x + ix * *dx;
	x2 = *x + (ix + 1) * *dx;
	y1 = *y + *ny * *dy;
	plot_(&x1, &y1, &c__2);
	plot_(&x2, y, &c__3);
    }
    plot_(x, y, &c__3);
    i__1 = *ny;
    for (iy = 0; iy <= i__1; ++iy) {
	y1 = *y + iy * *dy;
	y2 = *y + (iy + 1) * *dy;
	x1 = *x + *nx * *dx;
	plot_(&x1, &y1, &c__2);
	plot_(x, &y2, &c__3);
    }
    plot_(x, y, &c__3);
    return 0;
L200:
    nx1 = abs(*nx); /* TICKED GRID */
    ny1 = abs(*ny);
    ex = *x + (real) nx1 * *dx;
    ey = *y + (real) ny1 * *dy;
    if ( (*nx >= 0 ? 1 : -1) == (*ny >= 0 ? 1 : -1)) { /* BOX GRID AREA */
	plot_(x, y, &c__3);
	plot_(&ex, y, &c__2);
	plot_(&ex, &ey, &c__2);
	plot_(x, &ey, &c__2);
	plot_(x, y, &c__2);
    }
    t = (float).05;  /* TICK SIZE */
    i__1 = nx1;
    for (ix = 0; ix <= i__1; ++ix) {
	i__2 = ny1;
	for (iy = 0; iy <= i__2; ++iy) {
	    x0 = *x + (real) ix * *dx;
	    y0 = *y + (real) iy * *dy;
	    x1 = x0 + t;
	    x2 = x0 - t;
	    y1 = y0 + t;
	    y2 = y0 - t;
	    if (x2 < *x) {
		x2 = *x;
	    }
	    if (x1 > ex) {
		x1 = ex;
	    }
	    if (y2 < *y) {
		y2 = *y;
	    }
	    if (y1 > ey) {
		y1 = ey;
	    }
	    plot_(&x1, &y0, &c__3);
	    plot_(&x2, &y0, &c__2);
	    plot_(&x0, &y1, &c__3);
	    plot_(&x0, &y2, &c__2);
	}
    }
    return 0;
} /* grid_ */

