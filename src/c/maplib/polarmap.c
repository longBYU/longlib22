
/* *** LAST REVISED ON 10-MAR-1994 07:18:54.19 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MAPLIB]POLARMAP.C */

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
static real c_b11 = (float)1.;

/******************************************************************************/

/* Subroutine */ int polarmap_(x0, y0, rad, ang)
real *x0, *y0, *rad, *ang;
{
    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    double r_sign(), cos(), sin();

    /* Local variables */
    static real alat;
    extern /* Subroutine */ int plot_(), cterm_();
    static real a;
    static integer i;
    static real r, x, y, datin[10], along, ar, dtr;
    static integer ipt;

/* 	WRITTEN BY D. LONG JULY 1985  JPL */

/* 	DRAWS A LAND-EDGE MAP USING DATA FROM VECTOR LAND MAP FILE */
/* 	THIS ROUTINE USES A POLAR PROJECTION, I.E. LATTITUDE IS ASSUMED */
/* 	TO BE A LINEAR RADIUS FROM THE POLE. */

/* 	X0,Y0	REAL	ORIGIN OF THE POLE */
/* 	RAD	REAL	RADIUS OF EQUATOR */
/* 			> 0 NORTHERN HEMISPHERE */
/* 			< 0 SOUTHERN HEMISPHERE */
/* 	ANG	REAL	ANGLE OF PRIME MERIDAN FROM HORIZONTAL (DEG CCW) */

/* 	OPEN DATA FILE */

    earth = fopen(earthdat,"r");
    if (feof(earth)) {
	cterm_(&c__1);
	printf("\n *** ERROR Opening EARTH.DAT data file: '%s' ***\n",earthdat);
	return 0;
    }

    dtr = (float).017453292222222222;
    ar = dabs(*rad) / (float)90.;
    ipt = 3;

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
	if (datin[i] == (float)888.8) {
	    ipt = 3;
	    goto L20;
	}
	if ((r__1 = datin[i - 1], dabs(r__1)) > (float)180.5 || (r__2 = datin[
		i], dabs(r__2)) > (float)91.) {
	    ipt = 3;
	    goto L20;
	}
	if (r_sign(&c_b11, &datin[i]) != r_sign(&c_b11, rad)) {
	    ipt = 3;
	} else {
	    along = datin[i - 1];
	    alat = datin[i];
	    r = ((float)90. - dabs(alat)) * ar;
	    a = dtr * (along * r_sign(&c_b11, rad) + *ang);
	    x = cos(a) * r + *x0;
	    y = sin(a) * r + *y0;
	    plot_(&x, &y, &ipt);
	    ipt = 2;
	}
L20:
	;
    }
    goto L10;
L999:
    fclose(earth);
    return 0;
} /* polarmap_ */

