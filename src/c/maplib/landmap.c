
/* *** LAST REVISED ON 10-MAR-1994 07:18:28.88 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MAPLIB]LANDMAP.C */

#include "my.h"
#include <stdio.h>

#include "mapfiles.h"

/* *********************************************************************** */
/* this routines access a data file in the longlib graphics directory */
/* the name is defined in "mapfiles.h" as the string earthdat */
/* *********************************************************************** */

FILE *earth;

/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;

/******************************************************************************/

/* Subroutine */ int landmap_(ylat, xlong, slong)
real *ylat, *xlong, *slong;
{
    /* System generated locals */
    real r__1, r__2;

    /* Local variables */
    static logical last;
    extern /* Subroutine */ int plot_(), cterm_();
    static integer i;
    static real x, y, datin[10];
    static logical penup;
    static real x1, y1, y2;
    static integer ipt;

/* 	WRITTEN BY D. LONG JULY 1985  JPL */

/* 	DRAWS A LAND-EDGE MAP USING DATA FROM VECTOR LAND MAP FILE */
/* 	THIS ROUTINE USES A LINEAR PROJECTION, I.E. LAT/LONGS ARE ASSUMED */
/* 	TO BE X,Y POINTS ON A PLANE. */

/* 	YLAT	REAL	SCALE FACTOR LATITUDE INCH/360 DEGREES */
/* 	XLONG 	REAL	SCALE FACTOR LONGITUTDE INC/180 */
/* 	SLONG	REAL	LEFT-MOST LONGITUDE (-180 TO +180) */

/* 	ASSUMES THAT LONGLOC HAS BEEN ASSIGNED THE DIRECTORY OF THE */
/* 	EARTH.DAT FILE STORING THE EARTH LAND-EDGE MAP.*/

/* 	NOTE: SINCE MAP DATA HAS ITS ORIGIN FROM -180 TO 180, IF WE WANT */
/* 	THE MAP TO START FROM SOME OTHER POINT WE NEED TO DO SOME FANCY */
/* 	TRICKS */

/* 	OPEN DATA FILE */

    earth = fopen(earthdat,"r");
    if (feof(earth)) {
	cterm_(&c__1);
	printf("\n *** ERROR Opening EARTH.DAT data file: '%s' ***\n",earthdat);
	return 0;
    }
    ipt = 3;
    last = FALSE_;
    x = *xlong * (float)2.;

/* 	READ THE DATA */

L10:
    if (feof(earth))
	goto L999;

    fscanf(earth,"%f%f%f%f%f%f%f%f%f%f",&datin[0],&datin[1],&datin[2],
	&datin[3],&datin[4],&datin[5],&datin[6],&datin[7],&datin[8],
	&datin[9]);

/* 	CHECK THE STORED DATA COMMAND */

    for (i = 1; i <= 10; i += 2) {
	if ((integer) datin[i - 1] == 0 && (integer) datin[i] == 0) {
	    goto L20;
	}
	if (datin[i] == (float)888.8) {		/*  END OF LINE SEGMENT */
	    ipt = 3;
	    plot_(&x, &y, &ipt);
	    penup = TRUE_;
	    last = FALSE_;
	    x = *xlong * (float)2.;
	    goto L20;
	}
	if ((r__1 = datin[i - 1], dabs(r__1)) > (float)180.5 || (r__2 = datin[
		i], dabs(r__2)) > (float)91.) {		/* BAD POINT */
	    ipt = 3;
	    plot_(&x, &y, &ipt);
	    penup = TRUE_;
	    last = FALSE_;
	    x = *xlong * (float)2.;
	    goto L20;
	}
	penup = FALSE_;
	if (datin[i - 1] < *slong) {		/* LEFT OF DESIRED LONGITUDE */
	    if (last) {		/* CLIP INTERSECTION LINE */
		x1 = (datin[i - 1] + (float)360. - *slong) / (float)360. * *
			xlong;
		y1 = (datin[i] + (float)90.) / (float)180. * *ylat;
		y2 = y1 - (y - y1) * x1 / (x - x1);
		plot_(&x, &y2, &ipt);
		plot_(&x1, &y2, &c__3);
		plot_(&x1, &y1, &c__2);
		x = x1;
		y = y1;
	    } else {
		x = (datin[i - 1] + (float)360. - *slong) / (float)360. * *
			xlong;
		y = (datin[i] + (float)90.) / (float)180. * *ylat;
		plot_(&x, &y, &ipt);
	    }
	    ipt = 2;
	    last = FALSE_;
	} else {		/* RIGHT OF DESIRED LONGITUDE */

	    if (last) {
		x = (datin[i - 1] - *slong) / (float)360. * *xlong;
		y = (datin[i] + (float)90.) / (float)180. * *ylat;
		plot_(&x, &y, &ipt);
	    } else {		/* CLIP INTERSECTION LINE */
		x1 = (datin[i - 1] - *slong) / (float)360. * *xlong;
		y1 = (datin[i] + (float)90.) / (float)180. * *ylat;
		y2 = y - (y1 - y) * x / (x1 - x);
		plot_(&x, &y2, &ipt);
		plot_(&x1, &y2, &c__3);
		ipt = 3;
		if (penup) {
		    ipt = 3;
		}
		plot_(&x1, &y1, &ipt);
		x = x1;
		y = y1;
	    }
	    ipt = 2;
	    last = TRUE_;
	}
L20:
	;
    }
    goto L10;
L999:
    fclose(earth);
    return 0;
} /* landmap_ */

