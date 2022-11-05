/* earth3d.f -- translated by f2c (version of 2 February 1991  11:28:34).
   You must link the resulting object file with the libraries:
	-lF77 -lI77 -lm -lc   (in that order)
*/

#include "my.h"

/* Table of constant values */

static integer c__10 = 10;


/* *** LAST REVISED ON 26-JUN-1990 10:24:40.85 */
/* *** SOURCE FILE: [DL.GRAPHICS.LONGLIB77]MAPLIB.FOR */

/* *********************************************************************** */

/* 	SOURCE CODE FOR THE WORLD MAP ROUTINES OF THE LONGLIB GRAPHICS */
/* 	LIBRARY.  THESE ROUTINES ACCESS A DATA FILE WITHIN THE LONGLIB */
/* 	GRAPHICS DIRECTORY.  TO ACCESS THIS FILE THE DIRECTORY */
/* 	/home1/LongLib/aaData/ MUST BE DEFINED. */

/* *********************************************************************** */

/* Subroutine */ int earth3d_(r, flat)
real *r, *flat;
{
    /* Format strings */
    static char fmt_1005[] = "(10f8.0)";

    /* System generated locals */
    integer i__1;
    real r__1, r__2;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(), s_rsfe(), do_fio(), e_rsfe();
    double sin();
    integer f_clos();

    /* Local variables */
    static real alat;
    static integer i;
    static real v[4], datin[10], along;
    extern /* Subroutine */ int plot3d_();
    static integer id;
    extern /* Subroutine */ int sprect1_();
    static real rad;
    static integer ipt;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 2, 1, fmt_1005, 0 };



/* 	WRITTEN BY D. LONG   JULY 1985 */
/* 	DRAWS DATA FROM LAND-EDGE MAP OF THE EARTH IN 3d WITH THE OPTION */
/* 	OF A SPHERICAL OR ELLIPSOIDAL EARTH */

/* 	R	(R): EARTH RADIUS (IN PLOT UNITS) */
/* 	FLAT	(R): EARTH FLATNESS */
/* 			= 0 FOR SPHERICAL EARTH */
/* 			= 3.3528132E-3 FOR ELLIPSOIDAL EARTH */

/* 	READS THE DATA FILE EARTH.DAT IN THE LONGLIB GRAPHICS */
/* 	DIRECTORY.  REQUIRES /home1/LongLib/aaData/ TO BE THIS DIRECTORY. */
/* 	USES FORTRAN FILE UNIT NUMBER 2 FOR READING A FILE. */

/* 	USES THE INIT3D 3D PACKAGE BY CALLING PLOT3D */


/* 	DEFINE DEGREE TO RADIAN CONVERSION */


/* 	OPEN FILE CONTAINING EARTH LOCATION DATA */

    o__1.oerr = 0;
    o__1.ounit = 2;
    o__1.ofnmlen = 36;
    o__1.ofnm = "/rainier/c/users/long/LL77/EARTH.DAT";
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);

/* 	BEGIN READING DATA */

    id = 3;
L10:
    i__1 = s_rsfe(&io___2);
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = do_fio(&c__10, (char *)&datin[0], (ftnlen)sizeof(real));
    if (i__1 != 0) {
	goto L999;
    }
    i__1 = e_rsfe();
    if (i__1 != 0) {
	goto L999;
    }

    for (i = 1; i <= 10; i += 2) {
	if ((integer) datin[i - 1] == 0 && (integer) datin[i] == 0) {
	    goto L20;
	}
	if (datin[i] == (float)888.8) {

/* 	END OF LINE SEGMENT */

	    id = 3;
	    goto L20;
	}
	if ((r__1 = datin[i - 1], dabs(r__1)) > (float)180.5 || (r__2 = datin[
		i], dabs(r__2)) > (float)91.) {
/* 	BAD DATA POINT */
	    ipt = 3;
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

    cl__1.cerr = 0;
    cl__1.cunit = 2;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* earth3d_ */

