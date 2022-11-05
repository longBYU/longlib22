
/* *** LAST REVISED ON 10-MAR-1994 07:19:12.35 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MAPLIB]WORLDMAP.C */

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
static integer c__5 = 5;
static real c_b11 = (float)360.;
static real c_b12 = (float)0.;

/* Subroutine */ int worldmap_(xform, alatmin, alatmax, alonmin, alonmax, 
	ipflag, ilu)
/* Subroutine */ int (*xform) ();
real *alatmin, *alatmax, *alonmin, *alonmax;
integer *ipflag, *ilu;
{
    /* System generated locals */
    real r__1, r__2;

    /* Builtin functions */
    double r_mod();

    /* Local variables */
    static real alat, alon;
    extern /* Subroutine */ int plot_(), cterm_();
    static integer i;
    static real datin[10];
    static integer ipt;

/* 	WRITTEN BY D. LONG NOV. 1992 */

/* 	DRAWS A LAND-EDGE MAP USING DATA FROM VECTOR LAND MAP FILE */
/* 	USES USER SUPPLIED TRANSFORMATION */

/* 	XFORM	*	USER SUPPLIED SUBROUTINE TO PERFORM TRANSFORMATION */
/* 	ALATMIN, ALATMAX REAL	MIN, MAX LATTITUDE TO ATTEMPT TO PLOT */
/* 	ALONMIN, ALONMAX REAL	MIN, MAX LONGITUDE TO PLOT */
/* 	IPFLAG	INT	LONGITUDE OPTION FLAG FOR ALONMAX, ALONMIN */
/* 			= 0 IGNORE MIN, MAX LONGITUDE */
/* 			= 1 USE +/- 180 */
/* 			= 2 USE 0 TO 360 */
/* 	ILU	INT	FORTRAN UNIT NUMBER TO USE FOR DATA FILE READING */

/* 	OPEN DATA FILE */

    earth = fopen(earthdat,"r");
    if (feof(earth)) {
	cterm_(&c__1);
	printf("\n *** ERROR Opening EARTH.DAT data file: '%s' ***\n",earthdat);
	return 0;
    }

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
	if (datin[i] == (float)888.8) {	/* END OF SEGMENT */
	    ipt = 3;
	    (*xform)(&alon, &alat, &ipt);
	    goto L20;
	}
	if ((r__1 = datin[i - 1], dabs(r__1)) > (float)180.5 || (r__2 = datin[
		i], dabs(r__2)) > (float)91.) {	/* BAD POINT */
	    ipt = 3;
	    goto L20;
	}
	r__1 = datin[i - 1] + (float)360.;
	alon = r_mod(&r__1, &c_b11);
	alat = datin[i];
	if ((real) (*ipflag) != (float)0.) {
	    if (*ipflag == 1) {
		if (alon > (float)180.) {
		    alon += (float)-360.;
		}
	    }
	    if (alat > *alatmin && alat < *alatmax && alon > *alonmin && alon 
		    < *alonmax) {
		(*xform)(&alon, &alat, &ipt);
		ipt = 2;
	    } else {
		if (ipt == 2) {
		    (*xform)(&alon, &alat, &ipt);
		}
		ipt = 3;
	    }
	} else {
	    (*xform)(&alon, &alat, &ipt);
	    ipt = 2;
	}
L20:
	;
    }
    goto L10;
L999:
    fclose(earth);
    plot_(&c_b12, &c_b12, &c__5);
    return 0;
} /* worldmap_ */

