
/* *** LAST REVISED ON 24-DEC-1993 07:11:55.47 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.AUXLIB]LGRID.C */

#include "my.h"

/* Table of constant values */
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;


/* Subroutine */ int lgrid_(x, y, dx, dy, nx, ny, if_)
real *x, *y, *dx, *dy;
integer *nx, *ny, *if_;
{
    /* System generated locals */
    integer i__1, i__2;
    real r__1;

    /* Builtin functions */
    double r_lg10();

    /* External functions */
    extern /* Subroutine */ int plot_();
    extern /* Subroutine */ int newpen_();

    /* Local variables */
    static real x0, x1, y0, y1;
    static integer ix, iy;
    static real xm, ym;
    static integer ixm, iym, inx1, iny1;

/* 	ROUTINE TO PRODUCE LOGRITHMIC GRID */
/* 	CREATED BY D. LONG    NOV, 1983		AT JPL */
/* 	X,Y	COORDINATES OF BOTTOM LEFT CORNER */
/* 	DX,DY	SPACING OF GRID LINES IN X AND Y DIRECTIONS */
/* 	NX,NY	NUMBER OF GRIDS IN X AND Y DIRECTIONS */
/* 		IF NY > 0 AND NX > 0 THEN LINEAR GRID */
/* 		IF NY < 0 AND NX < 0 THEN LOG X AND LINEAR Y */
/* 		IF NY < 0 AND NX < 0 THEN LOG X AND LOG Y */
/* 		IF NY > 0 AND NX > 0 THEN LINEAR Y AND LOG Y */
/* 	IF	OPTION FLAG */
/* 		= 0 SOLID.  MINOR LINES FOR LOG SPACING */
/* 		= 1 DOTTED. MINOR LINES FOR LOG SPACING */
/* 		= 2 SOLID.  MINOR TICKS FOR LOG SPACING */

    if (*nx == 0 || *ny == 0) {
	return 0;
    }
    if (*if_ == 1) {		/* DOTTED LINES */
	newpen_(&c__2);
    }
    xm = abs(*nx) * *dx + *x;
    ym = abs(*ny) * *dy + *y;
    inx1 = abs(*nx) + 1;
    iny1 = abs(*ny) + 1;
    plot_(x, y, &c__3);
    plot_(x, &ym, &c__2);
    i__1 = abs(*nx);
    for (ix = 1; ix <= i__1; ++ix) {
	if (*nx < 0) {
	    x0 = (ix - 1) * *dx + *x;
	    for (ixm = 2; ixm <= 9; ++ixm) {
		r__1 = (real) ixm;
		x1 = r_lg10(&r__1) * *dx + x0;
		if (*if_ >= 2) {
		    i__2 = iny1;
		    for (iy = 1; iy <= i__2; ++iy) {
			y0 = (iy - 1) * *dy + *y - (float).08;
			y1 = y0 + (float).16;
			if (iy == 1 && *dy > (float)0.) {
			    y0 = *y;
			}
			if (iy == 1 && *dy < (float)0.) {
			    y1 = *y;
			}
			if (iy == iny1 && *dy > (float)0.) {
			    y1 = ym;
			}
			if (iy == iny1 && *dy < (float)0.) {
			    y0 = ym;
			}
			plot_(&x1, &y0, &c__3);
			plot_(&x1, &y1, &c__2);
		    }
		} else {
		    plot_(&x1, y, &c__3);
		    plot_(&x1, &ym, &c__2);
		}
	    }
	}
	x0 = ix * *dx + *x;
	plot_(&x0, y, &c__3);
	plot_(&x0, &ym, &c__2);
    }
    plot_(x, y, &c__3);
    plot_(&xm, y, &c__2);
    i__1 = abs(*ny);
    for (iy = 1; iy <= i__1; ++iy) {
	if (*ny < 0) {
	    y0 = (iy - 1) * *dy + *y;
	    for (iym = 2; iym <= 9; ++iym) {
		r__1 = (real) iym;
		y1 = r_lg10(&r__1) * *dy + y0;
		if (*if_ >= 2) {
		    i__2 = inx1;
		    for (ix = 1; ix <= i__2; ++ix) {
			x0 = (ix - 1) * *dx + *x - (float).08;
			x1 = x0 + (float).16;
			if (ix == 1 && *dx > (float)0.) {
			    x0 = *x;
			}
			if (ix == 1 && *dx < (float)0.) {
			    x1 = *x;
			}
			if (ix == inx1 && *dx > (float)0.) {
			    x1 = xm;
			}
			if (ix == inx1 && *dx < (float)0.) {
			    x0 = xm;
			}
			plot_(&x0, &y1, &c__3);
			plot_(&x1, &y1, &c__2);
		    }
		} else {
		    plot_(x, &y1, &c__3);
		    plot_(&xm, &y1, &c__2);
		}
	    }
	}
	y0 = iy * *dy + *y;
	plot_(x, &y0, &c__3);
	plot_(&xm, &y0, &c__2);
    }
    if (*if_ == 1) {		/* SOLID LINES */
	newpen_(&c__1);
    }
    return 0;
} /* lgrid_ */

