/* imagmap.f -- translated by f2c (version of 2 February 1991  11:28:34).
   You must link the resulting object file with the libraries:
	-lF77 -lI77 -lm -lc   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    integer lu, mp;
    real re[2], ox, oy, sf, px, py;
    integer mx, mw, mcol, msc;
    real pang, pvp[4];
} pxpcom_;

#define pxpcom_1 pxpcom_

/* Table of constant values */

static integer c__0 = 0;
static real c_b3 = (float)1.;
static integer c__1 = 1;
static real c_b7 = (float)0.;
static integer c_n1 = -1;
static real c_b17 = (float)4.;
static integer c_n3 = -3;
static integer c__50 = 50;
static integer c__100 = 100;
static real c_b37 = (float).12;
static real c_b38 = (float)6.2;
static integer c__101 = 101;
static real c_b50 = (float)90.;
static integer c_n101 = -101;
static integer c__5 = 5;
static integer c__2 = 2;
static integer c__3 = 3;
static integer c__2000 = 2000;
static integer c__2001 = 2001;
static integer c__32760 = 32760;
static integer c__2002 = 2002;

/* Main program */ MAIN__()
{
    /* System generated locals */
    integer i__1, i__2;
    real r__1;

    /* Builtin functions */
    double cos();
    integer i_nint();
    double r_nint();
    /* Subroutine */ int s_stop();

    /* Local variables */
    extern /* Subroutine */ int rect_(), plot_();
    static real rjxt, rjyt;
    extern /* Subroutine */ int axis3_();
    static integer i, j, n, ichan;
    extern /* Subroutine */ int frame_(), cterm_();
    static real stval[40000];
    extern /* Subroutine */ int rterm_(), rmpix_();
    static real xsize, ysize, af;
    static integer id, it;
    extern /* Subroutine */ int rammap_(), tekmap_(), terscl_(), plotnd_();
    static integer istval[40000], ix1, iy1;
    extern /* Subroutine */ int metmap2_();
    static real xsc, ysc;
    extern integer irmchan_();
    static integer ixr, iyr, ixt, iyt;
    static real rjx, rjy;
    static integer nsx, nsy, ixt1, iyt1;

/* *** LAST REVISED ON 12-APR-1991 14:35:42.27 */
/* *** SOURCE FILE: [LONGD.GRAPHICS]IMAGMAP.FOR */


/* 	OPEN PLOT PACKAGE */

    frame_(&c__0, &c__0, &c_b3, &c_b3, &c_b3);

/* 	SET SIZE AND SCALE FACTORS */

    nsx = 100;
    nsy = 100;
    xsize = (float)4.;
    ysize = (float)4.;

/* 	FILL ARRAY */

    i__1 = nsx;
    for (i = 1; i <= i__1; ++i) {
	i__2 = nsy;
	for (j = 1; j <= i__2; ++j) {
	    n = i + (j - 1) * nsx;
	    stval[n - 1] = cos(i * (float)6. / (real) nsx) * cos(j * (float)
		    5. / (real) nsy) + (float)1.;
	}
    }

/* 	DISPLAY IMAGE MAP TO TEKTRONICS TERMINAL */

    terscl_(&c__1, &it, &c_b7, &c_b7, &ixt, &iyt);
    terscl_(&c__1, &it, &xsize, &ysize, &ixt1, &iyt1);
    if (it > 0) {
/* IF PROPER TEK TERMINAL */
	rjxt = (real) (ixt1 - ixt) / (real) nsx;
	rjyt = (real) (iyt1 - iyt) / (real) nsy;

/* 	SCALE TO THE RANGE -15 TO 0 */

	i__1 = nsx * nsy;
	for (i = 1; i <= i__1; ++i) {
	    r__1 = stval[i - 1] * (float)7.5;
	    istval[i - 1] = -i_nint(&r__1);
	}
	cterm_(&c_n1);
	tekmap_(istval, &nsx, &nsy, &nsx, &nsy, &ixt, &iyt, &rjxt, &rjyt);
    }

/* 	DISPLAY IMAGE MAP TO RAMTEK DEVICE */

    rmpix_(&c_b7, &c_b7, &ixr, &iyr);
    rmpix_(&xsize, &ysize, &ix1, &iy1);
    rjx = (i__1 = ix1 - ixr, (real) abs(i__1)) / (real) nsx;
    rjy = (real) (iy1 - iyr) / (real) nsy;
    xsc = xsize / nsx;
    ysc = ysize / nsy;

/* 	SCALE TO (0..255) */

    i__1 = nsx * nsy;
    for (i = 1; i <= i__1; ++i) {
	r__1 = stval[i - 1] * 127;
	istval[i - 1] = i_nint(&r__1);
    }

/* 	PLOT TO RAMTEK ONLY IF RAMTEK IS OPEN */

    ichan = irmchan_(&id);
    if (ichan > 0) {
	rammap_(istval, &nsx, &nsy, &nsx, &nsy, &ixr, &iyr, &rjx, &rjy);
    }

/* 	SEND IMAGE MAP TO META FILE */

/* 	CALL METMAP(ISTVAL,NSX,NSY,NSX,NSY,0.,0.,XSIZE,YSIZE) */
    metmap2_(istval, &nsx, &nsy, &c__1, &c__1, &nsx, &nsy, &c_b7, &c_b7, &
	    xsize, &ysize);
    plot_(&c_b17, &c_b17, &c_n3);
    metmap2_(istval, &nsx, &nsy, &c__50, &c__50, &c__100, &c__100, &c_b7, &
	    c_b7, &xsize, &ysize);

/* 	NOW AXES PLOT TO ALL DEVICES */

    plot_(&c_b3, &c_b7, &c__0);

/* SET PLOT COLOR */
    rect_(&c_b7, &c_b7, &xsize, &ysize);
    af = r_nint(&xsize) + (float)1.0101;
    axis3_(&c_b7, &c_b7, "X", &c_n1, &xsize, &c_b7, &c_b7, &xsize, &af, &
	    c_b37, &c_b38, 1L);
    axis3_(&c_b7, &ysize, "X", &c__101, &xsize, &c_b7, &c_b7, &xsize, &af, &
	    c_b37, &c_b38, 1L);
    af = r_nint(&ysize) + (float)1.0101;
    axis3_(&c_b7, &c_b7, "Y", &c__1, &ysize, &c_b50, &c_b7, &ysize, &af, &
	    c_b37, &c_b38, 1L);
    axis3_(&xsize, &c_b7, "Y", &c_n101, &ysize, &c_b50, &c_b7, &ysize, &af, &
	    c_b37, &c_b38, 1L);
    plot_(&c_b7, &c_b7, &c__5);

/* 	CLEAR SCREENS AND CLOSE PACKAGES */

    cterm_(&c__2);
    rterm_(&c__2);
    plotnd_();
    s_stop("", 0L);
} /* MAIN__ */



