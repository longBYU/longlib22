
/* *** LAST REVISED ON  5-FEB-1994 17:23:06.22 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MAPLIB]BITMAP.C */

#include "my.h"

/* Table of constant values */

static integer c__2 = 2;
static integer c__3 = 3;
static real c_b6 = (float)0.;

/* ********************************************************************* */

/* THE FOLLOWING ARE ROUTINES USING THE CIA LAND/SEA BIT MAP FILE */
/* SEE THE COMMENTS IN THE BITMAP AND LNDSEA ROUTINES */

/* ********************************************************************* */

/* Subroutine */ int bitmap_(clong, xlong, ylat, nxpix, nypix, iland)
real *clong, *xlong, *ylat;
integer *nxpix, *nypix, *iland;
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static logical land;
    static integer imap, line;
    static real rlat, rlon;
    extern /* Subroutine */ int plot_();
    static real xpix, ypix;
    static integer i;
    static real x, y;
    static integer iline;
    static logical penup;
    static real x0, y0, x1, y1, x2, y2;
    extern integer lndsea_();
    static logical option;
    static real ccc;

/* 	BITMAP USES THE FILE "LNDSEA1.DAT" TO DRAW AN EARTH LAND MASK WHERE */

/* 	THE LAND SURFACE OF THE EARTH IS DRAWN USING HORIZONTAL LINES */
/* 	ON A RECTANGULAR PROJECTION OF THE EARTH'S SURFACE (SEE LANDMAP). */
/* 	A GRID OF PIXELS IS USED TO LOCATE POINTS WHICH ARE "LOOKED UP" */
/* 	IN LNDSEA1.DAT (WHICH IS INTERPOLATED) TO DETERMINE IF EACH PIXEL */
/* 	IS LAND/SEA.  USING HORIZONTAL SCANS, A PLOT LINE IS GENERATED OF */
/* 	THE LAND/SEA AREA WHICH IS OUTPUT WHEN THE TYPE CHANGES.  NOTE */
/* 	FOR HIGH DENSITY PLOTS THIS OPERATION IS VERY SLOW DUE TO THE HIGH */
/* 	NUMBER OF FILE READS OF LNDSEA1.DAT REQUIRED. */

/* 	INPUTS: */
/* 		CLONG	(R)	LEFT SIDE LONGITUDE OF MAP (DEGREES -180,180) */
/* 		XLONG	(R)	LENGTH OF LONGITUDE AXIS (INCHES) */
/* 		YLAT	(R)	LENGTH OF LATTITUDE AXIS (INCHES) */
/* 		NXPIX	(I)	NUMBER OF PIXELS IN X DIRECTION */
/* 		NYPIX	(I)	NUMBER OF PIXELS IN Y DIRECTION */
/* 		ILAND	(I)	LAND/SEA FLAG */
/* 				 = 0 PLOT LAND */
/* 				 = 1 PLOT SEA */
/* 	OUPUTS: (NONE) */
/* 	CALLS: */
/* 		LNDSEA */
/* 		PLOT */

    xpix = (real) (*nxpix);
    ypix = (real) (*nypix);
    ccc = *xlong * (*clong + (float)180.) / (float)360.;
    option = TRUE_;
    if (*iland != 0) {
	option = FALSE_;
    }

    i__1 = *nypix;
    for (iline = 1; iline <= i__1; ++iline) {
	line = *nypix - iline + 1;
	rlat = (float)90. - (real) (line - 1) / ypix * (float)180.;
	penup = TRUE_;
	y = (ypix - (real) (line - 1)) * *ylat / ypix;
	x0 = (float)0.;
	y0 = y;
	i__2 = *nxpix;
	for (i = 1; i <= i__2; ++i) {
	    rlon = (real) (i - 1) / xpix * (float)360. - (float)180.;
	    x = (real) (i - 1) * *xlong / xpix;
	    if (rlon < (float)0.) {
		rlon += (float)360.;
	    }
	    imap = lndsea_(&rlat, &rlon);
	    land = TRUE_;
	    if (imap == 0) {
		land = FALSE_;
	    }
	    if (! land && option || ! option && land) {
		if (penup) {
		    x0 = x;
		    y0 = y;
		    penup = FALSE_;
		}
	    } else {
		if (! penup) {
		    x1 = x0 - ccc;
		    y1 = y0;
		    x2 = x - ccc;
		    y2 = y;
		    if (x1 <= (float)0.) {
			if (x2 < (float)0.) {
			    x1 += *xlong;
			    x2 += *xlong;
			    plot_(&x1, &y1, &c__3);
			    plot_(&x2, &y2, &c__2);
			} else {
			    x1 += *xlong;
			    plot_(&c_b6, &y1, &c__3);
			    plot_(&x2, &y2, &c__2);
			    plot_(&x1, &y1, &c__3);
			    plot_(xlong, &y2, &c__2);
			}
		    } else {
			if (x2 > (float)0.) {
			    plot_(&x1, &y1, &c__3);
			    plot_(&x2, &y2, &c__2);
			} else {
			    x2 += *xlong;
			    plot_(&c_b6, &y2, &c__3);
			    plot_(&x1, &y1, &c__2);
			    plot_(&x2, &y2, &c__3);
			    plot_(xlong, &y1, &c__2);
			}
		    }
		    penup = TRUE_;
		}
	    }
/* L50: */
	}
	if (! penup) {
	    plot_(&x0, &y0, &c__3);
	    plot_(&x, &y, &c__2);
	    penup = TRUE_;
	}
/* L100: */
    }
    return 0;
} /* bitmap_ */

