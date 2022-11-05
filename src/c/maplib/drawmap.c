
/* *** LAST REVISED ON 10-MAR-1994 07:17:57.64 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.MAPLIB]DRAWMAP.C */

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
static integer c__5 = 5;
static real c_b9 = (float)0.;

/* Subroutine */ int drawmap_(name, irank, lu, slong, transform)
char *name;
integer *irank, *lu;
real *slong;
/* Subroutine */ int (*transform) ();
{
    /* Local variables */
    static integer iend;
    static real alat, alon;
    static integer icnt;
    static logical last;
    extern /* Subroutine */ int plot_(), cterm_();
    static real x, y, x1, y1, y2;
    static integer ic, ir;
    extern /* Subroutine */ int rmfile_();
    static integer ib1, ib2, ipt;


/* 	WRITTEN BY D. LONG MAY 1993  BYU */
/* 	DRAWS A *.MAP FILE USING A USER SPECIFIED PROJECTION ROUTINE */
/* 		"TRANSFORM(LATITUDE, LONGITUDE, IPEN)" */
/* 	WHERE IPEN=3 INDICATES "MOVE TO", AND IPEN=2 INDICATES "DRAW TO" */

/* 	NAME	CHAR	MAP FILE NAME */
/* 	IRANK	INT	SEGMENT RANK NUMBER TO DRAW (1 TO 15) */
/* 	LU	INT	FILE UNIT NUMBER  (not used in C version) */
/* 	SLONG	REAL	STARTING LONGITUDE (-180 TO +180) */
/* 	TRANSFORM EXTERNAL FUNCTION */

/* 	OPEN DATA FILE */

    earth = fopen(earthdat,"r");
    if (feof(earth)) {
	cterm_(&c__1);
	printf("\n *** ERROR Opening EARTH.DAT data file: '%s' ***\n",earthdat);
	return 0;
    }
    icnt = 0;
    iend = 0;

/* 	READ DATA */

L10:
    rmfile_(earth, &ib1, &ib2, &ic, &icnt, &iend);
    if (iend < 0) {
	goto L99;
    }

    if (ic < 0) {
	ir = ib1;		/* SEGMENT RANK */
	ipt = 3;
	last = FALSE_;
	x = *slong + (float)360.;
    } else {
	if (ir != *irank) {
	    goto L10;
	}
	alat = (real) ib1 / (float)3600.;
	alon = (real) ib2 / (float)3600.;

	if (alon < *slong) {	/* LEFT OF DESIRED START LONGITUDE */

	    if (last) {		/* CLIP INTERSECTION LINE FOR START LONGITUDE */
		x1 = alon + (float)360.;
		y1 = alat;
		y2 = y1 - (y - y1) * x1 / (x - x1);
		(*transform)(&y2, &x, &ipt);
		(*transform)(&y2, &x1, &c__3);
		(*transform)(&y1, &x1, &c__2);
		x = x1;
		y = y1;
	    } else {
		x = alon + (float)360.;
		y = alat;
		(*transform)(&y, &x, &ipt);
	    }
	    ipt = 2;
	    last = FALSE_;
	} else {		/* RIGHT OF DESIRED STARTING LONGITUDE */

	    if (last) {
		x = alon;
		y = alat;
		(*transform)(&y, &x, &ipt);
	    } else {		/* CLIP INTERSECTION LINE */
		x1 = alon;
		y1 = alat;
		y2 = y - (y1 - y) * x / (x1 - x);
		(*transform)(&y2, &x, &ipt);
		(*transform)(&y2, &x1, &c__3);
		ipt = 3;
		(*transform)(&y1, &x1, &ipt);
		x = x1;
		y = y1;
	    }
	    ipt = 2;
	    last = TRUE_;
	}
    }

    goto L10;
L99:
    plot_(&c_b9, &c_b9, &c__5);
    fclose(earth);
    return 0;
} /* drawmap_ */