/* Subroutine */ int metmap2_(iarray, na, ma, ns, ms, ne, me, xll, yll, xur, 
	yur)
integer *iarray, *na, *ma, *ns, *ms, *ne, *me;
real *xll, *yll, *xur, *yur;
{
    /* Initialized data */

    static real alim[2] = { (float)32.7,(float)32.7 };

    /* System generated locals */
    integer iarray_dim1, iarray_offset, i__1, i__2, i__3;

    /* Builtin functions */
    double cos(), sin();
    integer i_sign();

    /* Local variables */
    static real tang;
    static integer i1, i2;
    extern /* Subroutine */ int pplot_();
    static real av[2], xa, ya, ax, ay;
    static integer iv[2], nn, nx, ny, ix, iy;
    extern /* Subroutine */ int pplotp_();
    static integer nx1, nx2, ny1, ny2;


/* 	MAKE IMAGE MAP ON META FILE */

/* 	AUTHOR: DG LONG, JPL */
/* 	DATE: 25 JAN 1991 */

/* 	INPUTS: */
/* 	  IARRAY  : COLOR CODES */
/* 	  NA,MA	  : DIMENSIONS OF IARRAY */
/* 	  NS,MS	  : STARTING LOWER-LEFT CORNER ( 0 < NS < NA, 0 < MS < MA) */
/*	  NE,ME	  : ENDING UPPER-RIGHT CORNER  ( NS <= NS <= NA, MS <= MS <= MA
)*/
/* 	  	    OF RECTRANGLE TO PLOT (0 < NE-NS, ME-NS < 2048) */
/* 	  XLL,YLL : POSITION OF LOWER-LEFT CORNER OF MAP (IN PLOT UNITS) */
/* 	  XUR,YUR : POSITION OF UPPER-RIGHT CORNER OF MAP (IN PLOT UNITS) */

/* 	CALLS: */
/* 	  PPLOT */
/* 	  PPLOTP */



/* 	META FILE LIMITS ON X AND Y IN INCHES */

    /* Parameter adjustments */
    iarray_dim1 = *na;
    iarray_offset = iarray_dim1 + 1;
    iarray -= iarray_offset;

    /* Function Body */

    if (pxpcom_1.lu <= 0) {
	return 0;
    }

/* 	ENTER ORIGIN POINT IN METAFILE */

    pplot_(xll, yll, &c__3);

/* 	ENTER X,Y AXES LENGTHS */

    xa = *xll;
    ya = *yll;
    tang = pxpcom_1.pang * (float).0174532;
    av[0] = xa * cos(tang) - ya * sin(tang);
    av[1] = xa * sin(tang) + ya * cos(tang);
    ax = pxpcom_1.sf * av[0] + pxpcom_1.ox;
    ay = pxpcom_1.sf * av[1] + pxpcom_1.oy;
    xa = *xur;
    ya = *yur;
    tang = pxpcom_1.pang * (float).0174532;
    av[0] = xa * cos(tang) - ya * sin(tang);
    av[1] = xa * sin(tang) + ya * cos(tang);
    av[0] = pxpcom_1.sf * av[0] + pxpcom_1.ox - ax;
    av[1] = pxpcom_1.sf * av[1] + pxpcom_1.oy - ay;

    for (i1 = 1; i1 <= 2; ++i1) {
	if (av[i1 - 1] < (float)0.) {
	    av[i1 - 1] = (float)0.;
	}
	if (av[i1 - 1] > alim[i1 - 1]) {
	    av[i1 - 1] = alim[i1 - 1];
	}
	iv[i1 - 1] = av[i1 - 1] / pxpcom_1.re[i1 - 1];
/* L720: */
    }
    pplotp_(iv, &iv[1], &c__2000);

    nx1 = *ns;
    if (nx1 < 1) {
	nx1 = 1;
    }
    if (nx1 > 2047) {
	nx1 = 2047;
    }
    nx2 = *ne;
    if (nx2 < nx1) {
	nx2 = 1;
    }
    if (nx2 > 2048) {
	nx2 = 2048;
    }
    nx = nx2 - nx1 + 1;
    ny1 = *ms;
    if (ny1 < 1) {
	ny1 = 1;
    }
    if (ny1 > 2047) {
	ny1 = 2047;
    }
    ny2 = *me;
    if (ny2 < ny1) {
	ny2 = 1;
    }
    if (ny2 > 2048) {
	ny2 = 2048;
    }
    ny = ny2 - ny1 + 1;
    pplotp_(&nx, &ny, &c__2001);

/* 	OUTPUT MAP DATA IN Y-MAJOR ORDER, I.E., (1,1) (1,2) (1,3)... */

    nn = nx * ny;
    i2 = 1;
    i__1 = nx2;
    for (ix = nx1; ix <= i__1; ++ix) {
	i__2 = ny2;
	for (iy = ny1; iy <= i__2; ++iy) {
	    iv[i2 - 1] = iarray[ix + iy * iarray_dim1];
	    if ((i__3 = iv[i2 - 1], abs(i__3)) > 32760) {
		iv[i2 - 1] = i_sign(&c__32760, &iv[i2 - 1]);
	    }
	    ++i2;
	    if (i2 == 3) {
		pplotp_(iv, &iv[1], &c__2002);
		i2 = 1;
	    }
/* L100: */
	}
    }
    if (i2 == 2) {
	pplotp_(iv, &iv[1], &c__2002);
    }

    return 0;
} /* metmap2_ */

/* Main program alias */ int imagmap_ () { MAIN__ (); }
