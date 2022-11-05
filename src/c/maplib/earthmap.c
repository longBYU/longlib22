
/* *** LAST REVISED ON 10-MAR-1994 07:18:17.38 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MAPLIB]EARTHMAP.C */

#include "my.h"
#include <stdio.h>

#include "mapfiles.h"

/* *********************************************************************** */
/* this routines access a data file in the longlib graphics directory */
/* the name is defined in "mapfiles.h" as the string earthdat */
/* *********************************************************************** */

FILE *earth;

static integer c__1 = 1;

/* Subroutine */ int earth3d_(r, flat)
real *r, *flat;
{
    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    double sin();

    /* Local variables */
    static real alat;
    static integer i;
    static real v[4], datin[10], along;
    extern /* Subroutine */ int plot3d_(), cterm_();
    static integer id;
    extern /* Subroutine */ int sprect1_();
    static real rad;

/* 	WRITTEN BY D. LONG   JULY 1985 */
/* 	DRAWS DATA FROM LAND-EDGE MAP OF THE EARTH IN 3d WITH THE OPTION */
/* 	OF A SPHERICAL OR ELLIPSOIDAL EARTH */

/* 	R	(R): EARTH RADIUS (IN PLOT UNITS) */
/* 	FLAT	(R): EARTH FLATNESS */
/* 			= 0 FOR SPHERICAL EARTH */
/* 			= 3.3528132E-3 FOR ELLIPSOIDAL EARTH */

/* 	READS THE DATA FILE EARTH.DAT IN THE LONGLIB GRAPHICS */
/* 	DIRECTORY.  REQUIRES THE EARTH.DAT TO BE THIS DIRECTORY. */
/* 	USES THE INIT3D 3D PACKAGE BY CALLING PLOT3D */

/* 	OPEN FILE CONTAINING EARTH LOCATION DATA */

    earth = fopen(earthdat,"r");
    if (feof(earth)) {
	cterm_(&c__1);
	printf("\n *** ERROR Opening EARTH.DAT data file: '%s' ***\n",earthdat);
	return 0;
   }

/* 	BEGIN READING DATA */
    id = 3;
L10:
    if (feof(earth))
	goto L999;

    fscanf(earth,"%f%f%f%f%f%f%f%f%f%f",&datin[0],&datin[1],&datin[2],
	&datin[3],&datin[4],&datin[5],&datin[6],&datin[7],&datin[8],
	&datin[9]);

    for (i = 1; i <= 10; i += 2) {
	if ((integer) datin[i - 1] == 0 && (integer) datin[i] == 0) {
	    goto L20;
	}
	if (datin[i] == (float)888.8) {		/* END OF LINE SEGMENT */
	    id = 3;
	    goto L20;
	}
	if ((r__1 = datin[i - 1], dabs(r__1)) > (float)180.5 || (r__2 = datin[
		i], dabs(r__2)) > (float)91.) {	/* BAD DATA POINT */
	    goto L20;
	}

/* 	CONVERT INPUT LAT/LONG TO 3D VECTOR */

	along = datin[i - 1] * (float)3.141592654 / (float)180.;
	alat = datin[i] * (float)3.141592654 / (float)180.;

/* 	COMPUTE EARTH RADIUS ASSUMING ELLIPSOIDAL EARTH */

	rad = *r * ((float)1. - *flat * sin(alat));
	r__1 = datin[i] - (float)90.;
	alat = r__1 * (float)3.141592654 / (float)180.;
	sprect1_(v, &along, &alat, &rad);
	plot3d_(v, &v[1], &v[2], &id);
	id = 2;
L20:
	;
    }
    goto L10;
L999:

    fclose(earth);
    return 0;
} /* earth3d_ */
