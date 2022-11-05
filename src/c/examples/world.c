
/* *** LAST REVISED ON 24-FEB-1994 01:43:21.21 */
/* *** SOURCE FILE: [LONGLIB93.SOURCES.C.EXAMPLES]WORLD.C */

#include "my.h"

/* Table of constant values */

static integer c_n1 = -1;
static integer c__0 = 0;
static integer c__1 = 1;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__4 = 4;
static integer c__5 = 5;
static integer c__6 = 6;
static real c_b9 = (float)-.5;
static real c_b5 = (float)0.;
static real c_b3 = (float)5.;
static real c_b11 = (float).03;

int main()
{
    /* System generated locals */
    integer i__1, i__2;
    real r__1;

    /* Builtin functions */
    double sin();

    /* Local variables */
    static real alat, flat;
    static integer ilat;
    static real fpts;
    extern /* Subroutine */ int plot_();
    static integer npts;
    static real f, r, v[3], x, y, z;
    extern /* Subroutine */ int frame_();
    static real along;
    static integer ilong;
    extern /* Subroutine */ int cterm_(), rterm_();
    static real f3;
    extern /* Subroutine */ int init3d_(), plot3d_();
    static integer id;
    static real ds;
    extern /* Subroutine */ int newpen_(), plotnd_(), symbol_(), earth3d_(), 
	    sprect1_();
    static real rad, res;

/* 	AND EXAMPLE OF USING THE MAPLIB ROUTINES. */
/* 	THIS PROGRAM WILL PLOT A 3-D MAP OF THE WORLD WITH */
/* 	BINNING GRID INFORMATION ON IT. */

    r = (float)6378.1778;	/* RADIUS OF THE EARTH IN KM */
    flat = (float).0033528132;	/* FLATNESS OF EARTH */
    f3 = (float)2e-5;		/* 3D SCALE FACTOR */
    f = (float)5.;		/* PLOTTING SCALE FACTOR */
    x = (float)100.;		/* VIEW POINT LOCATION */
    y = (float)100.;
    z = (float)100.;
    ds = (float)600.;		/* PERSPECTIVE FACTOR */
    res = (float)20.;

/* LAT/LONG GRID RESOLUTION */
    npts = (float)180. / res;
    fpts = (real) npts;

/* 	OPEN LONGLIB PACKAGE WITH PROMPT FOR SCREEN DEVICE */

    frame_(&c__3, &c__0, &c_b3, &c_b3, &f);

/* 	INITIALIZE 3D ROUTINES */

    init3d_(&x, &y, &z, &c_b5, &c_b5, &c_b5, &c_b5, &ds, &f3);

/* 	PLOT A 2D LABEL (DOESN'T USE 3D ROUTINES) */

    symbol_(&c_b9, &c_b9, &c_b11, "WORLD", &c_b5, &c__5, &c_n1, 5L);

/* 	PLOT EARTH LAT/LONG GRID IN 3D */

    newpen_(&c__4);
    i__1 = npts;
    for (ilat = 2; ilat <= i__1; ++ilat) {
	r__1 = (ilat - 1) * (float)180. / fpts;
	alat = r__1 * (float)3.141592654 / (float)180.;
	id = 3;
	i__2 = (npts << 1) + 1;
	for (ilong = 1; ilong <= i__2; ++ilong) {
	    r__1 = (ilong - 1) * (float)180. / fpts;
	    along = r__1 * (float)3.141592654 / (float)180.;
	    rad = r * ((float)1. - flat * sin(alat));
	    sprect1_(v, &along, &alat, &rad);
	    plot3d_(v, &v[1], &v[2], &id);
	    id = 2;
/* L310: */
	}
    }
    newpen_(&c__6);
    i__2 = (npts << 1) + 1;
    for (ilong = 1; ilong <= i__2; ++ilong) {
	r__1 = (ilong - 1) * (float)180. / fpts;
	along = r__1 * (float)3.141592654 / (float)180.;
	id = 3;
	i__1 = npts + 1;
	for (ilat = 1; ilat <= i__1; ++ilat) {
	    r__1 = (ilat - 1) * (float)180. / fpts;
	    alat = r__1 * (float)3.141592654 / (float)180.;
	    rad = r * ((float)1. - flat * sin(alat));
	    sprect1_(v, &along, &alat, &rad);
	    plot3d_(v, &v[1], &v[2], &id);
	    id = 2;
/* L320: */
	}
    }
    plot_(&c_b5, &c_b5, &c__3);

/* 	ADD LAND MAP */

    newpen_(&c__1);
    earth3d_(&r, &flat);
    plot_(&c_b5, &c_b5, &c__3);

    rterm_(&c__2);
    cterm_(&c__2);
    plotnd_();
}

